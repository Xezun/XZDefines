//
//  XZTimestamp.m
//  XZKit
//
//  Created by Xezun on 2023/8/6.
//

#import "XZTimestamp.h"
#import <sys/time.h>

NSTimeInterval XZTimestamp(void) {
    struct timeval aTime;
    gettimeofday(&aTime, NULL);
    NSTimeInterval sec = aTime.tv_sec;
    NSTimeInterval u_sec = aTime.tv_usec * 1.0e-6L;
    return (sec + u_sec);
}
