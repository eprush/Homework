#pragma once
#include <chrono>
#include <random>
#include <set>
#include <string>
#include "boost/container_hash/hash.hpp"

template < typename T >
void hash_value(const T& value, std::size_t& seed = 0) noexcept
{
    hash_combine(value, seed);
}

template < typename T, typename ... Types >
void hash_value( const T& value, const Types & ... args, std::size_t& seed = 0) noexcept
{
    boost::hash_combine(seed, value);
    hash_value(args..., seed);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
    std::size_t seed = 0;
    hash_value(args..., seed);
    return seed;
}

std::set < std::string > make_random_words(std::size_t N, std::size_t length = 10) // length = 10 - good enough
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast <std::size_t> (
        std::chrono::system_clock::now().time_since_epoch().count()));

    std::set < std::string > words;

    for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
        for (auto& c : s)
            c = letter(e);

    return words;
}
