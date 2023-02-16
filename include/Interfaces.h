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

/// @brief Interface para apresentação ao usuário de telas relacionadas à serviço de autenticação de dados. 
class IApresentacaoAutenticacao {
 public:
        /// @brief Implementa autenticação de dados usuário.
        /// @param  parametro do tipo objeto Usuario: usuário a ser autenticado.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool autenticar(Usuario*) = 0;
        /// @brief Cria conexão entre a camada de apresentação de autenticação e a camada de serviço.
        /// @param  Ponteiro IServicoAutenticacao: Ponteiro à interface de serviço.
        virtual void setCntrServicoAutenticacao(IServicoAutenticacao*) = 0;
        /// @brief Método destrutor para a interface.
        virtual ~IApresentacaoAutenticacao(){}
};

/// @brief Interface para apresentação ao usuário de telas relacionadas à servicos de usuário. 
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

/// @brief Interface para apresentação ao usuário de telas relacionadas à servicos de administrador.
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

/// @brief Interface para serviços de autenticação do usuário.
class IServicoAutenticacao {
 public:
        /// @brief Solicita serviço de autenticação ao banco de dados.
        /// @param parametro ponteiro do tipo Usuario: usuário a ser autenticado.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool autenticar(Usuario*) = 0;
        /// @brief Método destrutor para a interface.
        virtual ~IServicoAutenticacao() {}
};

/// @brief Interface para serviços de usuário.
class IServicoUsuario {
 public:
        /// @brief Solicita serviço de cadastramento de usuário ao banco de dados.
        /// @param parametro Usuario: usuário com os dados preenchidos a ser cadastrado.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool cadastrar(Usuario) = 0;
        /// @brief Solicita serviço de descadastramento de usuário ao banco de dados.
        /// @param parametro int: id do usuário a ser descadastrado.
        /// @param parametro string: cargo do usuário a ser descadastrado.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool descadastrar(int, string) = 0;
        /// @brief Solicita serviço de edição de usuário ao banco de dados.
        /// @param parametro Usuario: usuário com os novos dados preenchidos a ser editado.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool editar(Usuario) = 0;
        /// @brief Solicita serviço de consulta de usuário ao banco de dados.
        /// @param parametro ponteiro do tipo Usuario: usuário a ser preenchido com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool consultar(Usuario*) = 0;
        /// @brief Solicita serviço de listagem de turmas às quais um aluno pertence ao banco de dados.
        /// @param parametro int: id do aluno a ser consultado.
        /// @param parametro ponteiro do tipo lista de turmas: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool listarTurmasAluno(int, list<Turma>*) = 0;
        /// @brief Solicita serviço de listagem de turmas de um professor ao banco de dados.
        /// @param parametro int: id do professor a ser consultado.
        /// @param parametro ponteiro do tipo lista de turmas: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool listarTurmasProfessor(int, list<Turma>*) = 0;
        /// @brief Solicita serviço de consulta de um usuário pelo email ao banco de dados.
        /// @param parametro ponteiro do tipo Usuario: usuario a ser preenchido pelos dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool consultarEmail(Usuario *usuario) = 0;
        /// @brief Método destrutor para a interface.
        virtual ~IServicoUsuario() {}
};

