//
//  HUD.m
//  Asteroids
//
//  Created by Alexander Sukharev on 20.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import "HUD.h"
#include "Common.h"

@implementation HUD

- (void)dealloc
{
    [_scoreLabel release];
    [_scoreLabel release];
    [super dealloc];
}

#pragma mark - Touch events

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        _scoreLabel = [[UILabel alloc] initWithFrame:CGRectMake(10.0f, 10.0f, 100.0f, 34.0f)];
        _scoreLabel.backgroundColor = [UIColor clearColor];
        _scoreLabel.textColor = [UIColor whiteColor];
//        _scoreLabel.text = [NSString stringWithFormat:@"Score: %d", _score];
        [self addSubview:_scoreLabel];

        _livesLabel = [[UILabel alloc] initWithFrame:CGRectMake(CGRectGetWidth(frame)-100.0f, 10.0f, 100.0f, 34.0f)];
        _livesLabel.backgroundColor = [UIColor clearColor];
        _livesLabel.textColor = [UIColor whiteColor];
//        _livesLabel.text = [NSString stringWithFormat:@"Lives: %d", _lives];
        [self addSubview:_livesLabel];
    }
    return self;
}

- (void)update
{
//    _scoreLabel.text = [NSString stringWithFormat:@"Score: %d", _score];
//    _livesLabel.text = [NSString stringWithFormat:@"Lives: %d", _lives];
}

@end
