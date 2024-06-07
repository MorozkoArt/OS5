#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "list.h"

int main() {
	setlocale(LC_ALL, "Rus");
	int numProc = 0;
	printf("Введите количество процессов: ");
	scanf("%d", &numProc);
	process* archiveProc = NULL;
	int procTime = 0;
	int procArrive = 0;
	int prior = 0;
	for (int i = 0; i < numProc; i++) {
		printf("\nВведите время процесса %d: ", i + 1);
		scanf("%d", &procTime);
		archiveProc = addLast(archiveProc, procTime, -1);
		getProc(archiveProc, i)->id = i + 1;
		printf("Введите время поступления процесса %d: ", i + 1);
		scanf("%d", &procArrive);
		getProc(archiveProc, i)->arriveTime = procArrive;
		printf("Введите приоритет процесса %d: ", i + 1);
		scanf("%d", &prior);
		getProc(archiveProc, i)->prior = prior;
	}
	int timer = 0;
	float sumWaitTime = 0;
	float avgTime = 0;
	int remainingProc;
	process* queueProc = NULL;
	process* tempQueue = NULL;
	int* exedockQueue = (int*)calloc(numProc, sizeof(int));
	process* varArchiveProc = copyQueue(archiveProc);
	remainingProc = numProc;
	int quantumTime = 1;
	int y = 0;
	while (remainingProc > 0) {
		if (varArchiveProc == NULL) {
			y = 1;
		}
		dockQueue(&varArchiveProc, &queueProc, timer, exedockQueue); //создаёт новую очередь... 
		tempQueue = copyQueue(queueProc);
		queueProc = NULL;
		sortIncr3(tempQueue, &queueProc, timer);
		process* curProc = copyQueue(queueProc);
		if (curProc == NULL) {
			break;
		}
		queueProc = specDelete(queueProc, curProc->id);
		curProc->startTime = timer;
		for (int i = 0; i < timer - curProc->cntStatus; i++) {
			curProc->conditionProc = addLastCond(curProc->conditionProc, 'Г');
		}
		curProc->cntStatus += timer - curProc->cntStatus;
		copyCond(curProc, archiveProc);
		if (quantumTime >= curProc->burstTime) {
			timer += curProc->burstTime;
			curProc->endTime = timer - exedockQueue[curProc->id - 1];
			curProc->waitTime = curProc->startTime - curProc->kollllllll;
			sumWaitTime += curProc->waitTime;
			avgTime += curProc->endTime;
			for (int i = 0; i < curProc->burstTime; i++) {
				curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			}
			curProc->cntStatus += curProc->burstTime;
			copyCond(curProc, archiveProc);
			remainingProc--;
		}
		else {
			timer += quantumTime;
			curProc->kollllllll += quantumTime;
			curProc->burstTime -= quantumTime;
			curProc->conditionProc = addLastCond(curProc->conditionProc, 'И');
			curProc->cntStatus += quantumTime;
			copyCond(curProc, archiveProc);
			queueProc = addLast(queueProc, curProc->burstTime, curProc->id);
			getLast(queueProc)->cntStatus += curProc->cntStatus;
			getLast(queueProc)->tagPrev = curProc->tagPrev;
			getLast(queueProc)->kollllllll += curProc->kollllllll;
			getLast(queueProc)->prior = curProc->prior;
			getLast(queueProc)->arriveTime = curProc->arriveTime;
			copyCond(curProc, queueProc);
		}
	}
	float sumTime = timer;
	avgTime /= numProc;
	float avgWaitTime = sumWaitTime / numProc;
	printf("\n");
	printf("-------\nSJF 3.0\n-------\n");
	printf("Время, необходимое для обработки всех процессов: %g\n", sumTime);
	printf("Среднее полное время выполнения: %6.1f\n", avgTime);
	printf("Среднее время ожидания: %6.1f\n", avgWaitTime);
	printf("T");
	for (int i = 0; i < sumTime; i++) {
		printf("%5d", i);
	}
	printf("\n");
	for (int i = 0; i < numProc; i++) {
		process* curProc = getProc(archiveProc, i);
		if (curProc != NULL) {
			printf("%d", i + 1);
			for (int j = 0; j < sumTime; j++) {
				if (curProc->conditionProc != NULL) {
					printf("%5c", curProc->conditionProc->condition);
					curProc->conditionProc = curProc->conditionProc->next;
				}
				else {
					printf("%5c", ' ');
				}
			}
			printf("\n");
		}
	}
}






