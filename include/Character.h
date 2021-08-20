#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"

class Character : public BaseCharacter {
public:
    Character(int winWidth, int winHeight);
    virtual Vector2 getScreenPos() override;
    virtual void tick(float dt) override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{ LoadTexture("characters/weapon_sword.png") };
    Rectangle weaponCollisionRec;
    float health{ 100.0f };
};

#endif // CHARACTER_H