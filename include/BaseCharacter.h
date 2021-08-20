#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter {
public:
    BaseCharacter();
    void undoMovement();
    virtual void tick(float dt);
    virtual Vector2 getScreenPos() = 0;
    Vector2 getWorldPos() { return worldPos; }
    Rectangle getCollisionRec();
    bool isAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
protected:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity;
    float rightLeft{ 1.0f };
    float runningTime{};
    int frame{};
    int maxFrames{ 6 };
    float updateTime{ 1.f / 12.f };
    float speed{ 4.f };
    float width{};
    float height{};
    float scale{ 4.0f };
private:
    bool alive{ true };
};

#endif