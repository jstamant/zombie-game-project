//************************************************
// main.cpp
//************************************************

//Include SFML dependencies
#include <SFML/Graphics.hpp>

//Include std dependencies
#include <stdlib.h>
#include <time.h>

//Include dependencies
#include "character.h"
#include "collisionmanager.h"
#include "defines.h"
#include "enemy.h"
#include "entitymanager.h"
#include "inputhandler.h"
#include "map.h"
#include "messagebus.h"
#include "pickup.h"
#include "solid.h"
#include "userinterface.h"

//Make these references global for now... :/
Character* g_character = NULL;
sf::View globalView;
sf::RenderWindow* globalWindow;

int main()
{
    srand(time(NULL));
    //Define core resources
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_CAPTION);
    globalWindow = &window;
    globalView = sf::View(sf::FloatRect(100, 100, WINDOW_WIDTH, WINDOW_HEIGHT));
    sf::Mouse mouse;

    EntityManager entitymanager(&window, &mouse);
    Map map("test.tmx", &entitymanager);
    InputHandler inputHandler(&window);
    inputHandler.addObserver(&entitymanager);
    CollisionManager collisionManager;
    entitymanager.addObserver(&collisionManager);

    MessageBus messageBus;
    messageBus.registerSystem(&entitymanager);
    messageBus.registerSystem(&collisionManager);

    window.setFramerateLimit(FRAMELIMIT);

    //Create some test entities
    entitymanager.new_entity(new Character(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
    entitymanager.new_entity(new UserInterface);
    entitymanager.new_entity(new Solid(100, 100));
    long unsigned int enemy_spawn = 0;
    long unsigned int pickup_spawn = 0;

    //Run the game
    while (window.isOpen())
    {
        //Process input
        inputHandler.handle_input();

        //Perform game logic
        collisionManager.checkAllCollisions();
        collisionManager.processCollisions();
        entitymanager.update_all();

        //DEBUG
        if (enemy_spawn++ >= 100) {
            entitymanager.new_entity(new Enemy(WINDOW_WIDTH+32,rand()%WINDOW_HEIGHT));
            enemy_spawn = 0;
        }
        if (pickup_spawn++ >= 370) {
            entitymanager.new_entity(new Pickup(rand()%(WINDOW_WIDTH/2),rand()%WINDOW_HEIGHT));
            pickup_spawn = 0;
        }

        //Render
        window.setView(globalView);
        window.clear(sf::Color(192, 192, 192));
        entitymanager.render();

        window.display();
    }

    return 0;
}

