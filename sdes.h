#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *initialPerm(char *plainText);
void *split(char *block, char *L0, char *R0);
char *expand(char *R);
char *feistelNetwork(char *block, char *key);
char *keySchedule(char *key, int round);
void *finalPerm(char *block);
