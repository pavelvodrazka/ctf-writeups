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
