#include "DataManager.h"
#include "../Common/Macros.h"
#include "../Common/Global.h"
#include "../Common/Definitions.h"
#include <stdio.h>

void InitializeSq120To64()
{
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    for(index = 0; index < BOARD_SEQUENCE_NUMBER; ++index){
        Sq120ToSq64[index] = 65;
    }
    for(index = 0; index < BOARD_REAL_NUMBER; ++index){
        Sq64ToSq120[index] = 120;
    }
    for(rank = RANK_1; rank <= RANK_8; ++rank){
        for(file = FILE_A; file <= FILE_H; ++file){
            sq = FR2SQ(file,rank);
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;            
            sq64++;
        }
    }
}

void printArrays(){
    int index = 0;
    for(index = 0; index < BOARD_SEQUENCE_NUMBER; ++index){
        if(index%10==0)
            printf("\n");
        printf("%5d",Sq120ToSq64[index]);
    }
    printf("\n");
    for(index = 0; index < BOARD_REAL_NUMBER; ++index){
        if(index%8==0)
            printf("\n");
        printf("%5d",Sq64ToSq120[index]);
    }
}

void LoadData()
{
    InitializeSq120To64();
    if(TESTING_MODE)
        printArrays();
}

