#include "Search.h"

#include <windows.h>
#include <iostream>

static bool isRepetition(const BOARD *position);
static void CheckUp(SEARCHINFO *info);
static void ClearForSearch(BOARD *position, SEARCHINFO *info);
static int AlphaBeta(int alpha, int beta, int depth, BOARD *position, SEARCHINFO *info, bool doNull);
static int Quiescence(int alpha, int beta, BOARD *position, SEARCHINFO *info);
static void PickNextMove(int moveNum, MOVELIST* lists);

void SearchPosition(BOARD *position, SEARCHINFO *info){

	int bestMove = NOMOVE;
	int bestScore = -INFINITY;
	int currentDepth,pvMoves,pvNum = 0;

	ClearForSearch(position,info);

	//if(EngineOptions->UseBook == TRUE) {
	//	bestMove = GetBookMove(pos);


	if(bestMove == NOMOVE) {
		for( currentDepth = 1; currentDepth <= info->depth; ++currentDepth ) {

			//rootDepth = currentDepth;
			bestScore = AlphaBeta(-INFINITY, INFINITY, currentDepth, position, info, TRUE);

			if(info->stopped == true)
				break;

			pvMoves = GetPVLine(currentDepth, position);
			bestMove = position->pvArray[0];

			printf("Depth:%d score:%d move:%s nodes:%1d ",
					currentDepth,bestScore,PrintMove(bestMove),info->nodes);

			pvMoves = GetPVLine(currentDepth, position);
			printf("pv");
			for(pvNum = 0; pvNum < pvMoves; ++pvNum) {
				printf(" %s",PrintMove(position->pvArray[pvNum]));
			}
			printf("\n");
			printf("Ordering:%.2f\n",(info->failHighFirst/info->failHigh));
			/*if(info->GAME_MODE == UCIMODE) {
				printf("info score cp %d depth %d nodes %ld time %d ",
					bestScore,currentDepth,info->nodes,GetTimeMs()-info->starttime);
			} else if(info->GAME_MODE == XBOARDMODE && info->POST_THINKING == TRUE) {
				printf("%d %d %d %ld ",
					currentDepth,bestScore,(GetTimeMs()-info->starttime)/10,info->nodes);
			} else if(info->POST_THINKING == TRUE) {
				printf("score:%d depth:%d nodes:%ld time:%d(ms) ",
					bestScore,currentDepth,info->nodes,GetTimeMs()-info->starttime);
			}

			if(info->GAME_MODE == UCIMODE || info->POST_THINKING == TRUE) {
				pvMoves = GetPvLine(currentDepth, pos);
				if(!info->GAME_MODE == XBOARDMODE) {
					printf("pv");
				}
				for(pvNum = 0; pvNum < pvMoves; ++pvNum) {
					printf(" %s",PrMove(pos->PvArray[pvNum]));
				}
				printf("\n");


			}*/
		}
	}

	/*if(info->GAME_MODE == UCIMODE) {
		printf("bestmove %s\n",PrMove(bestMove));
	} else if(info->GAME_MODE == XBOARDMODE) {
		printf("move %s\n",PrMove(bestMove));
		MakeMove(pos, bestMove);
	} else {
		printf("\n\n***!! Vice makes move %s !!***\n\n",PrMove(bestMove));
		MakeMove(pos, bestMove);
		PrintBoard(pos);
	}*/
}

static void CheckUp(SEARCHINFO *info){
	if(info->timeset == true && GetTickCount() > info->stoptime)
		info->stopped = true;
}

static void ClearForSearch(BOARD *position, SEARCHINFO *info){
	int index = 0;
	int index2 = 0;

	for(index = 0; index < PIECE_TYPE_NUMBER; ++index) {
		for(index2 = 0; index2 < BOARD_SQUARE_NUMBER; ++index2) {
			position->searchHistory[index][index2] = 0;
		}
	}

	for(index = 0; index < 2; ++index) {
		for(index2 = 0; index2 < MAXDEPTH; ++index2) {
			position->searchKillers[index][index2] = 0;
		}
	}

	ClearPVTable(position->pvTable);
	position->play = 0;

	info->starttime = GetTickCount();
	info->stopped = 0;
	info->nodes = 0;
	info->failHigh = 0;
	info->failHighFirst = 0;

	/*position->HashTable->overWrite=0;
	position->HashTable->hit=0;
	position->HashTable->cut=0;
	 */
}

