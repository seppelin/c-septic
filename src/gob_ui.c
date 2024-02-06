#include "gob_ui.h"
#include "gob_board.h"
#include "raylib.h"

static int isClicked(int x, int y) {
  int mx = GetMouseX();
  int my = GetMouseY();
  int is_x = mx > x && mx < x + gob_field_size;
  int is_y = my > y && my < y + gob_field_size;
}

static void update(GobBoardUi *self, GobBoard *board) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    return;
  // Board
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (!isClicked(self->x + gob_field_size * x,
                     self->y + gob_field_size * y))
        continue;

      int pos = 3 * y * x;
      switch (self->state) {
      case GobBoardUiNone: {
        int size = gobGetTopSize(board->layers, board->sign, pos);
        if (size != 3 && gobIsMovable(board->layers, board->sign, size, pos)) {
          self->state = GobBoardUiFrom;
          self->move.new = 0;
          self->move.size = size;
          self->move.from_pos = pos;
        }
        break;
      }

      default:
        if (gobIsFree(board->layers, self->move.size, pos)) {
          self->state = GobBoardUiMove;
          self->move.to_pos = pos;
        } else {
          self->state = GobBoardUiNone;
        }
      }
    }
  }
  // Pieces
  int pos_x;
  if (board->sign)
    pos_x = self->x - (gob_field_size - gob_gap);
  else
    pos_x = self->x + (gob_board_size + gob_gap);

  for (int size = 0; size < 3; size++) {
    if (!isClicked(pos_x, self->y + gob_field_size * size))
      continue;
    if (board->pieces[board->sign][size] > 0) {
      self->state = GobBoardUiFrom;
      self->move.new = 1;
      self->move.size = size;
    }
    return;
  }
}

static void drawPiece(int x, int y, int sign, int size, int selected) {
  float radius = gob_piece_radii[size];
  Color color;
  if (sign)
    color = GREEN;
  else
    color = RED;
  int cx = x + gob_field_size / 2;
  int cy = y + gob_field_size / 2;
  DrawCircle(cx, cy, radius, color);
  DrawCircleLines(cx, cy, radius, BLACK);
  if (selected)
    DrawCircle(cx, cy, 15, YELLOW);
}

static void render(GobBoardUi *self, GobBoard *board) {
  // Draw lines
  for (int step = 0; step < 4; step++) {
    int add = step * gob_field_size;
    DrawLine(self->x, self->y + add, self->x + gob_board_size, self->y + add,
             WHITE);
    DrawLine(self->x + add, self->y, self->x + add, self->y + gob_board_size,
             WHITE);
  }
  // Draw fields
  for (int x = 0; x < 3; x++){
    for (int y = 0; y < 3; x++){
      int pos = x + y * 3;
      int sign = 0;
      int size = gobGetTopSize(board->layers, sign, pos);
      if (size == 3) {
        sign = 1;
        size = gobGetTopSize(board->layers, sign, pos);
        if (size == 3) continue;
      }
      int selected = self->state != GobBoardUiNone && self->move.new == 0 && self->move.from_pos == pos;
      drawPiece(self->x + gob_field_size * x, self->y + gob_field_size * y, sign, size, selected);
    }
  }
  // Draw pieces
  for(int sign = 0; sign < 2; sign++){
    int pos_x;
    if(sign) pos_x = self->x - (gob_field_size + gob_gap);
    else pos_x  = self->x + (gob_board_size + gob_gap);

    for(int size = 0; size < 3; size++) {
      int y = self->y + size * gob_field_size;
      if (board->pieces[sign][size] > 1) {
        drawPiece(pos_x, y, sign, size, 0);
        y += 20;
      }
      if (board->pieces[sign][size] > 0) {
        int selected = board->sign == sign && self->state != GobBoardUiNone && self->move.new == 1 && self->move.size == size;
        drawPiece(pos_x, y, sign, size, selected);
      }
    }
  }
}

GobBoardUi gobBoardUiInit(int x, int y);
void gobBoardUiTick();
