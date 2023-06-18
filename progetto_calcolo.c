/*Implementare un programma parallelo per l’ambiente multicore con nq×np unità processanti che impieghi la libreria OpenMP.
Il programma deve essere organizzato come segue: il core master deve costruire una matrice A, di dimensione M×N, 
i cui blocchi sono generati casualmente e in parallelo da ogni core*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
	int N, M, id_thread, i, j, numT;
	double t0, t1, t;

	//Controllo del parametro di input
	if (argc > 1 && (atoi(argv[1])))
		numT = atoi(argv[1]);
	else
	{
		printf("ATTENZIONE: Numero thread errato o assente \n");
		exit(EXIT_FAILURE);
	}

	//lettura delle dimensioni della matrice con relativi controlli
	do {
		printf("Inserire il valore delle righe: \n");
		scanf("%d", &N);
		if (N == 0)
			printf("La matrice non presenta alcuna riga, RIPROVARE\n");
	} while (N == 0);

	do {
		printf("Inserire il valore delle colonne: \n");
		scanf("%d", &M);
		if (M == N)
			printf("ATTENZIONE : Il numero delle colonne deve essere diverso dal numero di righe\n");
		if (M == 0)
			printf("La matrice deve avere almeno una colonna\n");
	} while (M == N || M == 0);

	//ALLOCAZIONE DELLA MEMORIA PER LA MATRICE A
	int* A;
    
	A = (int*)malloc(N * M*sizeof(int));
    
	//Chiamata n.1 omp_get_wtime
	t0 = omp_get_wtime();
	
	//inizio del lavoro in parallelo DUE FOR, TEMPO T(NXM) = O(NXM)
	#pragma omp parallel  shared(N,M,A) private(i,j) num_threads(numT)
    {
     srand(time(NULL) ^ omp_get_thread_num());
     #pragma for schedule(static)
     for (i = 0; i <= N; i++) //ciclo principale
	{
		for (j = 0; j <= M; j++)
		{
			A[j*N+i] =rand()%100+1;
		}
	 }
    }
	//chiamata n.2 omp_get_wtime
	t1 = omp_get_wtime();
	//calcolo del tempo totale con relativa stampa
	t = t1 - t0;
	
	//stampa dei valori della matrice
	printf("I valori della matrice sono:\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf("%d\t",A[j*N+i]);
		}
		printf("\n");
	}
    printf("\nIl tempo necessario al calcolo e' : %lf sec.\n", t);
	//deallocazione della memoria
	free(A);
	return 0;
} 
