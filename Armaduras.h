#ifndef ARMADURAS_H
#define ARMADURAS_H

#include"Intf_Armaduras.h"

class Casco : public Intf_Armaduras{
    public:
        //constructor y destructor
        Casco(unique_ptr<Intf_Jugador> &&_jugador):Intf_Armaduras(move(_jugador)){
            this->armadura=0.20f;
        }
        ~Casco(){}
        //metodos
        void takeDamage(float danio)override{
            float armadura_total=getArmor();
            float danio_recibido=danio*(1-armadura_total);
            float danio_retenido=danio*armadura_total;
            cout<<"Armadura total : "<<armadura_total<<", danio recivido : "<<danio_recibido<<", danio reteniudo : "<<danio_retenido<<endl;

            jugador->takeDamage(danio_recibido);
        }
};

class Chaleco :public Intf_Armaduras{
    public:
        //Constructor y destructor
        Chaleco(unique_ptr<Intf_Jugador> &&_jugador):Intf_Armaduras(move(_jugador)){
            this->armadura=0.15f;
        }
        ~Chaleco(){}

        //metodos
        void takeDamage(float danio)override{
            float armadura_total=getArmor();
            float danio_recibido=danio*(1-armadura_total);
            float danio_retenido=danio*armadura_total;
            cout<<"Armadura total : "<<armadura_total<<", danio recivido : "<<danio_recibido<<", danio reteniudo : "<<danio_retenido<<endl;
            //jugador->setVida(jugador->getVida()-danio_recibido);
            jugador->takeDamage(danio_recibido);

        }
};

class Botas :public Intf_Armaduras {
public:
    //Constructor y destructor
    Botas(unique_ptr<Intf_Jugador> &&_jugador) :Intf_Armaduras(move(_jugador)) {
        this->armadura = 0.10f;
    }
    ~Botas() {}

    //metodos
    void takeDamage(float danio)override {
        float armadura_total = getArmor();
        float danio_recibido = danio * (1 - armadura_total);
        float danio_retenido = danio * armadura_total;
        cout << "Armadura total : " << armadura_total << ", danio recivido : " << danio_recibido << ", danio reteniudo : " << danio_retenido << endl;
        //jugador->setVida(jugador->getVida() - danio_recibido);
        jugador->takeDamage(danio_recibido);

    }
};
#endif // ARMADURAS_H