#ifndef PISTOLA_H
#define PISTOLA_H
#include"Intf_Arma.h"
class Pistola : public Intf_Arma{
    public:
        Pistola(){
            textura.loadFromFile("Assets/pistola.png");
            spriteArma.setTexture(textura);
            spriteArma.setScale(0.6f,0.6f);
            intervalo=300;
        }

        void setPosicion(Vector2f pos)override{
            spriteArma.setPosition(pos.x,pos.y-10);
        }
       void atacar(RenderWindow & w,vector<unique_ptr<Proyectil>> & disparos, FlyFactory * _fabrica,Vector2f jugador)override{
            if(Mouse::isButtonPressed(Mouse::Left)){
                setTiempoActual();
                if(disponible()){
                    Vector2f mousePos = w.mapPixelToCoords(Mouse::getPosition(w));
                    Vector2f direction = mousePos - jugador;
                    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    if (length > 0)
                    {
                        direction /= length;
                        disparos.push_back(make_unique<Proyectil>(_fabrica->getInstancia("bala"),100,jugador,direction,"aliadas_distancia"));
                        tiempoAnterior=tiempoActual;
                    }
                }

            }
        }

};
#endif // PISTOLA_H