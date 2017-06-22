#ifndef CARTE_COLLISION_H
#define CARTE_COLLISION_H
#include <../SFML-2.4.2/include/SFML/Graphics.hpp>



class carte_collision
{
public:
    carte_collision();
    virtual ~carte_collision();
    void load_all_image();
    bool get_collision(int x,int y,int direction);
    void void_presence(int x,int y);
    void presence(int x,int y);

protected:

private:
    sf::Image collision;
};

#endif // CARTE_COLLISION_H
