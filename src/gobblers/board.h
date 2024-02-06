#pragma once

typedef struct {
  int new;
  int size;
  int from_pos;
  int to_pos;
} Move;

typedef struct {
  int layers[2][3];
  int pieces[2][3];
  int sign;
  int moves;
} Board;

Board boardInit();
int topView(int layers[2][3], int sign);
int isMovable(int layers[2][3], int sign, int size, int pos);
int isFree(int layers[2][3], int size, int pos);
int isCover(int layers[2][3], int size, int pos);
int isLine(int view);

// 1-2=size 3=none
int getTopSize(int layers[2][3], int sign, int pos);
// 0=none 1=win 2=loss 3=draw
int getState(int layers[2][3], int sign);
int getMoves(Board *self, Move (*buf)[42]);

void doNewMove(Board *self, int size, int to_pos);
void doBoardMove(Board *self, int size, int from_pos, int to_pos);
void doMove(Board *self, Move move);
void undoNewMove(Board *self, int size, int to_pos);
void undoBoardMove(Board *self, int size, int from_pos, int to_pos);
void undoMove(Board *self, Move move);
