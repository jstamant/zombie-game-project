#include <cmath>
#include <SDL2/SDL.h>

#include "defines.h"
#include "globals.h"
#include "line.h"
#include "renderable.h"
#include "rendersystem.h"
#include "sprite.h"
#include "position.h"

//DEBUG
#include <iostream>

void RenderSystem::init()
{
    std::cout << "RenderSystem init()" << std::endl;
}

void renderAll(SDL_Renderer* renderer, entt::registry* ecs) {
    // Start by clearing the screen, filling it with a placeholder color
    SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render all bullets
    {
        auto view = ecs->view<Line>();
        for (entt::entity bullet : view) {
          Line &l = ecs->get<Line>(bullet);
          SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, SDL_ALPHA_OPAQUE); // Yellow
          SDL_RenderDrawLine(renderer, l.x1, l.y1, l.x2, l.y2);
        }
    }
    // Render all entities with sprites
    auto view = ecs->view<Renderable, Position, Sprite>();
    for (entt::entity entity : view) {
        Sprite sprite = view.get<Sprite>(entity);
        Position p = view.get<Position>(entity);
        SDL_Rect dest;
        dest.x = p.x - sprite.offsetX;
        dest.y = p.y - sprite.offsetY;
        dest.w = sprite.rect.w;
        dest.h = sprite.rect.h;
        // Render entity's sprite to screen, with rotation around the sprite's center
        SDL_RenderCopyEx(renderer, sprite.spritesheet, &(sprite.rect), &dest,
                        p.rotation * 180 / M_PI, NULL, SDL_FLIP_NONE);
    }

    //Push the composed frame to the screen
    SDL_RenderPresent(renderer);
}
