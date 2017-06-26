#ifndef __PRINT_H
#define __PRINT_H

#ifdef PRINT_GLOBALS
	#define	PRINT_EXT
#else
	#define	PRINT_EXT	extern
#endif

#include "usart.h"	
	
PRINT_EXT void print_init(void);
	
#endif // __USART1_H
