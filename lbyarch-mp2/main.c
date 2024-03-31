#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

extern void asm_dot_product();

int main(int argc, char* argv[]) {
	asm_dot_product();
	return 0;
}