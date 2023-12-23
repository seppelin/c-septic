#include "menu.h"

#include "raylib.h"
#include "app.h"
#include "ui.h"

Scene menuRun() {
  Button b = buttonInitText(10, 10, "Quit", 25, DARKPURPLE);
  int quit = 0;
  while (!quit && !WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BACKGROUND);
    quit |= buttonTick(&b);
    EndDrawing();
  }
  buttonDeinit(&b);
  return Quit;
}
