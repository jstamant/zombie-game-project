#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <SDL2/SDL_render.h>
#include <entt/entt.hpp>
#include <SDL2/SDL.h>
#include <string>

class RenderSystem
{
public:
  RenderSystem(SDL_Renderer*, entt::registry*);
  void renderAll();

private:
  void init(void);
  SDL_Point camera_;
  entt::registry *ecs_;
  SDL_Renderer *renderer_;
};


bool loadFromRenderedText(std::string, SDL_Color);

#endif //_RENDERSYSTEM_H_
