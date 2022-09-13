#include<bits/stdc++.h>
using namespace std;

#define input_length 5

enum sbhnm {
        process_id = 0,
        come_time,
        run_time,
        priority,
        time_piece
    };

class pross_info  {
    public :

    int pross_info_list[5];
    int remain_time;
    

    pross_info(int * list){
        memcpy(pross_info_list,list,sizeof(int) * 5);
        remain_time = pross_info_list[run_time];
    }

};
int find_min(int x,int y ) {
    if(x <= y) return x;
    else return  y;
}



int comp_fcfs(const void *tempa,const void  *tempb) {
    pross_info* a = (pross_info*)tempa;
    pross_info* b = (pross_info*)tempb;
        if(a->pross_info_list[come_time] < b->pross_info_list[come_time]) {
            return 0;
        }else if(a->pross_info_list[come_time] == b->pross_info_list[come_time]) {
            return  a->pross_info_list[process_id] >  b->pross_info_list[process_id];
        }else {
            return 1;
        }
    }

void fcfs(queue <pross_info> &pross_queue) {
    int sum_time = 0;
    int sum_order  = 1; 
    int size = pross_queue.size();
    // queueSort(pross_queue,comp_fcfs);
    int i = 0;
    pross_info * remapped_queue = (pross_info *)malloc(sizeof(pross_info) * pross_queue.size());
    while(!pross_queue.empty()) {
        pross_info sb = pross_queue.front();
        pross_queue.pop();
        remapped_queue[i++] = sb;
    }
    qsort(remapped_queue,size,sizeof(pross_info),comp_fcfs);

    for(i = 0 ;i < size ;i++) {
        pross_info sb = remapped_queue[i];

        if(sum_time < sb.pross_info_list[come_time]) 
            sum_time = sb.pross_info_list[come_time];
        cout<<sum_order<<'/'<<sb.pross_info_list[process_id]<<'/'<<sum_time<<'/';
        sum_time += sb.pross_info_list[run_time];
        cout<<sum_time<<'/'<<sb.pross_info_list[priority]<<endl;
        sum_order ++;
    }
    
}

