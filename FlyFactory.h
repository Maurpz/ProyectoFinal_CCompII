#ifndef FLYFACTORY_H
#define FLYFACTORY_H
#include"Pesado.h"
#include<vector>



class FlyFactory{
    private:
        static FlyFactory * instancia;
        vector<shared_ptr<Pesado>> listaPesada;
        vector<pair<string,string>> tipos_and_urls;
        FlyFactory(){}
    public:
        static FlyFactory* getInstance(){
            if(instancia==nullptr){
                instancia=new FlyFactory();
            }
            return instancia;
        }
        shared_ptr<Texture> getInstancia(string tipo){
            for(auto tipos: tipos_and_urls){
                if(tipos.first==tipo){
                    for(auto elemento : listaPesada){
                        if(elemento->mismoTipo(tipo)){
                            return elemento->getInstancia();
                        }
                    }
                    listaPesada.push_back(make_shared<Pesado>(tipos.second,tipo));
                    return listaPesada.back()->getInstancia();
                }else{
                    continue;
                }
            }
            return nullptr;
            
        }

        void agregarTipos(string tipo,string url){
            tipos_and_urls.push_back(make_pair(tipo,url));
        }

        void getElementos()const{
            cout << "La fabrica tiene :" << listaPesada.size() << " elementos " << endl;
        }

};
FlyFactory * FlyFactory::instancia=nullptr;
#endif // FLYFACTORY_H

/*



class FlyFactory{
    private:
        
        vector<shared_ptr<Pesado>> listaPesada;
        vector<pair<string,string>> tipos_and_urls;
    public:
        FlyFactory(){}

        shared_ptr<Texture> getInstancia(string tipo){
            for(auto tipos: tipos_and_urls){
                if(tipos.first==tipo){
                    for(auto elemento : listaPesada){
                        if(elemento->mismoTipo(tipo)){
                            return elemento->getInstancia();
                        }
                    }
                    listaPesada.push_back(make_shared<Pesado>(tipos.second,tipo));
                    return listaPesada.back()->getInstancia();
                }else{
                    continue;
                }
            }
            return nullptr;
            
        }

        void agregarTipos(string tipo,string url){
            tipos_and_urls.push_back(make_pair(tipo,url));
        }

        void getElementos()const{
            cout << "La fabrica tiene :" << listaPesada.size() << " elementos " << endl;
        }

};
#endif // FLYFACTORY_H
*/