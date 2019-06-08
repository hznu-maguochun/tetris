#include "fileop.h"

int MAX(int a,int b);


int MAX(int a,int b){
	return a>b?a:b;
}

void WriteRecordFile(UserRecordLinkList *p){
	FILE *fp;
	UserRecordNode *tempPlayer;
	if((fp=fopen("myrecordALL.txt","w+"))==NULL){
		printf("ERROR ON WRITING FILE");
		return;	
	}
	fwrite(p,sizeof(UserRecordLinkList),1,fp);
    tempPlayer = p->firstplayer;
    while(tempPlayer !=NULL){
    	fwrite(tempPlayer,sizeof(UserRecordNode),1,fp);
    	tempPlayer = tempPlayer->next;
    }
    fclose(fp);
}

UserRecordLinkList *ReadRecordFile(){
    FILE *fp;
    UserRecordLinkList *t;
    UserRecordNode *p;
    UserRecordNode *pre;
    int i;
    if((fp=fopen("myrecordALL.txt","r"))==NULL){
    	printf("No file AND created head\n");
        t = (UserRecordLinkList *)malloc(sizeof(UserRecordLinkList));
        t->firstplayer = NULL;
        t->currentplayer = NULL;
        t->PlayerCounts = 0;
		return t;
    }
   
    t = (UserRecordLinkList *)malloc(sizeof(UserRecordLinkList));
    fread(t,sizeof(UserRecordLinkList),1,fp);
    if(t->PlayerCounts ==0)
    	return t;
    p = (UserRecordNode *)malloc(sizeof(UserRecordNode));
    fread(p,sizeof(UserRecordNode),1,fp);
    t->firstplayer = p;
    if(t->PlayerCounts ==1)
    	return t;
    pre = p;
    for(i = 2;i<=t->PlayerCounts;i++){
         p = (UserRecordNode *)malloc(sizeof(UserRecordNode));
         fread(p,sizeof(UserRecordNode),1,fp);
         pre->next = p;
		 pre = p;
    }
    p->next = NULL;
    return t;
    
}
//
void SetCurrentUser(UserRecordLinkList *p,char currentplayerName[20]){
	UserRecordNode *tp;
	printf("This is set current user\n");
	tp = p->firstplayer;
	while(tp != NULL){
		if(strcmp(currentplayerName,tp->playname)==0){
            p->currentplayer = tp;
            return;
		}
        tp = tp->next;
	}
	tp = (UserRecordNode *)malloc(sizeof(UserRecordNode));
//	tp->id = p->PlayerCounts;
	strcpy(tp->playname,currentplayerName);
	tp->score = 0;
	tp->level = 0;
	tp->history.HistoryItemCounts = 0;
	tp->next = NULL;
	tp->next = p->firstplayer;
	p->firstplayer = tp;
	p->PlayerCounts++;
}

void ModifyUserScore(UserRecordLinkList *p,int score,int level){
	UserRecordNode *tp; 
	int i;
	if(p->currentplayer == NULL)
		return;
	tp = p->currentplayer;  
	//先修改当前用户的history表
	if(tp->history.HistoryItemCounts >= HISTORY_CAPACITY){
        for(i = 0;i<HISTORY_CAPACITY;i++){
            tp->history.history[i].level = tp->history.history[i+1].level;
            tp->history.history[i].score = tp->history.history[i+1].score;
        }
        tp->history.history[HISTORY_CAPACITY-1].level = level;
        tp->history.history[HISTORY_CAPACITY-1].score = score;
	}
	else{
     	tp->history.history[tp->history.HistoryItemCounts].no = tp->history.HistoryItemCounts+1;
     	tp->history.history[tp->history.HistoryItemCounts].level = level;
     	tp->history.history[tp->history.HistoryItemCounts].score = score;
     	tp->history.HistoryItemCounts++;
	}
	//再将最高分存入当前用户的score
	tp->score = MAX(tp->score,score);
	tp->level = level;
    
}

void ReRank(UserRecordLinkList *p){
	UserRecordNode *tp,*tq;
	int i; 
	int rank = 1;
	if(p->PlayerCounts <=1)
		return;
	//循环PlayerCounts次，因数据量不大，每一次都从开头遍历到结束
	for(i = 0;i<p->PlayerCounts;i++){
		//比较开头两个用户score
		tq = p->firstplayer;
        tp = tq->next;
		if(tq->score<tp->score){
			tq->next = tp->next;
			tp->next = tq;
			p->firstplayer = tp;
		}
		//冒泡比较剩余用户score
		tq = p->firstplayer;
        tp = tq->next;
	    while(tp->next != NULL){
	    	if(tp->score < tp->next->score){
	    		tq->next = tp->next;
	    		tp->next = tp->next->next;
	    		tp->next->next = tp;
            }
            tq = tp;
            tp = tp->next;
	    }
	}
	tp = p->firstplayer;
	while(tp != NULL){
		tp->rank = rank++;
		tp = tp->next;
	}
}

void ClearUserHistory(UserRecordNode *currentplayer){
	currentplayer->history.HistoryItemCounts = 0;
	currentplayer->score = 0;
	currentplayer->level = 0;
}

void ResetGameRecord(UserRecordLinkList *p){
	UserRecordNode *tp,*tq;
	if(p->PlayerCounts == 0)
		return;
	if(p->PlayerCounts == 1){
		tp = p->firstplayer;
		free(tp);
		p->firstplayer = NULL;
		p->currentplayer = NULL;
		p->PlayerCounts = 0;
		return;
	}
	tp = p->firstplayer;
	while(tp != NULL){
		tq = tp;
		tp = tp->next;
		free(tq);
	}
	p->firstplayer = NULL;
	p->currentplayer = NULL;
	p->PlayerCounts = 0;
	return;
}

void DeleteCurrentUser(UserRecordLinkList *p){
	UserRecordNode *tp,*tq;
	if(p->currentplayer == NULL)
		return;
	if(p->currentplayer == p->firstplayer){
		tp = p->currentplayer;
		p->firstplayer = tp->next;
		p->currentplayer = NULL;
		free(tp);
		return;
	}
	tp = p->firstplayer;
	while(tp->next != p->currentplayer){
		tp = tp->next;
	}
	tq = p->currentplayer;
	tp->next = tq->next;
	p->currentplayer = NULL;
	free(tq);
	return;
}

void WriteLastRecordFile(struct Tetris *p, int a[30][23])
{
	FILE *fp;
	if((fp=fopen("myLASTrecord.txt","w+"))==NULL){
		printf("ERROR ON WRITING FILE");
		return;	
	}
	fwrite(p,sizeof(struct Tetris),1,fp);
	fwrite(a,sizeof(int),30*23,fp);
    fclose(fp);
}


void ReadLastRecordFlietoMemory(struct Tetris *p, int a[30][23])
{
	FILE *fp;
    if((fp=fopen("myLASTrecord.txt","r"))==NULL){
    	printf("No file AND created head\n");
    	fclose(fp);
    	return;
    }
    fread(p,sizeof(struct Tetris),1,fp);
    fread(a,30*23*sizeof(int),1,fp);
    fclose(fp);
    return;
}

