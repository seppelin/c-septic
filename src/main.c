#include "raylib.h"
#include "ui.h"
#include <stdio.h>

int main(void) {
	InitWindow(1600, 900, "septic");
	Button b = buttonInitText(10, 10, "hellox", 50, DARKPURPLE);
	int quit = 0;
	printf("yay!");
	while(!quit && !WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		quit = buttonTick(&b);
		EndDrawing();
	}
	buttonDeinit(&b);
	return 0;
}
