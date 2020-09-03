# rsa
RSA algorithm implementation for C. The main purpouse of this repo is to have a snippet of code able to encrypt and decrypt strings, that can be copy/pasted inside of other projects, for example, into an Arduino sketch. I used it to encrypt the data written into a SD plugged on a ESP32CAM. 

# Use

You will have three methods available:

* void getKeys(int p, int q, int *n, int *e, int *d): Given two prime numbers 'p' and 'q' as inputs (with more or less the same amount of bits) the method calculates the variables 'n', 'e' and 'd'. The public key is (n,e) and the private key is (n,d).
* void encrypt(char * clear_data, int * cyphed_data, int len,  int *n, int *e): Given a message into the variable 'clear_data' and a public key formed by 'n' and 'e' the method returns the cyphed message into 'cyphed_data'.
* void decrypt(int * cyphed_data, char * clear_data, int len, int *n, int *d):  Given a cyphed message into the variable 'cyphed_data' and a private key formed by the variables 'n' and 'd' the method returns the original message into 'clear_data'.

# Example

Expected output of the example:

```
p: 17, q: 41, n: 697, e: 7,  d: 183
Original message: H=072  e=101  l=108  l=108  o=111   =032  w=119  o=111  r=114  l=108  d=100  !=033  
Cyphed message:     064    645    048    048    019    501    221    019    296    048    365    203  
Uncyphed message: H=072  e=101  l=108  l=108  o=111   =032  w=119  o=111  r=114  l=108  d=100  !=033 
```