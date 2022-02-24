#pragma once
#include "boost/container_hash/hash.hpp"

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
    boost::hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types & ... args) noexcept
{
    hash_value(seed, value);
    hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}