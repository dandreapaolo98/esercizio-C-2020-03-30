#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned long fibonacci(unsigned int n);	//punto A

unsigned long * fibonacci_array(unsigned int n);	//punto B
unsigned long fibonacci2(unsigned long * fib, unsigned int n);	//punto B

unsigned long * reverse(unsigned long * array, unsigned int i, unsigned int j); //punto C
unsigned long * complete_reverse(unsigned long * array, unsigned int array_len); //punto C
void swap_long(unsigned long *x, unsigned long *y);	//punto C

void bubble_sort(unsigned long * array, int array_dimension);	//punto C

/* main per la visualizzazione dei risultati dei punti A e B (a solo scopo di verifica)
int main(int argc, char * argv[]) {
	unsigned long result_A;
	unsigned long *result_B;
	unsigned int n;
	int scanf_check;
 
	printf("Inserisci un numero n>=0 per la serie di Fibonacci: ");
	scanf("%u", &n);

	//PUNTO A
	result_A = fibonacci(n);

	printf("\nPUNTO A:");
	printf("\n\tLa serie di Fibonacci per n = %u ha come risultato : %u", n, result_A);

	//PUNTO B
	result_B = fibonacci_array(n);

	printf("\n\nPUNTO B:");
	for(unsigned int i = 0; i <= n; i++){
		printf("\n\tfibonacci_array[%u] = %u", i, result_B[i]);
	}

	return 0;
}
*/

int main(int argc, char * argv[]) {
	unsigned int n = 39;
	int result;

	unsigned long *fibonacci_result = fibonacci_array(n);

	unsigned long *fibonacci_result_copy = malloc((n+1) * sizeof(unsigned long));
	memcpy(fibonacci_result_copy, fibonacci_result, (n+1) * sizeof(unsigned long));

	fibonacci_result_copy = complete_reverse(fibonacci_result_copy, n+1);

	bubble_sort(fibonacci_result_copy, n+1);

	result = memcmp(fibonacci_result, fibonacci_result_copy, (n+1) * sizeof(unsigned long));

	printf("\nRisultato confronto tra fibonacci_result e fibonacci_result_copy : %d", result);

	return 0;
}

unsigned long fibonacci(unsigned int n){
	if(n == 0)
		return 0;
	else if(n == 1)
		return 1;

	return fibonacci(n-1) + fibonacci(n-2);
}

unsigned long * fibonacci_array(unsigned int n){
	unsigned long *fib_array;
	fib_array = calloc(n+1, sizeof(unsigned long));

	if(n == 0){
		return fib_array;
	}

	fib_array[1] = 1;

	if(n == 1){
		return fib_array;
	}

	fib_array[n] = fibonacci2(fib_array, n);

	return fib_array;
}

/*
 * fibonacci2: variante della funzione fibonacci del punto A,
 * con l'unica differenza che qui vengono memorizzati i valori
 * della serie passo dopo passo
*/
unsigned long fibonacci2(unsigned long * fib, unsigned int n){
	if(n == 0)
		return 0;
	else if(n == 1)
		return 1;

	unsigned long res = fibonacci2(fib, n-1) + fibonacci2(fib, n-2);
	fib[n] = res;
	return res;
}

unsigned long * reverse(unsigned long * array, unsigned int i, unsigned int j)
{
	while (i < j)
		swap_long(&array[i++], &array[--j]);

	return array;
}

unsigned long * complete_reverse(unsigned long * array, unsigned int array_len) {
	return reverse(array, 0, array_len);
}

void swap_long(unsigned long *x, unsigned long *y) {
	unsigned long t = *x;
	*x = *y;
	*y = t;
}

void bubble_sort(unsigned long * array, int array_dimension) {

	int n = array_dimension;
	do{
		int newn = 0;
		for(int i = 1; i < n; i++){
			if(array[i - 1] > array[i]){
				swap_long(&array[i-1], &array[i]);
				newn = i;
			}
		}
		n = newn;
	}while(n > 1);
}


/*
 ***************TESTO ESERCIZIO*******************

A - scrivere la seguente funzione:

implementare una funzione che calcola la serie di Fibonacci:

unsigned long fibonacci(unsigned int n);

dove:
fibonacci(0) = 0
fibonacci(1) = 1
fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)  per n > 1

provare a scoprire quale è il valore massimo di n per cui fibonacci(n) restituisce un valore della serie corretto


B - scrivere la seguente funzione:

unsigned long * fibonacci_array(unsigned int n);

questa funzione restituisce un array di unsigned long di dimensione n+1 (n è l'argomento della funzione)
dove la cella i-ma contiene il valore di fibonacci(i).

C - main() fa queste operazioni:

calcola fibonacci_array(39) e lo assegna alla varibile 'fibonacci_result'  // fibonacci(39) = 63245986

fare una copia dell'array fibonacci_result in 'fibonacci_result_copy' (i due array devono avere aree di memoria distinte)

fibonacci_result_copy: fare il 'reverse' dell'array ('copiare' da esempio 004.1arrays-operations)

su fibonacci_result_copy: applicare bubble_sort ('copiare' da esempio 004.1arrays-operations)

confrontare fibonacci_result e fibonacci_result_copy, verificare che i due array siano uguali (scrivere su stdout il risultato).

*/
