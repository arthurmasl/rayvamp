#include "player.h"
#include "consts.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

Player createPlayer() {
  return (Player){.pos = {0, 0}, .dir = 0.0, .vel = {0, 0}, .exp = 100};
}

void updatePlayer(Player *player, float frametime, Camera2D camera,
                  Bullet *bullets) {
  // controls
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    player->vel.y -= PLAYER_SPEED;
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    player->vel.y += PLAYER_SPEED;
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    player->vel.x += PLAYER_SPEED;
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    player->vel.x -= PLAYER_SPEED;

  player->vel.x *= PLAYER_FRICTION;
  player->vel.y *= PLAYER_FRICTION;

  // reset
  if (IsKeyPressed(82)) {
    printf("reset\n");
    player->pos = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    player->vel = (Vector2){0, 0};
  }

  // mouse controls
  // if (IsMouseButtonDown(0)) {
  //   player->vel = Vector2Add(
  //       player->vel,
  //       Vector2Scale(Vector2Rotate((Vector2){1, 0}, player->dir * DEG2RAD),
  //                    800 * frametime));
  // } else {
  //   player->vel = Vector2Zero();
  // }

  // update
  Vector2 mousePos = GetMousePosition();
  float dx = mousePos.x - screenWidth / 2.0f;
  float dy = mousePos.y - screenHeight / 2.0f;
  float angle = atan2(dy, dx) * RAD2DEG;

  player->pos = Vector2Add(player->pos, Vector2Scale(player->vel, frametime));
  player->dir = angle;

  // shoot
  if (IsMouseButtonPressed(0)) {
    float bulletAngle = atan2f(mousePos.y - screenHeight / 2.0f,
                               mousePos.x - screenWidth / 2.0f);

    for (int i = 0; i < MAX_BULLETS; i++) {
      if (!bullets[i].active) {
        bullets[i] = (Bullet){
            player->pos,
            (Vector2){cosf(bulletAngle) * 12, sinf(bulletAngle) * 12}, true};
        ;
        break;
      }
    }
    // int bulletsCount = sizeof(bullets) / sizeof(bullets[0]);
  }

  // bullet update
  for (int i = 0; i < MAX_BULLETS; i++) {
    Bullet *bullet = &bullets[i];
    bullet->pos.x += bullet->vel.x;
    bullet->pos.y += bullet->vel.y;

    // if (bullet->pos.x > screenWidth * 3 || bullet->pos.x < 0 ||
    //     bullet->pos.y > screenHeight * 3 || bullet->pos.y < 0) {
    //   bullet->active = false;
    // }
  }
}

void drawPlayer(Player *player, Bullet *bullets) {
  // bullets
  for (int i = 0; i < MAX_BULLETS; i++) {
    Bullet bullet = bullets[i];
    if (bullet.active) {
      DrawCircleV(bullet.pos, 5, RED);
    }
  }

  // player
  Rectangle playerRectangle = {player->pos.x, player->pos.y, PLAYER_SIZE,
                               PLAYER_SIZE, BLACK};
  Vector2 playerCenter = {PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f};
  DrawRectanglePro(playerRectangle, playerCenter, player->dir, BLACK);
}
