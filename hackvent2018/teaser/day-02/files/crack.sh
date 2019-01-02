#!/bin/bash

INPUT="Final_easy.zip"
ARCHIVE="z.zip"

7z e -aoa "$INPUT" > /dev/null

while [[ $(7z l -slt -- "$ARCHIVE" | grep -c "Encrypted = +") -eq 1 ]]; do
    PASSWORD=$(fcrackzip -u -c '1aA:,. ' -l 1-1 "$ARCHIVE" | grep "PASSWORD FOUND" | cut -c 27)
    if [[ -z "$PASSWORD" ]]; then
        PASSWORD="-"
    fi

    7z e -aoa -p"$PASSWORD" "$ARCHIVE" > /dev/null

    echo -n "$PASSWORD"
done
