#ifndef COLISIONABLE_H
#define COLISIONABLE_H

#include<iostream>
#include"SFML/Graphics.hpp"
using namespace std;
using namespace sf;


class Colisionable{
    public:
        virtual FloatRect getBounds() const = 0;
        bool colisiona(Colisionable & ente)const{
            return getBounds().intersects(ente.getBounds());
        }

};
#endif // COLISIONABLE_H