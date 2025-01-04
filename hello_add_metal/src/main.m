#import <Metal/Metal.h>

#include <math.h>
#include <time.h>

#define N (1 << 20)

int main(int argc, const char *argv[]) {
  NSLog(@"Hello, world!");

  id<MTLDevice> device = MTLCreateSystemDefaultDevice();
  NSLog(@"Device Name: %@", device.name);

  MTLArchitecture *arch = device.architecture;
  NSLog(@"Device Architecture: %@", arch.name);

  MTLSize size = device.maxThreadsPerThreadgroup;

  NSLog(@"Max thread group size: (%lu, %lu, %lu)", size.width, size.height,
        size.depth);

  NSLog(@"Current allocated size: %lu", device.currentAllocatedSize);

  // Create default Metal library
  NSLog(@"Loading ./add.metallib");
  NSURL *url = [[NSURL alloc] initWithString:@"./add.metallib"];
  NSError *error = [NSError alloc];
  id<MTLLibrary> library = [device newLibraryWithURL:url error:&error];
  if (library == nil) {
    NSLog(@"Failed to create default library.");
    NSLog(@"%@", error);
    return 1;
  }

  id<MTLFunction> addFunction = [library newFunctionWithName:@"add"];
  if (addFunction == nil) {
    NSLog(@"Failed to find the add function.");
    return 1;
  }

  id<MTLComputePipelineState> pipeline =
      [device newComputePipelineStateWithFunction:addFunction error:&error];
  if (pipeline == nil) {
    NSLog(@"Failed to create Metal compute pipeline.");
    NSLog(@"%@", error);
    return 1;
  }

  id<MTLCommandQueue> queue = [device newCommandQueue];
  if (queue == nil) {
    NSLog(@"Failed to create Metal command queue.");
    return 1;
  }

  NSUInteger bufferSize = N * sizeof(float);

  id<MTLBuffer> buf_x =
      [device newBufferWithLength:bufferSize
                          options:MTLResourceStorageModeShared];
  if (buf_x == nil) {
    NSLog(@"Failed to create Metal buffer.");
    return 1;
  }

  id<MTLBuffer> buf_y =
      [device newBufferWithLength:bufferSize
                          options:MTLResourceStorageModeShared];
  if (buf_y == nil) {
    NSLog(@"Failed to create Metal buffer.");
    return 1;
  }

  float *ptr_x = buf_x.contents;
  float *ptr_y = buf_y.contents;
  for (int i = 0; i < N; ++i) {
    ptr_x[i] = 1.0f;
    ptr_y[i] = 2.0f;
  }

  clock_t start = clock();
  id<MTLCommandBuffer> commandBuffer = [queue commandBuffer];
  if (commandBuffer == nil) {
    NSLog(@"Failed to create Metal command buffer.");
    return 1;
  }

  id<MTLComputeCommandEncoder> computeEncoder =
      [commandBuffer computeCommandEncoder];
  if (computeEncoder == nil) {
    NSLog(@"Failed to create Metal compute command encoder.");
    return 1;
  }

  [computeEncoder setComputePipelineState:pipeline];
  [computeEncoder setBuffer:buf_x offset:0 atIndex:0];
  [computeEncoder setBuffer:buf_y offset:0 atIndex:1];

  MTLSize gridSize = MTLSizeMake(N, 1, 1);

  NSUInteger threadGroupSize = pipeline.maxTotalThreadsPerThreadgroup;
  if (threadGroupSize > N) {
    threadGroupSize = N;
  }

  MTLSize groupSize = MTLSizeMake(threadGroupSize, 1, 1);

  [computeEncoder dispatchThreads:gridSize threadsPerThreadgroup:groupSize];
  [computeEncoder endEncoding];

  [commandBuffer commit];
  [commandBuffer waitUntilCompleted];
  clock_t end = clock();
  NSLog(@"%f", (double)(end - start) / CLOCKS_PER_SEC);

  float maxError = 0.0f;
  for (int i = 0; i < N; ++i) {
    maxError = fmax(maxError, fabs(ptr_x[i] - 3.0f));
  }

  NSLog(@"Max error: %f", maxError);

  NSLog(@"All OK");
}
