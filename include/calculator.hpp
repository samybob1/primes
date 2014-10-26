#ifndef __FILE_H_
#define __FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cmath>
#include <thread>
#include <sstream>
#include <mutex>

#define THREADS 8

using namespace std;

namespace Prime {
    class Calculator {
    private:
        long unsigned int limit, candidate, lastFoundPrime, total;
        float progression, lastDisplayedProgression;
        bool validCandidate, multiThreads;
        string filePath;
        fstream file;
        double range;
        mutex mtx;

        void createFile(string fileName);
        void getNextCandidate();
        string getLastLine();
        istream& ignoreLine(ifstream::pos_type& position);
        long unsigned int getLastPrime();
        void run();
        void displayLargest();
        void saveCandidate();
        void threads();
        void process(unsigned int id, long unsigned int from, long unsigned int to);
        void rewindToLine(ifstream& f, unsigned long line);
        void log(string message);

    public:
        Calculator(string filePath, string limit);
        virtual ~Calculator();
        void start();
    };
}

#endif //__FILE_H_
