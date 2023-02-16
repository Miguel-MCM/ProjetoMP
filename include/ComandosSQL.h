#ifndef INCLUDE_COMANDOSSQL_H_

#define INCLUDE_COMANDOSSQL_H_

#include <list>
#include <string>
#include <iostream>

#include "./sqlite3.h"
#include "Entidades.h"

using std::string;
using std::list;

/**
 * @brief Classe de Erro para todos os comandos SQL
 */
class EErroPersistencia {
private:
        /**
         * @brief Atributo string que repesenta a mensagem do erro ocorrido.
         */
        string mensagem;
public:
        /**
         * @brief A prórpia função do erro de percistencia que define a mensagem de erro.
         * @param -parâmetro string: mensagem de erro
         */
        EErroPersistencia(string);
        /**
         * @brief Retorna qual é o erro ocorrido.
         * @return mensagem de erro. (string) 
         */
        string what();

};

inline string EErroPersistencia::what() {
        return mensagem;
}

inline EErroPersistencia::EErroPersistencia(string mensagem){
        this->mensagem = mensagem;
}

/**
 * @brief Classe de Resultados para todos os comandos SQL
 */
class ElementoResultado {
private:
        /**
         * @brief Atributo string que armazena o nome da coluna do banco de dados.
         */
        string nomeColuna;
        /**
         * @brief Atributo string que armazena o valor do banco de dados.
         */
        string valorColuna;
public:
        /**
         * @brief Define o nome da coluna do banco daquele dado.
         * @param referência a uma string constante
         */
        void setNomeColuna(const string&);
        /**
         * @brief Retorna o nome da coluna do banco daquele dado.
         * 
         * @return Nome da coluna (string). 
         */
        string getNomeColuna() const;
        /**
         * @brief Define o valor dado naquela linha.
         * @param referência a uma string constante
         */
        void setValorColuna(const string&);
        /**
         * @brief Retorna o valor dado naquela linha.
         * @return dado (string); 
         */
        string getValorColuna() const;
};

inline string ElementoResultado::getNomeColuna() const {
        return nomeColuna;
}

inline string ElementoResultado::getValorColuna() const {
        return valorColuna;
}

/**
 * @brief Classe base dos comandos SQl para todos os outros comandos a seguir.
 * 
 */
class ComandoSQL {
private:
        /**
         * @brief  Um Atributo char armazenando o nome do Banco de Dados em uso.
         */
        const char *nomeBancoDados;
        /**
         * @brief Atributo da biblioteca sqlite3.
         */
        sqlite3 *bd;
        /**
         * @brief Atributo contendo a mensagem do erro (se existir).
         */
        char *mensagem;
        int rc;
        /// @brief Método usado para conectar com o banco de dados.
        void conectar();
        /// @brief Método usado para desconectar do banco de dados.
        void desconectar();
        static int callback(void *, int, char **, char **);

protected:
        /**
         * @brief Lista de Resultados da consulta.
         */
        static list<ElementoResultado> listaResultado;
        /**
         * @brief Atributo string com o comando SQL a ser execudado.
         */
        string comandoSQL;
public:
        /**
         * @brief Construtor do comando SQl, define o comando e nome do banco.
         */
        ComandoSQL() {
                nomeBancoDados = "Banco.db";
        }
        /**
         * @brief Executa o comando SQL.
         */
        void executar();
};

/**
 * @brief Comando SQL utilizado para cadastrar um usuario no banco.
 */
class ComandoCadastrarUsuario:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para cadastrar usuario.
         * @param Usuario a ser cadastrado
         * 
         */
        ComandoCadastrarUsuario(Usuario);
        /**
         * @brief Retorna o resultado da consulta
         * @return id do aluno cadastrado (int). 
         */
        int getResultado();
};

/**
 * @brief Comando SQL utilizado para consultar um usuario no banco.
 */
