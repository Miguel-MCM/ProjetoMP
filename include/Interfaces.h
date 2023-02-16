#ifndef INCLUDE_INTERFACES_H_
#define INCLUDE_INTERFACES_H_

#include "Entidades.h"
#include <map>
#include <string>
#include <list>
#include <vector>

using std::string;
using std::list;
using std::vector;

class IApresentacaoAutenticacao;
class IApresentacaoUsuario;
class IApresentacaoAdmin;
class IApresentacaoTurma;
class IApresentacaoProva;

class IServicoAutenticacao;
class IServicoUsuario;
class IServicoAdmin;
class IServicoTurma;
class IServicoProva;
class IServicoQuestao;

/// @brief Interface para apresentação à usuário de telas relacionadas à serviço de autenticação de dados. 
class IApresentacaoAutenticacao {
 public:
        /// @brief Implementa interface para autenticação de dados usuário.
        /// @param  parametro do tipo objeto Usuario: usuários quais dados se deseja autenticar.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool autenticar(Usuario*) = 0;
        /// @brief Cria conexão entre a camada de apresentação de autenticação e a camada de serviço.
        /// @param  Ponteiro IServicoAutenticacao: Ponteiro à interface de serviço.
        virtual void setCntrServicoAutenticacao(IServicoAutenticacao*) = 0;
        /// @brief Método destrutor para a interface.
        virtual ~IApresentacaoAutenticacao(){}
};

/// @brief Interface para apresentação à usuário de telas relacionadas à servicos de usuário. 
class IApresentacaoUsuario {
 public:
        /// @brief Implementa ambiente para acessar os serviços e telas de usuário.
        /// @param  Parametro do tipo ponteiro à objeto Usuario: usuário sob quais serviços e telas deseja acessar.
        virtual void executar(Usuario*) = 0;
        /// @brief Implementa ambiente para acessar os serviços e telas remententes ao cadastro de usuário.
        virtual void cadastrar() = 0;
        /// @brief Cria conexão entre a camada de apresenação de usuário com a camada de serviço de usuário.
        /// @param  Ponteiro IServicoUsuario: ponteiro á interface de servico.
        virtual void setCntrServicoUsuario(IServicoUsuario*) = 0;
        /// @brief Cria conexão entre a camada de apresentação de usuário com a camada de apresenação de turma.
        /// @param  Ponteiro IApresentacaoTurma: ponteiro á interface de apresentação de turma.
        virtual void setCntrServicoTurma(IServicoTurma*) = 0;
        virtual void setCntrApresentacaoTurma(IApresentacaoTurma*) = 0;
        virtual void setCntrServicoProva(IServicoProva*) = 0;
        
        /// @brief Método para verificar se usuário está cadastrado.
        /// @return bool: retorna true para usuário já cadastrado
        virtual bool getStatusCadastro() = 0;
        /// @brief Método para definir se usuário está cadastrado. 
        /// @param  bool: setado true se usuário está cadastrado
        virtual void setStatusCadastro(bool) = 0;

        /// @brief Método destrutor para a interface.
        virtual ~IApresentacaoUsuario(){}
};

