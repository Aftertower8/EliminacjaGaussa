#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
//macierz[a][b] - a - wiersze, b - kolumny

//!!!SPRAWDZIC CZY WSZYSTKIE INDEKSY NA PEWNO MAJA SENS BO MOZNA SIE POGUBIC!!!

int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	//mat to macierz z niewiadomymi, b to macierz wynikami rownan, x to macierz do ktorej mam wstawic wartosci niewiadomych
	if(mat->r!=b->r || mat->c!=x->r || mat->c!=mat->r)
		return 2;
	int kolumna_akt_x = mat->c-1;
	for(int i=mat->r-1;i>=0;i--){
		double wartosc_akt_x=b->data[i][0];
		for(int j=kolumna_akt_x+1; j<mat->c; j++){
			wartosc_akt_x-=(mat->data[i][j])*(x->data[j][0]);	//przechodze po danym wierszu i dodaje do wartosc_akt_x,
			//od razu podstawiam pod wyliczone wczesniej x ich wartosci (przechodze po kolumnach macierzy x - odpowiadaja im wiersze macierzy m)
		}
		if(mat->data[i][kolumna_akt_x]==0)
			return 1;	//blad - dzielenie przez 0
		wartosc_akt_x/=mat->data[i][kolumna_akt_x];
		x->data[i][0]=wartosc_akt_x;
		kolumna_akt_x--;
	}
	return 0;
}

