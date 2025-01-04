#include "cl_device.h"

#include <OpenCL/OpenCL.h>
#include <stdio.h>

#include "hello_cl.h"

void hello_cl_device_print_type(cl_device_type type) {
  if (type & CL_DEVICE_TYPE_CPU) {
    printf("CL_DEVICE_TYPE_CPU ");
  }
  if (type & CL_DEVICE_TYPE_GPU) {
    printf("CL_DEVICE_TYPE_GPU ");
  }
  if (type & CL_DEVICE_TYPE_ACCELERATOR) {
    printf("CL_DEVICE_TYPE_ACCELERATOR ");
  }
  if (type & CL_DEVICE_TYPE_DEFAULT) {
    printf("CL_DEVICE_TYPE_DEFAULT ");
  }
  if (type & CL_DEVICE_TYPE_CUSTOM) {
    printf("CL_DEVICE_TYPE_CUSTOM");
  }
}

void hello_cl_device_print_fp_config(cl_device_fp_config config) {
  if (config & CL_FP_DENORM) {
    printf("CL_FP_DENORM ");
  }
  if (config & CL_FP_INF_NAN) {
    printf("CL_FP_INF_NAN ");
  }
  if (config & CL_FP_ROUND_TO_NEAREST) {
    printf("CL_FP_ROUND_TO_NEAREST ");
  }
  if (config & CL_FP_ROUND_TO_ZERO) {
    printf("CL_FP_ROUNT_TO_ZERO ");
  }
  if (config & CL_FP_ROUND_TO_INF) {
    printf("CL_FP_ROUNT_TO_INF ");
  }
  if (config & CL_FP_FMA) {
    printf("CL_FP_FMA ");
  }
  if (config & CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT) {
    printf("CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT ");
  }
  if (config & CL_FP_SOFT_FLOAT) {
    printf("CL_FP_SOFT_FLOAT ");
  }
}

void hello_cl_device_print_mem_cache_type(cl_device_mem_cache_type type) {
  if (type == CL_READ_WRITE_CACHE) {
    printf("CL_READ_WRITE_CACHE");
  } else if (type == CL_READ_ONLY_CACHE) {
    printf("CL_READ_ONLY_CACHE");
  } else {
    printf("CL_NONE");
  }
}

void hello_cl_device_print_local_mem_type(cl_device_local_mem_type type) {
  if (type == CL_LOCAL) {
    printf("CL_LOCAL");
  } else if (type == CL_GLOBAL) {
    printf("CL_GLOBAL");
  } else {
    printf("CL_NONE");
  }
}

void hello_cl_device_print_exec_capabilities(cl_device_exec_capabilities caps) {
  if (caps & CL_EXEC_KERNEL) {
    printf("CL_EXEC_KERNEL ");
  }
  if (caps & CL_EXEC_NATIVE_KERNEL) {
    printf("CL_EXEC_NATIVE_KERNEL ");
  }
}

void hello_cl_device_print_command_queue_properties(
    cl_command_queue_properties props) {
  if (props & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) {
    printf("CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
  }
  if (props & CL_QUEUE_PROFILING_ENABLE) {
    printf("CL_QUEUE_PROFILING_ENABLE ");
  }
}

#define _device_print_bool(device, param, value)                               \
  CL(clGetDeviceInfo(device, param, sizeof(cl_bool), &value, NULL));           \
  printf("\t" #param ": %d\n", value);

#define _device_print_uint(device, param, value)                               \
  CL(clGetDeviceInfo(device, param, sizeof(cl_uint), &value, NULL));           \
  printf("\t" #param ": %u\n", value);

#define _device_print_ulong(device, param, value)                              \
  CL(clGetDeviceInfo(device, param, sizeof(cl_ulong), &value, NULL));          \
  printf("\t" #param ": %llu\n", value);

#define _device_print_size(device, param, value)                               \
  CL(clGetDeviceInfo(device, param, sizeof(size_t), &value, NULL));            \
  printf("\t" #param ": %ld\n", value);

cl_int hello_cl_device_print_preferred_vector_width_info(cl_device_id device) {
  cl_uint width = 0;
  cl_int result = CL_SUCCESS;
  _device_print_uint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, width);
  _device_print_uint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, width);
  _device_print_uint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, width);
  _device_print_uint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, width);
  _device_print_uint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, width);
  _device_print_uint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, width);
  _device_print_uint(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, width);
  return CL_SUCCESS;
}

cl_int hello_cl_device_print_native_vector_width_info(cl_device_id device) {
  cl_uint width = 0;
  cl_int result = CL_SUCCESS;
  _device_print_uint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, width);
  _device_print_uint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, width);
  _device_print_uint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, width);
  _device_print_uint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, width);
  _device_print_uint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, width);
  _device_print_uint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, width);
  _device_print_uint(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, width);
  return CL_SUCCESS;
}

cl_int hello_cl_device_print_mem_info(cl_device_id device) {
  cl_uint address_bits = 0;
  cl_ulong max_alloc = 0;
  cl_int result = CL_SUCCESS;
  _device_print_uint(device, CL_DEVICE_ADDRESS_BITS, address_bits);
  _device_print_ulong(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, max_alloc);
  return CL_SUCCESS;
}

cl_int hello_cl_device_print_image_info(cl_device_id device) {
  cl_int result = CL_SUCCESS;
  cl_bool image_support = 0;
  cl_uint max_args = 0;
  size_t max_image_size = 0;
  _device_print_bool(device, CL_DEVICE_IMAGE_SUPPORT, image_support);
  _device_print_uint(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, max_args);
  _device_print_uint(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, max_args);
  _device_print_size(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, max_image_size);
  _device_print_size(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, max_image_size);
  _device_print_size(device, CL_DEVICE_IMAGE3D_MAX_WIDTH, max_image_size);
  _device_print_size(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT, max_image_size);
  _device_print_size(device, CL_DEVICE_IMAGE3D_MAX_DEPTH, max_image_size);
  _device_print_size(device, CL_DEVICE_IMAGE_MAX_BUFFER_SIZE, max_image_size);
  _device_print_size(device, CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, max_image_size);
  _device_print_size(device, CL_DEVICE_MAX_SAMPLERS, max_image_size);
  return CL_SUCCESS;
}

cl_int hello_cl_device_print_cache_info(cl_device_id device) {
  cl_int result = CL_SUCCESS;
  cl_device_mem_cache_type cache_type = CL_NONE;
  cl_ulong size = 0;
  CL(clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
                     sizeof(cl_device_mem_cache_type), &cache_type, NULL));
  printf("\tCL_DEVICE_GLOBAL_MEM_CACHE_TYPE: ");
  hello_cl_device_print_mem_cache_type(cache_type);
  printf("\n");
  _device_print_ulong(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, size);
  _device_print_ulong(device, CL_DEVICE_GLOBAL_MEM_SIZE, size);
  return CL_SUCCESS;
}

cl_int hello_cl_device_print_local_mem_info(cl_device_id device) {
  cl_int result = CL_SUCCESS;
  cl_device_local_mem_type mem_type = CL_NONE;
  cl_ulong size = 0;
  CL(clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE,
                     sizeof(cl_device_local_mem_type), &mem_type, NULL));
  printf("\tCL_DEVICE_LOCAL_MEM_TYPE: ");
  hello_cl_device_print_local_mem_type(mem_type);
  printf("\n");
  _device_print_ulong(device, CL_DEVICE_LOCAL_MEM_SIZE, size);
  return CL_SUCCESS;
}
