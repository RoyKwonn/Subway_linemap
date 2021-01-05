//
//  heap.c
//  Navigator
//
//  Created by Seokhwan Kwon on 2020/12/20.
//  20184646 권석환

#include "heap.h"

// 힙의 초기화
void Heap_Init(Heap* ph)
{
    ph->numOfData = 0;
}

// 힙이 비어있는지 확인
int H_Is_Empty(Heap* ph)
{
    if(ph->numOfData == 0)
        return TRUE;
    else
        return FALSE;
}


// 부모 노드의 인덱스 값 반환
int Get_Parent_IDX(int idx)
{
    return idx/2;
}

// 왼쪽 자식 노드의 인덱스 값 반환
int Get_L_Child_IDX(int idx)
{
    return idx*2;
}

// 오른쪽 자식 노드의 인덱스 값 반환
int Get_R_Child_IDX(int idx)
{
    return Get_L_Child_IDX(idx) + 1;
}


// 두 개의 자식 노드 중 높은 우선순위의 자식 노드 인덱스 값 반환
// (수가 낮을수록 높은 우선순위임)
int Get_Hi_Pri_Child_IDX(Heap* ph, int idx)
{
    if(Get_L_Child_IDX(idx) > ph->numOfData) // 자식이 없는 경우
        return 0;
    else if(Get_L_Child_IDX(idx) == ph->numOfData) // 왼쪽자식노드만 있는 경우
        return Get_L_Child_IDX(idx);
    else    // 자식이 두 개인 경우
    {
        if(ph->heapArr[Get_L_Child_IDX(idx)].weight > ph->heapArr[Get_R_Child_IDX(idx)].weight) // 오른쪽의 우선순위가 높은 경우
            return Get_R_Child_IDX(idx);
        else
            return Get_L_Child_IDX(idx);
    }
    
}

// weight가 작을 때 부모노드로 올리는 삽입
// void H_Insert_Min(Heap* ph, HData data, Priority weight)
void H_Insert_Min(Heap* ph, HeapElem newElem)
{
    int idx = ph->numOfData + 1;    // [!] 나중에 ++(ph->numOfData)로 바꾸어주자
    
    
    // 배열의 계산 용이성을 위하여 빼고 1부터 시작한다.
    while(idx != 1) // 루트 노드까지 반복
    {
        // 맨 마지막의 노드와 우선순위를 비교한다.
        if(newElem.weight < (ph->heapArr[Get_Parent_IDX(idx)].weight)) // 부모노드보다 새로 추가하는 데이터의 우선순위가 높은 경우
        {
            // 부모노드 데이터의 위치를 자식노드 위치와 교환한다.
            ph->heapArr[idx] = ph->heapArr[Get_Parent_IDX(idx)];
            idx = Get_Parent_IDX(idx);
        }
        else    // 새로운 노드의 weight값이 제 위치를 찾은 경우
            break;
    }
    
    ph->heapArr[idx] = newElem;
    ph->numOfData += 1;
}

// 힙에서 데이터 삭제
HeapElem H_Delete(Heap* ph)
{
    HeapElem retData = (ph->heapArr[1]);  // 루트노드의 데이터 받아오기
    HeapElem lastElem = ph->heapArr[ph->numOfData]; // 맨마지막 노드를 루트로 올리기위해 선언
    
    int parentIdx = 1;
    int childIdx;
    
    // 루트의 자식들 중에서 높은 우선순위를 가진것을 childIndx로 옮긴다.
    while(childIdx = Get_Hi_Pri_Child_IDX(ph, parentIdx))
    {
        if(lastElem.weight <= ph->heapArr[childIdx].weight) // 맨 마지막 노드와 루트의 자식노드중 높은 우선순위가 무엇인지 확인
            break; // 마지막노드가 루트인 조건과 부합할 경우
        // 자식 노드가 우선순위가 높을경우 옮겨준다.
        ph->heapArr[parentIdx] = ph->heapArr[childIdx];
        parentIdx = childIdx;
    }
    
    ph->heapArr[parentIdx] = lastElem; // 마지막 노드가 제자리를 찾은경우 위치시킨다.
    ph->numOfData -= 1; // 전체 크기를 알기 위하여 -1만큼 줄여준다
    
    return  retData; // 맨처음 받아온 루트노드값을 리턴해준다
}

