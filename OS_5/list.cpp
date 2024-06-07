#define _CRT_SECURE_NO_WARNINGS
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

process* newZveno() {
	process* V;
	V = (process*)malloc(sizeof(process));
	V->burstTime = 0;
	V->id = V->startTime = V->endTime = V->waitTime = V->cntStatus = V->tagPrev = V->arriveTime = V->kollllllll = V->prior = 0;
	V->conditionProc = NULL;
	V->next = NULL;
	return V;
}

process* addLast(process* head, int data, int idHist) {
	process* v = newZveno();
	if (head == NULL) {
		v->burstTime = data;
		if (idHist != -1)
			v->id = idHist;
		else
			v->id = 1;
		v->next = NULL;
		head = v;
		return head;
	}
	process* p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = v;
	v->burstTime = data;
	v->startTime = 0;
	v->endTime = 0;
	v->waitTime = 0;
	v->prior = 0;
	v->arriveTime = 0;
	v->next = NULL;

	if (idHist != -1)
		v->id = idHist;

	return head;
}

process* specDelete(process* head, int value) {
	process* pZveno = head;
	if (pZveno->id == value) {
		process* tempZveno = pZveno;
		head = pZveno->next;

		free(tempZveno);
		return head;
	}

	while (pZveno->next != NULL && pZveno->next->id != value)
		pZveno = pZveno->next;

	if (pZveno->next != NULL) {
		process* tempZveno = pZveno->next;
		pZveno->next = tempZveno->next;

		free(tempZveno);
	}
	else {
		printf("Элемент со значением %d не найден\n", value);
		return head;
	}

	return head;
}

process* getProc(process* queueProc, int index) {
	process* pProc = queueProc;
	int cnt = 0;
	while (pProc != NULL && cnt != index) {
		pProc = pProc->next;
		cnt++;
	}
	if ((cnt == index) && (pProc != NULL))
		return pProc;
	else
		return NULL;
}

process* copyQueue(process* queueProc) {
	process* pProc = queueProc;
	process* newQueue = newZveno();
	process* newProc = NULL;
	process* lastNewProc = newQueue;
	newQueue->id = pProc->id;
	newQueue->burstTime = pProc->burstTime;
	newQueue->startTime = pProc->startTime;
	newQueue->endTime = pProc->endTime;
	newQueue->waitTime = pProc->waitTime;
	newQueue->cntStatus = pProc->cntStatus;
	newQueue->tagPrev = pProc->tagPrev;
	newQueue->arriveTime = pProc->arriveTime;
	newQueue->kollllllll = pProc->kollllllll;
	newQueue->prior = pProc->prior;
	copyCond(pProc, newQueue);
	newQueue->next = NULL;

	pProc = pProc->next;
	while (pProc != NULL) {
		newProc = newZveno();
		newProc->id = pProc->id;
		newProc->burstTime = pProc->burstTime;
		newProc->startTime = pProc->startTime;
		newProc->endTime = pProc->endTime;
		newProc->waitTime = pProc->waitTime;
		newProc->cntStatus = pProc->cntStatus;
		newProc->tagPrev = pProc->tagPrev;
		newProc->arriveTime = pProc->arriveTime;
		newProc->kollllllll = pProc->kollllllll;
		newProc->prior = pProc->prior;
		copyCond(pProc, newProc);
		newProc->next = NULL;
		lastNewProc->next = newProc;
		lastNewProc = lastNewProc->next;
		pProc = pProc->next;
	}
	return newQueue;
}

statusProc* newZvenoCond() {
	statusProc* V;
	V = (statusProc*)malloc(sizeof(statusProc));
	V->next = NULL;
	return V;
}

statusProc* addLastCond(statusProc* head, char cond) {
	statusProc* v = newZvenoCond();
	if (head == NULL) {
		v->next = NULL;
		v->condition = cond;
		head = v;
		return head;
	}
	statusProc* p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = v;
	v->condition = cond;
	v->next = NULL;
	return head;
}

