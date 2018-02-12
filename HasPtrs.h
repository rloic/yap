#pragma once

#include <memory>

template<typename C>
class HasPtrs<C> {
    using Ptr = std::shared_ptr<C>;
    using ConstPtr = std::shared_ptr<const C>;
    using UniquePtr = std::unique_ptr<C>;
};
