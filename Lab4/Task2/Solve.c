
#include "C:\BSUIR\C\deRigorich\deRigorich.h"

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

typedef struct {
    char* Word;
    int Count;   
} Entry;

bool DictComp (void* a, void* b) {
    Entry* A = a;
    Entry* B = b;
    if (A->Count > B->Count) return true;
    if (A->Count < B->Count) return false;
    return CmpCharArray(&(A->Word), &(B->Word));
}

int main(void) {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);

    Vector* str = StringNew();
    char sym;
    
#ifdef USEFILE
    FILE* inflow = fopen("text.txt", "r");
    if (!inflow) {
        FatalError("Файл с текстом не найден");
    }
    fscanf(inflow, "%c", &sym);
    while (!feof(inflow)) {
        StringAddElem(str, sym);
        fscanf(inflow, "%c", &sym);
    }
    StringAddElem(str, '\n');
    printf("%s", StringBegin(str));
#else
    FILE* inflow = stdin;
    StringReadLn(str, inflow);
    StringAddElem(str, '\n');
#endif

    int i;
    for(i = 0; StringGetElem(str, i); i++ )
        StringSetElem(str, i, ToLowerCase(StringGetElem(str, i)));

    Vector* Alphabet = StringNew();
    for (sym = 'a'; sym <= 'z'; sym++)
        StringAddElem(Alphabet, sym);
    for (sym = 'а'; sym <= 'я'; sym++)
        StringAddElem(Alphabet, sym);
    
    int AnsLen = 0, AnsInd = -1;
    int WordBeginInd = 0;
    Map* Frequency = MapNew(sizeof(char*), sizeof(int), CmpCharArray, NullInt);
    
    for (i = 0; i < StringSize(str); i++) {
        if (!StringContainElem(Alphabet, StringGetElem(str, i))) {
            StringSetElem(str, i, '\0');
            if (WordBeginInd < i) {
                char* tmp = StringBegin(str) + WordBeginInd;
                (TO(int)MapValue(Frequency, &tmp))++; 
            }
            WordBeginInd = i+1;
        }
    }
    
    Vector* Dictionary = VectorNew(sizeof(Entry));
    for(i = 0; i < Frequency->size; i++) {
        Entry tmp;
        tmp.Word = TO(char*)VectorGetElem(Frequency->keys, i);
        tmp.Count = TO(int)VectorGetElem(Frequency->values, i);
        VectorAddElem(Dictionary, &tmp);
    }
    VectorSortComp(Dictionary, DictComp);
    /*
    for(i = 0; i < Frequency->size; i++)
        printf("%s - %d\n", TO(char*)VectorGetElem(Frequency->keys, i), 
                            TO(int)VectorGetElem(Frequency->values, i));
    */
    printf("\nТоп-%d слов:\n", min(VectorSize(Dictionary), 20));
    for(i = 0; i < min(VectorSize(Dictionary), 20); i++)
        printf("%s - %d\n", (TO(Entry)VectorGetElem(Dictionary, i)).Word, 
                            (TO(Entry)VectorGetElem(Dictionary, i)).Count);
    return 0;
}