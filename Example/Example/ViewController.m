//
//  ViewController.m
//  Example
//
//  Created by Xezun on 2023/7/27.
//

#import "ViewController.h"
@import XZDefines;

@import ObjectiveC;

@interface ViewController ()

@property (nonatomic, strong) void (^block)(void);
@end


@interface Bar : NSObject

@end


UIColor *rgba(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha) XZATTR_OVERLOAD {
    return [UIColor colorWithRed:red / 255.0 green:green / 255.0 blue:blue / 255.0 alpha:alpha / 255.0];
}

UIColor *rgba(UInt32 value) XZATTR_OVERLOAD {
    return rgba(value >> 24, (value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF);
}

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSLog(@"%s", __PRETTY_FUNCTION__);
    
    NSURL *url = asNonEmpty([NSURL URLWithString:@"mocoa://ios.com"], [NSURL URLWithString:@"https://xezun.com/1"]);
    NSLog(@"url: %@", url);

    NSLog(@"%@", rgba(0xAABBCCDD));
    NSLog(@"%@", rgba(0xAA, 0xBB, 0xCC, 0xDD));
    
    // NSString *foo; NSDictionary *bar;
    
    NSString *aString = @"1";
    if (isNonEmpty(aString)) {
        NSLog(@"aString is a non-emtpy string");
    }
    NSArray *anArray = @[@"1"];
    if (isNonEmpty(anArray)) {
        NSLog(@"anArray is a non-emtpy array");
    }
    
    id foo;
    if (isNonEmpty((NSString *)foo)) {
        NSLog(@"foo is a non-emtpy string");
    }
    
    if (isNonEmpty((NSArray *)foo)) {
        NSLog(@"foo is a non-emtpy array");
    }
    
    if (isNonEmpty((NSDictionary *)foo)) {
        NSLog(@"foo is a non-emtpy NSDictionary");
    }
    
    if (isNonEmpty((Bar *)foo)) {
        NSLog(@"foo is a Bar type value");
    }
    
    NSDictionary *dict;
    
    NSString *name = dict[@"name"];
    if (![name isKindOfClass:NSString.class] || name.length == 0) {
        name = @"Visitor";
    }
    
    name = asNonEmpty((NSString *)dict[@"name"], @"Visitor");
    
    
}


@end
