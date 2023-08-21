//
//  XZOpt.h
//  XZDefines
//
//  Created by Xezun on 2023/8/6.
//

#import <Foundation/Foundation.h>
#import <XZDefines/XZCmp.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_STATIC_INLINE id _Nullable __xz_opt_imp_string__(NSString * _Nullable value, id _Nullable defaultValue) {
    return __xz_cmp_imp_string__(value, YES) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_opt_imp_array__(NSArray * _Nullable value, id _Nullable defaultValue) {
    return __xz_cmp_imp_array__(value, YES) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_opt_imp_set__(NSSet * _Nullable value, id _Nullable defaultValue) {
    return __xz_cmp_imp_set__(value, YES) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_opt_imp_dictionary__(NSDictionary * _Nullable value, id _Nullable defaultValue) {
    return __xz_cmp_imp_dictionary__(value, YES) ? value : defaultValue;
}
FOUNDATION_STATIC_INLINE id _Nullable __xz_opt_imp_number__(NSNumber * _Nullable value, NSNumber * _Nullable defaultValue) {
    return __xz_cmp_imp_number__(value, YES) ? value : defaultValue;
}
FOUNDATION_EXPORT id _Nullable __xz_opt_imp_url__(NSURL *_Nullable value, id _Nullable defaultValue);
FOUNDATION_STATIC_INLINE id _Nullable __xz_opt_imp_object__(id _Nullable value, id _Nullable defaultValue) {
    return __xz_cmp_imp_object__(value, YES) ? value : defaultValue;
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
#define XZOpt(value, defaultValue)                                  \
_Generic((value),                                                   \
    NSString     * : __xz_opt_imp_string__,                         \
    NSArray      * : __xz_opt_imp_array__,                          \
    NSSet        * : __xz_opt_imp_set__,                            \
    NSDictionary * : __xz_opt_imp_dictionary__,                     \
    NSNumber     * : __xz_opt_imp_number__,                         \
    NSURL        * : __xz_opt_imp_url__,                            \
    default        : __xz_opt_imp_object__                          \
)((value), (defaultValue))

NS_ASSUME_NONNULL_END