void SJF(queue <pross_info> &pross_queue) {
    int sum_time = 0;
    int sum_order  = 1; 
    int size = pross_queue.size();
    // queueSort(pross_queue,comp_fcfs);
    int i = 0;
    pross_info * remapped_queue = (pross_info *)malloc(sizeof(pross_info) * pross_queue.size());
    while(!pross_queue.empty()) {
        pross_info sb = pross_queue.front();
        pross_queue.pop();
        remapped_queue[i++] = sb;
    }
    //先按照到来时间来进行重排列
    qsort(remapped_queue,size,sizeof(pross_info),comp_fcfs);

    for(i = 0 ;i < size ;i++) {
        pross_info sb = remapped_queue[i];
        int pross_to_do = i;
        for( int j = i + 1; j < size ;j++) {
            if(sb.pross_info_list[come_time] <= sum_time && remapped_queue[j].pross_info_list[come_time] <= sum_time) {
                if(sb.pross_info_list[run_time] > remapped_queue[j].pross_info_list[run_time]) {
                    sb = remapped_queue[j];
                    pross_to_do = j;
                }
            }
        } 
        if(i != pross_to_do) {
            for(int j = pross_to_do;j > i;j--) {
                remapped_queue[j] = remapped_queue[j - 1];
            }
        }
        cout<<sum_order<<'/'<<sb.pross_info_list[process_id]<<'/'<<sum_time<<'/';
        sum_time += sb.pross_info_list[run_time];
        cout<<sum_time<<'/'<<sb.pross_info_list[priority]<<endl;
        sum_order ++;
    }
    
}
int comp_with_runtime(const void *tempa,const void *tempb) {
    pross_info* a = (pross_info*)tempa;
    pross_info* b = (pross_info*)tempb;
    if(a->pross_info_list[come_time < b->pross_info_list[come_time]) {
        return 0;
    }else if(a->pross_info_list[come_time] == b->pross_info_list[come_time]) {
        if(a->pross_info_list[run_time] < b->pross_info_list[run_time]) {
            return 0;
        }else if(a->pross_info_list[run_time] == b->pross_info_list[run_time]) {
            return (a->pross_info_list[process_id] > b->pross_info_list[process_id]);
        }else{
            return 1;
        }
        //return  a->pross_info_list[process_id] >  b->pross_info_list[process_id];
    }else {
        return 1;
    }
}
void SJF_RACE(queue <pross_info> &pross_queue) {
    int sum_time          = 0;
    int sum_order         = 1; 
    int size              = pross_queue.size();
    int pross_id_pross    = pross_queue.front().pross_info_list[process_id];
    int remain_time_pross = pross_queue.front().remain_time;
    int come_time_pross   = pross_queue.front().pross_info_list[come_time];
    // // int 
    // // queueSort(pross_queue,comp_fcfs);
    // int i = 0;
    // pross_info * remapped_queue = (pross_info *)malloc(sizeof(pross_info) * pross_queue.size());
    // while(!pross_queue.empty()) {
    //     pross_info sb = pross_queue.front();
    //     pross_queue.pop();
    //     remapped_queue[i++] = sb;
    // }
    // //先按照到来时间来进行重排列
    // qsort(remapped_queue,size,sizeof(pross_info),comp_with_runtime);
    // for(i = 0;i<size;i++) {
    //     pross_queue.push(remapped_queue[i]);
    // }
    while(!pross_queue.empty()) {
        queue <pross_info> pross_temp;
        
        while(!pross_queue.empty()) {
            if(pross_queue.front().pross_info_list[come_time] <= sum_time ){
                if(pross_queue.front().remain_time < remain_time_pross || 
                    (pross_queue.front().remain_time == remain_time_pross && (pross_queue.front().pross_info_list[come_time] < remain_time_pross))) {
                    remain_time_pross = pross_queue.front().remain_time;
                    pross_id_pross = pross_queue.front().pross_info_list[process_id];
                    come_time_pross = pross_queue.front().pross_info_list[come_time];
                }
            }
            pross_temp.push(pross_queue.front());
            pross_queue.pop();
        }
        while(!pross_temp.empty()) {
            // if(pross_temp)
        }
        remain_time_pross--;
        sum_time++;
    }

    // for(i = 0 ;i < size ;i++) {
    //     pross_info sb = remapped_queue[i];
    //     int pross_to_do = i;
    //     for( int j = i + 1; j < size ;j++) {
    //         if(sb.pross_info_list[come_time] <= sum_time && remapped_queue[j].pross_info_list[come_time] <= sum_time) {
    //             if(sb.pross_info_list[run_time] > remapped_queue[j].pross_info_list[run_time]) {
    //                 sb = remapped_queue[j];
    //                 pross_to_do = j;
    //             }
    //         }
    //     } 
    //     if(i != pross_to_do) {
    //         for(int j = pross_to_do;j > i;j--) {
    //             remapped_queue[j] = remapped_queue[j - 1];
    //         }
    //     }
    //     cout<<sum_order<<'/'<<sb.pross_info_list[process_id]<<'/'<<sum_time<<'/';
    //     sum_time += sb.pross_info_list[run_time];
    //     cout<<sum_time<<'/'<<sb.pross_info_list[priority]<<endl;
    //     sum_order ++;
    // }
    

}



int main() {
    freopen("data_base.txt","r",stdin);
    queue <pross_info> pross_queue;
    int choice = 0;
    int process_num = 0;
    cin >> choice;
    int pross_info_list[5];
    while(~scanf("%d/%d/%d/%d/%d",&pross_info_list[process_id],&pross_info_list[come_time],
        &pross_info_list[run_time],&pross_info_list[priority],
        &pross_info_list[time_piece])) {
        pross_info * sb = new pross_info(pross_info_list);
        pross_queue.push(*sb);
        process_num ++;
    }
    switch (choice)
    {
    case 1/* constant-expression */:
        fcfs(pross_queue);
        break;
    case 2 :
        SJF(pross_queue);
        break;
    
    default:
        break;
    }
    
    

    // pross_info * sb = new pross_info;
    // pross_queue.push(*sb);



}




// //归并排序
// void queueSort(queue <pross_info> &pross_queue , int (* F)(pross_info ,pross_info)) {
//     queue <pross_info> temp_queue;
//     int step = 1;
//     int size = pross_queue.size();
//     int remain;
//     int k1,k2,i;
    
//     while(step <= size) { //归并排序
//         remain = size;
//         while(remain > 0) {
//             k1 = find_min(step,remain);
//             for(i = 0; i < k1; i++) {
//                 temp_queue.push(pross_queue.front());
//                 pross_queue.pop();
//             }
//             remain = remain - k1;
//             k2 = find_min(remain,step);
//             remain = remain - k2;
//             while(k1 > 0 && k2 > 0 ) {
//                 if(F(pross_queue.front(),temp_queue.front())) {
//                 // if(pross_queue.front().pross_info_list[num] <= temp_queue.front().pross_info_list[num]) {
//                     pross_queue.push(pross_queue.front());
//                     pross_queue.pop();
//                     k2 --;
//                 }else {
//                     pross_queue.push(temp_queue.front());
//                     temp_queue.pop();
//                     k1 --;
//                 }
//             }
//             while(k2 > 0) {
//                 pross_queue.push(pross_queue.front());
//                 pross_queue.pop();
//                 k2 --;
//             }
//             while(k1 > 0 ){
//                 pross_queue.push(temp_queue.front());
//                 temp_queue.pop();
//                 k1 --;
//             }
//             step = step * 2;
//         }
//     }
// }
