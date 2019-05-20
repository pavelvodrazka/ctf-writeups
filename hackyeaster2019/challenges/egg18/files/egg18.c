/* STACK:
.data:00000000                     db "fQ", 1, "iP", 13h, "WP", 3, 'j', 6, 7, 7, '{', 5, 4
.data:00000010                     db 'P', 0Bh, 6, 7, "WzP", 4
*/

int validatePassword(unsigned int param0, unsigned int param1, unsigned int param2, unsigned int param3, int param4, unsigned int param5, int param6, int param7, int param8, int param9, unsigned int param10, int param11, unsigned int param12, int param13, unsigned int param14, unsigned int param15, unsigned int param16, unsigned int param17, unsigned int param18, unsigned int param19, unsigned int param20, unsigned int param21, int param22, int param23) {
    functions();
    *24 = param0;
    *25 = param1;
    *26 = param2;
    *27 = param3;
    *28 = param4;
    *29 = param5;
    *30 = param6;
    *31 = param7;
    *32 = param8;
    *33 = param9;
    *34 = param10;
    *35 = param11;
    *36 = param12;
    *37 = param13;
    *38 = param14;
    *39 = param15;
    *40 = param16;
    *41 = param17;
    *42 = param18;
    *43 = param19;
    *44 = param20;
    *45 = param21;
    *46 = param22;
    *47 = param23;
    int i = 4;

    do {
        // check if letters in { 48, 49, 51, 52, 53, 72, 76, 88, 99, 100, 102, 114 } ~ "01345HLXcdfr"
        int valid = validateRange(((unsigned int)(*(i + 24))));
        if (valid == 0) {
            return 0;
        }
        else {
            ++i;
        }
    } while (param23 <= 24);

    if (param0 != 84) { // p0 == 84 ~ 'T'
        return 0;
    }
    else if (param1 != 104) { // p1 == 104 ~ 'h'
        return 0;
    }
    else if (param2 != 51) { // p2 == 51 ~ '3'
        return 0;
    }
    else if (param3 != 80) { // p3 = 80 ~ 'P'
        return 0;
    }
    else if (param17 != param23) { // p17 == p23
        return 0;
    }
    else if (param12 != param16) { // p12 == p16
        return 0;
    }
    else if (param15 != param22) { // p15 == p22
        return 0;
    }
    else if (param5 - param7 != 14) { // p5 == p7 + 14
        return 0;
    }
    else if (param14 + 1 != param15) { // p15 == p14 + 1
        return 0;
    }
    else if (param9 % param8 != 40) { // p9 % p8 == 40
        return 0;
    }
    else if (param5 - param9 + param19 != 79) { // p5 == 79 + p9 - p19
        return 0;
    }
    else if (param7 - param14 != param20) { // p7 == p20 + p14
        return 0;
    }
    else if (param9 % param4 * 2 != param13) { // p9 % p4 * 2 = p13
        return 0;
    }
    else if (param13 % param6 != 20) { // p13 % p6 == 20
        return 0;
    }
    else if (param21 - 46 != param11 % param13) { // p21 - 46 == p11 % p13
        return 0;
    }
    else if (param7 % param6 != param10) { // p7 & p6 == p10
        return 0;
    }
    else if (param23 % param22 != 2) { // p23 % p22 == 2
        return 0;
    }
    else {
        i = 4;
        unsigned int v2 = 0, v3 = 0;

        do {
            v2 += (unsigned int)(*(i + 24));
            v3 ^= (unsigned int)(*(i + 24));
            ++i;
        } while (i <= 24);

        if (v2 != 1352) {
            return 0;
        }
        else {
            if (v3 != 44) {
                return 0;
            }

            decrypt();
            return 1;
        }
    }
}

int validateRange(unsigned int param0) {
    if ((((unsigned int)(param0 == 48)) | ((unsigned int)(param0 == 49)) | ((unsigned int)(param0 == 51)) | ((unsigned int)(param0 == 52)) | ((unsigned int)(param0 == 53)) | ((unsigned int)(param0 == 72)) | ((unsigned int)(param0 == 76)) | ((unsigned int)(param0 == 88)) | ((unsigned int)(param0 == 99)) | ((unsigned int)(param0 == 100)) | ((unsigned int)(param0 == 102)) | ((unsigned int)(param0 == 114)))) {
        return 1;
    }
    else {
        return 0;
    }
}

int decrypt() {
    do {
        *ptr0 = (unsigned char)(((unsigned int)(*(ptr0 + 6))) ^ ((unsigned int)(*ptr0)));
        ptr0 = (int*)(((char*)ptr0) + 1);
    } while (((unsigned char)(((int)ptr0) <= 24)));

    return 1337;
}
