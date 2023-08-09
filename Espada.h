#ifndef ESPADA_H
#define ESPADA_H
#include"Intf_Arma.h"

class Espada : public Intf_Arma{
    private:
        float anguloRotacion=0;
    public:
        Espada(){
            textura.loadFromFile("Assets/espada1.png");
            spriteArma.setTexture(textura);
            spriteArma.setOrigin(8,35);
        }
        
        void setPosicion(Vector2f pos)override{
            spriteArma.setPosition(pos.x+20,pos.y);
        }
        void atacar(RenderWindow & w,vector<unique_ptr<Proyectil>> & disparos, FlyFactory * _fabrica,Vector2f jugador)override{
            if(Mouse::isButtonPressed(Mouse::Left)){
                if(spriteArma.getRotation()<=90.f){
                    anguloRotacion+=20.f;
                    spriteArma.setRotation(anguloRotacion);
                }
            }
            else{
                anguloRotacion=0;
                spriteArma.setRotation(anguloRotacion);
            }
        }
};
#endif // ESPADA_H

/*
        void atacar(Event & event)override{
            if(event.type == Event::MouseButtonPressed){
                if(spriteArma.getRotation()<=90.f){
                    anguloRotacion+=20.f;
                    spriteArma.setRotation(anguloRotacion);
                }
            }
            else if(event.type ==Event::MouseButtonReleased){
                anguloRotacion=0;
                spriteArma.setRotation(anguloRotacion);
            }
        }

*/