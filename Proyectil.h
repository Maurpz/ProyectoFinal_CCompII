#ifndef PROYECTIL_H
#define PROYECTIL_H
#include"Colisionable.h"
#include<memory>
#include <cmath>
class Proyectil : public Colisionable , public Drawable{
    private:
        int danio;
        Sprite spriteProyectil;
        Vector2f origen;
        Vector2f direccion;
        string tipo;
        bool estadoEliminar=false;
    public:
        Proyectil(shared_ptr<Texture> textura,int danioBala,Vector2f o,Vector2f direct,string _tipo){
            spriteProyectil.setTexture(*textura);
            spriteProyectil.setPosition(o);
            spriteProyectil.setScale(0.5f,0.5f);
            danio=danioBala;
            origen=o;
            direccion=direct;
            tipo=_tipo;
        }
        int getDanio(){
            return danio;
        }
        void detonar(){
			spriteProyectil.move(direccion * 8.f);
        }
        string getTipo(){
            return tipo;
        }
        void primerImpacto(){
            estadoEliminar=true;
        }
        bool getEstado(){
            return estadoEliminar;
        }
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(spriteProyectil,states);
        }
        FloatRect getBounds() const override{
            return spriteProyectil.getGlobalBounds();
        }
};
#endif // PROYECTIL_H