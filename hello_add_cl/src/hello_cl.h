#ifndef HELLO_CL_CL_H
#define HELLO_CL_CL_H

#include <OpenCL/cl.h>

#include <stdio.h>

#define CL(x)                                                                  \
  result = x;                                                                  \
  if (result != CL_SUCCESS) {                                                  \
    fprintf(stderr, "%s:%d %s:", __FILE__, __LINE__, #x);                      \
    return result;                                                             \
  }

#endif // HELLO_CL_H
