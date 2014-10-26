#include "../include/calculator.hpp"

using namespace std;

namespace Prime {
    Calculator::Calculator(string filePath, string limit) {
        this->limit = strtoul(limit.c_str(), nullptr, 0);
        this->filePath = filePath;
        this->file.open(filePath);

        if(!this->file.is_open()) {
            this->createFile(filePath);
            this->file.open(filePath);

            if(!this->file.is_open()) {
                cout << "unable to create file " << filePath << endl;
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

    long unsigned int Calculator::getLastPrime() {
        return strtoul(this->getLastLine().c_str(), nullptr, 0);
    }

    string Calculator::getLastLine() {
        ifstream::pos_type position = this->file.tellg(), lastPosition;
        this->total = 0;

        while(this->file >> ws && this->ignoreLine(lastPosition)) {
            position = lastPosition;
            this->total++;
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

    void Calculator::rewindToLine(ifstream& f, unsigned long line) {
        f.clear();
        f.seekg(ios::beg);

        for(int i = 0; i < line - 1; i++) {
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void Calculator::getNextCandidate() {
        this->lastFoundPrime = this->getLastPrime();
        this->candidate = this->lastFoundPrime;
    }

    void Calculator::start() {
        this->multiThreads = (this->total >= THREADS);
        cout << this->total << " prime numbers saved" << endl;
        this->displayLargest();

        if(this->multiThreads) {
            cout << THREADS << " threads, limit is " << this->limit << endl;
        } else {
            cout << "1 thread, limit is " << THREADS << endl;
        }

        this->run();
        this->displayLargest();
    }

    void Calculator::displayLargest() {
        cout << "largest saved prime number is " << this->lastFoundPrime << endl;
    }

    void Calculator::run() {
        while(this->multiThreads && this->candidate <= this->limit || !this->multiThreads && this->total < THREADS) {
            if(this->multiThreads) {
                this->progression = this->candidate * 100 / this->limit;

                if(this->progression != this->lastDisplayedProgression) {
                    this->lastDisplayedProgression = this->progression;
                    cout << this->progression << "% (" << this->lastFoundPrime << "), " << this->range << " prime numbers per thread" << endl;
                }
            }

            this->candidate += 2;
            this->validCandidate = true;

            if(this->multiThreads) {
                this->threads();
            } else {
                this->process(0, 0, this->total);
            }

            if(this->validCandidate) {
                this->saveCandidate();
            }
        }

        if(!this->multiThreads && this->total == THREADS) {
            this->start();
        }
    }

    void Calculator::saveCandidate() {
        this->file.clear();
        this->file.seekp(0, ios::end);
        this->file << endl << this->candidate;
        this->lastFoundPrime = this->candidate;
        this->total++;
    }

    void Calculator::threads() {
        thread threads[THREADS];
        double from, to;
        this->range = ceil(this->total / THREADS);

        for(unsigned int i = 0; i < THREADS; i++) {
            from = i * this->range;
            to = from + this->range - 1;

            if(i == THREADS - 1 && to != this->total) {
                to = this->total;
            }

            threads[i] = thread(&Calculator::process, this, i, from, to);
        }

        for(int i = 0; i < THREADS; i++) {
            threads[i].join();
        }
    }

    void Calculator::process(unsigned int id, long unsigned int from, long unsigned int to) {
        long unsigned int prime, line = from + 1;
        ifstream in(this->filePath);
        this->rewindToLine(in, line);

        while(in >> prime) {
            if(!this->validCandidate) {
                break;
            }

            if(this->candidate % prime == 0) {
                this->validCandidate = false;
                break;
            }

            if(line - 1 == to) {
                break;
            }

            line++;
        }
    }

    void Calculator::log(string message) {
        this->mtx.lock();
        cout << message;
        this->mtx.unlock();
    }
}
