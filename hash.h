#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

      // the substring will be max 28 letters, 5 groups of 6
      unsigned long long w[5] = {0, 0, 0, 0, 0};
      int wIndex = 4;

      for(int i = k.length(); i > 0; i -= 6)
      {
        int startIdx = std::max(0, i - 6);
        int len = i - startIdx;
        unsigned long long power = 1;
        unsigned long long wVal = 0;
        
        std::string sstring = k.substr(startIdx, len);
        for(int i = sstring.length() - 1; i >= 0; i--)
        {
          wVal += letterDigitToNumber(sstring[i]) * power;
          power *= 36;
        }
        w[wIndex--] = wVal;
      }

      unsigned long long hash = 0;
      for(int i = 0; i < 5; i++)
      {
        hash += rValues[i] * w[i];
      }
      return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      
      // 0 - 9 --> 26 - 35
      if(isdigit(letter))
      {
        int integer = letter - '0';
        return 26 + integer;
      }

      // 'a - z' --> 0 - 25
      else
      {
        int lowercase = tolower(letter);
        return lowercase - 'a';
      }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
