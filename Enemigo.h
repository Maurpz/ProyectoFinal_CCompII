#ifndef ENEMIGO_H
#define ENEMIGO_H
#include"Colisionable.h"
#include<memory>
#include"Proyectil.h"
#include"FlyFactory.h"
#include<chrono>
class Enemigo : public Colisionable, public Drawable{
    private:
        Sprite spriteEnemigo;
        float velocidadX=3.f;
        bool cambiarDireccion=true;
        chrono::time_point<chrono::steady_clock> tiempoAnterior;
        chrono::time_point<chrono::steady_clock> tiempoActual;
        int intervalo;
    public:
        Enemigo(shared_ptr<Texture> textura,int _intervalo=500){
            spriteEnemigo.setTexture(*textura);
            spriteEnemigo.setPosition(50,-100);
            spriteEnemigo.setScale(3,3);
            tiempoAnterior = chrono::steady_clock::now();
            intervalo = _intervalo;
        }
        void setTiempoActual(){
            tiempoActual=chrono::steady_clock::now();
        }
        Vector2f gePosition(){
            return spriteEnemigo.getPosition();
        }
        bool disponible(){
            auto diferencia=chrono::duration_cast<chrono::milliseconds>(tiempoActual - tiempoAnterior).count();
            if(diferencia>=intervalo){
                return true;
            }
            return false;
        }
        ~Enemigo(){}
        void mover(){
            if (spriteEnemigo.getPosition().x >= 750) {
                cambiarDireccion = false;
            } else if (spriteEnemigo.getPosition().x <= 50) {
                cambiarDireccion = true;
            }
            float moverX = cambiarDireccion ? velocidadX : -velocidadX;
            spriteEnemigo.move(moverX,0);
        }
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(spriteEnemigo,states);
        }

        FloatRect getBounds() const override{
            return spriteEnemigo.getGlobalBounds();
        }
        void atacar(vector<unique_ptr<Proyectil>> & proyectiles,FlyFactory * _fabrica){
            setTiempoActual();
            if(disponible()){
                Vector2f pos=spriteEnemigo.getPosition()+Vector2f(24,16);
                proyectiles.emplace_back(make_unique<Proyectil>(_fabrica->getInstancia("lazer"),250,pos,Vector2f(0,1),"enemigas"));
                tiempoAnterior=tiempoActual;
            }
        }
/*
        unique_ptr<LazerEnemigo> getLazers( FlyFactory & fabrica){
            tiempoAnterior=tiempoActual;
            auto aux= make_unique<LazerEnemigo>(fabrica);
            aux->posicionarProyectil(spriteEnemigo.getPosition(),Vector2f(0,0));
            return move(aux);
        }
*/

};
#endif //ENEMIGO_H