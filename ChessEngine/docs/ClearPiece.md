# ClearPiece Detailed Documentation

## Purpose

ClearPiece removes one piece from the board.

## How it Works

0. If finds the index of the element to remove by checking the square.
1. Asserts that is a valid index between 0 and 9 (there's a 10 piece max for each piece in chess).
2. Reduces the piece count.
3. Replaces the element to clear for the last piece in the array.
Because the array is zero-index while the count starts from 1, the new reduced count is the index of the "old" last element now out of reach.

## Code

```c
for (index = 0; index < position->pieceNumber[piece]; ++index) {
        if (position->pieceList[piece][index] == square) {
            t_pieceNum = index;
            break;
        }
    }

    ASSERT(t_pieceNum != -1);
    ASSERT(t_pieceNum >= 0 && t_pieceNum < 10);

    position->pieceNumber[piece]--;
    position->pieceList[piece][t_pieceNum] = position->pieceList[piece][position->pieceNumber[piece]];
