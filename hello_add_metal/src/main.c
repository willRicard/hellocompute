#include <stdio.h>
#include <stdlib.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "setup_metal.h"

static GLFWwindow *window = NULL;

void on_error(int error_code, const char *error_description) {
  fprintf(stderr, "%s\n", error_description);
  exit(EXIT_FAILURE);
}

static void cleanup() {
  if (window != NULL) {
    glfwDestroyWindow(window);
    window = NULL;
  }
  glfwTerminate();
}

int main(void) {
  glfwSetErrorCallback(on_error);
  if (!glfwInit()) {
    return EXIT_FAILURE;
  }

  atexit(cleanup);

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window = glfwCreateWindow(640, 480, "hello_add_metal", NULL, NULL);
  if (window == NULL) {
    exit(EXIT_FAILURE);
  }

  struct objc_object *nswin = glfwGetCocoaWindow(window);
  setup_metal(nswin);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  cleanup();

  return EXIT_SUCCESS;
}
