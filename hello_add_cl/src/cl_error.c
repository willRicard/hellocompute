#include "cl_error.h"

#include <stdio.h>

void hello_cl_handle_error(cl_int result) {
  if (result == CL_INVALID_VALUE) {
    fprintf(stderr, "CL_INVALID_VALUE\n");
  } else if (result == CL_OUT_OF_HOST_MEMORY) {
    fprintf(stderr, "CL_OUT_OF_HOST_MEMORY\n");
  } else if (result == CL_INVALID_PLATFORM) {
    fprintf(stderr, "CL_INVALID_PLATFORM\n");
  } else if (result == CL_INVALID_DEVICE) {
    fprintf(stderr, "CL_INVALID_DEVICE\n");
  } else if (result == CL_INVALID_DEVICE_TYPE) {
    fprintf(stderr, "CL_INVALID_DEVICE_TYPE\n");
  } else if (result == CL_DEVICE_NOT_FOUND) {
    fprintf(stderr, "CL_DEVICE_NOT_FOUND\n");
  } else if (result == CL_DEVICE_NOT_AVAILABLE) {
    fprintf(stderr, "CL_DEVICE_NOT_AVAILABLE\n");
  } else if (result == CL_OUT_OF_RESOURCES) {
    fprintf(stderr, "CL_OUT_OF_RESOURCES\n");
  } else if (result == CL_INVALID_PROPERTY) {
    fprintf(stderr, "CL_INVALID_PROPERTY\n");
  } else if (result == CL_INVALID_CONTEXT) {
    fprintf(stderr, "CL_INVALID_CONTEXT\n");
  } else if (result == CL_INVALID_QUEUE_PROPERTIES) {
    fprintf(stderr, "CL_INVALID_QUEUE_PROPERTIES\n");
  } else if (result == CL_INVALID_COMMAND_QUEUE) {
    fprintf(stderr, "CL_INVALID_COMMAND_QUEUE\n");
  } else if (result == CL_INVALID_BUFFER_SIZE) {
    fprintf(stderr, "CL_INVALID_BUFFER_SIZE\n");
  } else if (result == CL_INVALID_HOST_PTR) {
    fprintf(stderr, "CL_INVALID_HOST_PTR\n");
  } else if (result == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
    fprintf(stderr, "CL_MEM_OBJECT_ALLOCATION_FAILURE\n");
  } else if (result == CL_INVALID_MEM_OBJECT) {
    fprintf(stderr, "CL_INVALID_MEM_OBJECT\n");
  } else if (result == CL_INVALID_EVENT_WAIT_LIST) {
    fprintf(stderr, "CL_INVALID_EVENT_WAIT_LIST\n");
  } else if (result == CL_MISALIGNED_SUB_BUFFER_OFFSET) {
    fprintf(stderr, "CL_MISALIGNED_SUB_BUFFER_OFFSET\n");
  } else if (result == CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST) {
    fprintf(stderr, "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");
  } else if (result == CL_INVALID_OPERATION) {
    fprintf(stderr, "CL_INVALID_OPERATION\n");
  } else if (result == CL_INVALID_PROGRAM) {
    fprintf(stderr, "CL_INVALID_PROGRAM\n");
  } else if (result == CL_INVALID_BINARY) {
    fprintf(stderr, "CL_INVALID_BINARY\n");
  } else if (result == CL_INVALID_BUILD_OPTIONS) {
    fprintf(stderr, "CL_INVALID_BUILD_OPTIONS\n");
  } else if (result == CL_COMPILER_NOT_AVAILABLE) {
    fprintf(stderr, "CL_COMPILER_NOT_AVAILABLE\n");
  } else if (result == CL_BUILD_PROGRAM_FAILURE) {
    fprintf(stderr, "CL_BUILD_PROGRAM_FAILURE\n");
  } else if (result == CL_INVALID_PROGRAM_EXECUTABLE) {
    fprintf(stderr, "CL_INVALID_PROGRAM_EXECUTABLE\n");
  } else if (result == CL_INVALID_KERNEL_NAME) {
    fprintf(stderr, "CL_INVALID_KERNEL_NAME\n");
  } else if (result == CL_INVALID_KERNEL_DEFINITION) {
    fprintf(stderr, "CL_INVALID_KERNEL_DEFINITION\n");
  } else if (result == CL_INVALID_KERNEL) {
    fprintf(stderr, "CL_INVALID_KERNEL\n");
  } else if (result == CL_INVALID_ARG_INDEX) {
    fprintf(stderr, "CL_INVALID_ARG_INDEX\n");
  } else if (result == CL_INVALID_ARG_VALUE) {
    fprintf(stderr, "CL_INVALID_ARG_VALUE\n");
  } else if (result == CL_INVALID_ARG_SIZE) {
    fprintf(stderr, "CL_INVALID_ARG_SIZE\n");
  }
}
