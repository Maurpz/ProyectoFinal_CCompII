#ifndef INTF_EXPENDEDORAS_H
#define INTF_EXPENDEDORAS_H
#include"Colisionable.h"
#include"Intf_Jugador.h"
#include<chrono>
#include<memory>

class Intf_Expendedoras : public Colisionable , public Drawable{
    protected:
        Sprite spriteMaquina;
        chrono::time_point<chrono::steady_clock> tiempoAnterior;
        chrono::time_point<chrono::steady_clock> tiempoActual;
        int intervalo;
    public:
        Intf_Expendedoras(shared_ptr<Texture> textura,int _x,int _y,int lado){
            spriteMaquina.setTexture(*textura);
            tiempoAnterior=chrono::steady_clock::now();
            spriteMaquina.setPosition(_x*lado,_y*lado);
        }
        virtual ~Intf_Expendedoras(){}
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
        virtual void interactua(unique_ptr<Intf_Jugador> & jugador)=0;

        FloatRect getBounds() const override{
            return spriteMaquina.getGlobalBounds();
        }
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(spriteMaquina,states);
        }

};
#endif // INTF_EXPENDEDORAS_H