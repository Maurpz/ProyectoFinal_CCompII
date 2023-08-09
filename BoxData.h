#ifndef BOXDATA_H
#define BOXDATA_H

#include"SFML/Graphics.hpp"
#include<iostream>
using namespace std;
using namespace sf;

class BoxData : public Drawable{
private:
	RectangleShape shape;
	string tipo;
    Color colorBox;
	int lado;
	int x;
	int y;
public:
	BoxData(string _tipo, int _x, int _y,int _lado,Color color) {
		lado = _lado;
		tipo = _tipo;
		x = _x;
		y = _y;
		shape.setSize(Vector2f(lado-2,lado-2));
		shape.setPosition(x*_lado, y*_lado);
        colorBox=color;
        shape.setFillColor(colorBox);
	}
	bool contiene(Vector2i && punto){
		return shape.getGlobalBounds().contains(punto.x,punto.y);
	}
	void select(Color & color) {
		shape.setFillColor(color);
	}
	void draw(RenderTarget& target, RenderStates states)const override{
		target.draw(shape, states);
	}
	void setTipo(string n_tipo){
		tipo = n_tipo;
	}
    Color getColor(){
        return colorBox;
    }
	string getTipo()const {
		return tipo;
	}
	int getX()const {
		return x;
	}
	int getY()const {
		return y;
	}
};

#endif // BOXDATA_H