#include "Rational.h"
#include <cmath>

// Наибольший общий делитель
static int computeGCD(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Rational::simplify() {
    if (denominator == 0) {
        throw std::runtime_error("Zero denominator");
    }

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    int gcd = computeGCD(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

Rational::Rational() : numerator(0), denominator(1) {}
Rational::Rational(int num) : numerator(num), denominator(1) {}
Rational::Rational(int num, int den) : numerator(num), denominator(den) {
    simplify();
}

// Реализации операторов...
Rational& Rational::operator+=(const Rational& rhs) {
    numerator = numerator * rhs.denominator + denominator * rhs.numerator;
    denominator *= rhs.denominator;
    simplify();
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const {
    Rational result(*this);
    return result += rhs;
}

Rational Rational::operator-() const {
    return Rational(-numerator, denominator);
}

Rational& Rational::operator-=(const Rational& rhs) {
    return *this += (-rhs);
}

Rational Rational::operator-(const Rational& rhs) const {
    Rational result(*this);
    return result -= rhs;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    simplify();
    return *this;
}

Rational Rational::operator*(const Rational& rhs) const {
    Rational result(*this);
    return result *= rhs;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.numerator == 0) {
        throw std::runtime_error("Division by zero");
    }
    numerator *= rhs.denominator;
    denominator *= rhs.numerator;
    simplify();
    return *this;
}

Rational Rational::operator/(const Rational& rhs) const {
    Rational result(*this);
    return result /= rhs;
}

// Операторы сравнения
bool Rational::operator==(const Rational& rhs) const {
    return numerator == rhs.numerator && denominator == rhs.denominator;
}

bool Rational::operator!=(const Rational& rhs) const {
    return !(*this == rhs);
}

bool Rational::operator<(const Rational& rhs) const {
    return numerator * rhs.denominator < rhs.numerator * denominator;
}

bool Rational::operator<=(const Rational& rhs) const {
    return *this < rhs || *this == rhs;
}

bool Rational::operator>(const Rational& rhs) const {
    return rhs < *this;
}

bool Rational::operator>=(const Rational& rhs) const {
    return *this > rhs || *this == rhs;
}

// Операторы преобразования типов
Rational::operator int() const {
    return numerator / denominator;
}

Rational::operator double() const {
    return static_cast<double>(numerator) / denominator;
}

// Операторы ввода/вывода
std::istream& operator>>(std::istream& is, Rational& r) {
    int num, den = 1;
    char slash;

    is >> num;
    if (is.peek() == '/') {
        is >> slash >> den;
    }

    if (den == 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    r = Rational(num, den);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.numerator;
    if (r.denominator != 1) {
        os << '/' << r.denominator;
    }
    return os;
}

// Дружественные операторы для работы с целыми числами
Rational operator*(const Rational& r, int num) {
    return r * Rational(num);
}

Rational operator*(int num, const Rational& r) {
    return r * num;
}

Rational operator/(const Rational& r, int num) {
    return r / Rational(num);
}

Rational operator/(int num, const Rational& r) {
    return Rational(num) / r;
}

void inputNonZeroRational(Rational& coeff) {
    do {
        std::cout << "Enter coefficient (must be non-zero): ";
        std::cin >> coeff;
    } while (coeff == Rational(0));
}

void solveLinearEquation() {
    Rational a, b;
    std::cout << "Solving linear equation: a*x + b = 0\n";
    inputNonZeroRational(a);
    std::cout << "Enter coefficient b: ";
    std::cin >> b;

    Rational solution = -b / a;
    std::cout << "Solution: x = " << solution << "\n";
}

void solveQuadraticEquation() {
    Rational a, b, c;
    std::cout << "Solving quadratic equation: a*x^2 + b*x + c = 0\n";
    inputNonZeroRational(a);
    std::cout << "Enter coefficient b: ";
    std::cin >> b;
    std::cout << "Enter coefficient c: ";
    std::cin >> c;

    Rational discriminant = b * b - Rational(4) * a * c;
    double discrValue = static_cast<double>(discriminant);

    if (discrValue < 0) {
        std::cout << "No real roots\n";
    }
    else if (discrValue == 0) {
        Rational root = -b / (Rational(2) * a);
        std::cout << "Double root: x = " << root << "\n";
    }
    else {
        double sqrtDiscr = sqrt(discrValue);
        Rational root1 = (-b + Rational(sqrtDiscr)) / (Rational(2) * a);
        Rational root2 = (-b - Rational(sqrtDiscr)) / (Rational(2) * a);
        std::cout << "Two real roots:\n";
        std::cout << "x1 = " << root1 << "\n";
        std::cout << "x2 = " << root2 << "\n";
    }
}