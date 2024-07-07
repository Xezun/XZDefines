//
//  XZRuntime.h
//  XZKit
//
//  Created by Xezun on 2021/5/7.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

// 命名规则：
// 所有函数默认作用于实例方法、属性、变量。

NS_ASSUME_NONNULL_BEGIN

#pragma mark - 基础方法

/// 获取类 aClass 自身的 selector 实例方法，即不计算从父类继承的方法。
/// @note 为提高性能，使用本方法前可先检测类 aClass 是否能响应 target 方法。
///
/// @code
/// ```objc
/// if ([aClass instancesRespondToSelector:target]) {
///     Method method = xz_objc_class_getMethod(aClass, target);
///     if (method == nil) {
///         NSLog(@"方法 %s 从父类继承而来", target);
///     }
/// }
/// ```
/// @endcode
///
/// @param aClass 待获取方法的类
/// @param selector 待获取方法
FOUNDATION_EXPORT Method _Nullable xz_objc_class_getMethod(Class const aClass, SEL const selector);

/// 遍历类实例对象的方法，不包括父类的方法。
/// @param aClass 类。
/// @param enumerator 遍历所用的 block 块，返回 NO 遍历终止。
FOUNDATION_EXPORT void xz_objc_class_enumerateMethods(Class aClass, BOOL (^enumerator)(Method method, NSInteger index));

/// 遍历类实例对象的变量，不包括父类。
/// @param aClass 类。
/// @param enumerator 遍历所用的 block 块，返回 NO 遍历终止。
FOUNDATION_EXPORT void xz_objc_class_enumerateVariables(Class aClass, BOOL (^enumerator)(Ivar ivar));

/// 获取类实例对象的变量名。
/// @param aClass 类。
FOUNDATION_EXPORT NSArray<NSString *> * _Nullable xz_objc_class_getVariableNames(Class aClass);

/// 将指定类的 方法1 与 方法2 的方法体互换。
/// @param aClass 需要替换方法体的类。
/// @param selector1 待交换方法体的方法。
/// @param selector2 被交换方法体的方法。
FOUNDATION_EXPORT void xz_objc_class_exchangeMethods(Class aClass, SEL selector1, SEL selector2);

/// 给 aClass 添加 selector 方法。
///
/// @discussion
/// 重写方法，调用父类的方法，不能直接使用 super 调用，因为编译器编译 super 的规则发生了改变：
/// 编译器不再使用`self`来获取父类，而是直接使用所定义类的名字来获取，`super`不再有动态性。
///
/// 可以使用下面的方法手动向父类发送消息。
///
/// @code
/// ```objc
/// struct objc_super _super = {
///     .receiver = self,
///     .super_class = class_getSuperclass(object_getClass(self))
/// };
/// ((void (*)(struct objc_super *, SEL, BOOL))objc_msgSendSuper)(&_super, @selector(viewWillAppear:), animated);
/// ```
/// @endcode
///
/// @param aClass 待添加方法的类。
/// @param selector 待添加方法的名称。
/// @param source 提供方法 IMP 的类，如果为 nil 值，则使用自身，且不能与 creation 同时为 nil 值。
/// @param creation 如果待添加的方法为新方法时，将选择此方法的 IMP 为新方法的 IMP 使用，如果为空，则使用与待添加方法相同名称的方法。
/// @param override 如果待添加的方法已由父类实现，将选择此方法的 IMP 为新方法的 IMP 使用。
/// @param exchange 如果待添加的方法已由自身实现，那么想将此方法复制到 aClass 上，然后再交换 IMP 使用；如果 aClass 已有 exchange 方法，则添加方法失败。
FOUNDATION_EXPORT BOOL xz_objc_class_addMethod(Class aClass, SEL selector, Class _Nullable source, SEL _Nullable creation, SEL _Nullable override, SEL _Nullable exchange);

/// 获取 aClass 实例方法的 type-encoding 字符串。
/// @param aClass 获取的对象的类。
/// @param selector 获取的方法名。
FOUNDATION_EXPORT const char * _Nullable xz_objc_class_getMethodTypeEncoding(Class aClass, SEL selector);

