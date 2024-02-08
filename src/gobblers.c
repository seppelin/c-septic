#include "gobblers.h"

#include "gobblers/board.h"
#include "gobblers/ui.h"
#include "raylib.h"
#include "ui.h"

Scene gobRun() {
  Button quit = buttonInitText(10, 10, "Back", 25, PURPLE);
  Board board = boardInit();
  BoardUi board_ui = boardUiInit(500, 200);
  Scene scene = SceneNone;
  int ingame = 1;

  while (scene == SceneNone) {
    BeginDrawing();
    ClearBackground(BACKGROUND);
    boardUiDraw(&board_ui, &board);
    if (buttonTick(&quit))
      scene = SceneMenu;
    EndDrawing();

    if (ingame)
      boardUiUpdate(&board_ui, &board);
    if (board_ui.state == BoardUiMove) {
      doMove(&board, board_ui.move);
      if (getState(board.layers, !board.sign))
        ingame = 0;
      board_ui.state = BoardUiNone;
    }
    if (WindowShouldClose())
      scene = SceneQuit;
  }
  buttonDeinit(&quit);
  return scene;
}
