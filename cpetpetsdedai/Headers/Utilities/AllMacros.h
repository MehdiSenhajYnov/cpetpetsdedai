#pragma once

#define DefaultConstructor(className, baseClassName) \
className() : baseClassName(#className, baseClassName::GetStaticType()) { }\
className(const std::string& _name, Type* parentType) : baseClassName(_name, parentType) { }\

