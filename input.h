#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
//апролдж
using namespace std;

#ifndef INPUT_H
#define INPUT_H
int readNumber();
double readDouble();
string Vvod_z_klavy();
void Tolower(string &text);
//перерахування і структури до курсової

enum Type_currency { UAH, USD, EUR };
struct Currency {
  Type_currency currency;
  float kurs;
};
enum Type_account { Cash, Bank_acc, Priv_loan };
struct Account {
  Type_account type;
  Type_currency currency;
  string name;
  double balance_start = 0.00;
  double balance = 0.00;
};
enum Income_type { salary, interest, gift, other_inc };
struct Income {
  Income_type type;
  double amount;
  Type_currency currency;
  string acc_name;
};
enum Expenses_type {
  meal,
  household,
  clothing_and_shoes,
  capital_expenses,
  communal_payments,
  other_exp
};
struct Expenses {
  Expenses_type type;
  double amount;
  Type_currency currency;
  string acc_name;
};
struct Transfer {
  string name1;
  double amount1;
  Type_currency currency1;
  string name2;
  double amount2;
  Type_currency currency2;
};

//глобальні вектори з базами даних
vector<Currency> currency_all;
vector<Account> accounts_all;
vector<Income> income_all;
vector<Expenses> expenses_all;
vector<Transfer> transfers_all;

//запис у файл курсів.....................................................
void Curr_to_file() {
  ofstream out_cur("TXT/currency.txt");
  if (out_cur.is_open()) {
    // записываем все объекты в файл
    for (const Currency &cur : currency_all) {
      out_cur << cur.currency << "\t" << cur.kurs << std::endl;
    }
  }
  out_cur.close();
}
//читання з файла курсів.....................................................
void Curr_from_file() {
  ifstream in_cur("TXT/currency.txt");
  if (in_cur.is_open()) {
    currency_all.clear();
    int currency;
    float kurs;
    Currency cur;
    while (in_cur >> currency >> kurs) {
      cur.currency = (Type_currency)currency;
      cur.kurs = kurs;
      currency_all.push_back(cur);
    }
  }
  in_cur.close();
}
//запис у файл рахунків......................................................
void Acc_to_file() {
  ofstream out("TXT/accounts.txt");
  if (out.is_open()) {

    vector<Account> accounts_all1 = accounts_all;
    string x = " ", y = "*";
    size_t pos;
    for (int i = 0; i < accounts_all1.size(); i++) {
      while ((pos = accounts_all1[i].name.find(x)) != std::string::npos) {
        accounts_all1[i].name.replace(pos, 1, y);
      }
    }
    // записываем все объекты  в файл
    for (const Account &acc : accounts_all1) {
      out << acc.balance << "\t" << acc.balance_start << "\t" << acc.currency
          << "\t" << acc.name << "\t" << acc.type << std::endl;
    }
  }
  out.close();
}
//читання з файла рахунків...................................................
void Acc_from_file() {

  vector<Account> accounts_all1;
  ifstream in("TXT/accounts.txt");
  if (in.is_open()) {
    accounts_all.clear();
    double balance;
    double balance_start;
    int currency;
    string name;
    int type;

    Account akk;

    while (in >> balance >> balance_start >> currency >> name >> type) {
      akk.balance = balance;
      akk.balance_start = balance_start;
      akk.currency = (Type_currency)currency;
      akk.name = name;
      akk.type = (Type_account)type;
      accounts_all1.push_back(akk);
    }
  }
  in.close();
  string x = "*", y = " ";
  size_t pos;
  for (int i = 0; i < accounts_all1.size(); i++) {
    while ((pos = accounts_all1[i].name.find(x)) != std::string::npos) {
      accounts_all1[i].name.replace(pos, 1, y);
    }
  }
  accounts_all = accounts_all1;
}
//запис у файл доходів......................................................
void Inc_to_file() {

  vector<Income> income_all1 = income_all;
  string x = " ", y = "*";
  size_t pos;
  for (int i = 0; i < income_all1.size(); i++) {
    while ((pos = income_all1[i].acc_name.find(x)) != std::string::npos) {
      income_all1[i].acc_name.replace(pos, 1, y);
    }
  }
  ofstream out("TXT/incomes.txt");
  if (out.is_open()) {
    // записываем все объекты  в файл
    for (const Income &inc : income_all1) {
      out << inc.acc_name << "\t" << inc.amount << "\t" << inc.currency << "\t"
          << inc.type << std::endl;
    }
  }
  out.close();
}
//читання з файла доходів...................................................
void Inc_from_file() {
  vector<Income> income_all1;
  ifstream in("TXT/incomes.txt");
  if (in.is_open()) {
    income_all.clear();
    int type; //
    double amount;
    int currency; //
    string acc_name;

    Income ink;

    while (in >> acc_name >> amount >> currency >> type) {
      ink.acc_name = acc_name;
      ink.amount = amount;
      ink.currency = (Type_currency)currency;
      ink.type = (Income_type)type;
      income_all1.push_back(ink);
    }
  }
  in.close();
  string x = "*", y = " ";
  size_t pos;
  for (int i = 0; i < income_all1.size(); i++) {
    while ((pos = income_all1[i].acc_name.find(x)) != std::string::npos) {
      income_all1[i].acc_name.replace(pos, 1, y);
    }
  }
  income_all = income_all1;
}
//запис у файл витрат......................................................
void Exp_to_file() {
  vector<Expenses> expenses_all1 = expenses_all;
  string x = " ", y = "*";
  size_t pos;
  for (int i = 0; i < expenses_all1.size(); i++) {
    while ((pos = expenses_all1[i].acc_name.find(x)) != std::string::npos) {
      expenses_all1[i].acc_name.replace(pos, 1, y);
    }
  }
  ofstream out("TXT/expenses.txt");
  if (out.is_open()) {
    // записываем все объекты  в файл
    for (const Expenses &exp : expenses_all1) {
      out << exp.acc_name << "\t" << exp.amount << "\t" << exp.currency << "\t"
          << exp.type << std::endl;
    }
  }
  out.close();
}
//читання з файла витрат...................................................
void Exp_from_file() {
  vector<Expenses> expenses_all1;

  ifstream in("TXT/expenses.txt");
  if (in.is_open()) {
    expenses_all.clear();
    int type; //
    double amount;
    int currency; //
    string acc_name;

    Expenses exp;

    while (in >> acc_name >> amount >> currency >> type) {
      exp.acc_name = acc_name;
      exp.amount = amount;
      exp.currency = (Type_currency)currency;
      exp.type = (Expenses_type)type;
      expenses_all1.push_back(exp);
    }
  }
  in.close();
  string x = "*", y = " ";
  size_t pos;
  for (int i = 0; i < expenses_all1.size(); i++) {
    while ((pos = expenses_all1[i].acc_name.find(x)) != std::string::npos) {
      expenses_all1[i].acc_name.replace(pos, 1, y);
    }
  }
  expenses_all = expenses_all1;
}
//запис у файл переказів......................................................
void Transf_to_file() {
  vector<Transfer> transfers_all1 = transfers_all;
  string x = " ", y = "*";
  size_t pos;
  for (int i = 0; i < transfers_all1.size(); i++) {
    while ((pos = transfers_all1[i].name1.find(x)) != std::string::npos) {
      transfers_all1[i].name1.replace(pos, 1, y);
    }
    while ((pos = transfers_all1[i].name2.find(x)) != std::string::npos) {
      transfers_all1[i].name2.replace(pos, 1, y);
    }
  }

  ofstream out("TXT/transfers.txt");
  if (out.is_open()) {
    // записываем все объекты  в файл
    for (const Transfer &trans : transfers_all1) {
      out << trans.amount1 << "\t" << trans.amount2 << "\t" << trans.currency1
          << "\t" << trans.currency2 << "\t" << trans.name1 << "\t"
          << trans.name2 << std::endl;
    }
  }
  out.close();
}
//читання з файла переказів...................................................
void Transf_from_file() {
  vector<Transfer> transfers_all1;

  ifstream in("TXT/transfers.txt");
  if (in.is_open()) {
    transfers_all.clear();

    double amount1;
    double amount2;
    int currency1; // Type_currency
    int currency2; // Type_currency
    string name1;
    string name2;

    Transfer tr;

    while (in >> amount1 >> amount2 >> currency1 >> currency2 >> name1 >>
           name2) {
      tr.amount1 = amount1;
      tr.amount2 = amount2;
      tr.currency1 = (Type_currency)currency1;
      tr.currency2 = (Type_currency)currency2;
      tr.name1 = name1;
      tr.name2 = name2;
      transfers_all1.push_back(tr);
    }
  }
  in.close();
  string x = "*", y = " ";
  size_t pos;
  for (int i = 0; i < transfers_all1.size(); i++) {
    while ((pos = transfers_all1[i].name1.find(x)) != std::string::npos) {
      transfers_all1[i].name1.replace(pos, 1, y);
    }
    while ((pos = transfers_all1[i].name2.find(x)) != std::string::npos) {
      transfers_all1[i].name2.replace(pos, 1, y);
    }
  }
  transfers_all = transfers_all1;
}

