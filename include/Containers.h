#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include "Entidades.h"

#include <map>

using namespace std;

class ContainerUsuario{
    private:
        map<string, Usuario> container;                 // Mapa de usuários.
        static ContainerUsuario *instancia;             // Ponteiro para instância da classe.
        ContainerUsuario(){};                           // Construtor.
    public:
        static  ContainerUsuario* getInstancia();       // Método para instanciar classe.
        bool incluir(Usuario);                          // Métodos responsáveis por prestar serviços.
        bool remover(Matricula);
        bool pesquisar(Usuario*);
        bool atualizar(Usuario);
        bool autenticar(Usuario);
};

class ContainerProjeto{
    private:
        map<string, Projeto> container;                 // Mapa de usuários.
        static ContainerProjeto *instancia;             // Ponteiro para instância da classe.
        ContainerProjeto(){};                           // Construtor.
    public:
        static  ContainerProjeto* getInstancia();       // Método para instanciar classe.
        bool incluir(Projeto);                          // Métodos responsáveis por prestar serviços.
        bool remover(Codigo);
        bool pesquisar(Projeto*);
        bool atualizar(Projeto);
};

#endif // CONTROLADORAS_H_INCLUDED

