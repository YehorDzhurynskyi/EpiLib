#pragma once

#include "EpiCore/common.h"

EPI_NAMESPACE_BEGIN()

template<typename ReturnT, typename T>
std::shared_ptr<ReturnT> ImplOf(const T& obj)
{
    static_assert(std::is_base_of_v<T::Impl, ReturnT>);

    std::shared_ptr<ReturnT> r = std::static_pointer_cast<ReturnT>(T::Impl::ExtractImpl(obj));
    epiAssert(r != nullptr);

    // TODO: log null via source_location

    return r;
}

EPI_NAMESPACE_END()
