// Last modified: 2013-10-06 01:05:27
 
/**
 * @file: hash.h
 * @author: tongjiancong(lingfenghx@gmail.com)
 * @date:   2013-10-01 17:09:04
 * @brief: 
 **/
 
#ifndef _HASH_H_
#define _HASH_H_

#include <stdint.h>
#define MAX_HASH 15000000

typedef struct hashnode {
	//char *m_key;
	uint64_t m_start;
	struct hashnode *m_next;
} hashnode_t;
extern hashnode_t *hashTable[MAX_HASH];

int Hashkey(const char *str);
/*
 * {
	uint64_t h = 0, g;
	while (*str)
	{
		h = (h << 4) + *str++;
		if ((g = h & 0xf0000000))
			h ^= g >> 24;
		h &= ~g;
	}
	return (uint32_t)(h % MAX_HASH);
}
*/

void HT_Init();

void HT_Free();

void HT_Insert(const char *str, uint64_t position);

//hashnode_t *HT_GetNode(const char *str);
hashnode_t *HT_GetNode(const char *str, uint32_t idx);
 
#endif
