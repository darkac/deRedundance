// Last modified: 2013-10-06 01:19:41
 
/**
 * @file: de-redundance.c
 * @author: tongjiancong(lingfenghx@gmail.com)
 * @date:   2013-09-30 18:25:26
 * @brief: Identify the redundance in the dictionary and
 *			remove the duplicated part (as many as possible).
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hash.h"
#include "function.h"
#include "de_redundance.h"

int IsOverlap(uint32_t pf, uint32_t pp)
{
	if (pf + wsize - 1 >= pp)
		return 1;
	else
		return 0;
}

int IsValid(uint32_t marked[], uint32_t pf)
{
	uint32_t i;
	for (i = pf; i < pf + wsize; ++i)
	{
		if (marked[i] == 1)
			return 0;
	}
	return 1;
}

void mark(uint32_t marked[], uint32_t p, uint32_t l)
{
	uint32_t i;
	for (i = p; i < p + l; ++i)
		marked[i] = 1;
}

void identify(const char *file_buf, uint32_t dsize, uint32_t marked[])
{
	uint32_t idx = 0;
	uint32_t range = dsize - wsize;
	while (idx <= range)
	{
		hashnode_t *found = HT_GetNode(file_buf, idx);
		if (found == NULL)
		{
			//HT_Insert(file_buf + idx, idx);
			HT_Insert(file_buf, idx);
			idx++;
		}
		else
		{
			uint32_t pf = found->m_start;
			
			int valid = IsValid(marked, pf);
			
			if (valid == 0)
			{
				//HT_Delete(found);
				
				HT_Insert(file_buf, idx);
				// the invalid hashnode is still in the hash table,
				// however, it will never be reached again.
				// Because next time the same string arrives in this bucket,
				// it will be captured by this newly inserted node (more near
				// to the head of the linked list of this bucket)
				
				idx++;
				continue;
			}
			
			int overlap = IsOverlap(pf, idx);
			if (overlap == 0)
				mark(marked, idx, wsize);
			else
				mark(marked, pf + wsize, idx - pf);
			idx += wsize;
		}

		if (idx % 1048576 == 0)
			printf("Already processed %d MB (approximately)\n", idx / 1048576);
	}
}

void re_construct(const char *file_buf, uint32_t dsize,
		uint32_t marked[], const char *gen_dict)
{
	FILE *fgen = fopen(gen_dict, "wb");
	CheckHandler(fgen, gen_dict);
	
	size_t iter = 0, beg, step = 0;
	while (iter < dsize)
	{
		step = 0;
		
		while (marked[iter++] == 1);
		beg = --iter;
		while (marked[iter] == 0)
		{
			step++;
			if (iter++ == dsize - 1)
				break;
		}
		fwrite(file_buf + beg, sizeof(char), step, fgen);
	}
	
	/*
	uint32_t i;
	for (i = 0; i < dsize; ++i)
	{
		if (marked[i] == 0)
			fwrite(file_buf + i, sizeof(char), 1, fgen);
	}
	*/
	fclose(fgen);
}
