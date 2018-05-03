# 16 - git cloak --hard

This one requires your best Git-Fu! Find the hidden egg in the repository.

[repo.zip](files/repo.zip)

### Solution

I unzipped the repository.

```bash
$ unzip -d repo repo.zip
```

And then I took a look at the log.

```bash
$ cd repo
git log --reflog --graph --oneline --all
* b9e860f (HEAD -> master) even more funny images added
| * 9a29769 (branch) branch created
|/  
* 3839c14 more funny images added
| * 9d7c9b5 added one more image
| * b9820d5 temp branch created
|/  
* 228b603 created the funny git meme repo
```

The temp branch looked promising...

```bash
git checkout 9d7c9b5 .
```

...but I got trolled once again :)

![nope.png](files/nope.png "nope.png")

So I decided to try to check for dangling blobs.

```bash
$ git fsck --lost-found
Checking object directories: 100% (256/256), done.
dangling blob dbab6618f6dc00a18b4195fb1bec5353c51b256f
```

Gotcha!

```bash
$ git show dbab6618f6dc00a18b4195fb1bec5353c51b256f > egg.png
```

### Egg

![egg.png](files/egg.png "egg.png")