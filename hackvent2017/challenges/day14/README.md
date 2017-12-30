# Day 14: Happy Cryptmas

todays gift was encrypted with the attached program. try to unbox your xmas present.

```
Flag: 7A9FDCA5BB061D0D638BE1442586F3488B536399BA05A14FCAE3F0A2E5F268F2F3142D1956769497AE677A12E4D44EC727E255B391005B9ADCF53B4A74FFC34C
```

[Download](files/happy_cryptmas.zip "muffin_asm.py")

### Solution

Let's take a look what we've got.

```bash
$ unzip happy_cryptmas.zip 
Archive:  happy_cryptmas.zip
  inflating: hackvent                
$ file hackvent 
hackvent: Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|PIE>
```

IDA is very useful tool when it comes to decompiling executables into a pseudocode to figure out what cipher is used inside.

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  __int64 v3; // rdx
  size_t v4; // rsi
  int result; // eax
  const char **v6; // [rsp+50h] [rbp-70h]
  char v7; // [rsp+60h] [rbp-60h]
  char v8; // [rsp+70h] [rbp-50h]
  char v9; // [rsp+80h] [rbp-40h]
  char v10; // [rsp+A0h] [rbp-20h]
  __int64 v11; // [rsp+B8h] [rbp-8h]

  v6 = argv;
  if ( argc != 1 )
  {
    __gmpz_init(&v8, argv, envp);
    __gmpz_init(&v7, argv, v3);
    __gmpz_init_set_str(&v10, "F66EB887F2B8A620FD03C7D0633791CB4804739CE7FE001C81E6E02783737CA21DB2A0D8AF2D10B200006D10737A0872C667AD142F90407132EFABF8E5D6BD51", 16LL);
    __gmpz_init_set_str(&v9, "65537", 10LL);
    v4 = strlen(argv[1]);
    __gmpz_import(&v8, v4, 1LL, 1LL, 0LL, 0LL, v6[1]);
    if ( (signed int)__gmpz_cmp(&v8, &v10) > 0 )
      abort();
    __gmpz_powm(&v7, &v8, &v9, &v10);
    __gmp_printf("Crypted: %ZX\n", &v7);
    __gmpz_clears(&v8, &v7, &v10, &v9, 0LL);
  }
  result = 0;
  if ( __stack_chk_guard == v11 )
    result = 0;
  return result;
}
```

This one uses [GMP library](https://gmplib.org/) and `__gmpz_powm` function indicates that it is a RSA implementation. The same code rewritten to Scala looks like this:

```scala
val modulus = BigInt("F66EB887F2B8A620FD03C7D0633791CB4804739CE7FE001C81E6E02783737CA21DB2A0D8AF2D10B200006D10737A0872C667AD142F90407132EFABF8E5D6BD51", 16)
val pubkey = BigInt("65537")
val base = BigInt(plaintext.getBytes)
val encrypted = base.modPow(pubkey, modulus)
println(s"Crypted: ${encrypted.toString(16)}")
```

To decrypt the flag we have to calculate a private key first. Since this was the first time I was trying to reverse RSA I found this [Wikipedia article about RSA key generation](https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Key_generation) very useful. It contains all the necessary information.

```scala
val pubkey = BigInt("65537")

// modulus = p * q
// factorization of modulus (in decimal) done by http://factordb.com/index.php?query=12906717464348092265956410210860282684261200239649314436822666616460740520052403025774625130601134473716449192270880280937288228652858915015044165744901457
val p = BigInt("18132985757038135691")
val q = BigInt("711781150511215724435363874088486910075853913118425049972912826148221297483065007967192431613422409694054064755658564243721555532535827")

// calculate phi
val phi = lcm(p - 1, q - 1)

// privkey * pubkey ≡ 1 (mod phi)
val privkey = pubkey.modInverse(phi)
``` 

I put all the pieces together in this [Scala program](../../src/main/scala/hackvent2017/Day14.scala) which implements both RSA encryption and decryption with decompiled public key and modulus and calculated private key.

The decrypted flag is:

```
HV17-5BMu-mgD0-G7Su-EYsp-Mg0b
```