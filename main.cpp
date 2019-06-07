#include "matrix.h"
#include <fstream>
#include <sstream>

int main() {
    std::ifstream infile("testcase_matrix.in");
    std::string count;
    getline(infile, count);
    std::stringstream stream(count);
    int countNumber;
    stream >> countNumber;
    std::map<std::string, matrix> map;
    for (int j = 0; j < countNumber; ++j) {
        std::string name;
        infile >> name;
        std::string read[9];
        for (auto &d:read) infile >> d;
        map[name] = matrix(read);
    }
    infile.close();

    std::vector<matrix> result;
    std::ifstream fin("testcase_expression.in");
    char line[1024];
    while (fin.getline(line, sizeof(line))) {
        std::cout << line << std::endl;
        result.push_back(eval(line, map));
    }
    fin.close();

    std::ofstream output("result.out");
    for (auto &matrix:result) output << matrix;
    output.close();
}
