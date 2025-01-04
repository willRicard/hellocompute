#include "cl_platform.h"

#include <stdio.h>
#include <stdlib.h>

#include "cl_device.h"
#include "hello_cl.h"

cl_int hello_cl_platform_choose(cl_platform_id *platform,
                                cl_device_id *device) {
  cl_uint num_platforms = 0;
  cl_int result = CL_SUCCESS;
  CL(clGetPlatformIDs(0, NULL, &num_platforms));

  printf("There are %d OpenCL platforms\n", num_platforms);

  cl_platform_id platforms[4] = {NULL};
  CL(clGetPlatformIDs(num_platforms, platforms, &num_platforms));

  char value[256] = {0};
  size_t out_size = 0;
  for (cl_uint i = 0; i < num_platforms; ++i) {
    CL(clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, sizeof(value),
                         value, &out_size));
    printf("CL_PLATFORM_PROFILE: %s\n", value);

    CL(clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, sizeof(value),
                         value, &out_size));
    printf("CL_PLATFORM_VERSION: %s\n", value);

    CL(clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(value), value,
                         &out_size));
    printf("CL_PLATFORM_NAME: %s\n", value);

    CL(clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(value), value,
                         &out_size));
    printf("CL_PLATFORM_VENDOR: %s\n", value);

    CL(clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, sizeof(value),
                         value, &out_size));
    printf("CL_PLATFORM_EXTENSIONS: %s\n", value);

    cl_uint num_devices = 0;
    CL(clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices));
    printf("There are %d devices on platform #%d\n", num_devices, i);

    cl_device_id devices[8] = {NULL};
    CL(clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices,
                      &num_devices));

    // Pick first platform and device
    *platform = platforms[0];
    *device = devices[0];

    for (cl_uint j = 0; j < num_devices; ++j) {
      cl_device_type device_type = CL_DEVICE_TYPE_DEFAULT;
      cl_uint device_vendor = 0;

      cl_uint max_compute_units = 0;
      cl_uint max_work_item_dimensions = 0;
      size_t max_work_item_sizes[16] = {0};
      size_t max_work_group_size = 0;
      cl_uint max_clock_frequency = 0;

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_TYPE, sizeof(cl_device_type),
                         &device_type, &out_size));
      printf("\tCL_DEVICE_TYPE: ");
      hello_cl_device_print_type(device_type);
      printf("\n");

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR_ID, sizeof(cl_uint),
                         &device_vendor, &out_size));
      printf("\tCL_DEVICE_VENDOR_ID: %u\n", device_vendor);

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                         sizeof(cl_uint), &max_compute_units, &out_size));
      printf("\tCL_DEVICE_MAX_COMPUTE_UNITS: %u\n", max_compute_units);

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
                         sizeof(cl_uint), &max_work_item_dimensions,
                         &out_size));
      printf("\tCL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: %u\n",
             max_work_item_dimensions);

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES,
                         max_work_item_dimensions * sizeof(size_t),
                         max_work_item_sizes, &out_size));
      printf("\tCL_DEVICE_MAX_WORK_ITEM_SIZES: (%lu, %lu, %lu)\n",
             max_work_item_sizes[0], max_work_item_sizes[1],
             max_work_item_sizes[2]);

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE,
                         sizeof(size_t), &max_work_group_size, &out_size));
      printf("\tCL_DEVICE_MAX_WORK_GROUP_SIZE: %lu\n", max_work_group_size);

      // CL(hello_cl_device_print_preferred_vector_width_info(devices[j]));
      // CL(hello_cl_device_print_native_vector_width_info(devices[j]));

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY,
                         sizeof(cl_uint), &max_clock_frequency, &out_size));
      printf("\tCL_DEVICE_MAX_CLOCK_FREQUENCY: %u\n", max_clock_frequency);

      CL(hello_cl_device_print_mem_info(devices[j]));
      CL(hello_cl_device_print_image_info(devices[j]));

      size_t max_parameter_size = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_PARAMETER_SIZE,
                         sizeof(size_t), &max_parameter_size, &out_size));
      printf("\tCL_DEVICE_MAX_PARAMETER_SIZE: %ld\n", max_parameter_size);

      cl_uint addr_align = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MEM_BASE_ADDR_ALIGN,
                         sizeof(cl_uint), &addr_align, &out_size));
      printf("\tCL_DEVICE_MEM_BASE_ADDR_ALIGN: %u\n", addr_align);

      cl_device_fp_config single_fp_config = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_SINGLE_FP_CONFIG,
                         sizeof(cl_device_fp_config), &single_fp_config,
                         &out_size));
      printf("\tCL_DEVICE_SINGLE_FP_CONFIG: ");
      hello_cl_device_print_fp_config(single_fp_config);
      printf("\n");

      cl_device_fp_config double_fp_config = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_DOUBLE_FP_CONFIG,
                         sizeof(cl_device_fp_config), &double_fp_config,
                         &out_size));
      printf("\tCL_DEVICE_DOUBLE_FP_CONFIG: ");
      hello_cl_device_print_fp_config(double_fp_config);
      printf("\n");

      CL(hello_cl_device_print_cache_info(devices[j]));

      cl_ulong max_constant_buffer_size = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
                         sizeof(cl_ulong), &max_constant_buffer_size,
                         &out_size));
      printf("\tCL_DEVICE_MAX_CONSTANT_BUFFER_SIZE: %lld\n",
             max_constant_buffer_size);

      cl_uint max_constant_args = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CONSTANT_ARGS,
                         sizeof(cl_uint), &max_constant_args, &out_size));
      printf("\tCL_DEVICE_MAX_CONSTANT_ARGS: %u\n", max_constant_args);

      cl_bool error_correction = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_ERROR_CORRECTION_SUPPORT,
                         sizeof(cl_bool), &error_correction, &out_size));
      printf("\tCL_DEVICE_ERROR_CORRECTION_SUPPORT: %d\n", error_correction);

      cl_bool unified_memory = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_HOST_UNIFIED_MEMORY,
                         sizeof(cl_bool), &unified_memory, &out_size));
      printf("\tCL_DEVICE_HOST_UNIFIED_MEMORY: %d\n", unified_memory);

      size_t timer_resolution = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_PROFILING_TIMER_RESOLUTION,
                         sizeof(size_t), &timer_resolution, &out_size));
      printf("\tCL_DEVICE_PROFILING_TIMER_RESOLUTION: %lu\n", timer_resolution);

      cl_bool little_endian = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_ENDIAN_LITTLE, sizeof(cl_bool),
                         &little_endian, NULL));
      printf("\tCL_DEVICE_ENDIAN_LITTLE: %d\n", little_endian);

      cl_bool available = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_AVAILABLE, sizeof(cl_bool),
                         &available, &out_size));
      printf("\tCL_DEVICE_AVAILABLE: %d\n", available);

      cl_bool compiler_available = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_COMPILER_AVAILABLE,
                         sizeof(cl_bool), &compiler_available, &out_size));
      printf("\tCL_DEVICE_COMPILER_AVAILABLE: %d\n", compiler_available);

      cl_bool linker_available = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_LINKER_AVAILABLE,
                         sizeof(cl_bool), &linker_available, &out_size));
      printf("\tCL_DEVICE_LINKER_AVAILABLE: %d\n", linker_available);

      cl_device_exec_capabilities caps;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_EXECUTION_CAPABILITIES,
                         sizeof(cl_device_exec_capabilities), &caps,
                         &out_size));
      printf("\tCL_DEVICE_EXECUTION_CAPABILITIES: ");
      hello_cl_device_print_exec_capabilities(caps);
      printf("\n");

      cl_command_queue_properties props;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_QUEUE_PROPERTIES,
                         sizeof(cl_command_queue_properties), &props,
                         &out_size));
      printf("\tCL_DEVICE_QUEUE_PROPERTIES: ");
      hello_cl_device_print_command_queue_properties(props);
      printf("\n");

      char builtin_kernels[1024] = {0};
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_BUILT_IN_KERNELS,
                         sizeof(builtin_kernels), builtin_kernels, &out_size));
      printf("\tCL_DEVICE_BUILT_IN_KERNELS: %s (%ld)\n", builtin_kernels,
             out_size);

      char name[32] = {0};
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(name), name,
                         &out_size));
      printf("\tCL_DEVICE_NAME: %s (%ld)\n", name, out_size);

      char vendor[32] = {0};
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, sizeof(vendor), vendor,
                         &out_size));
      printf("\tCL_DEVICE_VENDOR: %s (%ld)\n", vendor, out_size);

      char version[32] = {0};
      CL(clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, sizeof(version),
                         version, &out_size));
      printf("\tCL_DRIVER_VERSION: %s (%ld)\n", version, out_size);

      char profile[32] = {0};
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_PROFILE, sizeof(profile),
                         profile, &out_size));
      printf("\tCL_DEVICE_PROFILE: %s (%ld)\n", profile, out_size);

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, sizeof(version),
                         version, &out_size));
      printf("\tCL_DEVICE_VERSION: %s (%ld)\n", version, out_size);

      CL(clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION,
                         sizeof(version), version, &out_size));
      printf("\tCL_DEVICE_OPENCL_C_VERSION: %s (%ld)\n", version, out_size);

      char extensions[512] = {0};
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_EXTENSIONS, sizeof(extensions),
                         extensions, &out_size));
      printf("\tCL_DEVICE_EXTENSIONS: %s (%ld)\n", extensions, out_size);

      size_t printf_buffer_size = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_PRINTF_BUFFER_SIZE,
                         sizeof(size_t), &printf_buffer_size, &out_size));
      printf("\tCL_DEVICE_PRINTF_BUFFER_SIZE: %ld\n", printf_buffer_size);

      cl_bool user_sync = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_INTEROP_USER_SYNC,
                         sizeof(cl_bool), &user_sync, &out_size));
      printf("\tCL_DEVICE_PREFERRED_INTEROP_USER_SYNC: %d\n", user_sync);

      cl_device_id parent_device = NULL;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_PARENT_DEVICE,
                         sizeof(cl_device_id), &parent_device, &out_size));
      printf("\tCL_DEVICE_PARENT_DEVICE: %p\n", parent_device);

      cl_uint max_subdevices = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_PARTITION_MAX_SUB_DEVICES,
                         sizeof(cl_uint), &max_subdevices, &out_size));
      printf("\tCL_DEVICE_PARTITION_MAX_SUB_DEVICES: %u\n", max_subdevices);

      cl_uint ref_count = 0;
      CL(clGetDeviceInfo(devices[j], CL_DEVICE_REFERENCE_COUNT, sizeof(cl_uint),
                         &ref_count, &out_size));
      printf("\tCL_DEVICE_REFERENCE_COUNT: %u\n", ref_count);
    }
  }

  return result;
}
