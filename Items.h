#ifndef ITEMS_H
#define ITEMS_H
#include"Colisionable.h"
#include<memory>
class Items : public Colisionable,public  Drawable{
    private:
        bool estadoEliminar=false;
        Sprite spriteItem;
    public:
        Items(shared_ptr<Texture> textura,Vector2f pos){
                spriteItem.setTexture(*textura);
                spriteItem.setPosition(pos);
            }
        void draw(RenderTarget& target, RenderStates states)const override{
            target.draw(spriteItem,states);
        }
        void colisiono(){
            estadoEliminar=true;
        }
        bool getEstado(){
            return estadoEliminar;
        }

        FloatRect getBounds() const override{
            return spriteItem.getGlobalBounds();
        }
};
#endif // ITEMS_H