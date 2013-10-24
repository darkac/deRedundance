// Last modified: 2013-10-01 21:02:59
 
/**
 * @file: function.c
 * @author: tongjiancong(lingfenghx@gmail.com)
 * @date:   2013-10-01 18:07:21
 * @brief: 
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "function.h"
 
void CheckHandler(FILE *handler, const char *filename)
{
	if (handler == NULL)
	{
		printf("Failed to open file %s !\n", filename);
		exit(-1);
	}
}

void CheckAndSetPointer(void *pointer, char content, size_t size)
{
	if (pointer == NULL)
	{
		printf("Null pointer!");
		exit(-1);
	}
	memset(pointer, content, size);
}

void FreePointer(void *pointer)
{
	if (pointer != NULL)
	{
		free(pointer);
		pointer = 0;
	}
}

uint32_t GetFileSize(const char *filename)
{
	FILE *fori = fopen(filename, "r");
	CheckHandler(fori, filename);
	fseek(fori, 0, SEEK_END);
	size_t dict_size = ftell(fori);
	fclose(fori);

	return (uint32_t)dict_size;
}
