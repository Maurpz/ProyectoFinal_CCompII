#ifndef INTF_BLOQUE_H
#define INTF_BLOQUE_H

#include"SFML/Graphics.hpp"
#include"Colisionable.h"
#include<memory>
class Intf_Bloque : public Colisionable ,public Drawable{
    protected:
        int x;
        int y;
        int duravilidad;
        bool destruir=false;
        Sprite spriteBloque;
        string tipo;
    public:
        Intf_Bloque(shared_ptr<Texture> & textura,int _x,int _y,int lado){
            spriteBloque.setTexture(*textura);
            spriteBloque.setPosition(_x*lado,_y*lado);
            x=_x;
            y=_y;
        }
        virtual ~Intf_Bloque(){}
        FloatRect getBounds() const override {
            return spriteBloque.getGlobalBounds();
        }
        void recibirDanio(float danio){
            duravilidad-=danio;
        }
        string getTipo()const{
            return tipo;
        }
        Vector2f getPosition(){
            return spriteBloque.getPosition();
        }
        void actualizarEstado(){
            if(duravilidad<=0){
                destruir=true;
            }
        }
        bool getEstado(){
            return destruir;
        }
};


#endif // INTF_BLOQUE_H