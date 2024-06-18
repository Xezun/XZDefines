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


#pragma mark - 创建类

Class xz_objc_createClassWithName(Class superClass, NSString *name, NS_NOESCAPE XZRuntimeCreateClassBlock _Nullable block) {
    NSCParameterAssert([name isKindOfClass:NSString.class] && name.length > 0);
    const char * const className = name.UTF8String;
    
    Class newClass = objc_getClass(className);
    if (newClass != Nil) {
        return Nil;
    }
    
    newClass = objc_allocateClassPair(superClass, className, 0);
    if (newClass != Nil) {
        if (block != nil) {
            block(newClass);
        }
        objc_registerClassPair(newClass);
    }
    return newClass;
}

Class xz_objc_createClass(Class superClass, NS_NOESCAPE XZRuntimeCreateClassBlock _Nullable classing)  {
    NSCParameterAssert(superClass != Nil);
    NSString *name = NSStringFromClass(superClass);
    if (![name hasPrefix:@"XZKit."]) {
        name = [NSString stringWithFormat:@"XZKit.%@", name];
    }
   
    Class newClass = xz_objc_createClassWithName(superClass, name, classing);
    
    NSInteger i = 0;
    while (newClass == Nil && i < 1024) {
        name = [NSString stringWithFormat:@"%@.%ld", name, (long)(i++)];
        newClass = xz_objc_createClassWithName(superClass, name, classing);
    }
    
    return newClass;
}


#pragma mark - Add Method

BOOL xz_objc_class_addMethodByCopyingMethod(Class target, Method method, id _Nullable implementation)  {
    if (target == Nil || method == nil) {
        return NO;
    }
    SEL const sel = method_getName(method);
    IMP const imp = implementation ? imp_implementationWithBlock(implementation) : method_getImplementation(method);
    const char * const encoding = method_getTypeEncoding(method);
    return class_addMethod(target, sel, imp, encoding);
}

BOOL xz_objc_class_copyMethodFromClass(Class target, Class source, SEL selector, id _Nullable implementation) {
    if (source == Nil || selector == nil) {
        return NO;
    }
    Method const method = class_getInstanceMethod(source, selector);
    return xz_objc_class_addMethodByCopyingMethod(target, method, implementation);
}

NSInteger xz_objc_class_copyMethodsFromClass(Class target, Class source) {
    NSInteger __block count = 0;
    xz_objc_class_enumerateMethods(source, ^(Method method) {
        if (xz_objc_class_addMethodByCopyingMethod(target, method, nil)) {
            count += 1;
        }
    });
    return count;
}

#pragma mark - 其他方法

void xz_objc_class_exchangeMethodsImplementations(Class aClass, SEL selector1, SEL selector2) {
    Method method1 = class_getInstanceMethod(aClass, selector1);
    Method method2 = class_getInstanceMethod(aClass, selector2);
    // 如果添加失败，则替换。
    if (!class_addMethod(aClass, selector1, method_getImplementation(method2), method_getTypeEncoding(method1))) {
        method_exchangeImplementations(method1, method2);
    }
}

void xz_objc_class_enumerateVariables(Class aClass, void (^block)(Ivar ivar)) {
    unsigned int count = 0;
    Ivar _Nonnull *ivars = class_copyIvarList(aClass, &count);
    if (count == 0) {
        return;
    }
    for (unsigned int i = 0; i < count; i++) {
        block(ivars[i]);
    }
    free(ivars);
}

NSArray<NSString *> *xz_objc_class_getVariableNames(Class aClass) {
    NSMutableArray * __block arrayM = nil;
    xz_objc_class_enumerateVariables(aClass, ^(Ivar ivar) {
        NSString *ivarName = [NSString stringWithUTF8String:ivar_getName(ivar)];
        if (arrayM == nil) {
            arrayM = [NSMutableArray arrayWithObject:ivarName];
        } else {
            [arrayM addObject:ivarName];
        }
    });
    return arrayM;
}

void xz_objc_class_enumerateMethods(Class aClass, void (^block)(Method method)) {
    unsigned int count = 0;
    Method *methods = class_copyMethodList(aClass, &count);
    if (count == 0) {
        return;
    }
    for (unsigned int i = 0; i < count; i++) {
        block(methods[i]);
    }
    free(methods);
}

NSArray<NSString *> *xz_objc_class_getMethodSelectors(Class aClass) {
    NSMutableArray * __block arrayM = nil;
    xz_objc_class_enumerateMethods(aClass, ^(Method method) {
        NSString *methodName = NSStringFromSelector(method_getName(method));
        if (arrayM == nil) {
            arrayM = [NSMutableArray arrayWithObject:methodName];
        } else {
            [arrayM addObject:methodName];
        }
    });
    return arrayM;
}
