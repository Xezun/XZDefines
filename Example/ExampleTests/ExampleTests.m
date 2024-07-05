//
//  ExampleTests.m
//  ExampleTests
//
//  Created by Xezun on 2023/7/27.
//

#import <XCTest/XCTest.h>
@import XZDefines;

@interface Foo : NSObject
- (void)foo;
- (NSString *)speakFoo;
- (NSString *)speakTwo;
@end

@interface Bar : Foo
- (void)bar;
- (NSString *)speakBar;
- (NSString *)speakTwo;
- (NSString *)exchange_speakTwo;
@end

@interface FooBar : NSObject
- (NSString *)speakNew;

- (NSString *)speakFoo;
- (NSString *)override_speakFoo;
- (NSString *)exchange_speakFoo;

- (NSString *)speakBar;
- (NSString *)override_speakBar;
- (NSString *)exchange_speakBar;

- (NSString *)speakTwo;
- (NSString *)override_speakTwo;
- (NSString *)exchange_speakTwo;
@end

@interface ExampleTests : XCTestCase

@end

@implementation ExampleTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    
}


- (void)testXZDefer {
    BOOL __block isOpen = NO;
    {
        isOpen = YES;
        NSLog(@"The database state: %@", isOpen ? @"open" : @"close");
        defer(^{
            isOpen = NO;
            NSLog(@"The database state: %@", isOpen ? @"open" : @"close");
        });
        
        NSLog(@"Insert data");
        NSLog(@"Update data");
        NSLog(@"Search data");
    }
    XCTAssert(isOpen == NO);
}

