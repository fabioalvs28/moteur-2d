#include "pch.h"
#include "CoreUtils.h"

std::wstring CoreUtils::GetResourceFolder()
{
#ifdef _DEBUG
    return L"../../res/";
#else
    return L"../../res/";
#endif
}

std::string CoreUtils::Demangle(std::string name)
{
    for(int i = 0; i < 6;i++)
        name.erase(name.begin());

    return name;
}
