# Day 08: True 1337s

*... can read this instantly*

I found this obfuscated code on a public FTP-Server. But I don't understand what it's doing...

[Download](files/True.1337 "True.1337")

### Solution

After analyzing given file it looks like two lines of an obfuscated Python code. When you try to run it as is you get `SyntaxError: invalid syntax`.

Let's take a closer look at the first line of code. It calls `exec` and passes some obfuscated text as its argument. The first thing which comes to my mind is to change `exec` to `print`, comment out the second line and run the program to see what is going on inside.

```bash
$ python True.1337 
A=chr;__1337=exec;SANTA=input;FUN=print
def _1337(B):return A(B//1337)
```

The first line of output defines aliases and the second one defines a function `_1337`. When we apply given alias for `A` we get this line of code.

```python
def _1337(B):return chr(B//1337)
```

Now it's time to analyze the second line. We know that `__1337` is alias for `exec`. Let's try the same thing as we did with the first line and print the result.

```python
C=SANTA("?")
if C=="1787569":FUN(''.join(chr(ord(a) ^ ord(b)) for a,b in zip("\x7B\x67\x05\x06\x18\x4D\x5A\x07\x46\x1E\x5F\x4D\x0C\x43\x14\x5F\x03\x58\x0B\x19\x5C\x07\x45\x52\x1E\x46\x5B\x58\x13","31415926535897932384626433832")))
```

When we apply the rest of aliases and remove the input check we get this simple [Python code](../../src/main/python/hackvent2017/Day08.py "Day08.py").

```python
print(''.join(chr(ord(a) ^ ord(b)) for a,b in zip("\x7B\x67\x05\x06\x18\x4D\x5A\x07\x46\x1E\x5F\x4D\x0C\x43\x14\x5F\x03\x58\x0B\x19\x5C\x07\x45\x52\x1E\x46\x5B\x58\x13","31415926535897932384626433832")))
```

The last step is to run this code and the flag gets printed.

```
HV17-th1s-ju5t-l1k3-j5sf-uck!
```