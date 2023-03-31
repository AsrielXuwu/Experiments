// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

# include <stdio.h> 
# include <stdlib.h>
# define MAX 100

int n; //�����������

struct /*����һ���ṹ�����飬�������̵���Ϣ*/ 
{ 
	int id;             //����id
	float ArriveTime;   //���̵���ʱ��
	float ServiceTime;  //���̷���ʱ��
	float priority;     //�������ȼ�
	float StartTime;    //���̿�ʼִ��ʱ��
	float EndTime;      //���̽���ִ��ʱ��
	float RunTime;      //������ת
	float DQRunTime;    //���̴�Ȩ��ת
	int Status;         //����״̬
}arrayTask[MAX]; /*�����ʼ���Ľṹ������*/ 

void initTask()/*���ṹ�����鸳ֵ�����뵽�����ʱ��*/ 
{ 
	//ÿ������һ�м�¼���ֱ𱣴浽��ʱ�䣬����ʱ�䣬���ȼ�
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

int FCFS() /*���� FCFS ��Ѱ��δִ�еĽ��̵����ȵ���ʱ��*/ 
{   
	int item=0;  //������С����ʱ���������±�
	float t=0;     //��ʱ����ʱ��
	/*�ڽṹ���������ҵ�һ��δִ�еĽ���*/  
	for(int i=0;i<n;i++)  
	{  
		if(arrayTask[i].Status==0)  
		{  
			t=arrayTask[i].ArriveTime;
			item=i;
			break;
		}    
	}  
	for(int i=0;i<n;i++) /*���������е���ʱ����Сδִ�еĽ���*/  
	{  
		if(arrayTask[i].ArriveTime<t && arrayTask[i].Status==0)  {
			t=arrayTask[i].ArriveTime;
			item=i;
		}

	} /*������С����ʱ���������±�*/  
	return item;  
}  

int SPF() /*�̽�������*/ 
{ 
	float atime=0;     //��ʱ����ﵽʱ��
	float stime=0;     //��ʱ����ﵽʱ��
	float etime=0;     //��ʱ�������ʱ��
	bool fflag=true;    //�ж��Ƿ��ǵ�һ��ִ��
	bool eflag=false;   //�жϵ���ʱ��FCFS����SPF
	int item=0;

	for(int i=0;i<n;i++) /*�ж��ǲ��ǵ�һ��ִ�еĽ���*/ 
	{ 
		if(arrayTask[i].Status==1) 
		{
			etime=arrayTask[i].EndTime; 
			fflag=false; 
		} 
	}
	if(fflag) /*��һ��ִ�еĽ��̰�FCFS*/ 
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
		for(int i=0;i<n;i++)   /*�����һ�������Ľ���*/ 
		{
			if(arrayTask[i].EndTime>etime) etime=arrayTask[i].EndTime; 
		} 
		for(int i=0;i<n;i++) /*�ж������һ������ǰ���Ƿ���δִ�н���*/ 
		{
			if(arrayTask[i].Status==0 && arrayTask[i].ArriveTime<=etime) 
			{
				stime=arrayTask[i].ServiceTime; 
				item=i; 
				eflag=true;
			} 
		} 
		if(eflag) /*�н��̵����� SPF*/ 
		{
			for(int i=0;i<n;i++) 
			{ 
				if(arrayTask[i].Status==0&&arrayTask[i].ArriveTime<=etime&&arrayTask[i].ServiceTime<stime)  /*�ж������һ������ǰ������ʱ����̵Ľ���*/ 
				{
					stime=arrayTask[i].ServiceTime;
					item=i;
				} 
			} 
			return item;
		} 
		else
		{ 
			/*���� FCFS*/ 
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


void Fresh(int s) /*����ִ�н��̺�������ݵ��޸�*/ 
{  
	bool fflag=false;    //�ж��Ƿ��ǵ�һ��ִ��
	float d=0;           //�� d ������ҵ����ʱ��
	for(int i=0;i<n;i++) 
	{ 
		if(arrayTask[i].Status==0) continue; 
		else 
		{ 
			fflag=true; 
			break; 
		} 
	} 
	if(fflag) /*��������ǵ�һ��δִ�еĽ���ʱִ��*/ 
	{ 
		arrayTask[s].StartTime=arrayTask[s].ArriveTime; 
		arrayTask[s].EndTime=arrayTask[s].ServiceTime+arrayTask[s].ArriveTime; 
		arrayTask[s].RunTime=arrayTask[s].ServiceTime; 
		arrayTask[s].Status=1; 
	} 
	else /*������Ĳ��ǵ�һ��δִ�еĽ���ʱִ��*/ 
	{ 
		arrayTask[s].Status=1; 
		for(int i=0;i<n;i++) 
		{ 
			if(arrayTask[i].Status==1) 
				d=arrayTask[i].EndTime; //��d������ҵ����ʱ��
		} 
		for(int i=0;i<n;i++) /*�������ִ�еĽ��̵����ʱ��*/ 
		{ 
			if(arrayTask[i].EndTime>d&&arrayTask[i].Status==1) d=arrayTask[i].EndTime; 
		} 
		/*�ж��޸ĵĽ��̵ĵ���ʱ���Ƿ���ǰһ��ִ�еĽ��̵����ʱ��ǰ�� */
		if(arrayTask[s].ArriveTime<d)  arrayTask[s].StartTime=d; 
		else arrayTask[s].StartTime=arrayTask[s].ArriveTime; 
		arrayTask[s].EndTime=arrayTask[s].StartTime+arrayTask[s].ServiceTime; 
		arrayTask[s].RunTime=arrayTask[s].EndTime-arrayTask[s].ArriveTime; 
	}
	arrayTask[s].DQRunTime=arrayTask[s].RunTime / arrayTask[s].ServiceTime;
} 

void printResult(int j) /*�����ӡ����*/ 
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
	int item,q=0;   //�����˳�
	int d[MAX];  //�������ִ��˳��
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
			initTask();  //����PBC��ʼ��
			printf("*****************************the result of FCFS*****************************\n"); 
			printf("Number\tArrive\tService\tStart\tFinish\tRun\tDQRuntime\n"); 
			for(int b=0;b<n;b++) /*�������������ı�ṹ������ֵ*/ 
			{ 
				item=FCFS(); 
				d[b]=item; 
				Fresh(item);
			} 
			for(int b=0;b<n;b++) 
				printResult(d[b]);/*���ô�ӡ����������*/ 
			break; 
		case 'S': 
			initTask();  //����PBC��ʼ��
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


