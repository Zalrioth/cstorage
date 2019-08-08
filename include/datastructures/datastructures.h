#pragma once
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdlib.h>
#include <string.h>

#define BOUNDS_CHECK
#if 1
#define SINGLE_PRECISION
typedef float real;
#else
#define DOUBLE_PRECISION
typedef double real;
#endif

#include "arraylist.h"
#include "priorityqueue.h"
#include "queue.h"
#include "stack.h"
#include "vector.h"
#include "octree.h"

#endif
