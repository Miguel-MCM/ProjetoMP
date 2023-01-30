#include "Containers.h"
#include "Telas.h"

#include <list>
#include <iostream>

ContainerUsuario* ContainerUsuario::instancia = nullptr;

//------------------------------------------------------------------------------------
// Implementa��es de m�todos de classe container.

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



ContainerProva* ContainerProva::instancia = nullptr;


ContainerProva* ContainerProva::getInstancia() {
    if (instancia == nullptr)
        instancia = new ContainerProva();
    return instancia;
}

bool ContainerProva::incluir(Prova prova){
    return container.insert(make_pair(prova.getCodigo().getValor(), prova)).second;
}

bool ContainerProva::remover(Codigo codigo){
    map<string, Prova>::iterator it = container.find(codigo.getValor());
    if(it != container.end()){
        container.erase(it);
        return true;
    }
    return false;
}

bool ContainerProva::pesquisar(Prova* prova){
    map<string, Prova>::iterator it = container.find(prova->getCodigo().getValor());
    if(it != container.end()){
            if(it->second.getUsuario().getValor() == prova->getUsuario().getValor()){
               *prova = it->second;
               return true;
            }
    }
    return false;
}

bool ContainerProva::atualizar(Prova prova){
    map<string, Prova>::iterator it = container.find(prova.getCodigo().getValor());
    if(it != container.end()){
        if(it->second.getUsuario().getValor() == prova.getUsuario().getValor()){
        it->second = prova;
        return true;
        }
    }
    return false;
}


ContainerQuestao* ContainerQuestao::instancia = nullptr;


ContainerQuestao* ContainerQuestao::getInstancia() {
    if (instancia == nullptr)
        instancia = new ContainerQuestao();
    return instancia;
}

bool ContainerQuestao::incluir(Questao questao){
    return container.insert(make_pair(questao.getCodigo().getValor(), questao)).second;
}

bool ContainerQuestao::remover(Codigo codigo){
    map<string, Questao>::iterator it = container.find(codigo.getValor());
    if(it != container.end()){
        container.erase(it);
        return true;
    }
    return false;
}

bool ContainerQuestao::pesquisar(Questao* questao){
    map<string, Questao>::iterator it = container.find(questao->getCodigo().getValor());
    if(it != container.end()){
            if(it->second.getUsuario().getValor() == questao->getUsuario().getValor()){
               *questao = it->second;
               return true;
            }
    }
    return false;
}

bool ContainerQuestao::atualizar(Questao questao){
    map<string, Questao>::iterator it = container.find(questao.getCodigo().getValor());
    if(it != container.end()){
        if(it->second.getUsuario().getValor() == questao.getUsuario().getValor()){
        it->second = questao;
        return true;
        }
    }
    return false;
}

bool ContainerQuestao::removerPorProva(Codigo prova) {
    //map<string, Questao>::iterator it;
    list<Codigo> paraRemover;
    for (map<string, Questao>::iterator it = container.begin(); it != container.end(); ++it) {
        if (it->second.getProva().getValor() == prova.getValor()) {
                paraRemover.push_front(it->second.getCodigo());
        }
    }

    for (list<Codigo>::iterator it = paraRemover.begin(); it != paraRemover.end(); ++it) {
        remover(*it);
    }
    return true;
}