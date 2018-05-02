# 15 - Manila greetings

Randy Waterhouse receives a package from his friend Enoch Root containing a deck of cards and a letter:

>Dear Randy,
>
>even though our stay in Manila was not very pleasant, I fondly think of our discussions there:  
>
>```
>GTIFL RVLEJ TAVEY ULDJO KCCOK P  
>```
>
>Wishing you happy Easter
>
>Enoch

Decrypt the message and enter the password in the Egg-o-Matic below. Uppercase only!

[deck](files/deck)

### Solution

Randy Waterhouse and Enoch Root are fictional characters from [Cryptonomicon](https://en.wikipedia.org/wiki/Cryptonomicon), a novel by American author Neal Stephenson. Root is portrayed as having a passionate belief that cryptography is important for maintaining freedom. 

Stephenson included a precise description of the [Solitaire (or Pontifex) cipher](http://jnicholl.org/Cryptanalysis/Ciphers/Solitaire.php) in the book. A cryptographic algorithm developed by Bruce Schneier for use with a deck of playing cards, as part of the plot.

I found a [Go implementation](https://github.com/danmux/pontifex) of this cipher on GitHub but it used a slightly different format of a cards deck. I had to convert given deck to the required format first. I wrote a simple [script](../../src/main/scala/hackyeaster2018/Egg15.scala) which generated this [converted deck](files/deck-converted) for me.

Then I had to generate my [keystream](files/keystream) from the deck.

```bash
$ go run main.go -op key -k keystream -i deck-converted
```

The final step was to store the encrypted message to a file and decrypt it using the keystream.

```bash
$ echo "GTIFL RVLEJ TAVEY ULDJO KCCOK P" > ciphertext
$ go run main.go -op dec -k keystream -i ciphertext -o /dev/stdout
THEPASSWORDISCRYPTONOMICONWE@X
```

The plaintext had to be trimmed to the size of the ciphered message which gave me this message.

```
THEPASSWORDISCRYPTONOMICON
```

### Egg

![egg.png](files/egg.png "egg.png")