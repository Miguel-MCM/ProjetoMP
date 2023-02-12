#ifndef INCLUDE_CONTROLADORAS_H_
#define INCLUDE_CONTROLADORAS_H_

#include "Interfaces.h"
#include "./curses.h"
#include <string>

using std::string;

class CntrApresentacaoUsuario:public IApresentacaoUsuario {
 private:
    IServicoUsuario * cntrServicoUsuario;
    void editar(Usuario*);

 public:
    void executar(Usuario*);
    void cadastrar() {}
    void setCntrServicoUsuario(IServicoUsuario*);
    void setCntrServicoAdmin(IServicoAdmin*);

    bool getStatusCadastro() {return false;}
    void setStatusCadastro(bool){}
};

inline void CntrApresentacaoUsuario::setCntrServicoUsuario(IServicoUsuario * cntr) {cntrServicoUsuario = cntr;}


class CntrApresentacaoControle{
 private:
        Usuario usuario;
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        IApresentacaoUsuario* cntrApresentacaoUsuario;
        IApresentacaoAdmin* cntrApresentacaoAdmin;
        IApresentacaoProva* cntrApresentacaoProva;
        IApresentacaoTurma* cntrApresentacaoTurma;
 public:
        void executar();
        void setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao*);
        void setCntrApresentacaoUsuario(IApresentacaoUsuario*);
        void setCntrApresentacaoAdmin(IApresentacaoAdmin*);
        void setCntrApresentacaoProva(IApresentacaoProva*);
        void setCntrApresentacaoTurma(IApresentacaoTurma*);
};

inline void CntrApresentacaoControle::setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao* cntr) {
    cntrApresentacaoAutenticacao = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoUsuario(IApresentacaoUsuario* cntr) {
    cntrApresentacaoUsuario = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoProva(IApresentacaoProva* cntr) {
    cntrApresentacaoProva = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoAdmin(IApresentacaoAdmin* cntr) {
    cntrApresentacaoAdmin = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoTurma(IApresentacaoTurma* cntr) {
    cntrApresentacaoTurma = cntr;
}

class CntrApresentacaoAutenticacao:public IApresentacaoAutenticacao {
 private:
    IServicoAutenticacao* cntrServicoAutenticacao;
 public:
    bool autenticar(Usuario*);
    void setCntrServicoAutenticacao(IServicoAutenticacao*);
};

void inline CntrApresentacaoAutenticacao::setCntrServicoAutenticacao(IServicoAutenticacao* cntrServicoAutenticacao) {
    this->cntrServicoAutenticacao = cntrServicoAutenticacao;
}

class CntrApresentacaoProva:public IApresentacaoProva {
 private:
        IServicoProva* cntrServicoProva;
 public:
        void executar(Usuario*);
        void setCntrServicoProva(IServicoProva*);
};

void inline CntrApresentacaoProva::setCntrServicoProva(IServicoProva* cntrServicoProva) {
    this->cntrServicoProva = cntrServicoProva;
}

class CntrApresentacaoAdmin:public IApresentacaoAdmin {
 private:
        IServicoAdmin* cntrServicoAdmin;
        IApresentacaoUsuario* cntrApresentacaoUsuario;
        IApresentacaoProva* cntrApresentacaoProva;
        IApresentacaoTurma* cntrApresentacaoTurma;
 public:
        void executar(Usuario*);

        void setCntrServicoAdmin(IServicoAdmin*);
        void setCntrApresentacaoUsuario(IApresentacaoUsuario*);
        void setCntrApresentacaoProva(IApresentacaoProva*);
        void setCntrApresentacaoTurma(IApresentacaoTurma*);
}

inline void CntrApresentacaoAdmin::setCntrServicoAdmin(IServicoAdmin* cntrServicoAdmin) {
    this->cntrServicoAdmin = cntrServicoAdmin;
}
inline void CntrApresentacaoControle::setCntrApresentacaoUsuario(IApresentacaoUsuario* cntr) {
    cntrApresentacaoUsuario = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoProva(IApresentacaoProva* cntr) {
    cntrApresentacaoProva = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoTurma(IApresentacaoTurma* cntr) {
    cntrApresentacaoTurma = cntr;
}

class CntrApresentacaoTurma : public IApresentacaoTurma {
 private:
    IServicoTurma *cntrServicoTurma;

 public:
    void executar(Usuario *);
    void setCntrServicoTurma(IServicoTurma *);
};

void inline CntrApresentacaoTurma::setCntrServicoTurma(IServicoTurma *cntrServicoTurma) {
    this->cntrServicoTurma = cntrServicoTurma;
}

class CntrServicoAutenticacao:public IServicoAutenticacao{
    public:
        bool autenticar(Usuario);
};

class CntrServicoUsuario:public IServicoUsuario {
 public:
        bool cadastrar(Usuario);
        bool descadastrar(Usuario);
        bool editar(Usuario);
        bool consultar(Usuario*);
};

class CntrServicoAdmin:public IServicoAdmin {
 public:
        bool numeroDeUsuarios(string*);
        bool numeroDeQuestoes(string*);
        bool numeroDeProvas(string*);
        bool numeroDeRespostas(string*);

        bool consultarUsuario(Usuario*);
        bool consultarTurma(Turma*);
};

// class CntrServicoProva:public IServicoProva{
//  public:
//         bool cadastrarProva(Prova);
//         bool descadastrarProva(Codigo);
//         bool editarProva(Prova);
//         bool consultarProva(Prova*);
//         bool cadastrarQuestao(Questao);
//         bool descadastrarQuestao(Codigo);
//         bool editarQuestao(Questao);
//         bool consultarQuestao(Questao*);
// };

#endif   // INCLUDE_CONTROLADORAS_H_