class ComandoConsultarUsuario:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para consultar um usuario pelo id.
         * @param parâmetro int: id do usuario que se quer consultar
         */
        ComandoConsultarUsuario(int);
        /**
         * @brief Construtor da classe para consultar um usuario pelo email.
         * @param parâmetro string: email do usuario que se quer consultar
         */
        ComandoConsultarUsuario(string);
        /**
         * @brief Retorna um objeto usuario com os dados obtidos na consulta.
         * 
         * @return Retorna o usuario encontrado (Usuario)
         */
        Usuario getResultado();
};


/**
 * @brief Comando SQL utilizado para descadastrar um usuario no banco.
 */
class ComandoDescadastrarUsuario:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para descadastrar um usuario pelo id.
         * @param -parâmetro int: id do usuário
         * @param -parâmetro string: cargo do usuário
         */
        ComandoDescadastrarUsuario(int, string);
};

/**
 * @brief Comando SQL utilizado para editar um usuario no banco.
 */

class ComandoEditarUsuario:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para editar um usuario.
         * @param parâmetro Usuario: um objeto usuário com as informações a serem atualizadas.
         */
        ComandoEditarUsuario(Usuario);
};

/**
 * @brief Comando SQL utilizado para cadastar um aluno na tabela de relacionamento do banco.
 */
class ComandoCadastrarAluno:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para cadastar um aluno na tabela de relacionamento pelo id.
         * @param parâmetro int: inteiro id do Aluno.
         */
        ComandoCadastrarAluno(int);
};

/**
 * @brief Comando SQL utilizado para cadastar um professor na tabela de relacionamento do banco.
 */
class ComandoCadastrarProfessor:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para cadastar um professor na tabela de relacionamento pelo id.
         * @param parâmetro int: inteiro id do Professor.
         */
        ComandoCadastrarProfessor(int);
};

/**
 * @brief Comando SQL utilizado para cadastar um administrador na tabela de relacionamento do banco.
 */
class ComandoCadastrarAdmin:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para cadastar um administrador na tabela de relacionamento pelo id.
         * @param parâmetro int: inteiro id do Administrador.
         */
        ComandoCadastrarAdmin(int);
};

/**
 * @brief Comando SQL utilizado para contar a quantidade de usuarios cadastrados no banco.
 */
class ComandoCountUsuarios:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para contar a quantidade de usuarios cadastrados.
         */
        ComandoCountUsuarios();
        /**
         * @brief Recebe o resultado do comando SQL
         * 
         * @return número de alunos no banco (int). 
         */
        int getResultado();
};

/**
 * @brief Comando SQL utilizado para cadastrar usuários no banco.
 */
class CadastrarUsuario {
 public:
        /**
         * @brief Construtor da classe para cadastrar usuários no banco.
         * @param parâmetro Usuario: objeto Usuario com os dados a serem cadastrados.
         */
        int executar(Usuario);
};

/**
 * @brief Comando SQL utilizado para cadastrar turmas no banco.
 */
class ComandoCadastrarTurma:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para cadastrar turmas no banco. 
         * @param -parâmetro Turma: objeto Turma com os dados da turma a ser criada.
         */
        ComandoCadastrarTurma(Turma);
        /**
         * @brief Retorna o id da turma criada.
         * 
         * @return id da turma (int). 
         */
        int getResultado();
};

/**
 * @brief Comando SQL utilizado para consultar turmas no banco.
 */
class ComandoConsultarTurma:public ComandoSQL {  //
 public:
        /**
         * @brief Construtor da classe para consultar turmas no banco. 
         * @param -parâmetro inteiro: id da turma a ser consultada.
         */
        ComandoConsultarTurma(int);
        Turma getResultado();
};

/**
 * @brief Comando SQL utilizado para descadastrar turmas no banco.
 */
class ComandoDescadastrarTurma:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para descadastar turmas no banco. 
         * @param -parâmetro inteiro: id da turma a ser descadastrada.
         */
        ComandoDescadastrarTurma(int);
};

/**
 * @brief Comando SQL utilizado para editar turmas no banco.
 */
class ComandoEditarTurma:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para editar turmas no banco. 
         * @param -parâmetro inteiro: id da turma a ser editada.
         */
        ComandoEditarTurma(Turma);
};

/**
 * @brief Comando SQL utilizado para registrar um aluno na turma.
 */
