#import "renderer.h"

#import <Foundation/Foundation.h>

@implementation Renderer : NSObject
- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size {
  NSLog(@"Drawable size will change");
}
- (void)drawInMTKView:(MTKView *)view {
  NSLog(@"Rendering");
  MTLRenderPassDescriptor *renderPassDescriptor =
      view.currentRenderPassDescriptor;
  if (renderPassDescriptor == nil) {
    return;
  }

  id<MTLCommandQueue> commandQueue = [view.device newCommandQueue];
  id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];

  id<MTLRenderCommandEncoder> commandEncoder =
      [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];

  [commandEncoder endEncoding];

  id<MTLDrawable> drawable = view.currentDrawable;
  [commandBuffer presentDrawable:drawable];
  [commandBuffer commit];
  NSLog(@"done");
}
@end
