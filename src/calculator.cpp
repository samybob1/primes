#include "../include/calculator.hpp"

using namespace std;

namespace Prime {
    Calculator::Calculator(string fileName, string limit) {
        this->limit = strtoul(limit.c_str(), nullptr, 0);
        this->file.open(fileName);

        if(!this->file.is_open()) {
            this->createFile(fileName);
            this->file.open(fileName);

            if(!this->file.is_open()) {
                cout << "unable to create file " << fileName << endl;
                exit(1);
            }
        }

        this->getNextCandidate();
        this->lastDisplayedProgression = 0;
    }

    Calculator::~Calculator() {
        this->file.close();
    }

    void Calculator::createFile(string fileName) {
        ofstream out(fileName);
        out << 2 << endl << 3;
        out.close();
    }

    unsigned long Calculator::getLastPrime() {
        return strtoul(this->getLastLine().c_str(), nullptr, 0);
    }

    string Calculator::getLastLine() {
        ifstream::pos_type position = this->file.tellg(), lastPosition;

        while(file >> ws && this->ignoreLine(lastPosition)) {
            position = lastPosition;
        }

        this->file.clear();
        this->file.seekg(position);

        string line;
        getline(this->file, line);
        return line;
    }

    istream& Calculator::ignoreLine(ifstream::pos_type &position) {
        position = this->file.tellg();
        return this->file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void Calculator::rewind() {
        this->file.clear();
        this->file.seekg(0, ios::beg);
    }

    void Calculator::getNextCandidate() {
        this->lastFoundPrime = this->getLastPrime();
        this->candidate = this->lastFoundPrime;
    }

    void Calculator::start() {
        this->displayLastPrime();
        cout << "limit is " << this->limit << endl;

        unsigned long prime;
        bool validCandidate;

        while(this->candidate <= this->limit) {
            this->progression = (unsigned int) (this->candidate * 100 / this->limit);

            if(this->progression != this->lastDisplayedProgression) {
                this->lastDisplayedProgression = this->progression;
                cout << this->progression << "% (" << this->lastFoundPrime << ")" << endl;
            }

            this->candidate += 2;
            validCandidate = true;
            this->rewind();

            while(this->file >> prime) {
                if(this->candidate % prime == 0) {
                    validCandidate = false;
                    break;
                }
            }

            if(validCandidate) {
                this->saveCandidate();
            }
        }

        this->displayLastPrime();
    }

    void Calculator::saveCandidate() {
        this->file.clear();
        this->file.seekp(0, ios::end);
        this->file << endl << this->candidate;
        this->lastFoundPrime = this->candidate;
    }

    void Calculator::displayLastPrime() {
        cout << "largest saved prime number is " << this->lastFoundPrime << endl;
    }
}
