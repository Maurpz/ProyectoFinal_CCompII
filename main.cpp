#include"BoxData.h"
#include"Funciones.h"
#include"FlyFactory.h"
#include"Jugadores.h"
#include"Intf_Bloque.h"
#include"BloqueMadera.h"
#include"BloquePiedra.h"

#include"Intf_Expendedoras.h"
#include"ExpendedoraSalud.h"
#include"ExpendedoraEscudo.h"
#include"ExpendedoraArmaduras.h"

#include"Estadisticas.h"
#include"SFML/Graphics.hpp"

#include"Proyectil.h"
#include"Enemigo.h"
#include"Items.h"
#include <random>





int main() {

	unique_ptr<BoxData> tipo1=make_unique<BoxData>("madera",15,5,50,Color::Red);
	unique_ptr<BoxData> tipo2 = make_unique<BoxData>("piedra", 15,6,50,Color::Blue);
	unique_ptr<BoxData> tipo3 = make_unique<BoxData>("expVida", 15,7,50,Color::Magenta);
	unique_ptr<BoxData> tipo4 = make_unique<BoxData>("expEscudo", 15,8,50,Color::Black);
	unique_ptr<BoxData> tipo5 = make_unique<BoxData>("expArmadura", 15,9,50,Color::Cyan);
    unique_ptr<BoxData> tipo6 = make_unique<BoxData>("", 15,10,50,Color::White);

	//---------------------------Inicializamos los datos de la Flyfactori------------------
	FlyFactory * fabrica1=FlyFactory::getInstance();
	fabrica1->agregarTipos("piedra", "Assets/piedra.png");
	fabrica1->agregarTipos("madera", "Assets/madera.png");
	fabrica1->agregarTipos("expVida", "Assets/vida.png");
	fabrica1->agregarTipos("expEscudo", "Assets/escudo.png");
	fabrica1->agregarTipos("expArmadura", "Assets/armaduras.png");
	fabrica1->agregarTipos("bala", "Assets/bala.png");
	fabrica1->agregarTipos("cartucho", "Assets/cartucho.png");
	fabrica1->agregarTipos("enemigo", "Assets/enemigo.png");
	fabrica1->agregarTipos("lazer", "Assets/lazer.png");
	fabrica1->agregarTipos("llave", "Assets/llave.png");


	//---------------------------Texto Jugar-----------------------------------
	Texture fondo1;
	fondo1.loadFromFile("Assets/fondo.jpg");
	Sprite fondo;
	fondo.setTexture(fondo1);
	fondo.setPosition(-400,-400);
	fondo.setScale(2,2);

	//------------------------
	Texture save;
	save.loadFromFile("Assets/button.png");
	Sprite button1;
	Sprite button2;
	button1.setTexture(save);
	button2.setTexture(save);
	button1.setScale(3,3);
	button2.setScale(5.5,3);

	button1.setPosition(300,350);
	button2.setPosition(500,350);


	Font fuente;
	fuente.loadFromFile("Assets/MinimalPixelFont.ttf");
	Text texto;
	Text texto2;
	texto.setFont(fuente);
	texto2.setFont(fuente);

	texto.setString("Jugar");
	texto2.setString("Crear mapa");

	texto.setScale(1.5,1.5);
	texto2.setScale(1.5,1.5);

	texto.setPosition(320,335);
	texto2.setPosition(520,335);

	



	//especificaciones para la creacion del mapa



	//Bucle crear Mapa


	bool salir = false;
	bool crear_mapa=false;
	RenderWindow window(VideoMode(800,800),"Menu");
	window.setFramerateLimit(30);
	while (window.isOpen() && salir != true) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (button1.getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y)) {
				salir = true;
			}
			if (button2.getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y)) {
				salir = true;
				crear_mapa=true;
			}
			
		}

		window.clear();
		window.draw(fondo);
		window.draw(button1);
		window.draw(button2);
		window.draw(texto);
		window.draw(texto2);


		window.display();


	}

