//
// Created by zhang on 5/31/2019.
//

#include <cstring>
#include "matrix.h"
#include <algorithm>
#include <list>

matrix::matrix(std::string matrix[]) {
    for (int j = 0; j < 9; ++j)
        matrixContent[j / 3][j % 3] = big_integer(matrix[j]);
}

const matrix operator+(matrix &left, matrix &right) {
    matrix result;
    for (int i = 0; i < 9; ++i)
        result.matrixContent[i / 3][i % 3] =
                left.matrixContent[i / 3][i % 3] + right.matrixContent[i / 3][i % 3];
    return result;
}

const matrix operator-(const matrix &left, const matrix &right) {
    matrix result;
    for (int i = 0; i < 9; ++i)
        result.matrixContent[i / 3][i % 3] =
                left.matrixContent[i / 3][i % 3] - right.matrixContent[i / 3][i % 3];
    return result;
}

const matrix operator*(const matrix &left, const matrix &right) {
    matrix result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            big_integer element(0);
            for (int k = 0; k < 3; ++k) {
                element += left.matrixContent[i][k] * right.matrixContent[k][j];
            }
            result.matrixContent[i][j] = element;
        }
    }
    return result;
}

const matrix operator*(const big_integer &bigNum, const matrix &right) {
    matrix result;
    for (int i = 0; i < 9; ++i)
        result.matrixContent[i / 3][i % 3] = bigNum * right.matrixContent[i / 3][i % 3];
    return result;
}

const matrix operator~(const matrix &right) {
    matrix result;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            result.matrixContent[i][j] = right.matrixContent[j][i];
    return result;
}

matrix &operator+=(matrix &left, const matrix &right) {
    matrix result;
    for (int i = 0; i < 9; ++i)
        result.matrixContent[i / 3][i % 3] =
                left.matrixContent[i / 3][i % 3] + right.matrixContent[i / 3][i % 3];
    left = result;
    return left;
}

matrix &operator-=(matrix &left, const matrix &right) {
    matrix result;
    for (int i = 0; i < 9; ++i)
        result.matrixContent[i / 3][i % 3] =
                left.matrixContent[i / 3][i % 3] - right.matrixContent[i / 3][i % 3];
    left = result;
    return left;
}

std::ostream &operator<<(std::ostream &stream, const matrix &matrix1) {
    for (auto &line:matrix1.matrixContent)
        stream << line[0] << " " << line[1] << " " << line[2] << "\n";
    return stream;
}

matrix computeExpression(const std::map<std::string, matrix> &map, const std::string &expression) {
    std::string localExpression = expression;
    std::list<std::string> subExpressions; //strings that are split by += and -=
    std::list<std::string> operators;
    while (expression.find("+=") != std::string::npos || expression.find("-=") != std::string::npos) {
        int index1 = expression.find("+="), index2 = expression.find("-=");
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
//    todo: To be changed in the future
    subExpressions.push_back(localExpression);
    std::list<matrix> matrixes;
    for (auto &subExpression:subExpressions)
        matrixes.push_back(computeExpression1(subExpression, map));
    return matrixes.back();
}

matrix computeExpression1(std::string expression, const std::map<std::string, matrix> &map) {
    std::vector<std::string> elements;
    int previousPosition = 0;
    std::map<std::string, matrix> customMap(map);
    for (int i = 0; i < expression.size(); ++i) {
        char character = expression[i];
        if (character == '~' || character == '*' || character == '+' || character == '-') {
            if (i == 0) {
                elements.push_back(expression.substr(previousPosition, 1));
                previousPosition++;
            } else {
                if (character == '~') elements.push_back("~");
                else {
                    elements.push_back(expression.substr(previousPosition, i - previousPosition));
                    elements.push_back(expression.substr(i, 1));
                }
                previousPosition = i + 1;
            }
        }
    }
    elements.push_back(expression.substr(previousPosition));
//    Process negative numbers
    int k = 0;
    if (elements[k] == "-" && (elements[k + 1][0] >= 48 && elements[k + 1][0] <= 57)) {
        auto iterator = elements.begin() + k;
        elements.erase(iterator);
        elements[k] = "-" + elements[k];
    }

//    Process ~ symbol
    std::vector<std::string> elements1;
    for (int j = 0; j < elements.size(); ++j) {
        std::string element = elements[j];
        if (element == "~") {
            matrix a = ~customMap.at(elements[++j]);
            customMap["~" + elements[j]] = a;
            elements1.push_back("~" + elements[j]);
        } else
            elements1.push_back(elements[j]);
    }

//    Process * symbol
    std::vector<std::string> elements2;
    for (int j = 0; j < elements1.size(); ++j) {
        std::string element = elements1[j];
        if (element == "*") {
            matrix a;
            if ((elements1[j - 1][0] >= 48 && elements1[j - 1][0] <= 57) ||
                (elements1[j - 1][0] == '-' && elements1[j - 1][1] >= 48 &&
                 elements1[j - 1][1] <= 57))
                a = big_integer(elements1[j - 1]) * customMap.at(elements1[j + 1]);
            else
                a = customMap.at(elements1[j - 1]) * customMap.at(elements1[j + 1]);
            elements2.pop_back();
            j++;
            elements1[j] = "*" + j + elements1[j];
            customMap[elements1[j]] = a;
            elements2.push_back(elements1[j]);
        } else elements2.push_back(elements1[j]);
    }

    //    Process +/- symbol
    std::vector<std::string> elements3;
    for (int j = 0; j < elements2.size(); ++j) {
        std::string element = elements2[j];
        if (element == "+") {
            matrix a = customMap.at(elements2[j - 1]) + customMap.at(elements2[j + 1]);
            elements3.pop_back();
            customMap["+" + elements2[++j]] = a;
            elements3.push_back("+" + elements2[j]);
            elements2[j] = "+" + elements2[j];
        } else if (element == "-") {
            matrix a = customMap.at(elements2[j - 1]) - customMap.at(elements2[j + 1]);
            elements3.pop_back();
            customMap["-" + elements2[++j]] = a;
            elements3.push_back("-" + elements2[j]);
            elements2[j] = "-" + elements2[j];
        } else elements3.push_back(elements2[j]);
    }
    return customMap.at(elements3.back());
}
