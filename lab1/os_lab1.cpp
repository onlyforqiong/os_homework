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

    pross_info(int * list){
        memcpy(pross_info_list,list,sizeof(int) * 5);
    }

};

void fcfs(queue <pross_info> pross_queue) {
    int sum_time = 0;
    int sum_order  = 1; 
    pross_info * remapped_queue = (pross_info *)malloc(sizeof(pross_info) * pross_queue.size());
    while(!pross_queue.empty()) {
        
    }

    // while(!pross_queue.empty()) {
    //     pross_info sb = pross_queue.front();
    //     // pross_queue(2);
    //     pross_queue.pop();
    //     if(sum_time < sb.pross_info_list[come_time]) 
    //         sum_time = sb.pross_info_list[come_time];
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
    
    default:
        break;
    }
    
    

    // pross_info * sb = new pross_info;
    // pross_queue.push(*sb);



}