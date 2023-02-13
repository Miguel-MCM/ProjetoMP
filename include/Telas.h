#ifndef INCLUDE_TELAS_H_
#define INCLUDE_TELAS_H_

#include "Entidades.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
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

class TelaMensagem:public Tela {
 public:
    void apresentar(string);
};

class TelaConsultaUsuario: public Tela {
 public:
    char apresentar(Usuario*);
};

class TelaConfirmacao:public Tela {
 public:
    bool apresentar();
};

class TelaAutenticacao {
public:
    void apresentar(Usuario*);
};

class TelaCadastro {
public:
    void apresentar(Usuario*);
};

/*
class TelaMensagem:public TelaApresentacao<string> {
 public:
    void apresentar(string);
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
*/

class TelaOpcoesProvas{
public:
    int apresentar(list<Prova>);
};

class TelaMenuProva {
public:
    char apresentar();
};


//class TelaCodigo {
//public:
//    void apresentar(Codigo*);
//};

class TelaConsultaProva {
public:
    char apresentar(Prova*, int);
};

class TelaCadastroProva {
public:
    void apresentar(Prova*, int);
};

class TelaEdicaoProva {
public:
    char apresentar(Prova*);
};
/*
class TelaConsultarUsuario {
public:
    char apresentar(Usuario);
};

class TelaEdicaoUsuario {
public:
    void apresentar(Usuario *);
};

*/
class TelaDefinicaoTipoQuestao {
public:
    char apresentar();
};

class TelaCadastroQuestao {
public:
    void apresentarCriarMultiplaEscolha(Questao*);
    void apresentarCriarCertoErrado(Questao*);
    void apresentarCriarNumerico(Questao*);
};
/*

class TelaConsultaQuestao {
public:
    char apresentar(Questao*);
};

class TelaEdicaoQuestao {
public:
    void apresentar(Questao *);
};
*/

class TelaOpcoesQuestoes {
public:
    int apresentar(list<Questao>);
}


#endif  // INCLUDE_TELAS_H_