class ComandoEntrarNaTurma:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para registrar um aluno na turma.
         * @param -parâmetros inteiros: id do Aluno e id da turma.
         */
        ComandoEntrarNaTurma(int, int);  
};


/**
 * @brief Comando SQL utilizado para cadastrar uma questão no banco.
 */
class ComandoCadastrarQuestao:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para cadastrar uma questão no banco.
         * @param -parâmetro Questao: objeto com os dados da questão a ser criada.
         */
        ComandoCadastrarQuestao(Questao);
        /**
         * @brief Retorna o id da questão criada.
         * 
         * @return id questçao (int). 
         */
        int getResultado();
};

/**
 * @brief Comando SQL utilizado para cadastrar uma alternativa no banco.
 */
class ComandoCadastrarAlternativa:public ComandoSQL {  
 public:
        /**
         * @brief Construtor da classe para cadastrar uma alternativa no banco.
         * @param -parâmetro int: id da questão a ser criada
         * @param -parâmetro string: o texto da alternativa.
         */
        ComandoCadastrarAlternativa(int, string);
};

/**
 * @brief Comando SQL utilizado para cadastrar uma questão no banco.
 */
class CadastrarQuestao {  
 public:
        /**
         * @brief Construtor da classe para cadastrar uma qeustão no banco.
         * @param -parâmetro Questao: um objeto da questão a ser criada.
         * @return inteiro que representa o id da questão
         */
        int cadastrar(Questao);
};

/**
 * @brief Comando SQL utilizado para descadastrar uma questão no banco.
 */
class ComandoDescadastrarQuestao:public ComandoSQL {    
 public:
        /**
         * @brief Construtor da classe para descadastrar uma questão no banco.
         * @param -parâmetro inteiro: id da questão a ser descadastrada.
         */
        ComandoDescadastrarQuestao(int);
};

/**
 * @brief Comando SQL utilizado para editar uma questão no banco.
 */
class ComandoEditarQuestao:public ComandoSQL {   
 public:
        /**
         * @brief Construtor da classe para editar uma questão no banco.
         * @param -parâmetro Questao: id da questão a ser editada.
         */
        ComandoEditarQuestao(Questao);
};

/**
 * @brief Comando SQL utilizado para consultar uma questão no banco.
 */
class ComandoConsultarQuestao:public ComandoSQL {   
 public:
         /**
         * @brief Construtor da classe para consultar uma questão no banco.
         * @param -parâmetro inteiro: id da questão a ser consultada.
         */
        ComandoConsultarQuestao(int);
        /// @brief Retorna o resultado da consulta ao cliente do banco de dados.
        /// @return Questao
        Questao getResultado();
};

/**
 * @brief Comando SQL utilizado para cadastrar uma prova no banco.
 */
class ComandoCadastrarProva:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para cadastrar uma questão no banco.
         * @param -parâmetro Prova: objeto prova com os dados informados.
         */
        ComandoCadastrarProva(Prova);
        /// @brief Retorna o id da prova cadastrada ao cliente do banco de dados.
        /// @return int id
        int getResultado();
};

/**
 * @brief Comando SQL utilizado para cadastrar uma questão a uma prova no banco.
 */
class ComandoAssociarQuestaoProva:public ComandoSQL { 
 public:
         /**
         * @brief Construtor da classe para cadastrar uma questão a uma prova no banco.
         * @param -parâmetros inteiros: id da prova, id da questão.
         */
        ComandoAssociarQuestaoProva(int, int);
};

/**
 * @brief Comando SQL utilizado para cadastrar uma prova no banco.
 */
class CadastrarProva {
 public:
         /**
         * @brief Cadastra uma prova no banco e retorna seu id.
         * @param -parâmetro Prova: objeto Prova com os dados a serem cadastrados.
         * @return int id da prova
         */
        int cadastrar(Prova);
};

/**
 * @brief Comando SQL utilizado para descadastrar uma prova no banco.
 */
class ComandoDescadastrarProva:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para descadastrar uma prova do banco.
         * @param -prarâmetro int: id da prova
         */
        ComandoDescadastrarProva(int);
};

