#include "cl_queue.h"

#include <OpenCL/OpenCL.h>
#include <stdio.h>

#include "hello_cl.h"

cl_int hello_cl_queue_create(cl_context context, cl_device_id device,
                             cl_command_queue *queue) {
  cl_int result = CL_SUCCESS;

  cl_command_queue_properties props = CL_QUEUE_PROFILING_ENABLE;

  *queue = clCreateCommandQueue(context, device, props, &result);
  if (*queue == NULL) {
    return result;
  }

  cl_uint ref_count = 0;
  CL(clGetCommandQueueInfo(*queue, CL_QUEUE_REFERENCE_COUNT, sizeof(cl_uint),
                           &ref_count, NULL));
  printf("CL_QUEUE_REFERENCE_COUNT: %u\n", ref_count);

  return CL_SUCCESS;
}

void hello_cl_queue_destroy(cl_command_queue *queue) {
  if (*queue != NULL) {
    clReleaseCommandQueue(*queue);
    *queue = NULL;
  }
}
