#pragma once

class CoreUtils
{
public:
    static std::wstring GetResourceFolder();
    static std::string Demangle(std::string name);

    template <class T>
    static std::string type(const T& t) {
        return Demangle(typeid(t).name());
    }
};
