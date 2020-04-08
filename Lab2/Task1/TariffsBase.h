#ifndef TARIFFSBASE_H
#define TARIFFSBASE_H

#include "C:\BSUIR\C\deRigorich\deRigorich.h"

/* ���������� ������������ */
typedef struct {
    int MinsInsideNetwork,
        MinsOthersOperators,
        SmsCount,
        MbCount;
} UserInfo;

/* ���������� � ������ */
typedef struct {
    char* Name;
    char* Info;
    double (*CostCalc)(void);
} Tariff;

/* ������� ������������ */
UserInfo* CurrentUser;

/* ������ ��������� ������� */
Vector* ListTariffs;

/* ������� ������ ������� �� ���� */
void ReadTariffs(void);

#endif