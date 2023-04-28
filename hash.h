#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>


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

    unsigned long long w[5];
    std::vector<unsigned long long> vecInts;
    unsigned long long base; 
    base = (unsigned long long ) 36;

    std::string b = k;
    int place = 4;

    while(b.size() > 6){

        for(int i = 6; i >= 1; i--){
                char temp = b[b.size()-i];
               vecInts.push_back((unsigned long long) letterDigitToNumber(temp));
              }

                w[place] = (((((vecInts[0]*base) + vecInts[1])*base + vecInts[2])*base + vecInts[3])*base + vecInts[4])*base + vecInts[5];
                vecInts.clear();
                b = b.substr(0, b.size()-6);
                place--;
        }


        for(int i = 6; i > b.size(); i-- ){
            vecInts.push_back(0);
        }

        for(int i = 0; i < b.size(); i++){
            vecInts.push_back((unsigned long long) letterDigitToNumber(b[i]));
        }

    w[place] = (((((vecInts[0]*base) + vecInts[1])*base + vecInts[2])*base + vecInts[3])*base + vecInts[4])*base + vecInts[5];
        place--;

    for(int i  = place; i >= 0; i-- ){
        w[i] = (unsigned long long) 0;
    }


    return (rValues[0]*w[0] +rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4] );

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      for(char i = '0'; i <= '9'; i++){
        if(letter == i){
          return (int) letter - 22;
          break;
        }
      }
        if(letter < 91){
          return (int) (letter - 65);
        }
        else{
        return (int) (letter - 97);
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
