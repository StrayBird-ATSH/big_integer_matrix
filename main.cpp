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
#include <algorithm>
#include <map>
#include <list>

matrix compute_expression(const std::map<std::string, matrix> &map, const std::string &expression) {
    std::string localExpression = expression;
    std::list<std::string> subExpressions; //strings that are split by += and -=
    std::list<std::string> operators;
    while (expression.find_first_of("+=") != std::string::npos || expression.find_first_of("-=") != std::string::npos) {
        int index1 = expression.find_first_of("+="), index2 = expression.find_first_of("-=");
        if (((index1 != -1 && index2 != -1) && (index1 < index2)) || index2 == -1) {
            subExpressions.push_back(localExpression.substr(0, index1));
            operators.emplace_back("+=");
            localExpression = localExpression.substr(index1 + 2);
        } else {
            subExpressions.push_back(localExpression.substr(0, index2));
            operators.emplace_back("-=");
            localExpression = localExpression.substr(index2 + 2);
        }
    }


    return
            matrix();
}

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

    std::vector<matrix> result;

    std::ifstream fin("expression.in", std::ios::in);
    char line[1024];
    while (fin.getline(line, sizeof(line))) {
        std::cout << line << std::endl;
        result.push_back(compute_expression(map, line));
    }
    fin.clear();
    fin.close();


    std::cout << "BigNumber ran successfully." << std::endl;
}
