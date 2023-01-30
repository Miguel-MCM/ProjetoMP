#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "Entidades.h"
#include "Containers.h"

class IServicoAutenticacao;
class IServicoUsuario;
class IServicoProva;

class IApresentacaoAutenticacao {
    public:
        virtual bool autenticar(Matricula*) = 0;
        virtual void setCntrServicoAutenticacao(IServicoAutenticacao*) = 0;
        virtual ~IApresentacaoAutenticacao(){}
};

class IApresentacaoUsuario {
    public:
        virtual void executar(Matricula*) = 0;
        virtual void cadastrar() = 0;
        virtual void setCntrServicoUsuario(IServicoUsuario*) = 0;

        virtual bool getStatusCadastro() = 0;
        virtual void setStatusCadastro(bool) = 0;

        virtual ~IApresentacaoUsuario(){}
};

class IApresentacaoProva {
    public:
        virtual void executar(Matricula*) = 0;
        virtual void setCntrServicoProva(IServicoProva*) = 0;
        virtual ~IApresentacaoProva(){}
};

class IServicoAutenticacao {
    public:
        virtual bool autenticar(Matricula, Senha) = 0;
        virtual ~IServicoAutenticacao(){}
};

class IServicoUsuario {
    public:
        virtual bool cadastrar(Usuario) = 0;
        virtual bool descadastrar(Matricula) = 0;
        virtual bool editar(Usuario) = 0;
        virtual bool consultar(Usuario*) = 0;
        virtual ~IServicoUsuario(){}
};

class IServicoProva {
    public:
        virtual bool cadastrarProva(Prova) = 0;
        virtual bool descadastrarProva(Codigo) = 0;
        virtual bool editarProva(Prova) = 0;
        virtual bool consultarProva(Prova*) = 0;
        virtual bool cadastrarQuestao(Questao) = 0;
        virtual bool descadastrarQuestao(Codigo) = 0;
        virtual bool editarQuestao(Questao) = 0;
        virtual bool consultarQuestao(Questao*) = 0;
        virtual ~IServicoProva(){}
};

#endif // INTERFACES_H_INCLUDED
