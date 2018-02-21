#pragma once

#include <type_traits>

namespace YAP {

template<typename T>
class Singleton {
protected:
    Singleton() noexcept = default;
    virtual ~Singleton() = default;

public:
    // Forbid move and copy
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

public:
    inline static T &Instance() noexcept(std::is_nothrow_constructible<T>::value) {
        static T instance;
        return instance;
    }

    inline static T *InstancePtr() noexcept(std::is_nothrow_constructible<T>::value) {
        return &T::Instance();
    }
};

} // namespace YAP
