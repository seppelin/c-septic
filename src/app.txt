#include "menu.h"

#include "raylib.h"
#include "ui.h"

void menuRun() {
  Button b = buttonInitText(10, 10, "Quit", 16, PURPLE);
  int quit = 0;
  while (!quit && !WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GRAY);
    quit |= buttonTick(&b);
    EndDrawing();
  }
  buttonDeinit(&b);
  return;
}
