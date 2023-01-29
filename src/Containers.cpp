#include "Containers.h"
#include "Telas.h"

#include <iostream>

ContainerUsuario* ContainerUsuario::instancia = nullptr;

//------------------------------------------------------------------------------------
// Implementações de métodos de classe container.

ContainerUsuario* ContainerUsuario::getInstancia() {
    if (instancia == nullptr)
        instancia = new ContainerUsuario();
    return instancia;
}

bool ContainerUsuario::incluir(Usuario usuario){
    return container.insert(make_pair(usuario.getMatricula().getValor(), usuario)).second;
}

bool ContainerUsuario::remover(Matricula matricula){
    map<string, Usuario>::iterator it = container.find(matricula.getValor());
    if(it != container.end()){
        container.erase(it);
        return true;
    }
    return false;
}

bool ContainerUsuario::pesquisar(Usuario * usuario){
    map<string, Usuario>::iterator it = container.find(usuario->getMatricula().getValor());
    if(it != container.end()){
        *usuario = it->second;
        return true;
    }
    return false;
}

bool ContainerUsuario::autenticar(Usuario usuario) {
    map<string, Usuario>::iterator it = container.find(usuario.getMatricula().getValor());
    if(it != container.end() && it->second.getSenha().getValor() == usuario.getSenha().getValor()){
        return true;
    }
    return false;
}

bool ContainerUsuario::atualizar(Usuario usuario){
    map<string, Usuario>::iterator it = container.find(usuario.getMatricula().getValor());
    if(it != container.end()){
        it->second = usuario;
        return true;
    }
    return false;
}



ContainerProjeto* ContainerProjeto::instancia = nullptr;


ContainerProjeto* ContainerProjeto::getInstancia() {
    if (instancia == nullptr)
        instancia = new ContainerProjeto();
    return instancia;
}

bool ContainerProjeto::incluir(Projeto projeto){
    return container.insert(make_pair(projeto.getCodigo().getValor(), projeto)).second;
}

bool ContainerProjeto::remover(Codigo codigo){
    map<string, Projeto>::iterator it = container.find(codigo.getValor());
    if(it != container.end()){
        container.erase(it);
        return true;
    }
    return false;
}

bool ContainerProjeto::pesquisar(Projeto* projeto){
    map<string, Projeto>::iterator it = container.find(projeto->getCodigo().getValor());
    if(it != container.end()){
            if(it->second.getUsuario().getValor() == projeto->getUsuario().getValor()){
               *projeto = it->second;
               return true;
            }
    }
    return false;
}

bool ContainerProjeto::atualizar(Projeto projeto){
    map<string, Projeto>::iterator it = container.find(projeto.getCodigo().getValor());
    if(it != container.end()){
        if(it->second.getUsuario().getValor() == projeto.getUsuario().getValor()){
        it->second = projeto;
        return true;
        }
    }
    return false;
}

