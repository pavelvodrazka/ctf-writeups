#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 STATE"
    exit 1
fi

STATE="$@"

openssl req -nodes -new -newkey rsa:2048 -sha256 -keyout /tmp/hv17-d24.key -out /tmp/hv17-d24.csr -subj "/C=GB/ST=$STATE/L=London/O=Hackvent/OU=1337/CN=1337.hackvent.com" &>/dev/null
[ $? -eq 0 ] || exit $?

CSR="$(cat /tmp/hv17-d24.csr)"
curl -s \
    -X POST "http://challenges.hackvent.hacking-lab.com:1088/php/api.php?function=csr&argument=&key=E7g24fPcZgL5dg78" \
    -H 'content-type: application/x-www-form-urlencoded' \
    --data-urlencode "csr=$CSR" | sed 's/<br>/\n/g' > /tmp/hv17-d24.cert

rm -f /tmp/hv17-d24.key
rm -f /tmp/hv17-d24.cert
rm -f /tmp/hv17-d24.csr
