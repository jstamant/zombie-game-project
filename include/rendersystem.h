#ifndef _RENDERSYSTEM_H_
#define _RENDERSYSTEM_H_

#include <entt/entt.hpp>
#include <SDL2/SDL.h>

class RenderSystem
{
public:
    void init(void);
private:
};

void renderAll(SDL_Renderer*, entt::registry*);

#endif //_RENDERSYSTEM_H_
