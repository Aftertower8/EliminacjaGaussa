#include <stdio.h>
#include <stdlib.h>

#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"

void test_poprawny() {
    printf("TEST 1: Sprawdzenie poprawnych danych (A.txt, b.txt)...\n");

    Matrix *A = readFromFile("A.txt");
    Matrix *b = readFromFile("b.txt");
    Matrix *x;

    if (A == NULL || b == NULL) {
        printf("BLAD Nie znaleziono plikow A.txt lub b.txt\n");
        return;
    }

    int res = eliminate(A, b);
    
    if (res != 0) {
        printf("BLAD Funkcja eliminate zwrocila blad %d dla poprawnej macierzy.\n", res);
    } else {
        x = createMatrix(b->r, 1);
        if (x != NULL) {
            backsubst(x, A, b);
            
            double w1 = x->data[0][0];
            double w2 = x->data[1][0];

            printf(" Wynik: x1=%f, x2=%f\n", w1, w2);

            if (w1 == 2.0 && w2 == 1.0) {
                printf("OK Wynik poprawny.\n");
            } else {
                printf("BLAD Zly wynik (oczekiwano 2.0 i 1.0).\n");
            }
            freeMatrix(x);
        }
    }
    
    freeMatrix(A);
    freeMatrix(b);
    printf("--------------------------------\n");
}

void test_osobliwa() {
    printf("TEST 2: Sprawdzenie macierzy osobliwej (A_bad.txt)...\n");

    Matrix *A = readFromFile("A_bad.txt");
    Matrix *b = readFromFile("b_bad.txt");

    if (A == NULL || b == NULL) {
        printf("BLAD Nie znaleziono plikow A_bad.txt lub b_bad.txt\n");
        return;
    }

    int res = eliminate(A, b);

    if (res == 1) {
        printf("OK Program poprawnie wykryl macierz osobliwa (zwrocil 1).\n");
    } else {
        printf("BLAD Program nie wykryl bledu! Zwrocil: %d\n", res);
    }

    freeMatrix(A);
    freeMatrix(b);
    printf("--------------------------------\n");
}

int main() {
    printf("--- START TESTOW ---\n");
    test_poprawny();
    test_osobliwa();
    printf("--- KONIEC TESTOW ---\n");
    return 0;
}