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

void SJF_RACE(queue <pross_info> &pross_queue) {
    int sum_time          = 0;
    int sum_order         = 1; 
    int counter           = 0;
    int now_index         = 0;
    int size              = pross_queue.size();
    //1pross_queue.front().pross_info_list[come_time];
    int i = 0;
    int sum_order_has_changed_switch = 0;
    int sum_order_has_changed_end = 0;
    int index_has_change = 0;

    pross_info * remapped_queue = (pross_info *)malloc(sizeof(pross_info) * pross_queue.size());
    while(!pross_queue.empty()) {
        pross_info sb = pross_queue.front();
        pross_queue.pop();
        remapped_queue[i++] = sb;
    }
    qsort(remapped_queue,size,sizeof(pross_info),comp_fcfs);
    int pross_id_pross    = remapped_queue[0].pross_info_list[process_id];//pross_queue.front().pross_info_list[process_id];
    int remain_time_pross = remapped_queue[0].remain_time;//pross_queue.front().remain_time;
    int come_time_pross   = remapped_queue[0].pross_info_list[come_time];
    int index_to_be = now_index;
    sum_time = remapped_queue[0].pross_info_list[come_time];
    int temp_index = 0;
    for(;temp_index < size;temp_index++) {
        if(remapped_queue[temp_index].pross_info_list[come_time] == come_time_pross && remapped_queue[temp_index].remain_time < remain_time_pross) {
            index_to_be = temp_index;
            pross_id_pross    = remapped_queue[index_to_be].pross_info_list[process_id];//pross_queue.front().pross_info_list[process_id];
            remain_time_pross = remapped_queue[index_to_be].remain_time;//pross_queue.front().remain_time;
            come_time_pross   = remapped_queue[index_to_be].pross_info_list[come_time];
    // int index_to_be = now_index;

        }
    }
    now_index = index_to_be;
    int counter_counter = 0;
    while(counter < size) {
        int temp_index = 0;
        // cout << "before index_to_be: " << index_to_be << endl;
        // cout << "counter_counter " << counter_counter++<<endl;
        for(;temp_index < size;temp_index++) {
            if(remapped_queue[temp_index].pross_info_list[come_time] <= sum_time && remapped_queue[temp_index].remain_time != 0 &&
                (now_index == -1 || (remapped_queue[temp_index].remain_time < remapped_queue[index_to_be].remain_time || 
                (remapped_queue[temp_index].remain_time == remapped_queue[index_to_be].remain_time  && 
                temp_index < index_to_be )))) {
                
                    index_has_change = 1;
                 
                    index_to_be = temp_index;

                    sum_order_has_changed_switch = 1;
                    // cout<<"now index = "<<now_index<<endl;
                }
        
        }
        //  cout << "after index_to_be: " << index_to_be << endl;
        if(index_has_change == 1) {
            // cout << "here"<<endl;
            if(now_index != -1  && !sum_order_has_changed_end) {
                cout << sum_order<<"/" << remapped_queue[now_index].pross_info_list[process_id] << "/";
                cout << come_time_pross << '/' << sum_time << '/' << remapped_queue[now_index].pross_info_list[priority] <<endl;
                sum_order++;     
            }
            come_time_pross = sum_time;
            now_index = index_to_be;
        }
        index_has_change = 0;
        sum_order_has_changed_end = 0;
        // cout << "now_index = "<<now_index<<"   remain_time = " << remapped_queue[now_index].remain_time <<endl;
        if(now_index >= 0 && now_index <size) {
            remapped_queue[now_index].remain_time -- ;
        }
        sum_time ++;
        // cout << "sum time = " <<sum_time <<endl;
        // for(int print_i = 0; print_i < size; print_i++) {
        //     cout <<"    remain time = " <<remapped_queue[print_i].remain_time << "  pross id = " << remapped_queue[print_i].pross_info_list[process_id] <<endl;
        // }
        
        // cout << now_index << "   now_index "<< sum_time<<" sum_time"<<endl;
        // cout << "pross_id = "<<remapped_queue[now_index].pross_info_list[process_id]<<
        //     " remain_time = "<<remapped_queue[now_index].remain_time;
        if(now_index >= 0 &&remapped_queue[now_index].remain_time == 0 ) {
            // cout << "now index = "<<now_index<<endl;
            counter ++;
            int tempi = 0;
            while(remapped_queue[tempi].remain_time == 0  || remapped_queue[tempi].pross_info_list[come_time] > sum_time) {
                tempi++;
                if(tempi >= size) {
                    break;
                }
            } 
            // cout <<"now index  " <<now_index <<endl;

            // if(sum_order_has_changed_switch == 0 ) {
            cout << sum_order<<"/" << remapped_queue[now_index].pross_info_list[process_id] << "/";
            cout << come_time_pross << '/' << sum_time << '/' << remapped_queue[now_index].pross_info_list[priority] <<endl;
            sum_order++;
                       
            come_time_pross = sum_time;
            sum_order_has_changed_end = 1;
            // }
            if(tempi < size) {
                now_index = tempi;
                index_to_be = tempi;
            }else {
                now_index = -1;
            }
            // cout << "change index = " << now_index<<endl;
            
        }
    }

}

