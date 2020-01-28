//
//  AppDelegate.m
//  OpenGL
//
//  Created by Alexander Sukharev on 27.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#import "AppDelegate.h"
#import "RootNavigationController.h"
#import "RootViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];

    RootViewController *rootViewController = [[RootViewController new] autorelease];
    RootNavigationController *rootNavigationController = [[[RootNavigationController alloc] initWithRootViewController:rootViewController] autorelease];
    [rootNavigationController.navigationBar setHidden:YES];

    self.window.rootViewController = rootNavigationController;
    [self.window makeKeyAndVisible];

    return YES;
}

- (void) applicationDidFinishLaunching:(UIApplication *)application
{
    //	[_glView startAnimation];
}

- (void) applicationWillResignActive:(UIApplication *)application
{
    //	[_glView stopAnimation];
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
    //    [_glView toggleDisplayLink];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    //	[_glView stopAnimation];
}

@end
