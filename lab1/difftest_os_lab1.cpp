#include<iostream>
#include<cstdlib> 
#include<cstdio> 
#include<cmath> 
#include<algorithm> 
#include<queue>
using namespace std;
struct process
{
	int pid;//进程号 
	int comeTime;//到达时间 
	int runTime;//运行所需时间 
	int beginTime;//开始运行的时间 
	int endTime;//结束运行的时间 
	int order;//调度顺序 
	int priority;//优先级 
	int slot;//时间片 
	int finish;//结束标志 
}que[1010];
void FCFS();//先来先服务 
void SJF();//不可剥夺的短作业优先算法 
void SRTF();//可剥夺式的短作业优先算法 
void RR();//时间片轮转 
void DPSA();//动态优先级 
bool cmp1(process, process);//FCFS、RR、DPSA 
bool cmp2(process, process);//SJF、SRTF 
int num;//输入的总进程数 
const int IsEnd = 1;//进程已经结束 
const int NoEnd = 0;//进程还未结束 
int main()
{
	// //freopen("osin.txt", "r", stdin); 
	freopen("diff_osout.txt", "w", stdout); 
    freopen("data_base.txt","r",stdin);
	int sig = 0;
	cin >> sig;   //算法选择标志 

	 //读入数据 
	num = 0;
	while (~scanf("%d/%d/%d/%d/%d", &que[num].pid, &que[num].comeTime, &que[num].runTime, &que[num].priority, &que[num].slot))
	{
		que[num].beginTime = que[num].endTime = que[num].order = 0;
		que[num].finish = NoEnd;
		num++;
	}

	//选择算法 
	switch (sig)
	{
		case 1:FCFS(); break;
		case 2:SJF(); break;
		case 3:SRTF(); break;
		case 4:RR(); break;
		case 5:DPSA(); break;
	}
	return 0;
}
void FCFS()
{
	sort(que, que + num, cmp1);//先来后到排好序 
	for (int i = 0; i < num; i++)
	{
		que[i].order = i + 1;
		if (i == 0)//第一个进程特判一下 
		{
			que[i].beginTime = que[i].comeTime;
		}
		else
		{
			que[i].beginTime = max(que[i].comeTime, que[i - 1].endTime);
		}
		que[i].endTime = que[i].beginTime + que[i].runTime;

		//输出 
		printf("%d/%d/%d/%d/%d\n", que[i].order, que[i].pid, que[i].beginTime, que[i].endTime, que[i].priority);
	}
}
void SJF()
{
	sort(que, que + num, cmp2);
	int lastTime = que[0].comeTime;//当前时间 
	int tmp = 0;//每次选中的短作业 
	for (int i = 0; i < num; i++)//筛选num次，每次选出最佳的短作业 
	{
		bool isBool = false;//判断当前时间是否有短作业在就绪队列中 
		while (1)
		{
			if (i == 0)
			{
				//排序后的第一个肯定满足条件，特判 
				break;
			}
			else
			{
				for (int j = 1; j < num; j++)//for一遍的复杂度为O(n),比排序O(nlogn)快 
				{
					if (que[j].finish == IsEnd)//当前短作业已经结束就跳过 
						continue;
					if (que[j].comeTime <= lastTime)//当前短作业在就绪队列中 
					{
						if (isBool == false)//没有标记最优短作业 
						{
							isBool = true;
							tmp = j;
						}
						else//已经标记了最优短作业 
						{
							//比较，更新最优短作业 
							 //当短作业运行时间相等时，优先调度进程号小的短作业执行 
							if (que[j].runTime < que[tmp].runTime)
								tmp = j;
							else if (que[j].runTime == que[tmp].runTime&&que[j].pid < que[tmp].pid)
								tmp = j;
						}
					}
				}
				if (isBool)//如果存在短进程满足条件就输出 
					break;
				else//不存在就把时间后移再寻找 
					lastTime++;
			}
		}
		que[tmp].order = i + 1;
		que[tmp].beginTime = max(que[tmp].beginTime, lastTime);
		que[tmp].endTime = que[tmp].beginTime + que[tmp].runTime;
		printf("%d/%d/%d/%d/%d\n", que[tmp].order, que[tmp].pid, que[tmp].beginTime, que[tmp].endTime, que[tmp].priority);

		lastTime = que[tmp].endTime;//更新当前时间 
		que[tmp].finish = IsEnd;//标记短作业结束 
	}
}
void SRTF()
{
	sort(que, que + num, cmp2);
	int lastTime = que[0].comeTime;
	int ID = 1;//输出顺序 
	int tmp = 0, counts = 0;//当前进程，输出次数 
	int isRun = -1, start = 0;//当前是否有进程运行,运行开始时间 
	while (counts < num)
	{
		while (que[tmp].comeTime <= lastTime && tmp < num)//当前时间内的进程 
		{
			tmp++;
		}
		int minx = 0x3f3f3f, minId = -1;//最短时间和下标 
		for (int i = 0; i < tmp; i++)//寻找当前进程中剩余运行时间最短的进程 
		{
			if (que[i].runTime < minx && que[i].finish == NoEnd)
			{
				minx = que[i].runTime;
				minId = i;
			}
		}
		if (minId == -1)//如果当前时间进程都结束了就等待下一个进程 
		{
			lastTime = que[tmp].comeTime;
			continue;
		}
		if (isRun == -1)//当前没有进程在运行 
		{
			isRun = minId;
			start = max(que[isRun].comeTime, lastTime);//运行刚找到的进程 
		}
		//如果找到进程的剩余运行时间小于当前进程的剩余运行时间 
		if (que[minId].runTime < que[isRun].runTime)
		{
			que[isRun].order = ID++;
			que[isRun].beginTime = start;
			que[isRun].endTime = lastTime;
			printf("%d/%d/%d/%d/%d\n", que[isRun].order, que[isRun].pid, que[isRun].beginTime, que[isRun].endTime, que[isRun].priority);
			isRun = minId;
			start = lastTime;
		}
		//运行进程 
		int run = que[tmp].comeTime - lastTime;
		//进程能运行完就运行完 
		if (run >= que[isRun].runTime || run <= 0)
		{
			lastTime += que[isRun].runTime;
			que[isRun].order = ID++;
			que[isRun].beginTime = start;
			que[isRun].endTime = lastTime;
			printf("%d/%d/%d/%d/%d\n", que[isRun].order, que[isRun].pid, que[isRun].beginTime, que[isRun].endTime, que[isRun].priority);

			que[isRun].runTime = 0;
			que[isRun].finish = IsEnd;
			counts++;
			isRun = -1;
			start = lastTime;
		}
		//进程不能运行完就运行一个时间片 
		else
		{
			lastTime += run;
			que[isRun].runTime -= run;
		}
	}
}
void RR()
{
	sort(que, que + num, cmp1);
	queue<process>q;//就绪队列 
	int lastTime = 0;//当前时间 
	int ID = 1;//输出顺序 
	int tmp = 0, counts = 0;//当前进程，输出次数 
	while (counts < num)
	{
		if (q.empty())//队列为空则等待进程到来 
		{
			lastTime = que[tmp].comeTime;
			while (que[tmp].comeTime <= lastTime && tmp < num)//当前时间内的进程 
			{
				if (que[tmp].finish == NoEnd)//还没完成的进程入队 
				{
					q.push(que[tmp]);
				}
				tmp++;
			}
		}
		else
		{
			process ans = q.front();//取出处于队列头的进程 
			q.pop();
			//进程可以运行完 
			if (ans.runTime <= ans.slot)
			{
				//输出当前进程调度 
				ans.order = ID++;
				ans.beginTime = lastTime;
				ans.endTime = ans.beginTime + ans.runTime;
				printf("%d/%d/%d/%d/%d\n", ans.order, ans.pid, ans.beginTime, ans.endTime, ans.priority);

				lastTime = ans.endTime;//更新当前时间 
				ans.finish = IsEnd;//标记短作业结束 
				counts++;

				while (que[tmp].comeTime <= lastTime && tmp < num)//当前时间内的进程 
				{
					if (que[tmp].finish == NoEnd)//还没完成的进程入队 
					{
						q.push(que[tmp]);
					}
					tmp++;
				}
			}
			//进程不能运行完 
			else
			{
				//输出当前进程调度 
				ans.order = ID++;
				ans.beginTime = lastTime;
				ans.endTime = ans.beginTime + ans.slot;
				printf("%d/%d/%d/%d/%d\n", ans.order, ans.pid, ans.beginTime, ans.endTime, ans.priority);

				lastTime = ans.endTime;
				ans.runTime -= ans.slot;

				while (que[tmp].comeTime <= lastTime && tmp < num)//当前时间内的进程 
				{
					if (que[tmp].finish == NoEnd)//还没完成的进程入队 
					{
						q.push(que[tmp]);
					}
					tmp++;
				}
				q.push(ans);//先让新进程入队再让当前进程入队 
			}
		}
	}
}
void DPSA()
{
	sort(que, que + num, cmp1);
	int lastTime = que[0].comeTime;//当前时间 
	int ID = 1;//输出顺序 
	int tmp = 0, counts = 0;//当前进程，输出次数 
	int start = lastTime;//当前进程开始时间 
	int minId, Smin;
	while (counts < num)
	{
		while (que[tmp].comeTime <= lastTime && tmp < num)//当前时间内的进程 
		{
			if (que[tmp].comeTime > start && que[tmp].comeTime < lastTime)
			{
				que[tmp].priority = max(que[tmp].priority - 1, 0);//等待时优先级加1 
			}
			tmp++;
		}
		//寻找最高优先级进程 
		minId = -1;
		Smin = 0x3f3f3f;
		for (int i = 0; i < tmp; i++)
		{
			if (que[i].priority < Smin && que[i].finish == NoEnd)
			{
				Smin = que[i].priority;
				minId = i;
			}
		}
		if (minId == -1)//如果当前时间进程都结束了就等待下一个进程 
		{
			lastTime = que[tmp].comeTime;
			continue;
		}
		//运行进程 
		start = lastTime;
		//进程能运行完 
		if (que[minId].runTime <= que[minId].slot)
		{
			que[minId].order = ID++;
			que[minId].beginTime = lastTime;
			que[minId].endTime = lastTime + que[minId].runTime;
			printf("%d/%d/%d/%d/%d\n", que[minId].order, que[minId].pid, que[minId].beginTime, que[minId].endTime, que[minId].priority + 3);

			counts++;
			lastTime += que[minId].runTime;
			que[minId].finish = IsEnd;
		}
		//进程不能运行完 
		else
		{
			que[minId].order = ID++;
			que[minId].beginTime = lastTime;
			que[minId].endTime = lastTime + que[minId].slot;
			printf("%d/%d/%d/%d/%d\n", que[minId].order, que[minId].pid, que[minId].beginTime, que[minId].endTime, que[minId].priority + 3);

			lastTime += que[minId].slot;
			que[minId].runTime -= que[minId].slot;
		}
		//改变进程优先级 
		for (int i = 0; i < tmp; i++)
		{
			if (que[i].finish == NoEnd)
			{
				if (i == minId)//运行优先级减3 
				{
					que[i].priority += 3;
				}
				else//等待优先级加1 
				{
					que[i].priority = max(que[i].priority - 1, 0);
				}
			}
		}
	}
}
bool cmp1(process a, process b)
{
	if (a.comeTime != b.comeTime)
		return a.comeTime < b.comeTime;
	else
		return a.pid < b.pid;
}
bool cmp2(process a, process b)
{
	if (a.comeTime != b.comeTime)
		return a.comeTime < b.comeTime;
	else if (a.runTime != b.runTime)
		return a.runTime > b.runTime;
	else
		return a.pid < b.pid;
}
