#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include "Entidades.h"

#include <map>

using namespace std;

class ContainerUsuario{
    private:
        map<string, Usuario> container;                 // Mapa de usu�rios.
        static ContainerUsuario *instancia;             // Ponteiro para inst�ncia da classe.
        ContainerUsuario(){};                           // Construtor.
    public:
        static  ContainerUsuario* getInstancia();       // M�todo para instanciar classe.
        bool incluir(Usuario);                          // M�todos respons�veis por prestar servi�os.
        bool remover(Matricula);
        bool pesquisar(Usuario*);
        bool atualizar(Usuario);
        bool autenticar(Usuario);
};

class ContainerProjeto{
    private:
        map<string, Projeto> container;                 // Mapa de usu�rios.
        static ContainerProjeto *instancia;             // Ponteiro para inst�ncia da classe.
        ContainerProjeto(){};                           // Construtor.
    public:
        static  ContainerProjeto* getInstancia();       // M�todo para instanciar classe.
        bool incluir(Projeto);                          // M�todos respons�veis por prestar servi�os.
        bool remover(Codigo);
        bool pesquisar(Projeto*);
        bool atualizar(Projeto);
};

#endif // CONTROLADORAS_H_INCLUDED