static int AlphaBeta(int alpha, int beta, int depth, BOARD *position, SEARCHINFO *info, bool doNull){

	ASSERT(CheckBoard(position));
	//ASSERT(beta>alpha);
	//ASSERT(depth>=0);


	if(depth <= 0)
		return Quiescence(alpha, beta, position, info);

	if((info->nodes & 2047) == 0)
		CheckUp(info);

	info->nodes++;

	if((isRepetition(position) || position->fiftyMove >= 100)/* && position->play*/)
		return 0;

	if(position->play > MAXDEPTH - 1)
		return EvalPosition(position);

	bool InCheck = SqAttacked(position->Kings[position->side],position->side^1,position);

	/*if(InCheck == true)
		depth++;*/

	int Score = -INFINITY;
	int PvMove = ProbePVTable(position);/*NOMOVE;*/

	/*if( ProbeHashEntry(pos, &PvMove, &Score, alpha, beta, depth) == TRUE ) {
		pos->HashTable->cut++;
		return Score;
	}

	if( DoNull && !InCheck && pos->ply && (pos->bigPce[pos->side] > 0) && depth >= 4) {
		MakeNullMove(pos);
		Score = -AlphaBeta( -beta, -beta + 1, depth-4, pos, info, FALSE);
		TakeNullMove(pos);
		if(info->stopped == TRUE) {
			return 0;
		}

		if (Score >= beta && abs(Score) < ISMATE) {
			info->nullCut++;
			return beta;
		}
	}*/

	MOVELIST list[1];
	GenerateAllMoves(position,list);

	int MoveNum = 0;
	int Legal = 0;
	int OldAlpha = alpha;
	int BestMove = NOMOVE;
	int BestScore = -INFINITY;
	Score = -INFINITY;

	if(PvMove != NOMOVE) {
		for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {
			if(list->moves[MoveNum].move == PvMove) {
				list->moves[MoveNum].score = 2000000;
				break;
			}
		}
	}

	for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {

		//TODO: cambar por lista ordenada post generacion
		PickNextMove(MoveNum, list);

		if (!MakeMove(position,list->moves[MoveNum].move))  {
			continue;
		}

		Legal++;
		Score = -AlphaBeta( -beta, -alpha, depth-1, position, info, TRUE);
		TakeMove(position);

		if(info->stopped == TRUE)
			return 0;


		//if(Score > BestScore) {
			//BestScore = Score;
			//BestMove = list->moves[MoveNum].move;
			if(Score > alpha) {
				if(Score >= beta) {
					if(Legal==1)
						info->failHighFirst++;
					info->failHigh++;

					if(!(list->moves[MoveNum].move & MFLAGCAP)) {
						position->searchKillers[1][position->play] = position->searchKillers[0][position->play];
						position->searchKillers[0][position->play] = list->moves[MoveNum].move;
					}

					/*StoreHashEntry(pos, BestMove, beta, HFBETA, depth);
					*/
					return beta;
				}
				alpha = Score;
				BestMove = list->moves[MoveNum].move;
				if(!(list->moves[MoveNum].move & MFLAGCAP)) {
					position->searchHistory[position->pieces[FROMSQ(BestMove)]][TOSQ(BestMove)] += depth;
				}
			}
		//}
	}

	if(Legal == 0) {
		if(InCheck)
			return -MATE + position->play;
		 else
			return 0;
	}

	//ASSERT(alpha>=OldAlpha);

	if(alpha != OldAlpha){
		StorePVMove(position, BestMove);
	}

	/*if(alpha != OldAlpha) {
		StoreHashEntry(pos, BestMove, BestScore, HFEXACT, depth);
	} else {
		StoreHashEntry(pos, BestMove, alpha, HFALPHA, depth);
	}*/

	return alpha;
}

//Todo: simplificar quiescence con alfa beta
static int Quiescence(int alpha, int beta, BOARD *position, SEARCHINFO *info){
	ASSERT(CheckBoard(position));

	if((info->nodes & 2047) == 0)
		CheckUp(info);

	info->nodes++;

	if(isRepetition(position) || position->fiftyMove >= 100)
		return 0;

	if(position->play > MAXDEPTH -1)
		return EvalPosition(position);

	int Score = EvalPosition(position);

	if(Score >= beta)
		return beta;

	if(Score >= alpha)
		alpha = Score;

	MOVELIST list[1];
	GenerateAllCaptures(position, list);

	int MoveNum = 0;
	int Legal = 0;
	int OldAlpha = alpha;
	int BestMove = NOMOVE;
	int BestScore = -INFINITY;
	Score = -INFINITY;
	int PvMove = ProbePVTable(position);

	if(PvMove != NOMOVE) {
		for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {
			if(list->moves[MoveNum].move == PvMove) {
				list->moves[MoveNum].score = 2000000;
				break;
			}
		}
	}

	for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {

		//TODO: cambar por lista ordenada post generacion
		PickNextMove(MoveNum, list);

		if (!MakeMove(position,list->moves[MoveNum].move))  {
			continue;
		}

		Legal++;
		Score = -Quiescence( -beta, -alpha, position, info);
		TakeMove(position);

		if(info->stopped == TRUE)
			return 0;

		if(Score > alpha) {
			if(Score >= beta) {
				if(Legal==1)
					info->failHighFirst++;
				info->failHigh++;
				return beta;
			}
			alpha = Score;
			BestMove = list->moves[MoveNum].move;
		}
	}

	if(alpha != OldAlpha)
		StorePVMove(position, BestMove);

	return alpha;
}

static void PickNextMove(int moveNum, MOVELIST* list){
	MOVE temp;
	int index, bestScore = 0;
	int bestNum = moveNum;

	for(index = moveNum; index< list->count; ++index){
		if(list->moves[index].score >bestScore){
			bestScore = list->moves[index].score;
			bestNum = index;
		}
	}

	temp = list->moves[moveNum];
	list->moves[moveNum] = list->moves[bestNum];
	list->moves[bestNum] = temp;
}

static bool isRepetition(const BOARD *position){

	int index = 0;

	for(index = position->historyPlay - position->fiftyMove; index < position->historyPlay-1; ++index){

		ASSERT(index >= 0 && index< MAX_GAME_MOVES);

		if(position->positionKey == position->history[index].positionKey)
			return true;
	}

	return false;
}
