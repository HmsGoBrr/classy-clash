#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter {
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual Vector2 getScreenPos() override;
    virtual void tick(float dt) override;
    void setTarget(Character* character) { target = character; }
private:
    Character* target;
    float damagePerSec{ 10.0f };
    float radius{ 25.0f };
};


#endif