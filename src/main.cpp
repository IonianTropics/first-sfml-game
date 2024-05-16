#include "Game.h"

int main() {
    game::Game game;
    sf::RenderWindow window = sf::RenderWindow{ { 512u, 256u }, "First Game" };
    window.setFramerateLimit(60);
    game.run(&window);
    
    return EXIT_SUCCESS;
}
