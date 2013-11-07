//
//  airplanedemoAppController.h
//  airplanedemo
//
//  Created by Leo Lin on 11/8/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

