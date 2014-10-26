#include "../include/calculator.hpp"

using namespace std;
using namespace Prime;

int main(int argc, char** argv) {
    if(argc != 3) {
        cout << "usage : ./primes [PATH] [LIMIT]" << endl;
        cout << "example : ./primes ~/primes.txt 1000" << endl;
        return 1;
    }

    Calculator calculator(argv[1], argv[2]);
    calculator.start();

    return 0;
}
