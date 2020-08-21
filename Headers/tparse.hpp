#pragma once
#include <string>
#include <stdexcept>

/*

    tparse.hpp

    � Seamus Smith 2020

*/

namespace tparse
{
    bool tryIntParse(const std::string str, int& output) // string to parse, output variable (int)
    {
        bool negative;
        if (str.find_first_not_of("-0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            try
            {
                output = std::stoi(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool tryLongParse(const std::string str, long& output) // string to parse, output variable (long)
    {
        bool negative;
        if (str.find_first_not_of("-0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            try
            {
                output = std::stol(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool tryLongParseU(const std::string str, unsigned long& output) // string to parse, output variable (unsigned long)
    {
        if (str.find_first_not_of("0123456789") == std::string::npos)
        {
            try
            {
                output = std::stoul(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool tryLLongParse(const std::string str, long long& output) // string to parse, output variable (long long)
    {
        bool negative;
        if (str.find_first_not_of("-0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            try
            {
                output = std::stoll(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool tryLLongParseU(const std::string str, unsigned long long& output) // string to parse, output variable (unsigned long long)
    {
        if (str.find_first_not_of("0123456789") == std::string::npos)
        {
            try
            {
                output = std::stoull(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool tryDoubleParse(const std::string str, double& output) // string to parse, output variable (double)
    {
        bool negative;
        int countPoint = 0;
        if (str.find_first_not_of("-.0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            for (auto i: str) // Check for duplicate decimal points
            {
                if (i == '.')
                {
                    countPoint++;
                }
                if (countPoint > 1)
                    return false;
            }
            try
            {
                output = std::stod(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool tryFloatParse(const std::string str, float& output) // string to parse, output variable (float)
    {
        bool negative;
        int countPoint = 0;
        if (str.find_first_not_of("-.0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            for (auto i: str) // Check for duplicate decimal points
            {
                if (i == '.')
                    countPoint++;
                if (countPoint > 1)
                    return false;
            }
            try
            {
                output = std::stof(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool isIntParsable(const std::string str) // string to parse
    {
        bool negative;
        int secondTest;
        if (str.find_first_not_of("-0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            try
            {
                secondTest = std::stoi(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool isLongParsable(const std::string str) // string to parse
    {
        bool negative;
        long secondTest;
        if (str.find_first_not_of("-0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            try
            {
                secondTest = std::stol(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool isLongParsableU(const std::string str) // string to parse
    {
        unsigned long secondTest;
        if (str.find_first_not_of("0123456789") == std::string::npos)
        {
            try
            {
                secondTest = std::stoul(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool isLLongParsable(const std::string str) // string to parse
    {
        bool negative;
        long long secondTest;
        if (str.find_first_not_of("-0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            try
            {
                secondTest = std::stoll(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool isLLongParsableU(const std::string str) // string to parse
    {
        unsigned long long secondTest;
        if (str.find_first_not_of("0123456789") == std::string::npos)
        {
            try
            {
                secondTest = std::stoull(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    bool isDoubleParsable(const std::string str) // string to parse
    {
        int countPoint = 0;
        bool negative;
        double secondTest;
        if (str.find_first_not_of("-.0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            for (auto i: str) // Check for duplicate decimal points
            {
                if (i == '.')
                    countPoint++;
                if (countPoint > 1)
                    return false;
            }
            try
            {
                secondTest = std::stod(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }
    
    bool isFloatParsable(const std::string str) // string to parse
    {
        bool negative;
        int countPoint = 0;
        float secondTest;
        if (str.find_first_not_of("-.0123456789") == std::string::npos)
        {
            if (str[0] == '-') // Check if negative
                negative = true;
            else
                negative = false;
            if (negative) // Checks for extra negative signs
            {
                for (int i = 1; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            else
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (str[i] == '-')
                        return false;
                }
            }
            for (auto i: str) // Check for duplicate decimal points
            {
                if (i == '.')
                    countPoint++;
                if (countPoint > 1)
                    return false;
            }
            try
            {
                secondTest = std::stof(str);
                return true;
            }
            catch(const std::out_of_range& e)
            {
                return false;
            }
            catch(const std::invalid_argument& e)
            {
                return false;
            }
        }
        else
            return false;
    }

    // Below is a namespace for experimental functions. These may not work as intended.
    namespace ex
    { 
        // ! Below function converts string to unsigned long making this function prone to overflowing unsigned ints.
        bool tryIntParseU(const std::string str, unsigned int& output) // string to parse, output variable (unsigned int)
        {
            bool findNum = str.find_first_not_of("0123456789") == std::string::npos; // only allow these characters in the string to parse
            unsigned long testLong;
            if (findNum)
            {
                try
                {
                    testLong = std::stoul(str); // ! This converts the string to an unsigned long.
                }
                catch(const std::out_of_range& e)
                {
                    return false;
                }
                catch(const std::invalid_argument& e)
                {
                    return false;
                }
                if (testLong > 4294967295) // ? Maybe this will prevent the unsigned int variable from overflowing
                    return false;
                else
                {
                    output = testLong;
                    return true;
                }
            }
            else
                return false;
        }

        // ! Below are some functions that wrap around std::stoi. These functions are ment to only allow valid numbers to be converted.
        int parseInt(const std::string str) // string to parse
        {
            bool negative;
            int result;
            if (str.find_first_not_of("-0123456789") == std::string::npos)
            {
                if (str[0] == '-') // Check if negative
                    negative = true;
                else
                    negative = false;
                if (negative) // Checks for extra negative signs
                {
                    for (int i = 1; i < str.size(); i++)
                    {
                        if (str[i] == '-')
                            throw std::invalid_argument("\"-\" found in invalid spot");
                    }
                }
                else
                {
                    for (int i = 0; i < str.size(); i++)
                    {
                        if (str[i] == '-')
                            throw std::invalid_argument("\"-\" found in invalid spot");
                    }
                }
                try
                {
                    result = std::stoi(str);
                    return result;
                }
                catch(const std::out_of_range& e)
                {
                    throw std::out_of_range("String given is out of range of int");
                }
                catch(const std::invalid_argument& e)
                {
                    throw std::invalid_argument("String given is empty");
                }
            }
            else
                throw std::invalid_argument("String given cannot be converted to int");
        }

        double parseDouble(const std::string str) // string to parse
        {
            bool negative;
            int result;
            int countPoint = 0;
            if (str.find_first_not_of("-.0123456789") == std::string::npos)
            {
                if (str[0] == '-') // Check if negative
                    negative = true;
                else
                    negative = false;
                if (negative) // Checks for extra negative signs
                {
                    for (int i = 1; i < str.size(); i++)
                    {
                        if (str[i] == '-')
                            throw std::invalid_argument("\"-\" found in invalid spot in given string");
                    }
                }
                else
                {
                    for (int i = 0; i < str.size(); i++)
                    {
                        if (str[i] == '-')
                            throw std::invalid_argument("\"-\" found in invalid spot in given string");
                    }
                }
                for (auto i: str) // Check for duplicate decimal points
                {
                    if (i == '.')
                        countPoint++;
                    if (countPoint > 1)
                        throw std::invalid_argument("Multiple \".\" found in given string");
                }
                try // Actual conversion to double
                {
                    result = std::stod(str);
                    return result;
                }
                catch(const std::out_of_range& e)
                {
                    throw std::out_of_range("String creates number that is out of range of double");
                }
                catch(const std::invalid_argument& e)
                {
                    throw std::invalid_argument("Given string is empty");
                }
            }
            else
                throw std::invalid_argument("String given cannot be converted to double");
        }
    }
}
