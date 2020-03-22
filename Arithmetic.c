#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

int main (int argc, char *argv[]) {
    
    FILE *pIn, *pOut;
    int len1, len2;
    len1 = len2 = 0;
    
    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();
    
    BigInteger C, D, E, F, G, H, I, J;
    
    pIn = fopen(argv[0], "r");
    pOut = fopen(argv[1], "w");

    
    if (pIn == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    if (pOut == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    
    fscanf(pIn, "%d", &len1);
    char *c1 = malloc((len1 + 2) * sizeof(char));
    fscanf(pIn, "%s", c1);
    
    fscanf(pIn, "%d", &len2);
    char *c2 = malloc((len2 + 2) * sizeof(char));
    fscanf(pIn, "%s", c2);

    A = stringToBigInteger(c1);
    B = stringToBigInteger(c2);
    
    printBigInteger(pOut, A);
    fprintf(pOut,"\n");

    printBigInteger(pOut, B);
    fprintf(pOut,"\n");
    
    C = sum(A, B);
    printBigInteger(pOut, C);
    fprintf(pOut,"\n");
    
    D = diff(A, B);
    printBigInteger(pOut, D);
    fprintf(pOut,"\n");
    
    E = diff(A, A);
    printBigInteger(pOut, E);
    fprintf(pOut,"\n");
    
    
//
//    freeBigInterger(&A);
//    freeBigInterger(&B);
//    freeBigInterger(&C);
//    freeBigInterger(&D);
//    freeBigInterger(&E);
//    freeBigInterger(&F);
//    freeBigInterger(&G);
//    freeBigInterger(&H);

    fclose(pIn);
    fclose(pOut);
}

