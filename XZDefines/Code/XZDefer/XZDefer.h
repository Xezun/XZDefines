//
//  XZDefer.h
//  XZKit
//
//  Created by Xezun on 2023/8/6.
//

#import <Foundation/Foundation.h>
#import <XZDefines/XZMacro.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef defer
typedef void (^__xz_defer_t__)(void);

FOUNDATION_EXPORT void __xz_defer_imp__(__strong __xz_defer_t__ _Nonnull * _Nonnull statements);

/// 延迟到当前作用域结束后才执行的代码块。
/// @param statements 延迟执行的语句
FOUNDATION_EXTERN void defer(__xz_defer_t__ statements);
#undef defer
#define defer(statements) \
__xz_defer_t__ __strong xzmacro_paste(__xz_defer_, __LINE__) __attribute__((cleanup(__xz_defer_imp__), unused)) = statements

#endif

NS_ASSUME_NONNULL_END
