//
//  Dijkstra.c
//  Navigator
//
//  Created by Seokhwan Kwon on 2020/12/20.
//  20184646 권석환

#include "Dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


HeapElem PQueue_Dijkstra(GraphType* g, int start, int end)
{
    // [0] 출발지는 found를 TURE로 distance는 0로...
    // 아 그냥 출발지 제외하거 넣는걸로 변경하자.
    
    // [1] 값을 healElem으로 옮겨주자.
    
    // [2] H_Delete를 실행한다 is_empty까지 반복 while문을 활용하자.
        // [3] 현재 상태 출력 (스텝과, 인덱스, 거리를 표시해준다)
        // [4] 방문되지 않은 정점중에서 distance값이 제일 짧은 값 u를 가져온다
                // 이것은 Heap-delete로 구현 가능
        // [5] 꺼내온 경로를 found로 바꾸어준다 // 어차피 heap tree에서 꺼낸 것이니 found는 무의미 하지 않는가?
        // [6] 그다음으로 짧은 경로 w를 가져온다.
        //      [7] w의 거리와 u->w의 거리 중 짧은게 무엇인지 비교한다
        //      [8] u->w가 더 짧은 경우 w의 최소 거리를 갱신해준다.
        //      [9] 다시 insert로 자료를 넣어준다.
    HeapElem u; // 확인된 정점
    HeapElem w; // 도착 정점
    // 전체 노드의 개수만큼 heapElem 생성하고
    
    Heap heap, support_Heap;
    HeapElem ret[g->n];
    Heap_Init(&heap);
    Heap_Init(&support_Heap);
    
    
    
    for(int i = 0; i < g->n; i++) // 초기화
    {
        // start에서 시작하여 가장 짧은길 찾기
        u.vertex = i;
        u.weight = g->weight[start][i];
        u.route.count = 1;
        u.route.edge[0] = i;    // 도착지가 0번지로
        H_Insert_Min(&heap, u);   // [!] i를 나중에 checker로 구현한거 옮기자
    }
    
    while(!H_Is_Empty(&heap))
    {
        u = H_Delete(&heap);
        // distance[u.vertex] = u.weight;
        ret[u.vertex] = u;  // 결정된 값을 넣어준다.
        
        while(!H_Is_Empty(&heap))
        {
            w = H_Delete(&heap);
            if(u.weight + g->weight[u.vertex][w.vertex] < w.weight)
            {
                w.weight = u.weight + g->weight[u.vertex][w.vertex];
                w.route.count = 1;
                for(int i = 0; i < u.route.count; i++)
                    w.route.edge[(w.route.count)++] = u.route.edge[i];
            }
            H_Insert_Min(&support_Heap, w);
        }
        while(!H_Is_Empty(&support_Heap))   // heap에서 u를 제외한 나머지를 복귀시켜준다.
        {
            w = H_Delete(&support_Heap);
            H_Insert_Min(&heap, w);
        }
    }
    
    return ret[end];
}
