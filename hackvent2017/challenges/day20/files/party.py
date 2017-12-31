#!/usr/bin/env python

import random
import string
import os

keywords = ['mUff!n', 'h4x', 'l3l', 'f4k3', 'wUt', 'p4rty', 'hackers?!', 'whadup', 'ok', 'cool', 'yougotit' ,'letmein', 'foundme',
'yeahyeah', 'whatsgoinon', 'shellz', 'parteeeeeyyz', 'nomonom', 'chips', 'pancakes', 'beach', 'random', 'wait', 'cooooool', 'eeeleeeeeet',
'hackveeeent', 'sw1ss', 'sw1ssfr13nds', 'w@@@@@@t', 'wo0t', '11010100101010010010101', 'funfunfun', 'techno', 'rock', 'guitar', 'ukulele' ]

dirs = [
    '/home/bot',
    '/home/alpha',
    '/home/beta',
    '/home/charlie',
    '/home/delta',
    '/var/www',
    '/etc/apache2'
    '/etc/mysql'
]

def gen_fake(): return 'HV17' + ''.join(['-' + random.choice(keywords) for i in range(random.randrange(3,6))])
def get_random_file_name(): return random.choice(['.','']) + ''.join([random.choice(string.ascii_letters) for i in range(random.randrange(10,32))])
def gen_rnd_txt(): return ''.join([random.choice(keywords) for i in range(random.randrange(100,200))])

random_dirs = []

for i in range(random.randrange(20,30)):
    rand_dir = random.choice(dirs) + '/' +get_random_file_name()

    try:
        if not os.path.exists(rand_dir): os.makedirs(rand_dir)
    except: pass

    random_dirs.append(rand_dir)


for i in range(random.randrange(40,50)):
    rand_file = random.choice(random_dirs) + '/' + get_random_file_name()
    rand_txt = ''

    for j in range(random.randrange(3, 6)): rand_txt += ('\n'*random.randrange(1,3)) +  (gen_fake() if random.choice([True, False]) else gen_rnd_txt())
    try:
        with open(rand_file, 'wb') as write_rand_file: write_rand_file.write(rand_txt)
    except: pass
