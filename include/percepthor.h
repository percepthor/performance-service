#ifndef _PERCEPTHOR_H_
#define _PERCEPTHOR_H_

#include "runtime.h"

struct _HttpResponse;

extern RuntimeType RUNTIME;

extern unsigned int PORT;

extern unsigned int CERVER_RECEIVE_BUFFER_SIZE;
extern unsigned int CERVER_TH_THREADS;
extern unsigned int CERVER_CONNECTION_QUEUE;

// inits percepthor main values
extern unsigned int percepthor_init (void);

// ends percepthor main values
extern unsigned int percepthor_end (void);

#endif