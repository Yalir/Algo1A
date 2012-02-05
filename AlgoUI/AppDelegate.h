//
//  AppDelegate.h
//  AlgoUI
//
//  Created by Lucas Soltic on 05/02/12.
//  Copyright (c) 2012 Yalir. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
	IBOutlet NSTextField *eqField;
	IBOutlet NSTextView *resView;
}

@property (assign) IBOutlet NSWindow *window;

- (IBAction)hitSolveButton:(id)sender;

@end
