#ifndef PLAYER_H
#define PLAYER_H

#include "consts.h"
#include "raylib.h"
#include "raymath.h"

typedef struct {
  Vector2 pos;
  Vector2 vel;
  float dir;
  int exp;
} Player;

typedef struct {
  Vector2 pos;
  Vector2 vel;
  bool active;
} Bullet;

Player createPlayer();
void updatePlayer(Player *player, float frametime, Camera2D camera,
                  Bullet bullets[]);
void drawPlayer(Player *player, Bullet bullets[]);

#endif /* PLAYER_H */
