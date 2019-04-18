#ifndef TOOLS_H_
#define TOOLS_H_

// Pour tracer les fuites mémoires
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>		//fonction rand()
#define _USE_MATH_DEFINES
#include <math.h>		// fonctions cos() / sin() / nombre M_PI


#define INFINI -1
#define TRUE 1
#define FALSE 0

typedef unsigned char BOOL;

#endif
