#ifndef INCLUDE_INTERFACES_H_
#define INCLUDE_INTERFACES_H_

#include "Entidades.h"
#include <string>
#include <list>

using std::string;
using std::list;

class IServicoUsuario;
class IServicoAdmin;
class IServicoAutenticacao;
class IServicoTurma;
class IServicoProva;
class IServicoQuestao;

class IApresentacaoAutenticacao {
 public:
        virtual bool autenticar(Usuario*) = 0;
        virtual void setCntrServicoAutenticacao(IServicoAutenticacao*) = 0;
        virtual ~IApresentacaoAutenticacao(){}
};

class IApresentacaoUsuario {
 public:
        virtual void executar(Usuario*) = 0;
        virtual void cadastrar() = 0;
        virtual void setCntrServicoUsuario(IServicoUsuario*) = 0;


        virtual bool getStatusCadastro() = 0;
        virtual void setStatusCadastro(bool) = 0;

        virtual ~IApresentacaoUsuario(){}
};

class IApresentacaoAdmin {
 public:
    virtual void executar(Usuario*) = 0;
    virtual void setCntrServicoAdmin(IServicoAdmin*) = 0;

    virtual ~IApresentacaoAdmin() {}
};

class IApresentacaoTurma {
 public:
    virtual void executar(Usuario*) = 0;
    virtual void setCntrServicoTurma(IServicoTurma*) = 0;

    virtual ~IApresentacaoTurma() {}
};

class IApresentacaoProva {
 public:
        virtual void executar(Usuario*) = 0;
        virtual void gerenciar(Prova*) = 0;
        virtual void interfaceEdicao(Prova*) = 0;
        virtual void setCntrServicoProva(IServicoProva*) = 0;
        virtual void setCntrServicoQuestao(IServicoQuestao*) = 0;

        virtual ~IApresentacaoProva() {}
};

class IServicoAutenticacao {
 public:
        virtual bool autenticar(Usuario) = 0;
        virtual ~IServicoAutenticacao() {}
};

class IServicoUsuario {
 public:
        virtual bool cadastrar(Usuario) = 0;
        virtual bool descadastrar(int) = 0;
        virtual bool editar(Usuario) = 0;
        virtual bool consultar(Usuario*) = 0;
        virtual bool listarTurmas(int, list<Turma>*) = 0;
        virtual ~IServicoUsuario() {}
};

class IServicoProva {
 public:
        virtual bool cadastrarProva(Prova) = 0;
        virtual bool descadastrarProva(int) = 0;
        virtual bool editarProva(Prova) = 0;
        virtual bool consultarProva(Prova*) = 0;
        virtual bool consultarResposta(Resposta*) = 0;
        virtual bool cadastrarResposta(Resposta) = 0;
        virtual bool getQtdQuestoes(Prova, int*) = 0;

        virtual bool cadastrarQuestao(Questao) = 0;
        virtual bool descadastrarQuestao(int) = 0;
        virtual bool editarQuestao(Questao) = 0;
        virtual bool consultarQuestao(Questao*) = 0;
        virtual bool getListaQuestoes(list<int>) = 0;
        virtual ~IServicoProva() {}
};

//class IServicoQuestao {
// public:
//        virtual bool cadastrar(Questao) = 0;
//        virtual bool descadastrar(int) = 0;
//        virtual bool editar(Questao) = 0;
//        virtual bool consultar(Questao*) = 0;
//
//        ~IServicoQuestao() {}
//};

class IServicoTurma {
 public:
        virtual bool cadastrar(Turma) = 0;
        virtual bool consultar(Turma*) = 0;
        virtual bool descadastrar(int) = 0;
        virtual bool editar(Turma) = 0;
        virtual bool listarAbertas(list<Turma>*) = 0;
        virtual bool listarProvas(int, list<Prova>*) = 0;
        virtual bool listarAlunos(int, list<Usuario>*) = 0;

        virtual ~IServicoTurma() {}
};

class IServicoAdmin {
 public:
    virtual int numeroDeUsuarios() = 0;
    virtual int numeroDeQuestoes() = 0;
    virtual int numeroDeProvas() = 0;
    virtual int numeroDeRespostas() = 0;
    virtual ~IServicoAdmin() {}
};
#endif  //  INCLUDE_INTERFACES_H_
