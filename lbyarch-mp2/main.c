#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern void asm_dot_product();

/*
* Initializes the 2 vectors with the given data
*
* @param n - length of the vector
* @param vectorA - factor 1
* @param vectorB - factor 2
*
*/
void initializeVectors(int n, float* vectorA, float* vectorB) {
	for (int i = 0; i < n; i++) {
		vectorA[i] = (float)i;
		vectorB[i] = 0.5f;
	}
}

int main(int argc, char* argv[]) {
	asm_dot_product();
	return 0;
}


/*
* Performs a dot product between 2 vectors
* 
* @param n - length of the vector
* @param vectorA - factor 1
* @param vectorB - factor 2
* 
* @return sdot - result of the dot product
*/
float c_dot_product(int n, float* vectorA, float* vectorB) {
	float sdot = 0.0; // Initialize output var

	for (int i = 0; i < n; i++) {
		sdot += vectorA[i] * vectorB[i];
	}
	return sdot;
}