
#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[]){
   
   
    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();
    BigInteger C = newBigInteger();
    BigInteger D = NULL;



    A = stringToBigInteger("222455509");
    B = stringToBigInteger("-11245555");
    printf("A: \n");
    printBigInteger(stdout, A);
    printf("\n");
    printf("B: \n");
    printBigInteger(stdout, B);
    printf("\n");

    add(C, A, B);
    printf("B: \n");
    printBigInteger(stdout, B);
    printf("\n");
    
    A = stringToBigInteger("+112345");
    B = stringToBigInteger("+99875554");

    D = stringToBigInteger("+3345632");
    add(C, A, B);


    B = stringToBigInteger("-2222222");
    add(C, A, B);



    B = stringToBigInteger("-000100");
    add(C, A, B);


    B = stringToBigInteger("-112122223333");
    add(C, A, B);


    A = stringToBigInteger("-221211110000");
    D = stringToBigInteger("-333333333333");
    add(C, A,B);

    printf("A: \n");
    printBigInteger(stdout, A);
    printf("\n");
    printf("B: \n");
    printBigInteger(stdout, B);
    printf("\n");
    printf("C: \n");
    printBigInteger(stdout, C);
    printf("\n");
    printf("D: \n");
    printBigInteger(stdout, D);
    printf("\n");


    B = stringToBigInteger("-112122223333");



    printf("A: \n");
    printBigInteger(stdout, A);
    printf("\n");
    printf("B: \n");
    printBigInteger(stdout, B);
    printf("\n");

    printf("D: \n");
    printBigInteger(stdout, D);
    printf("\n");

    add(C,A,B);
    printBigInteger(stdout, C);

    freeBigInteger(&A);
    freeBigInteger(&B);
}
