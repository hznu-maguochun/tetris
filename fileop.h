#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

#define HISTORY_CAPACITY 100

#ifndef _FILE_H
#define _FILE_H
typedef struct SA
{
	int no;
	int level;
	int score;
}HistoryItem;

typedef struct SB
{
	int HistoryItemCounts;
	HistoryItem history[HISTORY_CAPACITY];
}HistoryRecord;

typedef struct SC
{
	int id;
	char playname[20];
	int score;
	int level;
	int rank;
	HistoryRecord history;
	struct SC *next;
}UserRecordNode;

typedef struct SD
{
	UserRecordNode *firstplayer;
	UserRecordNode *currentplayer;
	int PlayerCounts;
}UserRecordLinkList;

#endif

void WriteRecordFile(UserRecordLinkList *p);
UserRecordLinkList *ReadRecordFile();
void SetCurrentUser(UserRecordLinkList *p,char currentplayerName[20]);
void ModifyUserScore(UserRecordLinkList *p,int score,int level);
void ReRank(UserRecordLinkList *p);
void ClearUserHistory(UserRecordNode *currentplayer);
void ResetGameRecord(UserRecordLinkList *p);
void DeleteCurrentUser(UserRecordLinkList *p);

void WriteLastRecordFile(struct Tetris *p, int a[30][23]);
void ReadLastRecordFlietoMemory(struct Tetris *p, int a[30][23]);
