// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

# include <stdio.h> 
# include <stdlib.h>
# define MAX 100

int n; //保存进程数量

struct /*定义一个结构体数组，包括进程的信息*/ 
{ 
	int id;             //进程id
	float ArriveTime;   //进程到达时间
	float ServiceTime;  //进程服务时间
	float priority;     //进程优先级
	float StartTime;    //进程开始执行时间
	float EndTime;      //进程结束执行时间
	float RunTime;      //进程周转
	float DQRunTime;    //进程带权周转
	int Status;         //进程状态
}arrayTask[MAX]; /*定义初始化的结构体数组*/ 

void initTask()/*给结构体数组赋值，输入到达，服务时间*/ 
{ 
	//每个进程一行记录，分别保存到达时间，服务时间，优先级
	float task[][3]={{1,10,3},{2,1,1},{3,2,3},{4,1,4},{5,5,2}};
	n=sizeof(task) / sizeof(task[0]);
	for(int i=0;i<n;i++)
	{
		arrayTask[i].id=i+1; 
		arrayTask[i].ArriveTime=task[i][0]; 
		arrayTask[i].ServiceTime=task[i][1]; 
		arrayTask[i].priority=task[i][2];
		arrayTask[i].StartTime=0; 
		arrayTask[i].EndTime=0; 
		arrayTask[i].RunTime=0; 
		arrayTask[i].Status=0; 
	} 
} 

int FCFS() /*定义 FCFS 中寻找未执行的进程的最先到达时间*/ 
{   
	int item=0;  //保存最小到达时间的数组的下标
	float t=0;     //临时保存时间
	/*在结构体数组中找到一个未执行的进程*/  
	for(int i=0;i<n;i++)  
	{  
		if(arrayTask[i].Status==0)  
		{  
			t=arrayTask[i].ArriveTime;
			item=i;
			break;
		}    
	}  
	for(int i=0;i<n;i++) /*查找数组中到达时间最小未执行的进程*/  
	{  
		if(arrayTask[i].ArriveTime<t && arrayTask[i].Status==0)  {
			t=arrayTask[i].ArriveTime;
			item=i;
		}

	} /*返回最小到达时间的数组的下标*/  
	return item;  
}  

int SPF() /*短进程优先*/ 
{ 
	float atime=0;     //临时保存达到时间
	float stime=0;     //临时保存达到时间
	float etime=0;     //临时保存结束时间
	bool fflag=true;    //判断是否是第一次执行
	bool eflag=false;   //判断调度时走FCFS还是SPF
	int item=0;

	for(int i=0;i<n;i++) /*判断是不是第一个执行的进程*/ 
	{ 
		if(arrayTask[i].Status==1) 
		{
			etime=arrayTask[i].EndTime; 
			fflag=false; 
		} 
	}
	if(fflag) /*第一个执行的进程按FCFS*/ 
	{ 
		atime=arrayTask[0].ArriveTime; 
		for(int i=0;i<n;i++) 
		{ 
			if(arrayTask[i].ArriveTime<atime) 
			{ 
				atime=arrayTask[i].ArriveTime; 
				item=i; 
			} 
		} 
		return item;
	} 
	else 
	{ 
		for(int i=0;i<n;i++)   /*找最后一个结束的进程*/ 
		{
			if(arrayTask[i].EndTime>etime) etime=arrayTask[i].EndTime; 
		} 
		for(int i=0;i<n;i++) /*判断在最后一个结束前，是否还有未执行进程*/ 
		{
			if(arrayTask[i].Status==0 && arrayTask[i].ArriveTime<=etime) 
			{
				stime=arrayTask[i].ServiceTime; 
				item=i; 
				eflag=true;
			} 
		} 
		if(eflag) /*有进程到达则按 SPF*/ 
		{
			for(int i=0;i<n;i++) 
			{ 
				if(arrayTask[i].Status==0&&arrayTask[i].ArriveTime<=etime&&arrayTask[i].ServiceTime<stime)  /*判断在最后一个结束前，服务时间最短的进程*/ 
				{
					stime=arrayTask[i].ServiceTime;
					item=i;
				} 
			} 
			return item;
		} 
		else
		{ 
			/*否则按 FCFS*/ 
			for(int i=0;i<n;i++) 
			{
				if(arrayTask[i].Status==0) atime=arrayTask[i].ArriveTime;
			} 
			for(int i=0;i<n;i++) 
			{ 
				if(arrayTask[i].Status==0&&arrayTask[i].ArriveTime<atime) 
				{
					atime=arrayTask[i].ArriveTime; 
					item=i; 
				} 
			} 
			return item;
		} 
	} 
} 


