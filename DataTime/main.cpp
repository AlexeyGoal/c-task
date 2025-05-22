#include "Header.h"


int main()
{
    setlocale(LC_ALL, "ru");
    DataTime data(1,1,2000);
    DataTime data2(2, 1, 2000);
    cout<<data.difference_days(data2);
    return 0;
}
