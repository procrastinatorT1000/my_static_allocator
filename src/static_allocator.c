/*
 ============================================================================
 Name        : static_allocator.c
 Author      : Slobodchikov Roman S.
 Version     :
 Copyright   : You can copy code
 Description : My version of static allocator
 ============================================================================
 */
#include "static_allocator.h"
#include <stdio.h>

typedef struct
{
	char *dataPtr;
	char isUsed;
}DataSegmentUsage_t;

static DataSegmentUsage_t dataSegm[SEGMENT_NUM] = {0};
static char isInitialised = FALSE;

int initStaticAllocator(char *data, size_t byteLen)
{
	size_t segByteSize = byteLen / SEGMENT_NUM;

	if(segByteSize < SEGMENT_MIN_BSIZE)
	{
		perror("Error: Static memory byte len should be bigger or equal to %d bytes\n", SEGMENT_NUM * SEGMENT_MIN_BSIZE);

		return FALSE;
	}

	if(byteLen % SEGMENT_NUM != 0)
	{
		perror("Error: Static memory byte len should be multiple to %d bytes\n", SEGMENT_NUM);

		return FALSE;
	}



	for(int i = 0; i < SEGMENT_NUM; i++)
	{
		dataSegm.dataPtr = &data[i*segByteSize];
		dataSegm.isUsed = FALSE;
	}
	isInitialised = TRUE;

	return TRUE;
}

//char * malloc()

