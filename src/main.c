#include "app.h"
#include "menu.h"
#include "raylib.h"
#include "ui.h"

int main(void) {
  InitWindow(1600, 900, "septic");
  Scene scene = Menu;
  while (scene != Quit) {
    switch (scene) {
    case Menu:
      scene = menuRun();
    default:
      scene = Quit;
    }
  }
  CloseWindow();
  return 0;
}
