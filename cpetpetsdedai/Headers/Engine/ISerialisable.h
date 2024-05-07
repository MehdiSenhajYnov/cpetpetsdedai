#pragma once
#include <string>

#include "../SerializeBuffer.h"
#include "../Utilities/AllConcepts.h"

class ISerialisable {
public:
	virtual          ~ISerialisable() = default;
	virtual uint64_t Serialize(SerializeBuffer& buffer) = 0;
	virtual void     Deserialize(const std::string& _serialised) = 0;

	template <typename T>
	static uint64_t Serializer(SerializeBuffer& buffer, T& object)
	{
		if constexpr (std::is_pointer<T>())
		{
			if (ISerialisable::IsOrIsPointerSerializable<T>(object))
			{

				
				std::cout << "pointer serializable" << std::endl;
			} else
			{
				std::cout << "pointer not serializable" << std::endl;
			}
		}
		else if constexpr (isSerialisable<T>)
		{
			return object.Serialize(buffer);
		}
		else if constexpr (CanString<T>)
		{
			buffer.mainBuffer << object;
		}
		else
		{
			std::cout << "WARNING : "<< typeid(object).name() <<" is not serializable !" << std::endl;
		}
		return 0;
	}

	template <typename T>
	static bool IsOrIsPointerSerializable(T& object)
	{
		if constexpr (std::is_pointer<T>())
		{
			return IsOrIsPointerSerializable(*object);
		}
		if (isSerialisable<T>)
		{
			return true;
		}
		return false;
	}
};
