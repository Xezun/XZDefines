//
//  XZOpt.m
//  XZDefines
//
//  Created by Xezun on 2023/8/6.
//

#import "XZOpt.h"

id _Nullable __xz_opt_imp_url__(NSURL *_Nullable value, id _Nullable defaultValue) {
    if (value == nil) return __xz_opt_imp_url__(defaultValue, nil);
    if ([value isKindOfClass:NSURL.class]) return value;
    if ([value isKindOfClass:NSString.class]) return __xz_opt_imp_url__([NSURL URLWithString:(id)value], defaultValue);
    return __xz_opt_imp_url__(defaultValue, nil);
}
