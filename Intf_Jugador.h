#ifndef  INTF_JUGADOR_H
#define INTF_JUGADOR_H
#include"FlyFactory.h"
#include"Colisionable.h"
#include"Intf_Bloque.h"
#include"Intf_Arma.h"
#include"Proyectil.h"


class Intf_Jugador : public Colisionable, public Drawable{
    protected:
        friend class Intf_Armaduras;
        friend class Casco;
        friend class Chaleco;

        
        float vida=0.f;
        float escudo=0.f;
        string nombre;
        float armadura=0.f;

        //..
        Texture textura;
        Sprite sprite;
        Vector2f posicion;
        //float velocidad=0.1f;
        float velocidad=3.f;
        shared_ptr<Intf_Arma> lista_de_Armas[3];
        shared_ptr<Intf_Arma> armaLista;



        //..
        //unique_ptr<Intf_Arma> arma=nullptr;
    public:
        //destrcutor
        virtual ~Intf_Jugador(){}

        //metodos
        virtual void takeDamage(float)=0;
        virtual void toString()const=0;
        
        //gets and sets
        virtual float getVida()const=0;
        virtual float getEscudo()const = 0;
        
        virtual void addVida(float)=0;
        virtual void addEscudo(float) = 0;

        virtual void addVelocidad() = 0;

        virtual void setVida(float) = 0;

        //...
        virtual float getArmor()const=0;

        //eventos
        virtual void update(View& v,RenderWindow & w,vector<unique_ptr<Proyectil>> & disparos,FlyFactory * fabrica)=0;
        virtual Vector2f getPosition() = 0;
        virtual void detector(Intf_Bloque & r2) = 0;
};
#endif // INTF_JUGADOR_H