#ifndef BLOC
#define BLOC
#include <SFML/Graphics.hpp>
class bloc{
public:
    sf::RectangleShape forma;
    bool alive;

    void update_texture(int matrice[100][100]);
};

#endif // BLOC
