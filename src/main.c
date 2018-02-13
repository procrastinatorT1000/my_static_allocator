/*
 ============================================================================
 Name        : static_allocator.c
 Author      : slb-rs
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "static_allocator.h"

int main(void) {

	char * staticDataPtr = malloc(1000);

	printf("staticDataPtr = %X\n", staticDataPtr);

	initStaticAllocator(staticDataPtr, 1000);

	char *myMallocPtr = my_malloc(145);
	char *myMallocPtr1 = my_malloc(234);

	printf("alloc %d bytes = %X\n", 145, (unsigned int)myMallocPtr );
//	my_free(myMallocPtr);

	printf("alloc %d bytes = %X\n", 145, (unsigned int)myMallocPtr1 );
	my_free(myMallocPtr);
	my_free(myMallocPtr1);

	free(staticDataPtr);


	return EXIT_SUCCESS;
}
