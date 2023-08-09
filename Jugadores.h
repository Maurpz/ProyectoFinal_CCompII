#ifndef JUGADORES_H
#define JUGADORES_H

#include"Intf_Jugador.h"
#include"Intf_Bloque.h"
#include"Escopeta.h"
#include"Pistola.h"
#include"Espada.h"
#include<iostream>
using namespace std;

class Jugadores:public Intf_Jugador{
    public:
        //constructores y destructor
        Jugadores(float _vida, string _nombre){
            this->vida=_vida;
            this->nombre=_nombre;
            this->textura.loadFromFile("Assets/LargeEliteKnight_Idle_1.png");
            this->sprite.setTexture(textura);
            this->sprite.setPosition(100.f, 100.f);
            this->sprite.setScale(1.5f,1.5f);
            this->sprite.setOrigin(8.f, 23.5f);
            lista_de_Armas[2]=make_shared<Espada>();
            lista_de_Armas[1]=make_shared<Pistola>();
            lista_de_Armas[0]=make_shared<Escopeta>();
            armaLista=lista_de_Armas[0];

        }
        ~Jugadores(){}


        //Metodos
        void takeDamage(float danio)override{
            if(escudo>0){
                escudo-=danio;
                if(escudo<0){
                    vida-=escudo;
                    escudo=0;
                }
            }
            else{
                vida-=danio;
            }
        }
        void toString()const override{
            cout << "Mi nombre es : " <<nombre << " y tenbgo de vida : " <<vida <<" escudo : " << escudo << endl;
        }


        //GET AND SET
        float getVida()const override{
            return this->vida;
        }
        float getEscudo()const override {
            return this->escudo;
        }
        void addVida(float n_vida)override{
            this->vida = vida + n_vida;
        }
        void addEscudo(float n_escudo)override {
            this->escudo = escudo + n_escudo;
        }
        void setVida(float n_vida)override {
            this->vida = n_vida;
        }
        void addVelocidad() {
            velocidad += 0.01f;
        }


        //...
        float getArmor()const override{
            return 0;
        }

        //dibujar
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(sprite,states);
            target.draw(*armaLista,states);
        }
        FloatRect getBounds() const override{
            return sprite.getGlobalBounds();
        }

        void update(View& v,RenderWindow & w,vector<unique_ptr<Proyectil>> & disparos,FlyFactory * fabrica)override{
            //eventos teclado movimineto
            Vector2f mover = { 0,0 };
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                mover.y = -velocidad;
            }
            else if (Keyboard::isKeyPressed(Keyboard::S)) {
                mover.y = +velocidad;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                mover.x = +velocidad;
            }
            else if (Keyboard::isKeyPressed(Keyboard::A)) {
                mover.x = -velocidad;
            }
            //eventos Teclado Armas
            if(Keyboard::isKeyPressed(Keyboard::Num1)){
                if(armaLista!=lista_de_Armas[0]){
                    armaLista=lista_de_Armas[0];
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Num2)){
                if(armaLista!=lista_de_Armas[1]){
                    armaLista=lista_de_Armas[1];
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Num3)){
                if(armaLista!=lista_de_Armas[2]){
                    armaLista=lista_de_Armas[2];
                }
            }
            //mueve el sprite y la vista
            armaLista->atacar(w,disparos,fabrica,sprite.getPosition());
            sprite.move(mover);
            v.setCenter(sprite.getPosition());
            armaLista->setPosicion(sprite.getPosition());

        }
        virtual Vector2f getPosition()override {
            return sprite.getPosition();
        }

        void detector(Intf_Bloque & r2) override{
            if (colisiona(r2)) {
                FloatRect f_r1 = getBounds();
                FloatRect f_r2 = r2.getBounds();

                float solapaminetoX = min(f_r1.left + f_r1.width, f_r2.left + f_r2.width) - max(f_r1.left, f_r2.left);
                float solapaminetoY = min(f_r1.top + f_r1.height, f_r2.top + f_r2.height) - max(f_r1.top, f_r2.top);

                if (solapaminetoX < solapaminetoY) {
                    if (f_r1.left < f_r2.left) {
                        sprite.move(-solapaminetoX, 0);
                    }
                    else {
                        sprite.move(solapaminetoX, 0);
                    }
                }
                else {
                    if (f_r1.top < f_r2.top) {
                        sprite.move(0, -solapaminetoY);
                    }
                    else {
                        sprite.move(0, solapaminetoY);
                    }
                }
            }
            else if(armaLista->colisiona(r2)&&Mouse::isButtonPressed(Mouse::Left)){
                r2.recibirDanio(500);
            }
        }

};

#endif // JUGADORES_H