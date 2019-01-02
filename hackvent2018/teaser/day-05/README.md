# Day -05: Teaser.pls

I used binwalk on the [PDF](../day-10/files/ZOoxjUSe1OVB7OPoVrsX.pdf) file and found this interesting RAR archive in it.

```
$ binwalk -y rar -e ZOoxjUSe1OVB7OPoVrsX.pdf 
DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
236069        0x39A25         RAR archive data, version 4.x, first volume type: MAIN_HEAD

$ unrar l _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar 
UNRAR 5.61 beta 1 freeware      Copyright (c) 1993-2018 Alexander Roshal

Archive: _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar
Details: RAR 4

 Attributes      Size     Date    Time   Name
----------- ---------  ---------- -----  ----
    ..A....    369852  2018-12-01 21:44  Final_easy.zip
    ..A....    526371  2018-12-03 02:07  old_school.jpg
    ..A....      1438  2018-11-28 08:45  QR3C.png
    ..A....       564  2018-12-03 01:58  Santa.txt
    ..A....       739  2018-12-02 23:31  teaser.pls
----------- ---------  ---------- -----  ----
               898964                    5
```

I extracted a file named [teaser.pls](files/teaser.pls) from the archive.

```
$ unrar e _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar teaser.pls
UNRAR 5.61 beta 1 freeware      Copyright (c) 1993-2018 Alexander Roshal

Extracting from _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar

Extracting  teaser.pls                                                OK 
All OK
```

This was the content of the pls file.

```oracle
CREATE OR REPLACE FUNCTION checkHV18teaser wrapped 
a000000
b2
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
abcd
8
37f 22f
9bGsDUl+WXOiRvCg6f+CmODMp3UwgwIJ+txqfC9Dgz+VaPwOTWaoKj5jW2QUCQapzabE52vy
50h+W7xBf1NE2/Fa93pBwUJtOxLvz1WIU75VaGjqH5M6oL4/aHovVUteU3Arw0eLvVRDEvbd
0mLqbyd4kEtMnI76J3vuLaHC1mkYuwEN6bdmd3GQPBtHV4fWHr5OM5B81yX+kw0560LKdDx8
mVHJvc7y7vShjsCpFgEUd6sfN3ZbOkjjbg+AJSGuIjZzvT7vkQwM5wcQL73C6+BCiaaEG2ja
r+3zqCSk6QzcKvIwuBwXf9UHGL4YS47JO3EOmIPOy8VQYfY1M9g6UeieqOftVm/Pr8smR11r
UWM8kk1WTmMvY13s1Klpr7tFnzwjmnSnTP9Exz/dV5+cU3mlgyjqkAIsWnGqDGKMfVahOHSc
Bzalmd+HDxxBF39ymrsGHfBUv0gAPtnYVCVWiG0Q9ij5DbBffRrsx4uOYuAqJ4KwT5vNpKon
MSMAM3ZsIFVQgfnY/sfkB+jfGEuldGYiui7zvIMSHVDfPEE=

/
```

It turned out to be a wrapped Oracle PL/SQL function. I [unwrapped](files/teaser.unwrapped) it using this [online tool](https://www.codecrete.net/UnwrapIt/).

```oracle
FUNCTION checkHV18teaser(FLAG VARCHAR2) RETURN NUMBER IS
    A VARCHAR2(4);
    B NUMBER(10);
    C NUMBER(10);
    H VARCHAR(40);
BEGIN
    A := SUBSTR(FLAG,1,4);
    IF NOT (A = 'HV18') THEN
	RETURN 0;
    END IF;
    
    B := TO_NUMBER(SUBSTR(FLAG,6,2));
    C := TO_NUMBER(SUBSTR(FLAG,8,2));
    IF NOT (((B * C) = 6497) AND (B < C)) THEN
	RETURN 0;
    END IF;
    
    A := SUBSTR(FLAG,11,4);
    SELECT STANDARD_HASH(A, 'MD5') INTO H FROM DUAL;
    IF NOT (H = 'CF945B5A36D1D3E68FFF78829CC8DBF6') THEN	
    RETURN 0;
    END IF;
    
    IF NOT ((UTL_RAW.CAST_TO_VARCHAR2(UTL_RAW.BIT_XOR (UTL_RAW.CAST_TO_RAW(SUBSTR(FLAG,16,4)), UTL_RAW.CAST_TO_RAW(SUBSTR(FLAG,21,4)))) = 'zvru') AND (TO_NUMBER(SUBSTR(FLAG,21,4)) = SQRT(8814961))) THEN
	RETURN 0;
    END IF;
    
    IF NOT ( UTL_RAW.CAST_TO_VARCHAR2(UTL_ENCODE.BASE64_ENCODE(UTL_RAW.CAST_TO_RAW(SUBSTR(FLAG,26,4)))) = 'RjBtMA==') THEN
	RETURN 0;
    END IF;
    
    DBMS_OUTPUT.PUT_LINE(A);
    RETURN 1;
END;
```

This function checked if given flag was the valid one. I had to revert it block by block to get the flag.

1. Known prefix → `HV18`
2. Factorize 6497 → `7389`
3. MD5 [reverse](https://md5.gromweb.com/?md5=CF945B5A36D1D3E68FFF78829CC8DBF6) → `H0b0`
4. XOR → `HODL`
5. Square root → `2969`
6. Base64 decode → `F0m0`

Flag: `HV18-7389-H0b0-HODL-2969-F0m0`
