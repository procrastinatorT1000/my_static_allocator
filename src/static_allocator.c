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


typedef struct
{
	char *dataPtr;
	char isUsed;
}DataSegmentUsage_t;

DataSegmentUsage_t dataSegm[SEGMENT_NUM] = {0};

