#include <iostream>
template<typename T>
concept CanString = requires(const T& t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};
