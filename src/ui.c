#include "ui.h"
#include "raylib.h"
#include <stdio.h>

Button buttonInit(Image img, int x, int y, int width, int height) {
  Image resize_img = ImageCopy(img);
  ImageResize(&resize_img, width, height);
  Texture texture = LoadTextureFromImage(resize_img);
  UnloadImage(resize_img);

  Rectangle rect = {x, y, width, height};
  Rectangle p_rect = {
      rect.x - rect.width * 0.05,
      rect.y - rect.height * 0.05,
      rect.width * 1.1,
      rect.height * 1.1,
  };
  return (Button){texture, {rect, p_rect}, 0};
}

Button buttonInitText(int x, int y, char *text, int size, Color tint) {
  int len = MeasureText(text, size);
  Image img = GenImageColor(len + 13, size + 10, BLANK);

  ImageDrawText(&img, text, 5, 5, size, tint);
  ImageDrawRectangleLines(&img, (Rectangle){ 0, 0, img.width, img.height }, 2, tint);
  Button b = buttonInit(img, x, y, img.width, img.height);
  UnloadImage(img);

  return b;
}

int buttonTick(Button *b) {
  b->isHovered =
      CheckCollisionPointRec(GetMousePosition(), b->rects[b->isHovered]);
  Vector2 pos = {b->rects[b->isHovered].x, b->rects[b->isHovered].y};
  float scale = 1.0 + 0.1 * b->isHovered;
  DrawTextureEx(b->texture, pos, 0.0, scale, WHITE);
  return b->isHovered && IsMouseButtonPressed(0);
}

void buttonDeinit(Button *b) { UnloadTexture(b->texture); }
