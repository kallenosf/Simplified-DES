# Simplified-DES Implementation
A simplified version of DES (Data Encryption Standard) Algorithm. It is designed to demonstrate the encryption process using a minimal version of the DES algorithm.

## Overview
S-DES is used for educational purposes, as it demonstrates the process of key generation, substitution-permutation, and encryption. It operates on 8-bit plaintext and uses a 10-bit key for encryption.
This implementation takes:
- A plaintext (8 bits in binary format)
- A key (10 bits in binary format)

as command line arguments and outputs the corresponding ciphertext. If arguments are not given, two default values for plaintext and key are used.

## Installation
Clone the repository using the following command, and change directory:
```sh
git clone https://github.com/kallenosf/Simplified-DES.git
cd Simplified-DES
```
Build the binary using `make`:
```sh
make
```
## Usage
Run the compiled binary with the following format:
```sh
./sdes [plaintext] [key]
```
### Arguments
- [plaintext]: An 8-bit binary string representing the plaintext to be encrypted (e.g., 10011010)
- [key]: A 10-bit binary string representing the encryption key (e.g., 1110001110)
### Example
```sh
./sdes 10101010 1100110011
```
Output:
```
SIMPLIFIED DES
--------------
 plainText = 10101010
       key = 1100110011
cipherText = 11101001
```
