#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) {
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    worldPos = pos;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

Vector2 Enemy::getScreenPos() {
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::tick(float dt) {
    if (!isAlive()) return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    if (Vector2Length(velocity) < radius) velocity = {};

    BaseCharacter::tick(dt);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())) {
        target->takeDamage(damagePerSec * dt);
    }
}