/// @brief Interface para serviços de prova.
class IServicoProva {
 public:
        /// @brief Solicita serviço de cadastramento de prova ao banco de dados.
        /// @param parametro Prova: prova com os dados preenchidos a ser cadastrada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool cadastrarProva(Prova) = 0;
        /// @brief Solicita serviço de descadastramento de prova ao banco de dados.
        /// @param parametro int: id da prova a ser descadastrada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool descadastrarProva(int) = 0;
        /// @brief Solicita serviço de edição de prova ao banco de dados.
        /// @param parametro Prova: prova com os novos dados preenchidos a ser editada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool editarProva(Prova) = 0;
        /// @brief Solicita serviço de consulta de prova ao banco de dados.
        /// @param parametro ponteiro do tipo Prova: prova a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool consultarProva(Prova*) = 0;
        /// @brief Solicita serviço de consulta de resposta ao banco de dados.
        /// @param parametro ponteiro do tipo Resposta: resposta a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool consultarResposta(Resposta*) = 0;
        /// @brief Solicita serviço de cadastramento de resposta ao banco de dados.
        /// @param parametro Resposta: resposta com os dados preenchidos a ser cadastrada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool cadastrarResposta(Resposta) = 0;
        /// @brief Solicita quantas questões estão cadastradas a uma prova no banco.
        /// @param  parametro Prova: prova da qual se quer a quantidade de questões .
        /// @param  parametro ponteiro do tipo inteiro: quantidade de questões a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool getQtdQuestoes(Prova, int*) = 0;
        /// @brief Solicita serviço de cadastramento de questão ao banco de dados.
        /// @param parametro Questao: questão com os dados preenchidos a ser cadastrada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool cadastrarQuestao(Questao) = 0;
        /// @brief Solicita serviço de descadastramento de questão ao banco de dados.
        /// @param parametro int: id da questão a ser descadastrada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool descadastrarQuestao(int) = 0;
        /// @brief Solicita serviço de listagem de questões de uma prova ao banco de dados.
        /// @param parametro int: id da prova a ser consultada.
        /// @param parametro ponteiro do tipo lista de Questões: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool getListaQuestoes(int, list<Questao>*) = 0;
        /// @brief Solicita o resultado da prova respondida por um aluno.
        /// @param parametro Resposta: objeto do tipo Resposta de um aluno.
        /// @param parametro ponteiro do tipo lista de inteiros: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool calcularResultado(Resposta, list<int> *) = 0;
        /// @brief Solicita serviço de listagem de respostas a uma prova ao banco de dados.
        /// @param parametro Prova: objeto Prova a ser consultada.
        /// @param parametro ponteiro do tipo lista de Usuarios: lista a ser preenchida com os dados do banco.
        /// @param parametro ponteiro do tipo lista de inteiros: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool getListaRespostaAlunos(Prova, list<Usuario>*, list<int>*) = 0;
        /// @brief Método destrutor para a interface.
        virtual ~IServicoProva() {}
};

/// @brief Interface para serviços de turma.
class IServicoTurma {
 public:
        /// @brief Solicita serviço de cadastramento de turma ao banco de dados.
        /// @param parametro Turma: turma com os dados preenchidos a ser cadastrada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool cadastrar(Turma) = 0;
        /// @brief Solicita serviço para um aluno entrar em uma turma ao banco de dados.
        /// @param parametro int: id do usuario.
        /// @param parametro int: id da turma.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool entrar(int, int) = 0;
        /// @brief Solicita serviço de descadastramento de turma ao banco de dados.
        /// @param parametro int: id da turma a ser descadastrada.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool descadastrar(int) = 0;
        /// @brief Solicita serviço de consulta de turma ao banco de dados.
        /// @param parametro ponteiro do tipo Turma: turma a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool consultar(Turma*) = 0;
        /// @brief Solicita serviço de edição de turma ao banco de dados.
        /// @param parametro ponteiro do tipo Turma: turma a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool editar(Turma*) = 0;
        /// @brief Solicita serviço de listagem de turmas ao banco de dados.
        /// @param parametro ponteiro do tipo lista de Turmas: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool listarTurmas(list<Turma>*) = 0;
        /// @brief Solicita serviço de listagem de provas de uma turma ao banco de dados.
        /// @param parametro int: id da turma a ser consultada.
        /// @param parametro ponteiro do tipo lista de Provas: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool listarProvas(int, list<Prova>*) = 0;
        /// @brief Solicita serviço de listagem de alunos de uma turma ao banco de dados.
        /// @param parametro int: id da turma a ser consultada.
        /// @param parametro ponteiro do tipo lista de Alunos: lista a ser preenchida com os dados do banco.
        /// @return bool indicando sucesso ou falha no processo.
        virtual bool listarAlunos(int, list<Usuario>*) = 0;
        /// @brief Método destrutor para a interface.
        virtual ~IServicoTurma() {}
};

/// @brief Interface para serviços de administrador.
class IServicoAdmin {
 public:
       /// @brief Solicita estatísticas do sistema ao banco de dados.
       /// @param parametro ponteiro do tipo vetor de strings: vetor a ser preenchido com os dados do banco.
       /// @return bool indicando sucesso ou falha no processo.
       virtual bool estatisticas(vector<string>*) = 0;
       /// @brief Método destrutor para a interface.
       virtual ~IServicoAdmin() {}
};
#endif  //  INCLUDE_INTERFACES_H_
