#ifndef INTF_ARMA_H
#define INTF_ARMA_H
#include"SFML/Graphics.hpp"
#include"Colisionable.h"
#include"Proyectil.h"
#include"FlyFactory.h"
#include<chrono>
#include<memory>
#include<vector>

class Intf_Arma :public Drawable , public Colisionable{
    protected:
        Texture textura;
        Sprite spriteArma;
        chrono::time_point<chrono::steady_clock> tiempoAnterior;
        chrono::time_point<chrono::steady_clock> tiempoActual;
        int intervalo;
    public:
        Intf_Arma(){}
        virtual void atacar(RenderWindow & w,vector<unique_ptr<Proyectil>> & disparos,FlyFactory  * _fabrica,Vector2f jugador)=0;
        virtual void setPosicion(Vector2f pos)=0;

        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(spriteArma,states);
        }
        FloatRect getBounds() const override{
            return spriteArma.getGlobalBounds();
        }
                void setTiempoActual(){
            tiempoActual=chrono::steady_clock::now();
        }
        bool disponible(){
            auto diferencia=chrono::duration_cast<chrono::milliseconds>(tiempoActual - tiempoAnterior).count();
            if(diferencia>=intervalo){
                return true;
            }
            return false;
        }
};
#endif //INTF_ARMA_H