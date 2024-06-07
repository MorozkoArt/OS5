struct statusProc {
	char condition;
	statusProc* next;
};

struct process {
	int id;
	int burstTime;
	int startTime;
	int endTime;
	int waitTime;
	int cntStatus;
	int tagPrev;
	int arriveTime;
	int kollllllll;
	int prior;
	statusProc* conditionProc;
	process* next;
};

process* newZveno();
statusProc* newZvenoCond();
process* addLast(process* head, int data, int idHist);
process* specDelete(process* head, int value);
process* getProc(process* queueProc, int index);
process* copyQueue(process* queueProc);
statusProc* addLastCond(statusProc* head, char cond);
void copyCond(process* queueProc, process* archiveProc);
process* getLast(process* head);
process* getMinList(process* archiveProc);
process* getMinList2(process* archiveProc);
void sortIncr3(process* archiveProc, process** queueProc, int timer);
void dockQueue(process** archiveProc, process** queueProc, int timer, int* exePenalty);

