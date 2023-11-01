#include <SDL2/SDL_render.h>
#include <cmath>
#include <SDL2/SDL.h>

#include "controllable.h"
#include "defines.h"
#include "globals.h"
#include "hitbox.h"
#include "line.h"
#include "renderable.h"
#include "rendersystem.h"
#include "sprite.h"
#include "position.h"

//DEBUG
#include <iostream>

RenderSystem::RenderSystem(SDL_Renderer* renderer, entt::registry* registry) {
  init();
  renderer_ = renderer;
  ecs_ = registry;
  camera_ = {0, 0};
}

void RenderSystem::init()
{
    std::cout << "RenderSystem init() (does nothing)" << std::endl;
}

void RenderSystem::renderAll() {
    // TODO need to implement some global coordinates and camera coordinates system
    // Start by clearing the screen, filling it with a placeholder color
    SDL_SetRenderDrawColor(renderer_, 0xaa, 0xaa, 0xaa, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);

    // Get player coordinates for the camera
    entt::entity player = ecs_->view<Controllable>().front();
    if (ecs_->valid(player)) {
      Position p = ecs_->get<Position>(player);
      camera_ = {(int)p.x, (int)p.y};
    }

    // Render all bullets
    {
        auto view = ecs_->view<Line>();
        for (entt::entity bullet : view) {
          Line &l = ecs_->get<Line>(bullet);
          SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0x00, SDL_ALPHA_OPAQUE); // Yellow
          SDL_RenderDrawLine(renderer_, l.x1 - camera_.x + WINDOW_WIDTH / 2,
                             l.y1 - camera_.y + WINDOW_HEIGHT / 2,
                             l.x2 - camera_.x + WINDOW_WIDTH / 2,
                             l.y2 - camera_.y + WINDOW_HEIGHT / 2);
        }
    }
    // Render all entities with sprites
    auto view = ecs_->view<Renderable, Position, Sprite>();
    for (entt::entity entity : view) {
        Sprite sprite = view.get<Sprite>(entity);
        Position p = view.get<Position>(entity);
        SDL_Rect dest;
        dest.x = (int)p.x - (int)sprite.offsetX - camera_.x + WINDOW_WIDTH / 2;
        dest.y = (int)p.y - (int)sprite.offsetY - camera_.y + WINDOW_HEIGHT / 2;
        dest.w = sprite.rect.w;
        dest.h = sprite.rect.h;
        // Render entity's sprite to screen, with rotation around the sprite's center
        SDL_RenderCopyEx(renderer_, sprite.spritesheet, &(sprite.rect), &dest,
                        p.rotation * 180 / M_PI, NULL, SDL_FLIP_NONE);
    }

    // DEBUG render a rectangle for orienting yourself while I add a camera
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_Rect bounds1 = {-10, -10, WINDOW_WIDTH+20, WINDOW_HEIGHT+20};
    SDL_Rect bounds2 = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Rect bounds3 = {10, 10, WINDOW_WIDTH - 20, WINDOW_HEIGHT - 20};
    bounds1.x -= camera_.x - WINDOW_WIDTH/2;
    bounds1.y -= camera_.y - WINDOW_HEIGHT/2;
    bounds2.x -= camera_.x - WINDOW_WIDTH/2;
    bounds2.y -= camera_.y - WINDOW_HEIGHT/2;
    bounds3.x -= camera_.x - WINDOW_WIDTH/2;
    bounds3.y -= camera_.y - WINDOW_HEIGHT/2;
    SDL_RenderDrawRect(renderer_, &bounds1);
    SDL_RenderDrawRect(renderer_, &bounds2);
    SDL_RenderDrawRect(renderer_, &bounds3);

    // TESTING render text to screen
    SDL_Rect src = {0, 0, WINDOW_WIDTH, 50};
    SDL_Rect dest = {0, 0, WINDOW_WIDTH, 50};
    SDL_RenderCopy(renderer_, gTextTexture, &src, &dest);

    //Push the composed frame to the screen
    SDL_RenderPresent(renderer_);
}

/* TODO I need to improve the loading of surfaces/textures. It's a mess, right
   now. And I need to make my own class for texture, along with member
   functions. */
bool loadFromRenderedText(std::string textureText, SDL_Color textColor) {
  // Get rid of preexisting texture
  // free();
  // Render text surface
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
  } else {
    // Create texture from surface pixels
    gTextTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (gTextTexture == NULL) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n",
             SDL_GetError());
    } else {
      // Get image dimensions
      // mWidth = textSurface->w;
      // mHeight = textSurface->h;
    }

    // Get rid of old surface
    // SDL_FreeSurface(textSurface);
  }

  // Return success
  return gTextTexture != NULL;
}
