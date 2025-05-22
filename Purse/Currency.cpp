#include "Currency.h";

// Currency
Currency::Currency(double value) {
	amount = value;
	
}

double Currency::to_rubles() {
	return amount * current_course;
}

string Currency::get_name() {
    return name_course;
}

void Currency::set_course(double new_course) {
    current_course = new_course;
}

double Currency::get_amount() {
    return amount;
}

// Dollar

Dollar::Dollar(double value) : Currency(value) { 
    current_course = 81;
    name_course = "Dollar"; 
}
 
   

void Dollar::print_amount() {
	cout << amount << " Dollars";
}

double Dollar::to_cents() {
	return amount * 100;
}



// Euro 

Euro::Euro(double value) : Currency(value) { 
    current_course = 92; 
    name_course = "Euro";

}

void Euro::print_amount() {
	cout << amount << " Euro";
}

double Euro::to_cents() {
	return amount * 100;
}


// Pound 

Pound::Pound(double value) : Currency(value) {
    current_course = 108; 
    name_course = "Pound";
}

void Pound::print_amount() {
	cout << amount << " Pounds";
}

double Pound::to_pence() {
	return amount * 100;
}



// Purse 

void Purse::add_currency(Currency* currency) {
	currencies.push_back(currency);
    history.push_back("Added " + to_string(currency->get_amount()) + " " + currency->get_name());
}

Purse :: ~Purse() {
	for (Currency* currency : currencies) {
		delete currency;
	}
}

void Purse::add_random(int count) {
    srand(time(0));
    for (int i = 0; i < count; ++i) {
        int num = rand() % 3;
        double amount = (rand() % 1000) / 10.0 + 1;

        switch (num) {
            case 0:
                currencies.push_back(new Dollar(amount));
                break;
            case 1:
                currencies.push_back(new Euro(amount));
                break;
            case 2:
                currencies.push_back(new Pound(amount));
                break;
        }
    }
}

double Purse::total_rubles() {
    double sum = 0;
    for (Currency* currency : currencies) {
       sum += currency->to_rubles();
    }
    return sum;
}


void Purse::new_course(string currency_name, double new_rate) {
    for (auto& currency : currencies) {
        if (currency->get_name() == currency_name) {
            currency->set_course(new_rate);
        }
    }
    
}


void Purse::print_history() {
    cout << "History:" << endl;
    for (auto& elem : history) {
        std::cout << elem << endl;
    }
}

