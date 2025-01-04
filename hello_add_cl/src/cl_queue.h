#ifndef HELLO_CL_QUEUE_H
#define HELLO_CL_QUEUE_H

#include <OpenCL/cl.h>

cl_int hello_cl_queue_create(cl_context context, cl_device_id device,
                             cl_command_queue *queue);

void hello_cl_queue_destroy(cl_command_queue *queue);

#endif // HELLO_CL_QUEUE_H
