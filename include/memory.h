#ifndef _INCLUDE_MEMORY_H_
#define _INCLUDE_MEMORY_H_


#include <types.h>


paddr_t alloc_page(void);

void free_page(paddr_t addr);


#endif
