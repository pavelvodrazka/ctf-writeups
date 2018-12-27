/*
.data:00000004    gvar_4           dd 0h
.data:00000008    gvar_8           dd 0h
.data:0000000C    gvar_C           dd 0h
.data:00000010    gvar_10          dd 0h
.data:00000014    gvar_14          dd 0h
.data:00000018    gvar_18          dd 0h
.data:0000001C    gvar_1C          dd 0h

...

.data:00000400    gvar_400         dq F0BC51F36874F2C1h
.data:00000408    gvar_408         dq E357D1A08AAB8700h
.data:00000410    gvar_410         dq 2FEB8572F31271DEh
.data:00000418    gvar_418         dd ABABA787h
.data:0000041C    gvar_41C         dw 74FFh
.data:0000041E                     db 0, 0
.data:00000420    aHV18_TRYH_ARDE_ db "HV18-TRYH-ARDE-RTRY_HARD_ER!!"
.data:0000043E                     db 0, 0
.data:00000440                     db 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
.data:00000450                     db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.data:00000460                     db 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, C8h, 4, 0, 0
.data:00000470                     db 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
.data:00000480                     db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0Ah, FFh, FFh, FFh, FFh
.data:00000490                     db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.data:000004A0                     db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.data:000004B0                     db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.data:000004BC    gvar_4BC         dd 440h
*/

int stackAlloc(int par0) {
    // DEMO VERSION LIMITATION - This method was not decompiled
}

int stackSave() {
    return __env.STACKTOP;
}

void stackRestore(int par0) {
    __env.STACKTOP = par0;
}

void establishStackSpace(int par0, int par1) {
    __env.STACKTOP = par0;
    __env.STACK_MAX = par1;
}

void setThrew(unsigned int par0, unsigned int par1) {
    // DEMO VERSION LIMITATION - This method was not decompiled
}

void setTempRet0(unsigned int par0) {
    g23 = par0;
}

int getTempRet0() {
    return g23;
}

int _main(unsigned int par0, unsigned int par1) {
    // DEMO VERSION LIMITATION - This method was not decompiled
}

