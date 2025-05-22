#ifndef CURRENCY_H
#define CURRENCY_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


class Currency {
protected:
	double current_course;
	double amount;
	string name_course;
public:
	Currency(double value);
	double to_rubles();
	virtual void print_amount() = 0;
	string get_name();
	void set_course(double new_course);
	double get_amount();
};

class Dollar : public Currency {
	
public:
	Dollar(double value);
	void print_amount() override;
	double to_cents();
	
};

class Euro : public  Currency {
	
public:
	Euro(double value);
	void print_amount() override;
	double to_cents();
	
};

class Pound : public Currency {
public:
	Pound(double value);
	void print_amount() override;
	double to_pence();
	
};


class Purse {
private:
	vector<Currency*> currencies;
	vector<string> history;
public:
	~Purse();
	void add_currency(Currency* currency);
	void add_random(int count);
	double total_rubles();
	void new_course(string name_course, double new_course);
	void print_history();
};



#endif