//
//  XZMacro.h
//  XZKit
//
//  Created by Xezun on 2021/4/20.
//

#import <Foundation/Foundation.h>

/// 默认动画时长 0.35 秒。
FOUNDATION_EXPORT NSTimeInterval const XZAnimationDuration;

#if DEBUG
// 空的 @autoreleasepool 不会被优化，只在 DEBUG 中使用。
#define xzmacro_keyize autoreleasepool {}
#else
// 空的 @try 在 5.x 的编译器中会被优化掉，但是会产生一条警告，所以只在 release 模式中使用。
#define xzmacro_keyize try {} @catch (...) {}
#endif

/// 连接两个参数
#define xzmacro_paste(A, B) __NSX_PASTE__(A, B)

/// 获取宏参数列表中的第 N 个参数。
#define xzmacro_args_at(N, ...) xzmacro_paste(xzmacro_args_at, N)(__VA_ARGS__)

/// 获取参数列表中的第一个个参数。
#define xzmacro_args_first(...) xzmacro_args_first_imp(__VA_ARGS__, 0)

/// 获取参数列表中参数的个数（最多10个）。
/// 在参数列表后添加从 10 到 1 的数字，取得第 11 个元素，就是原始参数列表的个数。
#define xzmacro_args_count(...) xzmacro_args_at(10, __VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/// 遍历参数列表：对参数列表中的参数，逐个应用 MACRO(INDEX, ARG) 宏函数。
#define xzmacro_args_map(MACRO, SEP, ...) xzmacro_args_map_imp(xzmacro_args_map_ctx, SEP, MACRO, __VA_ARGS__)

/// 宏 xzmacro_args_at 的实现：
/// 通过 xzmacro_paste 拼接 N 后，就变成下面对应的宏，
/// 由于 0 到 N - 1 之间的参数已占位，这样参数列表 ... 就是 N 及之后的参数，
/// 然后获取这个参数列表的第一个参数，即是原始参数列表的第 N 个参数。
#define xzmacro_args_at0(...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at1(_0, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at2(_0, _1, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at3(_0, _1, _2, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at4(_0, _1, _2, _3, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at5(_0, _1, _2, _3, _4, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at6(_0, _1, _2, _3, _4, _5, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at7(_0, _1, _2, _3, _4, _5, _6, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at8(_0, _1, _2, _3, _4, _5, _6, _7, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) xzmacro_args_first(__VA_ARGS__)
#define xzmacro_args_at10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) xzmacro_args_first(__VA_ARGS__)

/// 宏 xzmacro_args_first 的实现。
#define xzmacro_args_first_imp(FIRST, ...) FIRST

/// 宏 xzmacro_args_map 的实现。
/// 根据参数的个数，展开成相应的具体实现。
#define xzmacro_args_map_imp(CONTEXT, SEP, MACRO, ...) \
        xzmacro_paste(xzmacro_args_map_imp, xzmacro_args_count(__VA_ARGS__))(CONTEXT, SEP, MACRO, __VA_ARGS__)
#define xzmacro_args_map_ctx(INDEX, MACRO, ARG) MACRO(INDEX, ARG)

#define xzmacro_args_map_imp0(CONTEXT, SEP, MACRO)
#define xzmacro_args_map_imp1(CONTEXT, SEP, MACRO, _0) CONTEXT(0, MACRO, _0)

#define xzmacro_args_map_imp2(CONTEXT, SEP, MACRO, _0, _1) \
    xzmacro_args_map_imp1(CONTEXT, SEP, MACRO, _0) \
    SEP \
    CONTEXT(1, MACRO, _1)

#define xzmacro_args_map_imp3(CONTEXT, SEP, MACRO, _0, _1, _2) \
    xzmacro_args_map_imp2(CONTEXT, SEP, MACRO, _0, _1) \
    SEP \
    CONTEXT(2, MACRO, _2)

#define xzmacro_args_map_imp4(CONTEXT, SEP, MACRO, _0, _1, _2, _3) \
    xzmacro_args_map_imp3(CONTEXT, SEP, MACRO, _0, _1, _2) \
    SEP \
    CONTEXT(3, MACRO, _3)

#define xzmacro_args_map_imp5(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4) \
    xzmacro_args_map_imp4(CONTEXT, SEP, MACRO, _0, _1, _2, _3) \
    SEP \
    CONTEXT(4, MACRO, _4)

#define xzmacro_args_map_imp6(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5) \
    xzmacro_args_map_imp5(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4) \
    SEP \
    CONTEXT(5, MACRO, _5)

#define xzmacro_args_map_imp7(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5, _6) \
    xzmacro_args_map_imp6(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5) \
    SEP \
    CONTEXT(6, MACRO, _6)