//заповнення вектора валют
void Filling_vect_curr() {
  currency_all.clear();
  Currency cur = {Type_currency::UAH, 1.0};
  currency_all.push_back(cur);
  cur = {Type_currency::USD, 38.0};
  currency_all.push_back(cur);
  cur = {Type_currency::EUR, 43.0};
  currency_all.push_back(cur);
}
//друк валют
void Print_vect_curr() {
  cout << "\n";
  cout << " \x1b[46m\x1b[30m.                             RATES                "
          "                \x1b[37m\x1b[40m.\n";
  cout << "                        \x1b[36mShow exchange rates\x1b[37m\n";

  string cur_name[] = {"UAH", "USD", "EUR"};
  cout << " Currency\tRate\n";
  cout << " ______________________\n";
  for (int i = 0; i < currency_all.size(); i++) {
    cout << " " << cur_name[i] << "\t\t" << currency_all[i].kurs;
    cout << endl;
  }
  cout << " ______________________\n";
  cout << " Press any digit ";
  int charik;
  charik=readNumber();
}
//зміна курсу - КОРИСТУВАЧ!!!!!!!!!!!!!!!!!!!!!!!!
void Change_vect_curr() {
  cout << "\n";
    cout << " \x1b[46m\x1b[30m                              RATES                                \x1b[37m\x1b[40m \n";
    cout << "                        \x1b[36mEdit exchange rates\x1b[37m\n";

    string cur_name[] = { "usd","eur", };
    cout << "\n\x1b[32mEnter the name of the currency to edit (USD, EUR): \x1b[37m\n";
    string line;
    
    int ind = -1;
    while (ind == -1)
    {
        line = Vvod_z_klavy();
        Tolower(line);
        for (int i = 0; i < 2; i++)
        {
            if (cur_name[i] == line) {
                ind = i+1;
                break;
            }
        }
        if (ind == -1)
        {
            if (line == "UAH") {
                cout << "\x1b[31mThe UAH to UAH exchange rate does not change and is always 1\n(quit - press 0,continue - press any digit):\x1b[37m";
                int quit = readNumber();
                if (quit == 0)return;
                cout << "\n\x1b[32mTry again: \x1b[37m";

            }
            else {
                cout << "\x1b[31mNo such currency\n(quit - press 0,continue - press any digit): \x1b[37m";
                int quit = readNumber();
                if (quit == 0)return;
                cout << "\n\x1b[32mTry again: \x1b[37m";
            }
        }
        
    }
    cout << "\n\x1b[32mEnter the new value of the exchange rate: \x1b[37m";
    currency_all[ind].kurs = readDouble();
    while (currency_all[ind].kurs <= 0)
    {
        cout << "\n\x1b[31mThe exchange rate is a positive number\n(quit - press 0,continue - press any digit):\x1b[37m";
        int quit = readNumber();
        if (quit == 0)return;
        cout << "\n\x1b[32mTry again: \x1b[37m";
        currency_all[ind].kurs = readDouble();
    }
    cout << "Press any digit ";
    int charik;
    charik = readNumber();
}

//заповнення вектора автоматичними рахунками
void Filling_accounts() {
  accounts_all.clear();
  Account acc = {Cash, UAH, "My purse"};
  accounts_all.push_back(acc);
  acc = {Cash, USD, "For a rainy day", 100.0, 100.0};
  accounts_all.push_back(acc);
  acc = {Bank_acc, UAH, "Credit card", -100.0, -100.0};
  accounts_all.push_back(acc);
  acc = {Bank_acc, UAH, "Salary card"};
  accounts_all.push_back(acc);
}

