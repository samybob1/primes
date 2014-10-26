#ifndef __FILE_H_
#define __FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

namespace Prime {
    class Calculator {
    private:
        fstream file;
        unsigned long limit, candidate, lastFoundPrime;
        unsigned int progression, lastDisplayedProgression;

        void createFile(string fileName);
        void getNextCandidate();
        string getLastLine();
        istream& ignoreLine(ifstream::pos_type& position);
        unsigned long getLastPrime();
        void rewind();
        void saveCandidate();
        void displayLastPrime();

    public:
        Calculator(string fileName, string limit);
        virtual ~Calculator();
        void start();
    };
}

#endif //__FILE_H_
