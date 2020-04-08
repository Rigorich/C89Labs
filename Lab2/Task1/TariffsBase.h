#ifndef TARIFFSBASE_H
#define TARIFFSBASE_H

#include "C:\BSUIR\C\deRigorich\deRigorich.h"

/* Статистика пользователя */
typedef struct {
    int MinsInsideNetwork,
        MinsOthersOperators,
        SmsCount,
        MbCount;
} UserInfo;

/* Информация о тарифе */
typedef struct {
    char* Name;
    char* Info;
    double (*CostCalc)(void);
} Tariff;

/* Текущий пользователь */
UserInfo* CurrentUser;

/* Массив доступных тарифов */
Vector* ListTariffs;

/* Функция чтения тарифов из базы */
void ReadTariffs(void);

#endif