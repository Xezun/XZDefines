//
//  ViewController.m
//  Example
//
//  Created by Xezun on 2023/7/27.
//

#import "ViewController.h"
@import XZDefines;

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSLog(@"%s", __PRETTY_FUNCTION__);
    
    NSURL *url = XZOpt([NSURL URLWithString:@"mocoa://ios.com"], @"https://xezun.com/1");
    NSLog(@"url: %@", url);
}


@end
