#!/usr/bin/env python2

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
