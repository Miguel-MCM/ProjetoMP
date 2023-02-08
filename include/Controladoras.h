#ifndef INCLUDE_CONTROLADORAS_H_
#define INCLUDE_CONTROLADORAS_H_

#include <map>
#include <string>
#include <list>
#include "Interfaces.h"
#include "./curses.h"
#include <string>

using std::string;

using std::list;

class CntrApresentacaoUsuario:public IApresentacaoUsuario {
 private:
    IServicoUsuario * cntrServicoUsuario;
    void editar(Usuario*);
    void minhasTurmas(Usuario*);
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

class CntrApresentacaoTurma:public IApresentacaoTurma {
 public:
    void executar(Usuario*);
    void setCntrServicoTurma(IServicoTurma*);

    ~CntrApresentacaoTurma() {}
};

inline void CntrApresentacaoTurma::setCntrServicoTurma(IServicoTurma* cntr) {cntrServicoTurma = cntr;}

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
        void executar();

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
        bool cadastrar(Usuario){return false;}
        bool descadastrar(Usuario){return false;}
        bool editar(Usuario){return false;}
        bool consultar(Usuario*){return false;}
        bool listarTurmas(int, map<Turma, string>*){return false;}
        ~CntrServicoUsuario() {}
};

class CntrServicoTurma:public IServicoTurma {
 public:
    bool cadastrar(Turma) {return false;}
    bool consultar(Turma*) {return false;}
    bool descadastrar(int) {return false;}
    bool editar(Turma) {return false;}
    bool listarAbertas(list<Turma>*) {return false;}
    bool listarProvas(int, list<Prova>*) {return false;}
    bool listarAlunos(int, list<Usuario>*) {return false;}

    ~CntrServicoTurma() {}
}

class CntrServicoAdmin:public IServicoAdmin {
 public:
        bool numeroDeUsuarios(string*);
        bool numeroDeQuestoes(string*);
        bool numeroDeProvas(string*);
        bool numeroDeRespostas(string*);

        bool consultarUsuario(Usuario*);
        bool consultarTurma(Usuario*);
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
