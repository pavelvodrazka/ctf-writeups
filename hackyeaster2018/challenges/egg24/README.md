# 24 - ELF

The Egg Liberation Front (ELF) already marked this binary. Go ahead and free the egg!

Once the right PIN is provided, the binary spills out the Easter egg QR code.

[lock](files/lock)

### Solution

The lock binary was a 32-bit ELF.

```bash
$ file lock
lock: ELF 32-bit LSB shared object Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=8272392507ce63b716cc2e9c0feb001a5467ae53, not stripped
```

I decompiled it with IDA, but the result was confusing.

```c
int __cdecl __noreturn main(int argc, const char **argv, const char **envp) {
  if (argc == 2) {
    pin = atoi(argv[1]);
    mainPrg();
  } else {
    printf(help);
  }
  exit(0);
}

char *mainPrg() {
  char *result; // eax
  char *retaddr; // [esp+4h] [ebp+4h]

  printf(title);
  result = retaddr + 229;
  if (retaddr == (char *)-229)
    result = (char *)checkpin(0);
  return result;
}

int checkpin() {
  int result; // eax

  if (dword_204B >= dword_20AF)
    result = printqr(&qr2);
  else
    result = printqr(&qr1);
  return result;
}

int __cdecl printqr(int a1) {
  int v1; // edi
  int v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v3 = 0;
  printf(nl);
  do {
    printf(white);
    v1 = *(_DWORD *)(a1 + 4 * v3) << 6;
    v4 = 0;
    while (1) {
      if (v1 >= 0)
        printf(white);
      else
        printf((const char *)&black);
      if (++v4 == 25)
        break;
      v1 *= 2;
    }
    printf(nl);
    ++v3;
  } while (v3 != 25);
  return printf(nl);
}
```

It looked like the pin value was completely ignored which didn't make any sense. The `checkpin` function only compared the fourth elements of `qr1` and `qr2` int arrays and decided which QR code was printed. The first naive thing I tried was to invert that condition, but the result wasn't a QR code. 

I returned back to IDA and looked at the assembly code again. Luckily I noticed a `sp-analysis failed` error which apparently caused the decompilation process to fail. Then I found an interesting section of code at `075D` which wasn't decompiled to the pseudo-c source code. I converted it to a function.

```c
void __usercall sub_75B(int a1@<ebp>) {
  int v1; // ebx
  int v2; // ecx
  int v3; // eax
  int v4; // ecx

  v1 = 0;
  v2 = 0;
  do
    v1 += *((_DWORD *)&qr1 + v2++); // sums all int elements of qr1 array
  while (v2 != 25);
  v3 = *((_DWORD *)&qr1 - 1); // loads entered pin which is stored right before qr1
  if (v3 == v1) { // pin == sum(qr1) ?
    v4 = 0;
    do
      *((_DWORD *)&qr1 + v4++ + 25) -= v3; // subtracts pin value from the elements of qr2 (&qr1 + 25 points to qr2)
    while (v4 != 25);
  }
  JUMPOUT(__CS__, *(_DWORD *)(a1 + 4) + 62);
}
```

The function tried to hide what it was doing, but it wasn't that hard to figure it out. It compared the entered pin to the sum of all int elements of `qr1`. In case they were equal it subtracted the pin value from the elements of `qr2`. This operation caused that the other branch of the condition in `checkpin` was executed and the modified `qr2` was printed.

I wrote a simple [C program](files/calcpin.c) to calculate the pin.

```bash
$ gcc -o calcpin calcpin.c && ./calcpin 
pin: 1098505442
$ ./lock 1098505442
lock state: 


  ██████████████    ██        ██████  ██████████████
  ██          ██  ████  ██████████    ██          ██
  ██  ██████  ██    ██████        ██  ██  ██████  ██
  ██  ██████  ██  ████  ██    ██      ██  ██████  ██
  ██  ██████  ██      ██  ██    ████  ██  ██████  ██
  ██          ██  ██  ██    ██████    ██          ██
  ██████████████  ██  ██  ██  ██  ██  ██████████████
                          ██    ██                  
  ██████████  ██████████  ████    ████  ██  ██  ██  
        ████      ████      ██    ██        ██  ██  
  ██  ██  ██  ████  ██  ████  ████████  ████      ██
  ██  ████      ██  ██████    ████████████████  ████
    ██████    ██  ████  ██  ████      ██  ██  ██████
  ████  ██████    ██  ██  ██████    ██  ██  ████    
  ██  ████  ██████          ██  ████  ██    ██  ████
  ██      ██    ████████  ██    ████████  ████    ██
  ██  ██  ██████  ██  ██  ██  ██████████████████    
                  ██████    ████  ██      ██  ██    
  ██████████████  ██    ████    ████  ██  ██    ████
  ██          ██      ████        ██      ██      ██
  ██  ██████  ██  ████  ████  ████████████████      
  ██  ██████  ██  ██  ██  ████      ████████  ██████
  ██  ██████  ██  ██      ████      ████    ██    ██
  ██          ██  ████    ██  ██████        ██    ██
  ██████████████  ██        ████          ██  ██████

```

The last step to get the flag was to scan that QR code.

### Flag

```
he18-L88o-1ZeU-xNVF-zXKp
```