void time_piece_control(queue <pross_info> &pross_queue) {
    int sum_time          = 0;
    int sum_order         = 1; 
    int counter           = 0;
    int now_index         = 0;
    int size              = pross_queue.size();
    int start_run_time          = 0;
    queue <pross_info> prepare_queue;
    //1pross_queue.front().pross_info_list[come_time];
    int i = 0;
    int pross_id_pross    = 0;
    int remain_time_pross = 0;
    int come_time_pross   = 0;
    pross_info * remapped_queue = (pross_info *)malloc(sizeof(pross_info) * pross_queue.size());
    while(!pross_queue.empty()) {
        pross_info sb = pross_queue.front();
        pross_queue.pop();
        remapped_queue[i++] = sb;
    }

    qsort(remapped_queue,size,sizeof(pross_info),comp_fcfs);
    //  cout << "sum time = " <<sum_time <<endl;
    // for(int print_i = 0; print_i < size; print_i++) {
    //     cout <<"    come  time = " <<remapped_queue[print_i].pross_info_list[come_time] << "  pross id = " << remapped_queue[print_i].pross_info_list[process_id] <<endl;
    // }
    start_run_time = remapped_queue[0].pross_info_list[come_time];
    for(i = 0; i< size; i++) {
       prepare_queue.push(remapped_queue[i]);
    }
    while( !prepare_queue.empty()&& prepare_queue.front().pross_info_list[come_time] <= sum_time) {
        pross_queue.push(prepare_queue.front());
        prepare_queue.pop();
    }

    while(!(pross_queue.empty() && prepare_queue.empty()) ) {
        if(!pross_queue.empty()) {
            // cout << "sbsbs"<<endl;
            if( pross_queue.front().remain_time <= pross_queue.front().pross_info_list[time_piece]) {

                cout << sum_order<<"/" << pross_queue.front().pross_info_list[process_id] << "/";
                cout << sum_time << '/' << (sum_time + pross_queue.front().remain_time) << '/' << pross_queue.front().pross_info_list[priority] <<endl;
                sum_time += pross_queue.front().remain_time ;
                pross_queue.front().remain_time = 0;

            }else {
                pross_queue.front().remain_time = pross_queue.front().remain_time - pross_queue.front().pross_info_list[time_piece];
                cout << sum_order<<"/" << pross_queue.front().pross_info_list[process_id] << "/";
                cout << sum_time << '/' << ( sum_time + pross_queue.front().pross_info_list[time_piece] ) << '/' << pross_queue.front().pross_info_list[priority] <<endl;
                sum_time += pross_queue.front().pross_info_list[time_piece];
            }   
            sum_order++ ; 
            while( !prepare_queue.empty()&& prepare_queue.front().pross_info_list[come_time] <= sum_time) {
                pross_queue.push(prepare_queue.front());
                prepare_queue.pop();
            }
            pross_info sb = pross_queue.front();
            pross_queue.pop(); 
            if(sb.remain_time > 0) {
               
                pross_queue.push(sb);
            }
        }else{
            sum_time ++;
            while( !prepare_queue.empty()&& prepare_queue.front().pross_info_list[come_time] <= sum_time) {
                pross_queue.push(prepare_queue.front());
                prepare_queue.pop();
            }
        }
        

    }
}


int main() {
    // freopen("data_base.txt","r",stdin);
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
    case 3 :
        SJF_RACE(pross_queue);
    case 4:
        time_piece_control(pross_queue);
    default:
        break;
    }

}




