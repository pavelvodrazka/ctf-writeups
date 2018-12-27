# Day 19: PromoCode

*Get your free flag*

Santa is in good mood and gives away flags for free.

Get your free flag [here](https://hackvent.hacking-lab.com/Pr0m0C0de/promo.html).

### Description

You were asked to enter a promo code to get the free flag.

![web.png](files/web.png "web")

There were two versions of this challenge. The original version seemed to be too hard so an easier version was released later that day. The next chapter describes how I solved the original hard version of this challenge.

### Solution

I looked at the page source code and found out that the promo code service was implemented in [WebAssembly](files/promo.wasm). I used [JEB WebAssembly Decompiler](https://www.pnfsoftware.com/jeb/#more) which did pretty decent job. This was the [decompiled result](files/promo.c).

The relevant part was implemented in the [_checkPromoCode()](files/promo.c#L64) function. I added some comments for better understanding of what was happening inside.

```c
int checkPromoCode(int promo_code) {
    int r63 = __env.STACKTOP;                                   // r63 = F10h

    if (__env.STACKTOP + 112 >= __env.STACK_MAX) {
        abortStackOverflow(112);
    }

    unsigned int* r11 = r63 + 32;                               // r11 = 0xF30
    unsigned int* r22 = r63 + 92;                               // r22 = 0xF6C
    int r33 = r63;                                              // r33 = 0xF10
    int r0 = promo_code;                                        // r0  = 0x500F28

    *r11 = gvar_400;                                            // mem[0xF30] = 0xF0BC51F36874F2C1
    *((unsigned int)(((int)gvar_8) + ((int)r11))) = gvar_408;   // mem[0xF38] = 0xE357D1A08AAB8700
    *((unsigned int)(((int)gvar_10) + ((int)r11))) = gvar_410;  // mem[0xF40] = 0x2FEB8572F31271DE
    *((unsigned int)(((int)gvar_18) + ((int)r11))) = gvar_418;  // mem[0xF48] = 0xABABA787
    *((unsigned int)(((int)gvar_1C) + ((int)r11))) = gvar_41C;  // mem[0xF4C] = 0x74FF

    *r22 = 0L;                                                  // mem[0xF6C] = 0
    *((unsigned int)(((int)gvar_8) + ((int)r22))) = 0;          // mem[0xF74] = 0
    *((unsigned int)(((int)gvar_C) + ((int)r22))) = 0;          // mem[0xF78] = 0
    *(((unsigned int)(((int)gvar_C) + ((int)r22))) + 2) = 0;    // mem0xF7A[] = 0

    *r63 = *((long long*)(&aHV18_TRYH_ARDE_[0]));               // mem[0xF10] = "HV18-TRY"
    *((unsigned int)(((int)gvar_8) + r63))
        = *((long long*)(&aHV18_TRYH_ARDE_[&gvar_8]));          // mem[0xF18] = "H-ARDE-R"
    *((unsigned int)(((int)gvar_10) + r63))
        = *((long long*)(&aHV18_TRYH_ARDE_[&gvar_10]));         // mem[0xF20] = "TRY_HARD"
    *((unsigned int)(((int)gvar_18) + r63))
        = *((int*)(&aHV18_TRYH_ARDE_[&gvar_18]));               // mem[0xF28] = "_ER!"
    *((unsigned int)(((int)gvar_1C) + r63))
        = *((short*)(&aHV18_TRYH_ARDE_[&gvar_1C]));             // mem[0xF2C] = "!\0"

    unsigned int r44 = 0;                                       // result = 0
    int r55 = 165;                                              // last = 165
    int var50 = f32(promo_code);                                // len = strlen(promo_code)

    if (var50 == 15) {                                          // if (len == 15) {
        unsigned int r59 = 0;                                   //   i = 0

        while (1) {                                             //   while (1) {
            unsigned int r5 = r59;
            int var61 = f32(r0);                                //     n = strlen(code)

            if(r59 >= var61) {                                  //     if (i >= n) {
                break;                                          //       break;
            }                                                   //     }
            else {                                              //     else {
                unsigned int* var73 = r0 + r59;
                int r60 = ((int)(*var73)) * r55 + 1337;         //       b = code[i] * last + 1337
                unsigned int* var91 = r0 + r59;
                r44 = ((int)(*var91)) + r44 + r60;              //       result += code[i] + b
                int r61 = r60 % 255;
                *((unsigned int*)(((int)r22) + r59))            //       mem[0xF6C + i] = b % 255
                    = (unsigned char)r61;
                r55 = r61;                                      //       last = b % 255
                ++r59;                                          //       ++i
            }                                                   //     }
        }                                                       //   }

        if (r44 != 217675) {                                    //   if (result != 217675) {
            __env.STACKTOP = r63;
            return r33;                                         //     return mem[0xF10];
        }                                                       //   }
        else {                                                  //   else {
            for (int r1 = 0; r1 < 30; ++r1) {                   //     for (int i = 0; i < 30; ++i) {
                unsigned int* var142                            //       a = mem[0xF30 + i]
                    = (unsigned int*)(r1 + ((int)r11));
                unsigned int* var153                            //       b = mem[0xF6C + i % 15]
                    = (unsigned int*)(r1 % 15 + ((int)r22));
                *(r1 + r33) = (unsigned char)(((int)(*var142))  //       mem[0xF10 + i] = a ^ b
                    ^ ((int)(*var153)));
            }                                                   //     }
        }                                                       //   }
    }                                                           // }

    __env.STACKTOP = r63;
    return r33;                                                 // return return mem[0xF10];
}
```

It was clear that the promo code had to be a string consisting of 15 characters and its checksum had to be equal to 217675. Then it was XORed with the fake flag `HV18-TRYH-ARDE-RTRY_HARD_ER!!` to get the real one.

Since I had no better idea I decided to bruteforce it. It seemed to be doable because the promo code was half the length of the flag so each promo code character generated two flag characters.

I rewrote this function in Scala and made few modifications to meet my requirements.

```scala
def calculateFlag(stack: Array[Byte], code: String, checksum: Boolean): String = {
  var result = 0
  var last = 165

  if (code.length == 15) {
    for (i <- 0 until code.length) {
      val b = code(i) * last + 1337
      result += b + code(i)
      stack(92 + i) = (b % 255 & 0xFF).toByte
      last = b % 255
    }

    if (!checksum || result == 217675) {
      for (j <- 0 until 30) {
        val a = stack(32 + j)
        val b = stack(92 + j % 15)
        stack(j) = (b ^ a).toByte
      }
    }
  }

  ascii(stack.slice(0, 29))
}
```

Then I added support for stack operations. 

```scala
val stack = populateStack()

def populateStack(): Array[Byte] = {
  val stack = Array.fill[Byte](112)(0)
  val stack_seg_0x00 = hex2bytes("485631382D545259482D415244452D525452595F484152445F4552212100")
  val stack_seg_0x20 = hex2bytes("C1F27468F351BCF00087AB8AA0D157E3DE7112F37285EB2F87A7ABABFF74").dropWhile(_ == 0x0)
  stack_seg_0x00.copyToArray(stack, 0x0)
  stack_seg_0x20.copyToArray(stack, 0x20)
  stack
}

def cloneStack(): Array[Byte] = stack.clone()
```

In the next step I had to make a hard decision of which alphabet to use in my brute force attempt. At the end I decided to make it as easy as possible and picked alphanumeric characters only.

I expected the result flag to consist only of alphanumerics and hyphens at fixed positions. My plan was to bruteforce group of 5 characters at a time. To do that I prepared the following function which performed the attack in parallel to speed things up a bit.

```scala
val alphabet = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
val patterns = Array(
  "(?s)HV18-.{10}[a-zA-Z0-9]{4}-.{9}".r,
  "(?s)HV18-[a-zA-Z0-9]{4}-.{5}[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-.{4}".r,
  "^HV18-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}-[a-zA-Z0-9]{4}$".r)

def findNextGroup(prefix: String): Unit = {
  val index = prefix.length / 5
  val pattern = patterns(index)
  val length = 5 - (prefix.length % 5)
  assert(length > 0)

  val writer = new PrintWriter(new FileWriter(s"hackvent2018/challenges/day19/files/bf/grp$index.codes"), true)
  try {
    // start in parallel
    alphabet.par.foreach(head => {
      println(s"${LocalTime.now()}: searching for pattern $prefix$head*")
      for (tail <- Strings.of(alphabet).generate(length - 1)) {
        val code = assembleCode(prefix, head + tail)
        val flag = tryPromoCode(code, pattern)
        if (flag.isDefined) {
          println(s"$code  -->  ${flag.get}")
          writer.println(code.trim)
        }
      }
    })
  } finally {
    println(s"${LocalTime.now()}: done!")
    writer.close()
  }
}
```

Here is the complete [source code](../../src/main/scala/hackvent2018/Day19.scala) of my script.

Then it was time to run the program and hope for the best. I started with the following code to find all possible strings of the first group.

```scala
findNextGroup("")
```

It found [10 strings](files/bf/grp0.codes) which was a little bit more than I expected. Luckily I noticed one string which looked like first characters of *webasm* in leet speak: `W3b45`. It could not be just coincidence so I picked this one and appended missing lowercase `m` to it for the prefix of the second group.

```scala
findNextGroup("W3b45m")
```

This time it was much quicker but it gave me [308 strings](files/bf/grp1.codes) in total. I went through all of them manually and again found one promising camelcase leet speak string: `W3b45m1sRl`. I appended lowercase `y` to it and proceeded to the last group.

```scala
findNextGroup("W3b45m1sRly")
```

The [result](files/bf/grp2.codes) of this search was exactly one string: `W3b45m1sRlyF45t`. Bingo! I found the promo code I needed.

The last thing to do was to submit the promo code to get the flag.

```
HV18-rKRV-Cg2G-jz4B-QrIy-OF9i
```