//------------------------------------------------------------------------------------
	button1.setScale(3,3);
	button1.setPosition(700,752);
	texto.setString("Jugar");
	texto.setScale(1.5,1.5);
	texto.setPosition(720,735);
	int lado = 48;


	string tipo;
    Color ctipo;
	int filas=15;
	int columnas=15;
	auto mapa=crearMatriz(filas,columnas,48);
	if(crear_mapa==true){
		cout<<"Ingrese el numero de filas : ";cin>>filas;
		cout<<"Ingrese el numero de columnas : ";cin>>columnas;
		int medida=750/columnas;
		mapa=crearMatriz(filas,columnas,medida);

	}
	//---------------------------bucle-----------------------
	vector<vector<int>> matriz_int;
	window.setFramerateLimit(30);
	while (window.isOpen() && crear_mapa) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (tipo1->contiene(Mouse::getPosition(window))) {
				tipo = tipo1->getTipo();
                ctipo = tipo1->getColor();
			}
			else if (tipo2->contiene(Mouse::getPosition(window))) {
				tipo = tipo2->getTipo();
                ctipo = tipo2->getColor();
			}
			else if (tipo3->contiene(Mouse::getPosition(window))) {
				tipo = tipo3->getTipo();
                ctipo = tipo3->getColor();
			}
            else if (tipo4->contiene(Mouse::getPosition(window))) {
				tipo = tipo4->getTipo();
                ctipo = tipo4->getColor();
			}
			else if (tipo5->contiene(Mouse::getPosition(window))) {
				tipo = tipo5->getTipo();
                ctipo = tipo5->getColor();
			}
			else if (tipo6->contiene(Mouse::getPosition(window))) {
				tipo = tipo6->getTipo();
                ctipo = tipo6->getColor();
			}
			if (button1.getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y)) {
				crear_mapa=false;
			}
			
			
			for (auto& fila : mapa) {
				for (auto& columna : fila) {
					if (columna->contiene(Mouse::getPosition(window))) {
						columna->setTipo(tipo);
						columna->select(ctipo);
						//printMatriz(pp);
						matriz_int = convertirMatriz_a_numerica(mapa);

					}
				}
			}
		}

		window.clear();
		window.draw(fondo);

		for (auto & fila : mapa) {
			for (auto & columna : fila) {
				window.draw(*columna);
			}
		}
		window.draw(*tipo1);
		window.draw(*tipo2);
		window.draw(*tipo3);
        window.draw(*tipo4);
		window.draw(*tipo5);
		window.draw(*tipo6);
		window.draw(button1);
		window.draw(texto);

		window.display();


	}


	//-----------------------------------------segundo bucle------------------------------------------
	salir = false;
	vector<unique_ptr<Intf_Bloque>> bloques;
	vector<unique_ptr<Intf_Expendedoras>> expendedoras;
	vector<unique_ptr<Proyectil>> disparos;
	vector<unique_ptr<Items>> items;
	cout << "Segundo bucle" << endl;

	window.setFramerateLimit(60);
	for (auto& fila : mapa) {
		for (auto& box : fila) {
			int b_x = box->getX();
			int b_y = box->getY();
			if (box->getTipo() == "madera") {
				bloques.push_back(make_unique<BloqueMadera>(fabrica1->getInstancia(box->getTipo()), b_x, b_y, lado));
			}
			else if (box->getTipo() == "piedra") {
				bloques.push_back(make_unique<BloquePiedra>(fabrica1->getInstancia(box->getTipo()), b_x, b_y, lado));
			}
			else if(box->getTipo()=="expVida"){
				expendedoras.push_back(make_unique<ExpendedoraSalud>(fabrica1->getInstancia(box->getTipo()), b_x, b_y, lado));
			}
			else if (box->getTipo() == "expEscudo") {
				expendedoras.push_back(make_unique<ExpendedoraEscudo>(fabrica1->getInstancia(box->getTipo()), b_x, b_y, lado));
			}
			else if (box->getTipo() == "expArmadura") {
				expendedoras.push_back(make_unique<ExpendedoraArmaduras>(fabrica1->getInstancia(box->getTipo()), b_x, b_y, lado));
			}
		}
	}

	//--------------------------------------------------------Especificaciones del juego--------------
	unique_ptr<Intf_Jugador> p1 = make_unique<Jugadores>(1000.f, "Mauricio");
	unique_ptr<Enemigo> e1=make_unique<Enemigo>(fabrica1->getInstancia("enemigo"));
	FloatRect viewport_(0.f, 0.f, 400.f, 400.f);
	View vista(viewport_);
	unique_ptr<Estadisticas> estadisticas=make_unique<Estadisticas>();

	//random 
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 20);
	int randomNumber;
	int llavesEncontradas=0;
	
	salir=false;

	while (window.isOpen()&&salir!=true) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if(llavesEncontradas>=3){
			salir=true;
		}
		else if(p1->getVida()<=0){
			salir=true;
		}

		
		p1->update(vista,window,disparos,fabrica1);
		e1->mover();
		e1->atacar(disparos,fabrica1);

		//Deteccion de colisiones jugador con bloques
		for (auto& bloque : bloques) {
			p1->detector(*bloque);
			bloque->actualizarEstado();
			randomNumber = distribution(gen);
			if(bloque->getEstado()&&randomNumber>19){
				items.emplace_back(make_unique<Items>(fabrica1->getInstancia("llave"),bloque->getPosition()));
			}

		}

		//deteccion de interaccion de expendedoras con jugador
		for(auto & expendedora: expendedoras){
			expendedora->interactua(p1);
		}
		for(auto & proyectil : disparos){
			proyectil->detonar();
			if(proyectil->getTipo()=="aliadas_Cortas"){
				for(auto & bloque : bloques){
					if(proyectil->colisiona(*bloque)){
						bloque->recibirDanio(proyectil->getDanio());
						proyectil->primerImpacto();
					}
				}
			}
			else if(proyectil->getTipo()=="aliadas_distancia"){
				if(proyectil->colisiona(*e1)){
					proyectil->primerImpacto();
					//bajar vida al enemigo
				}
			}
			else if(proyectil->getTipo()=="enemigas"){
				if(proyectil->colisiona(*p1)){
					p1->takeDamage(proyectil->getDanio());
					proyectil->primerImpacto();
				}
			}
		}
		for(auto & item:items){
			if(item->colisiona(*p1)){
				item->colisiono();
				llavesEncontradas++;
			}
		}





		estadisticas->update(p1,llavesEncontradas);

		//eliminamos los bloques sin vida o resistencia
		bloques.erase(remove_if(bloques.begin(), bloques.end(), [](const unique_ptr<Intf_Bloque> & bloque ) {return bloque->getEstado();}), bloques.end());
		items.erase(remove_if(items.begin(), items.end(), [](const unique_ptr<Items> & item ) {return item->getEstado();}), items.end());
		disparos.erase(remove_if(disparos.begin(), disparos.end(), [](const unique_ptr<Proyectil> & proyectil ) {return proyectil->getEstado();}), disparos.end());

		//---------------------------------------LIMPIA LA PANTALLA-------------------------------

		window.clear();

		//------------------------------------------------------------------------------------------
		window.draw(fondo);
		//dibujar bloques
		for (auto& bloque : bloques) {
			if(!bloque->getEstado()){
				window.draw(*bloque);
			}
			else{
				cout<<"elemento destruido"<<endl;
			}
		}
		//dibujar expendedoras
		for(auto & expendedora: expendedoras){
			window.draw(*expendedora);
		}

		//dibujar Proyectiles
		if(disparos.size()>0){
			for(auto & proyectil : disparos){
				window.draw(*proyectil);
		}
		}
		for(auto &item : items){
			window.draw(*item);
		}
		window.setView(vista);
		window.draw(*p1);
		window.draw(*e1);
		window.draw(*estadisticas);
		window.display();

	}
	Texture win;
	win.loadFromFile("Assets/win.png");
	Texture lost;
	lost.loadFromFile("Assets/lost.png");
	Sprite fin;
	if(p1->getVida()>0){
		fin.setTexture(win);
		fin.setScale(.5f, .5f);
		fin.setOrigin((fin.getGlobalBounds().width/2)+200,fin.getLocalBounds().height/2);
		vista.setCenter(fin.getPosition());
	}
	else{
		fin.setTexture(lost);
		fin.setScale(.4f, .4f);
		fin.setOrigin((fin.getGlobalBounds().width/2)+200,fin.getLocalBounds().height/2);
		vista.setCenter(fin.getPosition());
	}

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.setView(vista);
		window.draw(fin);
		window.display();
	}




	return 0;
}