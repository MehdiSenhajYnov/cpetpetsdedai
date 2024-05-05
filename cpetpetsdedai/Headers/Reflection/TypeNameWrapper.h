#pragma once
#include <string_view>



class TypeNameWrapper
{
public:
    
    using type_name_prober = void;

    template <typename T>
    static constexpr std::string_view wrapped_type_name()
    {
#ifdef __clang__
        return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
        return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
        return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
    }

    static constexpr std::size_t wrapped_type_name_prefix_length()
    {
        return wrapped_type_name<type_name_prober>().find(TypeName<type_name_prober>());
    }

    static constexpr std::size_t wrapped_type_name_suffix_length()
    {
        return wrapped_type_name<type_name_prober>().length()
            - wrapped_type_name_prefix_length()
            - TypeName<type_name_prober>().length();
    }
};
