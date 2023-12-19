#pragma once

#include "raylib.h"

typedef struct Button {
  Texture texture;
  Rectangle rects[2];
  int isHovered;
} Button;

Button buttonInit(Image img, int x, int y, int width, int height);
Button buttonInitText(int x, int y, char text[], int size, Color tint);
int buttonTick(Button* b);
void buttonDeinit(Button* b);


