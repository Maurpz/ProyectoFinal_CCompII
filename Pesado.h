#ifndef PESADO_H
#define PESADO_H

#include"SFML/Graphics.hpp"
#include <iostream>
#include<memory>
using namespace sf;
using namespace std;

class Pesado{
    private:
        shared_ptr<Texture> textura;
        string tipo;
    public:
        Pesado(string url,string _tipo){
            textura=make_shared<Texture>();
            tipo=_tipo;
            textura->loadFromFile(url);
        }
        bool mismoTipo(string _tipo){
            if(tipo==_tipo){
                return true;
            }
            else{
                return false;
            }
        }
    shared_ptr<Texture> getInstancia(){
        return textura;
    }

};
#endif PESADO_H