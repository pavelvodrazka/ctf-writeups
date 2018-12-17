# Day 17: Faster Key Exchange

You were somehow able to intercept Santa's traffic.

But it's encrypted. Fortunately, you also intercepted the key exchange and figured out what software he was using.....

> a = 17577019968135092891915317246036083578063875217491307011102321322815719709605741738459191569497548099944025771002530369133716621942963853230082186943938164591230020725702755002287589522851172217336150522367152517270250629688405924844750026155547199020780202996200555426652190631837288299999083335649923708175859594750237448640513280683859296367607523542293538555215282798100455110266565881599829107971869244773384413618546118850868579583095489023778055976570366853411496753062216229293710557686212314300848121614558806328788578096144576605248971916454783615989429937555579437307320472405217413938048149254574677430624  
> b = 15228628318558071728245462802366236848375416102820239825350329247148900182647243994904519787528142824353837070194785550898962097219309344881183948914850354340893035399529028331238911753358245357848436203268982345430735846016484221944423499956958406189854969330305125479065873712331269870135028162018087451460656203085824963123310757985362748654204595136594184636862693563510767025800252822776154986386637346156842972134635578534633722315375292616298410141343725683471387328655106920310236007034951004329720717533666052625540760911360823548318810161367913281234234193760867208897459774865037319252137821553407707977377  
> message = jqMYIn4fzSqzIXArwJm/kPitNhf4lwhL0yPRKpF+NYXyPmhoEwNG/k2L5vCZqFWNPvTzisnu93/8uK/PZnnCGg==  

[FasterKeyExchange.py](files/FasterKeyExchange.py)

### Solution

The idea behind the Faster Key Exchange is really simple. It relies on given large prime number `p` and base number `g`, a randomly generated integer value `x` kept as a secret and simple modular arithmetic.

```python
class FasterKeyExchange():
    def __init__(self, g, p):
        self.g = g
        self.p = p
        self.x = self.get_random_x()

    def get_random_x(self):
        return secrets.SystemRandom().randint(g, p-2)
    
    def calculate_y(self):
        return (self.g * self.x) % self.p

    def calculate_key(self, y):
        return (y * self.x) % self.p
```

The exchange protocol consists of these steps:

1. Both sides randomly generate its own secret value `x` from range `<g, p-2>`
2. Server's `y` value is calculated as `y_server ≡ g * x_server (mod p)` and send to the client
3. Client's `y` value is calculated as `y_client ≡ g * x_client (mod p)` and send to the server
4. Both sides multiply received `y` value of the other side by its own secret value `x`
    1. Client gets value `s ≡ y_server * x_client (mod p) ≡ g * x_server * x_client (mod p)`
    2. Server gets value `s ≡ y_client * x_server (mod p) ≡ g * x_client * x_server (mod p)` 
5. Since both values of `s` from the previous step are equal to each other, server and client now shares the same secret value of `s`

Such key exchange implementation is however pretty weak. The secret values `x` can be calculated very easily from those intercepted exchanged values.

The only thing needed is to calculate a modular inverse `g_inv` of publicly known base number `g` such that:

```
g_inv * g ≡ 1 (mod p)
```

Here is a demonstration of how to calculate server's `x` value from the intercepted value of `y_server`.

```
y_server ≡ g * x_server (mod p)
g_inv * y_server ≡ g_inv * g * x_server (mod p)
g_inv * y_server ≡ x_server (mod p)
``` 

Since we also intercepted value of `y_client` we can calculate value of shared secret `s` by applying calculation from the 4th step of key exchange.

```
secret = (y_client * x_server) % p
```

Here is the part of [Python program](../../src/main/python/hackvent2018/Day17.py) I wrote which calculates AES decryption key and initial vector from the shared secret value.

```python
# publicly known values
g = 3
p = 0x00e1a540d72bb311db26ea6e58b7dc207cf55d0c3a90d7c1f74e7fcb67c7af097d99c73e002c9266e70cbdf735ebd864ea279a0a4d41dd6537837bfc07d84943a376d163ec20a51dd6073dbfc34cbdce9d88ad22a9bb72f5bb143b5c9e531ab100590b9f97d1e9c7a3dfe7961fd6e86078ad43918b47816925803db47862e5f69c90078c6dc287fc6cf7742a9f1717d828a610fe469c92f34783351b21ac1ec988eae0e16ff4ef89c1a19ccd7e3b5cb0c14e0424dfde338789923013aeb7791e19ba378cb2e0e0b318f46865d438ac53999f69f0ae8045d2ff40821b5fdcb0a3b9942f29a0cd8e55febd0ee9006d936d51335a2e63b6affbed6175e1228a53d6a9

# intercepted values
y_server = 17577019968135092891915317246036083578063875217491307011102321322815719709605741738459191569497548099944025771002530369133716621942963853230082186943938164591230020725702755002287589522851172217336150522367152517270250629688405924844750026155547199020780202996200555426652190631837288299999083335649923708175859594750237448640513280683859296367607523542293538555215282798100455110266565881599829107971869244773384413618546118850868579583095489023778055976570366853411496753062216229293710557686212314300848121614558806328788578096144576605248971916454783615989429937555579437307320472405217413938048149254574677430624
y_client = 15228628318558071728245462802366236848375416102820239825350329247148900182647243994904519787528142824353837070194785550898962097219309344881183948914850354340893035399529028331238911753358245357848436203268982345430735846016484221944423499956958406189854969330305125479065873712331269870135028162018087451460656203085824963123310757985362748654204595136594184636862693563510767025800252822776154986386637346156842972134635578534633722315375292616298410141343725683471387328655106920310236007034951004329720717533666052625540760911360823548318810161367913281234234193760867208897459774865037319252137821553407707977377
message = "jqMYIn4fzSqzIXArwJm/kPitNhf4lwhL0yPRKpF+NYXyPmhoEwNG/k2L5vCZqFWNPvTzisnu93/8uK/PZnnCGg=="

# g_inv * g ≡ 1 (mod p)
g_inv = gmpy.invert(g, p)

# y_server ≡ g * x_server (mod p)
# g_inv * y_server ≡ g_inv * g * x_server (mod p)
# g_inv * y_server ≡ x_server (mod p)
x_server = (g_inv * y_server) % p

# secret = (y_client * x_server) % p
secret = (y_client * x_server) % p

# calculate decryption key & initial vector
key = str(secret)
iv = key[0:16]
```

Now I had to implement AES decryption function.

```python
def decrypt(msg, key, iv):
    key_bytes = bytes(hashlib.md5(bytes(key, "utf-8")).hexdigest(), "utf-8")
    iv_bytes = bytes(iv, "utf-8")
    cipher = AES.new(key_bytes, AES.MODE_CBC, iv_bytes)
    return unpad(cipher.decrypt(msg), AES.block_size).decode("utf-8")
```

The last missing piece was this code which decodes the intercepted Base64 encoded message and decrypts it using calculated key and initial vector.

```python
# decrypt the flag
plaintext = decrypt(b64decode(message), key, iv)
print(plaintext)
```

Here is the decrypted message.

```
Congrats! Now take the flag: HV18-DfHe-KE1s-w44y-b3tt-3r!!
```
