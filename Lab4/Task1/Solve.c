
#include "deRigorich.h"

#include <windows.h>

#define USEFILE

char ToLowerCase(char what) {
    char sym;
    for (sym = 'A'; sym <= 'Z'; sym++)
        if(what == sym) return 'a'+sym-'A';
    for (sym = 'А'; sym <= 'Я'; sym++)
        if(what == sym) return 'а'+sym-'А';
    return what;
}

int main(void) {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);
    
#ifdef USEFILE
    FILE* inflow = fopen("text.txt", "r");
    if (!inflow) {
        FatalError("Файл с текстом не найден");
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
    
    Vector* Alphabet = StringNew();
    char sym;
    for (sym = 'a'; sym <= 'z'; sym++)
        StringAddElem(Alphabet, sym);
    for (sym = 'A'; sym <= 'Z'; sym++)
        StringAddElem(Alphabet, sym);
    for (sym = 'а'; sym <= 'я'; sym++)
        StringAddElem(Alphabet, sym);
    for (sym = 'А'; sym <= 'Я'; sym++)
        StringAddElem(Alphabet, sym);
    
    int AnsLen = 0, AnsInd = -1;
    int WordBeginInd = 0;
    Set* WordLetters = SetNew(sizeof(char), CmpChar);
    int i;
    for (i = 0; StringGetElem(str,i); i++) {
        if (!StringContainElem(Alphabet, StringGetElem(str,i))) {
            int Len = i - WordBeginInd;
            if (SetSize(WordLetters) == Len && Len > AnsLen) {
                AnsLen = Len;
                AnsInd = WordBeginInd;
            }
            WordBeginInd = i+1;
            SetClear(WordLetters);
        } else {
            char tmp = ToLowerCase(StringGetElem(str,i));
            SetAddElem(WordLetters, &tmp);
        }
    }
    
    printf("\nСамое длинное слово из различных букв: ");
    if (AnsInd != -1) {
        for (i = AnsInd; StringContainElem(Alphabet, StringGetElem(str,i)); i++)
            printf("%c", StringGetElem(str,i));
    } else {
         printf("---");
    }
    printf("\n");    
    return 0;
}