//
//  ExampleTests.m
//  ExampleTests
//
//  Created by Xezun on 2023/7/27.
//

#import <XCTest/XCTest.h>
@import XZDefines;


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
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    } {
        NSMutableArray *aMutableArray = nil;
        XCTAssert(isNonEmpty(aMutableArray) == NO);
        
        aMutableArray = (id)NSNull.null;
        XCTAssert(isNonEmpty(aMutableArray) == NO);
        
        aMutableArray = NSMutableArray.array;
        XCTAssert(isNonEmpty(aMutableArray) == NO);
        
        aMutableArray = [NSMutableArray arrayWithObject:@"MutableArray"];
        XCTAssert(isNonEmpty(aMutableArray) == YES);
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    } {
        NSSet *aSet = nil;
        XCTAssert(isNonEmpty(aSet) == NO);
        
        aSet = (id)NSNull.null;
        XCTAssert(isNonEmpty(aSet) == NO);
        
        aSet = NSSet.set;
        XCTAssert(isNonEmpty(aSet) == NO);
        
        aSet = [NSSet setWithObject:@"MutableArray"];
        XCTAssert(isNonEmpty(aSet) == YES);
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    } {
        NSMutableSet *aMutableSet = nil;
        XCTAssert(isNonEmpty(aMutableSet) == NO);
        
        aMutableSet = (id)NSNull.null;
        XCTAssert(isNonEmpty(aMutableSet) == NO);
        
        aMutableSet = NSMutableSet.set;
        XCTAssert(isNonEmpty(aMutableSet) == NO);
        
        aMutableSet = [NSMutableSet setWithObject:@"MutableArray"];
        XCTAssert(isNonEmpty(aMutableSet) == YES);
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    } {
        NSDictionary *aDictionary = nil;
        XCTAssert(isNonEmpty(aDictionary) == NO);
        
        aDictionary = (id)NSNull.null;
        XCTAssert(isNonEmpty(aDictionary) == NO);
        
        aDictionary = @{ };
        XCTAssert(isNonEmpty(aDictionary) == NO);
        
        aDictionary = @{ @"Key": @"Value" };
        XCTAssert(isNonEmpty(aDictionary) == YES);
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    } {
        NSMutableDictionary *aMutableDictionary = nil;
        XCTAssert(isNonEmpty(aMutableDictionary) == NO);
        
        aMutableDictionary = (id)NSNull.null;
        XCTAssert(isNonEmpty(aMutableDictionary) == NO);
        
        aMutableDictionary = NSMutableDictionary.dictionary;
        XCTAssert(isNonEmpty(aMutableDictionary) == NO);
        
        aMutableDictionary = [NSMutableDictionary dictionaryWithObject:@"Value" forKey:@"Key"];
        XCTAssert(isNonEmpty(aMutableDictionary) == YES);
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
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
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    } {
        UIView *anObject = nil;
        XCTAssert(isNonEmpty(anObject) == NO);
        
        anObject = (id)NSNull.null;
        XCTAssert(isNonEmpty(anObject) == NO);
        
        anObject = [[UIView alloc] init];
        XCTAssert(isNonEmpty(anObject) == YES);
        
        anObject = (id)NSUUID.UUID;
        XCTAssert(isNonEmpty(anObject) == YES);
        
        NSLog(@"isNonEmpty(NSString *) => Pass");
    }
}


- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
