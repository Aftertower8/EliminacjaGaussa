#include "gauss.h"
#include <math.h>
// Komentarz wywolujacy konflikt
/**
 * Zwraca 0 - eliminacja zakończona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int i, j, k, maxRow;
    double maxVal, factor, tmp;

    for (i = 0; i < mat->r; i++) {

        //Szukanie elementu maksymalnego w kolumnie
        maxRow = i;
        maxVal = fabs(mat->data[i][i]);

        for (j = i + 1; j < mat->r; j++) {
            if (fabs(mat->data[j][i]) > maxVal) {
                maxVal = fabs(mat->data[j][i]);
                maxRow = j;
            }
        }
        if (maxVal == 0.0) {
            return 1;
        }

        // Zamiana wierszy w macierzy
        if (maxRow != i) {
            for (k = 0; k < mat->c; k++) {
                tmp = mat->data[i][k];
                mat->data[i][k] = mat->data[maxRow][k];
                mat->data[maxRow][k] = tmp;
            }

            
            tmp = b->data[i][0];
            b->data[i][0] = b->data[maxRow][0];
            b->data[maxRow][0] = tmp;
        }

        //Eliminacja Gaussa 
        for (j = i + 1; j < mat->r; j++) {
            factor = mat->data[j][i] / mat->data[i][i];

            for (k = i; k < mat->c; k++) {
                mat->data[j][k] -= factor * mat->data[i][k];
            }

            b->data[j][0] -= factor * b->data[i][0];
        }
    }

    return 0;
}
