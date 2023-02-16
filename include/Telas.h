#ifndef INCLUDE_TELAS_H_
#define INCLUDE_TELAS_H_

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Entidades.h"

#ifdef WIN32
    #include "curses.h"
#else
    #include <ncurses.h>
#endif  // WIN32

#include <string.h>

using std::vector;
using std::to_string;

class Tela {
 public:
    const int LIMITE_CHAR = 40;
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
    string apresentar(list<Turma>, bool);
};

class TelaOpcoesProvas: public Tela {
public:
    int apresentar(list<Prova>);
};

class TelaMenuProva: public Tela {
public:
    char apresentar(string);
};

class TelaConsultaProva: public Tela {
public:
    char apresentar(Prova*);
};

class TelaCadastroProva: public Tela {
public:
    void apresentar(Prova*,int);
};

class TelaBusca: public Tela {
public:
    string apresentar(string);
};

class TelaConsultarProvas: public Tela {
public:
    string apresentar(list<Prova>);
};

class TelaInfoProvas: public Tela {
 public:
    void apresentar(list<Prova>);
};

class TelaListarAlunos: public Tela {
public:
    void apresentar(list<Usuario>);
};

class TelaDefinicaoTipoQuestao: public Tela  {
public:
    char apresentar();
};

class TelaCadastroQuestao: public Tela  {
public:
    void apresentarCriarMultiplaEscolha(Questao*);
    void apresentarCriarCertoErrado(Questao*);
    void apresentarCriarNumerico(Questao*);
};

class TelaConsultaQuestao: public Tela  {
public:
    void apresentar(list<Questao>);
};

class TelaOpcoesQuestoes: public Tela  {
public:
    int apresentar(list<Questao>);
};

class TelaRealizarProva: public Tela {
 public:
    Resposta apresentar(list<Questao>);
};

class TelaEdicaoProva: public Tela  {
public:
    char apresentar(Prova*);
};

class TelaMostrarResultados: public Tela {
 public:
    void apresentar(list<Questao>, list<int>);
};

class TelaMostrarResultadosProva: public Tela {
 public:
    void apresentar(Prova, list<Usuario>, list<int>);
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


//class TelaCodigo {
//public:
//    void apresentar(Codigo*);
//};

class TelaConsultarUsuario {
public:
    void apresentar(Usuario *);
};

*/



#endif  // INCLUDE_TELAS_H_
