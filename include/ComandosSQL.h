#ifndef INCLUDE_COMANDOSSQL_H_

#define INCLUDE_COMANDOSSQL_H_

#include <list>
#include <string>
#include "Entidades.h"

#include "sqlite3.h"

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
         */
        EErroPersistencia(string);
        /**
         * @brief Retorna qual é o erro ocorrido.
         * 
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
         */
        void setValorColuna(const string&);
        /**
         * @brief Retorna o valor dado naquela linha.
         * 
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
         * @brief Atributo da contendo a mensagem do erro (se existir).
         */
        char *mensagem;
        int rc;
        void conectar();
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
         * @brief Executa o comendo SQL.
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
         * 
         */
        ComandoCadastrarUsuario(Usuario);
        /**
         * @brief Retorna o resultado da consulta
         * 
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
         */
        ComandoConsultarUsuario(int);
        /**
         * @brief Construtor da classe para consultar um usuario pelo email.
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
         * @brief Construtor da classe para consultar um usuario pelo id.
         * também é necessário informar o cargo do usuário para remover-lô da tabela de relacionamentos
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
         * Recebe um objeto usuário com as informações a serem atualizadas.
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
         * Recebe um objeto com os dados da turma a ser criada.
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
         * Recebe um id da turma a ser consultada.
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
         * Recebe um id da turma a ser descadastar.
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
         * Recebe um objeto com os dados da turma a ser editada.
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
         * Recebe dois inteiros sendo o id do usuario e o id da turma.
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
         * Recebe um objeto com os dados da questão a ser criada.
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
         * Recebe um id da questão a ser criada e a string para entregar.
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
         * Recebe um objeto da questão a ser criada.
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
         */
        ComandoDescadastrarQuestao(int);
};

class ComandoEditarQuestao:public ComandoSQL {   
 public:
        ComandoEditarQuestao(Questao);
};

class ComandoConsultarQuestao:public ComandoSQL {   
 public:
        ComandoConsultarQuestao(int);
        Questao getResultado();
};

class ComandoCadastrarProva:public ComandoSQL {
 public:
        ComandoCadastrarProva(Prova);
        int getResultado();
};

class ComandoAssociarQuestaoProva:public ComandoSQL { 
 public:
        ComandoAssociarQuestaoProva(int, int);
};

class CadastrarProva {
 public:
        int cadastrar(Prova);
};

class ComandoDescadastrarProva:public ComandoSQL {
 public:
        ComandoDescadastrarProva(int);
};

class ComandoEditarProva:public ComandoSQL {
 public:
        ComandoEditarProva(Prova);
};

class ComandoConsultarProva:public ComandoSQL {
 public:
        ComandoConsultarProva(int);
        Prova getResultado();
};

class ComandoCadastrarResposta:public ComandoSQL {
 public:
        ComandoCadastrarResposta(Resposta);
        int getResultado();
};

class ComandoAssociarRespostaQuestaoRespostaProva:public ComandoSQL { //
 public:
        ComandoAssociarRespostaQuestaoRespostaProva(int, int, int);     
};

class CadastrarResposta {
 public:
        int cadastrar(Resposta);
};

class ComandoConsultarResposta:public ComandoSQL {
 public:
        ComandoConsultarResposta(int);
        ComandoConsultarResposta(int, int);
        Resposta getResultado();
};


class ComandoListarTurmas:public ComandoSQL {
 public:
        ComandoListarTurmas();
        list<Turma> getResultado();
};

class ComandoListarProvas:public ComandoSQL {
 public:
        ComandoListarProvas(int);
        list<Prova> getResultado();
};

class ComandoListarIDAlunosTurma:public ComandoSQL {
 public:
        ComandoListarIDAlunosTurma(int);
        list<int> getResultado();
};

class ListarAlunosTurma {   //
 public:
        list<Usuario> executar(int);
};

class ComandoListarIDQuestoesProva:public ComandoSQL {
 public:
        ComandoListarIDQuestoesProva(int);
        list<int> getResultado();
};

class ListarQuestoesProva {  //
 public:
        list<Questao> executar(int);
};


class ComandoCountProva:public ComandoSQL {
 public:
	ComandoCountProva();
	int getResultado();
};

class ComandoCountQuestao:public ComandoSQL {
 public:
	ComandoCountQuestao();
	int getResultado();
};

class ComandoCountResposta:public ComandoSQL {
 public:
	ComandoCountResposta();
	int getResultado();
};

class ComandoListarIdTurmaAluno:public ComandoSQL {
 public:
	ComandoListarIdTurmaAluno(int);
	list<int> getResultado();
};

class ListarTurmasAluno {
 public:
	list<Turma> executar(int);
};

class ComandoListarIdTurmasProfessor:public ComandoSQL {
 public:
	ComandoListarIdTurmasProfessor(int);
	list<Turma> getResultado();
};

class ComandoBuscarRespostaAluno:public ComandoSQL {
 public:
    ComandoBuscarRespostaAluno(int, int); // Id Prova, Id Aluno;
    bool getResultado();
};

#endif  //  INCLUDE_COMANDOSSQL_H_