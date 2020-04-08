
#include "C:\BSUIR\C\deRigorich\deRigorich.h"

typedef struct Vertex Vertex;
struct Vertex {
    void* value;
    Vertex* prev;
    Vertex* next;
};

typedef struct {
    Vertex* base;
    int elemsize;
    int size;
} List;

Vertex* ListBegin(List* this) { return this->base->next; }
Vertex* ListLast(List* this) { return this->base->prev; }
Vertex* ListEnd(List* this) { return this->base; }

List* ListNew(int sizeof_element){
    Vertex* tmpVertex = Malloc(sizeof(Vertex));
    tmpVertex->value = NULL;
    tmpVertex->prev = tmpVertex;
    tmpVertex->next = tmpVertex;
    
    List* tmpList = Malloc(sizeof(List));
    tmpList->base = tmpVertex;
    tmpList->elemsize = sizeof_element;
    tmpList->size = 0;
    return tmpList;
}

List* ListClear(List* this){
    Vertex* it = ListBegin(this);
    while(it != ListEnd(this)){
        Vertex* nextVertex = it->next;
        free(it->value);
        free(it);
        it = nextVertex;
    }
    this->base->prev = this->base;
    this->base->next = this->base;
}

List* ListDelete(List* this){
    ListClear(this);
    free(this->base);
    free(this);
}

void ListAddVertexRight(List* this, Vertex* afterWhich, void* what){
    Vertex* tmp = Malloc(sizeof(Vertex));
    tmp->value = Malloc(this->elemsize);
    memcpy(tmp->value, what, this->elemsize);
    
    tmp->next = afterWhich->next;
    tmp->prev = afterWhich;
    afterWhich->next->prev = tmp;
    afterWhich->next = tmp;
    
    this->size += 1;
}

void ListAddVertexLeft(List* this, Vertex* beforeWhich, void* what){
    ListAddVertexRight(this, beforeWhich->prev, what);
}

void ListAddVertexBegin(List* this, void* what){
    ListAddVertexRight(this, this->base, what);
}

void ListAddVertexEnd(List* this, void* what){
    ListAddVertexLeft(this, this->base, what);
}

void ListPrintInt(List* this){
    Vertex* it;
    for(it = ListBegin(this); it != ListEnd(this); it = it->next){
        printf("%d ", TO(int)it->value);
    }
    printf("\n");
}

void ListReverse(List* this){
    Vertex* it = ListEnd(this);
    do {
        swap(&(it->prev), &(it->next), sizeof(void*));
        it = it->next;
    }
    while (it != ListEnd(this));
}


int main(void) {
    List* a = ListNew(sizeof(int));
    int N = StringReadInt(stdin, 0, 42);
    int i;
    
    for(i = 0; i < N; i++) {
        int tmp = i + 1;
        ListAddVertexEnd(a, &tmp);
    }
    ListPrintInt(a);
    ListReverse(a);
    ListPrintInt(a);
    ListClear(a);
    
    printf("---\n");
    
    for(i = 0; i < N; i++) {
        int tmp = rand()%42;
        ListAddVertexBegin(a, &tmp);
    }
    ListPrintInt(a);
    ListReverse(a);
    ListPrintInt(a);
    ListDelete(a);
    return 0;
}