void copyCond(process* queueProc, process* archiveProc) {
	process* pProc = queueProc;
	while (pProc != NULL) {
		process* pArchive = archiveProc;
		while ((pArchive != NULL) && (pProc->id != pArchive->id)) {
			pArchive = pArchive->next;
		}
		if ((pProc != NULL) && (pArchive != NULL)) {
			statusProc* pCondProc = pProc->conditionProc;
			statusProc** ppCondArchive = &(pArchive->conditionProc);
			while (pCondProc != NULL) {
				if (pCondProc->condition != NULL) {
					statusProc* newCond = new statusProc;
					*newCond = *pCondProc;
					*ppCondArchive = newCond;
					ppCondArchive = &(newCond->next);
				}
				pCondProc = pCondProc->next;
			}
		}
		pProc = pProc->next;
	}
}

process* getLast(process* head) {
	process* last = head;
	while (last != NULL && last->next != NULL) {
		last = last->next;
	}
	return last;
}

process* getMinList(process* archiveProc) {
	process* pProc = archiveProc;
	process* minList = copyQueue(pProc);
	int minBurst = 99999999;
	while (pProc != NULL) {
		if ((pProc->arriveTime < minBurst) && (!pProc->tagPrev) && (pProc->prior == getMinList2(archiveProc)->prior)) {
			minBurst = pProc->arriveTime;
			minList = copyQueue(pProc);
		}
		if (pProc->tagPrev)
			pProc->tagPrev = 0;
		pProc = pProc->next;
	}
	return minList;
}

process* getMinList2(process* archiveProc) {
	process* pProc = archiveProc;
	process* minList = copyQueue(pProc);
	int minBurst = 9999999;
	while (pProc != NULL) {
		if ((pProc->prior < minBurst) && (!pProc->tagPrev)) {
			minBurst = pProc->prior;
			minList = copyQueue(pProc);
		}
		if (pProc->tagPrev)
			pProc->tagPrev = 0;
		pProc = pProc->next;
	}
	return minList;
}



void sortIncr3(process* archiveProc, process** queueProc, int timer) {

	process* pProc = archiveProc;
	while (archiveProc != NULL) {
		process* pProc = archiveProc;
		int deleteValue = 0;
		while (pProc != NULL) {
			if (pProc->arriveTime == getMinList(archiveProc)->arriveTime && pProc->prior == getMinList(archiveProc)->prior) {
				*queueProc = addLast(*queueProc, pProc->burstTime, pProc->id);
				getLast(*queueProc)->cntStatus += pProc->cntStatus;
				getLast(*queueProc)->tagPrev = pProc->tagPrev;
				getLast(*queueProc)->arriveTime = pProc->arriveTime;
				getLast(*queueProc)->kollllllll += pProc->kollllllll;
				getLast(*queueProc)->prior = pProc->prior;
				copyCond(pProc, *queueProc);
				deleteValue = pProc->id;
				pProc = pProc->next;
				archiveProc = specDelete(archiveProc, deleteValue);
			}
			else
				pProc = pProc->next;
		}
	}
}


void dockQueue(process** archiveProc, process** queueProc, int timer, int* exePenalty) {
	process* pProc = *archiveProc;
	int deleteValue = 0;
	while (pProc != NULL) {
		if (pProc->arriveTime <= timer) {
			*queueProc = addLast(*queueProc, pProc->burstTime, pProc->id);
			getLast(*queueProc)->tagPrev = pProc->tagPrev;
			getLast(*queueProc)->arriveTime = 0;
			for (int i = 0; i < timer; i++) {
				pProc->conditionProc = addLastCond(pProc->conditionProc, ' ');
			}
			pProc->kollllllll += timer;
			exePenalty[pProc->id - 1] += timer;
			pProc->cntStatus += timer;
			getLast(*queueProc)->arriveTime = pProc->arriveTime;
			getLast(*queueProc)->cntStatus += pProc->cntStatus;
			getLast(*queueProc)->kollllllll += pProc->kollllllll;
			getLast(*queueProc)->prior = pProc->prior;
			copyCond(pProc, *queueProc);
			deleteValue = pProc->id;
			pProc = pProc->next;
			*archiveProc = specDelete(*archiveProc, deleteValue);
		}
		else
			pProc = pProc->next;
	}
}




