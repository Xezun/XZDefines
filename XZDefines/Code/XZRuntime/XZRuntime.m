//
//  XZRuntime.m
//  XZKit
//
//  Created by Xezun on 2021/5/7.
//

#import "XZRuntime.h"

BOOL xz_objc_class_copyMethod(Class const cls, SEL const target, SEL const source) {
    if (class_respondsToSelector(cls, target)) {
        return NO;
    }
    Method       const mtd = class_getInstanceMethod(cls, source);
    IMP          const imp = method_getImplementation(mtd);
    const char * const tps = method_getTypeEncoding(mtd);
    return class_addMethod(cls, target, imp, tps);
}

Method xz_objc_class_getInstanceMethod(Class const cls, SEL const target) {
    Method method = NULL;
    
    unsigned int count = 0;
    Method *methods = class_copyMethodList(cls, &count);
    for (unsigned int i = 0; i < count; i++) {
        if (method_getName(methods[i]) == target) {
            method = methods[i];
            break;
        }
    }
    free(methods);
    
    return method;
}

xz_objc_status xz_objc_class_addMethod(Class const cls, SEL const name, SEL const source, SEL const sourceForOverride, SEL const sourceForExchange) {
    NSCAssert(cls && name, @"参数 cls 和 name 不能为空");
    // 方法已实现
    if ([cls instancesRespondToSelector:name]) {
        Method const oldMethod = xz_objc_class_getInstanceMethod(cls, name);
        
        // 方法由父类实现，重写方法
        if (oldMethod == NULL) {
            if (sourceForOverride != NULL) {
                Method      const mtd = class_getInstanceMethod(cls, sourceForOverride);
                IMP         const imp = method_getImplementation(mtd);
                const char *const enc = method_getTypeEncoding(mtd);
                if (class_addMethod(cls, name, imp, enc)) {
                    return xz_objc_status_success;
                }
                return xz_objc_status_failure;
            }
            return xz_objc_status_override;
        }
        
        // 方法已自身实现，交换方法
        if (sourceForExchange != NULL) {
            Method const newMethod = class_getInstanceMethod(cls, sourceForExchange);
            method_exchangeImplementations(oldMethod, newMethod);
            return xz_objc_status_success;
        }
        return xz_objc_status_exchange;
    }
    
    if (source == NULL) {
        return xz_objc_status_function;
    }
    
    // 添加新方法
    Method      const mtd = class_getInstanceMethod(cls, source);
    IMP         const imp = method_getImplementation(mtd);
    const char *const enc = method_getTypeEncoding(mtd);
    if (class_addMethod(cls, name, imp, enc)) {
        return xz_objc_status_success;
    }
    return xz_objc_status_failure;
}
