#pragma once


class TypeNameUtilities
{
public:
    template <typename T>
    static std::string_view TypeName();


    template <>
    static std::string_view TypeName<void>()
    {
        return "void";
    }

    

};

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
        return wrapped_type_name<type_name_prober>().find(TypeNameUtilities::TypeName<type_name_prober>());
    }

    static constexpr std::size_t wrapped_type_name_suffix_length()
    {
        return wrapped_type_name<type_name_prober>().length()
            - wrapped_type_name_prefix_length()
            - TypeNameUtilities::TypeName<type_name_prober>().length();
    }
};




template <typename T>
std::string_view TypeNameUtilities::TypeName()
{
    auto wrapped_name = TypeNameWrapper::wrapped_type_name<T>();
    auto prefix_length = TypeNameWrapper::wrapped_type_name_prefix_length();
    auto suffix_length = TypeNameWrapper::wrapped_type_name_suffix_length();
    auto type_name_length = wrapped_name.length() - prefix_length - suffix_length;
    return wrapped_name.substr(prefix_length, type_name_length);
}
