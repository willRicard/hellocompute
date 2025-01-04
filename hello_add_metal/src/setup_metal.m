#import <Cocoa/Cocoa.h>

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

#import "renderer.h"

void setup_metal(NSWindow *window) {
  @autoreleasepool {
    NSRect bounds = [[window contentView] bounds];
    MTKView *view =
        [[MTKView alloc] initWithFrame:bounds
                                device:MTLCreateSystemDefaultDevice()];

    Renderer *renderer = [[Renderer alloc] init];
    view.clearColor = MTLClearColorMake(0.0, 0.5, 1.0, 1.0);
    view.enableSetNeedsDisplay = YES;
    view.delegate = renderer;

    [[window contentView] addSubview:view];
  }
}
