/*
 * pal_os_memory.c
 *
 *  Created on: Nov 13, 2022
 *      Author: andre
 */
#include <stdlib.h>
#include "optiga/pal/pal_os_memory.h"

static volatile uint8_t heap[16 * 1024];

LIBRARY_EXPORTS void * pal_os_malloc(uint32_t block_size) {
	return malloc(block_size);
}

LIBRARY_EXPORTS void * pal_os_calloc(uint32_t number_of_blocks , uint32_t block_size) {
	return malloc(number_of_blocks * block_size);
}

LIBRARY_EXPORTS void pal_os_free(void * block) {
	free(block);
}

LIBRARY_EXPORTS void pal_os_memcpy(void * p_destination, const void * p_source, uint32_t size) {
	memcpy(p_destination, p_source, size);
}

LIBRARY_EXPORTS void pal_os_memset(void * p_buffer, uint32_t value, uint32_t size) {
	memset(p_buffer, value, size);
}
