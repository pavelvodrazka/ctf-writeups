# Day 13: muffin_asm

*As M. said, kind of a different architecture!*

ohai \o/

How about some custom asm to obsfucate the codez?

[Download](files/muffin_asm.py "muffin_asm.py")

### Solution

When we run the Python program we are asked to enter a flag which gets validated. We have to reverse the program in order to find the valid flag.

The first step is to add debug messages with state of registers and instructions flow to figure out what's going on inside. To do that I extended the `run` function a bit:

```python
def run(codez):
    global ip
    
    show_ins = True
    show_regs = True
    
    while ip < len(codez):
        c_ins = ins[ord(codez[ip])]
        c_ins_name = c_ins.func_name
        if show_regs: print(" > ip={0}, r={1}, f={2}".format(ip, r, f))
        if c_ins in [_je, _jne]:
            old_ip = ip
            c_ins_args = [struct.unpack('<I', codez[(ip+1):(ip+5)])[0]]
            if show_ins: print(" {0}({1})".format(c_ins_name, c_ins_args[0]))
            c_ins(struct.unpack('<I', codez[(ip+1):(ip+5)])[0])
            if old_ip == ip: ip += 5
            continue
        num_of_args = c_ins.func_code.co_argcount
        if num_of_args == 0:
            if show_ins: print(" {0}()".format(c_ins_name))
            c_ins()
        elif num_of_args == 1:
            c_ins_args = [ord(codez[ip+1])]
            if show_ins: print(" {0}({1})".format(c_ins_name, c_ins_args[0]))
            c_ins(ord(codez[ip+1]))
        else:
            c_ins_args = [ord(codez[ip+1]), ord(codez[ip+2])]
            if show_ins: print(" {0}({1},{2})".format(c_ins_name, c_ins_args[0], c_ins_args[1]))
            c_ins(ord(codez[ip+1]), ord(codez[ip+2]))
        ip += (1 + num_of_args)
```

Then I ran the program and focused on `_rchr` instructions which read characters of entered flag.

```bash
$ echo "HV17-?" | ./Day13.py | grep -B 1 -A 4 _rchr
 > ip=3609, r=[72, 0, 0, 0], f=[False]
 _rchr(2)
 > ip=3611, r=[72, 0, 72, 0], f=[False]
 _cmp(2,0)
 > ip=3614, r=[72, 0, 72, 0], f=[True]
 _jne(19335)
--
 > ip=3994, r=[0, 0, 86, 0], f=[True]
 _rchr(1)
 > ip=3996, r=[0, 86, 86, 0], f=[True]
 _cmp(1,2)
 > ip=3999, r=[0, 86, 86, 0], f=[True]
 _jne(19335)
--
 > ip=4379, r=[0, 0, 49, 0], f=[True]
 _rchr(0)
 > ip=4381, r=[49, 0, 49, 0], f=[True]
 _cmp(0,2)
 > ip=4384, r=[49, 0, 49, 0], f=[True]
 _jne(19335)
--
 > ip=4764, r=[0, 0, 55, 0], f=[True]
 _rchr(3)
 > ip=4766, r=[0, 0, 55, 55], f=[True]
 _cmp(3,2)
 > ip=4769, r=[0, 0, 55, 55], f=[True]
 _jne(19335)
--
 > ip=5149, r=[0, 45, 0, 0], f=[True]
 _rchr(3)
 > ip=5151, r=[0, 45, 0, 45], f=[True]
 _cmp(3,1)
 > ip=5154, r=[0, 45, 0, 45], f=[True]
 _jne(19335)
--
 > ip=5534, r=[109, 0, 0, 0], f=[True]
 _rchr(1)
 > ip=5536, r=[109, 63, 0, 0], f=[True]
 _cmp(1,0)
 > ip=5539, r=[109, 63, 0, 0], f=[False]
 _jne(19335)
```

As we can see the next expected character of the flag is the only non-zero value present in a register `r` at the moment of `_rchr` instruction execution. We can take advantage of this and modify `_rchr` instruction to simply read that value from the register instead of standard input and print it to standard output to reveal the expected flag.

The modified `_rchr` instruction looks like this:

```python
def _rchr(r1):
    r[r1] = filter(bool, r)[0]
    sys.stdout.write(chr(r[r1]))
```

Now it's time to run the modified Python program (source code can be found [here](../../src/main/python/hackvent2017/Day13.py)).

```
$ ./Day13.py
[ muffin asm ]
muffinx: Did you ever codez asm?
<< flag_getter v1.0 >>
ohai, gimmeh flag: HV17-mUff!n-4sm-!s-cr4zY
[+] valid! by muffinx :D if you liked the challenge, troll me @ twitter.com/muffiniks =D
```

The expected flag is:

```
HV17-mUff!n-4sm-!s-cr4zY
```