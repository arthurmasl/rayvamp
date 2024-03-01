#ifndef ENEMY_H
#define ENEMY_H

#include "consts.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"

typedef struct {
  Vector2 pos;
  Vector2 vel;
  float dir;
} Enemy;

Enemy createEnemy(Player *player);
void createEnemies(Player *player);
void drawEnemies();
void updateEnemies(Bullet *bullets, Player *player);
void drawEnemy(Enemy *enemy);

#endif /* ENEMY_H */
