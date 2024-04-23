#pragma once
#include <string>

class Type {
public:
	Type(const std::string& name, Type* parent);

	std::string GetName();
	Type* GetParent();
	bool operator==(const Type& Other) const{return name == Other.name && parent == Other.parent;}

private:
	std::string name;
	Type *parent = nullptr;

};
