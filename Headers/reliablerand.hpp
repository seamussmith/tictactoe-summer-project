#ifndef _RELIABLE_RAND_
#define _RELIABLE_RAND_

#include <cassert>
#include <random>
#include <ctime>

namespace relrand
{
    static std::random_device rd;
    static std::mt19937 generator(rd() + time(NULL));
    template<class Type = int> // Default type for genint is int. Can be changed to any integer type.
    Type genint(Type min, Type max, std::mt19937* gen = &generator)
    {
        assert(min < max); // Make sure min is less than max
        std::uniform_int_distribution<Type> dist(min, max);
        return dist(*gen);
    }
    double genfloat(double min, double max, std::mt19937* gen = &generator) // Probably not neccessary to make function for 32bit float. Will be automatically truncated if assigned to 32bit float
    {
        assert(min < max); // Make sure min is less than max
        std::uniform_real_distribution<double> dist(min, max);
        return dist(*gen);
    }
}

#endif
