#pragma once
#ifndef HEADER_H
#define HEADER_H
#include<iostream>
#include<cmath>
using namespace std;
class DataTime {
public:
    DataTime(int day, int mounth, int year);
    bool correct_date(int day, int mounth, int year);
    void get_data();
    void cin_data();
    int to_julian();
    int difference_days(DataTime& other);
    DataTime julianTodate(int jd);
    DataTime addDays(int days);
    DataTime minusDays(int days);
    string WeekDay();




private:
    int day;
    int mounth;
    int year;
    bool rightData;
};

#endif