int _checkPromoCode(int promo_code) {
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

int f32(unsigned int* promo_code_addr) {
    unsigned int* r4;
    unsigned int* r2;
    unsigned int* r8 = promo_code_addr;

    if (((unsigned int)(((int)promo_code_addr) & 3)) == 0) {
        r2 = promo_code_addr;
        // missing: r30 = 5;
    }
    else {
        unsigned int* r3 = promo_code_addr;

        while (((int)(*r3)) != 0) {
            unsigned int* r26 = (unsigned int*)(((char*)r3) + 1);

            if ((((unsigned int)(((char*)r3) + 1)) & 3) == 0) {
                r2 = r26;
                break;
            }
            else {
                r3 = r26;
            }
        }
    }

    unsigned int* r0 = r2;

    while (1) {
        unsigned int r9 = *r0;
        unsigned int* r15 = r0 + 1;

        if (((r9 - 16843009) & ((r9 & -2139062144) ^ -2139062144)) != 0) {
            break;
        }
        else {
            r0 = r15;
        }
    }

    if (((int)(((unsigned char)r9))) == 0) {
        r4 = r0;
    }
    else {
        unsigned int* r6 = r0;
        unsigned int* r18;

        for(r18 = (unsigned int*)(((char*)r0) + 1); ((int)(*r18)) != 0; r18 = (unsigned int*)(((char*)r6) + 1)) {
            r6 = r18;
        }

        r4 = r18;
    }

    return (unsigned int)(((int)r4) - ((int)r8));
}

int _malloc(unsigned int par0) {
    unsigned int* r901;
    unsigned int var2661;
    unsigned int r18;
    unsigned int r21;
    unsigned int* r84;
    unsigned int r20;
    unsigned int* var2400;
    unsigned int* r44;
    unsigned int r41;
    unsigned int* r1043;
    unsigned int var3074;
    unsigned int r11;
    unsigned int r14;
    unsigned int* r83;
    unsigned int r13;
    unsigned int r963;
    unsigned int* r956;
    unsigned int* r954;
    unsigned int var2815;
    unsigned int r934;
    unsigned int var2794;
    unsigned int r932;
    unsigned int var2782;
    unsigned int r16;
    unsigned int r2;
    unsigned int* r43;
    unsigned int r40;
    unsigned int* r45;
    unsigned int r42;
    unsigned int r60;
    unsigned int r766;
    unsigned int r749;
    unsigned int r728;
    unsigned int r727;
    unsigned int r722;
    unsigned int var2175;
    unsigned int r714;
    unsigned int var2157;
    unsigned int var2070;
    unsigned int r656;
    unsigned int var1975;
    int var1907;
    int r68;
    int r581;
    unsigned int var1762;
    int r76;
    int r75;
    int r55;
    int r57;
    int r56;
    unsigned int r531;
    unsigned int* r478;
    unsigned int var1426;
    unsigned int r24;
    unsigned int r30;
    unsigned int* r85;
    unsigned int r32;
    unsigned int* var1148;
    unsigned int r453;
    unsigned int* r53;
    unsigned int r50;
    unsigned int* r54;
    unsigned int r51;
    unsigned int r64;
    unsigned int var989;
    unsigned int var986;
    unsigned int r69;
    unsigned int r65;
    unsigned int r72;
    unsigned int r62;
    unsigned int var849;
    unsigned int r47;
    unsigned int r46;
    unsigned int r74;
    unsigned int r71;
    unsigned int r67;
    unsigned int var793;
    unsigned int r1094;
    unsigned int r63;
    unsigned int r61;
    unsigned int r58;
    unsigned int r28;
    unsigned int* r86;
    unsigned int r1;
    unsigned int* var539;
    unsigned int* r37;
    unsigned int r34;
    unsigned int var412;
    unsigned int var409;
    unsigned int r132;
    unsigned int* r36;
    unsigned int r33;
    unsigned int* r38;
    unsigned int r35;
    unsigned int r59;
    unsigned int r141;
    unsigned int r138;
    unsigned int r7;
    unsigned int r6;
    unsigned int r8;
    unsigned int* r87;
    unsigned int r9;
    unsigned int r980;
    unsigned int var14;
    int r1095 = __env.STACKTOP;

    if(__env.STACKTOP + &gvar_10 >= __env.STACK_MAX) {
        abortStackOverflow(&gvar_10);
    }

    int r91 = r1095;

    if(par0 < 245) {
        unsigned int r535 = (par0 + 11) & -8;

        if(par0 >= 11) {
            var14 = r535;
        }

        unsigned int r646 = var14;
        unsigned int r757 = var14 >>> 3;
        unsigned int r868 = *2256;
        unsigned int r979 = r868 >>> r757;

        if((r979 & 3) != 0) {
            unsigned int r136 = ((r979 & 1) ^ 1) + r757;
            unsigned int r158 = r136 * &gvar_8 + 2296;
            unsigned int* r169 = r158 + &gvar_8;
            unsigned int r180 = *r169;
            unsigned int* r191 = r180 + &gvar_8;
            unsigned int r203 = *r191;

            if(r158 == r203) {
                *2256 = ((1 << r136) ^ -1) & r868;
            }
            else {
                *((unsigned int)(((int)gvar_C) + r203)) = r158;
                *r169 = r203;
            }

            unsigned int r269 = r136 * &gvar_8;
            *((unsigned int)(((int)gvar_4) + r180)) = r269 | 3;
            unsigned int* r314 = r180 + r269 + &gvar_4;
            *r314 = *r314 | 1;
            __env.STACKTOP = r1095;
            return r191;
        }
        else {
            unsigned int r347 = *2264;

            if(r347 >= var14) {
                r8 = var14;
            }
            else if(r979 != 0) {
                unsigned int r391 = 2 << r757;
                unsigned int r425 = ((0 - r391) | r391) & (r979 << r757);
                unsigned int r458 = ((0 - r425) & r425) - 1;
                unsigned int r480 = (r458 >>> &gvar_C) & &gvar_10;
                unsigned int r491 = r458 >>> r480;
                unsigned int r513 = (r491 >>> 5) & &gvar_8;
                unsigned int r536 = r491 >>> r513;
                unsigned int r558 = (r536 >>> 2) & &gvar_4;
                unsigned int r580 = r536 >>> r558;
                unsigned int r602 = (r580 >>> 1) & 2;
                unsigned int r624 = r580 >>> r602;
                unsigned int r647 = (r624 >>> 1) & 1;
                unsigned int r680 = (r480 | r513 | r558 | r602 | r647) + (r624 >>> r647);
                unsigned int r702 = r680 * &gvar_8 + 2296;
                unsigned int* r713 = r702 + &gvar_8;
                unsigned int r724 = *r713;
                unsigned int* r735 = r724 + &gvar_8;
                unsigned int r746 = *r735;

                if(r702 == r746) {
                    *2256 = ((1 << r680) ^ -1) & r868;
                    r980 = ((1 << r680) ^ -1) & r868;
                }
                else {
                    *((unsigned int)(((int)gvar_C) + r746)) = r702;
                    *r713 = r746;
                    r980 = r868;
                }

                unsigned int r813 = r680 * &gvar_8;
                unsigned int r824 = r813 - var14;
                *((unsigned int)(((int)gvar_4) + r724)) = var14 | 3;
                unsigned int r857 = var14 + r724;
                *((unsigned int)(((int)gvar_4) + r857)) = r824 | 1;
                *(r724 + r813) = r824;

                if(r347 != 0) {
                    unsigned int r913 = *2276;
                    unsigned int r924 = r347 >>> 3;
                    unsigned int r946 = r924 * &gvar_8 + 2296;
                    unsigned int r957 = 1 << r924;

                    if((r957 & r980) == 0) {
                        *2256 = r957 | r980;
                        r9 = r946;
                        r87 = r946 + &gvar_8;
                    }
                    else {
                        unsigned int* r1013 = r946 + &gvar_8;
                        r9 = *r1013;
                        r87 = r1013;
                    }

                    *r87 = r913;
                    *((unsigned int)(((int)gvar_C) + r9)) = r913;
                    *((unsigned int)(((int)gvar_8) + r913)) = r9;
                    *((unsigned int)(((int)gvar_C) + r913)) = r946;
                }

                *2264 = r824;
                *2276 = r857;
                __env.STACKTOP = r1095;
                return r735;
            }
            else {
                unsigned int r1068 = *2260;

                if(r1068 == 0) {
                    r8 = var14;
                }
                else {
                    unsigned int r95 = ((0 - r1068) & r1068) - 1;
                    unsigned int r97 = (r95 >>> &gvar_C) & &gvar_10;
                    unsigned int r98 = r95 >>> r97;
                    unsigned int r100 = (r98 >>> 5) & &gvar_8;
                    unsigned int r102 = r98 >>> r100;
                    unsigned int r105 = (r102 >>> 2) & &gvar_4;
                    unsigned int r107 = r102 >>> r105;
                    unsigned int r109 = (r107 >>> 1) & 2;
                    unsigned int r111 = r107 >>> r109;
                    unsigned int r113 = (r111 >>> 1) & 1;
                    unsigned int r119 = *(((r97 | r100 | r105 | r109 | r113) + (r111 >>> r113)) * &gvar_4 + 2560);
                    unsigned int r5 = *(((r97 | r100 | r105 | r109 | r113) + (r111 >>> r113)) * &gvar_4 + 2560);
                    r6 = r119;
                    r7 = (*((unsigned int)(((int)gvar_4) + r119)) & -8) - var14;

                    while(1) {
                        unsigned int r126 = *((unsigned int)(((int)gvar_10) + r5));

                        if(r126 == 0) {
                            unsigned int r129 = *((unsigned int)(((int)gvar_14) + r5));

                            if(r129 == 0) {
                                r138 = r6 + r646;

                                if(r6 < r138) {
                                    r141 = *((unsigned int)(((int)gvar_18) + r6));
                                    unsigned int r143 = *((unsigned int)(((int)gvar_C) + r6));

                                    if(r6 == r143) {
                                        unsigned int* r150 = r6 + &gvar_14;
                                        unsigned int r151 = *r150;

                                        if(r151 == 0) {
                                            unsigned int* r153 = r6 + &gvar_10;
                                            unsigned int r154 = *r153;

                                            if(r154 == 0) {
                                                r59 = 0;
                                                goto loc_50000AE9;
                                            }
                                            else {
                                                r35 = r154;
                                                r38 = r153;
                                            }
                                        }
                                        else {
                                            r35 = r151;
                                            r38 = r150;
                                        }

                                        r33 = r35;
                                        r36 = r38;
                                        goto loc_50000A33;
                                    }
                                    else {
                                        unsigned int r146 = *((unsigned int)(((int)gvar_8) + r6));
                                        *((unsigned int)(((int)gvar_C) + r146)) = r143;
                                        *((unsigned int)(((int)gvar_8) + r143)) = r146;
                                        r59 = r143;
                                        goto loc_50000AE9;
                                    }
                                }
                                else {
                                    r8 = r646;
                                    break;
                                }
                            }
                            else {
                                r132 = r129;
                            }
                        }
                        else {
                            r132 = r126;
                        }

                        unsigned int r137 = (unsigned int)((*((unsigned int)(((int)gvar_4) + r132)) & -8) - r646 < r7);

                        if(!r137) {
                            var409 = r7;
                        }

                        unsigned int r1087 = var409;

                        if(!r137) {
                            var412 = r6;
                        }

                        r5 = r132;
                        r6 = var412;
                        r7 = var409;
                    }
                }

                goto loc_50001B50;
            loc_50000A33:

                while(1) {
                    unsigned int* r156 = r33 + &gvar_14;
                    unsigned int r157 = *r156;

                    if(r157 == 0) {
                        unsigned int* r160 = r33 + &gvar_10;
                        unsigned int r161 = *r160;

                        if(r161 == 0) {
                            *r36 = 0;
                            r59 = r33;
                            break;
                        }
                        else {
                            r34 = r161;
                            r37 = r160;
                        }
                    }
                    else {
                        r34 = r157;
                        r37 = r156;
                    }

                    r33 = r34;
                    r36 = r37;
                }

            loc_50000AE9:

                if(r141 != 0) {
                    unsigned int r165 = *((unsigned int)(((int)gvar_1C) + r6));
                    unsigned int* r166 = r165 * &gvar_4 + 2560;

                    if(*r166 == r6) {
                        *r166 = r59;

                        if(r59 == 0) {
                            *2260 = ((1 << r165) ^ -1) & r1068;
                            goto loc_50000C4D;
                        }
                    }
                    else {
                        unsigned int* r176 = r141 + &gvar_14;

                        if(*((unsigned int)(((int)gvar_10) + r141)) != r6) {
                            var539 = r176;
                        }

                        *var539 = r59;

                        if(r59 == 0) {
                            goto loc_50000C4D;
                        }
                    }

                    *((unsigned int)(((int)gvar_18) + r59)) = r141;
                    unsigned int r181 = *((unsigned int)(((int)gvar_10) + r6));

                    if(r181 != 0) {
                        *((unsigned int)(((int)gvar_10) + r59)) = r181;
                        *((unsigned int)(((int)gvar_18) + r181)) = r59;
                    }

                    unsigned int r186 = *((unsigned int)(((int)gvar_14) + r6));

                    if(r186 != 0) {
                        *((unsigned int)(((int)gvar_14) + r59)) = r186;
                        *((unsigned int)(((int)gvar_18) + r186)) = r59;
                    }
                }

            loc_50000C4D:

                if(r7 < &gvar_10) {
                    unsigned int r192 = r7 + r646;
                    *((unsigned int)(((int)gvar_4) + r6)) = r192 | 3;
                    unsigned int* r196 = r6 + r192 + &gvar_4;
                    *r196 = *r196 | 1;
                }
                else {
                    *((unsigned int)(((int)gvar_4) + r6)) = r646 | 3;
                    *((unsigned int)(((int)gvar_4) + r138)) = r7 | 1;
                    *(r7 + r138) = r7;

                    if(r347 != 0) {
                        unsigned int r207 = *2276;
                        unsigned int r208 = r347 >>> 3;
                        unsigned int r210 = r208 * &gvar_8 + 2296;
                        unsigned int r211 = 1 << r208;

                        if((r211 & r868) == 0) {
                            *2256 = r211 | r868;
                            r1 = r210;
                            r86 = r210 + &gvar_8;
                        }
                        else {
                            unsigned int* r216 = r210 + &gvar_8;
                            r1 = *r216;
                            r86 = r216;
                        }

                        *r86 = r207;
                        *((unsigned int)(((int)gvar_C) + r1)) = r207;
                        *((unsigned int)(((int)gvar_8) + r207)) = r1;
                        *((unsigned int)(((int)gvar_C) + r207)) = r210;
                    }

                    *2264 = r7;
                    *2276 = r138;
                }

                __env.STACKTOP = r1095;
                return r6 + &gvar_8;
            }
        }
    }
    else if(par0 > -65) {
        r8 = -1;
    }
    else {
        unsigned int r223 = par0 + 11;
        unsigned int r224 = r223 & -8;
        unsigned int r226 = *2260;

        if(r226 != 0) {
            unsigned int r228 = 0 - r224;
            unsigned int r229 = r223 >>> &gvar_8;

            if(r229 == 0) {
                r28 = 0;
            }
            else if(r224 > 16777215) {
                r28 = 31;
            }
            else {
                unsigned int r234 = ((r229 + 1048320) >>> &gvar_10) & &gvar_8;
                unsigned int r235 = r229 << r234;
                unsigned int r239 = ((r235 + 520192) >>> &gvar_10) & &gvar_4;
                unsigned int r241 = r235 << r239;
                unsigned int r244 = ((r241 + 245760) >>> &gvar_10) & 2;
                unsigned int r250 = 14 - (r234 | r239 | r244) + ((r241 << r244) >>> 15);
                r28 = (r250 * 2) | ((r224 >>> (r250 + 7)) & 1);
            }

            unsigned int r257 = *(r28 * &gvar_4 + 2560);

            if(r257 == 0) {
                r58 = 0;
                r61 = 0;
                r63 = r228;
                r1094 = 61;
            }
            else {
                unsigned int r262 = 25 - (r28 >>> 1);

                if(r28 != 31) {
                    var793 = r262;
                }

                unsigned int r22 = 0;
                unsigned int r26 = r228;
                unsigned int r27 = r257;
                unsigned int r29 = r224 << var793;

                while(1) {
                    unsigned int r268 = (*((unsigned int)(((int)gvar_4) + r27)) & -8) - r224;

                    if(r26 <= r268) {
                        r46 = r22;
                        r47 = r26;
                    }
                    else if(r268 == 0) {
                        r67 = r27;
                        r71 = 0;
                        r74 = r27;
                        r1094 = 65;
                        break;
                    }
                    else {
                        r46 = r27;
                        r47 = r268;
                    }

                    unsigned int r273 = *((unsigned int)(((int)gvar_14) + r27));
                    unsigned int r276 = *(((unsigned int)((r29 >>> 31) * &gvar_4 + ((int)gvar_10))) + r27);

                    if(!(((unsigned int)(r273 == 0)) | ((unsigned int)(r273 == r276)))) {
                        var849 = r273;
                    }

                    unsigned int r48 = var849;
                    unsigned int r1091 = r29 * 2;

                    if(r276 == 0) {
                        r58 = var849;
                        r61 = r46;
                        r63 = r47;
                        r1094 = 61;
                        break;
                    }
                    else {
                        r22 = r46;
                        r26 = r47;
                        r27 = r276;
                        r29 = r1091;
                    }
                }
            }

            if(r1094 == 61) {

                if((((unsigned int)(r58 == 0)) & ((unsigned int)(r61 == 0)))) {
                    unsigned int r283 = 2 << r28;
                    unsigned int r286 = ((0 - r283) | r283) & r226;

                    if(r286 == 0) {
                        r8 = r224;
                        goto loc_50001B50;
                    }
                    else {
                        unsigned int r290 = ((0 - r286) & r286) - 1;
                        unsigned int r293 = (r290 >>> &gvar_C) & &gvar_10;
                        unsigned int r294 = r290 >>> r293;
                        unsigned int r296 = (r294 >>> 5) & &gvar_8;
                        unsigned int r298 = r294 >>> r296;
                        unsigned int r300 = (r298 >>> 2) & &gvar_4;
                        unsigned int r303 = r298 >>> r300;
                        unsigned int r305 = (r303 >>> 1) & 2;
                        unsigned int r307 = r303 >>> r305;
                        unsigned int r309 = (r307 >>> 1) & 1;
                        r62 = 0;
                        r72 = *(((r293 | r296 | r300 | r305 | r309) + (r307 >>> r309)) * &gvar_4 + 2560);
                    }
                }
                else {
                    r62 = r61;
                    r72 = r58;
                }

                if(r72 == 0) {
                    r65 = r62;
                    r69 = r63;
                }
                else {
                    r67 = r62;
                    r71 = r63;
                    r74 = r72;
                    r1094 = 65;
                }
            }

            if(r1094 == 65) {
                unsigned int r66 = r67;
                unsigned int r70 = r71;
                unsigned int r73 = r74;

                while(1) {
                    unsigned int r322 = (unsigned int)((*((unsigned int)(((int)gvar_4) + r73)) & -8) - r224 < r70);

                    if(!r322) {
                        var986 = r70;
                    }

                    unsigned int r1088 = var986;

                    if(!r322) {
                        var989 = r66;
                    }

                    unsigned int r1090 = var989;
                    unsigned int r324 = *((unsigned int)(((int)gvar_10) + r73));
                    unsigned int r329 = r324 == 0 ? *((unsigned int)(((int)gvar_14) + r73)): r324;

                    if(r329 == 0) {
                        r65 = var989;
                        r69 = var986;
                        break;
                    }
                    else {
                        r66 = var989;
                        r70 = var986;
                        r73 = r329;
                    }
                }
            }

            if(r65 == 0) {
                r8 = r224;
                goto loc_50001B50;
            }
            else if(*2264 - r224 <= r69) {
                r8 = r224;
                goto loc_50001B50;
            }
            else {
                unsigned int r335 = r65 + r224;

                if(r65 < r335) {
                    unsigned int r339 = *((unsigned int)(((int)gvar_18) + r65));
                    unsigned int r341 = *((unsigned int)(((int)gvar_C) + r65));

                    if(r65 == r341) {
                        unsigned int* r348 = r65 + &gvar_14;
                        unsigned int r349 = *r348;

                        if(r349 == 0) {
                            unsigned int* r351 = r65 + &gvar_10;
                            unsigned int r352 = *r351;

                            if(r352 == 0) {
                                r64 = 0;
                                goto loc_500014DA;
                            }
                            else {
                                r51 = r352;
                                r54 = r351;
                            }
                        }
                        else {
                            r51 = r349;
                            r54 = r348;
                        }

                        unsigned int r49 = r51;
                        unsigned int* r52 = r54;

                        while(1) {
                            unsigned int* r354 = r49 + &gvar_14;
                            unsigned int r355 = *r354;

                            if(r355 == 0) {
                                unsigned int* r357 = r49 + &gvar_10;
                                unsigned int r359 = *r357;

                                if(r359 == 0) {
                                    *r52 = 0;
                                    r64 = r49;
                                    break;
                                }
                                else {
                                    r50 = r359;
                                    r53 = r357;
                                }
                            }
                            else {
                                r50 = r355;
                                r53 = r354;
                            }

                            r49 = r50;
                            r52 = r53;
                        }
                    }
                    else {
                        unsigned int r344 = *((unsigned int)(((int)gvar_8) + r65));
                        *((unsigned int)(((int)gvar_C) + r344)) = r341;
                        *((unsigned int)(((int)gvar_8) + r341)) = r344;
                        r64 = r341;
                    }

                loc_500014DA:

                    if(r339 == 0) {
                        r453 = r226;
                    }
                    else {
                        unsigned int r363 = *((unsigned int)(((int)gvar_1C) + r65));
                        unsigned int* r364 = r363 * &gvar_4 + 2560;

                        if(*r364 == r65) {
                            *r364 = r64;

                            if(r64 == 0) {
                                *2260 = ((1 << r363) ^ -1) & r226;
                                r453 = ((1 << r363) ^ -1) & r226;
                                goto loc_5000165F;
                            }
                        }
                        else {
                            unsigned int* r374 = r339 + &gvar_14;

                            if(*((unsigned int)(((int)gvar_10) + r339)) != r65) {
                                var1148 = r374;
                            }

                            *var1148 = r64;

                            if(r64 == 0) {
                                r453 = r226;
                                goto loc_5000165F;
                            }
                        }

                        *((unsigned int)(((int)gvar_18) + r64)) = r339;
                        unsigned int r378 = *((unsigned int)(((int)gvar_10) + r65));

                        if(r378 != 0) {
                            *((unsigned int)(((int)gvar_10) + r64)) = r378;
                            *((unsigned int)(((int)gvar_18) + r378)) = r64;
                        }

                        unsigned int r384 = *((unsigned int)(((int)gvar_14) + r65));

                        if(r384 != 0) {
                            *((unsigned int)(((int)gvar_14) + r64)) = r384;
                            *((unsigned int)(((int)gvar_18) + r384)) = r64;
                        }

                        r453 = r226;
                    }

                loc_5000165F:

                    if(r69 < &gvar_10) {
                        unsigned int r389 = r69 + r224;
                        *((unsigned int)(((int)gvar_4) + r65)) = r389 | 3;
                        unsigned int* r394 = r65 + r389 + &gvar_4;
                        *r394 = *r394 | 1;
                    }
                    else {
                        *((unsigned int)(((int)gvar_4) + r65)) = r224 | 3;
                        *((unsigned int)(((int)gvar_4) + r335)) = r69 | 1;
                        *(r69 + r335) = r69;
                        unsigned int r403 = r69 >>> 3;

                        if(r69 < 256) {
                            unsigned int r406 = r403 * &gvar_8 + 2296;
                            unsigned int r407 = *2256;
                            unsigned int r408 = 1 << r403;

                            if((r407 & r408) == 0) {
                                *2256 = r407 | r408;
                                r32 = r406;
                                r85 = r406 + &gvar_8;
                            }
                            else {
                                unsigned int* r412 = r406 + &gvar_8;
                                r32 = *r412;
                                r85 = r412;
                            }

                            *r85 = r335;
                            *((unsigned int)(((int)gvar_C) + r32)) = r335;
                            *((unsigned int)(((int)gvar_8) + r335)) = r32;
                            *((unsigned int)(((int)gvar_C) + r335)) = r406;
                        }
                        else {
                            unsigned int r418 = r69 >>> &gvar_8;

                            if(r418 == 0) {
                                r30 = 0;
                            }
                            else if(r69 > 16777215) {
                                r30 = 31;
                            }
                            else {
                                unsigned int r423 = ((r418 + 1048320) >>> &gvar_10) & &gvar_8;
                                unsigned int r426 = r418 << r423;
                                unsigned int r429 = ((r426 + 520192) >>> &gvar_10) & &gvar_4;
                                unsigned int r431 = r426 << r429;
                                unsigned int r434 = ((r431 + 245760) >>> &gvar_10) & 2;
                                unsigned int r440 = 14 - (r423 | r429 | r434) + ((r431 << r434) >>> 15);
                                r30 = (r440 * 2) | ((r69 >>> (r440 + 7)) & 1);
                            }

                            unsigned int* r446 = r30 * &gvar_4 + 2560;
                            *((unsigned int)(((int)gvar_1C) + r335)) = r30;
                            unsigned int* r449 = r335 + &gvar_10;
                            *((unsigned int)(((int)gvar_4) + ((int)r449))) = 0;
                            *r449 = 0;
                            unsigned int r451 = 1 << r30;

                            if((r451 & r453) == 0) {
                                *2260 = r451 | r453;
                                *r446 = r335;
                                *((unsigned int)(((int)gvar_18) + r335)) = r446;
                                *((unsigned int)(((int)gvar_C) + r335)) = r335;
                                *((unsigned int)(((int)gvar_8) + r335)) = r335;
                            }
                            else {
                                unsigned int r460 = *r446;

                                if((*((unsigned int)(((int)gvar_4) + r460)) & -8) == r69) {
                                    r24 = r460;
                                }
                                else {
                                    unsigned int r467 = 25 - (r30 >>> 1);

                                    if(r30 != 31) {
                                        var1426 = r467;
                                    }

                                    unsigned int r23 = r69 << var1426;
                                    unsigned int r25 = r460;

                                    while(1) {
                                        r478 = (r23 >>> 31) * &gvar_4 + r25 + &gvar_10;
                                        unsigned int r473 = *r478;

                                        if(r473 == 0) {
                                            break;
                                        }
                                        else {
                                            unsigned int r471 = r23 * 2;

                                            if((*((unsigned int)(((int)gvar_4) + r473)) & -8) == r69) {
                                                r24 = r473;
                                                goto loc_50001AC5;
                                            }
                                            else {
                                                r23 = r471;
                                                r25 = r473;
                                            }
                                        }
                                    }

                                    *r478 = r335;
                                    *((unsigned int)(((int)gvar_18) + r335)) = r25;
                                    *((unsigned int)(((int)gvar_C) + r335)) = r335;
                                    *((unsigned int)(((int)gvar_8) + r335)) = r335;
                                    goto loc_50001B32;
                                }

                            loc_50001AC5:
                                unsigned int* r484 = r24 + &gvar_8;
                                unsigned int r485 = *r484;
                                *((unsigned int)(((int)gvar_C) + r485)) = r335;
                                *r484 = r335;
                                *((unsigned int)(((int)gvar_8) + r335)) = r485;
                                *((unsigned int)(((int)gvar_C) + r335)) = r24;
                                *((unsigned int)(((int)gvar_18) + r335)) = 0;
                            }
                        }
                    }

                loc_50001B32:
                    __env.STACKTOP = r1095;
                    return r65 + &gvar_8;
                }
            }
        }

        r8 = r224;
    }

loc_50001B50:
    unsigned int r492 = *2264;

    if(r8 <= r492) {
        unsigned int r494 = r492 - r8;
        unsigned int r495 = *2276;

        if(r494 > 15) {
            *2276 = r8 + r495;
            *2264 = r494;
            *(((unsigned int)(((int)gvar_4) + r8)) + r495) = r494 | 1;
            *(r492 + r495) = r494;
            *((unsigned int)(((int)gvar_4) + r495)) = r8 | 3;
        }
        else {
            *2264 = 0;
            *2276 = 0;
            *((unsigned int)(((int)gvar_4) + r495)) = r492 | 3;
            unsigned int* r507 = r492 + r495 + &gvar_4;
            *r507 = *r507 | 1;
        }

        __env.STACKTOP = r1095;
        return r495 + &gvar_8;
    }
    else {
        unsigned int r511 = *2268;

        if(r8 < r511) {
            *2268 = r511 - r8;
            unsigned int r515 = *2280;
            *2280 = r8 + r515;
            *(((unsigned int)(((int)gvar_4) + r8)) + r515) = (r511 - r8) | 1;
            *((unsigned int)(((int)gvar_4) + r515)) = r8 | 3;
            __env.STACKTOP = r1095;
            return r515 + &gvar_8;
        }
        else {

            if(*2728 == 0) {
                *2736 = 4096;
                *2732 = 4096;
                *2740 = -1;
                *2744 = -1;
                *2748 = 0;
                *2700 = 0;
                *2728 = (r91 & -16) ^ 1431655768;
                r531 = 4096;
            }
            else {
                r531 = *2736;
            }

            unsigned int r528 = r8 + 48;
            unsigned int r529 = r8 + 47;
            unsigned int r530 = r529 + r531;
            unsigned int r532 = 0 - r531;
            int r533 = r530 & r532;

            if(r8 < r533) {
                unsigned int r537 = *2696;

                if(r537 != 0) {
                    unsigned int r539 = *2688;
                    unsigned int r540 = r533 + r539;

                    if((((unsigned int)(r537 < r540)) | ((unsigned int)(r539 >= r540)))) {
                        __env.STACKTOP = r1095;
                        return 0;
                    }
                }

                if((*2700 & &gvar_4) == 0) {
                    unsigned int r546 = *2280;

                    if(r546 == 0) {
                        r1094 = 128;
                    }
                    else {
                        unsigned int* r4 = 2704;

                        while(1) {
                            unsigned int r549 = *r4;

                            if(r546 >= r549 && *((unsigned int)(((int)gvar_4) + ((int)r4))) + r549 > r546) {
                                int r584 = (r530 - r511) & r532;

                                if(r584 < 2147483647) {
                                    unsigned int* r586 = r4 + 1;
                                    int var1711 = _sbrk(r584);
                                    int r587 = var1711;

                                    if(*r4 + *r586 != var1711) {
                                        r56 = var1711;
                                        r57 = r584;
                                        r1094 = 136;
                                    }
                                    else if(var1711 == -1) {
                                        r55 = r584;
                                    }
                                    else {
                                        r75 = r584;
                                        r76 = var1711;
                                        r1094 = 145;
                                        goto loc_500021FF;
                                    }
                                }
                                else {
                                    r55 = 0;
                                }

                                break;
                            }
                            else {
                                unsigned int* r556 = *((unsigned int)(((int)gvar_8) + ((int)r4)));

                                if(!((unsigned char)(((int)r556) != 0))) {
                                    r1094 = 128;
                                    break;
                                }
                                else {
                                    r4 = r556;
                                }
                            }
                        }
                    }

                    if(r1094 == 128) {
                        int var1735 = _sbrk(0);
                        int r559 = var1735;

                        if(var1735 != -1) {
                            unsigned int r562 = *2732;
                            unsigned int r563 = r562 - 1;
                            unsigned int r570 = ((var1735 + r563) & (0 - r562)) - var1735;

                            if((var1735 & r563) != 0) {
                                var1762 = r570;
                            }

                            int r1092 = r533 + var1762;
                            unsigned int r572 = *2688;
                            unsigned int r573 = r572 + r1092;

                            if(!(((unsigned int)(r8 < r1092)) & ((unsigned int)(r1092 < 2147483647)))) {
                                goto loc_500020BB;
                            }
                            else {
                                unsigned int r576 = *2696;

                                if(r576 != 0 && (((unsigned int)(r573 > r576)) | ((unsigned int)(r572 >= r573)))) {
                                    r55 = 0;
                                    goto loc_500020CA;
                                }
                                else {
                                    int var1797 = _sbrk(r1092);
                                    r581 = var1797;

                                    if(var1735 == var1797) {
                                        r75 = r1092;
                                        r76 = var1735;
                                        r1094 = 145;
                                        goto loc_500021FF;
                                    }
                                }
                            }

                            r56 = r581;
                            r57 = r1092;
                            r1094 = 136;
                        }
                        else {
                        loc_500020BB:
                            r55 = 0;
                        }
                    }

                loc_500020CA:

                    if(r1094 == 136) {
                        int r594 = 0 - r57;

                        if((((unsigned int)(r56 != -1)) & ((unsigned int)(r57 < r528)) & ((unsigned int)(r57 < 2147483647))) != 0) {
                            unsigned int r598 = *2736;
                            int r603 = (r529 - r57 + r598) & (0 - r598);

                            if(r603 >= 2147483647) {
                                r75 = r57;
                                r76 = r56;
                                r1094 = 145;
                                goto loc_500021FF;
                            }
                            else {
                                int var1855 = _sbrk(r603);

                                if(var1855 == -1) {
                                    _sbrk(r594);
                                    r55 = 0;
                                }
                                else {
                                    r75 = r57 + r603;
                                    r76 = r56;
                                    r1094 = 145;
                                    goto loc_500021FF;
                                }
                            }
                        }
                        else if(r56 == -1) {
                            r55 = 0;
                        }
                        else {
                            r75 = r57;
                            r76 = r56;
                            r1094 = 145;
                            goto loc_500021FF;
                        }
                    }

                    *2700 = *2700 | &gvar_4;
                    r68 = r55;
                }
                else {
                    r68 = 0;
                }

                r1094 = 143;
            loc_500021FF:

                if(r1094 == 143 && r533 < 2147483647) {
                    int var1880 = _sbrk(r533);
                    int r612 = var1880;
                    var1880 = _sbrk(0);
                    unsigned int r1085 = ((unsigned int)(r612 != -1)) & ((unsigned int)(var1880 != -1)) & ((unsigned int)(r612 < var1880));
                    unsigned int r622 = (unsigned int)(r8 + 40 < var1880 - r612);

                    if(!r622) {
                        var1907 = r68;
                    }

                    int r1093 = var1907;

                    if(((r622 ^ 1) | (r1085 ^ 1) | ((unsigned int)(r612 == -1))) == 0) {
                        r75 = var1907;
                        r76 = r612;
                        r1094 = 145;
                    }
                }

                if(r1094 == 145) {
                    unsigned int r627 = *2688 + r75;
                    *2688 = *2688 + r75;

                    if(*2692 < r627) {
                        *2692 = r627;
                    }

                    unsigned int r630 = *2280;

                    if(r630 == 0) {
                        unsigned int r632 = *2272;

                        if((((unsigned int)(r632 == 0)) | ((unsigned int)(r76 < r632)))) {
                            *2272 = r76;
                        }

                        *2704 = r76;
                        *2708 = r75;
                        *2716 = 0;
                        *2292 = *2728;
                        *2288 = -1;
                        *2308 = 2296;
                        *2304 = 2296;
                        *2316 = 2304;
                        *2312 = 2304;
                        *2324 = 2312;
                        *2320 = 2312;
                        *2332 = 2320;
                        *2328 = 2320;
                        *2340 = 2328;
                        *2336 = 2328;
                        *2348 = 2336;
                        *2344 = 2336;
                        *2356 = 2344;
                        *2352 = 2344;
                        *2364 = 2352;
                        *2360 = 2352;
                        *2372 = 2360;
                        *2368 = 2360;
                        *2380 = 2368;
                        *2376 = 2368;
                        *2388 = 2376;
                        *2384 = 2376;
                        *2396 = 2384;
                        *2392 = 2384;
                        *2404 = 2392;
                        *2400 = 2392;
                        *2412 = 2400;
                        *2408 = 2400;
                        *2420 = 2408;
                        *2416 = 2408;
                        *2428 = 2416;
                        *2424 = 2416;
                        *2436 = 2424;
                        *2432 = 2424;
                        *2444 = 2432;
                        *2440 = 2432;
                        *2452 = 2440;
                        *2448 = 2440;
                        *2460 = 2448;
                        *2456 = 2448;
                        *2468 = 2456;
                        *2464 = 2456;
                        *2476 = 2464;
                        *2472 = 2464;
                        *2484 = 2472;
                        *2480 = 2472;
                        *2492 = 2480;
                        *2488 = 2480;
                        *2500 = 2488;
                        *2496 = 2488;
                        *2508 = 2496;
                        *2504 = 2496;
                        *2516 = 2504;
                        *2512 = 2504;
                        *2524 = 2512;
                        *2520 = 2512;
                        *2532 = 2520;
                        *2528 = 2520;
                        *2540 = 2528;
                        *2536 = 2528;
                        *2548 = 2536;
                        *2544 = 2536;
                        *2556 = 2544;
                        *2552 = 2544;
                        unsigned int r637 = r75 - 40;
                        unsigned int r639 = r76 + &gvar_8;
                        unsigned int r643 = (0 - r639) & 7;

                        if((r639 & 7) != 0) {
                            var1975 = r643;
                        }

                        unsigned int r645 = r76 + var1975;
                        unsigned int r648 = r637 - var1975;
                        *2280 = r645;
                        *2268 = r648;
                        *((unsigned int)(((int)gvar_4) + r645)) = r648 | 1;
                        *(((unsigned int)(((int)gvar_4) + r76)) + r637) = 40;
                        *2284 = *2744;
                    }
                    else {
                        unsigned int* r15 = 2704;

                        while(1) {
                            unsigned int r654 = *r15;
                            r656 = *((unsigned int)(((int)gvar_4) + ((int)r15)));

                            if(r654 + r656 != r76) {
                                unsigned int* r661 = *((unsigned int)(((int)gvar_8) + ((int)r15)));

                                if(!((unsigned char)(((int)r661) != 0))) {
                                    goto loc_50002701;
                                }
                                else {
                                    r15 = r661;
                                }
                            }
                            else {
                                break;
                            }
                        }

                        r1094 = 154;
                    loc_50002701:

                        if(r1094 == 154) {
                            unsigned int* r663 = r15 + 1;

                            if((*((unsigned int)(((int)gvar_C) + ((int)r15))) & &gvar_8) == 0 && (((unsigned int)(r76 > r630)) & ((unsigned int)(r630 >= r654)))) {
                                *r663 = r75 + r656;
                                unsigned int r673 = *2268 + r75;
                                unsigned int r675 = r630 + &gvar_8;
                                unsigned int r679 = (0 - r675) & 7;

                                if((r675 & 7) != 0) {
                                    var2070 = r679;
                                }

                                unsigned int r682 = r630 + var2070;
                                unsigned int r683 = r673 - var2070;
                                *2280 = r682;
                                *2268 = r683;
                                *((unsigned int)(((int)gvar_4) + r682)) = r683 | 1;
                                *(((unsigned int)(((int)gvar_4) + r630)) + r673) = 40;
                                *2284 = *2744;
                                goto loc_500039E0;
                            }
                        }

                        if(*2272 > r76) {
                            *2272 = r76;
                        }

                        unsigned int r692 = r75 + r76;
                        unsigned int* r39 = 2704;

                        while(*r39 != r692) {
                            unsigned int* r696 = *((unsigned int)(((int)gvar_8) + ((int)r39)));

                            if(!((unsigned char)(((int)r696) != 0))) {
                                goto loc_500028B2;
                            }
                            else {
                                r39 = r696;
                            }
                        }

                        r1094 = 162;
                    loc_500028B2:

                        if(r1094 == 162 && (*((unsigned int)(((int)gvar_C) + ((int)r39))) & &gvar_8) == 0) {
                            *r39 = r76;
                            unsigned int* r703 = r39 + 1;
                            *r703 = *r703 + r75;
                            unsigned int r707 = r76 + &gvar_8;
                            unsigned int r711 = (0 - r707) & 7;

                            if((r707 & 7) != 0) {
                                var2157 = r711;
                            }

                            r714 = r76 + var2157;
                            unsigned int r716 = r692 + &gvar_8;
                            unsigned int r720 = (0 - r716) & 7;

                            if((r716 & 7) != 0) {
                                var2175 = r720;
                            }

                            r722 = r692 + var2175;
                            r727 = r8 + r714;
                            r728 = r722 - r714 - r8;
                            *((unsigned int)(((int)gvar_4) + r714)) = r8 | 3;

                            if(r630 == r722) {
                                unsigned int r733 = *2268 + r728;
                                *2268 = *2268 + r728;
                                *2280 = r727;
                                *((unsigned int)(((int)gvar_4) + r727)) = r733 | 1;
                                goto loc_50003301;
                            }
                            else if(*2276 == r722) {
                                unsigned int r740 = *2264 + r728;
                                *2264 = *2264 + r728;
                                *2276 = r727;
                                *((unsigned int)(((int)gvar_4) + r727)) = r740 | 1;
                                *(r727 + r740) = r740;
                                goto loc_50003301;
                            }
                            else {
                                unsigned int r745 = *((unsigned int)(((int)gvar_4) + r722));

                                if((r745 & 3) == 1) {
                                    r749 = r745 & -8;
                                    unsigned int r750 = r745 >>> 3;

                                    if(r745 < 256) {
                                        unsigned int r753 = *((unsigned int)(((int)gvar_8) + r722));
                                        unsigned int r755 = *((unsigned int)(((int)gvar_C) + r722));

                                        if(r753 == r755) {
                                            *2256 = ((1 << r750) ^ -1) & *2256;
                                        }
                                        else {
                                            *((unsigned int)(((int)gvar_C) + r753)) = r755;
                                            *((unsigned int)(((int)gvar_8) + r755)) = r753;
                                        }

                                        goto loc_50002E57;
                                    }
                                    else {
                                        r766 = *((unsigned int)(((int)gvar_18) + r722));
                                        unsigned int r768 = *((unsigned int)(((int)gvar_C) + r722));

                                        if(r722 == r768) {
                                            unsigned int* r775 = r722 + &gvar_10;
                                            unsigned int* r776 = r775 + 1;
                                            unsigned int r777 = *r776;

                                            if(r777 == 0) {
                                                unsigned int r779 = *r775;

                                                if(r779 == 0) {
                                                    r60 = 0;
                                                    goto loc_50002CCF;
                                                }
                                                else {
                                                    r42 = r779;
                                                    r45 = r775;
                                                }
                                            }
                                            else {
                                                r42 = r777;
                                                r45 = r776;
                                            }

                                            r40 = r42;
                                            r43 = r45;
                                            goto loc_50002C1B;
                                        }
                                        else {
                                            unsigned int r772 = *((unsigned int)(((int)gvar_8) + r722));
                                            *((unsigned int)(((int)gvar_C) + r772)) = r768;
                                            *((unsigned int)(((int)gvar_8) + r768)) = r772;
                                            r60 = r768;
                                            goto loc_50002CCF;
                                        }
                                    }
                                }
                                else {
                                    r2 = r722;
                                    r16 = r728;
                                    goto loc_50002E6F;
                                }
                            }
                        }
                        else {
                            unsigned int* r3 = 2704;

                            while(1) {
                                unsigned int r914 = *r3;

                                if(r630 >= r914) {
                                    unsigned int r918 = *((unsigned int)(((int)gvar_4) + ((int)r3))) + r914;

                                    if(r630 < r918) {
                                        unsigned int r922 = r918 - 47;
                                        unsigned int r925 = r922 + &gvar_8;
                                        unsigned int r929 = (0 - r925) & 7;

                                        if((r925 & 7) != 0) {
                                            var2782 = r929;
                                        }

                                        unsigned int r931 = r922 + var2782;
                                        r932 = r630 + &gvar_10;

                                        if(r931 >= r932) {
                                            var2794 = r931;
                                        }

                                        r934 = var2794;
                                        unsigned int* r936 = var2794 + &gvar_8;
                                        unsigned int* r937 = var2794 + &gvar_18;
                                        unsigned int r938 = r75 - 40;
                                        unsigned int r940 = r76 + &gvar_8;
                                        unsigned int r944 = (0 - r940) & 7;

                                        if((r940 & 7) != 0) {
                                            var2815 = r944;
                                        }

                                        unsigned int r947 = r76 + var2815;
                                        unsigned int r948 = r938 - var2815;
                                        *2280 = r947;
                                        *2268 = r948;
                                        *((unsigned int)(((int)gvar_4) + r947)) = r948 | 1;
                                        *(((unsigned int)(((int)gvar_4) + r76)) + r938) = 40;
                                        *2284 = *2744;
                                        r954 = var2794 + &gvar_4;
                                        *r954 = 27;
                                        *r936 = *2704;
                                        *((unsigned int)(((int)gvar_8) + ((int)r936))) = *2712;
                                        *2704 = r76;
                                        *2708 = r75;
                                        *2716 = 0;
                                        *2712 = r936;
                                        r956 = r937;
                                        break;
                                    }
                                }

                                r3 = *((unsigned int)(((int)gvar_8) + ((int)r3)));
                            }

                            while(1) {
                                unsigned int* r955 = r956 + 1;
                                *r955 = 7;

                                if(r956 + 2 >= r918) {
                                    break;
                                }
                                else {
                                    r956 = r955;
                                }
                            }

                            if(r630 != r934) {
                                r963 = r934 - r630;
                                *r954 = *r954 & -2;
                                *((unsigned int)(((int)gvar_4) + r630)) = r963 | 1;
                                *r934 = r963;
                                unsigned int r969 = r963 >>> 3;

                                if(r963 >= 256) {
                                    goto loc_50003685;
                                }
                                else {
                                    unsigned int r972 = r969 * &gvar_8 + 2296;
                                    unsigned int r973 = *2256;
                                    unsigned int r974 = 1 << r969;

                                    if((r973 & r974) == 0) {
                                        *2256 = r973 | r974;
                                        r13 = r972;
                                        r83 = r972 + &gvar_8;
                                    }
                                    else {
                                        unsigned int* r978 = r972 + &gvar_8;
                                        r13 = *r978;
                                        r83 = r978;
                                    }

                                    *r83 = r630;
                                    *((unsigned int)(((int)gvar_C) + r13)) = r630;
                                    *((unsigned int)(((int)gvar_8) + r630)) = r13;
                                    *((unsigned int)(((int)gvar_C) + r630)) = r972;
                                }
                            }

                            goto loc_500039E0;
                        }

                    loc_50003685:
                        unsigned int r985 = r963 >>> &gvar_8;

                        if(r985 == 0) {
                            r14 = 0;
                        }
                        else if(r963 > 16777215) {
                            r14 = 31;
                        }
                        else {
                            unsigned int r990 = ((r985 + 1048320) >>> &gvar_10) & &gvar_8;
                            unsigned int r992 = r985 << r990;
                            unsigned int r995 = ((r992 + 520192) >>> &gvar_10) & &gvar_4;
                            unsigned int r997 = r992 << r995;
                            unsigned int r1000 = ((r997 + 245760) >>> &gvar_10) & 2;
                            unsigned int r1006 = 14 - (r990 | r995 | r1000) + ((r997 << r1000) >>> 15);
                            r14 = (r1006 * 2) | ((r963 >>> (r1006 + 7)) & 1);
                        }

                        unsigned int* r1012 = r14 * &gvar_4 + 2560;
                        *((unsigned int)(((int)gvar_1C) + r630)) = r14;
                        *((unsigned int)(((int)gvar_14) + r630)) = 0;
                        *r932 = 0;
                        unsigned int r1016 = *2260;
                        unsigned int r1017 = 1 << r14;

                        if((r1016 & r1017) == 0) {
                            *2260 = r1016 | r1017;
                            *r1012 = r630;
                            *((unsigned int)(((int)gvar_18) + r630)) = r1012;
                            *((unsigned int)(((int)gvar_C) + r630)) = r630;
                            *((unsigned int)(((int)gvar_8) + r630)) = r630;
                        }
                        else {
                            unsigned int r1025 = *r1012;

                            if((*((unsigned int)(((int)gvar_4) + r1025)) & -8) == r963) {
                                r11 = r1025;
                            }
                            else {
                                unsigned int r1032 = 25 - (r14 >>> 1);

                                if(r14 != 31) {
                                    var3074 = r1032;
                                }

                                unsigned int r10 = r963 << var3074;
                                unsigned int r12 = r1025;

                                while(1) {
                                    r1043 = (r10 >>> 31) * &gvar_4 + r12 + &gvar_10;
                                    unsigned int r1038 = *r1043;

                                    if(r1038 == 0) {
                                        break;
                                    }
                                    else {
                                        unsigned int r1036 = r10 * 2;

                                        if((*((unsigned int)(((int)gvar_4) + r1038)) & -8) == r963) {
                                            r11 = r1038;
                                            goto loc_5000397C;
                                        }
                                        else {
                                            r10 = r1036;
                                            r12 = r1038;
                                        }
                                    }
                                }

                                *r1043 = r630;
                                *((unsigned int)(((int)gvar_18) + r630)) = r12;
                                *((unsigned int)(((int)gvar_C) + r630)) = r630;
                                *((unsigned int)(((int)gvar_8) + r630)) = r630;
                                goto loc_500039E0;
                            }

                        loc_5000397C:
                            unsigned int* r1049 = r11 + &gvar_8;
                            unsigned int r1050 = *r1049;
                            *((unsigned int)(((int)gvar_C) + r1050)) = r630;
                            *r1049 = r630;
                            *((unsigned int)(((int)gvar_8) + r630)) = r1050;
                            *((unsigned int)(((int)gvar_C) + r630)) = r11;
                            *((unsigned int)(((int)gvar_18) + r630)) = 0;
                        }

                        goto loc_500039E0;
                    loc_50002C1B:

                        while(1) {
                            unsigned int* r782 = r40 + &gvar_14;
                            unsigned int r783 = *r782;

                            if(r783 == 0) {
                                unsigned int* r785 = r40 + &gvar_10;
                                unsigned int r786 = *r785;

                                if(r786 == 0) {
                                    *r43 = 0;
                                    r60 = r40;
                                    break;
                                }
                                else {
                                    r41 = r786;
                                    r44 = r785;
                                }
                            }
                            else {
                                r41 = r783;
                                r44 = r782;
                            }

                            r40 = r41;
                            r43 = r44;
                        }

                    loc_50002CCF:

                        if(r766 != 0) {
                            unsigned int r790 = *((unsigned int)(((int)gvar_1C) + r722));
                            unsigned int* r792 = r790 * &gvar_4 + 2560;

                            if(*r792 == r722) {
                                *r792 = r60;

                                if(r60 == 0) {
                                    *2260 = ((1 << r790) ^ -1) & *2260;
                                    goto loc_50002E57;
                                }
                            }
                            else {
                                unsigned int* r803 = r766 + &gvar_14;

                                if(*((unsigned int)(((int)gvar_10) + r766)) != r722) {
                                    var2400 = r803;
                                }

                                *var2400 = r60;

                                if(r60 == 0) {
                                    goto loc_50002E57;
                                }
                            }

                            *((unsigned int)(((int)gvar_18) + r60)) = r766;
                            unsigned int* r806 = r722 + &gvar_10;
                            unsigned int r807 = *r806;

                            if(r807 != 0) {
                                *((unsigned int)(((int)gvar_10) + r60)) = r807;
                                *((unsigned int)(((int)gvar_18) + r807)) = r60;
                            }

                            unsigned int r812 = *((unsigned int)(((int)gvar_4) + ((int)r806)));

                            if(r812 != 0) {
                                *((unsigned int)(((int)gvar_14) + r60)) = r812;
                                *((unsigned int)(((int)gvar_18) + r812)) = r60;
                            }
                        }

                    loc_50002E57:
                        r2 = r722 + r749;
                        r16 = r728 + r749;
                    loc_50002E6F:
                        unsigned int* r819 = r2 + &gvar_4;
                        *r819 = *r819 & -2;
                        *((unsigned int)(((int)gvar_4) + r727)) = r16 | 1;
                        *(r16 + r727) = r16;
                        unsigned int r826 = r16 >>> 3;

                        if(r16 < 256) {
                            unsigned int r829 = r826 * &gvar_8 + 2296;
                            unsigned int r830 = *2256;
                            unsigned int r831 = 1 << r826;

                            if((r830 & r831) == 0) {
                                *2256 = r830 | r831;
                                r20 = r829;
                                r84 = r829 + &gvar_8;
                            }
                            else {
                                unsigned int* r836 = r829 + &gvar_8;
                                r20 = *r836;
                                r84 = r836;
                            }

                            *r84 = r727;
                            *((unsigned int)(((int)gvar_C) + r20)) = r727;
                            *((unsigned int)(((int)gvar_8) + r727)) = r20;
                            *((unsigned int)(((int)gvar_C) + r727)) = r829;
                        }
                        else {
                            unsigned int r841 = r16 >>> &gvar_8;

                            if(r841 == 0) {
                                r21 = 0;
                            }
                            else if(r16 > 16777215) {
                                r21 = 31;
                            }
                            else {
                                unsigned int r847 = ((r841 + 1048320) >>> &gvar_10) & &gvar_8;
                                unsigned int r848 = r841 << r847;
                                unsigned int r851 = ((r848 + 520192) >>> &gvar_10) & &gvar_4;
                                unsigned int r853 = r848 << r851;
                                unsigned int r856 = ((r853 + 245760) >>> &gvar_10) & 2;
                                unsigned int r862 = 14 - (r847 | r851 | r856) + ((r853 << r856) >>> 15);
                                r21 = (r862 * 2) | ((r16 >>> (r862 + 7)) & 1);
                            }

                            unsigned int* r870 = r21 * &gvar_4 + 2560;
                            *((unsigned int)(((int)gvar_1C) + r727)) = r21;
                            unsigned int* r872 = r727 + &gvar_10;
                            *((unsigned int)(((int)gvar_4) + ((int)r872))) = 0;
                            *r872 = 0;
                            unsigned int r874 = *2260;
                            unsigned int r875 = 1 << r21;

                            if((r874 & r875) == 0) {
                                *2260 = r874 | r875;
                                *r870 = r727;
                                *((unsigned int)(((int)gvar_18) + r727)) = r870;
                                *((unsigned int)(((int)gvar_C) + r727)) = r727;
                                *((unsigned int)(((int)gvar_8) + r727)) = r727;
                            }
                            else {
                                unsigned int r883 = *r870;

                                if((*((unsigned int)(((int)gvar_4) + r883)) & -8) == r16) {
                                    r18 = r883;
                                }
                                else {
                                    unsigned int r890 = 25 - (r21 >>> 1);

                                    if(r21 != 31) {
                                        var2661 = r890;
                                    }

                                    unsigned int r17 = r16 << var2661;
                                    unsigned int r19 = r883;

                                    while(1) {
                                        r901 = (r17 >>> 31) * &gvar_4 + r19 + &gvar_10;
                                        unsigned int r896 = *r901;

                                        if(r896 == 0) {
                                            break;
                                        }
                                        else {
                                            unsigned int r894 = r17 * 2;

                                            if((*((unsigned int)(((int)gvar_4) + r896)) & -8) == r16) {
                                                r18 = r896;
                                                goto loc_50003293;
                                            }
                                            else {
                                                r17 = r894;
                                                r19 = r896;
                                            }
                                        }
                                    }

                                    *r901 = r727;
                                    *((unsigned int)(((int)gvar_18) + r727)) = r19;
                                    *((unsigned int)(((int)gvar_C) + r727)) = r727;
                                    *((unsigned int)(((int)gvar_8) + r727)) = r727;
                                    goto loc_50003301;
                                }

                            loc_50003293:
                                unsigned int* r907 = r18 + &gvar_8;
                                unsigned int r908 = *r907;
                                *((unsigned int)(((int)gvar_C) + r908)) = r727;
                                *r907 = r727;
                                *((unsigned int)(((int)gvar_8) + r727)) = r908;
                                *((unsigned int)(((int)gvar_C) + r727)) = r18;
                                *((unsigned int)(((int)gvar_18) + r727)) = 0;
                            }
                        }

                    loc_50003301:
                        __env.STACKTOP = r1095;
                        return r714 + &gvar_8;
                    }

                loc_500039E0:
                    unsigned int r1056 = *2268;

                    if(r8 < r1056) {
                        *2268 = r1056 - r8;
                        unsigned int r1060 = *2280;
                        *2280 = r8 + r1060;
                        *(((unsigned int)(((int)gvar_4) + r8)) + r1060) = (r1056 - r8) | 1;
                        *((unsigned int)(((int)gvar_4) + r1060)) = r8 | 3;
                        __env.STACKTOP = r1095;
                        return r1060 + &gvar_8;
                    }
                }

                int var3182 = ___errno_location();
                *var3182 = &gvar_C;
            }

            __env.STACKTOP = r1095;
            return 0;
        }
    }
}

void _free(unsigned int par0) {
    unsigned int* r194;
    unsigned int var795;
    unsigned int r3;
    unsigned int r5;
    unsigned int* r25;
    unsigned int r6;
    unsigned int r21;
    unsigned int* var526;
    unsigned int* r19;
    unsigned int r16;
    unsigned int* r20;
    unsigned int r17;
    unsigned int r23;
    unsigned int* var242;
    unsigned int* r13;
    unsigned int r10;
    unsigned int* r14;
    unsigned int r11;
    unsigned int r22;
    unsigned int* r278;
    unsigned int r8;
    unsigned int* r7;

    if(par0 != 0) {
        unsigned int* r139 = par0 - &gvar_8;
        unsigned int r215 = *2272;
        unsigned int r237 = *(par0 - &gvar_4);
        unsigned int r248 = r237 & -8;
        unsigned int r259 = (unsigned int)(((int)r139) + r248);

        if((r237 & 1) == 0) {
            unsigned int r29 = *r139;

            if((r237 & 3) == 0) {
                return;
            }
            else {
                unsigned int* r73 = (unsigned int*)(0 - r29 + ((int)r139));
                unsigned int r84 = r29 + r248;

                if(!((unsigned char)(((int)r73) >= r215))) {
                    return;
                }
                else if(!((unsigned char)(*2276 != ((int)r73)))) {
                    unsigned int* r269 = r259 + &gvar_4;
                    unsigned int r271 = *r269;

                    if((r271 & 3) != 3) {
                        r7 = r73;
                        r8 = r84;
                        r278 = r73;
                    }
                    else {
                        *2264 = r84;
                        *r269 = r271 & -2;
                        *((unsigned int)(((int)gvar_4) + ((int)r73))) = r84 | 1;
                        *((unsigned int*)(((int)r73) + r84)) = r84;
                        return;
                    }
                }
                else {
                    unsigned int r128 = r29 >>> 3;

                    if(r29 < 256) {
                        unsigned int r162 = *((unsigned int)(((int)gvar_8) + ((int)r73)));
                        unsigned int r184 = *((unsigned int)(((int)gvar_C) + ((int)r73)));

                        if(r162 == r184) {
                            *2256 = ((1 << r128) ^ -1) & *2256;
                        }
                        else {
                            *((unsigned int)(((int)gvar_C) + r162)) = r184;
                            *((unsigned int)(((int)gvar_8) + r184)) = r162;
                        }
                    }
                    else {
                        unsigned int r219 = *((unsigned int)(((int)gvar_18) + ((int)r73)));
                        unsigned int r221 = *((unsigned int)(((int)gvar_C) + ((int)r73)));

                        if(!((unsigned char)(((int)r73) != r221))) {
                            unsigned int* r228 = r73 + &gvar_4;
                            unsigned int* r229 = r228 + 1;
                            unsigned int r230 = *r229;

                            if(r230 == 0) {
                                unsigned int r232 = *r228;

                                if(r232 == 0) {
                                    r22 = 0;
                                    goto loc_50003DC7;
                                }
                                else {
                                    r11 = r232;
                                    r14 = r228;
                                }
                            }
                            else {
                                r11 = r230;
                                r14 = r229;
                            }

                            unsigned int r9 = r11;
                            unsigned int* r12 = r14;

                            while(1) {
                                unsigned int* r234 = r9 + &gvar_14;
                                unsigned int r235 = *r234;

                                if(r235 == 0) {
                                    unsigned int* r238 = r9 + &gvar_10;
                                    unsigned int r239 = *r238;

                                    if(r239 == 0) {
                                        *r12 = 0;
                                        r22 = r9;
                                        break;
                                    }
                                    else {
                                        r10 = r239;
                                        r13 = r238;
                                    }
                                }
                                else {
                                    r10 = r235;
                                    r13 = r234;
                                }

                                r9 = r10;
                                r12 = r13;
                            }
                        }
                        else {
                            unsigned int r224 = *((unsigned int)(((int)gvar_8) + ((int)r73)));
                            *((unsigned int)(((int)gvar_C) + r224)) = r221;
                            *((unsigned int)(((int)gvar_8) + r221)) = r224;
                            r22 = r221;
                        }

                    loc_50003DC7:

                        if(r219 != 0) {
                            unsigned int r243 = *((unsigned int)(((int)gvar_1C) + ((int)r73)));
                            unsigned int* r244 = r243 * &gvar_4 + 2560;

                            if(!((unsigned char)(*r244 != ((int)r73)))) {
                                *r244 = r22;

                                if(r22 == 0) {
                                    *2260 = ((1 << r243) ^ -1) & *2260;
                                    r7 = r73;
                                    r8 = r84;
                                    r278 = r73;
                                    goto loc_50003F8C;
                                }
                            }
                            else {
                                unsigned int* r255 = r219 + &gvar_14;

                                if(((unsigned char)(*((unsigned int)(((int)gvar_10) + r219)) != ((int)r73)))) {
                                    var242 = r255;
                                }

                                *var242 = r22;

                                if(r22 == 0) {
                                    r7 = r73;
                                    r8 = r84;
                                    r278 = r73;
                                    goto loc_50003F8C;
                                }
                            }

                            *((unsigned int)(((int)gvar_18) + r22)) = r219;
                            unsigned int* r258 = r73 + &gvar_4;
                            unsigned int r260 = *r258;

                            if(r260 != 0) {
                                *((unsigned int)(((int)gvar_10) + r22)) = r260;
                                *((unsigned int)(((int)gvar_18) + r260)) = r22;
                            }

                            unsigned int r265 = *((unsigned int)(((int)gvar_4) + ((int)r258)));

                            if(r265 == 0) {
                                r7 = r73;
                                r8 = r84;
                                r278 = r73;
                                goto loc_50003F8C;
                            }
                            else {
                                *((unsigned int)(((int)gvar_14) + r22)) = r265;
                                *((unsigned int)(((int)gvar_18) + r265)) = r22;
                            }
                        }
                    }

                    r7 = r73;
                    r8 = r84;
                    r278 = r73;
                }
            }
        }
        else {
            r7 = r139;
            r8 = r248;
            r278 = r139;
        }

    loc_50003F8C:

        if(!((unsigned char)(r259 > ((int)r278)))) {
            return;
        }
        else {
            unsigned int* r280 = r259 + &gvar_4;
            unsigned int r282 = *r280;

            if((r282 & 1) == 0) {
                return;
            }
            else {

                if((r282 & 2) != 0) {
                    *r280 = r282 & -2;
                    *((unsigned int)(((int)gvar_4) + ((int)r7))) = r8 | 1;
                    *((unsigned int*)(r8 + ((int)r278))) = r8;
                    r21 = r8;
                }
                else if(*2280 == r259) {
                    unsigned int r290 = *2268 + r8;
                    *2268 = *2268 + r8;
                    *2280 = r7;
                    *((unsigned int)(((int)gvar_4) + ((int)r7))) = r290 | 1;

                    if(((unsigned char)(*2276 == ((int)r7)))) {
                        *2276 = 0;
                        *2264 = 0;
                    }

                    return;
                }
                else if(*2276 == r259) {
                    unsigned int r36 = *2264 + r8;
                    *2264 = *2264 + r8;
                    *2276 = r278;
                    *((unsigned int)(((int)gvar_4) + ((int)r7))) = r36 | 1;
                    *((unsigned int*)(r36 + ((int)r278))) = r36;
                    return;
                }
                else {
                    unsigned int r42 = (r282 & -8) + r8;
                    unsigned int r43 = r282 >>> 3;

                    if(r282 < 256) {
                        unsigned int r46 = *((unsigned int)(((int)gvar_8) + r259));
                        unsigned int r48 = *((unsigned int)(((int)gvar_C) + r259));

                        if(r46 == r48) {
                            *2256 = ((1 << r43) ^ -1) & *2256;
                        }
                        else {
                            *((unsigned int)(((int)gvar_C) + r46)) = r48;
                            *((unsigned int)(((int)gvar_8) + r48)) = r46;
                        }
                    }
                    else {
                        unsigned int r58 = *((unsigned int)(((int)gvar_18) + r259));
                        unsigned int r60 = *((unsigned int)(((int)gvar_C) + r259));

                        if(r60 == r259) {
                            unsigned int* r67 = r259 + &gvar_10;
                            unsigned int* r68 = r67 + 1;
                            unsigned int r69 = *r68;

                            if(r69 == 0) {
                                unsigned int r71 = *r67;

                                if(r71 == 0) {
                                    r23 = 0;
                                    goto loc_5000425F;
                                }
                                else {
                                    r17 = r71;
                                    r20 = r67;
                                }
                            }
                            else {
                                r17 = r69;
                                r20 = r68;
                            }

                            unsigned int r15 = r17;
                            unsigned int* r18 = r20;

                            while(1) {
                                unsigned int* r74 = r15 + &gvar_14;
                                unsigned int r75 = *r74;

                                if(r75 == 0) {
                                    unsigned int* r77 = r15 + &gvar_10;
                                    unsigned int r78 = *r77;

                                    if(r78 == 0) {
                                        *r18 = 0;
                                        r23 = r15;
                                        break;
                                    }
                                    else {
                                        r16 = r78;
                                        r19 = r77;
                                    }
                                }
                                else {
                                    r16 = r75;
                                    r19 = r74;
                                }

                                r15 = r16;
                                r18 = r19;
                            }
                        }
                        else {
                            unsigned int r64 = *((unsigned int)(((int)gvar_8) + r259));
                            *((unsigned int)(((int)gvar_C) + r64)) = r60;
                            *((unsigned int)(((int)gvar_8) + r60)) = r64;
                            r23 = r60;
                        }

                    loc_5000425F:

                        if(r58 != 0) {
                            unsigned int r82 = *((unsigned int)(((int)gvar_1C) + r259));
                            unsigned int* r83 = r82 * &gvar_4 + 2560;

                            if(*r83 == r259) {
                                *r83 = r23;

                                if(r23 == 0) {
                                    *2260 = ((1 << r82) ^ -1) & *2260;
                                    goto loc_5000439C;
                                }
                            }
                            else {
                                unsigned int* r94 = r58 + &gvar_14;

                                if(*((unsigned int)(((int)gvar_10) + r58)) != r259) {
                                    var526 = r94;
                                }

                                *var526 = r23;

                                if(r23 == 0) {
                                    goto loc_5000439C;
                                }
                            }

                            *((unsigned int)(((int)gvar_18) + r23)) = r58;
                            unsigned int* r98 = r259 + &gvar_10;
                            unsigned int r99 = *r98;

                            if(r99 != 0) {
                                *((unsigned int)(((int)gvar_10) + r23)) = r99;
                                *((unsigned int)(((int)gvar_18) + r99)) = r23;
                            }

                            unsigned int r104 = *((unsigned int)(((int)gvar_4) + ((int)r98)));

                            if(r104 != 0) {
                                *((unsigned int)(((int)gvar_14) + r23)) = r104;
                                *((unsigned int)(((int)gvar_18) + r104)) = r23;
                            }
                        }
                    }

                loc_5000439C:
                    *((unsigned int)(((int)gvar_4) + ((int)r7))) = r42 | 1;
                    *((unsigned int*)(r42 + ((int)r278))) = r42;

                    if(!((unsigned char)(*2276 != ((int)r7)))) {
                        *2264 = r42;
                        return;
                    }
                    else {
                        r21 = r42;
                    }
                }

                unsigned int r119 = r21 >>> 3;

                if(r21 < 256) {
                    unsigned int r122 = r119 * &gvar_8 + 2296;
                    unsigned int r123 = *2256;
                    unsigned int r124 = 1 << r119;

                    if((r123 & r124) == 0) {
                        *2256 = r123 | r124;
                        r6 = r122;
                        r25 = r122 + &gvar_8;
                    }
                    else {
                        unsigned int* r129 = r122 + &gvar_8;
                        r6 = *r129;
                        r25 = r129;
                    }

                    *r25 = r7;
                    *((unsigned int)(((int)gvar_C) + r6)) = r7;
                    *((unsigned int)(((int)gvar_8) + ((int)r7))) = r6;
                    *((unsigned int)(((int)gvar_C) + ((int)r7))) = r122;
                    return;
                }
                else {
                    unsigned int r134 = r21 >>> &gvar_8;

                    if(r134 == 0) {
                        r5 = 0;
                    }
                    else if(r21 > 16777215) {
                        r5 = 31;
                    }
                    else {
                        unsigned int r141 = ((r134 + 1048320) >>> &gvar_10) & &gvar_8;
                        unsigned int r142 = r134 << r141;
                        unsigned int r145 = ((r142 + 520192) >>> &gvar_10) & &gvar_4;
                        unsigned int r147 = r142 << r145;
                        unsigned int r150 = ((r147 + 245760) >>> &gvar_10) & 2;
                        unsigned int r156 = 14 - (r141 | r145 | r150) + ((r147 << r150) >>> 15);
                        r5 = (r156 * 2) | ((r21 >>> (r156 + 7)) & 1);
                    }

                    unsigned int* r163 = r5 * &gvar_4 + 2560;
                    *((unsigned int)(((int)gvar_1C) + ((int)r7))) = r5;
                    *((unsigned int)(((int)gvar_14) + ((int)r7))) = 0;
                    *((unsigned int)(((int)gvar_10) + ((int)r7))) = 0;
                    unsigned int r167 = *2260;
                    unsigned int r168 = 1 << r5;

                    if((r167 & r168) == 0) {
                        *2260 = r167 | r168;
                        *r163 = r7;
                        *((unsigned int)(((int)gvar_18) + ((int)r7))) = r163;
                        *((unsigned int)(((int)gvar_C) + ((int)r7))) = r7;
                        *((unsigned int)(((int)gvar_8) + ((int)r7))) = r7;
                    }
                    else {
                        unsigned int r176 = *r163;

                        if((*((unsigned int)(((int)gvar_4) + r176)) & -8) == r21) {
                            r3 = r176;
                        }
                        else {
                            unsigned int r183 = 25 - (r5 >>> 1);

                            if(r5 != 31) {
                                var795 = r183;
                            }

                            unsigned int r2 = r21 << var795;
                            unsigned int r4 = r176;

                            while(1) {
                                r194 = (r2 >>> 31) * &gvar_4 + r4 + &gvar_10;
                                unsigned int r189 = *r194;

                                if(r189 == 0) {
                                    break;
                                }
                                else {
                                    unsigned int r187 = r2 * 2;

                                    if((*((unsigned int)(((int)gvar_4) + r189)) & -8) == r21) {
                                        r3 = r189;
                                        goto loc_500047B7;
                                    }
                                    else {
                                        r2 = r187;
                                        r4 = r189;
                                    }
                                }
                            }

                            *r194 = r7;
                            *((unsigned int)(((int)gvar_18) + ((int)r7))) = r4;
                            *((unsigned int)(((int)gvar_C) + ((int)r7))) = r7;
                            *((unsigned int)(((int)gvar_8) + ((int)r7))) = r7;
                            goto loc_5000481E;
                        }

                    loc_500047B7:
                        unsigned int* r200 = r3 + &gvar_8;
                        unsigned int r201 = *r200;
                        *((unsigned int)(((int)gvar_C) + r201)) = r7;
                        *r200 = r7;
                        *((unsigned int)(((int)gvar_8) + ((int)r7))) = r201;
                        *((unsigned int)(((int)gvar_C) + ((int)r7))) = r3;
                        *((unsigned int)(((int)gvar_18) + ((int)r7))) = 0;
                    }

                loc_5000481E:
                    unsigned int r208 = *2288 - 1;
                    *2288 = *2288 - 1;

                    if(r208 != 0) {
                        return;
                    }
                    else {
                        unsigned int* r1 = 2712;

                        while(1) {
                            unsigned int r0 = *r1;
                            unsigned int* r211 = r0 + &gvar_8;

                            if(r0 == 0) {
                                break;
                            }
                            else {
                                r1 = r211;
                            }
                        }

                        *2288 = -1;
                    }
                }
            }
        }
    }
}

int f25(unsigned int par0) {
    // DEMO VERSION LIMITATION - This method was not decompiled
}

int f26(unsigned int* par0, unsigned int par1, unsigned int par2) {
    int var87;
    int r63 = __env.STACKTOP;

    if(__env.STACKTOP + 48 >= __env.STACK_MAX) {
        abortStackOverflow(48);
    }

    int r57 = r63 + 32;
    int r56 = r63 + &gvar_10;
    int r27 = r63;
    unsigned int* r38 = par0 + 7;
    unsigned int r49 = *r38;
    *r63 = *r38;
    unsigned int* r53 = par0 + 5;
    unsigned int r55 = *r53 - r49;
    *((unsigned int)(((int)gvar_4) + r63)) = *r53 - r49;
    *((unsigned int)(((int)gvar_8) + r63)) = par1;
    *((unsigned int)(((int)gvar_C) + r63)) = par2;
    unsigned int r9 = par2 + r55;
    unsigned int* r10 = par0 + 15;
    *r56 = *r10;
    *((unsigned int)(((int)gvar_4) + r56)) = r63;
    *((unsigned int)(((int)gvar_8) + r56)) = 2;
    int var55 = ___syscall146(r56, 146);
    int var58 = f28(var55);
    int r14 = var58;

    if(r9 != var58) {
        unsigned int r1 = 2;
        unsigned int r2 = r9;
        int r3 = r63;
        int r23 = var58;

        while(r23 >= 0) {
            unsigned int r33 = r2 - r23;
            unsigned int r36 = (unsigned int)(*((unsigned int)(((int)gvar_4) + r3)) < r23);

            if(!r36) {
                var87 = r3;
            }

            int r6 = var87;
            unsigned int r5 = ((r36 * -2147483648) >> 31) + r1;
            *var87 = *var87 + r23;
            unsigned int* r43 = var87 + &gvar_4;
            *r43 = *r43 - r23;
            *r57 = *r10;
            *((unsigned int)(((int)gvar_4) + r57)) = var87;
            *((unsigned int)(((int)gvar_8) + r57)) = r5;
            int var131 = ___syscall146(r57, 146);
            int var134 = f28(var131);
            int r50 = var134;

            if(r33 == var134) {
                goto loc_50004B17;
            }
            else {
                r1 = r5;
                r2 = r33;
                r3 = var87;
                r23 = var134;
            }
        }

        *((unsigned int)(((int)gvar_10) + ((int)par0))) = 0;
        *r38 = 0;
        *r53 = 0;
        *par0 = *par0 | 32;
    }

loc_50004B17:
    unsigned int r17 = *(par0 + 11);
    *((unsigned int)(((int)gvar_10) + ((int)par0))) = *(par0 + &gvar_C) + r17;
    *r38 = r17;
    *r53 = r17;
    __env.STACKTOP = r63;
    return par2;
}

int f27(unsigned int par0, unsigned int par1, unsigned int par2) {
    unsigned int r1;
    int r15 = __env.STACKTOP;

    if(__env.STACKTOP + 32 >= __env.STACK_MAX) {
        abortStackOverflow(32);
    }

    unsigned int* r2 = r15 + &gvar_14;
    *r15 = *(par0 + 60);
    *((unsigned int)(((int)gvar_4) + r15)) = 0;
    *((unsigned int)(((int)gvar_8) + r15)) = par1;
    *((unsigned int)(((int)gvar_C) + r15)) = r2;
    *((unsigned int)(((int)gvar_10) + r15)) = par2;
    int var30 = ___syscall140(r15, 140);
    int var33 = f28(var30);

    if(var33 < 0) {
        *r2 = -1;
        r1 = -1;
    }
    else {
        r1 = *r2;
    }

    __env.STACKTOP = r15;
    return r1;
}

int f28(unsigned int par0) {
    unsigned int r0;

    if(par0 > -4096) {
        unsigned int r2 = 0 - par0;
        int var5 = ___errno_location();
        *var5 = r2;
        r0 = -1;
    }
    else {
        r0 = par0;
    }

    return r0;
}

int ___errno_location() {
    return 2752;
}

int f30(unsigned int par0) {
    return par0;
}

int f31(int par0, int par1, int par2) {
    // DEMO VERSION LIMITATION - This method was not decompiled
}

int f33(unsigned int par0) {
    return 0;
}

void f34(unsigned int par0) {
}

int f35() {
    ___lock(2756);
    return 2764;
}

void f36() {
    ___unlock(2756);
}

int _fflush(int par0) {
    int r0;
    int r6;
    int r24;
    int r4;
    int r28;

    if(par0 == 0) {

        if(gvar_4BC == 0) {
            r28 = 0;
        }
        else {
            int var11 = _fflush(gvar_4BC);
            r28 = var11;
        }

        int var13 = f35();
        int r2 = *var13;

        if(r2 == 0) {
            r4 = r28;
        }
        else {
            int r3 = r2;
            int r5 = r28;

            while(1) {

                if(*(r3 + 76) > -1) {
                    int var30 = f33(r3);
                    r24 = var30;
                }
                else {
                    r24 = 0;
                }

                if(*((unsigned int)(((int)gvar_1C) + r3)) < *((unsigned int)(((int)gvar_14) + r3))) {
                    int var46 = f38(r3);
                    r6 = r5 | var46;
                }
                else {
                    r6 = r5;
                }

                if(r24 != 0) {
                    f34(r3);
                }

                int r1 = *(r3 + 56);

                if(r1 == 0) {
                    r4 = r6;
                    break;
                }
                else {
                    r3 = r1;
                    r5 = r6;
                }
            }
        }

        f36();
        r0 = r4;
    }
    else if(*(par0 + 76) <= -1) {
        int var78 = f38(par0);
        r0 = var78;
    }
    else {
        int var81 = f33(par0);
        unsigned int r36 = (unsigned int)(var81 == 0);
        int var85 = f38(par0);
        int r33 = var85;

        if(!r36) {
            f34(par0);
        }

        r0 = r33;
    }

    return r0;
}

int f38(int par0) {
    unsigned int* r1 = par0 + &gvar_14;
    unsigned int* r14 = par0 + &gvar_1C;

    if(*r1 > *r14) {
        *(((*(par0 + 36) & 7) + 2) * &gvar_4 + ptr_f45)(0, 0, par0);
    }

    unsigned int* r2 = par0 + &gvar_4;
    unsigned int r3 = *r2;
    unsigned int* r4 = par0 + &gvar_8;
    unsigned int r5 = *r4;

    if(r3 < r5) {
        *(((*(par0 + 40) & 7) + 2) * &gvar_4 + ptr_f45)(1, r3 - r5, par0);
    }

    *((unsigned int)(((int)gvar_10) + par0)) = 0;
    *r14 = 0;
    *r1 = 0;
    *r4 = 0;
    *r2 = 0;
    return 0;
}

void runPostSets() {
}

int _memcpy(int par0, int par1, int par2) {
    int r1;

    if(par2 >= 8192) {
        return _emscripten_memcpy_big(par2, par1, par0);
    }
    else {
        int r0 = par0;
        int r3 = par0 + par2;

        if((par0 & 3) == (par1 & 3)) {

            while((par0 & 3) != 0) {

                if(par2 == 0) {
                    return r0;
                }
                else {
                    *par0 = *par1;
                    ++par0;
                    ++par1;
                    --par2;
                }
            }

            r1 = r3 & -4;
            int r2 = r1 - 64;

            while(par0 <= r2) {
                *par0 = *par1;
                *((unsigned int)(((int)gvar_4) + par0)) = *((unsigned int)(((int)gvar_4) + par1));
                *((unsigned int)(((int)gvar_8) + par0)) = *((unsigned int)(((int)gvar_8) + par1));
                *((unsigned int)(((int)gvar_C) + par0)) = *((unsigned int)(((int)gvar_C) + par1));
                *((unsigned int)(((int)gvar_10) + par0)) = *((unsigned int)(((int)gvar_10) + par1));
                *((unsigned int)(((int)gvar_14) + par0)) = *((unsigned int)(((int)gvar_14) + par1));
                *((unsigned int)(((int)gvar_18) + par0)) = *((unsigned int)(((int)gvar_18) + par1));
                *((unsigned int)(((int)gvar_1C) + par0)) = *((unsigned int)(((int)gvar_1C) + par1));
                *(par0 + 32) = *(par1 + 32);
                *(par0 + 36) = *(par1 + 36);
                *(par0 + 40) = *(par1 + 40);
                *(par0 + 44) = *(par1 + 44);
                *(par0 + 48) = *(par1 + 48);
                *(par0 + 52) = *(par1 + 52);
                *(par0 + 56) = *(par1 + 56);
                *(par0 + 60) = *(par1 + 60);
                par0 += 64;
                par1 += 64;
            }

            while(par0 < r1) {
                *par0 = *par1;
                par0 += &gvar_4;
                par1 += &gvar_4;
            }
        }
        else {
            r1 = r3 - &gvar_4;

            while(par0 < r1) {
                *par0 = *par1;
                *(par0 + 1) = *(par1 + 1);
                *(par0 + 2) = *(par1 + 2);
                *(par0 + 3) = *(par1 + 3);
                par0 += &gvar_4;
                par1 += &gvar_4;
            }
        }

        while(par0 < r3) {
            *par0 = *par1;
            ++par0;
            ++par1;
        }

        return r0;
    }
}

int _memset(int* par0, unsigned int par1, int par2) {
    int r0 = (int)(((int)par0) + par2);
    par1 = (unsigned int)par1_lo;

    if(par2 >= 67) {

        while(((unsigned int)(((int)par0) & 3)) != 0) {
            *par0 = (unsigned char)par1;
            par0 = (int*)(((char*)par0) + 1);
        }

        int r1 = r0 & -4;
        int r2 = r1 - 64;
        unsigned int r3 = (par1 * 256) | (par1 * 65536) | (par1 * 16777216) | par1;

        while(((unsigned char)(((int)par0) <= r2))) {
            *par0 = r3;
            *((unsigned int)(((int)gvar_4) + ((int)par0))) = r3;
            *((unsigned int)(((int)gvar_8) + ((int)par0))) = r3;
            *((unsigned int)(((int)gvar_C) + ((int)par0))) = r3;
            *((unsigned int)(((int)gvar_10) + ((int)par0))) = r3;
            *((unsigned int)(((int)gvar_14) + ((int)par0))) = r3;
            *((unsigned int)(((int)gvar_18) + ((int)par0))) = r3;
            *((unsigned int)(((int)gvar_1C) + ((int)par0))) = r3;
            *(par0 + &gvar_8) = r3;
            *(par0 + 9) = r3;
            *(par0 + 10) = r3;
            *(par0 + 11) = r3;
            *(par0 + &gvar_C) = r3;
            *(par0 + 13) = r3;
            *(par0 + 14) = r3;
            *(par0 + 15) = r3;
            par0 += &gvar_10;
        }

        while(((unsigned char)(((int)par0) < r1))) {
            *par0 = r3;
            ++par0;
        }
    }

    while(((unsigned char)(((int)par0) < r0))) {
        *par0 = (unsigned char)par1;
        par0 = (int*)(((char*)par0) + 1);
    }

    return r0 - par2;
}

int _sbrk(int par0) {
    int r0 = *__env.DYNAMICTOP_PTR;
    int r2 = par0 + r0;

    if(((((unsigned int)(par0 > 0)) & ((unsigned int)(r0 > r2))) | ((unsigned int)(r2 < 0)))) {
        abortOnCannotGrowMemory();
        ___setErrNo(&gvar_C);
        return -1;
    }
    else {
        *__env.DYNAMICTOP_PTR = r2;
        int var6 = getTotalMemory();

        if(r2 > var6) {
            int var16 = enlargeMemory();

            if(var16 == 0) {
                *__env.DYNAMICTOP_PTR = r0;
                ___setErrNo(&gvar_C);
                return -1;
            }
        }

        return r0;
    }
}

int dynCall_ii(unsigned int par0, int par1) {
    return *((par0 & 1) * &gvar_4 + ptr_f45)(par1);
}

int dynCall_iiii(unsigned int par0, int par1, int par2, int par3) {
    return *(((par0 & 7) + 2) * &gvar_4 + ptr_f45)(par3, par2, par1);
}

int f45(unsigned int par0) {
    nullFunc_ii(0);
    return 0;
}

int f46(unsigned int par0, unsigned int par1, unsigned int par2) {
    nullFunc_iiii(1);
    return 0;
}