void Fresh(int s) /*定义执行进程后相关数据的修改*/ 
{  
	bool fflag=false;    //判断是否是第一次执行
	float d=0;           //用 d 保存作业结束时间
	for(int i=0;i<n;i++) 
	{ 
		if(arrayTask[i].Status==0) continue; 
		else 
		{ 
			fflag=true; 
			break; 
		} 
	} 
	if(fflag) /*当处理的是第一个未执行的进程时执行*/ 
	{ 
		arrayTask[s].StartTime=arrayTask[s].ArriveTime; 
		arrayTask[s].EndTime=arrayTask[s].ServiceTime+arrayTask[s].ArriveTime; 
		arrayTask[s].RunTime=arrayTask[s].ServiceTime; 
		arrayTask[s].Status=1; 
	} 
	else /*当处理的不是第一个未执行的进程时执行*/ 
	{ 
		arrayTask[s].Status=1; 
		for(int i=0;i<n;i++) 
		{ 
			if(arrayTask[i].Status==1) 
				d=arrayTask[i].EndTime; //用d保存作业结束时间
		} 
		for(int i=0;i<n;i++) /*查找最后执行的进程的完成时间*/ 
		{ 
			if(arrayTask[i].EndTime>d&&arrayTask[i].Status==1) d=arrayTask[i].EndTime; 
		} 
		/*判断修改的进程的到达时间是否在前一个执行的进程的完成时间前面 */
		if(arrayTask[s].ArriveTime<d)  arrayTask[s].StartTime=d; 
		else arrayTask[s].StartTime=arrayTask[s].ArriveTime; 
		arrayTask[s].EndTime=arrayTask[s].StartTime+arrayTask[s].ServiceTime; 
		arrayTask[s].RunTime=arrayTask[s].EndTime-arrayTask[s].ArriveTime; 
	}
	arrayTask[s].DQRunTime=arrayTask[s].RunTime / arrayTask[s].ServiceTime;
} 

void printResult(int j) /*定义打印函数*/ 
{  
	printf("%d\t",arrayTask[j].id); 
	printf("%5.2f\t",arrayTask[j].ArriveTime); 
	printf("%5.2f\t",arrayTask[j].ServiceTime); 
	printf("%5.2f\t",arrayTask[j].StartTime); 
	printf("%5.2f\t",arrayTask[j].EndTime); 
	printf("%5.2f\t",arrayTask[j].RunTime); 
	printf("%5.2f\n",arrayTask[j].DQRunTime); 
}


void main() 
{ 
	int item,q=0;   //代表退出
	int d[MAX];  //保存进程执行顺序
	printf("F. FCFS \n"); 
	printf("S. SFJ \n"); 
	printf("Q. EXIT \n"); 
	for(int i=0;;i++) 
	{
		if(q) break; 
		printf("please choose one: "); 
		switch(getchar())
		{ 
		case 'Q': 
			q=1; 
			break; 
		case 'F':
			initTask();  //进程PBC初始化
			printf("*****************************the result of FCFS*****************************\n"); 
			printf("Number\tArrive\tService\tStart\tFinish\tRun\tDQRuntime\n"); 
			for(int b=0;b<n;b++) /*调用两个函数改变结构体数的值*/ 
			{ 
				item=FCFS(); 
				d[b]=item; 
				Fresh(item);
			} 
			for(int b=0;b<n;b++) 
				printResult(d[b]);/*调用打印函数打出结果*/ 
			break; 
		case 'S': 
			initTask();  //进程PBC初始化
			printf("******************************the result of SPF*****************************\n"); 
			printf("Number\tArrive\tService\tStart\tEnd\tRun\tDQRuntime\n"); 
			for(int b=0;b<n;b++) 
			{ 
				item=SPF(); 
				d[b]=item; 
				Fresh(item); 
			} 
			for(int b=0;b<n;b++)
			{
				printResult(d[b]); 
			}
			break; 
		default:
			printf("Number Error, please input another one!\n"); 
		} 
	} 
} 


