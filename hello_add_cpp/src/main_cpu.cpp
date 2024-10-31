#include <iostream>
#include <chrono>
#include <math.h>

void add(int n, float *x, float *y) {
  for (int i = 0; i < n; ++i) {
    y[i] = x[i] + y[i];
  }
}

int main(int argc, char **argv) {
  int N = 1 << 20;

  float *x = new float[N];
  float *y = new float[N];

  for (int i = 0; i < N; ++i) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  auto start = std::chrono::high_resolution_clock::now();
  add(N, x, y);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
  std::cout << 1000.0 * duration.count() << " ms" << std::endl;

  float maxError = 0.0f;
  for (int i = 0; i < N; ++i) {
    maxError = fmax(maxError, fabs(y[i] - 3.0f));
  }
  std::cout << "Max error: " << maxError << std::endl;

  delete[] x;
  delete[] y;

  return 0;
}
