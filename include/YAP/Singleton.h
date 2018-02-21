#pragma once

#include <type_traits>

namespace YAP {

template<typename T>
class Singleton {
protected:
    Singleton() noexcept = default;
    virtual ~Singleton() = default;

public:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

public:
    static T &Instance() noexcept(std::is_nothrow_constructible<T>::value) {
        static T instance;
        return instance;
    }

    static T *InstancePtr() noexcept(std::is_nothrow_constructible<T>::value) {
        return &T::Instance();
    }
};

} // namespace YAP
