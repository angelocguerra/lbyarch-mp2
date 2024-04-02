#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Call Assembly function
extern float asm_dot_product(int n, float* vectorA, float* vectorB);

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

int main(int argc, char* argv[]) {
	// Initialize input variables
	int exponent = 20; // Change variable assignment value to set vector size
					   // 20 for 2^20, 24 for 2^24, 30 for 2^30
	int n = 1 << exponent; 
	float* vectorA;
	float* vectorB;

	// Initialize output variables
	float sdot_c = 0.0f, sdot_asm = 0.0f;

	// Initialize timer variables
	clock_t start_c, end_c; // Timers for C kernel
	clock_t start_asm, end_asm; // Timers for ASM kernel
	double totalTime_c = 0, totalTime_asm = 0;
	double aveTime_c, aveTime_asm;

	int error_flag = 0; // Set when sdot do not match

	// Initialize vector sizes
	vectorA = (float*)malloc(n * sizeof(float));
	vectorB = (float*)malloc(n * sizeof(float));

	// Initialize vector data
	initializeVectors(n, vectorA, vectorB);

	int iterations = 24; // Time both functions 30 times

	// Display console
	printf("Vector Size: 2^%d\n\n", exponent);

	for (int i = 0; i < iterations; i++) {
		// C Function
		start_c = clock(); // Start timer
		sdot_c = c_dot_product(n, vectorA, vectorB); // Perform function
		end_c = clock(); // End timer
		
		// Compute time for C function
		totalTime_c += ((double)(end_c - start_c)) / CLOCKS_PER_SEC;

		// Assembly Function
		start_asm = clock(); // Start timer
		sdot_asm = asm_dot_product(n, vectorA, vectorB); // Perform function
		end_asm = clock(); // End timer

		// Compute time for ASM function
		totalTime_asm += ((double)(end_asm - start_asm)) / CLOCKS_PER_SEC;

		// Output Correctness Checking
		if (sdot_c != sdot_asm) {
			error_flag = 1;
			printf("Error: Outputs do not match, found sdot at C = %f while ASM = %f\n", sdot_c, sdot_asm);
		}
	}

	// Compute for average execution times
	aveTime_c = totalTime_c / iterations;
	aveTime_asm = totalTime_asm / iterations;

	printf("ERROR CHECKING:\n");
	if (error_flag == 0) { // No errors
		printf("All iterations yielded the same results for both C and x86-65 Assembly kernels. No errors have been found.\n\n");
	}
	else { // With errors
		printf("C and x86-64 Assembly kernel do not have matching outputs. Errors have been found.\n\n");
	}

	// Display outputs
	printf("OUTPUTS (DOT PRODUCT):\n");
	printf("              C: %f\n", sdot_c);
	printf("x86-64 Assembly: %f\n\n", sdot_asm);
	
	// Display runtimes
	printf("AVERAGE EXECUTION TIMES:\n");
	printf("              C: %lf seconds\n", aveTime_c);
	printf("x86-64 Assembly: %lf seconds\n", aveTime_asm);

	// De-allocate memory
	free(vectorA);
	free(vectorB);
	
	return 0;
}