#define xzmacro_args_map_imp8(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5, _6, _7) \
    xzmacro_args_map_imp7(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    CONTEXT(7, MACRO, _7)

#define xzmacro_args_map_imp9(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    xzmacro_args_map_imp8(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    CONTEXT(8, MACRO, _8)

#define xzmacro_args_map_imp10(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    xzmacro_args_map_imp9(CONTEXT, SEP, MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    CONTEXT(9, MACRO, _9)


/// 函数重载
#define XZATTR_OVERLOAD             __attribute__((overloadable))
/// 函数外部不可见
#define XZATTR_INTERNAL             __attribute__ ((visibility("hidden")))

/// 废弃声明
#define XZ_DEPRECATED(message)      __deprecated_msg(message)

/// 仅对外部生效的标记
#ifdef XZ_FRAMEWORK
#define XZ_CONST
#define XZ_READONLY
#define XZ_UNAVAILABLE
#else
#define XZ_CONST            const
#define XZ_READONLY         readonly
#define XZ_UNAVAILABLE      NS_UNAVAILABLE
#endif


#ifndef weakize
/// @code
/// @weakize(self);             // 将变量进行 weak 编码
/// dispatch_async(dispatch_get_main_queue(), ^{
///     @strongize(self);       // 将变量进行 weak 解码
///     [self description];     // 此处的 self 为 strong，为 block 内局部变量，非捕获外部的变量
/// });
/// @endcode
/// 将变量进行 weak 编码，并且在之后的 block 中，可以通过 strongize(VAR) 解码出 VAR 变量以供使用，以避免循环引用。
/// @note 该方法不改变 VAR 自身的强、弱引用属性。
/// @note 该方法不改变 VAR 的引用计数。
/// @define weakize
/// @param VAR 变量
#define weakize(...) xzmacro_keyize  xzmacro_args_map(__weakize_imp__,, __VA_ARGS__)
#define __weakize_imp__(INDEX, VAR) __typeof__(VAR) __weak const xzmacro_paste(__xz_weak_, VAR) = (VAR);
#endif

#ifndef strongize
/// 将变量进行 weak 解码，以便之后可以将变量将作为强引用变量使用。
/// @note 该方法必须搭配 @weakize 使用。
/// @note 在 block 中，该方法捕获的是 weakize 编码后的弱引用变量，即不捕获外部的 VAR 变量，不会造成循环引用。
/// @note 该方法必须在使用 VAR 变量之前使用。
/// @seealso @weakize()
/// @define strongize
/// @param VAR 变量
#define strongize(...) xzmacro_keyize                   \
_Pragma("clang diagnostic push")                        \
_Pragma("clang diagnostic ignored \"-Wshadow\"")        \
xzmacro_args_map(__strongize_imp__,, __VA_ARGS__)       \
_Pragma("clang diagnostic pop")
#define __strongize_imp__(INDEX, VAR) __typeof__(VAR) __strong const VAR = xzmacro_paste(__xz_weak_, VAR);
#endif



// 关于重写 NSLog 的一点笔记
// stderr: 标准错误输出，立即输出到屏幕。
// stdout: 标准输出，当遇到刷新标志（比如换行）或缓冲满时，才把缓冲的数据输出到设备中。
// STDERR_FILENO: 与 stderr 相同
//
// 经过溯源原代码，在 CF-1153.18 源文件 CFUtilities.c 中可以找到 NSLog 函数的源码：
//     NSLog() => CFLog() => _CFLogvEx() => __CFLogCString() =>
//     #if DEPLOYMENT_TARGET_MACOSX || DEPLOYMENT_TARGET_EMBEDDED || DEPLOYMENT_TARGET_EMBEDDED_MINI
//         => writev(STDERR_FILENO)
//     #elif DEPLOYMENT_TARGET_WINDOWS
//         => fprintf_s(stderr)
//     #else
//         => fprintf(stderr)
//     #endif
// 而在 CFBundle_Resources.c 文件的 320-321 行
//     #elif DEPLOYMENT_TARGET_EMBEDDED || DEPLOYMENT_TARGET_EMBEDDED_MINI
//         return CFSTR("iPhoneOS");
// 所以在 iOS 平台，NSLog 最终使用的是 writev 函数输出日志，并且使用了 CFLock_t 保证线程安全。
// 而且函数 __CFLogCString() 是 static 局部函数，保证 writev 线程安全的 CFLock_t 锁也是局部的，
// 并不能被访问，而如果使用其它函数在控制台输出，就会不可避免出现与 NSLog 的输出内容互相嵌入的情况。
//
// XZLog 仅在 XZ_DEBUG 且 DEBUG 模式下才会输出日志到控制台。
#ifndef XZLog
#ifdef XZ_DEBUG
#if DEBUG
#define XZLog(format, ...) NSLog(@"%s(%d) \n%@", __PRETTY_FUNCTION__, __LINE__, [NSString stringWithFormat:format, ##__VA_ARGS__])
#else  // => #if DEBUG
#define XZLog(...)  do {} while (0)
#endif // => #if DEBUG
#else  // => #ifdef XZ_DEBUG
#define XZLog(...)  do {} while (0)
#endif // => #ifdef XZ_DEBUG
#endif // => #ifndef XZLog


