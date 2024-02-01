#pragma once

#include "gob_board.h"

typedef enum {
  GBUNone,
  GBUFrom,
  GBUBoth,
} GobBoardUiState;

typedef struct {
  int x;
  int y;
  GobBoardUiState state;
  GobMove move;
} GobBoardUi;


