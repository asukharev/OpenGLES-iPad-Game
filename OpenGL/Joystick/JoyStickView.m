//
//  JoyStickView.m
//  JoyStick
//
//  Created by Alexander Sukharev on 22.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import "JoyStickView.h"

#define STICK_CENTER_TARGET_POS_LEN 20.0f

@implementation JoyStickView

@synthesize delegate;
@synthesize placement;
@synthesize feedback = _feedback;

#pragma mark -

- (void)initStick
{
    _imgStickNormal = [[UIImage imageNamed:@"stick_normal.png"] retain];
    _imgStickHold = [[UIImage imageNamed:@"stick_hold.png"] retain];

    UIImageView *stickViewBase = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"stick_base.png"]] autorelease];
    [self addSubview:stickViewBase];

    _stickView = [[UIImageView alloc] initWithImage:_imgStickNormal];
    [self addSubview:_stickView];

    _mCenter.x = 64.0f;
    _mCenter.y = 64.0f;
}

- (id)init
{
    self = [super initWithFrame:CGRectMake(0.0f, 0.0f, 128.0f, 128.0f)];
    if (self)
    {
        [self initStick];
    }
    return self;
}

- (void)dealloc
{
    [_timer invalidate];
    [_timer release];
    [_stickView release];
    [_imgStickNormal release];
    [_imgStickHold release];
    [super dealloc];
}

- (void)didMoveToSuperview
{
    CGRect rect = self.frame;
    CGRect super_rect = self.superview.frame;
    if (placement == JoystickPlacementLeft)
    {
        rect.origin.x = 10.0f;
    }
    else
    {
        rect.origin.x = CGRectGetWidth(super_rect) - CGRectGetWidth(rect) - 10.0f;;
    }
    rect.origin.y = CGRectGetHeight(super_rect) - CGRectGetHeight(rect) - 10.0f;
    self.frame = CGRectIntegral(rect);
}

#pragma mark -

- (void)notifyDir:(CGPoint)dir
{
    if ([self.delegate conformsToProtocol:@protocol(JoyStickViewDelegate)])
    {
        [self.delegate joystickUpdate:self dir:dir];
    }
}

- (void)stickMoveTo:(CGPoint)deltaToCenter
{
    CGRect fr = _stickView.frame;
    fr.origin.x = deltaToCenter.x;
    fr.origin.y = deltaToCenter.y;
    _stickView.frame = fr;
}

- (void)touchEvent:(NSSet *)touches
{
    if ([touches count] != 1)
        return;
    
    UITouch *touch = [touches anyObject];
    UIView *view = [touch view];
    if (view != self)
        return;

    CGPoint touchPoint = [touch locationInView:view];
    CGPoint dtarget;
    _dir.x = touchPoint.x - _mCenter.x;
    _dir.y = touchPoint.y - _mCenter.y;
    double len = sqrt(_dir.x * _dir.x + _dir.y * _dir.y);

    if (len < 10.0 && len > -10.0)
    {
        // center pos
        dtarget.x = 0.0;
        dtarget.y = 0.0;
        _dir.x = 0;
        _dir.y = 0;
    }
    else
    {
        double len_inv = (1.0 / len);
        _dir.x *= len_inv;
        _dir.y *= len_inv;
        dtarget.x = _dir.x * STICK_CENTER_TARGET_POS_LEN;
        dtarget.y = _dir.y * STICK_CENTER_TARGET_POS_LEN;
    }
    [self stickMoveTo:dtarget];
    if (_feedback == JoystickPlacementOnce)
    {
        [self notifyDir:_dir];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    _stickView.image = _imgStickHold;
    [self touchEvent:touches];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self touchEvent:touches];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    _stickView.image = _imgStickNormal;
    CGPoint dtarget;
    _dir.x = dtarget.x = 0.0;
    _dir.y = dtarget.y = 0.0;
    [self stickMoveTo:dtarget];
    if (_feedback == JoystickPlacementOnce)
    {
        [self notifyDir:_dir];
    }
}

- (void)setFeedback:(JoystickFeedback)feedback
{
    _feedback = feedback;

    if (feedback == JoystickFeedbackRepeat)
    {
        [_timer invalidate];
        [_timer release];
        _timer = [[NSTimer scheduledTimerWithTimeInterval:1.0f/30.0f
                                                  target:self
                                                selector:@selector(doTimer:)
                                                userInfo:nil
                                                 repeats:YES] retain];
    }
    else if (feedback == JoystickPlacementOnce || _feedback != feedback)
    {
        [_timer invalidate];
    }
}

- (void)doTimer:(NSTimer *)timer
{
    if (_dir.x != 0.0f || _dir.y != 0.0f)
    {
        [self notifyDir:_dir];
    }
}

@end
