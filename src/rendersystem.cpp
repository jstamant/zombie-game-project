#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>
#include <string>

#include "controllable.h"
#include "defines.h"
#include "globals.h"
#include "hitbox.h"
#include "line.h"
#include "position.h"
#include "renderable.h"
#include "rendersystem.h"
#include "sprite.h"

RenderSystem::RenderSystem(SDL_Renderer *renderer, entt::registry *registry) {
  renderer_ = renderer;
  ecs_ = registry;
  camera_ = {0, 0};

  spritesheet_ = loadTexture("spritesheet.png");
  if (spritesheet_ == NULL) // Not sure if this works as intended
    std::cout << "Failed to load spritesheet" << std::endl;
  std::cout << "Loaded spritesheet successfully" << std::endl;
  // TODO - NEED TO FREE THIS TEXTURE ON DESTRUCTION
}

SDL_Texture *RenderSystem::loadTexture(std::string path) {
  SDL_Texture *texture = NULL;
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (surface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    texture =
        SDL_CreateTextureFromSurface(game.get_renderer(), surface);
    if (texture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }
    SDL_FreeSurface(surface);
  }
  return texture;
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
        dest.x = (int)p.x - (int)sprite.offset.x - camera_.x + WINDOW_WIDTH / 2;
        dest.y = (int)p.y - (int)sprite.offset.y - camera_.y + WINDOW_HEIGHT / 2;
        dest.w = sprite.rect.w;
        dest.h = sprite.rect.h;
        // Render entity's sprite to screen, with rotation around the sprite's center
        SDL_RenderCopyEx(renderer_, spritesheet_, &(sprite.rect), &dest,
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
    gTextTexture = SDL_CreateTextureFromSurface(game.get_renderer(), textSurface);
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
