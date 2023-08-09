#ifndef ESCOPETA_H
#define ESCOPETA_H
#include"Intf_Arma.h"
class Escopeta : public Intf_Arma{
    public:
        Escopeta(){
            textura.loadFromFile("Assets/escopeta.png");
            spriteArma.setTexture(textura);
            spriteArma.setScale(0.5f,0.5f);
            intervalo=1000;
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
                        disparos.push_back(make_unique<Proyectil>(_fabrica->getInstancia("cartucho"),500,jugador,direction,"aliadas_Cortas"));
                        tiempoAnterior=tiempoActual;
                    }
                }

            }
        }
};
#endif // ESCOPETA_H
