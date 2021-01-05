//
//  heap.h
//  Navigator
//
//  Created by Seokhwan Kwon on 2020/12/20.
//  20184646 권석환

#ifndef heap_h
#define heap_h

#define TRUE 1
#define FALSE 0

#define HEAP_MAX 700

typedef int Priority;       // 우선순위


typedef struct _hData {   // 경로
    int edge[HEAP_MAX];
    int count;
} HData;



// Dijkstra 기준
typedef struct _heapElem {
    Priority weight;
    int vertex;
    HData route;     // [!] checker로 구현한걸 옮기자!! 리스트로 하면 좋을까.?
} HeapElem;


typedef struct _heap {
    int numOfData;
    HeapElem heapArr[HEAP_MAX];
} Heap;

void Heap_Init(Heap* ph);
int H_Is_Empty(Heap* ph);

// void H_Insert_Min(Heap* ph, HData data, Priority weight);
void H_Insert_Min(Heap* ph, HeapElem newElem);
HeapElem H_Delete(Heap* ph);

int Get_Hi_Pri_Child_IDX(Heap* ph, int idx);

#endif /* heap_h */
