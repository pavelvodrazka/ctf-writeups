# Day -02: Final.zip

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

I extracted a ZIP file named [Final_easy.zip](files/Final_easy.zip) from the archive.

```
$ unrar e _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar Final_easy.zip
UNRAR 5.61 beta 1 freeware      Copyright (c) 1993-2018 Alexander Roshal

Extracting from _ZOoxjUSe1OVB7OPoVrsX.pdf.extracted/39A25.rar

Extracting  Final_easy.zip                                            OK 
All OK
```

The ZIP archive was password protected. After a few rounds of manual password cracking with `fcrackzip` I realized that it was a [Matryoshka](https://en.wikipedia.org/wiki/Matryoshka_doll) archive with single character only passwords.

I expected the passwords-generated message to be quite long so I wrote this Bash [script](files/crack.sh) to crack all the passwords and print the message.

```bash
#!/bin/bash

ARCHIVE="z.zip"

if [[ $# -eq 0 ]]; then
    echo "No ZIP archive provided"
    exit 1
fi

if [[ "$1" != "$ARCHIVE" ]]; then
    cp "$1" "$ARCHIVE"
fi

while [[ $(7z l -slt -- "$ARCHIVE" | grep -c "Encrypted = +") -eq 1 ]]; do
    PASSWORD=$(fcrackzip -u -c '1aA:,. ' -l 1-1 "$ARCHIVE" | grep "PASSWORD FOUND" | cut -c 27)
    if [[ -z "$PASSWORD" ]]; then
        PASSWORD="-"
    fi

    7z e -aoa -p"$PASSWORD" "$ARCHIVE" > /dev/null

    echo -n "$PASSWORD"
done
``` 

This was the message it printed:

> Far shed each high read are men over day. Afraid we praise lively he suffer family estate is. Ample order up in of in ready. Timed blind had now those ought set often which. Or snug dull he show more true wish. No at many deny away miss evil. On in so indeed spirit an mother. Amounted old strictly but marianne admitted. People former is remove remain as. Sudden looked elinor off gay estate nor silent. Son read such next see the rest two. Was use extent old entire sussex. Your nugget ist **HV18-WO3y-7FLk-ExvN-kDue-28JF**. All men drew its post knew. Of talking of calling however civilly wishing resolve. Eat imagine you chiefly few end ferrars compass. Be visitor females am ferrars inquiry. Latter law remark two lively thrown. Spot set they know rest its. Raptures law diverted believed jennings consider children the see. Had invited beloved carried the colonel. Occasional principles discretion it as he unpleasing boisterous. She bed sing dear now son half. Congratulations, you have reached the last level.

Flag: `HV18-WO3y-7FLk-ExvN-kDue-28JF`
