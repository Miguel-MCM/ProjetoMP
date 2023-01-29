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
        IApresentacaoProjeto* cntrApresentacaoProjeto;
        void menuAutenticado(Matricula*);

    public:
        void executar();
        void setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao*);
        void setCntrApresentacaoUsuario(IApresentacaoUsuario*);
        void setCntrlApresentacaoProjeto(IApresentacaoProjeto*);
};

inline void CntrApresentacaoControle::setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao* cntr){
    cntrApresentacaoAutenticacao = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoUsuario(IApresentacaoUsuario* cntr){
    cntrApresentacaoUsuario = cntr;
}

inline void CntrApresentacaoControle::setCntrlApresentacaoProjeto(IApresentacaoProjeto* cntr){
    cntrApresentacaoProjeto = cntr;
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

class CntrApresentacaoProjeto:public IApresentacaoProjeto {
    private:
        IServicoProjeto* cntrServicoProjeto;
    public:
        void executar(Matricula*);
        void setCntrServicoProjeto(IServicoProjeto*);
};

void inline CntrApresentacaoProjeto::setCntrServicoProjeto(IServicoProjeto* cntrServicoProjeto){
    this->cntrServicoProjeto = cntrServicoProjeto;
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

class CntrServicoProjeto:public IServicoProjeto{
public:
        bool cadastrarProjeto(Projeto);
        bool descadastrarProjeto(Codigo);
        bool editarProjeto(Projeto);
        bool consultarProjeto(Projeto*);
        bool cadastrarTarefa(Tarefa);
        bool descadastrarTarefa(Codigo);
        bool editarTarefa(Tarefa);
        bool consultarTarefa(Tarefa*);
};

#endif // CONTROLADORAS_H_INCLUDED
