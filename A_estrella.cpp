#include<iostream>
#include<memory>
#include<vector>
#include<cmath>
#include<utility>
using namespace std;

//------------------------------------------Nodos---------------------------------------------
class Nodo{
    private:
        int x;
        int y;
        float costo_acumulado=0;
        float costo;
        float heuristica;
        float f_n;
        shared_ptr<Nodo> nodoPadre;
    public:
        Nodo(int &x_a, int &y_a, int &x_d, int &y_d,shared_ptr<Nodo> padre=nullptr,float _costo=0){
            x=x_a;
            y=y_a;
            nodoPadre=padre;
            heuristica=abs(x-x_d)+abs(y-y_d);
            costo=_costo;
            costo_acumulado=calcularCostoAcumulado();
            calcularF_n();
        }
        //gets
        float getF_n()const{
            return f_n;
        }
        float getCosto()const{
            return costo_acumulado;
        }
        void calcularF_n(){
            f_n=costo_acumulado+heuristica;
        }
        int getX()const{
            return x;
        }
        int getY()const{
            return y;
        }
        float getH(){
            return heuristica;
        }
        //actualizar nodos
        void actualizarPadre(shared_ptr<Nodo> n_padre){
            nodoPadre=n_padre;
        }
        void actualizarCosto(float n_costo){
            costo_acumulado=n_costo;
            calcularF_n();
        }
        float calcularCostoAcumulado(){
            if(nodoPadre!=nullptr){
                float cost=costo+nodoPadre->calcularCostoAcumulado();
                return cost;
            }
            return costo;
        }
        void desendencia(){
            if(nodoPadre!=nullptr){
                nodoPadre->desendencia();
            }
            cout<<" x : "<<x<<" y : "<<y<<" costoAcumulado :"<<costo_acumulado<<endl;
        }

};



//--------------------------------------------------Lista Abierta--------------------------------------------------
class ListaAbierta{
    private:
        vector<shared_ptr<Nodo>> abierta;
    public:
        ListaAbierta(){}
        ~ListaAbierta(){}

        void tostring(){
            for(auto nodo : abierta){
                cout<<"f: "<<nodo->getF_n()<<" | costo : "<<nodo->getCosto()<<" | h : "<<nodo->getH()<<" | x : "<<nodo->getX()<<" | y : "<<nodo->getY()<<endl;
            }
        }

        pair<shared_ptr<Nodo>,int> nodoConMenorF_n(){
            if(abierta.size()>0){
                int nodoEliminar=0;
                shared_ptr<Nodo>auxiliar=abierta[0];
                for(int i=0;i<abierta.size();i++){
                    if(abierta[i]->getF_n()<auxiliar->getF_n()){
                        auxiliar=abierta[i];
                        nodoEliminar=i;
                    }
                
                }
                return make_pair(auxiliar,nodoEliminar);
            }
            else{
                cout<<"La lista se encuentra vacia"<<endl;
                return make_pair(nullptr,-1);
            }
            
        }

        void eliminarDeLaLista(int indice){
            abierta.erase(abierta.begin()+indice);
        }

        pair<bool,int> estaEnAbierta(float x, float y){
            int indice=0;
            for(int i =0;i<abierta.size();i++){
                if(abierta[i]->getX()==x && abierta[i]->getY()==y){
                    indice=i;
                    return make_pair(true,indice);
                    
                }
            }
            return make_pair(false,-1);
            
        }

        void actualizarNodo(shared_ptr<Nodo> n_nodo,int indice){
            if(n_nodo->getF_n()<abierta[indice]->getF_n()){
                abierta[indice]=n_nodo;
            }
        }

        void addAbierta(shared_ptr<Nodo>n_nodo){
            abierta.push_back(n_nodo);
        }

        

};

//-------------------------------------------lista cerrada----------------------------------------------------
class ListaCerrada{
    private:
        vector<shared_ptr<Nodo>>cerrada;
    public:
        ListaCerrada(){}
        ~ListaCerrada(){}

        void tostring(){
            for(auto nodo : cerrada){
                cout<<"f: "<<nodo->getF_n()<<" | costo : "<<nodo->getCosto()<<" | h : "<<nodo->getH()<<" | x : "<<nodo->getX()<<" | y : "<<nodo->getY()<<endl;
            }
        }

        void addNodo(shared_ptr<Nodo> nuevo_nodo){
            cerrada.push_back(nuevo_nodo);
        }

        bool estaEnCerrada(float x, float y){
            for(auto & nodo :cerrada){
                if(nodo->getX()==x && nodo->getY()==y){
                    return true;
                }
            }
            return false;
        }
};


//---------------------------------funciones vecino-----------------------------------------


