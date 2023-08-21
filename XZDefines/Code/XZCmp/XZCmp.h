//
//  XZCmp.h
//  XZDefines
//
//  Created by Xezun on 2023/8/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_STATIC_INLINE BOOL __xz_cmp_imp_string__(NSString * _Nullable value, BOOL trueOrFalse) {
    return (value && [value isKindOfClass:NSString.class] && value.length > 0) == trueOrFalse;
}
FOUNDATION_STATIC_INLINE BOOL __xz_cmp_imp_array__(NSArray * _Nullable value, BOOL trueOrFalse) {
    return (value && [value isKindOfClass:NSArray.class] && value.count > 0) == trueOrFalse;
}
FOUNDATION_STATIC_INLINE BOOL __xz_cmp_imp_set__(NSSet * _Nullable value, BOOL trueOrFalse) {
    return (value && [value isKindOfClass:NSArray.class] && value.count > 0) == trueOrFalse;
}
FOUNDATION_STATIC_INLINE BOOL __xz_cmp_imp_dictionary__(NSDictionary * _Nullable value, BOOL trueOrFalse) {
    return (value && [value isKindOfClass:NSDictionary.class] && value.count > 0) == trueOrFalse;
}
FOUNDATION_STATIC_INLINE BOOL __xz_cmp_imp_number__(NSNumber * _Nullable value, BOOL trueOrFalse) {
    return (value && [value isKindOfClass:NSNumber.class] && value.doubleValue != 0) == trueOrFalse;
}
FOUNDATION_STATIC_INLINE BOOL __xz_cmp_imp_object__(id _Nullable value, BOOL trueOrFalse) {
    return (value != nil && value != NSNull.null) == trueOrFalse;
}
/// @define
/// 当 value 作为布尔值时，判断其是否为指定布尔值。
/// @discussion
/// value 的声明类型不能为 id 类型。
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
/// 当 value 的类型为其它类型时，不为 NSNull 的对象为真值。
/// @code
/// XZCmp(@"", YES);       // equals NO
/// XZCmp(@"", NO);        // equals YES
/// XZCmp(@"123", YES);    // equals YES
/// XZCmp(@"123", NO);     // equals NO
/// @endcode
/// @param value 待判断的值
/// @param yesOrNO 期待的值
/// @returns YES 表示结果为期待的值
#define XZCmp(value, yesOrNO)                                   \
_Generic((value),                                               \
    NSString     * : __xz_cmp_imp_string__,                     \
    NSArray      * : __xz_cmp_imp_array__,                      \
    NSSet        * : __xz_cmp_imp_set__,                        \
    NSDictionary * : __xz_cmp_imp_dictionary__,                 \
    NSNumber     * : __xz_cmp_imp_number__,                     \
    default        : __xz_cmp_imp_object__                      \
)((value), (yesOrNO))

NS_ASSUME_NONNULL_END
