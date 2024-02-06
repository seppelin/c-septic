#pragma once

#include "raylib.h"
#include "gob_board.h"

typedef enum {
  GobBoardUiNone,
  GobBoardUiFrom,
  GobBoardUiMove,
} GobBoardUiState;

typedef struct {
  int x;
  int y;
  GobBoardUiState state;
  GobMove move;
} GobBoardUi;

const float gob_piece_radii[3] = { 35, 60, 85 };
const int gob_field_size = 200;
const int gob_board_size = gob_field_size * 3;
const int gob_gap = gob_field_size / 4;

static int isClicked(int x, int y);
static void update(GobBoardUi *self, GobBoard* board);
static void drawPiece(int x, int y, int sign, int size, int selected);
static void render(GobBoardUi* self, GobBoard *board);

GobBoardUi gobBoardUiInit(int x, int y);
void gobBoardUiTick();
