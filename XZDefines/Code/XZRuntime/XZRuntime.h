//
//  XZRuntime.h
//  XZKit
//
//  Created by Xezun on 2021/5/7.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - 基础方法

/// 获取类 aClass 自身的 selector 实例方法，即不计算从父类继承的方法。
/// @note 为提高性能，使用本方法前可先检测类 cls 是否能响应 target 方法。
/// @code
/// if ([cls instancesRespondToSelector:target]) {
///     Method method = xz_objc_class_getInstanceMethod(cls, target);
///     if (method == nil) {
///         NSLog(@"方法 %s 从父类继承而来", target);
///     }
/// }
/// @endcode
/// @param aClass 待获取方法的类
/// @param selector 待获取方法
FOUNDATION_EXPORT Method _Nullable xz_objc_class_getInstanceMethod(Class const aClass, SEL const selector);

/// 遍历类实例对象的方法，不包括父类的方法。
/// @param aClass 类。
/// @param block 遍历所用的 block 块，返回 NO 遍历终止。
FOUNDATION_EXPORT void xz_objc_class_enumerateInstanceMethods(Class aClass, BOOL (^block)(Method method, NSInteger index));

/// 遍历类实例对象的变量，不包括父类。
/// @param aClass 类。
/// @param block 遍历所用的 block 。
FOUNDATION_EXPORT void xz_objc_class_enumerateInstanceVariables(Class aClass, void (^block)(Ivar ivar));

/// 获取类实例对象的变量名。
/// @param aClass 类。
FOUNDATION_EXPORT NSArray<NSString *> * _Nullable xz_objc_class_getInstanceVariableNames(Class aClass);

/// 将指定类的 方法1 与 方法2 的方法体互换。
/// @param aClass 需要替换方法体的类。
/// @param selector1 待交换方法体的方法。
/// @param selector2 被交换方法体的方法。
FOUNDATION_EXPORT void xz_objc_class_exchangeInstanceMethods(Class aClass, SEL selector1, SEL selector2);

/// 给 aClass 添加 selector 方法。
///
/// @discussion
/// 重写方法，调用父类的方法，不能直接使用 super 调用，因为编译器编译 super 的规则发生了改变：
/// 编译器不再使用`self`来获取父类，而是直接使用所定义类的名字来获取，`super`不再有动态性。
///
/// 可以使用下面的方法手动向父类发送消息。
/// @code
/// struct objc_super _super = {
///     .receiver = self,
///     .super_class = class_getSuperclass(object_getClass(self))
/// };
/// ((void (*)(struct objc_super *, SEL, BOOL))objc_msgSendSuper)(&_super, @selector(viewWillAppear:), animated);
/// @endcode
///
/// @param aClass 待添加方法的类。
/// @param selector 待添加方法的名称。
/// @param source 提供方法 IMP 的类，如果为 nil 值，则使用自身，且不能与 creation 同时为 nil 值。
/// @param creation 如果待添加的方法为新方法时，将选择此方法的 IMP 为新方法的 IMP 使用，如果为空，则使用与待添加方法相同名称的方法。
/// @param override 如果待添加的方法已由父类实现，将选择此方法的 IMP 为新方法的 IMP 使用。
/// @param exchange 如果待添加的方法已由自身实现，将选择此方法的 IMP 与原方法交换 IMP 使用。
FOUNDATION_EXPORT BOOL xz_objc_class_addMethod(Class aClass, SEL selector, Class _Nullable source, SEL _Nullable creation, SEL _Nullable override, SEL _Nullable exchange);


#pragma mark - 创建类

/// @define
/// 构造 Class 的块函数。
/// @param newClass 构造过程中的 Class 对象，只可用来添加变量、方法，不可直接实例化
typedef void (^XZRuntimeCreateClassBlock)(Class newClass);

/// 派生子类或创建新类，如果已存在，则返回 Nil 。
/// @param superClass 新类的超类，如果为 Nil 则表示创建基类
/// @param name 新类的类名
/// @param block 给新类添加实例变量的操作必须在此block中执行
FOUNDATION_EXPORT Class _Nullable xz_objc_createClassWithName(Class _Nullable superClass, NSString *name, NS_NOESCAPE XZRuntimeCreateClassBlock _Nullable block);

/// 创建类，不指定名字。
/// @note 子类命名格式为 `XZKit.SuperClassName.<number>` 即每次调用此函数，都会生成一个新的类。
/// @param superClass 新类的超类
/// @param block 给新类添加实例变量的操作必须在此block中执行
FOUNDATION_EXPORT Class xz_objc_createClass(Class superClass, NS_NOESCAPE XZRuntimeCreateClassBlock _Nullable block);



#pragma mark - 添加方法


/// 复制方法：将类 source 的方法 sourceSelector 复制为类 target 的 targetSelector 方法。
/// @discussion
/// 如果 target 自身已存在 targetSelector 方法，则不复制，返回 NO 值。
/// @discussion
/// 参数 target 和 targetSelector 不能同时为 nil 值，否则返回 NO 值。
/// @param source 被复制方法的类
/// @param sourceSelector 被复制方法的方法名
/// @param target 待添加方法的类，如果为 nil 则表示使用 source
/// @param targetSelector 待添加的方法名，为 nil 则使用 sourceSelector
/// @returns 是否复制成功
FOUNDATION_EXPORT BOOL xz_objc_class_copyMethod(Class source, SEL sourceSelector, Class _Nullable target, SEL _Nullable targetSelector);

/// 将 source 自身的所有实例方法都复制到 target 上，不包括 super 的方法。
/// @discussion
/// 复制会跳过 target 自身存在的同名方法，同样不包括 super 的方法。
/// @param source 被复制方法的类
/// @param target 待添加方法的类
/// @return 被成功复制的方法的数量
FOUNDATION_EXPORT NSInteger xz_objc_class_copyMethods(Class source, Class target);



NS_ASSUME_NONNULL_END
