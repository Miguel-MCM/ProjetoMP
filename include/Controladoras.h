#ifndef INCLUDE_CONTROLADORAS_H_
#define INCLUDE_CONTROLADORAS_H_

#include <map>
#include <string>
#include <list>
#include "Interfaces.h"
#include <vector>
#include "./curses.h"
#include "ComandosSQL.h"

using std::string;
using std::list;

class CntrApresentacaoUsuario:public IApresentacaoUsuario {
 private:
    bool status;
    IServicoUsuario * cntrServicoUsuario;
    IServicoAdmin* cntrServicoAdmin;
    IApresentacaoTurma * cntrApresentacaoTurma;
    void editar(Usuario*);
    void minhasTurmas(Usuario*);
 public:
    void executar(Usuario*);
    void cadastrar();

    void setCntrServicoUsuario(IServicoUsuario*);
    void setCntrServicoAdmin(IServicoAdmin*);
    void setCntrApresentacaoTurma(IApresentacaoTurma*);

    bool getStatusCadastro() {return false;}
    void setStatusCadastro(bool);
};

inline void CntrApresentacaoUsuario::setCntrServicoUsuario(IServicoUsuario * cntr) {
    cntrServicoUsuario = cntr;
}

inline void CntrApresentacaoUsuario::setCntrServicoAdmin(IServicoAdmin * cntr) {
    cntrServicoAdmin = cntr;
}

inline void CntrApresentacaoUsuario::setCntrApresentacaoTurma(IApresentacaoTurma* cntr) {
    cntrApresentacaoTurma = cntr;
}

inline void CntrApresentacaoUsuario::setStatusCadastro(bool status) {
    this->status = status;
}
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

inline void CntrApresentacaoControle::setCntrApresentacaoTurma(IApresentacaoTurma* cntr) {
    cntrApresentacaoTurma = cntr;
}

inline void CntrApresentacaoControle::setCntrApresentacaoAdmin(IApresentacaoAdmin* cntr) {
    cntrApresentacaoAdmin = cntr;
}

class CntrApresentacaoAutenticacao:public IApresentacaoAutenticacao {
 private:
    IServicoAutenticacao* cntrServicoAutenticacao;
 public:
    bool autenticar(Usuario*);
    void setCntrServicoAutenticacao(IServicoAutenticacao*);
};

inline void CntrApresentacaoAutenticacao::setCntrServicoAutenticacao(IServicoAutenticacao* cntrServicoAutenticacao) {
    this->cntrServicoAutenticacao = cntrServicoAutenticacao;
}

class CntrApresentacaoTurma:public IApresentacaoTurma {
 private:
    IServicoTurma* cntrServicoTurma;
    IServicoUsuario* cntrServicoUsuario;
    IApresentacaoProva* cntrApresentacaoProva;

 public:
    void executar(Usuario*);
    void editar(Turma*);

    void setCntrServicoUsuario(IServicoUsuario*);
    void setCntrServicoTurma(IServicoTurma*);
    void setCntrApresentacaoProva(IApresentacaoProva*);
    
};

inline void CntrApresentacaoTurma::setCntrServicoTurma(IServicoTurma* cntr) {
    cntrServicoTurma = cntr;
}

inline void CntrApresentacaoTurma::setCntrServicoUsuario(IServicoUsuario* cntr) {
    cntrServicoUsuario = cntr;
}

inline void CntrApresentacaoTurma::setCntrApresentacaoProva(IApresentacaoProva* cntr) {
    cntrApresentacaoProva = cntr;
}

class CntrApresentacaoProva:public IApresentacaoProva {
 private:
        IServicoTurma* cntrServicoTurma;
        IServicoProva* cntrServicoProva;
 public:
        void executar(Turma*);
        void gerenciar(Prova*);
        void editar(Prova*);
        void setCntrServicoProva(IServicoProva*);
        void setCntrServicoTurma(IServicoTurma*);
};

void inline CntrApresentacaoProva::setCntrServicoProva(IServicoProva* cntrServicoProva) {
    this->cntrServicoProva = cntrServicoProva;
}