- (void)testXZEmpty {
    {
        NSString *aString = nil;
        XCTAssert(isNonEmpty(aString) == NO);
        
        aString = (id)NSNull.null;
        XCTAssert(isNonEmpty(aString) == NO);
        
        aString = @"";
        XCTAssert(isNonEmpty(aString) == NO);
        
        aString = @"String";
        XCTAssert(isNonEmpty(aString) == YES);
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    } {
        NSArray *anArray = nil;
        XCTAssert(isNonEmpty(anArray) == NO);
        
        anArray = (id)NSNull.null;
        XCTAssert(isNonEmpty(anArray) == NO);
        
        anArray = @[];
        XCTAssert(isNonEmpty(anArray) == NO);
        
        anArray = @[@"Array"];
        XCTAssert(isNonEmpty(anArray) == YES);
        
        NSLog(@"isNonEmpty(NSArray *) => Pass");
    } {
        NSMutableArray *aMutableArray = nil;
        XCTAssert(isNonEmpty(aMutableArray) == NO);
        
        aMutableArray = (id)NSNull.null;
        XCTAssert(isNonEmpty(aMutableArray) == NO);
        
        aMutableArray = NSMutableArray.array;
        XCTAssert(isNonEmpty(aMutableArray) == NO);
        
        aMutableArray = [NSMutableArray arrayWithObject:@"MutableArray"];
        XCTAssert(isNonEmpty(aMutableArray) == YES);
        
        NSLog(@"isNonEmpty(NSMutableArray *) => Pass");
    } {
        NSSet *aSet = nil;
        XCTAssert(isNonEmpty(aSet) == NO);
        
        aSet = (id)NSNull.null;
        XCTAssert(isNonEmpty(aSet) == NO);
        
        aSet = NSSet.set;
        XCTAssert(isNonEmpty(aSet) == NO);
        
        aSet = [NSSet setWithObject:@"MutableArray"];
        XCTAssert(isNonEmpty(aSet) == YES);
        
        NSLog(@"isNonEmpty(NSSet *) => Pass");
    } {
        NSMutableSet *aMutableSet = nil;
        XCTAssert(isNonEmpty(aMutableSet) == NO);
        
        aMutableSet = (id)NSNull.null;
        XCTAssert(isNonEmpty(aMutableSet) == NO);
        
        aMutableSet = NSMutableSet.set;
        XCTAssert(isNonEmpty(aMutableSet) == NO);
        
        aMutableSet = [NSMutableSet setWithObject:@"MutableArray"];
        XCTAssert(isNonEmpty(aMutableSet) == YES);
        
        NSLog(@"isNonEmpty(NSMutableSet *) => Pass");
    } {
        NSDictionary *aDictionary = nil;
        XCTAssert(isNonEmpty(aDictionary) == NO);
        
        aDictionary = (id)NSNull.null;
        XCTAssert(isNonEmpty(aDictionary) == NO);
        
        aDictionary = @{ };
        XCTAssert(isNonEmpty(aDictionary) == NO);
        
        aDictionary = @{ @"Key": @"Value" };
        XCTAssert(isNonEmpty(aDictionary) == YES);
        
        NSLog(@"isNonEmpty(NSDictionary *) => Pass");
    } {
        NSMutableDictionary *aMutableDictionary = nil;
        XCTAssert(isNonEmpty(aMutableDictionary) == NO);
        
        aMutableDictionary = (id)NSNull.null;
        XCTAssert(isNonEmpty(aMutableDictionary) == NO);
        
        aMutableDictionary = NSMutableDictionary.dictionary;
        XCTAssert(isNonEmpty(aMutableDictionary) == NO);
        
        aMutableDictionary = [NSMutableDictionary dictionaryWithObject:@"Value" forKey:@"Key"];
        XCTAssert(isNonEmpty(aMutableDictionary) == YES);
        
        NSLog(@"isNonEmpty(NSMutableDictionary *) => Pass");
    } {
        NSNumber *aNumber = nil;
        XCTAssert(isNonEmpty(aNumber) == NO);
        
        aNumber = (id)NSNull.null;
        XCTAssert(isNonEmpty(aNumber) == NO);
        
        aNumber = [NSNumber numberWithBool:false];
        XCTAssert(isNonEmpty(aNumber) == NO);
        
        aNumber = [NSNumber numberWithInt:0];
        XCTAssert(isNonEmpty(aNumber) == NO);
        
        aNumber = [NSNumber numberWithDouble:0];
        XCTAssert(isNonEmpty(aNumber) == NO);
        
        aNumber = [NSNumber numberWithInt:10];
        XCTAssert(isNonEmpty(aNumber) == YES);
        
        NSLog(@"isNonEmpty(NSNumber *) => Pass");
    } {
        UIView *anObject = nil;
        XCTAssert(isNonEmpty(anObject) == NO);
        
        anObject = (id)NSNull.null;
        XCTAssert(isNonEmpty(anObject) == NO);
        
        anObject = [[UIView alloc] init];
        XCTAssert(isNonEmpty(anObject) == YES);
        
        anObject = (id)NSUUID.UUID;
        XCTAssert(isNonEmpty(anObject) == YES);
        
        NSLog(@"isNonEmpty(UIView *) => Pass");
    }
    
    {
        id value = nil;
        XCTAssert([asNonEmpty(value, @"123") isEqualToString:@"123"]);
        XCTAssert(asNonEmpty(value, (NSString *)nil) == nil);
        
        value = @"";
        XCTAssert([asNonEmpty(value, @"123") isEqualToString:@"123"]);
        XCTAssert(asNonEmpty(value, (NSString *)nil) == nil);
        
        value = @"456";
        XCTAssert([asNonEmpty(value, @"123") isEqualToString:@"456"]);
        XCTAssert([asNonEmpty(value, (NSString *)nil) isEqualToString:@"456"]);
    } {
        id value = nil;
        XCTAssert([asNonEmpty(value, @[@"123"]) isEqualToArray:@[@"123"]]);
        XCTAssert(asNonEmpty(value, (NSArray *)nil) == nil);
        
        value = @[];
        XCTAssert([asNonEmpty(value, @[@"123"]) isEqualToArray:@[@"123"]]);
        XCTAssert(asNonEmpty(value, (NSArray *)nil) == nil);
        
        value = @[@"456"];
        XCTAssert([asNonEmpty(value, @[@"123"]) isEqualToArray:@[@"456"]]);
        XCTAssert([asNonEmpty(value, (NSArray *)nil) isEqualToArray:@[@"456"]]);
    } {
        id value = nil;
        XCTAssert([asNonEmpty(value, [NSSet setWithObject:@"123"]) isEqualToSet:[NSSet setWithObject:@"123"]]);
        XCTAssert(asNonEmpty(value, (NSSet *)nil) == nil);
        
        value = [NSSet set];
        XCTAssert([asNonEmpty(value, [NSSet setWithObject:@"123"]) isEqualToSet:[NSSet setWithObject:@"123"]]);
        XCTAssert(asNonEmpty(value, (NSSet *)nil) == nil);
        
        value = [NSSet setWithObject:@"456"];
        XCTAssert([asNonEmpty(value, [NSSet setWithObject:@"123"]) isEqualToSet:[NSSet setWithObject:@"456"]]);
        XCTAssert([asNonEmpty(value, (NSSet *)nil) isEqualToSet:[NSSet setWithObject:@"456"]]);
    } {
        id value = nil;
        XCTAssert([asNonEmpty(value, @{@"Key": @"Value"}) isEqualToDictionary:@{@"Key": @"Value"}]);
        XCTAssert(asNonEmpty(value, (NSDictionary *)nil) == nil);
        
        value = @{};
        XCTAssert([asNonEmpty(value, @{@"Key": @"Value"}) isEqualToDictionary:@{@"Key": @"Value"}]);
        XCTAssert(asNonEmpty(value, (NSDictionary *)nil) == nil);
        
        value = @{@"Key1": @"Value1"};
        XCTAssert([asNonEmpty(value, @{@"Key": @"Value"}) isEqualToDictionary:@{@"Key1": @"Value1"}]);
        XCTAssert([asNonEmpty(value, (NSDictionary *)nil) isEqualToDictionary:@{@"Key1": @"Value1"}]);
    } {
        id value = nil;
        XCTAssert([asNonEmpty(value, @(10)) isEqualToNumber:@(10)]);
        XCTAssert(asNonEmpty(value, (NSNumber *)nil) == nil);
        
        value = [NSNumber numberWithInt:0];
        XCTAssert([asNonEmpty(value, @(10)) isEqualToNumber:@(10)]);
        XCTAssert(asNonEmpty(value, (NSNumber *)nil) == nil);
        
        value = [NSNumber numberWithInt:20];
        XCTAssert([asNonEmpty(value, @(10)) isEqualToNumber:@(20)]);
        XCTAssert([asNonEmpty(value, (NSNumber *)nil) isEqualToNumber:@(20)]);
    } {
        id value = nil;
        NSURL * const defaultValue = [NSURL URLWithString:@"https://www.xezun.com/"];
        XCTAssert([asNonEmpty(value, defaultValue) isEqual:defaultValue]);
        XCTAssert(asNonEmpty(value, (NSURL *)nil) == nil);
        
        value = [NSURL URLWithString:@""];
        XCTAssert([asNonEmpty(value, defaultValue) isEqual:defaultValue]);
        XCTAssert(asNonEmpty(value, (NSURL *)nil) == nil);
        
        value = [NSURL URLWithString:@"http://xzkit.xezun.com/"];
        XCTAssert([asNonEmpty(value, defaultValue) isEqual:[NSURL URLWithString:@"http://xzkit.xezun.com/"]]);
        XCTAssert([asNonEmpty(value, (NSURL *)nil) isEqual:[NSURL URLWithString:@"http://xzkit.xezun.com/"]]);
    }{
        id value = nil;
        UIView * const defaultValue = [[UIView alloc] init];
        
        XCTAssert([asNonEmpty(value, defaultValue) isEqual:defaultValue]);
        XCTAssert(asNonEmpty(value, (UIView *)nil) == nil);
        
        value = NSNull.null;
        XCTAssert([asNonEmpty(value, defaultValue) isEqual:defaultValue]);
        XCTAssert(asNonEmpty(value, (UIView *)nil) == nil);
        
        value = [NSUUID UUID];
        XCTAssert([asNonEmpty(value, defaultValue) isEqual:value]);
        XCTAssert([asNonEmpty(value, (UIView *)nil) isEqual:value]);
    }
}

