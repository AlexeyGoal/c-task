#ifndef MOON_H
#define MOON_H

#include <cmath>
#include <string>

struct MoonObservation {
    std::string date;      // Формат "YYYYMMDD"
    std::string time;      // Формат "HHMMSS"
    double hours;         // Время в часах (десятичное)
    double elevation;     // Высота над горизонтом (градусы)
};

namespace MoonUtils {
    bool compareStrings(const std::string& a, const std::string& b);
    std::string convertDateFormat(const std::string& dd_mm_yyyy);
    double timeToDecimalHours(const std::string& hhmmss);
    std::string hoursToHMS(double decimal_hours);
    bool invert3x3Matrix(const double matrix[3][3], double inverse[3][3]);
    void multiplyMatrixByVector(const double matrix[3][3], const double vector[3], double result[3]);
}

#endif