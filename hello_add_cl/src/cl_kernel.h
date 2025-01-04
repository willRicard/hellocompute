#ifndef HELLO_CL_KERNEL_H
#define HELLO_CL_KERNEL_H

#include <OpenCL/cl.h>

cl_int hello_cl_kernel_create(cl_program, const char *name, cl_kernel *kernel);

cl_int hello_cl_kernel_print_work_group_info(cl_kernel kernel,
                                             cl_device_id device);

void hello_cl_kernel_destroy(cl_kernel *kernel);

#endif // HELLO_CL_KERNEL_H
