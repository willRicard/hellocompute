#ifndef HELLO_CL_BUFFER_H
#define HELLO_CL_BUFFER_H

#include <OpenCL/cl.h>

cl_int hello_cl_buffer_create(cl_context context, cl_mem_flags flags,
                              size_t size, void *host_ptr, cl_mem *buffer);

cl_int hello_cl_buffer_read(cl_command_queue queue, cl_mem buffer,
                            size_t offset, size_t size, void *ptr);

void hello_cl_buffer_destroy(cl_mem *buffer);

#endif // HELLO_CL_BUFFER_H
