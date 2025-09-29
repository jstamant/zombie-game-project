#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <entt/entt.hpp>
#include <string>

class RenderSystem
{
public:
  RenderSystem(SDL_Renderer*, entt::registry*);
  SDL_Texture *load_image(std::string);
  SDL_Surface *load_surface_from_text(std::string);
  void renderAll(void);

private:
  SDL_Point camera_;
  entt::registry *ecs_;
  SDL_Renderer *renderer_;
  SDL_Texture *spritesheet_;
  TTF_Font *font_;
  SDL_Color text_color;
  struct {
    SDL_Surface *health_indicator;
    SDL_Surface *health;
    SDL_Surface *ammo_indicator;
    SDL_Surface *ammo;
  } ui;
};

#endif //_RENDERSYSTEM_H_
