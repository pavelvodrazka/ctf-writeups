# Day 03: Strange Logcat Entry

*Lost in messages*

I found those strange entries in my Android logcat, but I don't know what it's all about... I just want to read my messages!

[Get the logcat](files/logcat.txt "logcat.txt")

### Solution

When we try to find the word *message* in the logcat file we get an interesting debug line.

```bash
$ grep -i message logcat.txt
11-13 20:40:13.418  1237  1237 I System  : 	at android.view.ViewRootImpl$ViewRootHandler.handleMessage(ViewRootImpl.java:2818)
11-13 20:40:13.418  1237  1237 I System  : 	at android.os.Handler.dispatchMessage(Handler.java:99)
11-13 20:40:13.542   137   137 I DEBUG   : 	      FAILED TO SEND RAW PDU MESSAGE
```

When we follow that PID we get these lines. 

```bash
$ grep "\s137\s" logcat.txt 
11-13 20:40:13.542   137   137 I DEBUG	 : 	      FAILED TO SEND RAW PDU MESSAGE
11-13 20:40:24.044   137   137   DEBUG   : I 07914400000000F001000B913173317331F300003AC7F79B0C52BEC52190F37D07D1C3EB32888E2E838CECF05907425A63B7161D1D9BB7D2F337BB459E8FD12D188CDD6E85CFE931
```

Now we have SMS PDU (Packet Data Unit) encoded message. To decode it we can use [this online tool](https://www.diafaan.com/sms-tutorials/gsm-modem-tutorial/online-sms-pdu-decoder/ "Online SMS PDU Decoder"). Decoded message looks like this.

```
To: +13371337133
Message: Good Job! Now take the Flag: HV17-th1s-isol-dsch-00lm-agic
```