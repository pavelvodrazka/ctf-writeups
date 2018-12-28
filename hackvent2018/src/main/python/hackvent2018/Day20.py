#!/usr/bin/env python3

from tools.spritz import Spritz

spritz = Spritz()

K = bytearray(b'shuffle*whip$crush%squeeze\0')
M = bytearray.fromhex('f42df92b389fffca59598465c7a51d36082ecfea567a900e5eac9e5e9fb1')
C = spritz.encrypt(K, M)

print("flag: " + C.decode("utf-8"))
