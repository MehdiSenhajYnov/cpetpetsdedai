#pragma once

#define DefaultConstructorNoParams(className, baseClassName) \
className::className() : className(#className, baseClassName::GetStaticType()) { }

#define DefaultConstructorTypeParams(className, baseClassName) \
className::className(const std::string& _typeName, Type* parentType) : baseClassName(_typeName, parentType) { }

#define DefaultConstructor(className, baseClassName) \
DefaultConstructorNoParams(className, baseClassName) \
DefaultConstructorTypeParams(className, baseClassName) \

#define HeaderDefaultConstructorNoParams(className) \
className();

#define HeaderDefaultConstructorTypeParams(className) \
className(const std::string& _name, Type* parentType);

#define HeaderDefaultConstructor(className) \
HeaderDefaultConstructorNoParams(className) \
HeaderDefaultConstructorTypeParams(className) \


// ADD TYPE WITH PARENT, MACRO CHOOSER
#define NO_CHOOSE_ZERO_ARG()

#define CHOOSER_ADD_TYPE_WITH_PARENT_AND_REGISTER(Object, Parent, toReg) INTERNAL_ADD_TYPE(Object, Parent) INTERNAL_REGISTER_TYPE(Object)
#define CHOOSER_ADD_TYPE_WITH_PARENT_CHOICE(Object, Parent) INTERNAL_ADD_TYPE(Object, Parent)
#define NO_CHOOSE_ONE_ARG(x)

#define FUNC_CHOOSER_3_ARGS_MAX(_f1, _f2, _f3, _f4, ...) _f4
#define FUNC_RECOMPOSER_3_ARGS_MAX(argsWithParentheses) FUNC_CHOOSER_3_ARGS_MAX argsWithParentheses
#define CHOOSE_FROM_ARG_COUNT_TYPE_3_ARGS_MAX(...) FUNC_RECOMPOSER_3_ARGS_MAX((__VA_ARGS__, CHOOSER_ADD_TYPE_WITH_PARENT_AND_REGISTER, CHOOSER_ADD_TYPE_WITH_PARENT_CHOICE, NO_CHOOSE_ONE_ARG, ))
#define NO_ARG_EXPANDER_3_ARGS() ,,,NO_CHOOSE_ZERO_ARG
#define ADD_TYPE_WITH_PARENT_CHOOSER(...) CHOOSE_FROM_ARG_COUNT_TYPE_3_ARGS_MAX(NO_ARG_EXPANDER_3_ARGS __VA_ARGS__ ())
#define ADD_TYPE(...) ADD_TYPE_WITH_PARENT_CHOOSER(__VA_ARGS__)(__VA_ARGS__)


// ADD TYPE WITHOUT PARENT, MACRO CHOOSER
#define CHOOSER_ADD_TYPE_NO_PARENT_AND_REGISTER(Object, toReg) INTERNAL_ADD_TYPE_NO_PARENT(Object) INTERNAL_REGISTER_TYPE(Object)
#define CHOOSER_ADD_TYPE_NO_PARENT_CHOICE(Object) INTERNAL_ADD_TYPE_NO_PARENT(Object)

#define FUNC_CHOOSER_2_ARGS_MAX(_f1, _f2, _f3, ...) _f3
#define FUNC_RECOMPOSER_2_ARGS_MAX(argsWithParentheses) FUNC_CHOOSER_2_ARGS_MAX argsWithParentheses
#define CHOOSE_FROM_ARG_COUNT_TYPE_2_ARGS_MAX(...) FUNC_RECOMPOSER_2_ARGS_MAX((__VA_ARGS__, CHOOSER_ADD_TYPE_NO_PARENT_AND_REGISTER, CHOOSER_ADD_TYPE_NO_PARENT_CHOICE, ))
#define NO_ARG_EXPANDER_2_ARGS() ,,NO_CHOOSE_ZERO_ARG
#define ADD_TYPE_NO_PARENT_CHOOSER(...) CHOOSE_FROM_ARG_COUNT_TYPE_2_ARGS_MAX(NO_ARG_EXPANDER_2_ARGS __VA_ARGS__ ())
#define ADD_TYPE_NO_PARENT(...) ADD_TYPE_NO_PARENT_CHOOSER(__VA_ARGS__)(__VA_ARGS__)





#define INTERNAL_ADD_TYPE(Object, Parent) \
private:\
inline static Type _registertype = Type(#Object, Parent::GetStaticType()); \
public:\
static Type* GetStaticType() \
{ \
static Type _objtype = Type(#Object, Parent::GetStaticType()); \
return &_objtype; \
}

#define INTERNAL_ADD_TYPE_NO_PARENT(Object) \
private:\
inline static Type _registertype = Type(#Object, nullptr); \
public:\
static Type* GetStaticType() \
{ \
static Type _objtype = Type(#Object, nullptr); \
return &_objtype; \
}

#define INTERNAL_REGISTER_TYPE(Object) inline static RegisterClass<Object> registerClass;

#define SERIALIZE_FIELD(name) \
auto _##name##SetInvoke = [this](decltype(name) _newValue) \
{ \
this->name = _newValue; \
}; \
std::function<decltype(name)()> _##name##GetInvoke = [this]() { return this->##name##; };\
GetType()->CreateField<decltype(name)>(#name, _##name##SetInvoke, _##name##GetInvoke);


#define SERIALIZE_FIELD_CSET(name, customSetFunction) \
std::function<decltype(name)()> _##name##GetInvoke = [this]() { return this->##name##; };\
GetType()->CreateFieldCSet<decltype(name)>(#name, customSetFunction, this, _##name##GetInvoke);


#define SERIALIZE_FIELD_CGET(name, customGetFunction) \
auto _##name##SetInvoke = [this](decltype(name) _newValue) \
{ \
this->name = _newValue; \
}; \
GetType()->CreateFieldCGet<decltype(name)>(#name, _##name##SetInvoke, customGetFunction, this);

#define SERIALIZE_FIELD_C(name, customSetFunction, customGetFunction) \
GetType()->CreateFieldC<decltype(name)>(#name, customSetFunction, customGetFunction, this);



#define SERIALIZE_METHOD(className, returnType, Name, ...) \
MethodContainer::AddFunction<className, returnType, __VA_ARGS__>(#Name + std::to_string(GetId()), &className::Name, this);

// MethodContainer::AddFunction<MenuScene, void, Button*>("OnPlayButtonClicked", &MenuScene::OnPlayButtonClicked, this);
