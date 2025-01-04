#include "cl_buffer.h"
#include "cl_context.h"
#include "cl_error.h"
#include "cl_kernel.h"
#include "cl_platform.h"
#include "cl_program.h"
#include "cl_queue.h"

#include <OpenCL/OpenCL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N (1 << 20)

static const char *kernel_source =
    "__kernel void add(int n, __global float *x, const __global float *y) {\n\
for (int i = 0; i < n; ++i) {\n\
    x[i] = x[i] + y[i];\n\
  }\n\
}";

int main(void) {
  cl_platform_id platform = NULL;
  cl_device_id device = NULL;
  cl_int result = hello_cl_platform_choose(&platform, &device);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    fprintf(stderr, "Creating OpenCL platform failed\n");
    return EXIT_FAILURE;
  }

  cl_context context = NULL;
  result = hello_cl_context_create(platform, device, &context);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    fprintf(stderr, "Creating OpenCL context failed\n");
  }

  cl_command_queue queue = NULL;
  result = hello_cl_queue_create(context, device, &queue);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    fprintf(stderr, "Creating OpenCL command queue failed\n");
  }

  size_t buf_size = N * sizeof(float);
  float *input_mem_x = NULL;
  input_mem_x = (float *)malloc(buf_size);
  if (input_mem_x == NULL) {
    return EXIT_FAILURE;
  }

  float *input_mem_y = NULL;
  input_mem_y = (float *)malloc(buf_size);
  if (input_mem_y == NULL) {
    return EXIT_FAILURE;
  }

  for (int i = 0; i < N; ++i) {
    input_mem_x[i] = 1.0f;
  }
  for (int i = 0; i < N; ++i) {
    input_mem_y[i] = 2.0f;
  }

  cl_mem input_buffer_x = NULL;
  result =
      hello_cl_buffer_create(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                             buf_size, input_mem_x, &input_buffer_x);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    fprintf(stderr, "Creating first OpenCL buffer failed.\n");
  }

  cl_mem input_buffer_y = NULL;
  result =
      hello_cl_buffer_create(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                             buf_size, input_mem_x, &input_buffer_x);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    fprintf(stderr, "Creating second OpenCL buffer failed.\n");
  }

  float *output_mem_x = NULL;
  output_mem_x = (float *)malloc(buf_size);
  if (output_mem_x == NULL) {
    return EXIT_FAILURE;
  }

  cl_program program = NULL;
  result = hello_cl_program_create(context, device, kernel_source, &program);
  if (result != CL_SUCCESS) {
    fprintf(stderr, "Creating OpenCL program failed.\n");
    return EXIT_FAILURE;
  }

  cl_kernel kernel = NULL;
  result = hello_cl_kernel_create(program, "add", &kernel);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    fprintf(stderr, "Creating OpenCL kernel failed.\n");
    return EXIT_FAILURE;
  }
  int num_values = N;
  result = clSetKernelArg(kernel, 0, sizeof(int), &num_values);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    return EXIT_FAILURE;
  }
  result = clSetKernelArg(kernel, 1, sizeof(cl_mem), &input_buffer_x);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    return EXIT_FAILURE;
  }
  result = clSetKernelArg(kernel, 2, sizeof(cl_mem), &input_buffer_y);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    return EXIT_FAILURE;
  }

  // Get work group info
  result = hello_cl_kernel_print_work_group_info(kernel, device);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    return EXIT_FAILURE;
  }

  // Execute kernel
  cl_event event;
  result = clEnqueueTask(queue, kernel, 0, NULL, &event);
  if (result != CL_SUCCESS) {
    hello_cl_handle_error(result);
    return EXIT_FAILURE;
  }
  clFinish(queue);
  clWaitForEvents(1, &event);

  cl_ulong start = 0, end = 0;
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
                          &start, NULL);
  clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
                          &end, NULL);
  printf("Execution time: %f s\n", (double)(end - start) / 1000000000.0);

  // Read back buffer
  result =
      hello_cl_buffer_read(queue, input_buffer_x, 0, buf_size, output_mem_x);
  float max_error = 0.0f;
  for (int i = 0; i < N; ++i) {
    max_error = fmax(max_error, fabs(output_mem_x[i] - 3.0f));
  }
  printf("Max error: %f\n", max_error);

  hello_cl_kernel_destroy(&kernel);
  hello_cl_program_destroy(&program);
  hello_cl_buffer_destroy(&input_buffer_y);
  hello_cl_buffer_destroy(&input_buffer_x);
  hello_cl_queue_destroy(&queue);
  hello_cl_context_destroy(&context);

  return EXIT_SUCCESS;
}
