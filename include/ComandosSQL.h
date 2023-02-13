#ifndef INCLUDE_COMANDOSSQL_H_
#define INCLUDE_COMANDOSSQL_H_

#include <list>
#include <string>
#include "sqlite3.h"
#include "Entidades.h"

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
        void executar(Usuario);
};



#endif  //  INCLUDE_COMANDOSSQL_H_