// Last modified: 2013-10-01 21:44:40
 
/**
 * @file: function.h
 * @author: tongjiancong(lingfenghx@gmail.com)
 * @date:   2013-10-01 18:06:40
 * @brief: 
 **/
 
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <stdio.h>
#include <stdint.h>

void CheckHandler(FILE *handler, const char *filename);

void CheckAndSetPointer(void *pointer, char content, size_t size);

void FreePointer(void *pointer);

uint32_t GetFileSize(const char *filename);
 
#endif
