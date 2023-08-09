#ifndef EXPENDEDORAESCUDO_H
#define EXPENDEDORAESCUDO_H
#include"Intf_Expendedoras.h"

class ExpendedoraEscudo : public Intf_Expendedoras{
    public:
        ExpendedoraEscudo(shared_ptr<Texture> textura,int _x,int _y,int lado):Intf_Expendedoras(textura,_x,_y,lado){
            intervalo=3000;
        }
        void interactua(unique_ptr<Intf_Jugador> & jugador)override{
            setTiempoActual();
            if(this->colisiona(*jugador) && disponible()){
                cout<<"Escudo"<<endl;
                jugador->addEscudo(50);
                tiempoAnterior=tiempoActual;
            }
        }
};
#endif // EXPENDEDORAESCUDO_H