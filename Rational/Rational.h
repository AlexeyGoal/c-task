#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <stdexcept>

class Rational {
private:
    int numerator;
    int denominator;
    void simplify();

public:
    Rational();
    Rational(int num);
    Rational(int num, int den);

    // �������������� ��������
    Rational& operator+=(const Rational& rhs);
    Rational operator+(const Rational& rhs) const;
    Rational operator-() const;
    Rational& operator-=(const Rational& rhs);
    Rational operator-(const Rational& rhs) const;
    Rational& operator*=(const Rational& rhs);
    Rational operator*(const Rational& rhs) const;
    Rational& operator/=(const Rational& rhs);
    Rational operator/(const Rational& rhs) const;

    // �������� ���������
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;

    // �������������� �����
    explicit operator int() const;
    explicit operator double() const;

    // ����/�����
    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
};

// ��������������� ������� ��� ������ � �����������
void inputNonZeroRational(Rational& coeff);
void solveLinearEquation();
void solveQuadraticEquation();

#endif