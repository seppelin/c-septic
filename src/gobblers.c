#include "gobblers.h"

#include "gobblers/board.h"
#include "gobblers/ui.h"
#include "raylib.h"
#include "ui.h"

Scene gobRun() {
  Button quit = buttonInitText(10, 10, "Quit", 25, PURPLE);
  Board board = boardInit();
  BoardUi board_ui = boardUiInit(500, 200);
  Scene scene = SceneNone;

  while (scene == SceneNone) {
    BeginDrawing();
    ClearBackground(BACKGROUND);
    if (buttonTick(&quit))
      scene = SceneMenu;
    boardUiTick(&board_ui, &board);
    EndDrawing();

    if (WindowShouldClose())
      scene = SceneQuit;
    if (board_ui.state == BoardUiMove) {
      doMove(&board, board_ui.move);
      board_ui.state = BoardUiNone;
    }
  }
  buttonDeinit(&quit);
  return scene;
}
