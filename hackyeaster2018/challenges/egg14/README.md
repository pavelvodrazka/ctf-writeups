# 14 - Same same...

...but different!

Upload the right files and make the server return an Easter egg!

```
http://whale.hacking-lab.com:4444
```

[upload.php.txt](files/upload.php.txt)

### Description

There was a simple PHP page hosted on port 4444 which allowed you to submit two files.

### Solution

I looked at the provided source code of that page.

```php
<?php
require __DIR__ . "/vendor/autoload.php"; // QR decoder library from https://github.com/khanamiryan/php-qrcode-detector-decoder

try {
    $qrcode1 = new QrReader($_FILES["file1"]["tmp_name"]);
    $answer1 = $qrcode1->text();
} catch(Exception $e) {
    exit("Error while reading the first QR.");
}

try {
    $qrcode2 = new QrReader($_FILES["file2"]["tmp_name"]);
    $answer2 = $qrcode2->text(); 
} catch(Exception $e) {
    exit("Error while reading the second QR.");
}

if(($answer1 == "Hackvent" && $answer2 == "Hacky Easter" or $answer1 == "Hacky Easter" && $answer2 == "Hackvent") && sha1_file($_FILES["file1"]["tmp_name"]) == sha1_file($_FILES["file2"]["tmp_name"])) {
    [SURPRISE]
}
else {
    echo ":-(";
}
?>
``` 

I lost lot of time trying to exploit that PHP code but it was an dead end. Later I remembered the [SHAttered collision attack](https://shattered.it/) which allow you to craft two colliding PDF files and obtain a SHA-1 digital signature on the first PDF file which can also be abused as a valid signature on the second PDF file. It looked very promising since the QR library also accepted PDF files as an input. 

Then I prepared two QR code images: [hackvent.jpeg](files/hackvent.jpeg) and [hackyeaster.jpeg](files/hackyeaster.jpeg). I uploaded them to this [online service](http://alf.nu/SHA1) which generated colliding PDFs for me: [hackvent.pdf](files/hackvent.pdf) and [hackyeaster.pdf](files/hackyeaster.pdf). It worked like a charm!

```bash
$ sha1sum hackvent.pdf hackyeaster.pdf 
80f993aeaed12859ff00f6438425f14462269e29  hackvent.pdf
80f993aeaed12859ff00f6438425f14462269e29  hackyeaster.pdf
```

I submitted those files to the PHP page and got the egg.

### Egg

![egg.png](files/egg.png "egg.png")