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

int main(int agc, char *argv[]) 
{

	cout<<"In Blocked Process"<<endl;

	int fd1,fd2;
	srand(time(NULL));
	
	queue blocked_Q;
	Process proc;

	istringstream(argv[1])>>fd1;// receive from running
	istringstream(argv[2])>>fd2;// return to ready

	while(1)
	{	
		while(read( fd1 , &proc , sizeof(proc) )>0)// enqueuing processes if in the pipe
		{	
			proc.blocking_time=1;//15+rand()%11; 
			blocked_Q.enqueue(proc);
			cout<<"Blocked: Process "<<proc.number<<" is in blocked queue"<<endl;			
		}
		if(!blocked_Q.isEmpty())
		{
			sleep(1);
			
			blocked_Q.add_turn_time(proc.blocking_time);//add to turn around time
			//search for zero blocking time and dequeue it
			//send it to ready queue again
			blocked_Q.decrease_blocking_time();//decrement all blocking times in the queue
			if(blocked_Q.zeroTracker(3));// for zero waiting time to the front
			{	
				Process proc_to_send=blocked_Q.dequeue();
				cout<<"Blocked: Sending process "<<proc_to_send.number<<" back to Running."<<endl;
				cout<<"Blocked: Its Blocking Time is now "<<proc_to_send.blocking_time<<endl;
				write( fd2 , &proc_to_send, sizeof(proc_to_send) );
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

int main(int agc, char *argv[]) 
{

	cout<<"In Blocked Process"<<endl;

	int fd1,fd2;
	srand(time(NULL));
	
	queue blocked_Q;
	Process proc;
	
	int err_read;

	istringstream(argv[1])>>fd1;// receive from running
	istringstream(argv[2])>>fd2;// return to ready

	while(1)
	{	err_read=read( fd1 , &proc , sizeof(proc));
		switch (err_read) 
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
			} 
			case 0: 
			cout<<"End Of Conversation 1st\n";  
			default: 
			if(proc.number>=0)
			{
				proc.blocking_time=5;//15+rand()%11; 
				blocked_Q.enqueue(proc);
				cout<<"Blocked: Process "<<proc.number<<" is in blocked queue"<<endl;
			}
		}
		blocked_Q.add_turn_time(1);//add to turn around time
		//search for zero blocking time and dequeue it
		//send it to ready queue again
		blocked_Q.decrease_blocking_time(1);//decrement all blocking times in the queue
		if(!blocked_Q.isEmpty())
		{
			
			
			if(blocked_Q.zeroTracker(3));// for zero waiting time to the front
			{	
				Process proc_to_send=blocked_Q.dequeue();
				cout<<"Blocked: Sending process "<<proc_to_send.number<<" back to Running."<<endl;
				cout<<"Blocked: Its Blocking Time is now "<<proc_to_send.blocking_time<<endl;
				write( fd2 , &proc_to_send, sizeof(proc_to_send) );
			}
		}
	}
}
















