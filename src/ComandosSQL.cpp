#include "ComandosSQL.h"
#include <iostream>

using std::to_string;
using std::stoi;

list<ElementoResultado> ComandoSQL::listaResultado;

void ElementoResultado::setNomeColuna(const string& nomeColuna) {
        this->nomeColuna = nomeColuna;
}

void ElementoResultado::setValorColuna(const string& valorColuna){
        this->valorColuna = valorColuna;
}


void ComandoSQL::conectar() {
      rc = sqlite3_open(nomeBancoDados, &bd);
      if( rc != SQLITE_OK )
        throw EErroPersistencia("Erro na conexao ao banco de dados");
}

void ComandoSQL::desconectar() {
      rc =  sqlite3_close(bd);
      if( rc != SQLITE_OK )
        throw EErroPersistencia("Erro na desconexao ao banco de dados");
}

void ComandoSQL::executar() {
        conectar();
        rc = sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem);
        if(rc != SQLITE_OK){
                std::cout << mensagem << std::endl;
                sqlite3_free(mensagem);
                desconectar();
                throw EErroPersistencia("Erro na execucao do comando SQL");
        }
        desconectar();
}

int ComandoSQL::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
      NotUsed=0;
      ElementoResultado elemento;
      int i;
      for(i=0; i<argc; i++){
        elemento.setNomeColuna(nomeColuna[i]);
        elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
        listaResultado.push_front(elemento);
      }
      return 0;
}

ComandoCadastrarUsuario::ComandoCadastrarUsuario(Usuario usuario) {
    comandoSQL = "INSERT INTO Usuario (Nome, Email, Senha) VALUES(";
    comandoSQL += "'" + usuario.getNome() + "', ";
    comandoSQL += "'" + usuario.getEmail() + "', ";
    comandoSQL += "'" + usuario.getSenha() + "');";
}

ComandoConsultarUsuario::ComandoConsultarUsuario(int id) {
    comandoSQL = "SELECT * FROM Usuario WHERE idUsuario = ";
    comandoSQL += to_string(id);
}

Usuario ComandoConsultarUsuario::getResultado() {
        ElementoResultado resultado;
        Usuario usuario;

        if (listaResultado.empty())
                throw EErroPersistencia("Lista de resultados vazia.");
        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setId(stoi(resultado.getValorColuna()));

        if (listaResultado.empty())
                throw EErroPersistencia("Lista de resultados vazia.");
        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setNome(resultado.getValorColuna());

        if (listaResultado.empty())
                throw EErroPersistencia("Lista de resultados vazia.");
        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setEmail(resultado.getValorColuna());

        if (listaResultado.empty())
                throw EErroPersistencia("Lista de resultados vazia.");
        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setSenha(resultado.getValorColuna());
        return usuario;
}

ComandoDescadastrarUsuario::ComandoDescadastrarUsuario(int id) {
        comandoSQL = "DELETE FROM Usuario WHERE idUsuario = ";
        comandoSQL += to_string(id);
}

ComandoEditarUsuario::ComandoEditarUsuario(Usuario usuario) {
        comandoSQL = "UPDATE Usuario ";
        comandoSQL += "SET Nome = '" + usuario.getNome();
        comandoSQL += "', Email = '" + usuario.getEmail();
        comandoSQL += "', Senha = '" + usuario.getSenha();
        comandoSQL += "' WHERE idUsuario = " + to_string(usuario.getId());
}