#ifndef BLOQUEPIEDRA_H
#define BLOQUEPIEDRA_H

#include"Intf_Bloque.h"

class BloquePiedra : public Intf_Bloque{
    public:
        BloquePiedra(shared_ptr<Texture> textura,int _x,int _y,int lado) : Intf_Bloque(textura,_x,_y,lado){
            tipo="bloque";
            duravilidad=2000;
        }
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(spriteBloque,states);
        }
};
#endif // BLOQUEPIEDRA_H