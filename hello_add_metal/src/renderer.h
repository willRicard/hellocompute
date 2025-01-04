#import <MetalKit/MTKView.h>
#import <MetalKit/MetalKit.h>

@interface Renderer : NSObject <MTKViewDelegate>
- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size;
- (void)drawInMTKView:(MTKView *)view;
@end
