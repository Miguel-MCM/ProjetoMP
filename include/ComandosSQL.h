#ifndef INCLUDE_COMANDOSSQL_H_

#define INCLUDE_COMANDOSSQL_H_

#include <list>
#include <string>
#include "Entidades.h"

#include "sqlite3.h"

using std::string;
using std::list;

class EErroPersistencia {
private:
        string mensagem;
public:
        EErroPersistencia(string);
        string what();
};

inline string EErroPersistencia::what() {
        return mensagem;
}

inline EErroPersistencia::EErroPersistencia(string mensagem){
        this->mensagem = mensagem;
}

class ElementoResultado {
private:
        string nomeColuna;
        string valorColuna;
public:
        void setNomeColuna(const string&);
        string getNomeColuna() const;
        void setValorColuna(const string&);
        string getValorColuna() const;
};

inline string ElementoResultado::getNomeColuna() const {
        return nomeColuna;
}

inline string ElementoResultado::getValorColuna() const {
        return valorColuna;
}

class ComandoSQL {
private:
        const char *nomeBancoDados;
        sqlite3 *bd;
        char *mensagem;
        int rc;
        void conectar();
        void desconectar();
        static int callback(void *, int, char **, char **);

protected:
        static list<ElementoResultado> listaResultado;
        string comandoSQL;
public:
        ComandoSQL() {
             nomeBancoDados = "Banco.db";
        }
        void executar();
};

class ComandoCadastrarUsuario:public ComandoSQL {
 public:
    ComandoCadastrarUsuario(Usuario);
    int getResultado();
};

class ComandoConsultarUsuario:public ComandoSQL {
 public:
    ComandoConsultarUsuario(int);
    ComandoConsultarUsuario(string);
    Usuario getResultado();
};

class ComandoDescadastrarUsuario:public ComandoSQL {
 public:
    ComandoDescadastrarUsuario(int, string);
};

class ComandoEditarUsuario:public ComandoSQL {
 public:
        ComandoEditarUsuario(Usuario);
};

class ComandoCadastrarAluno:public ComandoSQL {
 public:
        ComandoCadastrarAluno(int);
};

class ComandoCadastrarProfessor:public ComandoSQL {
 public:
        ComandoCadastrarProfessor(int);
};

class ComandoCadastrarAdmin:public ComandoSQL {
 public:
        ComandoCadastrarAdmin(int);
};

class ComandoCountUsuarios:public ComandoSQL {
 public:
        ComandoCountUsuarios();
        int getResultado();
};

class CadastrarUsuario {
 public:
        int executar(Usuario);
};

class ComandoCadastrarTurma:public ComandoSQL {
 public:
        ComandoCadastrarTurma(Turma);
        int getResultado();
};

class ComandoConsultarTurma:public ComandoSQL {
 public:
        ComandoConsultarTurma(int);
        Turma getResultado();
};

class ComandoDescadastrarTurma:public ComandoSQL {
 public:
        ComandoDescadastrarTurma(int);
};

class ComandoEditarTurma:public ComandoSQL {
 public:
        ComandoEditarTurma(Turma);
};

class ComandoEntrarNaTurma:public ComandoSQL {
 public:
      ComandoEntrarNaTurma(int, int);  
};

class ComandoCadastrarQuestao:public ComandoSQL {
 public:
        ComandoCadastrarQuestao(Questao);
        int getResultado();
};

class ComandoCadastrarAlternativa:public ComandoSQL {
 public:
        ComandoCadastrarAlternativa(int, string);
};

class CadastrarQuestao {
 public:
        int cadastrar(Questao);
};

class ComandoDescadastrarQuestao:public ComandoSQL {
 public:
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

class ComandoAssociarRespostaQuestaoRespostaProva:public ComandoSQL {
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

class ListarAlunosTurma {
 public:
        list<Usuario> executar(int);
};

class ComandoListarIDQuestoesProva:public ComandoSQL {
 public:
        ComandoListarIDQuestoesProva(int);
        list<int> getResultado();
};

class ListarQuestoesProva {
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

#endif  //  INCLUDE_COMANDOSSQL_H_