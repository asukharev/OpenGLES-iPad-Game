//
//  JoyStickView.h
//  JoyStick
//
//  Created by Alexander Sukharev on 22.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum JoystickPlacement {
	JoystickPlacementLeft,
    JoystickPlacementRight
} JoystickPlacement;

typedef enum JoystickFeedback {
    JoystickPlacementOnce,
	JoystickFeedbackRepeat
} JoystickFeedback;

@class JoyStickView;

@protocol JoyStickViewDelegate <NSObject>
- (void)joystickUpdate:(JoyStickView *)joystick dir:(CGPoint)direction;
@end

@interface JoyStickView : UIView
{
    UIImageView *_stickView;
    UIImage *_imgStickNormal;
    UIImage *_imgStickHold;
    CGPoint _mCenter;
    CGPoint _dir;
    NSTimer *_timer;
    JoystickFeedback _feedback;
}

@property (nonatomic, assign) id<JoyStickViewDelegate> delegate;
@property (nonatomic, assign) JoystickPlacement placement;
@property (nonatomic, assign) JoystickFeedback feedback;

@end
