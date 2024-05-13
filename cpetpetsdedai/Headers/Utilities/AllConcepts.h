#pragma once
#include <iostream>
#include <vector>

template<typename T>
concept CanString = requires(const T& t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};


template<typename Base, typename Derived>
constexpr bool isBaseOf()
{
    if constexpr (std::is_pointer_v<Base>)
    {
        using CleanedBase = std::remove_pointer_t<Base>;
        return isBaseOf<CleanedBase, Derived>();
    }
    if constexpr (std::is_pointer_v<Derived>)
    {
        using CleanedDerived = std::remove_pointer_t<Derived>;
        return isBaseOf<Base, CleanedDerived>();
    }
    return std::is_base_of_v<Base, Derived>;
}

template<typename Derived, typename Base>
concept IsDerivedFrom = isBaseOf<Base, Derived>();

template<typename Base, typename Derived>
concept IsBaseOf = isBaseOf<Base, Derived>();

template <typename T>
concept IsSceneClass = requires (T t) {
    t.InitializeScene();
    t.Update();
    t.OnKeyDown();
    t.DestroyScene();
};

template<typename T>
concept IsType = requires(T t) {
    T::GetStaticType();
};

struct SerializeBuffer;

template<typename T>
concept IsSerialisable = requires(T t) {
    t.Serialize(std::declval<SerializeBuffer&>(), std::declval<std::string_view>());
    t.Deserialize("", "");
};

template <typename T>
concept InternalHasValue = requires {
    typename T::value_type;
};

template <typename VectorClass>
constexpr bool InternalIsVector()
{
    if constexpr (InternalHasValue<VectorClass>)
    {
        using ElementClass = typename VectorClass::value_type;
        if constexpr (std::is_base_of_v<std::vector<ElementClass>, VectorClass>)
        {
            return true;
        }
    }
    return false;	
}

template <typename T>
concept IsVector = InternalIsVector<T>();

