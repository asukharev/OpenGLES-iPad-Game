//
//  OpenGLView.m
//  Asteroids
//
//  Created by Alexander Sukharev on 17.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import "OpenGLView.h"
#include "Common.h"

const CGFloat FPS = 1.0f/30.0f;

@interface OpenGLView()
{
    CADisplayLink * _displayLink;
}

- (void)setupLayer;
- (void)setupContext;
- (void)doTimer:(NSTimer *)timer;

@end

@implementation OpenGLView

@synthesize delegate;

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (void)setupLayer
{
    _eaglLayer = (CAEAGLLayer *)self.layer;

    // Make CALayer visibale
    _eaglLayer.opaque = YES;

    // Set drawable properties
    _eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                     [NSNumber numberWithBool:NO],
                                     kEAGLDrawablePropertyRetainedBacking,
                                     kEAGLColorFormatRGBA8,
                                     kEAGLDrawablePropertyColorFormat,
                                     nil];
}

- (void)setupContext
{
    // Set OpenGL version, here is OpenGL ES 2.0
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context)
    {
        NSLog(@" >> Error: Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }

    // Set OpenGL context
    if (![EAGLContext setCurrentContext:_context])
    {
        _context = nil;
        NSLog(@" >> Error: Failed to set current OpenGL context");
        exit(1);
    }

    _wscale = self.contentScaleFactor;
}

#pragma mark -

- (void)toggleDisplayLink
{
    if (_displayLink == nil)
    {
        _displayLink = [CADisplayLink displayLinkWithTarget:self
                                                   selector:@selector(displayLinkCallback:)];
        [_displayLink setFrameInterval:1];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                           forMode:NSDefaultRunLoopMode];

        [_timer invalidate];
        [_timer release];
        _timer = [[NSTimer scheduledTimerWithTimeInterval:FPS
                                                   target:self
                                                 selector:@selector(doTimer:)
                                                 userInfo:nil
                                                  repeats:YES] retain];
    }
    else
    {
        [_timer invalidate];
        [_displayLink invalidate];
        [_displayLink removeFromRunLoop:[NSRunLoop currentRunLoop]
                                forMode:NSDefaultRunLoopMode];
        _displayLink = nil;
    }
}

- (void)doTimer:(NSTimer *)timer
{
    time_t ctime = time(0);
    if (difftime(ctime, _time) > 0)
    {
        if ([self.delegate conformsToProtocol:@protocol(OpenGLViewDelegate)])
        {
            [self.delegate glViewDidUpdate:self];
        }
    }
    timerCallback();
}

- (void)displayLinkCallback:(CADisplayLink*)displayLink
{
    if (_context == nil)
    {
        return;
    }

    render();

    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

#pragma mark -

- (void)layoutSubviews
{
    [EAGLContext setCurrentContext:_context];
    glUseProgram(_programHandle);
    glDestoryBuffers();

    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
    glSetupBuffers();
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        _waspect = frame.size.width / frame.size.height;
        _wwidth = frame.size.width;
        _wheight = frame.size.height;

        [self setupLayer];
        [self setupContext];

        glSetupProgram();
        glSetupTextures();
        initGame();
    }
    return self;
}

- (void)dealloc
{
    glCleanup();
    [_timer invalidate];
    [_timer release];
    [_context release];
    [super dealloc];
}

@end
