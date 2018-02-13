/*
 ============================================================================
 Name        : static_allocator.h
 Author      : Slobodchikov Roman S.
 Version     :
 Copyright   : You can copy code
 Description : My version of static allocator
 ============================================================================
 */

#include <stdio.h>
#define SEGMENT_NUM		100
#define SEGMENT_MIN_BSIZE	4

#define TRUE			1
#define FALSE			0


int initStaticAllocator(char *data, size_t byteLen);
char * my_malloc(size_t bytenum);
void my_free(char *dataPtr);
