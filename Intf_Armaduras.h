#ifndef INTF_ARMADURAS_H
#define INTF_ARMADURAS_H

#include "Intf_Jugador.h"
#include "Intf_Bloque.h"
#include<memory>

class Intf_Armaduras:public Intf_Jugador{
    protected:
        unique_ptr<Intf_Jugador> jugador;
    public:
        //constructor y destructor
        Intf_Armaduras(unique_ptr<Intf_Jugador> _jugador){
            this->jugador=move(_jugador);
        }
        virtual ~Intf_Armaduras(){}

        //metodos
        void takeDamage(float danio)override{
            jugador->takeDamage(danio);
        }
        void toString()const override{
            jugador->toString();
        }


        //GET AND SET
        float getVida()const override{
            return jugador->getVida();
        }
        float getEscudo()const override {
            return jugador->getEscudo();
        }
        void setVida(float n_vida)override{
            jugador->setVida(n_vida);
        }

        void addVida(float n_vida) {
            jugador->addVida(n_vida);
        }
        void addEscudo(float n_escudo) {
            jugador->addEscudo(n_escudo);
        }

        void addVelocidad() {
            jugador->addVelocidad();
        }

        //...
        float getArmor()const override{
            return jugador->getArmor()+this->armadura;
        }
        void draw(RenderTarget& target, RenderStates states)const override{
            jugador->draw(target,states);
        }

        virtual FloatRect getBounds() const override{
            return jugador->getBounds();
        }
        void update(View& v,RenderWindow & w,vector<unique_ptr<Proyectil>> & disparos,FlyFactory * fabrica)override{
            jugador->update(v,w,disparos,fabrica);
        }
        virtual Vector2f getPosition()override {
            return jugador->getPosition();
        }
        void detector(Intf_Bloque & r2)override {
            return jugador->detector(r2);
        }


        //herencia



};
#endif // INTF_ARMADURAS_H