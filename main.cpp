////////////////////////////
//To make sure assert works:
#ifdef NDEBUG
#undef NDEBUG
#endif
////////////////////////////

#include "big_integer.h"
#include "matrix.h"
#include <assert.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

int main() {
    std::string file = "matrix.in";
    std::ifstream infile;
    infile.open(file.data());
    assert(infile.is_open());
    std::string count;
    getline(infile, count);
    std::stringstream stream(count);
    int countNumber;
    stream >> countNumber;
    std::map<std::string, matrix> map;
    for (int j = 0; j < countNumber; ++j) {
        std::string name;
        getline(infile, name);
        std::string read[3];
        for (auto &d:read) {
            std::string line;
            getline(infile, line);
            d = line;
        }
        matrix matrix1(read);
        map.insert(std::pair<std::string, matrix>(name, matrix1));
    }
    infile.close();


    std::ifstream fin("expression.in", std::ios::in);
    char line[1024];
    while (fin.getline(line, sizeof(line))) {

        std::cout << line << std::endl;

    }
    fin.clear();
    fin.close();


    std::cout << "BigNumber ran successfully." << std::endl;
}
