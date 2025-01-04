#include "cl_context.h"

#include <OpenCL/OpenCL.h>
#include <stdio.h>

#include "hello_cl.h"

void on_device_error(const char *errinfo, const void *private_info, size_t cb,
                     void *user_data) {
  printf("[cl:err] %s\n", errinfo);
}

cl_int hello_cl_context_create(cl_platform_id platform, cl_device_id device,
                               cl_context *context) {
  cl_int result = CL_SUCCESS;

  cl_context_properties props[] = {CL_CONTEXT_PLATFORM,
                                   (cl_context_properties)platform,
                                   (cl_context_properties)NULL};

  *context = clCreateContext(props, 1, &device, on_device_error, NULL, &result);
  if (context == NULL) {
    return result;
  }

  cl_uint ref_count = 0;
  CL(clGetContextInfo(*context, CL_CONTEXT_REFERENCE_COUNT, sizeof(cl_uint),
                      &ref_count, NULL));
  printf("CL_CONTEXT_REFERENCE_COUNT: %u\n", ref_count);

  cl_uint num_devices = 0;
  CL(clGetContextInfo(*context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint),
                      &num_devices, NULL));
  printf("CL_CONTEXT_NUM_DEVICES: %u\n", num_devices);

  return CL_SUCCESS;
}

void hello_cl_context_destroy(cl_context *context) {
  if (*context != NULL) {
    clReleaseContext(*context);
    *context = NULL;
  }
}
