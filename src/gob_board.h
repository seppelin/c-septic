#pragma once

#include <sys/types.h>

typedef struct {
  int new;
  int size;
  int from_pos;
  int to_pos;
} GobMove;

typedef struct {
  uint layers[2][3];	
  int pieces[2][3];
  int sign;
  int moves;
} GobBoard;

GobBoard gobBoardInit();
uint gobTopView(uint layers[2][3], int sign);
uint gobIsMovable(uint layers[2][3], int sign, int size, int pos);
uint gobIsFree(uint layers[2][3], int size, int pos);
uint gobIsCover(uint layers[2][3], int size, int pos);
uint gobIsLine(uint view);

// 1-2=size 3=none
int gobGetTopSize(uint layers[2][3], int sign, int pos);
// 0=none 1=win 2=loss 3=draw
int gobGetState(uint layers[2][3], int sign);
int gobGetMoves(GobBoard* self, GobMove (*buf)[42]);

void gobDoNewMove(GobBoard* self, int size, int to_pos);
void gobDoBoardMove(GobBoard* self, int size, int from_pos, int to_pos);
void gobDoMove(GobBoard* self, GobMove move);
void gobUndoNewMove(GobBoard* self, int size, int to_pos);
void gobUndoBoardMove(GobBoard* self, int size, int from_pos, int to_pos);
void gobUndoMove(GobBoard* self, GobMove move);
