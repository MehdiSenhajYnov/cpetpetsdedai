#pragma once

#define DefaultConstructorNoParams(className, baseClassName) \
className::className() : className(#className, baseClassName::GetStaticType()) { }

#define DefaultConstructorTypeParams(className, baseClassName) \
className::className(const std::string& _typeName, Type* parentType) : baseClassName(_typeName, parentType) { }

#define DefaultConstructorIdTypeParams(className, baseClassName) \
className::className(const uint64_t& _id, const std::string& _name, Type* parentType): baseClassName(_id, _name, parentType) {}

#define DefaultConstructorId(className, baseClassName) \
className::className(uint64_t _id): className(_id, #className, baseClassName::GetStaticType()) {}

#define DefaultConstructor(className, baseClassName) \
DefaultConstructorNoParams(className, baseClassName) \
DefaultConstructorTypeParams(className, baseClassName) \
DefaultConstructorId(className, baseClassName) \
DefaultConstructorIdTypeParams(className, baseClassName) \


#define HeaderDefaultConstructorNoParams(className) \
className();

#define HeaderDefaultConstructorTypeParams(className) \
className(const std::string& _name, Type* parentType);

#define HeaderDefaultConstructorIdTypeParams(className) \
className(const uint64_t& _id, const std::string& _name, Type* parentType);

#define HeaderDefaultConstructorId(className) \
className(uint64_t _id);

#define HeaderDefaultConstructor(className) \
HeaderDefaultConstructorNoParams(className) \
HeaderDefaultConstructorTypeParams(className) \
HeaderDefaultConstructorId(className) \
HeaderDefaultConstructorIdTypeParams(className) \

