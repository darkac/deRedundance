// Last modified: 2013-10-06 01:05:18
 
/**
 * @file: hash.c
 * @author: tongjiancong(lingfenghx@gmail.com)
 * @date:   2013-10-01 17:45:05
 * @brief: 
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hash.h"
#include "function.h"
#include "de_redundance.h"

hashnode_t *hashTable[MAX_HASH];

inline int Hashkey(const char *str)
{
	uint64_t h = 0, g;
	const char *end = str + wsize;
	while (str < end)
	{
		h = (h << 4) + *str++;
		if ((g = h & 0xf0000000))
			h ^= g >> 24;
		h &= ~g;
	}
	return (uint32_t)(h % MAX_HASH);
}

void HT_Init()
{
	uint32_t i;
	for (i = 0; i < MAX_HASH; ++i)
	{
		hashTable[i] = (hashnode_t *)malloc(sizeof(hashnode_t));
		CheckAndSetPointer(hashTable[i], 0, sizeof(hashnode_t));
	}
}

void HT_Free()
{
	uint32_t i;
	for (i = 0; i < MAX_HASH; ++i)
	{
		hashnode_t *temp = hashTable[i]->m_next;
		hashnode_t *todel;
		while (temp != NULL)
		{
			todel = temp;
			temp = temp->m_next;
			//FreePointer(todel->m_key);
			FreePointer(todel);
		}
		FreePointer(hashTable[i]);
	}

}

void HT_Insert(const char *str, uint64_t position)
{
	//int slot = Hashkey(str);
	int slot = Hashkey(str + position);
	
	hashnode_t *hnode = (hashnode_t *)malloc(sizeof(hashnode_t));
	CheckAndSetPointer(hnode, 0, sizeof(hashnode_t));

	//hnode->m_key = (char *)malloc((wsize + 1) * sizeof(char));
	//CheckAndSetPointer(hnode->m_key, 0, (wsize + 1) * sizeof(char));
	
	//strncpy(hnode->m_key, str, wsize);
	//hnode->m_key[wsize] = '\0';
	//memcpy(hnode->m_key, str, wsize);
	
	hnode->m_start = position;
	hnode->m_next = hashTable[slot]->m_next;
	hashTable[slot]->m_next = hnode;
}

//hashnode_t *HT_GetNode(const char *str)
hashnode_t *HT_GetNode(const char *str, uint32_t idx)
{
	//int slot = Hashkey(str);
	int slot = Hashkey(str + idx);

	hashnode_t *p = hashTable[slot];
	hashnode_t *q;
	while ((q = p->m_next) != NULL)
	{
		//if (strncmp(q->m_key, str, wsize) == 0)
		//if (memcmp(q->m_key, str, wsize) == 0)
		if (memcmp(str + q->m_start, str + idx, wsize) == 0)
			break;
		p = p->m_next;
	}

	return q;
}
