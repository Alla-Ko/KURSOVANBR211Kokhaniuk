#define _CRT_SECURE_NO_WARNINGS
#include "input.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  Print_Hello();
  //початок роботи витягування файлів

  Curr_from_file(); //витягування курсів з файла
  Acc_from_file(); //підтягуємо з файла рахунки початкові
  Inc_from_file();    //втягнення доходів
  Exp_from_file();    //втягнення витрат
  Transf_from_file(); //втягнення переказів

  int vybir = 199;
  while (vybir != -2) {
    vybir = Menu();
    if (vybir == -2)
      return 0;
    if (vybir == 0)
      Save_all();
    if (vybir == -1)
      Delete_data();

    //робота з курсами
    if (vybir == 1) Print_vect_curr();
    if (vybir == 2) Change_vect_curr();

    //робота з рахунками
    if (vybir == 3) Filling_acc_manual();
    if (vybir == 4) Change_account();
    if (vybir == 5) Del_acc();
    //введення операцій
    if (vybir == 6) Filling_incom_manual();
    if (vybir == 7) Filling_exp_manual();
    if (vybir == 8) Filling_transf_manual();
    //відображення таблиць
    if (vybir == 9) Print_accounts();
    if (vybir == 10) Print_incom();
    if (vybir == 11) Print_exp();
    if (vybir == 12) Print_transf();
    //звіти
    if (vybir == 13) Report_inc();
    if (vybir == 14) Report_exp();
  }

  return 0;
}