//введення нового рахунку вручну - КОРИСТУВАЧ!!!!!!!!!!!!!!!!!!!!!!!!
void Filling_acc_manual() {
   cout << "\n";
    cout << " \x1b[46m\x1b[30m                            ACCOUNTS                               \x1b[37m\x1b[40m \n";
    cout << "                           \x1b[36mNew account\x1b[37m\n";
    
    Account acc1;
    cout << "\x1b[32mEnter the account type\n(Cash - 0,Bank_acc - 1,Priv_loan - 2): \x1b[37m" << endl;
    int type_int = -1;
    while (type_int < 0 || type_int>2) {
        type_int = readNumber();
        if (type_int < 0 || type_int>2) {
            cout << "\x1b[31mQuit - press 0,continue - press any digit:\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\x1b[32mEnter the account type\n(Cash - 0,Bank_acc - 1,Priv_loan - 2): \x1b[37m" << endl;
        }
    }
    Type_account type = (Type_account)type_int;
    cout << endl << "\x1b[32mEnter the account currency\n(UAH-0,USD-1,EUR-2): \x1b[37m";
    int type_curr = -1;
    while (type_curr < 0 || type_curr>2) {
        type_curr = readNumber();
        if (type_curr < 0 || type_curr>2) {
            cout << "\x1b[31mThis type does not exist\n(quit - press 0,continue - press any digit:\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << endl << "\x1b[32mEnter the account currency\n(UAH-0,USD-1,EUR-2): \x1b[37m";
        }

    }
    Type_currency currency = (Type_currency)type_curr;

    cout << endl << "\x1b[32mEnter the name of the account\n(letters, numbers and spaces up to 15 characters): \x1b[37m";
    int perev = -1;
    int perev1 = -1;
    string name;
    string tymchas;
    string name_tymch;
    while (perev == -1|| perev1 == -1)
    {
        name = Vvod_z_klavy();
        name_tymch = name;
        Tolower(name_tymch);
        perev = 0;
        perev1 = 0;
        for (int i = 0; i < accounts_all.size(); i++)
        {
            tymchas = accounts_all[i].name;
            Tolower(tymchas);
            if (name_tymch == tymchas)
            {
                perev = -1;
                break;
            }
        }
        if (perev == -1) {
            cout << "\x1b[31mThis name already exists\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";
        }
        if (name.find("*") != string::npos) {
            perev1 = -1;
            cout << "\x1b[31mNo **** please!!!!!\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";
        }
    }
    

    cout << endl << "\x1b[32mEnter the start balance: \x1b[37m";
    int perev_plus = 1;
    double balance_start;
    while (perev_plus) {
        balance_start = readDouble();
        perev_plus = 0;
        if ((balance_start < 0) && (type == Cash)) {
            perev_plus = 1;
            cout << "\x1b[31mCash cannot have a negative balance\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";
        }
    }
    

    acc1.type = type;
    acc1.name = name;
    acc1.currency = currency;
    acc1.balance_start = balance_start;
    acc1.balance = balance_start;
    accounts_all.push_back(acc1);
    cout << "Press any digit ";
    int charik;
    charik = readNumber();
}
//редагування рахунків - КОРИСТУВАЧ!!!!!!!!!!!!!!!!!!!!!!!!
void Change_account() {
  cout << "\n";
    cout << " \x1b[46m\x1b[30m                            ACCOUNTS                               \x1b[37m\x1b[40m \n";
    cout << "                           \x1b[36mEdit account\x1b[37m\n";
    
    
    cout << "\n\x1b[32mWhich account do you want to edit? Enter its name:\x1b[37m\n";

    int perev = 1;
    int iter = -1;
    string name_tymch;
    string tymchas;
    while (perev)
    {
        string name = Vvod_z_klavy();
        name_tymch = name;
        Tolower(name_tymch);
        for (int i = 0; i < accounts_all.size(); i++)
        {
            tymchas = accounts_all[i].name;
            Tolower(tymchas);
            if (name_tymch == tymchas)
            {
                iter = i;
                perev = 0;
                break;
            }
        }
        if (perev) {
            cout << "\x1b[31mNo such account\n(quit - press 0,continue - press any digit)\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";

        }
    }//знайде існуючий рахунок і перевірка буде 0
    for (int i = 0; i < income_all.size(); i++) {
        if (income_all[i].acc_name == accounts_all[iter].name) {
            perev = 1;
            break;
        }
    }
    if(perev!=1)for (int i = 0; i < expenses_all.size(); i++) {
        if (expenses_all[i].acc_name == accounts_all[iter].name) {
            perev = 1;
            break;
        }
    }
    if (perev != 1)for (int i = 0; i < transfers_all.size(); i++) {
        if (transfers_all[i].name1 == accounts_all[iter].name || transfers_all[i].name2 == accounts_all[iter].name) {
            perev = 1;
            break;
        }
    }
    if (perev)  {
        cout << "\x1b[31mIt is not possible to change the account on \nwhich there are saved transactions!\n\x1b[37m";
        cout << "Press any digit ";
        char charik;
        cin >> charik;
        return;
    }

    cout << "\x1b[32mDo you want to change the account type?\n(1 - YES, other digit - NO)\x1b[37m" << endl; //зміна типу рахунку
    int change = readNumber();
    if (change == 1)
    {
        int type_int = -1;
        while (type_int < 0 || type_int>2)
        {
            cout << "\x1b[32mEnter the account type\n(Cash - 0,Bank_acc - 1,Priv_loan - 2): \x1b[37m" << endl;
            type_int = readNumber();
            if (type_int < 0 || type_int>2) {
                cout << "\x1b[31mThis type does not exist\n(quit - press 0,continue - press any digit):\n\x1b[37m";
                int quit = readNumber();
                if (quit == 0)return;
                cout << "\n\x1b[32mTry again: \x1b[37m";
            }
            
        }
        accounts_all[iter].type = (Type_account)type_int;
    }
    cout << "\x1b[32mDo you want to change the account currency?\n(1 - YES, other digit - NO)\x1b[37m" << endl;//зміна валюти
    change = readNumber();
    if (change == 1)
    {
        cout << endl << "\x1b[32mEnter the account currency\n(UAH-0,USD-1,EUR-2): \x1b[37m";
        int type_curr=-1;
        while (type_curr < 0 || type_curr>2) {
            type_curr = readNumber();
            if (type_curr < 0 || type_curr>2) {
                cout << "\x1b[31mThis currency does not exist\n(quit - press 0,continue - press any digit):\n\x1b[37m";
                int quit = readNumber();
                if (quit == 0)return;
                cout << "\n\x1b[32mTry again: \x1b[37m";
            }
        }
            
        accounts_all[iter].currency = (Type_currency)type_curr;
    }
    cout << "\x1b[32mDo you want to change the account name?\n(1 - YES, other digit - NO)\x1b[37m" << endl;//зміна назви
    change = readNumber();
    if (change == 1)
    {
        
        int perev = -1;
        
        string name;
        string name_tymch;
        string tymchas;
        
        while (perev == -1)
        {
            cout << endl << "\x1b[32mEnter the name of the account\n(letters, numbers and spaces up to 20 characters): \x1b[37m";
            name = Vvod_z_klavy();
            name_tymch = name;
            Tolower(name_tymch);
            perev = 0;
            for (int i = 0; i < accounts_all.size(); i++)
            {
                tymchas = accounts_all[i].name;
                Tolower(tymchas);
                if (name_tymch == tymchas)
                {
                    perev = -1;
                    break;
                }
            }
            if (perev == -1) {
                cout << "\x1b[31mThis name already exists\n(quit - press 0,continue - press any digit):\n\x1b[37m";
                int quit = readNumber();
                if (quit == 0)return;
                cout << "\n\x1b[32mTry again: \x1b[37m";

            }
            if (name.find("*") != string::npos) {
                perev = -1;
                cout << "\x1b[31mNo **** please!!!!!\n(quit - press 0,continue - press any digit):\n\x1b[37m";
                int quit = readNumber();
                if (quit == 0)return;
                cout << "\n\x1b[32mTry again: \x1b[37m";

            }
        }
        accounts_all[iter].name = name;
    }
    cout << "\x1b[32mDo you want to change the starting balance?\n(1 - YES, other digit - NO)\x1b[37m" << endl;//зміна початкового балансу
    change = readNumber();
    if (change == 1)
    {
        cout << endl << "\x1b[32mEnter the start balance: \x1b[37m";
        double balance_start;
        int perev_plus = 1;
        while (perev_plus) {
            balance_start = readDouble();
            perev_plus = 0;
            if ((balance_start < 0) && (accounts_all[iter].type == Cash)) {
                perev_plus = 1;
                cout << "\x1b[31mCash cannot have a negative balance \n(quit - press 0,continue - press any digit):\n\x1b[37m";
                int quit = readNumber();
                if (quit == 0)return;
                cout << "\n\x1b[32mTry again: \x1b[37m";
            }
        }




        accounts_all[iter].balance_start = balance_start;
        accounts_all[iter].balance = balance_start;
    }
    cout << "Press any digit ";
    int charik;
    charik = readNumber();
}
//оновлення балансів рахунків
void Update_balance() {
  for (int i = 0; i < accounts_all.size(); i++)
    accounts_all[i].balance =
        accounts_all[i].balance_start; //баланс=поч балансу

  for (int i = 0; i < accounts_all.size(); i++) {
    for (int inc = 0; inc < income_all.size(); inc++) { //пройтися по доходах
      if (income_all[inc].acc_name == accounts_all[i].name)
        accounts_all[i].balance += income_all[inc].amount;
    }

    for (int exp = 0; exp < expenses_all.size(); exp++) { //пройтися по витратах
      if (expenses_all[exp].acc_name == accounts_all[i].name)
        accounts_all[i].balance -= expenses_all[exp].amount;
    }

    for (int trans = 0; trans < transfers_all.size();
         trans++) { //пройтися по переказах
      if (transfers_all[trans].name1 == accounts_all[i].name)
        accounts_all[i].balance -= transfers_all[trans].amount1;
      if (transfers_all[trans].name2 == accounts_all[i].name)
        accounts_all[i].balance += transfers_all[trans].amount2;
    }
  }
}
//друк рахунків
void Print_accounts() {
  cout << "\n";
  cout << " \x1b[46m\x1b[30m.                            REPORTS               "
          "                \x1b[37m\x1b[40m.\n";
  cout << "                           \x1b[36mShow accounts\x1b[37m\n";

  Update_balance();
  float uah = 0.0, usd = 0.0, eur = 0.0;
  string acc_type[] = {"Cash", "Bank account", "Privat loan"};
  string cur_name[] = {"UAH", "USD", "EUR"};
  cout << " ___________________________________________________________________"
          "\n";
  cout << " Account                 |Currency|      Balance      | Account "
          "type\n";
  cout
      << " -------------------------------------------------------------------\n";

  string tymch;
  for (int i = 0; i < accounts_all.size(); i++) {

    cout << " ";
    cout << accounts_all[i].name;
    for (int k = 23; k > accounts_all[i].name.size(); k--)
      cout << " ";
    cout << " |  " << cur_name[(int)accounts_all[i].currency] << "   |   ";
    tymch = to_string(accounts_all[i].balance);
    tymch.pop_back();
    tymch.pop_back();
    tymch.pop_back();
    tymch.pop_back();
    for (int k = 15; k > tymch.size(); k--)
      cout << " ";
    if (accounts_all[i].balance < 0)
      cout << "\x1b[31m";
    cout << tymch;
    if (accounts_all[i].balance < 0)
      cout << "\x1b[37m";
    cout << " | " << acc_type[accounts_all[i].type];
    cout<<endl;
    if (accounts_all[i].currency == UAH)
      uah += accounts_all[i].balance;
    if (accounts_all[i].currency == USD)
      usd += accounts_all[i].balance;
    if (accounts_all[i].currency == EUR)
      eur += accounts_all[i].balance;
  }
  cout << " ___________________________________________________________________"
          "\n";
  cout << " Total in UAH is " << uah << endl;
  cout << " Total in USD is " << usd << endl;
  cout << " Total in EUR is " << eur << endl;

  cout << " ___________________________________________________________________"
          "\n";
  cout << " The summary in UAH is "
       << round(
              (uah + usd * currency_all[1].kurs + eur * currency_all[2].kurs) *
              100) /
              100
       << endl;
  cout << " The summary in USD is "
       << round(
              (uah + usd * currency_all[1].kurs + eur * currency_all[2].kurs) /
              currency_all[1].kurs * 100) /
              100
       << endl;
  cout << " The summary in EUR is "
       << round(
              (uah + usd * currency_all[1].kurs + eur * currency_all[2].kurs) /
              currency_all[2].kurs * 100) /
              100
       << endl;
  cout << " ___________________________________________________________________"
          "_\n";
  cout << "Press any digit ";
  int charik;
  charik=readNumber();
}
//видалення рахунку - КОРИСТУВАЧ!!!!!!!!!!!!!!!!!!!!!!!!
int Del_acc() {
  cout << "\n";
    cout << " \x1b[46m\x1b[30m                            ACCOUNTS                               \x1b[37m\x1b[40m \n";
    cout << "                          \x1b[36mDelete account\x1b[37m\n";


    cout << "\n\x1b[32mWhich account do you want to delete? Enter its name:\n\x1b[37m";
    int perev = 1;
    int iter = -1;
    string tymchas;
    string name_tymch;
    string name;
    while (perev)
    {
        name = Vvod_z_klavy();
        name_tymch = name;
        Tolower(name_tymch);
        for (int i = 0; i < accounts_all.size(); i++)
        {
            tymchas = accounts_all[i].name;
            Tolower(tymchas);
            if (name_tymch == tymchas)
            {
                iter = i;
                perev = 0;
                break;
            }
        }
        if (perev) {
            cout << "\x1b[31mNo such account\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return 0;
            cout << "\n\x1b[32mTry again: \x1b[37m";
        }
    }
    for (int i = 0; i < income_all.size(); i++) {
        if (income_all[i].acc_name == accounts_all[iter].name){
            perev = 1;
        }
    }
    for(int i=0;i<expenses_all.size();i++){
        if (expenses_all[i].acc_name == accounts_all[iter].name){
            perev = 1;
        }
    }
    for (int i = 0; i < transfers_all.size(); i++) {
        if (transfers_all[i].name1 == accounts_all[iter].name|| transfers_all[i].name2 == accounts_all[iter].name) {
            perev = 1;
        }
    }
    if (!perev) {
        cout << "\x1b[31mAre you sure? (0-YES, 1- NO): \x1b[37m\n";
        int vybir = readNumber();
        if (vybir == 0) accounts_all.erase(accounts_all.begin() + iter);
    }
    else {
        cout << "\x1b[31mIt is not possible to delete the account on which there are saved \ntransactions!\n\x1b[37m";
        cout << "Press any digit ";
        char charik;
        cin >> charik;
        return 0;
    }
    return 0;
    cout << "Press any digit ";
    int charik;
    charik = readNumber();
}

//введення доходів вручну - КОРИСТУВАЧ!!!!!!!!!!!!!!!!!!!!!!!!
void Filling_incom_manual() {

  cout << "\n";
    cout << " \x1b[46m\x1b[30m                           OPERATIONS                              \x1b[37m\x1b[40m \n";
    cout << "                            \x1b[36mNew income\x1b[37m\n";

    Income inc;

    cout << endl << "\x1b[32mEnter the type of income\n(salary-0, interest-1, gift-2, other_inc-3):\x1b[37m";
    int type_inc_int =-1;
    while (type_inc_int < 0 || type_inc_int>3) {
        type_inc_int = readNumber();
        if (type_inc_int < 0 || type_inc_int>3) {
            cout << "\x1b[31mThis type does not exist\n(quit - press 0,continue - press any digit):\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << endl << "\x1b[32mTry again: \x1b[37m";
        }

    }
    inc.type = (Income_type)type_inc_int;  //type

    
    cout << endl << "\x1b[32mEnter the amount: \x1b[37m";
    double amount = readDouble();
    while (amount<=0) {
        cout << "\x1b[31mThe amount cannot be negative\n(quit - press 0,continue - press any digit):\x1b[37m";
        int quit = readNumber();
        if (quit == 0)return;
        cout << endl << "\x1b[32mTry again: \x1b[37m";
        amount = readDouble();
    }
    
    
    inc.amount = amount;   //amount


    cout << endl << "\x1b[32mEnter the name of the account:\x1b[37m ";
    string acc_name;
    string name_tymch;
    string tymchas;
    int perev = 0;
    int iter = -1;
    while (perev == 0)
    {
        acc_name = Vvod_z_klavy();
        name_tymch = acc_name;
        Tolower(name_tymch);
        for (int i = 0; i < accounts_all.size(); i++)
        {
            tymchas = accounts_all[i].name;
            Tolower(tymchas);
            if (name_tymch == tymchas)
            {
                iter = i;
                perev = 1;
                break;
            }
        }
        if (perev == 0)
        {
            cout << "\x1b[31mNo such account found\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";

        }
    }
    inc.acc_name = acc_name; //acc_name
    inc.currency = accounts_all[iter].currency;

    income_all.push_back(inc);
    cout << "Press any digit ";
    int charik;
    charik = readNumber();
}
//друк доходів
void Print_incom()
{
    cout << "\n";
    cout << " \x1b[46m\x1b[30m                             REPORTS                               \x1b[37m\x1b[40m \n";
    cout << "                            \x1b[36mShow incomes\x1b[37m\n";

    cout << "\n\n -------------------------------------------------------------------\n";
    cout << " #  |Currency|      Amount      | Category |      Account";
    cout << "\n -------------------------------------------------------------------\n";
    for (int i = 0; i < income_all.size(); i++)
    {
        cout <<" " << i + 1 ;
        if (i + 1 < 10)cout << "  |  ";
        if (i + 1 > 9 && i + 1 < 100 )cout << " |  ";
        if (income_all[i].currency == UAH)cout << "UAH   |";
        if (income_all[i].currency == USD)cout << "USD   |";
        if (income_all[i].currency == EUR)cout << "EUR   |";
        string sss = to_string(income_all[i].amount);
        sss.pop_back();
        sss.pop_back();
        sss.pop_back();
        sss.pop_back();
        for (int k = 17; k > sss.size(); k--)cout << " ";
        cout << sss;
       
        if (income_all[i].type == salary)cout << " | salary   | ";
        if (income_all[i].type == interest)cout << " | interest | ";
        if (income_all[i].type == gift)cout << " | gift     | ";
        if (income_all[i].type == other_inc)cout << " | other    | ";
        cout << income_all[i].acc_name;
        for (int k = 21; k >= income_all[i].acc_name.size(); k--)cout << " ";
        cout<<"\n";
    }
    cout << " -------------------------------------------------------------------\n\n";
    cout << "Press any digit ";
    int charik;
    charik = readNumber();

}

//введення витрат вручну - КОРИСТУВАЧ!!!!!!!!!!!!!!!!!!!!!!!!
void Filling_exp_manual() {
  cout << "\n";
    cout << " \x1b[46m\x1b[30m                           OPERATIONS                              \x1b[37m\x1b[40m \n";
    cout << "                            \x1b[36mNew expense\x1b[37m\n";
    Update_balance();
    Expenses exp;

    cout << endl << "\x1b[32mEnter the expense type (meal-0, household-1, clothing_and_shoes-2, \ncapital_expenses-3, communal_payments-4, other_exp-5):\x1b[37m";
    int type_exp_int = -1;
    while (type_exp_int < 0 || type_exp_int>5) {
        type_exp_int = readNumber();
        if (type_exp_int < 0 || type_exp_int>5) {
            cout << "\x1b[31mThis type does not exist (quit - press 0,continue - press any digit):\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << endl << "\x1b[32mTry again: \x1b[37m";
        }

    }
    exp.type = (Expenses_type)type_exp_int;  //type

    double amount_exp = 0;
    cout << endl << "\x1b[32mEnter the amount: \x1b[37m";
    amount_exp = readDouble();
    while (amount_exp <= 0) {
        cout << "\x1b[31mEnter a positive amount\n(quit - press 0,continue - press any digit):\x1b[37m";
        int quit = readNumber();
        if (quit == 0)return;
        cout << endl << "\x1b[32mTry again: \x1b[37m";
        amount_exp = readDouble();

    }
    exp.amount = amount_exp;   //amount

    cout << endl << "\x1b[32mEnter the name of the account:\x1b[37m";
    string acc_name_exp;
    string name_tymch;
    string tymchas;
    int perev1 = 0;
    int iter = -1;
    while (perev1 == 0)
    {
        acc_name_exp = Vvod_z_klavy();
        name_tymch = acc_name_exp;
        Tolower(name_tymch);
        for (int i = 0; i < accounts_all.size(); i++)

        {
            tymchas = accounts_all[i].name;
            Tolower(tymchas);
            if (name_tymch == tymchas)
            {
                perev1 = 1;
                iter = i;
                break;
            }
        }
        if (perev1 == 0)
        {
            cout << "\x1b[31mNo such account found\n(quit - press 0,continue - press any digit):\x1b[37m\n";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";

        }
    }
    

    exp.acc_name = acc_name_exp; //acc_name
    exp.currency = accounts_all[iter].currency;
    if (accounts_all[iter].balance < exp.amount && accounts_all[iter].type == Cash)
    {
        cout << "\x1b[31mSuch spending is not possible, it is greater than \nthe balance of cash, such transactions are possible\nonly with bank accounts or private loans\n\x1b[37m";
        return;
    }
    expenses_all.push_back(exp);
    cout << "Press any digit ";
    int charik;
    charik = readNumber();
}
//друк витрат
void Print_exp()
{
    cout << "\n";
    cout << " \x1b[46m\x1b[30m                             REPORTS                               \x1b[37m\x1b[40m \n";
    cout << "                           \x1b[36mShow expenses\x1b[37m\n";

    cout << "\n\n -------------------------------------------------------------------\n";
    cout << " #  |Currency|      Amount      |     Category     |   Account";
    cout << "\n -------------------------------------------------------------------\n";
    for (int i = 0; i < expenses_all.size(); i++)
    {
        cout << " " << i + 1;
        if (i + 1 < 10)cout << "  |  ";
        if (i + 1 > 9 && i + 1 < 100)cout << " |  ";
        if (expenses_all[i].currency == UAH)cout << "UAH   |";
        if (expenses_all[i].currency == USD)cout << "USD   |";
        if (expenses_all[i].currency == EUR)cout << "EUR   |";


        string sss = to_string(expenses_all[i].amount);
        sss.pop_back();
        sss.pop_back();
        sss.pop_back();
        sss.pop_back();
        for (int k = 17; k > sss.size(); k--)cout << " ";
        cout << sss;


        if (expenses_all[i].type == household)cout <<          " | household        | ";
        if (expenses_all[i].type == clothing_and_shoes)cout << " | clothing/shoes   | ";
        if (expenses_all[i].type == meal)cout <<               " | meal             | ";
        if (expenses_all[i].type == capital_expenses)cout <<   " | capital expenses | ";
        if (expenses_all[i].type == communal_payments)cout <<  " | communal payments| ";
        if (expenses_all[i].type == other_exp)cout <<          " | other            | ";
        cout << expenses_all[i].acc_name;
        for (int k = 21; k >= expenses_all[i].acc_name.size(); k--) cout << " ";
        cout << "\n";
    }
    cout << " -------------------------------------------------------------------\n\n";
    cout << "Press any digit ";
    int charik;
    charik = readNumber();

}

//введення переказу вручну - КОРИСТУВАЧ!!!!!!!!!!!!!!!!!!!!!!!!
void Filling_transf_manual() {
   cout << "\n";
    cout << " \x1b[46m\x1b[30m                           OPERATIONS                              \x1b[37m\x1b[40m \n";
    cout << "                           \x1b[36mNew transfer\x1b[37m\n";
    Update_balance();
    Transfer trans;
    cout << endl << "\x1b[32mEnter the name of the account from which funds are transferred (#1): \x1b[37m";
    string acc_name1;
    string name_tymch;
    string tymchas;
    int perev = 0;
    int iter1 = -1;
    while (perev == 0)
    {
        acc_name1 = Vvod_z_klavy();
        name_tymch = acc_name1;
        Tolower(name_tymch);
        for (int i = 0; i < accounts_all.size(); i++)
        {
            tymchas = accounts_all[i].name;
            Tolower(tymchas);
            if (name_tymch == tymchas)
            {
                iter1 = i;
                perev = 1;
                break;
            }
        }
        if (perev == 0)
        {
            cout << "\x1b[31mNo such account found\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";

        }
    }
    trans.name1= acc_name1; //acc_name1
    trans.currency1 = accounts_all[iter1].currency; //currency1
    cout << endl << "\x1b[32mEnter the amount (#1) in ";
    if (trans.currency1 == UAH)cout << "UAH: \x1b[37m";
    if (trans.currency1 == USD)cout << "USD: \x1b[37m";
    if (trans.currency1 == EUR)cout << "EUR: \x1b[37m";
    double amount1 = readDouble();
    trans.amount1 = amount1;   //amount1
    if (accounts_all[iter1].balance < trans.amount1 && accounts_all[iter1].type == Cash)
    {
        cout << "\x1b[31mSuch transfer is not possible, it is greater\nthan the balance of cash, such transactions are \npossible only with bank accounts or private loans\n\x1b[37m";
        return;
    }
    cout << endl << "\x1b[32mEnter the name of the account to which funds are transferred (#2): \x1b[37m";
    string acc_name2;
    string name_tymch1;
    string tymchas1;
    perev = 0;
    int iter2 = -1;
    while (perev == 0)
    {
        acc_name2 = Vvod_z_klavy();
        name_tymch1 = acc_name2;
        Tolower(name_tymch1);
        for (int i = 0; i < accounts_all.size(); i++)
        {
            tymchas1 = accounts_all[i].name;
            Tolower(tymchas1);
            if (name_tymch1 == tymchas1)
            {
                iter2 = i;
                perev = 1;
                break;
            }
        }
        if (perev == 0)
        {
            cout << "\x1b[31mNo such account found\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";

        }
        if (acc_name2 == acc_name1) {
            perev = 0;
            cout << "\x1b[31mThe accounts must not match!\n(quit - press 0,continue - press any digit):\n\x1b[37m";
            int quit = readNumber();
            if (quit == 0)return;
            cout << "\n\x1b[32mTry again: \x1b[37m";
        }

    }
    
    trans.currency2 =  accounts_all[iter2].currency; //currency2
    
    double amount2;
    if (trans.currency2 != trans.currency1)
    {
        cout << endl << "\x1b[32mEnter the amount (#2) in ";
        if (trans.currency2 == UAH)cout << "UAH: \x1b[37m";
        if (trans.currency2 == USD)cout << "USD: \x1b[37m";
        if (trans.currency2 == EUR)cout << "EUR: \x1b[37m";
        amount2 = readDouble();
    }
    else amount2 = amount1;

    trans.amount2 = amount2;   //amount2
    trans.name2 = acc_name2; //acc_name2
    transfers_all.push_back(trans);
    cout << "Press any digit ";
    int charik;
    charik = readNumber();
}
//друк перекзів      ?????????
void Print_transf() {
  cout << "\n";
  cout << " \x1b[46m\x1b[30m.                            REPORTS               "
          "                \x1b[37m\x1b[40m.\n";
  cout << "                           \x1b[36mShow transfers\x1b[37m\n";

  cout << "\n\n "
          "--------------------------------------------------------------------"
          "--------------\n";
  cout << " #  |      Account1       |     Amount1    |      Account2      |   "
          "  Amount2\n";
  cout << " -------------------------------------------------------------------"
          "---------------\n";
  for (int i = 0; i < transfers_all.size(); i++) {
    cout << " " << i + 1;
    if (i + 1 < 10)
      cout << "  |  ";
    if (i + 1 > 9 && i + 1 < 100)
      cout << " |  ";
    cout << transfers_all[i].name1;
    for (int k = 18; k >= transfers_all[i].name1.size(); k--)
      cout << " ";
    cout << "|";
    string sss = to_string(transfers_all[i].amount1);
    sss.pop_back();
    sss.pop_back();
    sss.pop_back();
    sss.pop_back();
    for (int k = 11; k > sss.size(); k--)
      cout << " ";
    cout << "-" << sss;

    if (transfers_all[i].currency1 == UAH)
      cout << " UAH| ";
    if (transfers_all[i].currency1 == USD)
      cout << " USD| ";
    if (transfers_all[i].currency1 == EUR)
      cout << " EUR| ";

    cout << transfers_all[i].name2;
    for (int k = 18; k >= transfers_all[i].name2.size(); k--)
      cout << " ";
    cout << "|";
    string sss1;
    sss1 = to_string(transfers_all[i].amount2);
    sss1.pop_back();
    sss1.pop_back();
    sss1.pop_back();
    sss1.pop_back();
    for (int k = 11; k > sss1.size(); k--)
      cout << " ";
    cout << " +" << sss1;

    if (transfers_all[i].currency2 == UAH)
      cout << " UAH";
    if (transfers_all[i].currency2 == USD)
      cout << " USD";
    if (transfers_all[i].currency2 == EUR)
      cout << " EUR";
    cout << "\n";
  }
  cout << " -------------------------------------------------------------------"
          "---------------\n\n";
  cout << "Press any digit ";
  int charik;
  charik=readNumber();
}

//все поудаляти
void Delete_data() {
  cout << "\n";
  cout << " \x1b[46m\x1b[30m.                           DELETE ALL             "
          "                \x1b[37m\x1b[40m.\n";
  cout << "\x1b[31mAre you sure? (0-YES, 1- NO): \x1b[37m\n";
  cout << "                         \x1b[36mAll data was deleted\x1b[37m\n";
  int vybir = readNumber();
  if (vybir == 0) {
    expenses_all.clear();
    accounts_all.clear();
    income_all.clear();
    transfers_all.clear();
    Filling_vect_curr();
    Filling_accounts();
  }

  cout << "Press any digit ";
  int charik;
  charik=readNumber();
}
//логотип
void Print_Hello() {
  cout << "****************************\n";
  cout << "*      *                   *\n";
  cout << "*    *****    \x1b[32mMY FINANCES\x1b[37m  *   Welcome to the "
          "personal\n";
  cout << "*  *********               *   finance accounting application!\n";
  cout << "*   |  \x1b[32m$\x1b[37m  |     \x1b[32mver 1.0.\x1b[37m   *\n";
  cout << "* -----------              *\n";
  cout << "****************************\n\n";
}
//меню
int Menu(){
  cout << "\n\n";
  cout << "**\x1b[32m MENU "
          "\x1b[37m************************************************************"
          "*\n";
  cout << "*\x1b[42m\x1b[30m.                             RATES                "
          "                \x1b[37m\x1b[40m*\n";
  cout << "*                  Show exchange rates \x1b[32m(press  1)\x1b[37m   "
          "                *\n";
  cout << "*                  Edit exchange rates \x1b[32m(press  2)\x1b[37m   "
          "                *\n";
  cout << "********************************************************************"
          "*\n";
  cout << "*\x1b[42m\x1b[30m.          ACCOUNTS              "
          "\x1b[37m\x1b[40m*\x1b[42m\x1b[30m.           OPERATIONS           "
          "\x1b[37m\x1b[40m*\n";
  cout << "* New account         \x1b[32m(press  3)\x1b[37m  *   New income    "
          "      \x1b[32m(press  6)\x1b[37m*\n";
  cout << "* Edit account        \x1b[32m(press  4)\x1b[37m  *   New expense   "
          "      \x1b[32m(press  7)\x1b[37m*\n";
  cout << "* Delete account      \x1b[32m(press  5)\x1b[37m  *   New transfer  "
          "      \x1b[32m(press  8)\x1b[37m*\n";
  cout << "********************************************************************"
          "*\n";
  cout << "*\x1b[42m\x1b[30m.                            REPORTS               "
          "                \x1b[37m\x1b[40m*\n";
  cout << "* Show accounts       \x1b[32m(press  9)\x1b[37m  *   Show "
          "transfers      \x1b[32m(press 12)\x1b[37m*\n";
  cout << "* Show incomes        \x1b[32m(press 10)\x1b[37m  *   Income report "
          "      \x1b[32m(press 13)\x1b[37m*\n";
  cout << "* Show expenses       \x1b[32m(press 11)\x1b[37m  *   Expense "
          "report      \x1b[32m(press 14)\x1b[37m*\n";
  cout << "********************************************************************"
          "*\n";
  cout << "*                 SAVE                \x1b[32m(press  0)\x1b[37m    "
          "                *\n";
  cout << "*                 Delete all data     \x1b[32m(press -1)\x1b[37m    "
          "                *\n";
  cout << "*                 EXIT                \x1b[32m(press -2)\x1b[37m    "
          "                *\n";
  cout << "********************************************************************"
          "*\n";

  int vybir = -3;
  while (vybir < -2 || vybir > 14) {
    cout << "\x1b[32mMake your choice, please:  \x1b[37m";
    vybir = readNumber();
  }
  return vybir;
}
void Save_all() {
  cout << "\n";
  cout << " \x1b[46m\x1b[30m.                            SAVE ALL              "
          "                \x1b[37m\x1b[40m.\n";
  cout << "                         \x1b[36mAll data was saved\x1b[37m\n";
  Update_balance();
  Curr_to_file();
  Acc_to_file();
  Inc_to_file();
  Exp_to_file();
  Transf_to_file();
  cout << "Press any digit ";
  int charik;
  charik=readNumber();
}

//звіт по доходах в розрізі категорій      ?????????
void Report_inc() {
  cout << "\n";
  cout << " \x1b[46m\x1b[30m.                            REPORTS               "
          "                \x1b[37m\x1b[40m.\n";
  cout << "                           \x1b[36mIncome report\x1b[37m\n";
  Income_type type;
  double amount = 0.0, amount_salary = 0.0, amount_interest = 0.0,
         amount_gift = 0.0, amount_other = 0.0;
  // Type_currency currency;
  // string acc_name;

  //сума доходу
  for (int i = 0; i < income_all.size(); i++) {
    double rate = 0.00;
    for (int k = 0; k < currency_all.size(); k++) {
      if (income_all[i].currency == currency_all[k].currency) {
        rate = currency_all[k].kurs;
        break;
      }
    }
    amount += income_all[i].amount * rate;

    if (income_all[i].type == salary)
      amount_salary += income_all[i].amount * rate;
    if (income_all[i].type == interest)
      amount_interest += income_all[i].amount * rate;
    if (income_all[i].type == gift)
      amount_gift += income_all[i].amount * rate;
    if (income_all[i].type == other_inc)
      amount_other += income_all[i].amount * rate;
  }

  // salary, interest, gift,other_inc
  cout << "The total amount of income is  " << amount << " UAH, including:\n\n";

  if (amount_salary) {
    cout << "\n   * salary:   ";
    for (int i = 0; i <= amount_salary / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_salary << " UAH \x1b[32m("
         << round(amount_salary / amount * 100 * 100) / 100 << " %)\x1b[37m\n";
  }
  if (amount_interest) {
    cout << "\n   * interest: ";
    for (int i = 0; i <= amount_interest / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_interest << " UAH \x1b[32m("
         << round(amount_interest / amount * 100 * 100) / 100
         << " %)\x1b[37m\n";
  }
  if (amount_gift) {
    cout << "\n   * gift:     ";
    for (int i = 0; i <= amount_gift / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_gift << " UAH \x1b[32m("
         << round(amount_gift / amount * 100 * 100) / 100 << " %)\x1b[37m\n";
  }
  if (amount_other) {
    cout << "\n   * other:    ";
    for (int i = 0; i <= amount_other / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_other << " UAH \x1b[32m("
         << round(amount_other / amount * 100 * 100) / 100 << " %)\x1b[37m\n";
  }
  cout << "\n";

  cout << "Press any digit ";
  int charik;
  charik=readNumber();
}
//звіт по витратах в розрізі категорій      ?????????
void Report_exp() {
  cout << "\n";
  cout << " \x1b[46m\x1b[30m.                            REPORTS               "
          "                \x1b[37m\x1b[40m.\n";
  cout << "                           \x1b[36mExpense report\x1b[37m\n";
  Income_type type;
  double amount = 0.0, amount_meal = 0.0, amount_household = 0.0,
         amount_clothing_and_shoes = 0.0, amount_capital_expenses = 0.0,
         amount_communal_payments = 0.0, amount_other_exp = 0.0;

  //сума витрат
  for (int i = 0; i < expenses_all.size(); i++) {
    double rate = 0.00;
    for (int k = 0; k < currency_all.size(); k++) {
      if (expenses_all[i].currency == currency_all[k].currency) {
        rate = currency_all[k].kurs;
        break;
      }
    }
    amount += expenses_all[i].amount * rate;
    if (expenses_all[i].type == meal)
      amount_meal += expenses_all[i].amount * rate;
    if (expenses_all[i].type == household)
      amount_household += expenses_all[i].amount * rate;
    if (expenses_all[i].type == clothing_and_shoes)
      amount_clothing_and_shoes += expenses_all[i].amount * rate;
    if (expenses_all[i].type == capital_expenses)
      amount_capital_expenses += expenses_all[i].amount * rate;
    if (expenses_all[i].type == communal_payments)
      amount_communal_payments += expenses_all[i].amount * rate;
    if (expenses_all[i].type == other_exp)
      amount_other_exp += expenses_all[i].amount * rate;
  }

  cout << "The total amount of expenses is  " << amount
       << " UAH, including:\n\n";

  if (amount_meal) {
    cout << "\n* meal:              ";
    for (int i = 0; i <= amount_meal / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_meal << " UAH \x1b[32m("
         << round(amount_meal / amount * 100 * 100) / 100 << " %)\x1b[37m\n";
  }

  if (amount_household) {
    cout << "\n* household:         ";
    for (int i = 0; i <= amount_household / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_household << " UAH \x1b[32m("
         << round(amount_household / amount * 100 * 100) / 100
         << " %)\x1b[37m\n";
  }

  if (amount_clothing_and_shoes) {
    cout << "\n* clothing and shoes:";
    for (int i = 0; i <= amount_clothing_and_shoes / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_clothing_and_shoes << " UAH \x1b[32m("
         << round(amount_clothing_and_shoes / amount * 100 * 100) / 100
         << " %)\x1b[37m\n";
  }

  if (amount_capital_expenses) {
    cout << "\n* capital expenses:  ";
    for (int i = 0; i <= amount_capital_expenses / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_capital_expenses << " UAH \x1b[32m("
         << round(amount_capital_expenses / amount * 100 * 100) / 100
         << " %)\x1b[37m\n";
  }

  if (amount_communal_payments) {
    cout << "\n* communal payments: ";
    for (int i = 0; i <= amount_communal_payments / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_communal_payments << " UAH \x1b[32m("
         << round(amount_communal_payments / amount * 100 * 100) / 100
         << " %)\x1b[37m\n";
  }

  if (amount_other_exp) {
    cout << "\n* other:             ";
    for (int i = 0; i <= amount_other_exp / amount * 30; i++)
      cout << "\x1b[42m\x1b[30m+\x1b[37m\x1b[40m";
    cout << "...." << amount_other_exp << " UAH \x1b[32m("
         << round(amount_other_exp / amount * 100 * 100) / 100
         << " %)\x1b[37m\n";
  }
  cout << "\n";
  cout << "Press any digit ";
  int charik;
  charik=readNumber();
}

/////////////////////////////////////////////////////////

int readNumber() {
  int a;
  while (true) {
    // cout << "Введіть число:";
    cin >> a;
    if (cin.fail()) // если предыдущее извлечение оказалось неудачным
    {
      cin.clear(); //  возвращаем cin в 'обычный' режим работы
      cin.ignore(
          32767,
          '\n'); // и удаляем значения предыдущего ввода из входного буфера
      cout << "\x1b[31mPlease try again! \x1b[37m\n";
    } else {
      cin.ignore(32767, '\n'); // удаляем лишние значения
      return a;
    }
  }
}
double readDouble() {
  double a;
  while (true) {
    cin >> a;
    if (cin.fail()) // если предыдущее извлечение оказалось неудачным
    {
      cin.clear(); //  возвращаем cin в 'обычный' режим работы
      cin.ignore(
          32767,
          '\n'); // и удаляем значения предыдущего ввода из входного буфера
      cout << "\x1b[31mPlease try again! \x1b[37m\n";
    } else {
      cin.ignore(32767, '\n'); // удаляем лишние значения
      return a;
    }
  }
}
string Vvod_z_klavy() {
  string riadok;
  cin.clear(); //  возвращаем cin в 'обычный' режим работы
  while (riadok.size() == 0)
    getline(cin, riadok);

  return riadok;
}

void Tolower(string &text)
{
    for (int i = 0; i < text.length(); i++)
        text[i] = tolower(text[i]);
}

#endif