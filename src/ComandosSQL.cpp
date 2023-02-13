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
    comandoSQL = "BEGIN; INSERT INTO Usuario (Nome, Email, Senha, Cargo) VALUES(";
    comandoSQL += "'" + usuario.getNome() + "', ";
    comandoSQL += "'" + usuario.getEmail() + "', ";
    comandoSQL += "'" + usuario.getSenha() + "', ";
    comandoSQL += "'" + usuario.getCargo() + "'); SELECT last_insert_rowid(); COMMIT";
}

int ComandoCadastrarUsuario::getResultado() {
        return stoi(listaResultado.back().getValorColuna());
}

ComandoConsultarUsuario::ComandoConsultarUsuario(int id) {
    comandoSQL = "SELECT * FROM Usuario WHERE idUsuario = ";
    comandoSQL += to_string(id);
}

Usuario ComandoConsultarUsuario::getResultado() {
        ElementoResultado resultado;
        Usuario usuario;

        if(listaResultado.size() < 5)
                throw EErroPersistencia("Lista de resultados vazia.");

        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setId(stoi(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setNome(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setEmail(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setSenha(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        usuario.setCargo(resultado.getValorColuna());
        return usuario;
}

ComandoDescadastrarUsuario::ComandoDescadastrarUsuario(int id, string cargo) {
        if (cargo == "aluno") {
                comandoSQL = "DELETE FROM Aluno WHERE Usuario_idUsuario = ";
        } else if (cargo == "professor") {
                comandoSQL = "DELETE FROM Professor WHERE Usuario_idUsuario = ";
        } else if (cargo == "admin") {
                comandoSQL = "DELETE FROM Admin WHERE Usuario_idUsuario = ";
        }
        comandoSQL += to_string(id) + ";";
        comandoSQL += "DELETE FROM Usuario WHERE idUsuario = ";
        comandoSQL += to_string(id) + ";";
}

ComandoEditarUsuario::ComandoEditarUsuario(Usuario usuario) {
        comandoSQL = "UPDATE Usuario ";
        comandoSQL += "SET Nome = '" + usuario.getNome();
        comandoSQL += "', Email = '" + usuario.getEmail();
        comandoSQL += "', Senha = '" + usuario.getSenha();
        comandoSQL += "' WHERE idUsuario = " + to_string(usuario.getId());
}

ComandoCadastrarAluno::ComandoCadastrarAluno(int id) {
    comandoSQL = "INSERT INTO Aluno (idAluno, Usuario_idUsuario) VALUES(";
    comandoSQL += to_string(id) + ", ";
    comandoSQL += to_string(id) + ");";
}

ComandoCadastrarProfessor::ComandoCadastrarProfessor(int id) {
    comandoSQL = "INSERT INTO Professor (idProfessor, Usuario_idUsuario) VALUES(";
    comandoSQL += to_string(id) + ", ";
    comandoSQL += to_string(id) + ");";
}

ComandoCadastrarAdmin::ComandoCadastrarAdmin(int id) {
    comandoSQL = "INSERT INTO Admin (idAdmin, Usuario_idUsuario) VALUES(";
    comandoSQL += to_string(id) + ", ";
    comandoSQL += to_string(id) + ");";
}

void CadastrarUsuario::executar(Usuario usuario) {
    ComandoCadastrarUsuario comandoCadastrar(usuario);
    comandoCadastrar.executar();
    
    usuario.setId(comandoCadastrar.getResultado());

    if (usuario.getCargo() == "aluno") {
        ComandoCadastrarAluno cmdCadastrarAluno(usuario.getId());
        cmdCadastrarAluno.executar();
    } else if (usuario.getCargo() == "professor") {
        ComandoCadastrarProfessor cmdCadastrarProfessor(usuario.getId());
        cmdCadastrarProfessor.executar();
    } else if (usuario.getCargo() == "admin") {
        ComandoCadastrarAdmin cmdCadastrarAdmin(usuario.getId());
        cmdCadastrarAdmin.executar();
    }
}

ComandoCountUsuarios::ComandoCountUsuarios() {
        comandoSQL = "SELECT COUNT(*) FROM Usuario";
}

int ComandoCountUsuarios::getResultado() {
        return stoi(listaResultado.back().getValorColuna());
}