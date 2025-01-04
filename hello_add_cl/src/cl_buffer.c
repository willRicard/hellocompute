#include "cl_buffer.h"

#include <stdio.h>

#include "hello_cl.h"

cl_int hello_cl_buffer_create(cl_context context, cl_mem_flags flags,
                              size_t size, void *host_ptr, cl_mem *buffer) {
  cl_int result = CL_SUCCESS;

  *buffer = clCreateBuffer(context, flags, size, host_ptr, &result);
  if (*buffer == NULL) {
    return result;
  }

  return CL_SUCCESS;
}

cl_int hello_cl_buffer_read(cl_command_queue queue, cl_mem buffer,
                            size_t offset, size_t size, void *output) {
  cl_int result = CL_SUCCESS;
  CL(clEnqueueReadBuffer(queue, buffer, CL_TRUE, offset, size, output, 0, NULL,
                         NULL));
  return CL_SUCCESS;
}

void hello_cl_buffer_destroy(cl_mem *buffer) {
  if (*buffer != NULL) {
    clReleaseMemObject(*buffer);
    *buffer = NULL;
  }
}
