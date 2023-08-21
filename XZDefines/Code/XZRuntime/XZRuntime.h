//
//  XZRuntime.h
//  XZKit
//
//  Created by Xezun on 2021/5/7.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

/// 执行结果状态码
typedef NS_ENUM(NSInteger, xz_objc_status) {
    /// 执行失败。
    xz_objc_status_failure  = -1,
    /// 执行成功。
    xz_objc_status_success  = 0,
    /// 执行失败，需提供方法实现。
    xz_objc_status_function = 1,
    /// 执行失败，方法已由父类实现，需提供重写方法的实现。
    xz_objc_status_override = 2,
    /// 执行失败，方法已存在，需提供交换方法的实现。
    xz_objc_status_exchange = 3,
};

/// 将类 cls 的方法 source 复制为 target 方法。
/// @note 两个方法使用相同的实现，如果 target 方法已存在，则不复制。
/// @note 提供源的类，须与 cls 相同，不建议是 cls 的父类。
/// @param cls 待添加方法的类
/// @param target 待添加的方法名
/// @param source 被复制的方法名，该方法的实现将被作为新方法的实现
/// @returns 类已有 target 方法（包括父类已实现了该方法）或添加失败，返回 NO
FOUNDATION_EXPORT BOOL xz_objc_class_copyMethod(Class const cls, SEL const target, SEL const source);

/// 获取类 cls 自身的 target 实例方法，即不计算从父类继承的方法。
/// @note 为提高性能，使用本方法前可先检测类 cls 是否能响应 target 方法。
/// @code
/// if ([cls instancesRespondToSelector:target]) {
///     Method method = xz_objc_class_getInstanceMethod(cls, target);
///     if (method == nil) {
///         NSLog(@"方法 %s 从父类继承而来", target);
///     }
/// }
/// @endcode
/// @param cls 待获取方法的类
/// @param target 待获取方法
FOUNDATION_EXPORT Method _Nullable xz_objc_class_getInstanceMethod(Class const cls, SEL const target);

/// 给类添加方法，方法的实现来自类当前已有的方法。
/// @param cls 待添加方法的类
/// @param name 待添加的方法名
/// @param source 如果方法不存在，则使用此方法的实现为类添加新方法
/// @param sourceForOverride 如果方法由父类已实现，则使用方法的实现重写父类的方法
/// @param sourceForExchange 如果方法由当前类实现，则与此方法交换实现
/// @returns 执行状态
FOUNDATION_EXPORT xz_objc_status xz_objc_class_addMethod(Class const cls, SEL const name, SEL const _Nullable source, SEL const _Nullable sourceForOverride, SEL const _Nullable sourceForExchange);

NS_ASSUME_NONNULL_END
