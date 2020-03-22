/*
 Ahmad Hawamdah
 ahawamda
 pa3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BigInteger.h"
#include "List.h"
#define POWER 9
#define BASE 1000000000

typedef struct BigIntegerObj { //to rename the struct as node
    List L;
    int sign;

} BigIntegerObj;



BigInteger newBigInteger() {
    
    BigInteger B;
    B = malloc(sizeof(BigIntegerObj));
    B->L = newList();
    B->sign = 0;
    
    return (B);
}



int sign(BigInteger N) {
    return(N->sign);
}


// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B) {

      List L1 = A->L;
      List L2 = B->L;
    
    if (length(L1) < 0 || length(L2) < 0) {
        printf("Compare Error: Length does not exist!");
        exit(1);
    }

    if (A->sign > B->sign) {
       return 1;
    }
    if (A->sign < B->sign) {
       return -1;
    }
    
    if (A->sign == B->sign) {
        if (A->sign > 0 && B->sign > 0) {
            if (length(L1) > length(L2)) {
                return 1;
            }
            if (length(L1) < length(L2)) {
                return -1;
            }
          if (length(L1) == length(L2)) {
              moveFront(L1);
              moveFront(L2);
              long arrow1 = get(L1);
              long arrow2 = get(L2);
              for (int i = 0; i < length(L1); i++) {
                    arrow1 = get(L1);
                    arrow2 = get(L2);
                    if (arrow1 == arrow2) {
                        moveNext(L1);
                        moveNext(L2);
                    }
                    if (arrow1 > arrow2) {
                        return 1;
                    }
                    if (arrow1 < arrow2) {
                        return -1;
                    }
                }
            }
        }
        
        if (A->sign < 0 && B->sign < 0) {
            if (length(L1) < length(L2)) {
                return 1;
            }
            if (length(L1) > length(L2)) {
                return -1;
            }
            if (length(L1) == length(L2)) {
                moveFront(L1);
                moveFront(L2);
                long arrow1 = get(L1);
                long arrow2 = get(L2);
                for (int i = 0; i < length(L1); i++) {
                   arrow1 = get(L1);
                   arrow2 = get(L2);
                   if (arrow1 == arrow2) {
                       moveNext(L1);
                       moveNext(L2);
                   }
                   if (arrow1 < arrow2) {
                       return 1;
                   }
                   if (arrow1 > arrow2) {
                       return -1;
                   }
               }
           }
       }
        return 0;
    }
    return 0;
}


void negateElement(List L) {
    moveFront(L);
     while (index(L) > - 1) {
        set(L, -get(L));
        moveNext(L);
    }
}



void normalized(BigInteger N) {

    if(N == NULL) {
        printf("BigInteger Error: calling normalize() on NULL BigInteger reference\n");
        exit(1);
    }

    List L = N->L;
    moveBack(L);
    while (index(L) != - 1) {
        long E = get(L);
        if (E >= BASE) {
            E = E - BASE; // E % base, set. CRRY out is E/base
            set (L, E);
            if (index(L) == 0) {
                prepend(L, 1);
                movePrev(L);
            } else {
                movePrev(L);
                E = get(L);
                E = E + 1;
                set(L, E);
            }
        } else if (E < 0) {
            E = E + BASE;
            set (L, E);
            if (index(L) == 0) {
                prepend(L, -1);
                movePrev(L);
                break;
            } else {
                movePrev(L);
                E = get(L);
                E = E - 1;
                set(L, E);
            }
        } else
            movePrev(L);
    }


    if (front(L) == 0 && length(L) != 0) {
        deleteFront(L);

    }


    if (length(L) != 0) {
        if (front(L) > 0) {
            N->sign = 1;
        } else if (front(L) < 0) {
            negateElement(L);
            normalized(N);
            N->sign = -1;
        }
    }
}


void printBigInteger(FILE* out, BigInteger N) {
    
    if( N == NULL ){
        printf("Queue Error: calling printQueue() on NULL Queue reference\n");
        exit(1);
    }
    List L = N->L;
    
    if (N->sign == -1) {
        fprintf(out, "-");
    }
    moveFront(L);
    while (index(L) > -1) {
        if (index(L) == 0) {
            fprintf(out, "%ld", get(L));
        } else {
            fprintf(out, "%0*ld", POWER, get(L));
        }
        moveNext(L);
    }
}



BigInteger stringToBigInteger(char* s) {
    int length = strlen(s);

    if (s == NULL) {
       exit(1);
    }

    BigInteger B = newBigInteger();
    List L = B->L;

    if (s[0] == '+') {
        B->sign = 1;
        s = s + 1;
        length = length - 1;
    } else if (s[0] == '-') {
        B->sign = -1;
        s = s + 1;
        length = length - 1;

    } else {
        B->sign = 1;
    }

    char *t = malloc(length+(POWER-(length%POWER)) * sizeof(char));

    while (length % POWER != 0) {

        strcat(t, "0");
        length++;
    }

    strcat(t,s);

    char *f = malloc(POWER * sizeof(char));
    char *c = malloc(sizeof(char));

    int numC = 0;
    for (int i = 0; i < ((length)/POWER); i++) {
        for (int j = 0; j < POWER; j++){
            *c = t[numC]; //*c = *(t + numC);
            strcat(f, c);
            numC++;
        }

        append(L, atoi(f));
        strcpy(f, "");
    }


    free(t);
    free(f);
    free(c);

    while (front(B->L) == 0) {
        deleteFront(B->L);
    }
    
    return(B);
}



void negate(BigInteger N) {
    if(N->sign == 1) {
        N->sign = -1;
    }
    else if(N->sign == -1) {
        N->sign = 1;
    }
}


int equals(BigInteger A, BigInteger B) {
    if (compare(A,B) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void makeZero(BigInteger N) {
    
    if(N == NULL) {
        printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
        exit(1);
    }
    List L = N->L;
    clear(L);
    N->sign = 0;
}


BigInteger sum(BigInteger A, BigInteger B) {

     if(A==NULL || B==NULL) {
               printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
               exit(1);
         }
    
      BigInteger S = newBigInteger();
        
      List L1 = A->L;
      List L2 = B->L;

      moveBack(L1);
      moveBack(L2);
      
      while (index(L1) != -1 && index(L2) != -1) {
         long E1 = get(L1);
         long E2 = get(L2);
          
             if (A->sign == B->sign) {
                  if (A->sign > 0 && B->sign > 0) {
                    long E3 = E2 + E1;
                    prepend(S->L, E3);
                    movePrev(L1);
                    movePrev(L2);
                    } else if (A->sign < 0 && B->sign < 0) {
                        long E3 = E2 + E1;
                        prepend(S->L, -E3);
                        movePrev(L1);
                        movePrev(L2);
                    }
             }

              
            if (A->sign > B->sign) {
                 long E3 = E1 - E2;
                 prepend(S->L, E3);
                 movePrev(L1);
                 movePrev(L2);
             }  if (A->sign < B->sign) {
                 long E3 = E2 - E1;
                 prepend(S->L, E3);
                 movePrev(L1);
                 movePrev(L2);
             }
      }


      while (index(L1) != - 1) {
         long E1;
         if (A->sign == -1) {
             E1 = -1 * get(L1);
         } else {
             E1 = get(L1);
         }
         prepend(S->L, E1);
         movePrev(L1);
      }

      while (index(L2) != -1) {
         long E2;
         if (B->sign == -1) {
             E2 = -1 * get(L2);

         } else {
             E2 = get(L2);
         }
         prepend(S->L, E2);
         movePrev(L2);
      }
      
      moveFront(S->L);
      while (index(S->L) > - 1) {
          long E = get(S->L);
          if (E > 0) {
              S->sign = 1;
          } else if (E < 0) {
              S->sign = -1;
          }
      moveNext(S->L);
      }
    
    normalized(S);
    return(S);
    
}


BigInteger diff(BigInteger A, BigInteger B) {
    
    if(A==NULL || B==NULL) {
            printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
            exit(1);
      }
    BigInteger N = newBigInteger();
    negate(B);
    
    N = sum(A, B);
    
    return (N);
      
}




void add(BigInteger S, BigInteger A, BigInteger B) {

    if(A==NULL || B==NULL) {
             printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
             exit(1);
       }
    
    makeZero(S);
    
    List L1 = A->L;
    List L2 = B->L;

    moveBack(L1);
    moveBack(L2);
    
    while (index(L1) != -1 && index(L2) != -1) {
       long E1 = get(L1);
       long E2 = get(L2);
        
           if (A->sign == B->sign) {
                if (A->sign > 0 && B->sign > 0) {
                  long E3 = E2 + E1;
                  prepend(S->L, E3);
                  movePrev(L1);
                  movePrev(L2);
                  } else if (A->sign < 0 && B->sign < 0) {
                      long E3 = E2 + E1;
                      prepend(S->L, -E3);
                      movePrev(L1);
                      movePrev(L2);
                  }
           }  if (A->sign > B->sign) {
               long E3 = E1 - E2;
               prepend(S->L, E3);
               movePrev(L1);
               movePrev(L2);
           }  if (A->sign < B->sign) {
               long E3 = E2 - E1;
               prepend(S->L, E3);
               movePrev(L1);
               movePrev(L2);
           }
        }



    while (index(L1) != - 1) {
       long E1;
       if (A->sign == -1) {
           E1 = -1 * get(L1);
       } else {
           E1 = get(L1);
       }
       prepend(S->L, E1);
       movePrev(L1);
    }

    while (index(L2) != -1) {
       long E2;
       if (B->sign == -1) {
           E2 = -1 * get(L2);

       } else {
           E2 = get(L2);
       }
       prepend(S->L, E2);
       movePrev(L2);
    }
    
    moveFront(S->L);
    while (index(S->L) > - 1) {
        long E = get(S->L);
        if (E > 0) {
            S->sign = 1;
        } else if (E < 0) {
            S->sign = -1;
        }
    moveNext(S->L);
    }
    
    normalized(S);
}



void subtract(BigInteger D, BigInteger A, BigInteger B){
    
    if(A==NULL || B==NULL) {
        printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
        exit(1);
    }
    
    negate(B);
    add(D, A, B);
    
}

BigInteger copy(BigInteger N) {
    if( N == NULL ){
         printf("Queue Error: calling copy() on NULL Queue reference\n");
         exit(1);
     }
    BigInteger C = newBigInteger();
    C->sign = N->sign;
    
    List L = N->L;
    moveBack(L);
    while (index(L) > -1) {
        long x = get(L);
        prepend(C->L, x);
        movePrev(L);
    }
    
    return (C);
}

void scalarMult(BigInteger N, long m) {
    List L1 = N->L;
    moveFront(L1);
    while (index(L1) > -1) {
        if (m != 0) {
            long E = get(L1);
            set(L1, m*E);
        }
        moveNext(L1);
   }
}



BigInteger prod(BigInteger A, BigInteger B) {

 
    BigInteger P = newBigInteger();
    BigInteger T = newBigInteger();

    List L1 = A->L;
    List L2 = B->L;
    List L3 = T->L;
    List L4 = P->L;

    int length1 = length(L1);
    int length2 = length(L2);
    
    long E1, E2;
    long E3 = 0;
    long E4 = 0;
    moveBack(L1);
    moveBack(L2);
   
    for (int i = 0; i < length2; i++) {
        moveBack(L1);
        clear(L3);
        clear(L4);
        for (int j = 0; j < length1; j++) {
            E1 = get(L1);
            E2 = get(L2);
            E3 = (E1 * E2);
            if (index(L3) > -1) {
                prepend(L3, E3);
                movePrev(L3);
            } else {
                prepend(L4, E3);
            }
            movePrev(L1);
        }
        prepend(L3, 0);
        add(P,P,T);
        movePrev(L2);
    }
    
    
    
    if (A->sign == B->sign) {
        P->sign = 1;
    }
    if (A->sign > B->sign || A->sign < B->sign) {
        P->sign = -1;
    }
    return(P);
}



void freeBigInteger(BigInteger* pN) {
    
    if(pN!=NULL && *pN!=NULL) {
        freeList(&((*pN)->L));
        free(*pN);
        *pN = NULL;
    }
}

