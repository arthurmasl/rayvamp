#include "enemy.h"
#include "consts.h"
#include <raylib.h>
#include <raymath.h>

#define ORC_SIZE 48
#define ORC_COUNT 6
#define ORC_FPS 10
#define ORC_TIME 1.0f / ORC_FPS

Texture2D orc;
int orcIndex = 0;
float orcTimer = ORC_TIME;

bool loaded = false;

Enemy createEnemy(Player *player) {
  if (!loaded) {
    orc = LoadTexture("resources/orc/D_Walk.png");
    loaded = true;
  }
  Vector2 pos = {GetRandomValue(-1500, 1500), GetRandomValue(-1500, 1500)};
  Vector2 center = {(int)(screenWidth / 2), (int)(screenHeight / 2)};

  return (Enemy){.pos = pos, .dir = 0, .vel = 0};
}

void drawEnemy(Enemy *enemy) {
  // DrawRectangle(enemy->pos.x, enemy->pos.y, PLAYER_SIZE, PLAYER_SIZE, GRAY);
  Rectangle source = {ORC_SIZE * orcIndex, 0, ORC_SIZE, ORC_SIZE};
  Rectangle dest = {ORC_SIZE / 2.0f, ORC_SIZE / 2.0f, source.width,
                    source.height};
  Vector2 origin = (Vector2){enemy->pos.x, enemy->pos.y};
  DrawTexturePro(orc, source, dest, origin, 0, WHITE);
}

#define ENEMIES_COUNT 1000
Enemy enemies[ENEMIES_COUNT];
void createEnemies(Player *player) {
  for (int i = 0; i < ENEMIES_COUNT; i++) {
    enemies[i] = createEnemy(player);
  }
}

void updateEnemies(Bullet *bullets, Player *player) {
  orcTimer -= GetFrameTime();
  if (orcTimer <= 0) {
    orcTimer = ORC_TIME;
    orcIndex++;
  }

  for (int i = 0; i < ENEMIES_COUNT; i++) {
    Vector2 direction = {player->pos.x - enemies[i].pos.x,
                         player->pos.y - enemies[i].pos.y};
    Vector2 velocity = {direction.x * 0.001, direction.y * 0.001};

    enemies[i].pos.x += velocity.x;
    enemies[i].pos.y += velocity.y;

    // for (int j = 0; j < MAX_BULLETS; j++) {
    //   if (bullets[j].active &&
    //       CheckCollisionCircleRec(
    //           bullets[j].pos, 20,
    //           (Rectangle){enemies[i].pos.x, enemies[i].pos.y, PLAYER_SIZE}))
    //           {
    //
    //     {
    //       enemies[i] = createEnemy(player);
    //       bullets[j].active = false;
    //       player->exp += 5;
    //     }
    //   }
    // }
  }
}

void drawEnemies() {
  for (int i = 0; i < ENEMIES_COUNT; i++) {
    Enemy enemy = enemies[i];
    drawEnemy(&enemy);
  }
}
