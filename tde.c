// Last modified: 2013-10-04 21:55:19
 
/**
 * @file: tde.c
 * @author: tongjiancong(lingfenghx@gmail.com)
 * @date:   2013-10-01 18:40:31
 * @brief: 
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"
#include "function.h"
#include "de_redundance.h"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("%s [ori_dict] [gen_dict]\n", argv[0]);
		return -1;
	}
 
	FILE *fori = fopen(argv[1], "rb");
	CheckHandler(fori, argv[1]);
	
	fseek(fori, 0, SEEK_END);
	size_t dict_size = ftell(fori);
	uint32_t dsize = (uint32_t)dict_size;
	rewind(fori);

	uint32_t *marked = (uint32_t *)malloc(dsize * sizeof(uint32_t));
	CheckAndSetPointer(marked, 0, dsize * sizeof(uint32_t));
	
	char *file_buf = (char *)malloc(dsize * sizeof(char));
	CheckAndSetPointer(file_buf, 0, dsize * sizeof(char));
	
	size_t rn = fread(file_buf, sizeof(char), dict_size, fori);
	assert(dict_size == rn);
	
	fclose(fori);

	printf("Initiating hash table ...\n");
	HT_Init();
	
	printf("Identifying the redundance ...\n");
	identify(file_buf, dsize, marked);
	printf("Reconstructing the dictionary ...\n");
	re_construct(file_buf, dsize, marked, argv[2]);

	printf("Destroying hash table ...\n");
	HT_Free();

	FreePointer(marked);
	FreePointer(file_buf);

    return 0;
}
