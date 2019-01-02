# int __cdecl main(int argc, const char **argv, const char **envp)
                .globl main
main:                                   # CODE XREF: __crtmain+24↑p

.set back_chain, -0x1A0
.set rc4_state, -0x198
.set ciphertext, -0x98
.set hint, -0x70
.set rc4_key, -0x50
.set var_38, -0x38
.set var_30, -0x30
.set var_14, -0x14
.set var_10, -0x10
.set var_C, -0xC
.set var_8, -8
.set var_4, -4
.set sender_lr,  4

                stwu      r1, back_chain(r1)
                mflr      r0
                stw       r0, 0x1A0+sender_lr(r1)
                stw       r27, 0x1A0+var_14(r1)
                stw       r28, 0x1A0+var_10(r1)
                stw       r29, 0x1A0+var_C(r1)
                stw       r30, 0x1A0+var_8(r1)
                stw       r31, 0x1A0+var_4(r1)
                bl        xenon_smc_power_shutdown
                li        r3, -1        # videoMode
                bl        xenos_init
                li        r4, -1        # foreground
                li        r3, 0         # background
                bl        console_set_colors
                bl        console_init
                bl        console_clrscr
                lis       r3, aHackvent2018@ha
                addi      r3, r3, aHackvent2018@l # fmt
                crclr     4*cr1+eq
                bl        printf
                lis       r3, aDrschottkyWish@ha
                addi      r3, r3, aDrschottkyWish@l # s
                bl        puts
                li        r3, 0         # nr
                bl        xenon_secotp_read_line
                mr        r8, r4
                insrdi    r8, r3, 32,0
                li        r3, 1         # nr
                std       r8, 0x1A0+var_30(r1)
                bl        xenon_secotp_read_line
                lis       r7, dword_8001EA20@ha
                ld        r8, 0x1A0+var_30(r1)
                lis       r6, qword_8001EA88@ha
                addi      r9, r7, dword_8001EA20@l
                addi      r10, r6, qword_8001EA88@l
                li        r27, 8
                lwz       r12, dword_8001EA20@l(r7)
                insrdi    r4, r3, 32,0
                ld        r6, qword_8001EA88@l(r6)
                mtctr     r27
                lwz       r30, (dword_8001EA24 - 0x8001EA20)(r9)
                lwz       r31, (dword_8001EA28 - 0x8001EA20)(r9)
                lwz       r0, (dword_8001EA2C - 0x8001EA20)(r9)
                lwz       r11, (dword_8001EA30 - 0x8001EA20)(r9)
                lwz       r3, (dword_8001EA34 - 0x8001EA20)(r9)
                lwz       r5, (dword_8001EA38 - 0x8001EA20)(r9)
                lwz       r7, (dword_8001EA40 - 0x8001EA20)(r9)
                ld        r28, (qword_8001EA90 - 0x8001EA88)(r10)
                ld        r29, (qword_8001EA98 - 0x8001EA88)(r10)
                lbz       r10, (byte_8001EAA0 - 0x8001EA88)(r10)
                std       r6, 0x1A0+var_38(r1)
                lwz       r6, (dword_8001EA3C - 0x8001EA20)(r9)
                lwz       r9, (dword_8001EA44 - 0x8001EA20)(r9)
                ld        r27, 0x1A0+var_38(r1)
                stw       r9, 0x1A0+ciphertext+0x24(r1)
                li        r9, 0
                std       r27, 0x1A0+hint(r1)
                stw       r12, 0x1A0+ciphertext(r1)
                std       r28, 0x1A0+hint+8(r1)
                stw       r30, 0x1A0+ciphertext+4(r1)
                std       r29, 0x1A0+hint+0x10(r1)
                stw       r31, 0x1A0+ciphertext+8(r1)
                stb       r10, 0x1A0+hint+0x18(r1)
                stw       r0, 0x1A0+ciphertext+0xC(r1)
                stw       r11, 0x1A0+ciphertext+0x10(r1)
                stw       r3, 0x1A0+ciphertext+0x14(r1)
                stw       r5, 0x1A0+ciphertext+0x18(r1)
                stw       r6, 0x1A0+ciphertext+0x1C(r1)
                stw       r7, 0x1A0+ciphertext+0x20(r1)
                nop

loc_80002008:                           # CODE XREF: main+140↓j
                srawi     r7, r9, 1
                addze     r7, r7
                addi      r10, r1, 0x1A0+rc4_key
                subfic    r7, r7, 7
                slwi      r7, r7, 3
                srd       r6, r8, r7
                srd       r7, r4, r7
                stbux     r6, r10, r9
                addi      r9, r9, 2
                stb       r7, 1(r10)
                bdnz      loc_80002008
                addi      r3, r1, 0x1A0+rc4_state # m
                li        r5, 0x100     # n
                li        r4, 0         # c
                bl        memset
                addi      r3, r1, 0x1A0+rc4_state # state
                addi      r4, r1, 0x1A0+rc4_key # key
                li        r5, 0x10      # len
                bl        rc4_init
                addi      r3, r1, 0x1A0+rc4_state # state
                addi      r4, r1, 0x1A0+ciphertext # data
                li        r5, 0x28      # len
                bl        rc4_crypt
                li        r3, 0         # background
                li        r4, 0         # foreground
                bl        console_set_colors
                addi      r31, r1, 0x1A0+rc4_state+0xFF
                addi      r30, r1, 0x1A0+ciphertext+0x27

loc_80002078:                           # CODE XREF: main+194↓j
                lbzu      r3, 1(r31)    # c
                bl        putchar
                cmpw      cr7, r31, r30
                bne       cr7, loc_80002078

loc_80002088:                           # CODE XREF: main+1A8↓j
                li        r3, 0xD       # c
                bl        putchar
                li        r3, 0xD       # c
                bl        putchar
                b         loc_80002088
