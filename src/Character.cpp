#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :windowWidth(winWidth), windowHeight(winHeight) {
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos() {
    return Vector2{
        windowWidth / 2.0f - scale * (0.5f * width),
        windowHeight / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float dt) {
    if (!isAlive()) return;

    if (IsKeyDown(KEY_A)) velocity.x -= 1.0f;
    if (IsKeyDown(KEY_D)) velocity.x += 1.0f;
    if (IsKeyDown(KEY_W)) velocity.y -= 1.0f;
    if (IsKeyDown(KEY_S)) velocity.y += 1.0f;

    BaseCharacter::tick(dt);

    Vector2 origin{};
    Vector2 offset{};
    float rotation;
    if (rightLeft > 0.0f) {
        origin = { 0.0f, weapon.height * scale };
        offset = { 35.0f, 55.0f };
        weaponCollisionRec = {
            getCollisionRec().x + offset.x,
            getCollisionRec().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };

        (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE)) ? rotation = 35.0f : rotation = 0;
    }
    else {
        origin = { weapon.width * scale, weapon.height * scale };
        offset = { 25.0f, 55.0f };
        weaponCollisionRec = {
            getCollisionRec().x + offset.x - weapon.width * scale,
            getCollisionRec().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };

        (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE)) ? rotation = -35.0f : rotation = 0;
    }

    DrawTexturePro(
        weapon,
        { 0.0f, 0.0f, (float)weapon.width * rightLeft, (float)weapon.height },
        { getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale },
        origin,
        rotation,
        WHITE
    );

    // Draw Weapon Collision Rectangle (for debugging)
    // DrawRectangleLines(
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED
    // );
}

void Character::takeDamage(float damage) {
    health -= damage;
    if (health <= 0.0f) setAlive(false);
}
