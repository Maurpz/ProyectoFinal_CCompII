#ifndef EXPENDEDORAARMADURAS_H
#define EXPENDEDORAARMADURAS_H
#include"Intf_Expendedoras.h"
#include"Intf_Armaduras.h"
#include"Armaduras.h"


class ExpendedoraArmaduras : public Intf_Expendedoras{
    private:
        static int armadurasEntregadas;
    public:
        ExpendedoraArmaduras(shared_ptr<Texture> textura,int _x,int _y,int lado):Intf_Expendedoras(textura,_x,_y,lado){
            intervalo=10000;
        }

        void interactua(unique_ptr<Intf_Jugador> & jugador)override{
            setTiempoActual();
            if(this->colisiona(*jugador)&& disponible()){
                if(armadurasEntregadas==0){
                    jugador=make_unique<Botas>(move(jugador));
                    armadurasEntregadas++;
                    cout<<"BOTAS"<<endl;

                }
                else if(armadurasEntregadas==1){
                    jugador=make_unique<Casco>(move(jugador));
                    armadurasEntregadas++;
                    cout<<"CASCO"<<endl;
                }
                else if(armadurasEntregadas==2){
                    jugador=make_unique<Chaleco>(move(jugador));
                    armadurasEntregadas++;
                    cout<<"CHALECO"<<endl;
                }
                else{
                    cout<<"Son todas las armaduras disponibles"<<endl;
                }
                tiempoAnterior=tiempoActual;
            }
        }
};
int ExpendedoraArmaduras::armadurasEntregadas=0;
#endif // EXPENDEDORAARMADURAS_H