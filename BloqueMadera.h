#ifndef BLOQUEMADERA_H
#define BLOQUEMADERA_H

#include"Intf_Bloque.h"

class BloqueMadera : public Intf_Bloque{
    public:
        BloqueMadera(shared_ptr<Texture> textura,int _x,int _y,int lado): Intf_Bloque(textura,_x,_y,lado){
            tipo="madera";
            duravilidad=500;
        }
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(spriteBloque,states);
        }
};
#endif // BLOQUEMADERA_H