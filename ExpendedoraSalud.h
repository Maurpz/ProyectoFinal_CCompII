#ifndef EXPENDEDORASALUD_H
#define EXPENDEDORASALUD_H
#include"Intf_Expendedoras.h"

class ExpendedoraSalud : public Intf_Expendedoras{
    public:
        ExpendedoraSalud(shared_ptr<Texture> textura,int _x,int _y,int lado):Intf_Expendedoras(textura,_x,_y,lado){
            intervalo=5000;
        }
        void interactua(unique_ptr<Intf_Jugador> & jugador)override{
            setTiempoActual();
            if(this->colisiona(*jugador)&& disponible()){
                cout<<"Vida"<<endl;
                jugador->addVida(100);
                tiempoAnterior=tiempoActual;
            }
        }
};
#endif // EXPENDEDORASALUD_H