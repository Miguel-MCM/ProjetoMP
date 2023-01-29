#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "Entidades.h"
#include "Containers.h"

class IServicoAutenticacao;
class IServicoUsuario;
class IServicoProjeto;

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

class IApresentacaoProjeto {
    public:
        virtual void executar(Matricula*) = 0;
        virtual void setCntrServicoProjeto(IServicoProjeto*) = 0;
        virtual ~IApresentacaoProjeto(){}
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

class IServicoProjeto {
    public:
        virtual bool cadastrarProjeto(Projeto) = 0;
        virtual bool descadastrarProjeto(Codigo) = 0;
        virtual bool editarProjeto(Projeto) = 0;
        virtual bool consultarProjeto(Projeto*) = 0;
        virtual bool cadastrarTarefa(Tarefa) = 0;
        virtual bool descadastrarTarefa(Codigo) = 0;
        virtual bool editarTarefa(Tarefa) = 0;
        virtual bool consultarTarefa(Tarefa*) = 0;
        virtual ~IServicoProjeto(){}
};

#endif // INTERFACES_H_INCLUDED