/**
 * @brief Comando SQL utilizado para editar uma prova no banco.
 */
class ComandoEditarProva:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para editar uma prova do banco.
         * @param -prarâmetro Prova: objeto do tipo prova com os novos dados.
         */
        ComandoEditarProva(Prova);
};

/**
 * @brief Comando SQL utilizado para consultar uma prova no banco.
 */
class ComandoConsultarProva:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para consultar uma prova do banco.
         * @param -prarâmetro int: id da prova procurada.
         */
        ComandoConsultarProva(int);
        /// @brief Retorna a prova procurada pelo cliente no banco de dados.
        /// @return Prova
        Prova getResultado();
};

/**
 * @brief Comando SQL utilizado para cadastrar uma prova no banco.
 */
class ComandoCadastrarResposta:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para cadastrar resposta no banco.
         * @param -prarâmetro Resposta: objeto resposta do aluno.
         */
        ComandoCadastrarResposta(Resposta);
        /// @brief Retorna o id da resposta cadastrada no banco de dados.
        /// @return int id
        int getResultado();
};

 /**
 * @brief Comando SQL utilizado para associar uma resposta a uma questão com uma resposta de prova.
 */

class ComandoAssociarRespostaQuestaoRespostaProva:public ComandoSQL { //
 public:
         /**
         * @brief Construtor da classe para associar uma resposta a uma questão com uma resposta de prova no banco.
         * @param -parâmetros int: inteiros que representam o id da Prova, o id da Questao e o numero de Resposta.
         */
        ComandoAssociarRespostaQuestaoRespostaProva(int, int, int);     
};

 /**
 * @brief Comando SQL utilizado para cadastrar uma resposta a uma prova.
 */
class CadastrarResposta {
 public:
        /// @brief Retorna o id da resposta cadastrada
        /// @param  -parâmetro Resposta: objeto resposta com os dados a serem cadastrados.
        /// @return int id
        int cadastrar(Resposta);
};

 /**
 * @brief Comando SQL utilizado para consultar respostas a uma prova.
 */
class ComandoConsultarResposta:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para consultar respostas a uma prova no banco.
         * @param -parâmetro int: inteiro que representa o id da Prova.
         */
        ComandoConsultarResposta(int);
         /**
         * @brief Construtor da classe para consultar resposta de uma aluno a uma prova no banco.
         * @param -parâmetros int: inteiros que representam o id do Aluno e o id da Prova.
         */
        ComandoConsultarResposta(int, int);
        /// @brief Retorna um objeto Resposta com os dados no banco.
        /// @return Resposta
        Resposta getResultado();
};

 /**
 * @brief Comando SQL utilizado para listar turmas do banco de dados.
 */ 
class ComandoListarTurmas:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para listar turmas do banco de dados.
         */
        ComandoListarTurmas();
        /// @brief Retorna um objeto lista de Turmas com os dados no banco.
        /// @return list<Turma>
        list<Turma> getResultado();
};

 /**
 * @brief Comando SQL utilizado para listar provas de uma turma do banco de dados.
 */ 
class ComandoListarProvas:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para listar provas de uma turma do banco de dados.
         * @param -parâmetro int: inteiro que representa o id da turma.
         */
        ComandoListarProvas(int);
        /// @brief Retorna um objeto lista de Provas com os dados no banco.
        /// @return list<Prova>
        list<Prova> getResultado();
};

 /**
 * @brief Comando SQL utilizado para listar alunos de uma turma do banco de dados.
 */ 
class ComandoListarIDAlunosTurma:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para listar alunos de uma turma do banco de dados.
         * @param -parâmetro int: inteiro que representa o id da turma.
         */
        ComandoListarIDAlunosTurma(int);
        /// @brief Retorna um objeto lista de inteiros com os ids dos alunos da turma.
        /// @return list<int>
        list<int> getResultado();
};

 /**
 * @brief Comando SQL utilizado para executar a listagem de alunos de uma turma do banco de dados.
 */ 
