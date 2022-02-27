#pragma once
#include <string>
#include <iterator>
#include <exception>

enum class Function
{
    RSHash = 0,
    JSHash,
    PJWHash,
    ELFHash,
    BKDRHash,
    SDBMHash,
    DJBHash,
    DEKHash,
    APHash
};

std::size_t RSHash(std::string str, std::size_t length)
{
    const std::size_t b = 378551;
    std::size_t a = 63689;
    std::size_t hash = 0;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash = hash * a + (*begin);
        a *= b;
    }

    return hash;
}

std::size_t JSHash(std::string str, std::size_t length)
{
    std::size_t hash = 1315423911;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash ^= ((hash << 5) + (*begin) + (hash >> 2));
    }

    return hash;
}

std::size_t PJWHash(std::string str, std::size_t length)
{
    const std::size_t BitsInUnsignedInt = (std::size_t)(sizeof(std::size_t) * 8);
    const std::size_t ThreeQuarters = (std::size_t)((BitsInUnsignedInt * 3) / 4);
    const std::size_t OneEighth = (std::size_t)(BitsInUnsignedInt / 8);
    const std::size_t HighBits =
        (std::size_t)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    std::size_t hash = 0;
    std::size_t test = 0;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash = (hash << OneEighth) + (*begin);

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

std::size_t ELFHash(std::string str, std::size_t length)
{
    std::size_t hash = 0;
    std::size_t x = 0;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash = (hash << 4) + (*begin);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

std::size_t BKDRHash(std::string str, std::size_t length)
{
    std::size_t seed = 131; /* 31 131 1313 13131 131313 etc.. */
    std::size_t hash = 0;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash = (hash * seed) + (*begin);
    }

    return hash;
}

std::size_t SDBMHash(std::string str, std::size_t length)
{
    std::size_t hash = 0;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash = (*begin) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

std::size_t DJBHash(std::string str, std::size_t length)
{
    std::size_t hash = 5381;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash = ((hash << 5) + hash) + (*begin);
    }

    return hash;
}

std::size_t DEKHash(std::string str, std::size_t length)
{
    std::size_t hash = length;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*begin);
    }

    return hash;
}

std::size_t APHash(std::string str, std::size_t length)
{
    std::size_t hash = 0xAAAAAAAA;
    std::string::iterator begin = str.begin();

    for (auto i = 0U; i < length; ++begin, ++i)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*begin) * (hash >> 3)) :
            (~((hash << 11) + ((*begin) ^ (hash >> 5))));
    }

    return hash;
}

std::size_t Hash(std::string str, Function function , std::size_t length = 10)
{
    switch (function)
    {
    case(Function::RSHash):
        return RSHash(str, length);
    case(Function::JSHash):
        return JSHash(str, length);
    case(Function::ELFHash):
        return ELFHash(str, length);
    case(Function::APHash):
        return APHash(str, length);
    case(Function::BKDRHash):
        return BKDRHash(str, length);
    case(Function::DEKHash):
        return DEKHash(str, length);
    case(Function::DJBHash):
        return DJBHash(str, length);
    case(Function::PJWHash):
        return PJWHash(str, length);
    case(Function::SDBMHash):
        return SDBMHash(str, length);
    default:
        throw std::exception("Unfound hash function");
    }
}