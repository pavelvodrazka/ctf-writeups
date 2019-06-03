#!/usr/bin/env python2

from Crypto.Cipher import AES
import base64

# the session cookie
session_cookie = 'u.P9Esvw1OEjw4xlJpDKMM5Rv4YFQmeigTfcfEwCgkT7NuU5vtwWbHFhcLPr5isrmQ7+FIndJifnGkBMxuqtBaiuyBKV2xRzVEDAY3DjX7RBL9UI/1CnH9CMyDQfolOxX2A2Qnr0yS9u1XGXf85qim8gOrYY9Z4SNVUMJNKXac5Sn4kFX/Gu/z8wXOQ45WZLtK5QQ5jk9ci+H7Sogb9UvC+r3mBUzZHR2KMtIXSQjh3U8jw9KxV/RGbXHgEHPZe0RiQDtlOgtzrJFrBCdUBjmMCKiQPF2VAfEstYiclbpz1W+sfvwpmYQohWyQvdW57Gh1jcG+xF5NHtc3VYFjKlKBCLZeR01b/ipDKj3hvw6pElxeX3VcbiPHwrdxR3y6DWCUHUffSbqr3WsFyPgGXpc7TLABvyZGfcFwf81Z9NSB+XZxbWhmSYCOfojxyMeRsV99iVknac96aEQILKn9HzcJmpNCyn75pUss5TO0KRwJqBgNC3QQqaCL9f9QzDWE6xD9nOPD2Rg0/oK1RRWthrngSzkA7IUkCAHpHWDAZNkK6oWAIdbzjJqEVUdOEDCkWUnt7kQy1uXDFqFg6MTf9OGI/XEPRW1oypfKzgQIVc3rY4g4QGmwQU92QY6DHRwgv/R3cP3uVoQRzCtQKzaY6TC3vJ/qz0rUTvTe/7obN0rVY3SiR/y68Bu+lQ==.9K7QrLGMo7nLkHV1dGMH+A==.TDC4F2T6wABJ5+Xu+2EdHw=='

# the crypto key
crypto_key = '\x74\x69\x6D\x65\x74\x6F\x01\x67\x75\x65\x73\x73\x03\x61\x03\x6C\x61\x73\x74\x07\x74\x69\x6D\x65'

# split the session cookie : <z|u>.<base64 cipher text>.<base64 mac>.<base64 nonce>
parts = session_cookie.split('.')

# decode the cookie parts from base64
ciphertext = base64.b64decode(bytes(parts[1]))
mac = base64.b64decode(bytes(parts[2]))
nonce = base64.b64decode(bytes(parts[3]))

# decrypt data
cipher = AES.new(crypto_key, AES.MODE_EAX, nonce)
data = cipher.decrypt_and_verify(ciphertext, mac)

print(str(data))
