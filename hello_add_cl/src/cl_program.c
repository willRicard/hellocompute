#include "cl_program.h"

#include <OpenCL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hello_cl.h"

void hello_cl_program_print_build_status(cl_build_status status) {
  if (status == CL_BUILD_SUCCESS) {
    printf("CL_BUILD_SUCCESS");
  } else if (status == CL_BUILD_ERROR) {
    printf("CL_BUILD_ERROR");
  } else if (status == CL_BUILD_IN_PROGRESS) {
    printf("CL_BUILD_IN_PROGRESS");
  } else {
    printf("CL_BUILD_NONE");
  }
}

void hello_cl_program_print_binary_type(cl_program_binary_type type) {
  if (type == CL_PROGRAM_BINARY_TYPE_COMPILED_OBJECT) {
    printf("CL_PROGRAM_BINARY_TYPE_COMPILED_OBJECT");
  } else if (type == CL_PROGRAM_BINARY_TYPE_LIBRARY) {
    printf("CL_PROGRAM_BINARY_TYPE_LIBRARY");
  } else if (type == CL_PROGRAM_BINARY_TYPE_EXECUTABLE) {
    printf("CL_PROGRAM_BINARY_TYPE_EXECUTABLE");
  }
}

cl_int hello_cl_program_create(cl_context context, cl_device_id device,
                               const char *source, cl_program *program) {
  cl_int result = CL_SUCCESS;
  size_t length = strnlen(source, 1024);
  *program = clCreateProgramWithSource(context, 1, &source, &length, &result);
  if (*program == NULL) {
    return result;
  }

  CL(clBuildProgram(*program, 1, &device, NULL, NULL, NULL));

  cl_build_status build_status = CL_BUILD_NONE;
  CL(clGetProgramBuildInfo(*program, device, CL_PROGRAM_BUILD_STATUS,
                           sizeof(cl_build_status), &build_status, NULL));
  printf("CL_PROGRAM_BUILD_STATUS: ");
  hello_cl_program_print_build_status(build_status);
  printf("\n");

  // Print program build log
  size_t log_size = 0;
  char build_log[2048] = {0};
  CL(clGetProgramBuildInfo(*program, device, CL_PROGRAM_BUILD_LOG,
                           sizeof(build_log), build_log, &log_size));
  printf("CL_PROGRAM_BUILD_LOG: %s (%ld)\n", build_log, log_size);

  cl_program_binary_type binary_type = CL_PROGRAM_BINARY_TYPE_NONE;
  CL(clGetProgramBuildInfo(*program, device, CL_PROGRAM_BINARY_TYPE,
                           sizeof(cl_program_binary_type), &binary_type, NULL));
  printf("CL_PROGRAM_BINARY_TYPE: ");
  hello_cl_program_print_binary_type(binary_type);
  printf("\n");

  // Export program binary
  size_t binary_size = 0;
  CL(clGetProgramInfo(*program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t),
                      &binary_size, NULL));
  printf("CL_PROGRAM_BINARY_SIZES: %lu\n", binary_size);

  unsigned char *output_binary = NULL;
  output_binary = (unsigned char *)malloc(binary_size);
  if (output_binary == NULL) {
    return CL_OUT_OF_HOST_MEMORY;
  }

  size_t out_size = 0;
  clGetProgramInfo(*program, CL_PROGRAM_BINARIES, binary_size, output_binary,
                   &out_size);

  FILE *output_file = NULL;
  output_file = fopen("out.bin", "wb");
  if (output_file == NULL) {
    return CL_OUT_OF_RESOURCES;
  }

  fwrite(output_binary, binary_size, 1, output_file);
  fclose(output_file);

  return CL_SUCCESS;
}

void hello_cl_program_destroy(cl_program *program) {
  if (*program != NULL) {
    clReleaseProgram(*program);
    *program = NULL;
  }
}
