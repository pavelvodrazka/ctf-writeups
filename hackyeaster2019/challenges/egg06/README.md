# 06 - Dots

Uncover the dots' secret!

Then enter the password in the *egg-o-matic* below. **Uppercase only**, and **no spaces**!

![dots1.png](files/dots1.png "dots1.png")

![dots2.png](files/dots2.png "dots2.png")

### Solution

Dots were the mask for reading letters from the corresponding grid positions, but it was not complete. So the first step was to complete the mask in the lower-right quadrant. After inspecting positions of dots I noticed that none of them shared the same position inside the quadrant. Therefore I supposed that the missing dots have the same property and put dots on the positions which were left unoccupied. That gave me this mask.

![mask.png](files/mask.png "mask.png")

Then I applied all four possible rotation of the mask in anti-clockwise order and read letters row by row in each rotation.

![password.png](files/password.png "password.png")

That gave me:

```
HELLO BUCK THE PASSWORD IS WHITE CHOCOLATE
```

### Egg

![egg.png](files/egg.png "egg.png")
