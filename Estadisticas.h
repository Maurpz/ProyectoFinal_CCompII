#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H
#include"SFML/Graphics.hpp"
#include"Intf_Jugador.h"
#include<iostream>
using namespace std;
class Estadisticas : public Drawable{
    private:
        Font fuente;
        Text textoArmadura;
        Text textoVida;
        Text textoEscudo;
        Text llaves;
    public:
        Estadisticas(){
            fuente.loadFromFile("Assets/MinimalPixelFont.ttf");
            textoArmadura.setFont(fuente);
            textoEscudo.setFont(fuente);
            textoVida.setFont(fuente);
            llaves.setFont(fuente);
        }
        void update(unique_ptr<Intf_Jugador> & jugador,int n_llave){
            textoArmadura.setPosition(jugador->getPosition()-Vector2f(185,180));
            textoVida.setPosition(jugador->getPosition()-Vector2f(185,165));
            textoEscudo.setPosition(jugador->getPosition()-Vector2f(185,140));
            llaves.setPosition(jugador->getPosition()-Vector2f(185,125));

            textoArmadura.setString("Armadura "+to_string(jugador->getArmor()));
            textoVida.setString("Vida "+to_string(jugador->getVida()));
            textoEscudo.setString("Escudo "+to_string(jugador->getEscudo()));
            llaves.setString("Llaves : "+to_string(n_llave));
        }
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(textoArmadura,states);
            target.draw(textoEscudo,states);
            target.draw(textoVida,states);
            target.draw(llaves,states);

        }

    


};

#endif // ESTADISTICAS_H