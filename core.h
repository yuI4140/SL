#pragma once
#ifdef DEF
#include "defines.h"
#endif // END-DEF
#ifdef NORMAL
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
#endif // END-NORMAL
#ifdef VARIANTIC
#include <stdarg.h>
#endif // END-VARIANTIC
#ifdef ERRH
#include <assert.h>
#include <errno.h>
#endif // END-ERRH
#ifdef CR_THREAD
#include "thread.c"
#endif // END-CR_THREAD
//CORE.H