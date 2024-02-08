#include "board.h"

Board boardInit() {
  return (Board){
      {{0, 0, 0}, {0, 0, 0}},
      {{2, 2, 2}, {2, 2, 2}},
      0,
      0,
  };
}

int topView(int layers[2][3], int sign) {
  return layers[sign][0] & ~layers[sign ^ 1][1] |
         layers[sign][1] & ~layers[sign ^ 1][2] | layers[sign][2];
}

int isMovable(int layers[2][3], int sign, int size, int pos) {
  int bigger = 0; // w default
  switch (size) {
  case 0:
    bigger |= layers[0][1] | layers[1][1];
  case 1:
    bigger |= layers[0][2] | layers[1][2];
  }
  return ((1 << pos) & layers[sign][size] & (~bigger)) != 0;
}

int isFree(int layers[2][3], int size, int pos) {
  int same = layers[0][2] | layers[1][2];
  switch (size) {
  case 0:
    same |= layers[0][0] | layers[1][0];
  case 1:
    same |= layers[0][1] | layers[1][1] ;
  }
  return ((1 << pos) & same) == 0;
}

int isCover(int layers[2][3], int size, int pos) {
  int one_smaller;
  switch (size) {
  case 0:
    one_smaller = 0;
    break;
  case 1:
    one_smaller = layers[0][0] | layers[1][0];
    break;
  case 2:
    one_smaller = layers[0][1] | layers[1][1];
    break;
  }
  return ((1 << pos) & one_smaller) != 0;
}

int isLine(int view) {
  int check = view & view << 1 & view << 2 & 0b100100100; // vertical
  check |= view & view << 2 & view << 4 & 0b001000000;    // right-top left-bot
  check |= view & view << 3 & view << 6;                  // horizontal
  check |= view & view << 4 & view << 8;                  // left-top right-bot
  return check != 0;
}

int getTopSize(int layers[2][3], int sign, int pos) {
  for (int size = 0; size < 3; size++) {
    if (isMovable(layers, sign, size, pos))
      return size;
  }
  return 3;
}

int getState(int layers[2][3], int sign) {
  int win = isLine(topView(layers, sign));
  int loss = isLine(topView(layers, sign));
  return win | (loss << 1);
}

int getMoves(Board *self, Move (*buf)[42]) {
  int len = 0;
  for (int size = 2; size > -1; size -= 1) {
    for (int to_pos = 0; to_pos < 9; to_pos += 1) {
      if (!isFree(self->layers, size, to_pos))
        continue;
      // Board move
      for (int from_pos = 0; from_pos < 9; from_pos += 1) {
        if (!isMovable(self->layers, self->sign, size, from_pos))
          continue;
        Move move;
        move.new = 0;
        move.size = size;
        move.from_pos = from_pos;
        move.to_pos = to_pos;
        *buf[len] = move;
        len += 1;
      }
      // New move
      if (self->pieces[self->sign][size] < 1)
        continue;
      Move move;
      move.new = 1;
      move.size = size;
      move.to_pos = to_pos;
      *buf[len] = move;
      len += 1;
    }
  }
  return len;
}

void doNewMove(Board *self, int size, int to_pos) {
  self->pieces[self->sign][size] -= 1;
  self->layers[self->sign][size] |= 1 << to_pos;
  self->sign ^= 1;
  self->moves += 1;
}

void doBoardMove(Board *self, int size, int from_pos, int to_pos) {
  self->layers[self->sign][size] ^= 1 << from_pos;
  self->layers[self->sign][size] |= 1 << to_pos;
  self->sign ^= 1;
  self->moves += 1;
}

void doMove(Board *self, Move move) {
  if (move.new)
    doNewMove(self, move.size, move.to_pos);
  else
    doBoardMove(self, move.size, move.from_pos, move.to_pos);
}

void undoNewMove(Board *self, int size, int to_pos) {
  self->moves -= 1;
  self->sign ^= 1;
  self->layers[self->sign][size] ^= 1 << to_pos;
  self->pieces[self->sign][size] += 1;
}

void undoBoardMove(Board *self, int size, int from_pos, int to_pos) {
  self->moves -= 1;
  self->sign ^= 1;
  self->layers[self->sign][size] ^= 1 << to_pos;
  self->layers[self->sign][size] |= 1 << from_pos;
}

void undoMove(Board *self, Move move) {
  if (move.new)
    undoNewMove(self, move.size, move.to_pos);
  else
    undoBoardMove(self, move.size, move.from_pos, move.to_pos);
}