inline void CntrApresentacaoProva::setCntrServicoTurma(IServicoTurma* cntrServicoTurma) {
    this->cntrServicoTurma = cntrServicoTurma;
}

class CntrApresentacaoAdmin:public IApresentacaoAdmin {
 private:
        IServicoAdmin* cntrServicoAdmin;
        IServicoUsuario* cntrServicoUsuario;
        IServicoTurma* cntrServicoTurma;
        IServicoProva* cntrServicoProva;

        IApresentacaoUsuario* cntrApresentacaoUsuario;
        IApresentacaoProva* cntrApresentacaoProva;
        IApresentacaoTurma* cntrApresentacaoTurma;
 public:
        void executar(Usuario*);

        void setCntrServicoAdmin(IServicoAdmin*);
        void setCntrServicoUsuario(IServicoUsuario*);
        void setCntrApresentacaoUsuario(IApresentacaoUsuario*);
        void setCntrApresentacaoProva(IApresentacaoProva*);
        void setCntrApresentacaoTurma(IApresentacaoTurma*);
        void setCntrServicoTurma(IServicoTurma*);
        void setCntrServicoProva(IServicoProva*);
};

inline void CntrApresentacaoAdmin::setCntrServicoAdmin(IServicoAdmin* cntrServicoAdmin) {
    this->cntrServicoAdmin = cntrServicoAdmin;
}

inline void CntrApresentacaoAdmin::setCntrServicoUsuario(IServicoUsuario* cntrServicoUsuario) {
    this->cntrServicoUsuario = cntrServicoUsuario;
}

inline void CntrApresentacaoAdmin::setCntrServicoTurma(IServicoTurma* cntrServicoTurma) {
    this->cntrServicoTurma = cntrServicoTurma;
}

inline void CntrApresentacaoAdmin::setCntrServicoProva(IServicoProva* cntrServicoProva) {
    this->cntrServicoProva = cntrServicoProva;
}

inline void CntrApresentacaoAdmin::setCntrApresentacaoUsuario(IApresentacaoUsuario* cntr) {
    cntrApresentacaoUsuario = cntr;
}

inline void CntrApresentacaoAdmin::setCntrApresentacaoProva(IApresentacaoProva* cntr) {
    cntrApresentacaoProva = cntr;
}

inline void CntrApresentacaoAdmin::setCntrApresentacaoTurma(IApresentacaoTurma* cntr) {
    cntrApresentacaoTurma = cntr;
}

class CntrServicoAutenticacao:public IServicoAutenticacao{
 public:
        bool autenticar(Usuario);
};

class CntrServicoUsuario:public IServicoUsuario {
 public:
        bool cadastrar(Usuario);
        bool descadastrar(int, string); // id e cargo
        bool editar(Usuario);
        bool consultar(Usuario*);
        bool listarTurmasAluno(int, list<Turma>*); // id aluno
        bool listarTurmasProfessor(int, list<Turma>*);
        ~CntrServicoUsuario() {}
};

class CntrServicoTurma:public IServicoTurma {
 public:
    bool cadastrar(Turma);
    bool consultar(Turma*);
    bool descadastrar(int);
    bool editar(Turma*);

    bool entrar(int, int);
    bool listarTurmas(list<Turma>*);
    bool listarProvas(int, list<Prova>*);
    bool listarAlunos(int, list<Usuario>*);

    ~CntrServicoTurma() {}
};

class CntrServicoAdmin:public IServicoAdmin {
 public:
        bool estatisticas(vector<string>*);
};

class CntrServicoProva:public IServicoProva{
 public:
        bool cadastrarProva(Prova);
        bool descadastrarProva(int);
        bool editarProva(Prova);
        bool consultarProva(Prova*);
        bool getQtdQuestoes(Prova, int*) {return false;} 
        vector<string> getProvas();

        bool cadastrarQuestao(Questao);
        bool descadastrarQuestao(int);
        bool editarQuestao(Questao);
        bool consultarQuestao(Questao*);
        bool getListaQuestoes(list<int>, list<Questao>*);
};

#endif   // INCLUDE_CONTROLADORAS_H_