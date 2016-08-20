//NEED TO ADD A HEADER GUARD

//TODO am I supposed to include this here?
#include "defines.h"

typedef class Character
{
    public:
        Character();
        Character(int, int);
        int get_pos_x(void);
        int get_pos_y(void);
        void set_pos(int, int);
        void move(void);
        void rotate(sf::RenderWindow*, sf::Mouse*);
        sf::Sprite get_sprite(void);
        void set_movement(int, int=SPEED);
    private:
        void init(void);
        int movement[MOVEMENT_KEYS];
        sf::Texture texture;
        sf::Sprite sprite;
} Character;

