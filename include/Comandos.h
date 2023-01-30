#ifndef COMANDOS_H_INCLUDED
#define COMANDOS_H_INCLUDED

#include "Interfaces.h"
#include "Telas.h"
#include <stdexcept>
#include <cstdlib>

class ComandoIAUsuario {
public:
    virtual void executar(IServicoUsuario*, Matricula*) = 0;
    virtual ~ComandoIAUsuario(){}
};

class ComandoIAUsuarioDescadastrar:public ComandoIAUsuario {
    void executar(IServicoUsuario*, Matricula*);
};

class ComandoIAUsuarioEditar:public ComandoIAUsuario {
    void executar(IServicoUsuario*, Matricula*);
};

class ComandoIAUsuarioConsultar: public ComandoIAUsuario {
    void executar(IServicoUsuario*, Matricula*);
};

class ComandoIAProva {
public:
    virtual void executar(IServicoProva*, Matricula*) = 0;
    virtual ~ComandoIAProva(){}
};

class ComandoIAProvaConsultarProva:public ComandoIAProva {
public:
    void executar(IServicoProva*, Matricula*);
};

class ComandoIAProvaCadastrarProva:public ComandoIAProva {
public:
    void executar(IServicoProva*, Matricula*);
};

class ComandoIAProvaEditarProva {
public:
    void executar(IServicoProva*, Prova);
};

class ComandoISProvaConsultarProva {
public:
    bool executar(Prova* prova);
};

class ComandoISProvaCadastrarProva {
public:
    bool executar(Prova);
};

class ComandoISProvaEditarProva {
public:
    bool executar(Prova);
};


#endif // COMANDOS_H_INCLUDED


