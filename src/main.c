#include "septic.h"
#include "raylib.h"
#include "ui.h"

Scene runGobblers() {
  
}

Scene runMenu() {
  Button quit = buttonInitText(10, 10, "Quit", 25, PURPLE);
  Button gobblers = buttonInitText(250, 250, "Gobblers", 25, PURPLE);
  Scene retScene = SceneNone;
  while (retScene == SceneNone) {
    BeginDrawing();
    ClearBackground(BACKGROUND);
    if (buttonTick(&quit)) retScene = SceneQuit;
    if (buttonTick(&gobblers)) retScene = SceneGobblers;
    EndDrawing();
    if (WindowShouldClose()) retScene = SceneQuit;
  }
  buttonDeinit(&quit);
  buttonDeinit(&gobblers);
  return retScene;
}

int main(void) {
  InitWindow(1600, 900, "septic");
  Scene scene = SceneMenu;
  while (scene != SceneQuit) {
    switch (scene) {
    case SceneMenu:
      scene = runMenu();
      break;
    default:
      scene = SceneQuit;
    }
  }
  CloseWindow();
  return 0;
}
