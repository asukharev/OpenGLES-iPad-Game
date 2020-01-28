//
//  HUD.h
//  Asteroids
//
//  Created by Alexander Sukharev on 20.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface HUD : UIView
{
    UILabel *_scoreLabel;
    UILabel *_livesLabel;
}

- (void)update;

@end