/// @brief Interface para apresentação à usuário de telas relacionadas à servicos de administrador.
class IApresentacaoAdmin {
 public:
        /// @brief Implementa ambiente para acessar os serviços e telas de admin
        /// @param  Parametro do tipo ponteiro à objeto Usuario: usuário sob quais serviços e telas deseja acessar.
        virtual void executar(Usuario*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de administrador com a camada de serviço de admin.
        /// @param  Ponteiro IServicoAdmin: ponteiro á interface de serviço de admin.
        virtual void setCntrServicoAdmin(IServicoAdmin*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de administrador com a camada de serviço de usuário.
        /// @param   Ponteiro IServicoUsuario: ponteiro á interface de serviço de usuário.
        virtual void setCntrServicoUsuario(IServicoUsuario*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de administrador com a camada de serviço de turma.
        /// @param   Ponteiro IServicoTurma: ponteiro á interface de serviço de turma.
        virtual void setCntrServicoTurma(IServicoTurma*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de administrador com a camada de serviço de prova.
        /// @param   Ponteiro IServicoProva: ponteiro á interface de serviço de prova.
        virtual void setCntrServicoProva(IServicoProva*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de administrador com a camada de apresentacao de usuario.
        /// @param   Ponteiro IApresentacaoUsuario: ponteiro á interface de apresentacao de usuario.
        virtual void setCntrApresentacaoUsuario(IApresentacaoUsuario*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de administrador com a camada de apresentacao de prova.
        /// @param  Ponteiro IApresentacaoProva: ponteiro á interface de apresentacao de prova.
        virtual void setCntrApresentacaoProva(IApresentacaoProva*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de administrador com a camada de apresentacao de turma.
        /// @param  Ponteiro IApresentacaoTurma: ponteiro á interface de apresentacao de turma. 
        virtual void setCntrApresentacaoTurma(IApresentacaoTurma*) = 0;

        /// @brief Método destrutor para a interface.
        virtual ~IApresentacaoAdmin() {}
};

/// @brief Interface para apresentação ao usuário de telas relacionadas à servicos de turma. 
class IApresentacaoTurma {
 public:
        /// @brief Implementa ambiente para acessar os serviços e telas de turma.
        /// @param  Parametro do tipo ponteiro à objeto Usuario: usuário sob quais serviços e telas deseja acessar.
        virtual void executar(Usuario*) = 0;
        /// @brief Implementa ambiente para acessar os serviços e telas de edição turma.
        /// @param  Parametro do tipo ponteiro à objeto Turma: turma sob quais serviços e telas deseja acessar.
        virtual void editar(Turma*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de turma com a camada de servico de turma.
        /// @param  Ponteiro IServicoUsuario: ponteiro á interface de servico de turma.
        virtual void setCntrServicoTurma(IServicoTurma*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de turma com a camada de servico de usuario.
        /// @param  Ponteiro IServicoUsuario: ponteiro á interface de serviço de usuário.
        virtual void setCntrServicoUsuario(IServicoUsuario*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de turma com a camada de servico de turma.
        /// @param  Ponteiro IApresentacaoTurma: ponteiro á interface de apresentacao de turma. 
        virtual void setCntrApresentacaoProva(IApresentacaoProva*) = 0;
        /// @brief Método destrutor para a interface.
        virtual ~IApresentacaoTurma() {}
};

/// @brief Interface para apresentação ao usuário de telas relacionadas à servicos de prova e questão.
class IApresentacaoProva {
 public:
        /// @brief implementa ambiente para acessar os serviços e telas de prova.
        /// @param Parametro do tipo objeto Usuario: para auxiliar a implementação de serviços e telas.
        /// @param  Parametro do tipo ponteiro à objeto Turma: turma sob quais serviços e telas deseja acessar.
        virtual void executar(Turma*, Usuario) = 0;
        /// @brief implementa ambiente para acessar os serviços e telas de gerenciamento de prova.
        /// @param  Parametro do tipo ponteiro à objeto Prova: prova sob quais serviços e telas deseja acessar.
        virtual void gerenciar(Prova*) = 0;
        /// @brief implementa ambiente para acessar os serviços e telas de edição de prova.
        /// @param  Parametro do tipo ponteiro à objeto Prova: prova sob quais serviços e telas deseja acessar.
        virtual void editar(Prova*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de prova com a camada de servico de usuario.
        /// @param  Ponteiro IServicoProva: ponteiro á interface de serviço de prova. 
        virtual void setCntrServicoProva(IServicoProva*) = 0;
        /// @brief Cria conexão entre a camada de apresenação de prova com a camada de servico de prova.
        /// @param  Ponteiro IServicoTurma: ponteiro á interface de serviço de turma.
        virtual void setCntrServicoTurma(IServicoTurma*) = 0;

        /// @brief Método destrutor para a interface.
        virtual ~IApresentacaoProva() {}
};

class IServicoAutenticacao {
 public:
        virtual bool autenticar(Usuario*) = 0;
        virtual ~IServicoAutenticacao() {}
};

class IServicoUsuario {
 public:
        virtual bool cadastrar(Usuario) = 0;
        virtual bool descadastrar(int, string) = 0;
        virtual bool editar(Usuario) = 0;
        virtual bool consultar(Usuario*) = 0;
        virtual bool listarTurmasAluno(int, list<Turma>*) = 0; // id aluno
        virtual bool listarTurmasProfessor(int, list<Turma>*) = 0; // id professor
        virtual bool consultarEmail(Usuario *usuario) = 0;
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
        virtual bool getListaQuestoes(int, list<Questao>*) = 0;
        virtual bool calcularResultado(Resposta, list<int> *) = 0;
        virtual bool getListaRespostaAlunos(Prova, list<Usuario>*, list<int>*) = 0;


        virtual ~IServicoProva() {}
};

class IServicoTurma {
 public:
        virtual bool cadastrar(Turma) = 0;
        virtual bool entrar(int, int) = 0; // id do usuario, id da turma
        virtual bool descadastrar(int) = 0;

        virtual bool consultar(Turma*) = 0;
        virtual bool editar(Turma*) = 0;

        virtual bool listarTurmas(list<Turma>*) = 0;
        virtual bool listarProvas(int, list<Prova>*) = 0; // id da turma, lista de provas
        virtual bool listarAlunos(int, list<Usuario>*) = 0; // id da turma, lista de alunos

        virtual ~IServicoTurma() {}
};

class IServicoAdmin {
 public:
    virtual bool estatisticas(vector<string>*) = 0;

    virtual ~IServicoAdmin() {}
};
#endif  //  INCLUDE_INTERFACES_H_
