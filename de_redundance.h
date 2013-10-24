// Last modified: 2013-10-06 03:19:26
 
/**
 * @file: de-redundance.h
 * @author: tongjiancong(lingfenghx@gmail.com)
 * @date:   2013-09-30 18:41:24
 * @brief: 
 **/
 
#ifndef _DE_REDUNDANCE_H_
#define _DE_REDUNDANCE_H_ 

#include <stdint.h>

#include "hash.h"

#define wsize 64

// pf stands for `position of found`,
// while pp stands for `position of pattern`
int IsOverlap(uint32_t pf, uint32_t pp);

int IsValid(uint32_t marked[], uint32_t pf);

void mark(uint32_t marked[], uint32_t p, uint32_t l);

void identify(const char *filename, uint32_t dsize, uint32_t marked[]);

void re_construct(const char *ori_dict, uint32_t dsize,
		uint32_t marked[], const char *gen_dict);

#endif
