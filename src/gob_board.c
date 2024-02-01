#include "gob_board.h"

GobBoard gobInit() {
  return (GobBoard){
      {{0, 0, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}},
      0,
      0,
  };
}

uint gobTopView(uint layers[2][3], int sign) {
  return layers[sign][0] & ~layers[sign ^ 1][1] |
         layers[sign][1] & ~layers[sign ^ 1][2] | layers[sign][2];
}

uint gobIsMovable(uint layers[2][3], int sign, int size, int pos) {
  int bigger; // bigger pieces
  switch(size) {
  case 0:
    bigger = layers[0][1] | layers[1][1] | layers[0][2] | layers[1][2];
  case 1:
    bigger = layers[0][2] | layers[1][2];
  case 2:
    bigger = 0;      
  }
  return (1 << pos) & layers[sign][size] & ~bigger != 0;
}

uint gobIsFree(uint layers[2][3], int size, int pos) {
  int same;
  switch(size) {
  case 0:
    same = layers[0][0] | layers[1][0] | layers[0][1] | layers[1][1] | layers[0][2] | layers[1][2];
  case 1:
    same = layers[0][1] | layers[1][1] | layers[0][2] | layers[1][2];
  case 2:
    same = layers[0][2] | layers[1][2];
  }
  return ((1 << pos) & same) == 0;
}

uint gobIsCover(uint layers[2][3], int size, int pos) {
  int one_smaller;
  switch(size) {
  case 0:
    one_smaller = 0;
  case 1:
    one_smaller = layers[0][0] | layers[1][0];
  case 2:
    one_smaller = layers[0][1] | layers[1][1];
  }
  return ((1 << pos) & one_smaller) != 0;
}

uint gobIsLine(uint view) {
  int check = view & view << 1 & view << 2 & 0b100100100; // vertical
  check |= view & view << 2 & view << 4 & 0b001000000; // right-top left-bot
  check |= view & view << 3 & view << 6; // horizontal 
  check |= view & view << 4 & view << 8; // left-top right-bot
  return check != 0;
}

int gobGetTopSize(uint layers[2][3], int sign, int pos) {
  for (int size = 0; size < 3; size += 1) {
    if (gobIsMovable(layers, sign, size, pos)) return size;
  }
  return 3;
}

int gobGetState(uint layers[2][3], int sign) {
  int win = gobIsLine(gobTopView(layers, sign));
  int loss = gobIsLine(gobTopView(layers, sign));
  return win | loss << 1;
}

int gobGetMoves(GobBoard* self, GobMove (*buf)[42]) {
  int len = 0;
  for (int size = 2; size >= 0; size -= 1) {
    for (int to_pos = 0; to_pos < 9; to_pos += 1) {
      if (!gobIsFree(self->layers, size, to_pos)) continue;
      // Board move
      for (int from_pos = 0; from_pos < 9; from_pos += 1) {
        if (!gobIsMovable(self->layers, self->sign, size, from_pos)) continue;
        GobMove move;
        move.new = 0;
        move.size = size;
        move.from_pos = from_pos;
        move.to_pos = to_pos;
        *buf[len] = move;
        len += 1;
      }
      // New move
      if (self->pieces[self->sign][size] < 1) continue;
      GobMove move;
      move.new = 1;
      move.size = size;
      move.to_pos = to_pos;
      *buf[len] = move;
      len += 1;
    }
  }
  return len;
}

void gobDoNewMove(GobBoard* self, int size, int to_pos) {
  self->pieces[self->sign][size] -= 1;
  self->layers[self->sign][size] |= 1 << to_pos;
  self->sign ^= 1;
  self->moves += 1;
}

void gobDoBoardMove(GobBoard* self, int size, int from_pos, int to_pos) {
  self->layers[self->sign][size] ^= 1 << from_pos;
  self->layers[self->sign][size] |= 1 << to_pos;
  self->sign ^= 1;
  self->moves += 1;
}

void gobDoMove(GobBoard* self, GobMove move) {
  if (move.new) gobDoNewMove(self, move.size, move.to_pos);
  else gobDoBoardMove(self, move.size, move.from_pos, move.to_pos);
}

void gobUndoNewMove(GobBoard* self, int size, int to_pos) {
  self->moves -= 1;
  self->sign ^= 1;
  self->layers[self->sign][size] ^= 1 << to_pos;
  self->pieces[self->sign][size] += 1;
}

void gobUndoBoardMove(GobBoard* self, int size, int from_pos, int to_pos) {
  self->moves -= 1;
  self->sign ^= 1;
  self->layers[self->sign][size] ^= 1 << to_pos;
  self->layers[self->sign][size] |= 1 << from_pos;
}

void gobUndoMove(GobBoard* self, GobMove move) {
  if (move.new) gobUndoNewMove(self, move.size, move.to_pos);
  else gobUndoBoardMove(self, move.size, move.from_pos, move.to_pos);
}
