#include "consts.h"
#include "enemy.h"
#include "player.h"
#include <raylib.h>
#include <stdio.h>

int main() {
  Bullet bullets[MAX_BULLETS] = {};

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "rayvamp");
  SetWindowPosition(1000, 0);
  SetTargetFPS(60);

  Player player = createPlayer();
  createEnemies(&player);

  Camera2D camera = {0};
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.zoom = 0.8f;

  while (!WindowShouldClose()) {
    // update
    float frametime = GetFrameTime();
    updatePlayer(&player, frametime, camera, bullets);
    updateEnemies(bullets, &player);
    camera.target = player.pos;
    // camera.rotation = player.dir;

    // draw
    BeginDrawing();
    ClearBackground((Color){255, 220, 132, 0});

    BeginMode2D(camera);
    drawEnemies();
    drawPlayer(&player, bullets);

    EndMode2D();

    // UI
    DrawFPS(10, 10);
    DrawText("Level: ", 20, screenHeight - 40, 20, BLACK);
    int playerLevel = (player.exp / 100);
    char playerLevelStr[20];
    sprintf(playerLevelStr, "%d", playerLevel);
    DrawText(playerLevelStr, 80, screenHeight - 40, 20, BLACK);

    DrawRectangle(120, screenHeight - 40, 500, 20, GRAY);

    int newWidth = ((player.exp - (playerLevel * 100)) * 490) / 100;
    DrawRectangle(125, screenHeight - 35, newWidth, 10, GREEN);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
