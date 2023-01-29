#ifndef TELAS_H_INCLUDED
#define TELAS_H_INCLUDED

#include "Entidades.h"
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
    #include "curses.h"
#else
    #include <ncurses.h>

#endif // WIN32

class TelaAutenticacao {
public:
    void apresentar(Matricula*, Senha*);
};

class TelaMensagem {
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

class TelaMenuProjeto {
public:
    char apresentar();
};

class TelaCodigo {
public:
    void apresentar(Codigo*);
};

class TelaConsultaProjeto {
public:
    char apresentar(Projeto*);
};

class TelaCadastroProjeto {
public:
    void apresentar(Projeto*);
};

class TelaEdicaoProjeto {
public:
    void apresentar(Projeto*);
};

class TelaConsultarUsuario {
public:
    char apresentar(Usuario);
};

class TelaEdicaoUsuario {
public:
    void apresentar(Usuario *);
};

#endif // TELAS_H_INCLUDED
