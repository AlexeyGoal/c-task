#include <iostream>
#include "Currency.h"
int main()
{
    Purse myPurse;
    
    
    myPurse.add_currency(new Dollar(20));
    myPurse.add_currency(new Dollar(50));
    myPurse.add_currency(new Euro(30));
    myPurse.add_currency(new Pound(10));
    cout << "Wallet amount:";
    cout << myPurse.total_rubles()<<endl;
    cout << "\nWallet amount after exchange rate:";
    myPurse.new_course("Dollar", 120);
    cout << myPurse.total_rubles() << endl;
    cout << "\n";
    myPurse.print_history();

    return 0;

}


