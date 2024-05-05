#pragma once

#include "TypeInfo.h"
#include <string>
#include <unordered_map>

#include "RegisterType.h"
#include "TypeId.h"

class VariableId final
{
private:

	const static uint32_t ConstFlag				= 1 << 0;
	const static uint32_t ReferenceFlag			= 1 << 1;
	const static uint32_t VolatileFlag			= 1 << 2;
	const static uint32_t RValReferenceFlag		= 1 << 3;

public:

	explicit VariableId(TypeId id) : Type{ id } {};
	VariableId() = default;

	template <typename T>
	static VariableId Create();

public:
	TypeId GetTypeId						() const			{ return Type; }
	void SetTypeId						(TypeId id)			{ Type = id; }

	void SetConstFlag						()					{ TraitFlags |= ConstFlag; }
	void SetReferenceFlag					()					{ TraitFlags |= ReferenceFlag; }
	void SetVolatileFlag					()					{ TraitFlags |= VolatileFlag; }
	void SetRValReferenceFlag				()					{ TraitFlags |= RValReferenceFlag; }

	void RemoveConstFlag					()					{ TraitFlags &= ~ConstFlag; }
	void RemoveReferenceFlag				()					{ TraitFlags &= ~ReferenceFlag; }
	void RemoveVolatileFlag				()					{ TraitFlags &= ~VolatileFlag; }
	void RemoveRValReferenceFlag			()					{ TraitFlags &= ~RValReferenceFlag; }

	void SetPointerAmount					(uint16_t amount)	{ PointerAmount = amount; }
	uint32_t GetPointerAmount				() const			{ return PointerAmount; }

	void SetArraySize						(uint32_t Size)		{ ArraySize = Size; }
	uint32_t GetArraySize					() const			{ return ArraySize; }

	bool IsConst							() const			{ return TraitFlags & ConstFlag; }
	bool IsReference						() const			{ return TraitFlags & ReferenceFlag; }
	bool IsVolatile						() const			{ return TraitFlags & VolatileFlag; }
	bool IsRValReference					() const			{ return TraitFlags & RValReferenceFlag; }
	bool IsPointer						() const			{ return PointerAmount; }
	bool IsArray							() const			{ return ArraySize == 1; }
	bool IsRefOrPointer					() const			{ return IsPointer() || IsReference() || IsRValReference(); }

	uint32_t GetSize						() const			{ return IsRefOrPointer() ? sizeof(void*) : (GetTypeId().GetTypeSize() * GetArraySize()); }
	uint32_t GetAlign						() const			{ return IsRefOrPointer() ? alignof(void*) : GetTypeId().GetTypeAlignment(); }

	uint64_t	GetHash						() const			{ return Type.GetId() ^ ArraySize ^ (static_cast<uint64_t>(PointerAmount) << 32) ^ (static_cast<uint64_t>(TraitFlags) << 40); }

	friend bool operator==(const VariableId& lhs, const VariableId& rhs);

private:

	TypeId		Type			;	// The underlying type id
	uint32_t	ArraySize		{ };	// if the variable is a fixed sized array, the size will be contained in this. else it will be 1
	uint16_t	PointerAmount	{ };	// The amount of pointers that are attached to the Type
	uint8_t		TraitFlags		{ };	// Other flags (const, volatile, reference, RValReference)

};



template <typename T>
uint32_t CountPointers(uint32_t counter = 0)
{
	if (std::is_pointer_v<T>)
		return CountPointers<std::remove_pointer_t<T>>(++counter);
	else
		return counter;
}

template <typename T> struct remove_all_pointers
{
	using Type = T;
};

template <typename T> struct remove_all_pointers<T*>
{
	using Type = remove_all_pointers<T>::Type;
};

template <typename T>
using remove_all_pointers_t = remove_all_pointers<T>::Type;



template<typename T>
inline VariableId VariableId::Create()
{
	using Type_RemovedExtents = std::remove_all_extents_t<T>;
	using Type_RemovedRefs = std::remove_reference_t<Type_RemovedExtents>;
	using Type_RemovedPtrs = remove_all_pointers_t<Type_RemovedRefs>;

	using StrippedType = std::remove_cvref_t<Type_RemovedPtrs>;
	RegisterType<StrippedType> TypeRegister{};

	bool IsRef{ std::is_reference_v<T> };
	bool IsRValRef{ std::is_rvalue_reference_v<T> };
	bool IsConst{ std::is_const_v<Type_RemovedPtrs> };
	bool IsVolatile{ std::is_volatile_v<Type_RemovedPtrs> };

	uint32_t PointerAmount{ CountPointers<Type_RemovedRefs>() };

	auto variable = VariableId(TypeId::Create<StrippedType>());

	if (IsConst)		variable.SetConstFlag();
	if (IsVolatile)	variable.SetVolatileFlag();
	if (IsRef)		variable.SetReferenceFlag();
	if (IsRValRef)	variable.SetRValReferenceFlag();

	variable.SetPointerAmount(PointerAmount);

	if (!std::is_same_v<void, Type_RemovedExtents>)
	{
		uint32_t ArraySize{ sizeof(T) / sizeof(Type_RemovedExtents) };
		variable.SetArraySize(ArraySize);
	}
	else
	{
		variable.SetArraySize(1);
	}

	return variable;
}



template <>
struct std::hash<VariableId>
{
	std::size_t operator()(const VariableId& id) const noexcept
	{
		return static_cast<size_t>(id.GetHash());
	}
};

bool operator==(const VariableId& lhs, const VariableId& rhs)
{
	return	lhs.Type == rhs.Type &&
			lhs.ArraySize == rhs.ArraySize &&
			lhs.PointerAmount == rhs.PointerAmount &&
			lhs.TraitFlags == rhs.TraitFlags;
}

inline const std::string& GetVariableName(const VariableId& variableId)
{
	static std::unordered_map<VariableId, std::string> VariableNames{};

	auto it = VariableNames.find(variableId);
	if (it != VariableNames.end())
	{
		return it->second;
	}

	{
		std::string Name = variableId.GetTypeId().GetTypeInfo()->Name;

		if (variableId.IsVolatile()) Name = "volatile " + Name;
		if (variableId.IsConst()) Name = "const " + Name;

		const uint32_t pointerAmount = variableId.GetPointerAmount();
		for (uint32_t i{}; i < pointerAmount; ++i)
		{
			Name += '*';
		}
		
		if (variableId.GetArraySize() > 1)
		{
			Name += '[';
			Name += std::to_string(variableId.GetArraySize());
			Name += ']';
		}

		if (variableId.IsRValReference()) Name += "&&";
		else if (variableId.IsReference()) Name += '&';

		return VariableNames.emplace(variableId, std::move(Name)).first->second;
	}
}