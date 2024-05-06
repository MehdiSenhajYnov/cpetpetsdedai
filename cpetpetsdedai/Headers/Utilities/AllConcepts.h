#pragma once
#include <iostream>
class BaseField;
class EngineUIElement;
class Object;
class GameObject;

template<typename T>
concept CanString = requires(const T& t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};

template<typename T>
concept isObject =
    std::is_base_of_v<Object, T> &&
    std::is_convertible_v<const T*, const Object*>;

template<typename T>
concept isGameObject =
    std::is_base_of_v<GameObject, T> &&
    std::is_convertible_v<const T*, const GameObject*>;

template<typename T>
concept isEngineUIElement =
    std::is_base_of_v<EngineUIElement, T> &&
    std::is_convertible_v<const T*, const EngineUIElement*>;

template<typename T>
concept isField =
    std::is_base_of_v<BaseField*, T> &&
    std::is_convertible_v<const T*, const BaseField*>;


template<typename T>
concept isSerialisable =
    std::is_base_of_v<ISerialisable*, T> &&
    std::is_convertible_v<const T*, const ISerialisable*>;