- (void)testXZUtils {
    XCTAssert(XZVersionStringCompare(@"1.2.3", @"1.2.4") == NSOrderedAscending);
    XCTAssert(XZVersionStringCompare(@"1.2.3", @"1.2") == NSOrderedDescending);
    XCTAssert(XZVersionStringCompare(@"1.2.3", @"1.2.3") == NSOrderedSame);
    XCTAssert(XZVersionStringCompare(@"1.2", @"1.2.3") == NSOrderedAscending);
    XCTAssert(XZVersionStringCompare(@"2.2", @"1.2.3") == NSOrderedDescending);
    NSLog(@"Timestamp: %f", XZTimestamp());
}

- (void)testXZRuntime {
    XCTAssert(xz_objc_class_getInstanceMethod([Foo class], @selector(foo)) != nil);
    XCTAssert(xz_objc_class_getInstanceMethod([Foo class], @selector(bar)) == nil);
    
    XCTAssert(xz_objc_class_getInstanceMethod([Bar class], @selector(foo)) == nil);
    XCTAssert(xz_objc_class_getInstanceMethod([Bar class], @selector(bar)) != nil);
    
    xz_objc_class_enumerateInstanceMethods([Foo class], ^BOOL(Method  _Nonnull method, NSInteger index) {
        NSLog(@"-[Foo %@]", NSStringFromSelector(method_getName(method)));
        return YES;
    });
    xz_objc_class_enumerateInstanceMethods([Bar class], ^BOOL(Method  _Nonnull method, NSInteger index) {
        NSLog(@"-[Bar %@]", NSStringFromSelector(method_getName(method)));
        return YES;
    });
    xz_objc_class_enumerateInstanceVariables([Foo class], ^BOOL(Ivar  _Nonnull ivar) {
        NSLog(@"Foo->%s", ivar_getName(ivar));
        return YES;
    });
    xz_objc_class_enumerateInstanceVariables([Bar class], ^BOOL(Ivar  _Nonnull ivar) {
        NSLog(@"Bar->%s", ivar_getName(ivar));
        return YES;
    });
    
    Bar *bar = [[Bar alloc] init];
    XCTAssert([[bar speakFoo] isEqualToString:@"foo"]);
    XCTAssert([[bar speakBar] isEqualToString:@"bar"]);
    xz_objc_class_exchangeInstanceMethods([Bar class], @selector(speakFoo), @selector(speakBar));
    XCTAssert([[bar speakFoo] isEqualToString:@"bar"]);
    XCTAssert([[bar speakBar] isEqualToString:@"foo"]);
    
    xz_objc_class_addMethod([Bar class], @selector(speakNew), [FooBar class], @selector(speakNew), nil, nil);
    XCTAssert([[(FooBar*)bar speakNew] isEqualToString:@"foobar new"]);
    
    xz_objc_class_addMethod([Bar class], @selector(speakFoo), [FooBar class], @selector(speakFoo), @selector(override_speakFoo), @selector(exchange_speakFoo));
    XCTAssert([[bar speakFoo] isEqualToString:@"foobar override foo"]);
    
    xz_objc_class_addMethod([Bar class], @selector(speakBar), [FooBar class], @selector(speakBar), @selector(override_speakBar), @selector(exchange_speakBar));
    XCTAssert([[bar speakBar] isEqualToString:@"foobar exchange bar"]);
    
    BOOL success = xz_objc_class_addMethod([Bar class], @selector(speakTwo), [FooBar class], @selector(speakTwo), @selector(override_speakTwo), @selector(exchange_speakTwo));
    XCTAssert(success == NO);
}

