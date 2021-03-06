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
	int marker;	/* segments allocated same time will have same marker 0 means it's free */
}DataSegmentUsage_t;

static DataSegmentUsage_t dataSegm[SEGMENT_NUM] = {0};
static char isInitialised = FALSE;
static size_t segmByteSize = 0;
static int markerCount = 1;	/* Can't be 0, 0 it's free */

int initStaticAllocator(char *data, size_t byteLen)
{
	size_t segBSize = byteLen / SEGMENT_NUM;

	if(segBSize < SEGMENT_MIN_BSIZE)
	{
		printf("Error: Static memory byte len should be bigger or equal to %d bytes\n", SEGMENT_NUM * SEGMENT_MIN_BSIZE);

		return FALSE;
	}

	if(byteLen % SEGMENT_NUM != 0)
	{
		printf("Error: Static memory byte len should be multiple to %d bytes\n", SEGMENT_NUM);

		return FALSE;
	}



	for(int i = 0; i < SEGMENT_NUM; i++)
	{
		dataSegm[i].dataPtr = &data[i*segBSize];
		dataSegm[i].isUsed = FALSE;
	}
	isInitialised = TRUE;
	segmByteSize = segBSize;
	markerCount = 1;

	return TRUE;
}

char * my_malloc(size_t bytenum)
{
	if(isInitialised == FALSE)
	{
		printf("Static allocator isn't initialized\n");
		return NULL;
	}

	int segNum = bytenum / segmByteSize + 1;
	int counter = 0;
	int allocSegIdx = 0;
	char *allocPtr = NULL;

	int idx = 0;
	for(idx = 0; idx < SEGMENT_NUM; idx++)
	{
		if(dataSegm[idx].isUsed == FALSE)
			counter++;
		if(counter >= segNum)
			break;
	}

	if(idx == SEGMENT_NUM)
	{
		return NULL;	/* No free mem */
	}

	int startAllocIdx = idx - segNum + 1;
	allocPtr = dataSegm[startAllocIdx].dataPtr;

	for(int k = startAllocIdx; k <= idx; k++ )
	{
		dataSegm[k].isUsed = TRUE;
		dataSegm[k].marker = markerCount;
	}
	markerCount++;

	return allocPtr;
}

void my_free(char *dataPtr)
{
	int idx = 0;

	for(idx = 0; idx < SEGMENT_NUM; idx++)
	{
		if(dataSegm[idx].dataPtr == dataPtr)
			break;
	}

	if(idx == SEGMENT_NUM)
	{
		printf("That mem was not allocated\n");
		return;
	}

	int curMarker = dataSegm[idx].marker;

	for(int i = idx; i < SEGMENT_NUM; i++)
	{
		if(dataSegm[i].marker == curMarker)
		{
			dataSegm[i].isUsed = FALSE;
		}
		else
		{
			break;
		}
	}

	return;
}