/// 通过块函数给对象添加方法。
/// @discussion
/// 块函数形式如 `block(self, args...)` 并将作为原生函数 `imp_implementationWithBlock(block)` 的参数使用。
///
/// @code
/// ```objc
/// // 先在任意类上定义一个待添加的方法，用于获取 type-encoding ，如果熟悉编码规则，也可以手写。
/// const char *encoding = xz_objc_class_getMethodTypeEncoding([AnyClass class], @selector(sayHello:));
/// // 向 Foobar 上添加 -sayHello: 方法。
/// xz_objc_class_addMethodWithBlock([Foobar class], @selector(sayHello:), encoding, ^NSString *(Foobar *self, NSString *name) {
///     return [NSString stringWithFormat:@"Hello %@!", name];
/// }, ^NSString *(Foobar *self, NSString *name) {
///     struct objc_super super = {
///         .receiver = self,
///         .super_class = class_getSuperclass(object_getClass(self))
///     };
///     // 调用父类方法，相当于 [super sayHello:name]
///     NSString *word = ((NSString *(*)(struct objc_super *, SEL, NSString *))objc_msgSendSuper)(&super, @selector(sayHello:), name);
///     return [NSString stringWithFormat:@"override %@", word];
/// }, ^id _Nonnull(SEL  _Nonnull selector) {
///     return ^NSString *(Foobar *self, NSString *name) {
///         // 调用原始方法，相当于 [self exchange_sayHello:name]
///         NSString *word = ((NSString *(*)(Foobar *, SEL, NSString *))objc_msgSend)(self, selector, name);
///         return [NSString stringWithFormat:@"exchange %@", word];
///     };
/// });
/// ```
/// @endcode
///
/// 在 Swift 中，必须使用 `@convention(block)` 将闭包转换为 `block` 才能作为方法的 IMP 使用。
///
/// 由于 Swift 不支持 `objc_msgSend` 和 `objc_msgSendSuper` 函数，我们需要将调用父类和调用原始方法的逻辑使用 OC 实现。
///
/// @code
/// ```objc
/// NSString *xz_msgSendSuper_sayHello(Foo *receiver, NSString *name) NS_SWIFT_NAME(xz_msgSendSuper(_:sayHello:)) {
///     struct objc_super super = {
///         .receiver = receiver,
///         .super_class = class_getSuperclass(object_getClass(receiver))
///     };
///     return ((NSString *(*)(struct objc_super *, SEL, NSString *))objc_msgSendSuper)(&super, @selector(sayHello:), name);
/// }
///
/// NSString *xz_msgSendExchange_sayHello(Foo *receiver, SEL selector, NSString *name) NS_SWIFT_NAME(xz_msgSend(_:exchange:sayHello:))  {
///     return ((NSString *(*)(Foo *, SEL, NSString *))objc_msgSend)(receiver, selector, name);
/// }
/// ```
/// @endcode
///
/// @code
/// ```swift
/// typealias MethodBlock = @convention(block) (Foo, String) -> String
/// let selector = #selector(Bar.sayHello(_:))      // 在 Bar 上定义了一个我们要添加的方法，以便获取方法的 type-encoding
/// let encoding = xz_objc_class_getMethodTypeEncoding(Bar.self, selector)
/// let creation: MethodBlock = { `self`, name in   // 在 block 中，使用 self 代表 Foo 对象
///     return "Hello \(name)";
/// }
/// let override: MethodBlock = { `self`, name in
///     let word = xz_msgSendSuper(self, sayHello: name);
///     return "override \(word)"
/// }
/// let exchange = { (_ selector: Selector) in
///     let exchange: MethodBlock = { `self`, name in
///         let word = xz_msgSend(self, exchange: selector, sayHello: name)
///         return "exchange \(word)"
///     }
/// }
/// xz_objc_class_addMethodWithBlock(Foo.self, selector, encoding, creation, override, exchange)
/// ```
/// @endcode
///
/// 在 Swift 中，必须使用 `@convention(block)` 标记的闭包，才能作为方法的实现。
///
/// 且由于 Swift 不支持 `objc_msgSend` 和 `objc_msgSendSuper` 函数，避免将调用父类和调用原始方法的逻辑使用 OC 实现。
///
/// @code
/// typealias MethodType = @convention(block) (Foobar, String) -> String
/// let creation: MethodType = { `self`, name in
///     return "Hello \(name)";
/// }
/// let override: MethodType = { `self`, name in
///     let word = Foobar.msgSendSuper(self, name);
///     return "override \(word)"
/// }
/// let exchange = { (_ selector: Selector) in
///     let exchange: MethodType = { `self`, name in
///         let word = Foobar.msgSendExchange(selector, self, name)
///         return "exchange \(word)"
///     }
/// }
/// xz_objc_class_addMethodWithBlock(Foobar.self, #selector(sayHello(_:)), encoding, creation, override, exchange)
/// @endcode
///
/// @param aClass 要添加方法的类。
/// @param selector 要添加的方法名。
/// @param encoding 待添加方法的 type-encoding 编码，如果是已存在的方法，可以为 NULL 值。
/// @param creation 如果待添加的方法未创建，则使用此块函数作为 IMP 新建方法，同时参数 encoding 必须提供。
/// @param override 如果待添加的方法已由超类实现，则使用此块函数作为 IMP 重写方法。
/// @param exchange 如果待添加的方法已由自身实现，则使用此块函数*返回的块函数*为 IMP 构造方法，并与原方法进行交换；新构造的方法，作为此参数块函数的参数。
FOUNDATION_EXPORT BOOL xz_objc_class_addMethodWithBlock(Class aClass, SEL selector, const char * _Nullable encoding, id _Nullable creation, id _Nullable override, id (^ _Nullable exchange)(SEL selector));

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
