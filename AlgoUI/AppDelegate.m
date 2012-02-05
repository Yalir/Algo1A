//
//  AppDelegate.m
//  AlgoUI
//
//  Created by Lucas Soltic on 05/02/12.
//  Copyright (c) 2012 Yalir. All rights reserved.
//

#import "AppDelegate.h"
#import "parser.h"
#import "resolution.h"
#import "affichage.h"
#import "donnees.h"

@implementation AppDelegate

@synthesize window = _window;
static NSFileHandle *pipeReadHandle;
static NSFileHandle *pipeReadHandle2;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	// Insert code here to initialize your application
	[NSApp setDelegate:self];
	[self.window center];
	
	NSPipe *pipe = [NSPipe pipe] ;
	pipeReadHandle = [pipe fileHandleForReading] ;
	dup2([[pipe fileHandleForWriting] fileDescriptor], fileno(stdout)) ;
	
	[[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(handleStdout:) name: NSFileHandleReadCompletionNotification object: pipeReadHandle] ;
	[pipeReadHandle readInBackgroundAndNotify] ;
	
	NSPipe *pipe2 = [NSPipe pipe] ;
	pipeReadHandle2 = [pipe2 fileHandleForReading] ;
	dup2([[pipe2 fileHandleForWriting] fileDescriptor], fileno(stderr)) ;
	
	[[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(handleStderr:) name: NSFileHandleReadCompletionNotification object: pipeReadHandle2] ;
	[pipeReadHandle2 readInBackgroundAndNotify] ;
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app
{
	return YES;
}

- (IBAction)hitSolveButton:(id)sender
{
	ResolutionErr err;
	Solutions s;
	NSString *eq = [eqField stringValue];
	
	// Clean result view
	[[[resView textStorage] mutableString] setString:@""];
	
	
	Systeme t = creer_systeme_depuis_texte([eq cStringUsingEncoding:NSUTF8StringEncoding]);
	
	
	if (t)
	{
		printf("Système: ");
		afficher_systeme(t);
		
		s = traiter_systeme(t, &err);
		
		if (s)
		{
			afficher_solutions(s);
			destroy_solutions(s);
		}
		else
		{
			if (err == ResolutionErrImpossible)
				puts("Système insoluble.");
			else
				puts("Système invalide.");
		}
		
		destroy_systeme(t);
	}
	else
	{
		puts("Erreur à la création du système");
	}
}

- (void)handleStdout:(NSNotification *)notification
{
	[pipeReadHandle readInBackgroundAndNotify] ;
	NSString *str = [[NSString alloc] initWithData: [[notification userInfo] objectForKey: NSFileHandleNotificationDataItem] encoding: NSUTF8StringEncoding] ;
	
	[[[resView textStorage] mutableString] appendString: str];
	[resView setTextColor:[NSColor blackColor]];
}

- (void)handleStderr:(NSNotification *)notification
{
	[pipeReadHandle2 readInBackgroundAndNotify] ;
	NSString *str = [[NSString alloc] initWithData: [[notification userInfo] objectForKey: NSFileHandleNotificationDataItem] encoding: NSUTF8StringEncoding] ;
	
	[[[resView textStorage] mutableString] appendString: str];
	[resView setTextColor:[NSColor redColor]];
}

@end
