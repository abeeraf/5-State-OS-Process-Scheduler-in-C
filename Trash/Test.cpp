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
int main()
{
	queue newq;
	Process proc;
	proc.number=1332;
	proc.arrival_time=7;
	Process proc2;
	proc2.number=2;
	Process proc3;
	proc3.number=3;
	Process proc4;
	proc4.number=4;
	proc2.arrival_time=1;
	proc3.arrival_time=13;
	proc4.arrival_time=5;
	newq.enqueue(proc);
	newq.enqueue(proc2);
	newq.enqueue(proc3);
	newq.enqueue(proc4);
	
	newq.zeroTracker(2);
	newq.Display();
	newq.dequeue();
	newq.zeroTracker(2);
	newq.Display();
	newq.dequeue();
	newq.zeroTracker(2);
	newq.Display();
	newq.dequeue();
	
}
