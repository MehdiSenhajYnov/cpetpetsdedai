#pragma once
#include <string>
#include <map>
#include <iostream>
#include <ostream>

#include "ISerialisable.h"
#include "../../Factory.h"
#include "../../Type.h"
#include "../Utilities/AllMacros.h"
#include "../Utilities/Event.h"
#include "../Utilities/ExternClassOperator.h"

template <typename T>
class RegisterClass 
{
public:
	RegisterClass()
	{
		if constexpr (IsType<T>)
		{
			if constexpr (HasDefaultConstructor<T>)
			{
				std::cout << "Registering class: " << T::GetStaticType()->GetName() << std::endl;
				Factory::GetInstance()->RegisterType(T::GetStaticType()->GetName(),
					[](){
					return Factory::GetInstance()->CreateObject<T>();
				},
				[](uint64_t _id){
								return Factory::GetInstance()->CreateObject<T>(_id);
							}
				);
			} else
			{
				std::cout << "Cannot register class: " << T::GetStaticType()->GetName() << std::endl;
			}
			
		} else
		{
			std::cout << "Cannot register class, no type class" << std::endl;
		}
	}
};

class Object : public ISerialisable {
public:
	ADD_TYPE_NO_PARENT(Object, REG_TYPE)
	
	//Object(std::string typeName, Type* parentType);
	Type* GetType();

	virtual void PreDestroy() {}
	virtual ~Object() override = default ;

	[[nodiscard]] uint64_t GetId() const;
	void SetId(uint64_t _id);
	Event<uint64_t, uint64_t>& OnIdChanged() { return onIdChanged; }
public:

	virtual uint64_t Serialize(SerializeBuffer& buffer, const std::string_view _previousContent) override;

	virtual bool Deserialize(const std::string& _serialised, const std::string& _serializeContext) override;

	//virtual void Deserialize(const TList<std::string>& _serialised);

	template <typename T>
	static T* Create();
	
	template <typename T>
	static T* Create(uint64_t _id);

	void SetCanBeSerialized(bool _canBeSerialized) { CanBeSerialized = _canBeSerialized; }
	bool GetCanBeSerialized() const { return CanBeSerialized; }
	
private:

	Event<uint64_t, uint64_t> onIdChanged;
	uint64_t id;
	Type type;
	bool CanBeSerialized = true;
protected:
	Object() = default;
	Object(const std::string& typeName, Type* parentType);
	
};

template <typename T>
T* Object::Create()
{
	return Factory::GetInstance()->CreateObject<T>();
}

template <typename T>
T* Object::Create(uint64_t _id)
{
	return Factory::GetInstance()->CreateObject<T>(_id);
}




