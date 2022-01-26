#include "bullet.h"
#include "globals.h"
#include "renderable.h"
#include "rendersystem.h"
#include <SDL2/SDL.h>
#include "position.h"

//DEBUG
#include <iostream>

void RenderSystem::init()
{
    //gCoordinator.AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));
    std::cout << "RenderSystem init()" << std::endl;
}

void renderAll(SDL_Renderer* renderer, entt::registry* ecs) {
    SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xaa, 0xaa, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer); //Start by clearing the screen

    //Render bullets
    {
        entt::view view = ecs->view<Bullet>();
        for (entt::entity bullet: view) {
            Bullet& b = view.get<Bullet>(bullet);
            b.draw(renderer);
        }
    }
    //Render all renderable entities
    entt::view view = ecs->view<Renderable, Position>();
    for (entt::entity entity : view) {
        auto r = view.get<Renderable>(entity);
        auto p = view.get<Position>(entity);
        SDL_Rect dest;
        dest.x = p.x-r.sprite.offsetX;
        dest.y = p.y-r.sprite.offsetY;
        dest.w = r.sprite.rect.w;
        dest.h = r.sprite.rect.h;
        //SDL_RenderCopy(renderer, renderable.sprite.spritesheet, &(renderable.sprite.rect), &dest);
        //Render entity's sprite to screen, with rotation around the sprite's center
        SDL_RenderCopyEx(gRenderer, r.sprite.spritesheet, &(r.sprite.rect), &dest, p.rotation, NULL, SDL_FLIP_NONE);
    }
    
    //Push the current frame to the screen
    SDL_RenderPresent(gRenderer);
}
