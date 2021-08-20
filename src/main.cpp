#include "raylib.h"
#include "raymath.h"

#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main() {
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = { 0, 0 };
    const float mapScale = 4.0f;

    Character knight{ windowWidth, windowHeight };

    Prop props[2]{
        Prop{ Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png") },
        Prop{ Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png") }
    };

    Enemy goblin{
        Vector2{800.0f, 300.0f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.0f, 700.0f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{ &goblin, &slime };

    for (Enemy* enemy : enemies) {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

        for (Prop prop : props) {
            prop.Render(knight.getWorldPos());
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) {
                knight.undoMovement();
            }
        }

        if (!knight.isAlive()) {
            DrawText("Game Over!", windowWidth / 2 - MeasureText("Game Over!", 40) / 2, 45.0f, 40, RED);
        }
        else {
            DrawText(TextFormat("Health %.2f", knight.getHealth()), 55.0f, 45.0f, 40, RED);
        }

        knight.tick(dt);
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale) {
            knight.undoMovement();
        }

        for (Enemy* enemy : enemies) {
            enemy->tick(dt);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) {
            for (Enemy* enemy : enemies) {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec())) {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}
