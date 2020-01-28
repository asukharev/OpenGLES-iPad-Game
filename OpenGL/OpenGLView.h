//
//  OpenGLView.h
//  Asteroids
//
//  Created by Alexander Sukharev on 17.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>

@class OpenGLView;

@protocol OpenGLViewDelegate <NSObject>
- (void)glViewDidUpdate:(OpenGLView*)glView;
@end

@interface OpenGLView : UIView
{
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    NSTimer *_timer;
}

@property (nonatomic, assign) id<OpenGLViewDelegate> delegate;

- (void)toggleDisplayLink;

@end
