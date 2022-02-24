#pragma once
#include <chrono>
#include <random>
#include <set>
#include <string>
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

std::size_t RSHash(const char* str, std::size_t length)
{
    std::size_t b = 378551;
    std::size_t a = 63689;
    std::size_t hash = 0;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a = a * b;
    }

    return hash;
}

std::size_t JSHash(const char* str, std::size_t length)
{
    std::size_t hash = 1315423911;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

std::size_t PJWHash(const char* str, std::size_t length)
{
    const std::size_t BitsInUnsignedInt = (std::size_t)(sizeof(std::size_t) * 8);
    const std::size_t ThreeQuarters = (std::size_t)((BitsInUnsignedInt * 3) / 4);
    const std::size_t OneEighth = (std::size_t)(BitsInUnsignedInt / 8);
    const std::size_t HighBits =
        (std::size_t)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    std::size_t hash = 0;
    std::size_t test = 0;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

std::size_t ELFHash(const char* str, std::size_t length)
{
    std::size_t hash = 0;
    std::size_t x = 0;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

std::size_t BKDRHash(const char* str, std::size_t length)
{
    std::size_t seed = 131; /* 31 131 1313 13131 131313 etc.. */
    std::size_t hash = 0;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

std::size_t SDBMHash(const char* str, std::size_t length)
{
    std::size_t hash = 0;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

std::size_t DJBHash(const char* str, std::size_t length)
{
    std::size_t hash = 5381;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

std::size_t DEKHash(const char* str, std::size_t length)
{
    std::size_t hash = length;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

std::size_t APHash(const char* str, std::size_t length)
{
    std::size_t hash = 0xAAAAAAAA;
    std::size_t i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
            (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
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
