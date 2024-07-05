//
//  XZEmpty.h
//  XZDefines
//
//  Created by Xezun on 2023/8/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef isNonEmpty

FOUNDATION_STATIC_INLINE BOOL __xz_is_non_empty_imp_string__(NSString * _Nullable value) {
    return (value && [value isKindOfClass:NSString.class] && value.length > 0);
}
FOUNDATION_STATIC_INLINE BOOL __xz_is_non_empty_imp_array__(NSArray * _Nullable value) {
    return (value && [value isKindOfClass:NSArray.class] && value.count > 0);
}
FOUNDATION_STATIC_INLINE BOOL __xz_is_non_empty_imp_set__(NSSet * _Nullable value) {
    return (value && [value isKindOfClass:NSArray.class] && value.count > 0);
}
FOUNDATION_STATIC_INLINE BOOL __xz_is_non_empty_imp_dictionary__(NSDictionary * _Nullable value) {
    return (value && [value isKindOfClass:NSDictionary.class] && value.count > 0);
}
FOUNDATION_STATIC_INLINE BOOL __xz_is_non_empty_imp_number__(NSNumber * _Nullable value) {
    return (value && [value isKindOfClass:NSNumber.class] && value.boolValue);
}
FOUNDATION_STATIC_INLINE BOOL __xz_is_non_empty_imp_object__(id _Nullable value) {
    return (value != nil && value != NSNull.null);
}



/// @define
/// 对值进行非空判断。
/// @attention
/// 值 value 不能时 id 类型，因为 id 会适配所有类型，导致宏不能确定要使用的函数。
/// @discussion
/// 当 value 的类型为 NSString 时，非空字符串为真值。
/// @discussion
/// 当 value 的类型为 NSArray 时，非空数组为真值。
/// @discussion
/// 当 value 的类型为 NSSet 时，非空集合为真值。
/// @discussion
/// 当 value 的类型为 NSDictionary 时，非空字典为真值。
/// @discussion
/// 当 value 的类型为 NSNumber 时，浮点值不为零为真值。
/// @discussion
/// 其它类型的值，仅判断为非 nil 和非 NSNull.null 值。
/// @code
/// isNonEmpty(@"");     // equals NO
/// isNonEmpty(@"0");    // equals YES
/// isNonEmpty(@"1");    // equals YES
/// @endcode
/// @param value 待判断的值
/// @returns 是否非空
#define isNonEmpty(value)                                               \
_Generic((value),                                                       \
    NSMutableString     * : __xz_is_non_empty_imp_string__,             \
    NSString            * : __xz_is_non_empty_imp_string__,             \
    NSMutableArray      * : __xz_is_non_empty_imp_array__,              \
    NSArray             * : __xz_is_non_empty_imp_array__,              \
    NSMutableSet        * : __xz_is_non_empty_imp_set__,                \
    NSSet               * : __xz_is_non_empty_imp_set__,                \
    NSMutableDictionary * : __xz_is_non_empty_imp_dictionary__,         \
    NSDictionary        * : __xz_is_non_empty_imp_dictionary__,         \
    NSNumber            * : __xz_is_non_empty_imp_number__,             \
    default               : __xz_is_non_empty_imp_object__              \
)((value))

#endif // #ifndef isNonEmpty

#ifndef asNonEmpty

FOUNDATION_STATIC_INLINE id _Nullable __xz_as_non_emtpy_imp_string__(id _Nullable value, NSString * _Nullable defaultValue) {
    return __xz_is_non_empty_imp_string__(value) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_as_non_emtpy_imp_array__(id _Nullable value, NSArray * _Nullable defaultValue) {
    return __xz_is_non_empty_imp_array__(value) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_as_non_emtpy_imp_set__(id _Nullable value, NSSet * _Nullable defaultValue) {
    return __xz_is_non_empty_imp_set__(value) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_as_non_emtpy_imp_dictionary__(id _Nullable value, NSDictionary * _Nullable defaultValue) {
    return __xz_is_non_empty_imp_dictionary__(value) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_as_non_emtpy_imp_number__(id _Nullable value, NSNumber * _Nullable defaultValue) {
    return __xz_is_non_empty_imp_number__(value) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_as_non_emtpy_imp_url__(id _Nullable value, NSURL * _Nullable defaultValue) {
    if (value == nil) return defaultValue;
    if ([value isKindOfClass:NSURL.class]) return value;
    if ([value isKindOfClass:NSString.class]) return __xz_as_non_emtpy_imp_url__([NSURL URLWithString:(id)value], defaultValue);
    return defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_as_non_emtpy_imp_object__(id _Nullable value, id _Nullable defaultValue) {
    return __xz_is_non_empty_imp_object__(value) ? value : defaultValue;
}
/// @define
/// 判断 value 非空，否则使用 defaultValue 代替。
/// @discussion
/// 变量声明为 NSString/NSArray/NSSet/NSDictionary/NSNumber 类型，进行非空或非零判断。
/// @code
/// XZOpt(@"", @"123");     // equals @"123"
/// XZOpt(@"xxx", @"123");  // equals @"xxx"
/// @endcode
/// @discussion
/// 变量声明为 NSURL 类型，如果实际值为 NSURL 则直接使用；如果实际值为 URL 格式的字符串，则构造为 NSURL 对象，并返回；否则返回 defaultValue 值。
/// @code
/// XZOpt(nil, @"https://xezun.com");                                               // equals [NSURL URLWithString:@"https://xezun.com"]
/// XZOpt([NSURL URLWithString:@"https://xzkit.xezun.com"], @"https://xezun.com");  // equals [NSURL URLWithString:@"https://xzkit.xezun.com"]
/// @endcode
/// @discussion
/// 变量声明为 id 类型，需要转换指定类型。
/// @code
/// XZOpt((NSString *)aValue, @"123"); // 如果 aValue 为非空字符串，返回 aString 否则返回 @"123"
/// @endcode
/// @discussion
/// 变量声明为其它类型，进行非 nil 和非 NSNull 判断
/// @param value 待判断的值，不能是 id 类型
/// @param defaultValue 默认值
/// @returns 原始值，或者默认值
#define asNonEmpty(value, defaultValue)                                      \
_Generic((defaultValue),                                                     \
    NSString     * : __xz_as_non_emtpy_imp_string__,                         \
    NSArray      * : __xz_as_non_emtpy_imp_array__,                          \
    NSSet        * : __xz_as_non_emtpy_imp_set__,                            \
    NSDictionary * : __xz_as_non_emtpy_imp_dictionary__,                     \
    NSNumber     * : __xz_as_non_emtpy_imp_number__,                         \
    NSURL        * : __xz_as_non_emtpy_imp_url__,                            \
    default        : __xz_as_non_emtpy_imp_object__                          \
)((value), (defaultValue))

#endif // #ifndef asNonEmpty

NS_ASSUME_NONNULL_END