pair<bool,shared_ptr<Nodo>>validarVecinos(int x,int y,shared_ptr<Nodo> & padre,ListaAbierta & lAbierta,ListaCerrada & lCerrada,pair<int,int>destino,float costo){
    //comprovamos si el vecino es el destino
    if(!(x==destino.first && y==destino.second)){
        if(!lCerrada.estaEnCerrada(x,y)){
            auto vecinoValidacion = lAbierta.estaEnAbierta(x,y);
            if(!vecinoValidacion.first){
                lAbierta.addAbierta(make_shared<Nodo>(x,y,destino.first,destino.second,padre,costo));
            }
            else{
                lAbierta.actualizarNodo(make_shared<Nodo>(x,y,destino.first,destino.second,padre,costo),vecinoValidacion.second);
            }
        }
        return make_pair(false,nullptr);

    }
    else{
        return make_pair(true,make_shared<Nodo>(x,y,destino.first,destino.second,padre,costo));
        //el vecino es el destino terminamos la funcion y el bucle
    }
}

pair<bool,shared_ptr<Nodo>> expandirVecinos(shared_ptr<Nodo> & padre,ListaAbierta & lAbierta,ListaCerrada & lCerrada,vector<vector<int>> & matriz,pair<int,int>destino,float costo,pair<int,int>lim){
    int x=padre->getX();
    int y=padre->getY();
    //agregamos los vecinos del eje x
    if(x!=0 && matriz[x-1][y]==0){
        auto retornar=validarVecinos(x-1,y,padre,lAbierta,lCerrada,destino,costo);
        if(retornar.first){
            cout<<"1"<<endl;
            return retornar;
        }
    }
    if(x!=lim.first && matriz[x+1][y]==0){
        auto retornar=validarVecinos(x+1,y,padre,lAbierta,lCerrada,destino,costo);
        if(retornar.first){
            cout<<"2"<<endl;
            return retornar;
        }
    }

    //agregamos los vecinos del eje y

    if(y!=0 && matriz[x][y-1]==0){
        auto retornar=validarVecinos(x,y-1,padre,lAbierta,lCerrada,destino,costo);
        if(retornar.first){
            cout<<"2"<<endl;
            return retornar;
        }
    }
    if(y!=lim.second && matriz[x][y+1]==0){
        auto retornar=validarVecinos(x,y+1,padre,lAbierta,lCerrada,destino,costo);
        if(retornar.first){
            cout<<"4"<<endl;
            return retornar;
        }
    }
    return make_pair(false,nullptr);

}
// -------------------------------------------------------Main---------------------------------------------------
int main(){
    int iteraciones=0;
    ListaAbierta listaAbierta;
    ListaCerrada listaCerrada;

    vector<vector<int>>matriz(7);
    for(int i =0;i<matriz.size();i++){
        for(int j=0;j<7;j++){
            matriz[i].push_back(0);
        }
    }
    matriz[1][0]=1;
    matriz[2][0]=1;
    matriz[3][0]=1;
    matriz[3][1]=1;
    matriz[3][2]=1;
    matriz[4][2]=1;
    matriz[5][2]=1;
    matriz[5][3]=1;
    matriz[5][4]=1;
    matriz[5][5]=1;
    matriz[1][2]=1;
    matriz[1][3]=1;
    matriz[1][4]=1;
    matriz[2][4]=1;
    matriz[3][4]=1;
    matriz[3][5]=1;
    matriz[3][6]=1;


    pair<int,int> p_origen=make_pair(2,6);
    pair<int,int> p_destino=make_pair(6,1);

    pair<int,int> limites=make_pair(6,6);

    shared_ptr<Nodo> origen=make_shared<Nodo>(p_origen.first,p_origen.second,p_destino.first,p_destino.second);
    shared_ptr<Nodo> destino;
    pair<shared_ptr<Nodo>,int> nodoActual;
    int costo = 1;
    
    listaAbierta.addAbierta(origen);

    bool salir=false;
    while(!salir){
        iteraciones++;
        nodoActual=listaAbierta.nodoConMenorF_n();
        if(nodoActual.first->getX()==p_destino.first && nodoActual.first->getY()==p_destino.second){
            destino=nodoActual.first;
            
            break;
        }
        listaCerrada.addNodo(nodoActual.first);
        listaAbierta.eliminarDeLaLista(nodoActual.second);

        auto salirDelBucle=expandirVecinos(nodoActual.first,listaAbierta,listaCerrada,matriz,p_destino,costo,limites);
        if(salirDelBucle.first){
            salir=true;
            destino=salirDelBucle.second;
        }
    }
    cout<<"Se salio del bucle :,3"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"Punto de origen : "<<p_origen.first<<","<<p_origen.second<<endl;
    cout<<"Punto de destino : "<<p_destino.first<<","<<p_destino.second<<endl;
    
    cout<<"supuesto destino : "<<destino->getX()<<" "<<destino->getY()<<endl;
    
    cout<<"lista Abierta"<<endl;
    listaAbierta.tostring();
    cout<<"Lista Cerrada"<<endl;
    listaCerrada.tostring();

    cout<<"-------------mostrar camino----------"<<endl<<endl;
    cout<<"Mostratremos la desendencia del nodo destino.............."<<endl;
    destino->desendencia();
    
    cout<<"El bucle dio "<<iteraciones<<" iteraciones ";



    return 0;
}