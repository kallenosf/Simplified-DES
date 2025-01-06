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
## How it works
The program implements the following diagram:
![S-DES workflow](https://raw.githubusercontent.com/kallenosf/Simplified-DES/refs/heads/main/sdes.png)
These are the steps:
1. Key Generation:
   - Derives two subkeys (K1 and K2) from the 10-bit input key using permutation and shifting operations.
2. Initial Permutation (IP):
   - Rearranges the 8-bit plaintext input into a predefined order.
3. Rounds:
   - Executes two rounds of encryption using the Feistel structure and the subkeys K1 and K2.
4. Final Permutation (Inverse IP):
   - Applies the inverse of the initial permutation to produce the final ciphertext.
  
## Cleaning Up
To remove the compiled binary and other generated files, run:
```sh
make clean
```
