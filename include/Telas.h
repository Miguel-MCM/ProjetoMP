#ifndef INCLUDE_TELAS_H_
#define INCLUDE_TELAS_H_

#include "Entidades.h"
#include <stdlib.h>
#include <string>
#include <vector>
#ifdef WIN32
    #include "curses.h"
#else
    #include <ncurses.h>
#endif  // WIN32

using std::vector;

class Tela {
 protected:
    void mostrarLinhas(vector<string>, int, int, int);
    void mostrarLinhas(vector<string>, int, int);
};

template <class entidade>
class TelaApresentacao:public Tela {
 public:
    virtual void apresentar(entidade) = 0;
};

class TelaMenu:public Tela {
 public:
    string apresentar(string, vector<string>);
};

class TelaFormulario:public Tela {
 public:
    void apresentar(string, vector<string>, string *);
};


/*
class TelaAutenticacao {
public:
    void apresentar(Matricula*, Senha*);
};

class TelaMensagem:public TelaApresentacao<string> {
 public:
    void apresentar(string);
};

class TelaCadastro {
public:
    void apresentar(Usuario*);
};

class TelaMenuUsuario {
public:
    char apresentar();
};

class TelaDescadastro {
public:
    char apresentar();
};

class TelaControle {
public:
    char apresentar();
};

class TelaMenu {
public:
    char apresentar();
};

class TelaMenuProva {
public:
    char apresentar();
};

class TelaCodigo {
public:
    void apresentar(Codigo*);
};

class TelaConsultaProva {
public:
    char apresentar(Prova*);
};

class TelaCadastroProva {
public:
    void apresentar(Prova*);
};

class TelaEdicaoProva {
public:
    void apresentar(Prova*);
};

class TelaConsultarUsuario {
public:
    char apresentar(Usuario);
};

class TelaEdicaoUsuario {
public:
    void apresentar(Usuario *);
};

class TelaCadastroQuestao {
public:
    void apresentar(Questao*);
};

class TelaConsultaQuestao {
public:
    char apresentar(Questao*);
};

class TelaEdicaoQuestao {
public:
    void apresentar(Questao *);
};
*/


#endif  // INCLUDE_TELAS_H_
