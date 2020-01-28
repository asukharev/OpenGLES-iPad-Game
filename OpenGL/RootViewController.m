//
//  RootViewController.m
//  Asteroids
//
//  Created by Alexander Sukharev on 20.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import "RootViewController.h"
#import "OpenGLView.h"
#import "HUD.h"
#include "Common.h"

@interface RootViewController ()

@end

@implementation RootViewController

- (void)dealloc
{
    [_hud release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    CGRect rect;
    if ([[[UIDevice currentDevice] name] hasPrefix:@"iPad"])
    {
        rect = CGRectMake(0.0f, 0.0f, 1024.0f, 768.0f);
    }
    else
    {
        rect = CGRectMake(0.0f, 0.0f, 568, 320.0f);
    }
    self.view.frame = rect;

    OpenGLView *glView = [[[OpenGLView alloc] initWithFrame:rect] autorelease];
    glView.delegate = self;
    [self.view addSubview:glView];
    [glView toggleDisplayLink];

    _hud = [[HUD alloc] initWithFrame:rect];
    [self.view addSubview:_hud];

    JoyStickView *joystickLeft = [[JoyStickView new] autorelease];
    joystickLeft.placement = JoystickPlacementLeft;
    joystickLeft.feedback = JoystickFeedbackRepeat;
    joystickLeft.delegate = self;
    [self.view addSubview:joystickLeft];

    JoyStickView *joystickRight = [[JoyStickView new] autorelease];
    joystickRight.placement = JoystickPlacementRight;
    joystickRight.feedback = JoystickFeedbackRepeat;
    joystickRight.delegate = self;
    [self.view addSubview:joystickRight];
}

- (void)joystickUpdate:(JoyStickView *)joystick dir:(CGPoint)direction
{
    if (joystick.placement == JoystickPlacementLeft)
    {
        leftStick(direction.x, direction.y);
    }
    else if (joystick.placement == JoystickPlacementRight)
    {
        rightStick(direction.x, direction.y);
    }
}

- (void)glViewDidUpdate:(OpenGLView*)glView
{
    [_hud update];
}

@end
