/** @file sdes.c
 *  @brief A simple programm that takes as input an 8-bit binary plainText and
 *  outputs an 8-bit encrypted cipherText, using simplified DES.
 *
 *  @author Frixos Kallenos
 *  @bug No known bugs. 
 */
#include "sdes.h"

int main(int argc, char *argv[]){

	char *plainText = malloc(8);
	char *key = malloc(10);

	if (argc == 1){
		strcpy(plainText, "01010001");
		strcpy(key, "0101001100");
	}
	else{
		strcpy(plainText, argv[1]);
		strcpy(key, argv[2]);
	}
	printf("SIMPLIFIED DES\n");
	printf("--------------\n");
	printf(" plainText = %s\n", plainText);
	printf("       key = %s\n", key);

	char *ip;
	ip = initialPerm(plainText);

	char *cipherText = feistelNetwork(ip, key);

	printf("cipherText = %s\n", cipherText);

}

char *initialPerm(char *plainText){
	char *ip = malloc(8);
	int ip_table[8] = {1,5,2,0,3,7,4,6};
	
	int i;
	for (i = 0; i < 8; i++){
		ip[i] = plainText[ip_table[i]];
	}

	return ip;
}

void *finalPerm(char *block){
	char *temp = malloc(8);
	strcpy(temp, block);
	int perm_table[8] = {3,0,2,4,6,1,7,5};
	
	int i;
	for (i = 0; i < 8; i++){
		block[i] = temp[perm_table[i]];
	}
	free(temp);
	return 0;
}

void *split(char *block, char *L0, char *R0){
	int i;
	for (i = 0; i < 4; i++){
		L0[i] = block[i];
		R0[i] = block[4 + i];
	}
	return 0;
}

char *keySchedule(char *key, int round){
	int i;
	char *k1 = malloc(10);
	char *k2 = malloc(10);
	char *temp = malloc(10);
	char *subKey = malloc(8);

	int pc_1[10] = {2,4,1,6,3,9,0,8,7,5};
	int pc_2[8] = {5,2,6,3,7,4,9,8};
	int ls_1[10] = {1,2,3,4,0,6,7,8,9,5};
	int ls_2[10] = {2,3,4,0,1,7,8,9,5,6};
	for (i = 0; i < 10; i++)
		k1[i] = key[pc_1[i]];
	strcpy(temp, k1);
	for (i = 0; i < 10; i++)
		k1[i] = temp[ls_1[i]];
	for (i = 0; i < 8; i++)
		subKey[i] = k1[pc_2[i]];
	if (round == 2){
		for (i = 0; i < 10; i++)
			k2[i] = k1[ls_2[i]];
		for (i = 0; i < 8; i++)
			subKey[i] = k2[pc_2[i]];
	}
	free(k1);
	free(k2);
	free(temp);
	return subKey;
}

char *expand(char *R){
	char *expansion = malloc(8);
	int exp_table[8] = {3,0,1,2,1,2,3,0};

	int i;
	for (i = 0; i < 8; i ++)
		expansion[i] = R[exp_table[i]];
	return expansion;
}

int binToDecimal(char a, char b){
	int dec;
	if (a == '1')
		dec = 2;
	else
		dec = 0;
	
	if (b == '1')
		dec++;

	return dec;
}

void decToBinary(char sbout[], int a, int b){
	switch (a){
		case 0: sbout[0] = '0'; sbout[1] = '0'; break;
		case 1: sbout[0] = '0'; sbout[1] = '1'; break;
		case 2: sbout[0] = '1'; sbout[1] = '0'; break;
		case 3: sbout[0] = '1'; sbout[1] = '1'; break;
	}
	switch (b){
		case 0: sbout[2] = '0'; sbout[3] = '0'; break;
		case 1: sbout[2] = '0'; sbout[3] = '1'; break;
		case 2: sbout[2] = '1'; sbout[3] = '0'; break;
		case 3: sbout[2] = '1'; sbout[3] = '1'; break;
	}
}

char *feistelNetwork(char *block, char *key){
	char *cipherText = malloc(8);
	int i;
	char *L0 = malloc(4);
	char *R0 = malloc(4);
	split(block, L0, R0);

	char *expansion;
	expansion = expand(R0);
	
	char *subKey1 = keySchedule(key, 1);

	//Expanded R0 XOR subkey1
	char *sboxInput = malloc(9);
	for (i = 0; i < 8; i++)
		if (expansion[i] == subKey1[i])
			sboxInput[i] = '0';
		else
			sboxInput[i] = '1';
	sboxInput[8] = '\0';

	int i0, j0, i1, j1;
	int sbox0[4][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}}; 
	int sbox1[4][4] = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}}; 
	
	//find indecies of sbox0 and sbox1
	i0 = binToDecimal(sboxInput[0], sboxInput[3]);
	j0 = binToDecimal(sboxInput[1], sboxInput[2]);
	i1 = binToDecimal(sboxInput[4], sboxInput[7]);
	j1 = binToDecimal(sboxInput[5], sboxInput[6]);

	//calculate Sbox output
	char sboxOutput[4];
	decToBinary(sboxOutput, sbox0[i0][j0], sbox1[i1][j1]);

	char p4[4];
	p4[0] = sboxOutput[1];
	p4[1] = sboxOutput[3];
	p4[2] = sboxOutput[2];
	p4[3] = sboxOutput[0];

	char *L1 = R0;
	char *R1 = malloc(4);

	//R1 = p4 XOR L0
	for (i = 0; i < 4; i++)
		if (p4[i] == L0[i])
			R1[i] = '0';
		else	
			R1[i] = '1';

	free(expansion);
	expansion = expand(R1);

	char *subKey2 = keySchedule(key, 2);

	//Expanded R1 XOR subkey2
	for (i = 0; i < 8; i++)
		if (expansion[i] == subKey2[i])
			sboxInput[i] = '0';
		else
			sboxInput[i] = '1';
	sboxInput[8] = '\0';

	//find indecies of sbox0 and sbox1
	i0 = binToDecimal(sboxInput[0], sboxInput[3]);
	j0 = binToDecimal(sboxInput[1], sboxInput[2]);
	i1 = binToDecimal(sboxInput[4], sboxInput[7]);
	j1 = binToDecimal(sboxInput[5], sboxInput[6]);
	
	//calculate Sbox output
	decToBinary(sboxOutput, sbox0[i0][j0], sbox1[i1][j1]);

	p4[0] = sboxOutput[1];
	p4[1] = sboxOutput[3];
	p4[2] = sboxOutput[2];
	p4[3] = sboxOutput[0];

	//p4 XOR L1
	for (i = 0; i < 4; i++)
		if (p4[i] == L1[i])
			cipherText[i] = '0';
		else
			cipherText[i] = '1';

	strcat(cipherText, R1);
	finalPerm(cipherText);

	free(L0);
	free(R0);

	return cipherText;
}
