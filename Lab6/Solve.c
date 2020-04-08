
#include "C:\BSUIR\C\deRigorich\deRigorich.h"

#include <windows.h>

#define USEFILE

char Vowels[] =
    {'a','e','i','o','u','A','E','I','O','U',
    '�','�','�','�','�','�','�','�','�','�',
    '�','�','�','�','�','�','�','�','�','�', '\0'};
    
bool IsLetterVowel(char sym){
    int i;
    for(i = 0; Vowels[i]; i++)
        if(Vowels[i] == sym)
            return true;
    return false;
}

int main(void) {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);
    
    
    Vector* Alphabet = StringNew();
    char sym;
    for (sym = 'a'; sym <= 'z'; sym++)
        StringAddElem(Alphabet, sym);
    for (sym = 'A'; sym <= 'Z'; sym++)
        StringAddElem(Alphabet, sym);
    for (sym = '�'; sym <= '�'; sym++)
        StringAddElem(Alphabet, sym);
    for (sym = '�'; sym <= '�'; sym++)
        StringAddElem(Alphabet, sym);

#ifdef USEFILE
    FILE* inflow = fopen("text.txt", "r");
    if (!inflow) {
        FatalError("���� � ������� �� ������");
    }
#else
    FILE* inflow = stdin;
#endif

    Vector* str = StringNew();
    StringReadLn(str, inflow);
    StringAddElem(str, '\n');
    
#ifdef USEFILE
    printf("%s", StringBegin(str));
#endif
    
    Map* Analysis = MapNew(sizeof(char), sizeof(int), CmpChar, NullInt);
    int i;
    for(i = 0; i < StringSize(str); i++){
        char sym = StringGetElem(str, i);
        (TO(int)MapValue(Analysis, &sym)) += 1;
    }
    
    int VowelsCount = 0, ConsonantsCount = 0;
    for(i = 0; i < StringSize(Alphabet); i++){
        char sym = StringGetElem(Alphabet, i);
        if(IsLetterVowel(sym)) {
            VowelsCount += (TO(int)MapValue(Analysis, &sym));
        } else {
            ConsonantsCount += (TO(int)MapValue(Analysis, &sym));
        }
    }
    printf(" ��������� ���� - %d \n ������� ���� - %d \n ������� > ��������� ? %d \n",
            ConsonantsCount, VowelsCount, VowelsCount > ConsonantsCount);
    
    return 0;
}