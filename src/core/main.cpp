#include <dlfcn.h>
#include <iostream>
#include "../graphical_lib/abstract_graphical_lib.h"
#include "../game_logic/game.cpp"
#include <SFML/Window/Keyboard.hpp>

typedef AbstractGraphicalLib* create_t();
typedef void destroy_t(AbstractGraphicalLib*);

void displayMenu() {
    std::cout << "1. Lancer mon jeu\n";
    std::cout << "2. Afficher les scores (Non implémenté)\n";
    std::cout << "3. Quitter le menu\n";
    std::cout << "Veuillez entrer votre choix: ";
}

int main(int argc, char *argv[]) {

    //qjjouter sdl2
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <graphical_lib.so>" << std::endl;
        return 1;
    }

    int choice = 0;
    while(choice != 3) {
        displayMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                void *handle = dlopen(argv[1], RTLD_LAZY);
                if (!handle) {
                    std::cerr << "Error loading library: " << dlerror() << std::endl;
                    return 1;
                }

                create_t* create = (create_t*)dlsym(handle, "create");
                if (!create) {
                    std::cerr << "Error finding symbol create: " << dlerror() << std::endl;
                    dlclose(handle);
                    return 1;
                }

                destroy_t* destroy = (destroy_t*)dlsym(handle, "destroy");
                if (!destroy) {
                    std::cerr << "Error finding symbol destroy: " << dlerror() << std::endl;
                    dlclose(handle);
                    return 1;
                }

                AbstractGraphicalLib *graphicalLib = create();
                graphicalLib->initialize();

                Game game;

                while (true) {
                    bool keys[sf::Keyboard::KeyCount] = {false};
                    for (int key = 0; key < sf::Keyboard::KeyCount; ++key) {
                        keys[key] = graphicalLib->isKeyPressed(key);
                    }

                    game.handleInput(keys);

                    graphicalLib->render(game.getPlayerX(), game.getPlayerY());

                    if (graphicalLib->isKeyPressed(sf::Keyboard::Escape)) {
                        break;
                    }
                }

                destroy(graphicalLib);
                dlclose(handle);

                break;
            }
            case 2:
                // Implémentez la logique pour afficher les scores ici
                std::cout << "Affichage des scores (à implémenter)...\n";
                break;
            case 3:
                break;
            default:
                std::cout << "Choix invalide, veuillez réessayer.\n";
        }
    }

    return 0;
}
