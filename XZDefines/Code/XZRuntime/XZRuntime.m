//
//  XZRuntime.m
//  XZKit
//
//  Created by Xezun on 2021/5/7.
//

#import "XZRuntime.h"

Method xz_objc_class_getInstanceMethod(Class const cls, SEL const target) {
    Method __block result = NULL;
    
    xz_objc_class_enumerateInstanceMethods(cls, ^BOOL(Method method, NSInteger index) {
        if (method_getName(method) == target) {
            result = method;
            return NO;
        }
        return YES;
    });
    
    return result;
}

void xz_objc_class_enumerateInstanceMethods(Class aClass, BOOL (^enumerator)(Method method, NSInteger index)) {
    unsigned int count = 0;
    Method *methods = class_copyMethodList(aClass, &count);
    if (count == 0) {
        return;
    }
    
    for (unsigned int i = 0; i < count; i++) {
        if (!enumerator(methods[i], i)) {
            break;
        }
    }
    free(methods);
}

void xz_objc_class_enumerateInstanceVariables(Class aClass, BOOL (^enumerator)(Ivar ivar)) {
    unsigned int count = 0;
    Ivar _Nonnull *ivars = class_copyIvarList(aClass, &count);
    for (unsigned int i = 0; i < count; i++) {
        if (!enumerator(ivars[i])) {
            break;
        }
    }
    free(ivars);
}

NSArray<NSString *> *xz_objc_class_getInstanceVariableNames(Class aClass) {
    NSMutableArray * __block arrayM = nil;
    xz_objc_class_enumerateInstanceVariables(aClass, ^BOOL(Ivar ivar) {
        NSString *ivarName = [NSString stringWithUTF8String:ivar_getName(ivar)];
        if (arrayM == nil) {
            arrayM = [NSMutableArray arrayWithObject:ivarName];
        } else {
            [arrayM addObject:ivarName];
        }
        return YES;
    });
    return arrayM;
}

void xz_objc_class_exchangeInstanceMethods(Class aClass, SEL selector1, SEL selector2) {
    if (aClass == Nil || selector1 == nil || selector2 == nil) {
        return;
    }
    
    Method method1 = class_getInstanceMethod(aClass, selector1);
    if (method1 == nil) return;
    Method method2 = class_getInstanceMethod(aClass, selector2);
    if (method2 == nil) return;
    // 如果添加失败，则替换。
    method_exchangeImplementations(method1, method2);
}

BOOL xz_objc_class_addMethod(Class aClass, SEL selector, Class _Nullable source, SEL _Nullable creation, SEL _Nullable override, SEL _Nullable exchange) {
    if (aClass == Nil || selector == Nil) {
        return NO;
    }
    
    if (source == Nil) {
        if (creation == nil) {
            return NO;
        }
        source = aClass;
    } else if (creation == Nil) {
        if (aClass == source) {
            return NO;
        }
        creation = selector;
    }
    
    // 方法已实现
    if ([aClass instancesRespondToSelector:selector]) {
        Method const oldMethod = xz_objc_class_getInstanceMethod(aClass, selector);
        
        // 当前类没有这个方法，说明方法由父类实现，重写方法。
        if (oldMethod == NULL) {
            //
            if (override == NULL) {
                return NO;
            }
            
            Method      const overrideMethod         = class_getInstanceMethod(source, override);
            IMP         const overrideMethodIMP      = method_getImplementation(overrideMethod);
            const char *const overrideMethodEncoding = method_getTypeEncoding(overrideMethod);

            return class_addMethod(aClass, selector, overrideMethodIMP, overrideMethodEncoding);
        }
        
        // 方法已自身实现，交换方法
        if (exchange == NULL) {
            return NO;
        }
        
        // 先将待交换的方法，添加到 aClass 上，然后再交换 aClass 上的两个方法的实现。
        Method exchangeMethod = class_getInstanceMethod(aClass, exchange);
        if (aClass != source) {
            if ([aClass instancesRespondToSelector:exchange]) {
                NSString * const name = NSStringFromSelector(selector);
                
                NSString *exchangeName = [NSString stringWithFormat:@"__xz_exchange_%@", name];
                exchange = sel_registerName(exchangeName.UTF8String);
                NSInteger index = 0;
                while ([aClass instancesRespondToSelector:exchange]) {
                    exchangeName = [NSString stringWithFormat:@"__xz_exchange_%ld_%@", index++, name];
                    exchange = sel_registerName(exchangeName.UTF8String);
                }
            }
            
            if (!class_addMethod(aClass, exchange, method_getImplementation(exchangeMethod), method_getTypeEncoding(exchangeMethod))) {
                return NO;
            }
            
            exchangeMethod = class_getInstanceMethod(aClass, exchange);
        }
        method_exchangeImplementations(oldMethod, exchangeMethod);
        return YES;
    }
    
    // 方法未实现，添加新方法
    Method      const mtd = class_getInstanceMethod(source, creation);
    IMP         const imp = method_getImplementation(mtd);
    const char *const enc = method_getTypeEncoding(mtd);
    return class_addMethod(aClass, selector, imp, enc);
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

Class xz_objc_createClass(Class superClass, NS_NOESCAPE XZRuntimeCreateClassBlock _Nullable block)  {
    NSCParameterAssert(superClass != Nil);
    NSString *name = NSStringFromClass(superClass);
    if (![name hasPrefix:@"XZKit."]) {
        name = [NSString stringWithFormat:@"XZKit.%@", name];
    }
   
    Class newClass = xz_objc_createClassWithName(superClass, name, block);
    
    NSInteger i = 0;
    while (newClass == Nil) {
        NSString *newName = [NSString stringWithFormat:@"%@.%ld", name, (long)(i++)];
        newClass = xz_objc_createClassWithName(superClass, newName, block);
    }
    
    return newClass;
}


#pragma mark - 添加方法

BOOL xz_objc_class_copyMethod(Class source, SEL sourceSelector, Class target, SEL targetSelector) {
    if (source == Nil || sourceSelector == nil) {
        return NO;
    }
    
    if (target == Nil) {
        if (targetSelector == nil) {
            return NO;
        }
        target = source;
    } else if (targetSelector == nil) {
        if (source == target) {
            return NO;
        }
        targetSelector = sourceSelector;
    }
    
    if ([target instancesRespondToSelector:targetSelector]) {
        if (xz_objc_class_getInstanceMethod(target, targetSelector) != nil) {
            return NO;
        }
    }
    
    Method       const mtd = class_getInstanceMethod(source, sourceSelector);
    IMP          const imp = method_getImplementation(mtd);
    const char * const enc = method_getTypeEncoding(mtd);
    
    return class_addMethod(target, targetSelector, imp, enc);
}

NSInteger xz_objc_class_copyMethods(Class source, Class target) {
    NSInteger __block result = 0;
    
    unsigned int count = 0;
    Method *oldMethods = class_copyMethodList(target, &count);
    xz_objc_class_enumerateInstanceMethods(source, ^BOOL(Method method, NSInteger index) {
        // 不复制同名的方法
        for (unsigned int i = 0; i < count; i++) {
            if (oldMethods[i] == method) return YES;
            if (method_getName(oldMethods[i]) == method_getName(method)) return YES;
        }
        // 复制方法
        SEL          const sel = method_getName(method);
        IMP          const imp = method_getImplementation(method);
        const char * const enc = method_getTypeEncoding(method);
        if (class_addMethod(target, sel, imp, enc)) {
            result += 1;
        }
        return YES;
    });
    free(oldMethods);
    
    return result;
}

