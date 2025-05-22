#include "Moon.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace MoonUtils {
    bool compareStrings(const std::string& a, const std::string& b) {
        return a == b;
    }

    std::string convertDateFormat(const std::string& dd_mm_yyyy) {
        if (dd_mm_yyyy.length() != 10 || dd_mm_yyyy[2] != '.' || dd_mm_yyyy[5] != '.') {
            throw std::invalid_argument("Invalid date format. Use DD.MM.YYYY");
        }
        return dd_mm_yyyy.substr(6, 4) + dd_mm_yyyy.substr(3, 2) + dd_mm_yyyy.substr(0, 2);
    }

    double timeToDecimalHours(const std::string& hhmmss) {
        int hours = std::stoi(hhmmss.substr(0, 2));
        int minutes = std::stoi(hhmmss.substr(2, 2));
        int seconds = std::stoi(hhmmss.substr(4, 2));
        return hours + minutes / 60.0 + seconds / 3600.0;
    }

    std::string hoursToHMS(double decimal_hours) {
        int h = static_cast<int>(decimal_hours);
        double remainder = decimal_hours - h;
        double total_minutes = remainder * 60.0;
        int m = static_cast<int>(total_minutes);
        double remainder_seconds = total_minutes - m;
        int s = static_cast<int>(remainder_seconds * 60.0 + 0.5);

        if (s >= 60) { s -= 60; m++; }
        if (m >= 60) { m -= 60; h++; }

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << h
            << std::setw(2) << std::setfill('0') << m
            << std::setw(2) << std::setfill('0') << s;
        return oss.str();
    }

    bool invert3x3Matrix(const double matrix[3][3], double inverse[3][3]) {
        double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
            - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
            + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

        if (fabs(det) < 1e-9) return false;

        inverse[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) / det;
        inverse[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / det;
        inverse[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / det;

        inverse[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / det;
        inverse[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / det;
        inverse[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) / det;

        inverse[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) / det;
        inverse[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) / det;
        inverse[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) / det;

        return true;
    }

    void multiplyMatrixByVector(const double matrix[3][3], const double vector[3], double result[3]) {
        for (int i = 0; i < 3; i++) {
            result[i] = 0;
            for (int j = 0; j < 3; j++) {
                result[i] += matrix[i][j] * vector[j];
            }
        }
    }
}