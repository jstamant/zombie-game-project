#ifndef _BULLET_H_
#define _BULLET_H_
//******************************************************************************
// bullet.h
//******************************************************************************

//Include dependencies
#include <SDL2/SDL.h>

// class Bullet: public Entity
class Bullet
{
public:
    SDL_Point source;
    SDL_Point target;
    int ttl;
    double angle;

    void draw(SDL_Renderer*);
//         Bullet(sf::Vector2f, sf::Vector2f);
//         //~Bullet();
//         //Access functions
//         sf::VertexArray get_line(void);
//         void setEndpoint(sf::Vector2f);
//         virtual void update_logic(void);
//         virtual bool is_bullet(void);
//     private:
//         int time_to_live;
//         float slope_;
//         sf::VertexArray line;
//         virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
//         bool checked_collisions;
//         void find_potential_collisions(void);
//         void find_first_collision(void);
//         std::list<Entity*> collision_list;
//         void extend_line(void);
};

#endif //_BULLET_H_
