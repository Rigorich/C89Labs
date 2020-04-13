#include "TariffsBase.h"

/* 
    ��� ���������� ������ � ���� ������ �������� �������� ����
    � ����� �������, ��������������� ���������, ���������
    � �������� ���������� �������� ����� �� ���������� ������������
    (����������� ���������� CurrentUser ���� ��������� UserInfo)
    � ��������� � � ���� ������ ������� void ReadTariffs(void).
    
    typedef struct {
        int MinsInsideNetwork,
            MinsOthersOperators,
            SmsCount,
            MbCount;
    } UserInfo;
    
    
    ������ ������:
    
    char* NameXX = "��������";
    char* InfoXX = "��������";
    double FuncXX(void) {
        double sum = %�����������_�����%;
        
        sum += f1(CurrentUser->MinsInsideNetwork);
        
        sum += f2(CurrentUser->MinsOthersOperators);
        
        sum += f3(CurrentUser->SmsCount);
        
        sum += f4(CurrentUser->MbCount);
        
        return sum;
    }
 
*/

/* ���������� ������ ������ � ������ */
void AddTariff(char* NameStr, char* InfoStr, double (*CostFunc)( )) {
    Tariff tmp = {NameStr, InfoStr, CostFunc};
    VectorAddElem(ListTariffs, &tmp);   
}

/* �������� �������� ��� */
double OpenInternet(int MB) {
    if(MB < 1) return 0;
    if(MB < 100) return 1.75;
    if(MB < 500) return 3.55;
    if(MB < 2*1024) return 8.35;
    if(MB < 5*1024) return 12.00;
    if(MB < 10*1024) return 18.00;
    if(MB < 15*1024) return 24.00;
    if(MB < 30*1024) return 42.00;
    if(MB < 60*1024) return 60.00;
    return 100.00;
}

char* Name1 = "����� �������";
char* Info1 = "�������� ������ �� ������ ��������� ���";
double Func1(void) {
    double sum = 0.64;
    
    sum += min(CurrentUser->MinsInsideNetwork, 3) * 0.0838;
    sum += max(CurrentUser->MinsInsideNetwork - 3, 0) * 0.0298;
    
    sum += CurrentUser->MinsOthersOperators * 0.1684;
    
    sum += CurrentUser->SmsCount * 0.023;
    
    sum += OpenInternet(CurrentUser->MbCount - 50);
    
    return sum;
}

char* Name2 = "����������� 2.0";
char* Info2 = "����������� �������� ��� ���������";
double Func2(void) {
    double sum = 22.50;
    int FreeMinCnt = 400;
    int tmp;

    tmp = min(FreeMinCnt, CurrentUser->MinsInsideNetwork);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsInsideNetwork - tmp) * 0.045;
    
    tmp = min(FreeMinCnt, CurrentUser->MinsOthersOperators);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsOthersOperators - tmp) * 0.095;
    
    sum += CurrentUser->SmsCount * 0.075;
    
    return sum;
}

char* Name3 = "����� max+";
char* Info3 = "�������� �� YouTube � �������, 20 �� � �������� ������� �� ��� ����";
double Func3(void) {
    double sum = 25.00;
    
    sum += OpenInternet(CurrentUser->MbCount - 20*1024);
    
    sum += CurrentUser->SmsCount * 0.0595;
    
    return sum;
}

char* Name4 = "����� 8";
char* Info4 = "�������� �� ������� � ����������� � 8 �� �� ��������� ��������";
double Func4(void) {
    double sum = 17.70;
    
    int FreeMinCnt = 400;
    int tmp;

    tmp = min(FreeMinCnt, CurrentUser->MinsInsideNetwork);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsInsideNetwork - tmp) * 0.0365;
    
    tmp = min(FreeMinCnt, CurrentUser->MinsOthersOperators);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsOthersOperators - tmp) * 0.0938;
    
    sum += OpenInternet(CurrentUser->MbCount - 8*1024);
    
    sum += CurrentUser->SmsCount * 0.0595;
    
    return sum;
}

char* Name5 = "�����";
char* Info5 = "�������� �� ����������� � 1 �� ���������";
double Func5(void) {
    double sum = 10.40;
    
    int FreeMinCnt = 200;
    int tmp;

    tmp = min(FreeMinCnt, CurrentUser->MinsInsideNetwork);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsInsideNetwork - tmp) * 0.0469;
    
    tmp = min(FreeMinCnt, CurrentUser->MinsOthersOperators);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsOthersOperators - tmp) * 0.1147;
    
    sum += OpenInternet(CurrentUser->MbCount - 1*1024);
    
    sum += CurrentUser->SmsCount * 0.0595;
    
    return sum;
}

char* Name6 = "ULTRA";
char* Info6 = "��� ���, ��� �� ������������ ���� � �������";
double Func6(void) {
    double sum = 52.98;
    int FreeMinCnt = 1000;
    int tmp;

    tmp = min(FreeMinCnt, CurrentUser->MinsInsideNetwork);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsInsideNetwork - tmp) * 0.0236;
    
    tmp = min(FreeMinCnt, CurrentUser->MinsOthersOperators);
    FreeMinCnt -= tmp;
    sum += (CurrentUser->MinsOthersOperators - tmp) * 0.0960;
    
    sum += OpenInternet(CurrentUser->MbCount - 10*1024);
    
    sum += max(CurrentUser->SmsCount - 1000, 0) * 0.047;
    
    return sum;
}

char* Name7 = "�������";
char* Info7 = "���������� �������� �� ���";
double Func7(void) {
    double sum = 143.41;

    return sum;
}

/* ���������� ��������� ������� � ������ */
void ReadTariffs(void) {
    AddTariff(Name1, Info1, Func1);
    AddTariff(Name2, Info2, Func2);
    AddTariff(Name3, Info3, Func3);
    AddTariff(Name4, Info4, Func4);
    AddTariff(Name5, Info5, Func5);
    AddTariff(Name6, Info6, Func6);
    AddTariff(Name7, Info7, Func7);
}
