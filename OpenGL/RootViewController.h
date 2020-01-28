//
//  RootViewController.h
//  Asteroids
//
//  Created by Alexander Sukharev on 20.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "JoyStickView.h"
#import "OpenGLView.h"

@class HUD;

@interface RootViewController : UIViewController <JoyStickViewDelegate, OpenGLViewDelegate>
{
    HUD *_hud;
}

@end
