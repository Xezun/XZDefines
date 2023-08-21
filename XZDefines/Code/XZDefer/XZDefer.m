//
//  XZDefer.m
//  XZKit
//
//  Created by Xezun on 2023/8/6.
//

#import "XZDefer.h"

void __defer_imp__(__strong __defer_t__ _Nonnull * _Nonnull statements) {
    (*statements)();
}
