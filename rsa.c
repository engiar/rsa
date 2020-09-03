///////////////////////////////////////////////////////////////////
// Enrique Gil Arcas
// engiar@upv.es
// enriquegil1982@gmail.com
///////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


////////////////////////////////
// Auxiliar Methods
////////////////////////////////

int findGCD(int n1, int n2) {
    int i, gcd;
    for(i = 1; i <= n1 && i <= n2; ++i) {
        if(n1 % i == 0 && n2 % i == 0) gcd = i;
    }
    return gcd;
}

int powMod(int a, int b, int n) {
    long long x = 1, y = a;
    while (b > 0) {
        if (b % 2 == 1) x = (x * y) % n;
        y = (y * y) % n; 
        b /= 2;
    }
    return x % n;
}

  
////////////////////////////////
// Main Methods
////////////////////////////////

// Given two prime numbers 'p' and 'q' as inputs (with more or less the same amount of bits)
// The method calculates the variables 'n', 'e' and 'd'.
// The public key is (n,e) and the private key is (n,d).
void getKeys(int p, int q, int *n, int *e, int *d){ 
    int phin;
    *n = p * q;
    phin = (p - 1) * (q - 1);
    
    *e = 5;
    while(1){
        if (findGCD(phin, *e) == 1) break;
        *e = *e + 1;
    } 
    *d = *e + 1; 
    while(1){
        if ( ((*d * *e) % phin) == 1) break;
        *d = *d + 1;
    }  
}

// Given a message into the variable 'clear_data' and a public key formed by 'n' and 'e'
// The method returns the cyphed message into 'cyphed_data'  
void encrypt(char * clear_data, int * cyphed_data, int len,  int *n, int *e){ 
    char c;
    for(int i = 0; i < len; i++){
        cyphed_data[i] = powMod(clear_data[i], *e, *n);
    }
}

// Given a cyphed message into the variable 'cyphed_data' and a private key formed by the variables 'n' and 'd'
// The method returns the original message into 'clear_data' 
void decrypt(int * cyphed_data, char * clear_data, int len, int *n, int *d){  
    for(int i = 0; i < len; i++){
        clear_data[i] = (char) powMod(cyphed_data[i], *d, *n);
    }
}


////////////////////////////////
// Example Of Use
////////////////////////////////

int main(){
    int rsa_p = 17, rsa_q = 41; // Two prime numbers choosen by the user.
    int rsa_len; // Size of the message
    int rsa_d, rsa_e, rsa_n; // These will be calculated by the algorithm to form the 'public key' (n,e) and the 'private key' (n,d).
    char original_msg[100], uncyphed_msg[100]; // String to be cyphed
    int cyphed_msg[100]; // Array of ints which will contain the cyphed message

    strcpy(original_msg, "Hello world!");
    rsa_len = strlen(original_msg);    

    getKeys(rsa_p, rsa_q, &rsa_n, &rsa_e, &rsa_d);    
    encrypt(original_msg, cyphed_msg, rsa_len, &rsa_n, &rsa_e);
    decrypt(cyphed_msg, uncyphed_msg, rsa_len, &rsa_n, &rsa_d);

    printf("p: %d, q: %d, n: %d, e: %d,  d: %d\n", rsa_p, rsa_q, rsa_n, rsa_e, rsa_d);

    printf("Original message: ");
    for( int i = 0; i < rsa_len; i++){
        printf("%c=%03d  ", original_msg[i], original_msg[i]);
    }
    printf("\n");

    printf("Cyphed message:   ");
    for( int i = 0; i < rsa_len; i++){
        printf("  %03d  ", cyphed_msg[i]);
    }
    printf("\n");

    printf("Uncyphed message: ");
    for( int i = 0; i < rsa_len; i++){
        printf("%c=%03d  ", uncyphed_msg[i], uncyphed_msg[i]);
    }
    printf("\n");

    return 0;
}
