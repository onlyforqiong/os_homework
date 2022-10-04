#include<bits/stdc++.h>
#include<iostream>

using namespace std;

#define input_length 5
#define CONTENT_NULL   -1
#define EVER  (;;)
      
class memory_info  {
    public :

    int table_instance ;
    //这玩意到时候会自己螺旋上升
    int last_use_time;
    int come_time;
    memory_info (){
          table_instance  = CONTENT_NULL;
          last_use_time = 0;
          come_time     = 0;
    }

};
int find_min(int x,int y ) {
    if(x <= y) return x;
    else return  y;
}
void show_memory_table_all(memory_info * memory_table_list , int size) {
    int i = 0;
    for(;i<size;i++) {
        if( memory_table_list[i].table_instance == CONTENT_NULL ) {
            cout <<"-";
             cout << ",";
        }else {
            cout << memory_table_list[i].table_instance;
             cout << ",";
        }
        if(i < size -1) {
           
        }
        
    }
   
}
void show_memory_info_all(memory_info * memory_table_list , int size) {
    // int i = 0;
    // cout <<endl;
    // for(;i<size;i++) {
    //    cout <<"instance " << memory_table_list[i].table_instance << "come_time " << memory_table_list[i].come_time << endl;
        
    // }
   
}


void opt_control(int memory_length,queue<int> memory_list) {
    int sum_page_loss = 0;
    memory_info * memory_table_list = (memory_info *)malloc(sizeof(memory_info) * memory_length);
    for(int i = 0; i < memory_length; i++) memory_table_list[i] = *(new memory_info);
    int not_hit_times = 0;
    int sum_time= 0;

    while(!memory_list.empty()) {
        int i = 0;
        int hit_state = 0;
        // cout<<"come to cal "<<endl;
        //看有没有命中
        for(i = 0;i < memory_length;i++) {
            if(memory_table_list[i].table_instance == memory_list.front()) {
                hit_state = 1;
                break;
            }
        }
        // cout <<"fifo size is " << memory_list.size() << endl;
        // cout <<"hit state is " << hit_state <<endl;
        if(hit_state == 1) {
            memory_list.pop();
            show_memory_table_all(memory_table_list,memory_length);
             show_memory_info_all(memory_table_list,memory_length);
            if(memory_list.empty()) {
                // cout <<"sbssbs";
                cout << "1\n";
            }else {
                cout << "1/";
            }
            continue;
        }
        not_hit_times++;
        //没有命中后面的处理
        for(i = 0;i < memory_length;i++) {
            // cout << memory_table_list[i].table_instance << "   instance " << endl;
            if(memory_table_list[i].table_instance == CONTENT_NULL) {
                break;
            }
        }
        if(i < memory_length) {
            // cout << "i = " << i << endl;
            memory_table_list[i].table_instance = memory_list.front();
            memory_table_list[i].come_time      = sum_time;
            memory_list.pop();
            show_memory_table_all(memory_table_list,memory_length);
            if(memory_list.empty()) {
                // cout <<"sbssbs";
                cout << "0\n";
            }else {
                cout << "0/";
            }
            // while(1);
            // assert(0);
        } else {

            int temp_index = 0;
            int next_use_num = -1;
            int next_use_index = -1;
            int next_use_come_time = -1;
            for(;temp_index < memory_length;temp_index++) {
                int temp_instance = memory_table_list[temp_index].table_instance;
                int next_use_counting_num  = 0;
                queue<int> temp_queue = memory_list;
                // cout <<
                while(!temp_queue.empty()) {
                    if(temp_queue.front() == temp_instance) {
                        break;
                    }
                    temp_queue.pop();
                    next_use_counting_num ++;
                }
                if(next_use_counting_num > next_use_num || (next_use_counting_num == next_use_num && next_use_come_time > memory_table_list[temp_index].come_time)) {
                    next_use_index = temp_index;
                    next_use_num   =  next_use_counting_num;
                    next_use_come_time  = memory_table_list[temp_index].come_time;
                }
            }
            memory_table_list[next_use_index].table_instance = memory_list.front();
            memory_table_list[next_use_index].come_time      = sum_time;
            show_memory_table_all(memory_table_list,memory_length);
            if(memory_list.empty()) {
                // cout <<"sbssbs";
                cout << "0\n";
            }else {
                cout << "0/";
            }
            memory_list.pop();
        }
        show_memory_info_all(memory_table_list,memory_length);
        sum_time ++ ;
        // cout << "sum_time: " << sum_time << endl;
    }
    cout << not_hit_times << endl;

}
void fifo_control(int memory_length,queue<int> memory_list) {
     int sum_page_loss = 0;
    memory_info * memory_table_list = (memory_info *)malloc(sizeof(memory_info) * memory_length);
    for(int i = 0; i < memory_length; i++) memory_table_list[i] = *(new memory_info);
    int not_hit_times = 0;
    int sum_time= 0;

    while(!memory_list.empty()) {
        int i = 0;
        int hit_state = 0;
        // cout<<"come to cal "<<endl;
        //看有没有命中
        for(i = 0;i < memory_length;i++) {
            if(memory_table_list[i].table_instance == memory_list.front()) {
                hit_state = 1;
                break;
            }
        }
        // cout <<"fifo size is " << memory_list.size() << endl;
        // cout <<"hit state is " << hit_state <<endl;
        if(hit_state == 1) {
            memory_list.pop();
            show_memory_table_all(memory_table_list,memory_length);
           
            if(memory_list.empty()) {
                cout << "1\n";
            }else {
                cout << "1/";
            }  show_memory_info_all(memory_table_list,memory_length);
            sum_time ++ ;
            continue;
        }
        not_hit_times++;
        //没有命中后面的处理
        for(i = 0;i < memory_length;i++) {
            // cout << memory_table_list[i].table_instance << "   instance " << endl;
            if(memory_table_list[i].table_instance == CONTENT_NULL) {
                break;
            }
        }
        // cout << "i = " << i << endl;
        if(i < memory_length) {
            // cout << "i = " << i << endl;
            memory_table_list[i].table_instance = memory_list.front();
            memory_table_list[i].come_time      = sum_time;
            // cout << "sum_time" << sum_time <<endl;
            memory_list.pop();
            show_memory_table_all(memory_table_list,memory_length);
            if(memory_list.empty()) {
                // cout <<"sbssbs";
                cout << "0\n";
            }else {
                cout << "0/";
            }
            // while(1);
            // assert(0);
        } else {
            // cout <<"sbssbbsb    " << endl;
            int temp_index = 0;
            int next_use_index = 0;
            int next_use_come_time = memory_table_list[0].come_time;
            //  cout << "next use come time : " << next_use_come_time << endl;
            for(;temp_index < memory_length;temp_index++) {
                if( (next_use_come_time > memory_table_list[temp_index].come_time)) {
                    // cout << "next_use_index: " << next_use_index << endl;
                    next_use_index = temp_index;
                    // next_use_num   =  next_use_counting_num;
                    next_use_come_time  = memory_table_list[temp_index].come_time;
                }
            }
            memory_table_list[next_use_index].table_instance = memory_list.front();
            memory_table_list[next_use_index].come_time      = sum_time;
            show_memory_table_all(memory_table_list,memory_length);
            memory_list.pop();
            if(memory_list.empty()) {
                // cout <<"sbssbs";
                cout << "0\n";
            }else {
                cout << "0/";
            }
            
        }
        show_memory_info_all(memory_table_list,memory_length);
        
        sum_time ++ ;
        // cout << "sum_time: " << sum_time << endl;
    }
    // cout << "\n";
    cout << not_hit_times << endl;

}
void lru_control(int memory_length,queue<int> memory_list) {
    int sum_page_loss = 0;
    memory_info * memory_table_list = (memory_info *)malloc(sizeof(memory_info) * memory_length);
    for(int i = 0; i < memory_length; i++) memory_table_list[i] = *(new memory_info);
    int not_hit_times = 0;
    int sum_time= 0;

    while(!memory_list.empty()) {
        int i = 0;
        int hit_state = 0;
        // cout<<"come to cal "<<endl;
        //看有没有命中
        for(i = 0;i < memory_length;i++) {
            if(memory_table_list[i].table_instance == memory_list.front()) {
                hit_state = 1;
                memory_table_list[i].last_use_time = sum_time;
                break;
            }
        }
        // cout <<"fifo size is " << memory_list.size() << endl;
        // cout <<"hit state is " << hit_state <<endl;
        if(hit_state == 1) {
            memory_list.pop();
            show_memory_table_all(memory_table_list,memory_length);
           
            if(memory_list.empty()) {
                cout << "1\n";
            }else {
                cout << "1/";
            }  show_memory_info_all(memory_table_list,memory_length);
            
            sum_time ++ ;
            continue;
        }
        not_hit_times++;
        //没有命中后面的处理
        for(i = 0;i < memory_length;i++) {
            // cout << memory_table_list[i].table_instance << "   instance " << endl;
            if(memory_table_list[i].table_instance == CONTENT_NULL) {
                break;
            }
        }
        // cout << "i = " << i << endl;
        if(i < memory_length) {
            // cout << "i = " << i << endl;
            memory_table_list[i].table_instance = memory_list.front();
            memory_table_list[i].come_time      = sum_time;
            memory_table_list[i].last_use_time = sum_time;
            // cout << "sum_time" << sum_time <<endl;
            memory_list.pop();
            show_memory_table_all(memory_table_list,memory_length);
            if(memory_list.empty()) {
                // cout <<"sbssbs";
                cout << "0\n";
            }else {
                cout << "0/";
            }
            // while(1);
            // assert(0);
        } else {
            // cout <<"sbssbbsb    " << endl;
            int temp_index = 0;
            int next_use_index = 0;
            int next_use_come_time = memory_table_list[0].come_time;
            int next_use_last_use_time = memory_table_list[0].last_use_time;
            //  cout << "next use come time : " << next_use_come_time << endl;
            for(;temp_index < memory_length;temp_index++) {
                if( (next_use_last_use_time > memory_table_list[temp_index].last_use_time) ) {
                    next_use_index = temp_index;
                    // next_use_num   =  next_use_counting_num;
                    next_use_come_time  = memory_table_list[temp_index].come_time;
                    next_use_last_use_time = memory_table_list[temp_index].last_use_time;
                }
            }
            memory_table_list[next_use_index].table_instance = memory_list.front();
            memory_table_list[next_use_index].come_time      = sum_time;
            memory_table_list[next_use_index].last_use_time  = sum_time;
            show_memory_table_all(memory_table_list,memory_length);
            memory_list.pop();
            if(memory_list.empty()) {
                // cout <<"sbssbs";
                cout << "0\n";
            }else {
                cout << "0/";
            }
            
        }
        show_memory_info_all(memory_table_list,memory_length);
        
        sum_time ++ ;
        // cout << "sum_time: " << sum_time << endl;
    }
    // cout << "\n";
    cout << not_hit_times << endl;

}


int main() {
    // freopen("osout.txt", "w", stdout); 
    // freopen("data_base.txt","r",stdin);
    queue <int> memory_list;
    int choice = 0;
    int memory_num = 0;
    cin >> choice;
    cin >> memory_num;
    int data = 0;
    char c = 0;

    // int i = 0;
    while (~scanf("%d", &data))//输入页面序列 
	{
        // cout << "data = " << data << endl;
        memory_list.push(data);
		c = getchar();
		if (c == '\n')//遇到换行符则输入结束 
		{
			break;
		}
		else if (c == ',')//遇到逗号则继续读取 
		{
			continue;
		}
	}

    switch (choice)
    {
    case 1/* constant-expression */:
        opt_control(memory_num,memory_list);
        break;
    case 2 :
        fifo_control(memory_num,memory_list);
        break;
    case 3 :
        lru_control(memory_num,memory_list);
    default:
        break;
    }

}




