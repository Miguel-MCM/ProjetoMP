#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED

#include "Interfaces.h"
#include "curses.h"

#include <stdexcept>

using namespace std;

class CntrApresentacaoControle{
    private:
        Matricula matricula;
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        IApresentacaoUsuario* cntrApresentacaoUsuario;
        IApresentacaoProva* cntrApresentacaoProva;
        void menuAutenticado(Matricula*);

    public:
        void executar();
        void setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao*);
        void setCntrApresentacaoUsuario(IApresentacaoUsuario*);
        void setCntrlApresentacaoProva(IApresentacaoProva*);
};

inline void CntrApresentacaoControle::setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao* cntr){
    cntrApresentacaoAutenticacao = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoUsuario(IApresentacaoUsuario* cntr){
    cntrApresentacaoUsuario = cntr;
}

inline void CntrApresentacaoControle::setCntrlApresentacaoProva(IApresentacaoProva* cntr){
    cntrApresentacaoProva = cntr;
}


class CntrApresentacaoAutenticacao:public IApresentacaoAutenticacao {
private:
    IServicoAutenticacao* cntrServicoAutenticacao;
public:
    bool autenticar(Matricula*);
    void setCntrServicoAutenticacao(IServicoAutenticacao*);
};

void inline CntrApresentacaoAutenticacao::setCntrServicoAutenticacao(IServicoAutenticacao* cntrServicoAutenticacao){
    this->cntrServicoAutenticacao = cntrServicoAutenticacao;
}

class CntrApresentacaoUsuario:public IApresentacaoUsuario {
private:
    IServicoUsuario* cntrServicoUsuario;
    bool cadastro;
public:
    void executar(Matricula*);
    void cadastrar();
    void setCntrServicoUsuario(IServicoUsuario*);
    bool getStatusCadastro();
    void setStatusCadastro(bool);
    void editar();
};

void inline CntrApresentacaoUsuario::setCntrServicoUsuario(IServicoUsuario* cntrServicoUsuario){
    this->cntrServicoUsuario = cntrServicoUsuario;
}

bool inline CntrApresentacaoUsuario::getStatusCadastro() {
    return cadastro;
}

void inline CntrApresentacaoUsuario::setStatusCadastro(bool status) {
    cadastro = status;
}

class CntrApresentacaoProva:public IApresentacaoProva {
    private:
        IServicoProva* cntrServicoProva;
    public:
        void executar(Matricula*);
        void setCntrServicoProva(IServicoProva*);
};

void inline CntrApresentacaoProva::setCntrServicoProva(IServicoProva* cntrServicoProva){
    this->cntrServicoProva = cntrServicoProva;
}

class CntrServicoAutenticacao:public IServicoAutenticacao{
    public:
        bool autenticar(Matricula, Senha);
};

class CntrServicoUsuario:public IServicoUsuario{
    public:
        bool cadastrar(Usuario);
        bool descadastrar(Matricula);
        bool editar(Usuario);
        bool consultar(Usuario*);
};

class CntrServicoProva:public IServicoProva{
public:
        bool cadastrarProva(Prova);
        bool descadastrarProva(Codigo);
        bool editarProva(Prova);
        bool consultarProva(Prova*);
        bool cadastrarQuestao(Questao);
        bool descadastrarQuestao(Codigo);
        bool editarQuestao(Questao);
        bool consultarQuestao(Questao*);
};

#endif // CONTROLADORAS_H_INCLUDED
