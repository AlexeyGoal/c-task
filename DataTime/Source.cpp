#include "Header.h"


DataTime::DataTime(int day = 1, int mounth = 1, int year = 2000) {
    if (correct_date(day, mounth, year)) {
        this->day = day;
        this->mounth = mounth;
        this->year = year;
        rightData = true;
    }
    else
        rightData = false;
}

void DataTime::get_data() {

    if (rightData) {
        cout << day << "." << mounth << "." << year;
        return;
    }

    cout << "Incorrect data";
}

void DataTime::cin_data() {
    char p1, p2;
    int ch_day, ch_mounth, ch_year;
    cout << "enter data(for example,1.2.2003):";
    cin >> ch_day >> p1 >> ch_mounth >> p2 >> ch_year;
    if (p1 == '.' && p2 == '.' && correct_date(ch_day, ch_mounth, ch_year)) {
        this->day = ch_day;
        this->mounth = ch_mounth;
        this->year = ch_year;
        cout << "date entered successfully" << endl;
    }
    else
        cout << "Incorrect date" << endl;
}

int DataTime::to_julian() {
    int a = (14 - mounth) / 12;
    int y = year + 4800 - a;
    int m = mounth + 12 * a - 3;
    return day + (153 * m + 2) / 5 + y * 365 + y / 4 - y / 100 + y / 400 - 32045;
}


DataTime DataTime::julianTodate(int jd) {
    int f = jd + 1401 + (((4 * jd + 274277) / 146097) * 3 / 4 - 38);
    int e = 4 * f + 3;
    int g = (e % 1461) / 4;
    int h = 5 * g + 2;
    int day = (h % 153) / 5 + 1;
    int mounth = (h / 153 + 2) % 12 + 1;
    int year = e / 1461 - 4716 + (14 - mounth) / 12;
    return DataTime(day, mounth, year);
}

DataTime DataTime::addDays(int days) {
    int jd = to_julian();
    jd += days;
    return julianTodate(jd);
}

DataTime DataTime::minusDays(int days) {
    int jd = to_julian();
    jd -= days;
    return julianTodate(jd);
}

string DataTime::WeekDay() {
    int jd = to_julian();
    int w_day = jd % 7;
    string week_days[7] = { "Mondey","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
    return week_days[w_day];
}

int DataTime::difference_days(DataTime& other) {

    return abs(this->to_julian() - other.to_julian());
}
bool DataTime::correct_date(int day, int mounth, int year) {
    if (year < 1 || day < 1 || (mounth < 1 || mounth > 12))
        return false;

    int days_mounth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((mounth == 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        days_mounth[1] = 29;

    if (day > days_mounth[mounth - 1])
        return false;

    return true;
}