class ListarAlunosTurma {   //
 public:
        /// @brief Executa o comando para listar alunos de uma turma.
        /// @param -parâmetro int> inteiro que representar o id da turma.
        /// @return lista com os alunos da turma.
        list<Usuario> executar(int);
};

 /**
 * @brief Comando SQL utilizado para listar as questões de uma prova do banco de dados.
 */
class ComandoListarIDQuestoesProva:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para listar as questões de uma prova do banco de dados.
         * @param -parâmetro int: inteiro que representa o id da prova.
         */
        ComandoListarIDQuestoesProva(int);
        /// @brief Retorna um objeto lista de inteiros com os ids das questões da prova.
        /// @return list<int>
        list<int> getResultado();
};

 /**
 * @brief Comando SQL utilizado para executar a listagem de questões de uma prova do banco de dados.
 */ 
class ListarQuestoesProva {  //
 public:
        /// @brief Executa o comando para listar questões de uma prova.
        /// @param -parâmetro int> inteiro que representar o id da prova.
        /// @return lista com as questões da prova.
        list<Questao> executar(int);
};

 /**
 * @brief Comando SQL utilizado para contar quantas prova existem no banco de dados.
 */
class ComandoCountProva:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para contar quantas prova existem no banco de dados.
         */
	ComandoCountProva();
        /// @brief Retorna um inteiro com a quantidade de provas no banco de dados.
        /// @return int
	int getResultado();
};

 /**
 * @brief Comando SQL utilizado para contar quantas questões existem no banco de dados.
 */
class ComandoCountQuestao:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para contar quantas questões existem no banco de dados.
         */
	ComandoCountQuestao();
        /// @brief Retorna um inteiro com a quantidade de questões no banco de dados.
        /// @return int
	int getResultado();
};

 /**
 * @brief Comando SQL utilizado para contar quantas respostas existem no banco de dados.
 */
class ComandoCountResposta:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para contar quantas respostas existem no banco de dados.
         */
	ComandoCountResposta();
        /// @brief Retorna um inteiro com a quantidade de respostas no banco de dados.
        /// @return int
	int getResultado();
};

 /**
 * @brief Comando SQL utilizado para executar a listagem de turmas que um determinado usuário faz parte.
 */ 
class ComandoListarIdTurmaAluno:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para listar as turmas que um determinado usuário faz parte.
         * @param -parâmetro int: inteiro que representa o id do aluno.
         */
	ComandoListarIdTurmaAluno(int);
        /// @brief Retorna um objeto lista de inteiros com os ids das turma.
        /// @return list<int>
	list<int> getResultado();
};

 /**
 * @brief Comando SQL utilizado para executar a listagem de turmas que um determinado usuário faz parte.
 */ 
class ListarTurmasAluno {
 public:
        /// @brief Executa o comando para listar questões de uma prova.
        /// @param -parâmetro int> inteiro que representar o id da prova.
        /// @return lista com as questões da prova.
	list<Turma> executar(int);
};

 /**
 * @brief Comando SQL utilizado para executar a listagem de turmas de um professor.
 */
class ComandoListarIdTurmasProfessor:public ComandoSQL {
 public:
         /**
         * @brief Construtor da classe para listar as turmas de um professor.
         * @param -parâmetro int: inteiro que representa o id do professor.
         */
	ComandoListarIdTurmasProfessor(int);
        /// @brief Retorna um objeto lista de Turmas do professor.
        /// @return list<Turma>
	list<Turma> getResultado();
};

 /**
 * @brief Comando SQL utilizado para buscar a resposta de um aluno a uma prova no banco de dados.
 */
class ComandoBuscarRespostaAluno:public ComandoSQL {
 public:
        /**
         * @brief Construtor da classe para buscar a resposta de um aluno a uma prova no banco de dados.
         * @param -parâmetro int: inteiro que representa o id do professor.
         */
        ComandoBuscarRespostaAluno(int, int); // Id Prova, Id Aluno;
        /// @brief Retorna se existe ou não a resposta do aluno a uma prova.
        /// @return bool
        bool getResultado();
};

#endif  //  INCLUDE_COMANDOSSQL_H_