#include "gobblers.h"
#include "raylib.h"
#include "septic.h"
#include "ui.h"
#include <stdio.h>

Scene menuRun() {
  Button quit = buttonInitText(10, 10, "Quit", 25, PURPLE);
  Button gobblers = buttonInitText(250, 250, "Gobblers", 25, PURPLE);
  Scene retScene = SceneNone;
  while (retScene == SceneNone) {
    BeginDrawing();
    ClearBackground(BACKGROUND);
    if (buttonTick(&quit))
      retScene = SceneQuit;
    if (buttonTick(&gobblers))
      retScene = SceneGobblers;
    EndDrawing();
    if (WindowShouldClose())
      retScene = SceneQuit;
  }
  buttonDeinit(&quit);
  buttonDeinit(&gobblers);
  return retScene;
}

int main(void) {
  InitWindow(1600, 900, "septic");
  SetTargetFPS(60);
  Scene scene = SceneMenu;
  while (scene != SceneQuit) {
    switch (scene) {
    case SceneMenu:
      scene = menuRun();
      break;
    case SceneGobblers:
      scene = gobRun();
      break;
    default:
      scene = SceneQuit;
    }
  }
  CloseWindow();
  return 0;
}
