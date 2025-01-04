#include "cl_kernel.h"

#include <OpenCL/OpenCL.h>
#include <stdio.h>

#include "hello_cl.h"

cl_int hello_cl_kernel_create(cl_program program, const char *name,
                              cl_kernel *kernel) {
  cl_int result = CL_SUCCESS;
  *kernel = clCreateKernel(program, name, &result);
  if (*kernel == NULL) {
    return result;
  }
  return CL_SUCCESS;
}

cl_int hello_cl_kernel_print_work_group_info(cl_kernel kernel,
                                             cl_device_id device) {
  cl_int result = CL_SUCCESS;

#if 0
  size_t work_size[3] = {0};
  CL(clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_GLOBAL_WORK_SIZE,
                              sizeof(work_size), &work_size, NULL));
  printf("CL_KERNEL_GLOBAL_WORK_SIZE: (%ld, %ld, %ld)", work_size[0],
         work_size[1], work_size[2]);
#endif

  size_t group_size = 0;
  CL(clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_WORK_GROUP_SIZE,
                              sizeof(size_t), &group_size, NULL));
  printf("CL_KERNEL_WORK_GROUP_SIZE: %ld\n", group_size);

  CL(clGetKernelWorkGroupInfo(kernel, device,
                              CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
                              sizeof(size_t), &group_size, NULL));
  printf("CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE: %ld\n", group_size);

  return CL_SUCCESS;
}

void hello_cl_kernel_destroy(cl_kernel *kernel) {
  if (*kernel != NULL) {
    clReleaseKernel(*kernel);
    *kernel = NULL;
  }
}
