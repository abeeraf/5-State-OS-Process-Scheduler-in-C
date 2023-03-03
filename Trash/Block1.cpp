#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <sstream>
#include <string>
#include <iostream>
#include <time.h>
#include "queue.h"
using namespace std;


class queue2
{

public:

	int size;
	int start;
	int end;
	Process *data;

public:
    
	queue2()
	{
		size=50;
		start=end=0;
		data=new Process[size];
	}
 
	queue2(int n)
	{
		size=n;
		start=0;
		data=new Process[size];
	}

	void put(Process value)
	{
		data[start++]=value;
		return;
	}
	//utility function to decrease blockingTime of procs
	void dec()
	{
		for(int i = 0 ;i < start ; i++)
		data[i].blocking_time--;
	}

	void show()
	{
		//for(int i = 0 ; i < start ;  i++)
		// data[i].Display();
	}

	void clear()
	{
		for(int i = 0 ; i < start ; i++)
		{
			if(data[i].number<0||data[i].number>1000)
			remove(i);
		}
	}
	
	//utility function to increase completion time of proc
	void incCompletionTime()
	{
		for(int i = 0 ; i < start ; i++)
		data[i].turnat++;
	}
	
	void remove(int pos)
	{
		for(int j = pos ; j<start ; j++ )
		data[j]=data[j+1];

		start--;
	}
	//utility function to check if  time get zero of proc, it return the index, indicating that now a proc has
	//finished blocking state;
	int dispatch()
	{
		for(int i = 0 ;i < start ; i++)
		{
			if(data[i].blocking_time<=0)
			return i;
		}
		return -1;
	}

	//utility function to increase the waiting time of procs in queue
	void increaseWaitingTime()
	{
		for(int i = 0 ; i < start ; i++)
		data[i].waiting_time++;
	}
  
};

int main(int agc, char *argv[]) 
{

	cout<<"In Blocked Process"<<endl;

	int fd1,fd2;
	srand(time(NULL));
	
	queue2 blocked_Q;
	Process proc;

	istringstream(argv[1])>>fd1;// receive from running
	istringstream(argv[2])>>fd2;// return to ready
	int s = 1;
	Process p3;

	int nread2;
	queue2 printer;
  
while (1) 
{ 
        nread2 = read(fd1, &p3, sizeof(p3)); 
        switch (nread2) 
	{ 
		case -1: 
		if (errno == EAGAIN) 
		{ 
			sleep(1); 
			break; 
		} 
		else
		{ 
			cout<<"Error in block:\n";
			exit(4); 
		} 
		case 0: 
		cout<<"End Of Conversation 1st\n";  
		exit(4); 

		default: 
		if(p3.number>=0)
		{
			srand(time(NULL));
			int b=rand()%10+15;
			p3.blocking_time=b;
			printer.put(p3);
			s =0;
			printer.increaseWaitingTime();
			cout<<"Size of The printer Block Queue "<<printer.start<<endl;
		}
	}
	printer.dec();
	printer.increaseWaitingTime();
	if(s==0)
	{
		cout<<"Got Proc "<<printer.data[printer.start-1].number<<" in printer block"/*<<" With block Time "<<b*/<<endl;
		s=1;
	}
	int d= printer.dispatch();
	if(d!=-1)
	{
		write(fd2,&printer.data[d],sizeof(p3));
                cout<<"Sent Proc "<<printer.data[d].number<<" back to ready queue from printer block state"<<endl;
                printer.remove(d);
	}
}

}