- (void)xz_creation {
    
}

- (void)xz_override {
    
    
}

- (void)xz_exchange {
    
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end


@implementation Foo {
    NSInteger _foo;
}

- (void)foo {
    NSLog(@"method foo");
}

- (NSString *)speakFoo {
    return @"foo";
}

- (NSString *)speakTwo {
    return @"foo two";
}

@end

@implementation Bar {
    NSInteger _bar;
}

- (void)bar {
    NSLog(@"method bar");
}

- (NSString *)speakBar {
    return @"bar";
}

- (NSString *)speakTwo {
    NSLog(@"exchange_speakTwo => %@", NSStringFromSelector(_cmd));
    return @"bar two";
}

- (NSString *)exchange_speakTwo {
    return @"bar exchange two";
}

@end


@implementation FooBar

- (NSString *)speakNew {
    return @"foobar new";
}

- (NSString *)speakFoo {
    return @"foobar foo";
}
- (NSString *)override_speakFoo {
    return @"foobar override foo";
}
- (NSString *)exchange_speakFoo {
    return @"foobar exchange foo";
}

- (NSString *)speakBar {
    return @"foobar bar";
}
- (NSString *)override_speakBar {
    return @"foobar override bar";
}
- (NSString *)exchange_speakBar {
    return @"foobar exchange bar";
}

- (NSString *)speakTwo {
    return @"foobar two";
}
- (NSString *)override_speakTwo {
    return @"foobar override two";
}
- (NSString *)exchange_speakTwo {
    NSLog(@"exchange_speakTwo => %@", NSStringFromSelector(_cmd));
    [self exchange_speakTwo];
    return @"foobar exchange two";
}

@end
