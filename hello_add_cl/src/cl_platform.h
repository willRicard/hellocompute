#ifndef HELLO_CL_PLATFORM_H
#define HELLO_CL_PLATFORM_H

#include <OpenCL/cl.h>

cl_int hello_cl_platform_choose(cl_platform_id *platform, cl_device_id *device);

#endif // HELLO_CL_PLATFORM_H
