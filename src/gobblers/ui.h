#pragma once

#include "board.h"

typedef enum {
  BoardUiNone,
  BoardUiFrom,
  BoardUiMove,
} BoardUiState;

typedef struct {
  int x;
  int y;
  BoardUiState state;
  Move move;
} BoardUi;

BoardUi boardUiInit(int x, int y);
void boardUiDraw(BoardUi *self, Board *board);
void boardUiUpdate(BoardUi *self, Board *board);
