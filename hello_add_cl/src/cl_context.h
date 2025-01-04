#ifndef HELLO_CL_CONTEXT_H
#define HELLO_CL_CONTEXT_H

#include <OpenCL/cl.h>

cl_int hello_cl_context_create(cl_platform_id platform, cl_device_id device,
                               cl_context *context);

void hello_cl_context_destroy(cl_context *context);

#endif // HELLO_CL_CONTEXT_H
