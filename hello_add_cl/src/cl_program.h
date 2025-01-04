#ifndef HELLO_CL_PROGRAM_H
#define HELLO_CL_PROGRAM_H

#include <OpenCL/cl.h>

cl_int hello_cl_program_create(cl_context context, cl_device_id device,
                               const char *source, cl_program *program);

void hello_cl_program_destroy(cl_program *program);

#endif // HELLO_CL_PROGRAM_H
