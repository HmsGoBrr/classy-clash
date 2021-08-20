#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {
}

void BaseCharacter::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
    return Rectangle{ getScreenPos().x, getScreenPos().y, width * scale, height * scale };
}

void BaseCharacter::tick(float dt) {
    worldPosLastFrame = worldPos;

    // Update animation frame
    runningTime += dt;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.0f;
        frame %= maxFrames;
    }

    if (Vector2Length(velocity) != 0.0f) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        rightLeft = velocity.x < 0.0f ? -1.0f : 1.0f;
        texture = run;
    }
    else {
        texture = idle;
    }
    velocity = {};

    DrawTexturePro(
        texture,
        { frame * width, 0.0f, rightLeft * width, height },
        { getScreenPos().x, getScreenPos().y, scale * width, scale * height },
        {},
        0.0f,
        WHITE
    );
}
