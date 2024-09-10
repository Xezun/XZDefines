//
//  XZEmpty.h
//  XZDefines
//
//  Created by Xezun on 2023/8/6.
//
//
// 【开发备忘】
// 宏 `_Generic` 不能在其中同时加入子类和父类，否则无法使用。
// #define isNonEmpty(value)                                               \
// _Generic((value),                                                       \
//     NSString            * : __xz_is_non_empty_imp_string__,             \
//     NSArray             * : __xz_is_non_empty_imp_array__,              \
//     NSSet               * : __xz_is_non_empty_imp_set__,                \
//     NSDictionary        * : __xz_is_non_empty_imp_dictionary__,         \
//     NSNumber            * : __xz_is_non_empty_imp_number__,             \
//     default               : __xz_is_non_empty_imp_object__              \
// )((value))


#import <Foundation/Foundation.h>
#import <XZDefines/XZMacro.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef isNonEmpty

/// 当 value 为非空字符串时，返回 YES 值。
FOUNDATION_STATIC_INLINE BOOL isNonEmpty(NSString * _Nullable value) XZATTR_OVERLOAD {
    return (value && [value isKindOfClass:NSString.class] && value.length > 0);
}
/// 当 value 为非空数组时，返回 YES 值。
FOUNDATION_STATIC_INLINE BOOL isNonEmpty(NSArray * _Nullable value) XZATTR_OVERLOAD {
    return (value && [value isKindOfClass:NSArray.class] && value.count > 0);
}
/// 当 value 为非空集合时，返回 YES 值。
FOUNDATION_STATIC_INLINE BOOL isNonEmpty(NSSet * _Nullable value) XZATTR_OVERLOAD {
    return (value && [value isKindOfClass:NSSet.class] && value.count > 0);
}
/// 当 value 为非空字典时，返回 YES 值。
FOUNDATION_STATIC_INLINE BOOL isNonEmpty(NSDictionary * _Nullable value) XZATTR_OVERLOAD {
    return (value && [value isKindOfClass:NSDictionary.class] && value.count > 0);
}
/// 当 value 为非零数值时，返回 YES 值。
FOUNDATION_STATIC_INLINE BOOL isNonEmpty(NSNumber * _Nullable value) XZATTR_OVERLOAD {
    return (value && [value isKindOfClass:NSNumber.class] && value.boolValue);
}
/// 当 value 不为 nil 和 NSNull.null 时，返回 YES 值。
FOUNDATION_STATIC_INLINE BOOL isNonEmpty(id _Nullable value) XZATTR_OVERLOAD {
    return (value != nil && value != NSNull.null);
}

#endif // #ifndef isNonEmpty

#ifndef asNonEmpty

// 备忘：参数 defultValue 不能为 NSObject 类型。

/// 如果值 value 为非空字符串，那么返回 value 值，否则返回 defaultValue 值。
FOUNDATION_STATIC_INLINE NSString * _Nullable asNonEmpty(id _Nullable value, NSString * _Nullable defaultValue) XZATTR_OVERLOAD {
    return isNonEmpty((NSString *)value) ? value : defaultValue;
}
/// 如果值 value 为非空数组，那么返回 value 值，否则返回 defaultValue 值。
FOUNDATION_STATIC_INLINE NSArray * _Nullable asNonEmpty(id _Nullable value, NSArray * _Nullable defaultValue) XZATTR_OVERLOAD {
    return isNonEmpty((NSArray *)value) ? value : defaultValue;
}
/// 如果值 value 为非空集合，那么返回 value 值，否则返回 defaultValue 值。
FOUNDATION_STATIC_INLINE NSSet *  _Nullable asNonEmpty(id _Nullable value, NSSet * _Nullable defaultValue) XZATTR_OVERLOAD {
    return isNonEmpty((NSSet *)value) ? value : defaultValue;
}
/// 如果值 value 为非空字典，那么返回 value 值，否则返回 defaultValue 值。
FOUNDATION_STATIC_INLINE NSDictionary * _Nullable asNonEmpty(id _Nullable value, NSDictionary * _Nullable defaultValue) XZATTR_OVERLOAD {
    return isNonEmpty((NSDictionary *)value) ? value : defaultValue;
}
/// 如果值 value 为非零数值，那么返回 value 值，否则返回 defaultValue 值。
FOUNDATION_STATIC_INLINE NSNumber * _Nullable asNonEmpty(id _Nullable value, NSNumber * _Nullable defaultValue) XZATTR_OVERLOAD {
    return isNonEmpty((NSNumber *)value) ? value : defaultValue;
}
/// 如果值 value 为 NSURL 对象，那么返回 value 值；
/// 如果值 value 为合法的 URL 字符串，那么返回 value 构造的 NSURL 对象；
/// 否则返回 defaultValue 值。
FOUNDATION_STATIC_INLINE NSURL * _Nullable asNonEmpty(id _Nullable value, NSURL * _Nullable defaultValue) XZATTR_OVERLOAD {
    if (value == nil) {
        return defaultValue;
    }
    if ([value isKindOfClass:NSURL.class]) {
        if (((NSURL *)value).absoluteString.length > 0) {
            return value;
        }
        return defaultValue;
    }
    if ([value isKindOfClass:NSString.class]) {
        return asNonEmpty([NSURL URLWithString:(id)value], defaultValue);
    }
    return defaultValue;
}
/// 如果值 value 不为 nil 且不为 NSNull 值，那么返回 value 值，否则返回 defaultValue 值。
FOUNDATION_STATIC_INLINE id _Nullable asNonEmpty(id _Nullable value, id _Nullable defaultValue) XZATTR_OVERLOAD {
    return isNonEmpty(value) ? value : defaultValue;
}

#endif // #ifndef asNonEmpty

NS_ASSUME_NONNULL_END
