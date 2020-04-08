
#include "C:\BSUIR\C\deRigorich\deRigorich.h"

#include <stdlib.h>
#include <locale.h>

#include "C:\BSUIR\C\Lab2\Task1\TariffsBase.h"

void WriteTariffs(void) {
    system("cls");
    printf("Доступные тарифы:\n\n");
    int i;
    for (i = 0; i < ListTariffs->size; i++) 
    {
        printf(" %s: \n %s \n Стоимость: %.2f \n\n", 
               ((Tariff*)VectorGetElem(ListTariffs, i))->Name,
               ((Tariff*)VectorGetElem(ListTariffs, i))->Info,
               ((Tariff*)VectorGetElem(ListTariffs, i))->CostCalc());
    }
    printf("----------\n");
    getch();
}

void EnterUserInfo(void) {
    system("cls");
    printf("\n Пожалуйста, заполните статистику\n");
    printf("\n Введите количество минут звонков в сети МТС:\n ");
    CurrentUser->MinsInsideNetwork = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
    printf("\n Введите количество минут звонков в другие сети:\n ");    
    CurrentUser->MinsOthersOperators = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
    printf("\n Введите количество отправленных СМС:\n ");        
    CurrentUser->SmsCount = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
    printf("\n Введите количество использованных МБ Интернета:\n ");        
    CurrentUser->MbCount = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
}

void ContactInfo(void) {
    system("cls");
    FILE* inflow = fopen("ContactInfo.txt", "r");
    if (!inflow) 
    {
        printf("Файл с контактной информацией не найден\n");
        getch();
        return;
    }
    char sym;
    fscanf(inflow, "%c", &sym);
    while (!feof(inflow)) 
    {
        printf("%c", sym);
        fscanf(inflow, "%c", &sym);
    }
    printf("\n");
    getch();
}

void FindBestSolution(void) {
    system("cls");
    if (!ListTariffs->size) 
    {
        printf("Нет тарифов в базе данных!\n");
        getch();
        return;
    }
    int MinInd = 0;
    int i;
    for (i = 0; i < ListTariffs->size; i++) 
    {
        if(((Tariff*)VectorGetElem(ListTariffs, i))->CostCalc() <
           ((Tariff*)VectorGetElem(ListTariffs, MinInd))->CostCalc()) 
           {
                MinInd = i;
           }
    }
    printf("\n Лучший тариф для вас: %s \n %s \n Плата за месяц: %.2f \n\n", 
           ((Tariff*)VectorGetElem(ListTariffs, MinInd))->Name,
           ((Tariff*)VectorGetElem(ListTariffs, MinInd))->Info,
           ((Tariff*)VectorGetElem(ListTariffs, MinInd))->CostCalc());
    getch();
}

void Menu(void) {
    char MenuItem;
    for(;;) 
    {
        system("cls");
        printf("\n");
        printf(" Меню:\n");
        printf(" 1 - Изменить статистику\n");
        printf(" 2 - Подобрать лучший тариф\n");
        printf(" 3 - Посмотреть все тарифы\n");
        printf(" 4 - Контактная информация\n");
        printf(" Esc - Выход\n");
        printf("\n");
        MenuItem = getch();
        switch(MenuItem)
        {
            case ESC:
                return;
            case '1':
                EnterUserInfo();
                break;
            case '2':
                FindBestSolution();
                break;
            case '3':
                WriteTariffs();
                break;
            case '4':
                ContactInfo();
                break;
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "");
    printf("\n Добро пожаловать в помощник МТС!\n\n Нажмите любую клавишу для продолжения ");
    getch();
    ListTariffs = VectorNew(sizeof(Tariff));
    ReadTariffs();
    CurrentUser = Malloc(sizeof(UserInfo));
    EnterUserInfo();
    Menu();
    printf(" Хорошего дня!\n");
    return 0;
}