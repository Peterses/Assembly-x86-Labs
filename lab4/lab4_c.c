#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//#define rozmiar 8192

void dodawanie_sse(int* tab1, int* tab2, int* wynik, int len);
void odejmowanie_sse(int* tab1, int* tab2, int* wynik, int len);
void mnozenie_sse(int* tab1, int* tab2, int* wynik, int len);
void dzielenie_sse(int* tab1, int* tab2, float* wynik, int len);

void dodawanie_sisd(int* tab1, int* tab2, int* wynik, int len);
void odejmowanie_sisd(int* tab1, int* tab2, int* wynik, int len);
void mnozenie_sisd(int* tab1, int* tab2, float* wynik, int len);
void dzielenie_sisd(int* tab1, int* tab2, float* wynik, int len);

unsigned long long timestamp();

int main()
{
	int rozmiar = 2048;
	unsigned long long start, stop;
	unsigned long long cycles_sse, cycles_simple;
	unsigned long long cycles_sec;
	int tab1[rozmiar];
	int tab2[rozmiar];
	double timeAdd = 0.0;
	double timeSub = 0.0;
	double timeMul = 0.0;
	double timeDiv = 0.0;
	double times_sse[10];
	double times_sisd[10];
	double time_sse;
	double time_sisd;
	double sum = 0.0;
	double sum2 = 0.0;
	srand(time(NULL));

	// LOSOWANIE LICZB
	for(int i = 0; i < rozmiar; i++) {
		tab1[i] = rand() % 1001;
		tab2[i] = rand() % 1001;
	}	

	start = timestamp();
	sleep(1);
	stop = timestamp();
	cycles_sec = stop - start;

	for(int i = 0; i < 3; i++) {
		FILE *ofp;
		int tab1[rozmiar];
		int tab2[rozmiar];
		int wynik[rozmiar];
		float wynikF[rozmiar];
		
		for(int i = 0; i < rozmiar; i++) {
			tab1[i] = rand() % 1001;
			tab2[i] = rand() % 1001;
		}
	
		dodawanie_sse(tab1, tab2, wynik, rozmiar);
		odejmowanie_sse(tab1, tab2, wynik, rozmiar);
		mnozenie_sse(tab1, tab2, wynik, rozmiar);
		dzielenie_sse(tab1, tab2, wynikF, rozmiar);

		// DODAWANIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			dodawanie_sse(tab1, tab2, wynik, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sse = (double)cycles_sse/(double)cycles_sec;

			times_sse[i] = time_sse;
		}

		for(int i = 0; i < 10; i++) {
			timeAdd += times_sse[i];
		}
		
		timeAdd = timeAdd / 10;

		// ODEJMOWANIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			odejmowanie_sse(tab1, tab2, wynik, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sse = (double)cycles_sse/(double)cycles_sec;

			times_sse[i] = time_sse;
		}


		for(int i = 0; i < 10; i++) {
			timeSub += times_sse[i];
		}
		
		timeSub = timeSub / 10;

		// MNOZENIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			mnozenie_sse(tab1, tab2, wynik, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sse = (double)cycles_sse/(double)cycles_sec;

			times_sse[i] = time_sse;
		}


		for(int i = 0; i < 10; i++) {
			timeMul += times_sse[i];
		}
		
		timeMul = timeMul / 10;

		// DZIELENIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			dzielenie_sse(tab1, tab2, wynikF, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sse = (double)cycles_sse/(double)cycles_sec;

			times_sse[i] = time_sse;	
		}

		for(int i = 0; i < 10; i++) {
			timeDiv += times_sse[i];
		}
		
		timeDiv = timeDiv / 10;

		printf("Typ obliczen: SIMD \n Liczba liczb: %i \n Sredni czas [s]: \n + %f \n - %f \n * %f \n / %f \n\n", rozmiar, timeAdd, timeSub, timeMul, timeDiv);


		ofp = fopen("wyniki_simd.txt", "a");
		
		if (ofp) {
		  fprintf(ofp, "Typ obliczen: SIMD \n Liczba liczb: %i \n Sredni czas [s]: \n + %f \n - %f \n * %f \n / %f \n\n", rozmiar, timeAdd, timeSub, timeMul, timeDiv);
		}

		fclose(ofp);

		rozmiar *= 2;
	}

	rozmiar = 2048;

	for(int i = 0; i < 3; i++) {
		FILE *ofp2;
		int tab1[rozmiar];
		int tab2[rozmiar];
		int wynik[rozmiar];
		float wynikF[rozmiar];
		
		for(int i = 0; i < rozmiar; i++) {
			tab1[i] = rand() % 1001;
			tab2[i] = rand() % 1001;
		}

		dodawanie_sisd(tab1, tab2, wynik, rozmiar);
		odejmowanie_sisd(tab1, tab2, wynik, rozmiar);
		mnozenie_sisd(tab1, tab2, wynikF, rozmiar);
		dzielenie_sisd(tab1, tab2, wynikF, rozmiar);
	
		// DODAWANIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			dodawanie_sisd(tab1, tab2, wynik, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sisd = (double)cycles_sse/(double)cycles_sec;

			times_sisd[i] = time_sisd;
		}

		for(int i = 0; i < 10; i++) {
			timeAdd += times_sisd[i];
		}
		
		timeAdd = timeAdd / 10;

		// ODEJMOWANIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			odejmowanie_sisd(tab1, tab2, wynik, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sisd = (double)cycles_sse/(double)cycles_sec;

			times_sisd[i] = time_sisd;
		}


		for(int i = 0; i < 10; i++) {
			timeSub += times_sisd[i];
		}
		
		timeSub = timeSub / 10;

		// MNOZENIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			mnozenie_sisd(tab1, tab2, wynikF, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sisd = (double)cycles_sse/(double)cycles_sec;

			times_sisd[i] = time_sisd;
		}


		for(int i = 0; i < 10; i++) {
			timeMul += times_sisd[i];
		}
		
		timeMul = timeMul / 10;

		// DZIELENIE
		for(int i = 0; i < 10; i++) {
			start = timestamp();
			dzielenie_sisd(tab1, tab2, wynikF, rozmiar);
			stop = timestamp();
			cycles_sse = stop - start;
			time_sisd = (double)cycles_sse/(double)cycles_sec;

			times_sisd[i] = time_sisd;	
		}

		for(int i = 0; i < 10; i++) {
			timeDiv += times_sisd[i];
		}
		
		timeDiv = timeDiv / 10;

		printf("Typ obliczen: SISD \n Liczba liczb: %i \n Sredni czas [s]: \n + %f \n - %f \n * %f \n / %f \n\n", rozmiar, timeAdd, timeSub, timeMul, timeDiv);


		ofp2 = fopen("wyniki_sisd.txt", "a");
		
		if (ofp2) {
		  fprintf(ofp2, "Typ obliczen: SISD \n Liczba liczb: %i \n Sredni czas [s]: \n + %f \n - %f \n * %f \n / %f \n\n", rozmiar, timeAdd, timeSub, timeMul, timeDiv);
		}

		fclose(ofp2);

		rozmiar *= 2;
	}

	return 0;
}
