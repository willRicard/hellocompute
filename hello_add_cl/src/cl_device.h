#ifndef HELLO_CL_DEVICE_H
#define HELLO_CL_DEVICE_H

#include <OpenCL/cl.h>

void hello_cl_device_print_type(cl_device_type type);

void hello_cl_device_print_fp_config(cl_device_fp_config config);

void hello_cl_device_print_mem_cache_type(cl_device_mem_cache_type type);

void hello_cl_device_print_exec_capabilities(cl_device_exec_capabilities caps);

void hello_cl_device_print_command_queue_properties(
    cl_command_queue_properties props);

cl_int hello_cl_device_print_preferred_vector_width_info(cl_device_id device);
cl_int hello_cl_device_print_native_vector_width_info(cl_device_id device);

cl_int hello_cl_device_print_mem_info(cl_device_id device);

cl_int hello_cl_device_print_image_info(cl_device_id device);

cl_int hello_cl_device_print_cache_info(cl_device_id device);

cl_int hello_cl_device_print_local_mem_info(cl_device_id device);

#endif // HELLO_CL_DEVICE_H
