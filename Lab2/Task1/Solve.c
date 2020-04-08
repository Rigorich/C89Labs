
#include "C:\BSUIR\C\deRigorich\deRigorich.h"

#include <stdlib.h>
#include <locale.h>

#include "C:\BSUIR\C\Lab2\Task1\TariffsBase.h"

void WriteTariffs(void) {
    system("cls");
    printf("��������� ������:\n\n");
    int i;
    for (i = 0; i < ListTariffs->size; i++) 
    {
        printf(" %s: \n %s \n ���������: %.2f \n\n", 
               ((Tariff*)VectorGetElem(ListTariffs, i))->Name,
               ((Tariff*)VectorGetElem(ListTariffs, i))->Info,
               ((Tariff*)VectorGetElem(ListTariffs, i))->CostCalc());
    }
    printf("----------\n");
    getch();
}

void EnterUserInfo(void) {
    system("cls");
    printf("\n ����������, ��������� ����������\n");
    printf("\n ������� ���������� ����� ������� � ���� ���:\n ");
    CurrentUser->MinsInsideNetwork = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
    printf("\n ������� ���������� ����� ������� � ������ ����:\n ");    
    CurrentUser->MinsOthersOperators = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
    printf("\n ������� ���������� ������������ ���:\n ");        
    CurrentUser->SmsCount = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
    printf("\n ������� ���������� �������������� �� ���������:\n ");        
    CurrentUser->MbCount = StringReadInt(stdin, 0, MAXINT);
    StringIgnore(stdin);
}

void ContactInfo(void) {
    system("cls");
    FILE* inflow = fopen("ContactInfo.txt", "r");
    if (!inflow) 
    {
        printf("���� � ���������� ����������� �� ������\n");
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
        printf("��� ������� � ���� ������!\n");
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
    printf("\n ������ ����� ��� ���: %s \n %s \n ����� �� �����: %.2f \n\n", 
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
        printf(" ����:\n");
        printf(" 1 - �������� ����������\n");
        printf(" 2 - ��������� ������ �����\n");
        printf(" 3 - ���������� ��� ������\n");
        printf(" 4 - ���������� ����������\n");
        printf(" Esc - �����\n");
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
    printf("\n ����� ���������� � �������� ���!\n\n ������� ����� ������� ��� ����������� ");
    getch();
    ListTariffs = VectorNew(sizeof(Tariff));
    ReadTariffs();
    CurrentUser = Malloc(sizeof(UserInfo));
    EnterUserInfo();
    Menu();
    printf(" �������� ���!\n");
    return 0;
}