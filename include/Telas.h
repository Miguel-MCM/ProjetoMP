#ifndef INCLUDE_TELAS_H_
#define INCLUDE_TELAS_H_

#include "Entidades.h"
#include <map>

#include <string>
#include <vector>
#include <list>
#ifdef WIN32
    #include "curses.h"
#else
    #include <ncurses.h>
#endif  // WIN32

using std::vector;
using std::to_string;

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

class TelaMensagens:public Tela {
 public:
    void apresentar(vector<string>);
};

class TelaConsultaUsuario: public Tela {
 public:
    char apresentar(Usuario*);
};

class TelaConfirmacao:public Tela {
 public:
    bool apresentar();
};

class TelaAutenticacao: public Tela {
public:
    void apresentar(Usuario*);
};

class TelaCadastro: public Tela {
public:
    void apresentar(Usuario*);
};

class TelaConsultarTurmas: public Tela {
 public:
    string apresentar(list<Turma>);
};

class TelaOpcoesProvas: public Tela {
public:
    int apresentar(list<Prova>);
};

class TelaMenuProva: public Tela {
public:
    char apresentar();
};

class TelaConsultaProva: public Tela {
public:
    char apresentar(Prova*, int);
};

class TelaCadastroProva: public Tela {
public:
    void apresentar(Prova*,int);
};

class TelaEdicaoProva: public Tela {
public:
    void apresentar(Prova*);
};


class TelaBusca: public Tela {
public:
    string apresentar(string);
};

class TelaConsultarProvas: public Tela {
public:
    string apresentar(list<Prova>);
};

class TelaListarAlunos: public Tela {
public:
    void apresentar(list<Usuario>);
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


class TelaCodigo {
public:
    void apresentar(Codigo*);
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
