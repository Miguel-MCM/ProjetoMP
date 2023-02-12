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
};

class ComandoConsultarUsuario:public ComandoSQL {
 public:
    ComandoConsultarUsuario(int);
};

#endif  //  INCLUDE_COMANDOSSQL_H_