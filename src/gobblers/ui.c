#include "ui.h"
#include "raylib.h"

const float piece_radii[3] = {35, 60, 85};
const int field_size = 200;
const int board_size = field_size * 3;
const int gap = field_size / 4;

int isClicked(int x, int y) {
  int mx = GetMouseX();
  int my = GetMouseY();
  int is_x = mx > x && mx < x + field_size;
  int is_y = my > y && my < y + field_size;
  return is_x && is_y;
}

void update(BoardUi *self, Board *board) {
  if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    return;
  // Board
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (!isClicked(self->x + field_size * x, self->y + field_size * y))
        continue;

      int pos = x + y * 3;
      switch (self->state) {
      case BoardUiNone: {
        int size = getTopSize(board->layers, board->sign, pos);
        if (size != 3 && isMovable(board->layers, board->sign, size, pos)) {
          self->state = BoardUiFrom;
          self->move.new = 0;
          self->move.size = size;
          self->move.from_pos = pos;
        }
        break;
      }

      default:
        if (isFree(board->layers, self->move.size, pos)) {
          self->state = BoardUiMove;
          self->move.to_pos = pos;
        } else {
          self->state = BoardUiNone;
        }
      }
      return;
    }
  }
  // Pieces
  int pos_x;
  if (!board->sign)
    pos_x = self->x - (field_size + gap);
  else
    pos_x = self->x + (board_size + gap);

  for (int size = 0; size < 3; size++) {
    if (!isClicked(pos_x, self->y + field_size * size))
      continue;
    if (board->pieces[board->sign][size] > 0) {
      self->state = BoardUiFrom;
      self->move.new = 1;
      self->move.size = size;
    }
    return;
  }
  self->state = BoardUiNone;
}

void drawPiece(int x, int y, int sign, int size, int selected) {
  float radius = piece_radii[size];
  Color color;
  if (!sign)
    color = GREEN;
  else
    color = RED;
  int cx = x + field_size / 2;
  int cy = y + field_size / 2;
  DrawCircle(cx, cy, radius, color);
  DrawCircleLines(cx, cy, radius, BLACK);
  if (selected)
    DrawCircle(cx, cy, 15, YELLOW);
}

void draw(BoardUi *self, Board *board) {
  // Draw lines
  for (int step = 0; step < 4; step++) {
    int add = step * field_size;
    DrawLine(self->x, self->y + add, self->x + board_size, self->y + add,
             WHITE);
    DrawLine(self->x + add, self->y, self->x + add, self->y + board_size,
             WHITE);
  }
  // Draw fields
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      int pos = x + y * 3;
      int sign = 0;
      int size = getTopSize(board->layers, sign, pos);
      if (size == 3) {
        sign = 1;
        size = getTopSize(board->layers, sign, pos);
        if (size == 3){
          continue;
        }
      }
      int selected = self->state != BoardUiNone && self->move.new == 0 &&
                     self->move.from_pos == pos;
      drawPiece(self->x + field_size * x, self->y + field_size * y, sign, size,
                selected);
    }
  }
  // Draw pieces
  for (int sign = 0; sign < 2; sign++) {
    int pos_x;
    if (!sign)
      pos_x = self->x - (field_size + gap);
    else
      pos_x = self->x + (board_size + gap);

    for (int size = 0; size < 3; size++) {
      int y = self->y + size * field_size;
      if (board->pieces[sign][size] > 1) {
        drawPiece(pos_x, y, sign, size, 0);
        y += 20;
      }
      if (board->pieces[sign][size] > 0) {
        int selected = board->sign == sign && self->state != BoardUiNone &&
                       self->move.new == 1 && self->move.size == size;
        drawPiece(pos_x, y, sign, size, selected);
      }
    }
  }
}

BoardUi boardUiInit(int x, int y) {
  BoardUi ui;
  ui.x = x;
  ui.y = y;
  ui.state = BoardUiNone;
  return ui;
}

void boardUiTick(BoardUi *self, Board *board) {
  update(self, board);
  draw(self, board);
}
