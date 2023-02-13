#include "ComandosSQL.h"
#include <iostream>

using std::to_string;
using std::stoi;
using std::list;

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

ComandoConsultarUsuario::ComandoConsultarUsuario(string email) {
        comandoSQL = "SELECT * FROM Usuario WHERE Email = '";
        comandoSQL += email + "'";
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
        comandoSQL = "DELETE FROM UsuarioTurma WHERE Usuario_idUsuario = ";
        comandoSQL += to_string(id) + ";";
        if (cargo == "aluno") {
                comandoSQL += "DELETE FROM Aluno WHERE Usuario_idUsuario = ";
        } else if (cargo == "professor") {
                comandoSQL += "DELETE FROM Professor WHERE Usuario_idUsuario = ";
        } else if (cargo == "admin") {
                comandoSQL += "DELETE FROM Admin WHERE Usuario_idUsuario = ";
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

int CadastrarUsuario::executar(Usuario usuario) {
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

    return usuario.getId();
}

ComandoCountUsuarios::ComandoCountUsuarios() {
        comandoSQL = "SELECT COUNT(*) FROM Usuario";
}

int ComandoCountUsuarios::getResultado() {
        int id = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return id;
}

ComandoCadastrarTurma::ComandoCadastrarTurma(Turma turma) {
    comandoSQL = "BEGIN; INSERT INTO Turma (nome, descricaoTurma, turmaAberta, Professor_idProfessor, Professor_Usuario_idUsuario) VALUES(";
    comandoSQL += "'" + turma.getNome() + "', ";
    comandoSQL += "'" + turma.getDescricao() + "', ";
    comandoSQL += to_string(turma.taAberta()) + ", ";
    comandoSQL += to_string(turma.getIdProf()) + ", ";
    comandoSQL += to_string(turma.getIdProf()) + "); SELECT last_insert_rowid(); COMMIT";
}

int ComandoCadastrarTurma::getResultado() {
        int id = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return id;
}

ComandoConsultarTurma::ComandoConsultarTurma(int id) {
        comandoSQL = "SELECT * FROM Turma WHERE idTurma = ";
        comandoSQL += to_string(id);
}

Turma ComandoConsultarTurma::getResultado() {
        ElementoResultado resultado;
        Turma turma;

        if(listaResultado.size() < 6)
                throw EErroPersistencia("Lista de resultados vazia.");

        resultado = listaResultado.back();
        listaResultado.pop_back();
        turma.setId(stoi(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        turma.setNome(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        turma.setDescricao(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        if(turma.taAberta() != stoi(resultado.getValorColuna()))
                turma.switchAberta();
        
        resultado = listaResultado.back();
        listaResultado.pop_back();
        turma.setIdProf(stoi(resultado.getValorColuna()));

        listaResultado.pop_back();

        return turma;
}

ComandoDescadastrarTurma::ComandoDescadastrarTurma(int id) {
        comandoSQL = "DELETE FROM UsuarioTurma WHERE Turma_idTurma = ";
        comandoSQL += to_string(id) + ";";
        comandoSQL += "DELETE FROM Turma WHERE idTurma = ";
        comandoSQL += to_string(id) + ";";
}

ComandoEditarTurma::ComandoEditarTurma(Turma turma) {
        comandoSQL = "UPDATE Turma ";
        comandoSQL += "SET nome = '" + turma.getNome();
        comandoSQL += "', descricaoTurma = '" + turma.getDescricao();
        comandoSQL += "', turmaAberta = '" + to_string(turma.taAberta());
        comandoSQL += "' WHERE idTurma = " + to_string(turma.getId());
}

ComandoEntrarNaTurma::ComandoEntrarNaTurma(int idUsuario, int idTurma) {
    comandoSQL = "INSERT INTO UsuarioTurma (Usuario_idUsuario, Turma_idTurma) VALUES(";
    comandoSQL += to_string(idUsuario) + ", ";
    comandoSQL += to_string(idTurma) + ")";
}

ComandoCadastrarQuestao::ComandoCadastrarQuestao(Questao questao) {
    comandoSQL = "BEGIN; INSERT INTO Questao (nomeQuestao, textoQuestao, numAlternativas, alternativaCorreta, Professor_idProfessor, Professor_Usuario_idUsuario) VALUES(";
    comandoSQL += "'" + questao.getNome() + "', ";
    comandoSQL += "'" + questao.getTexto() + "', ";
    comandoSQL += to_string(questao.getAlternativas().size()) + ", ";
    comandoSQL += to_string(questao.getRespostaCorreta()) + ", ";
    comandoSQL += to_string(questao.getIdProf()) + ", ";
    comandoSQL += to_string(questao.getIdProf()) + "); SELECT last_insert_rowid();";
    
    comandoSQL += "COMMIT";
}

int ComandoCadastrarQuestao::getResultado() {
        int id = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return id;
}

ComandoCadastrarAlternativa::ComandoCadastrarAlternativa(int idQuestao, string texto) {
        comandoSQL = "INSERT INTO Alternativas (Questao_idQuestao, textoAlternativa) VALUES(";
        comandoSQL += to_string(idQuestao) + ", ";
        comandoSQL += "'" + texto + "');";
}

int CadastrarQuestao::cadastrar(Questao questao) {
        ComandoCadastrarQuestao cmdCadastrar(questao);
        cmdCadastrar.executar();
        int id = cmdCadastrar.getResultado();
        list<string> alternativas = questao.getAlternativas();

        for (list<string>::iterator it = alternativas.begin(); it != alternativas.end(); it++) {
                std::cout << *it << "\n";
                ComandoCadastrarAlternativa cmdCadastrarAlternativa(id, *it);
                cmdCadastrarAlternativa.executar();
        }
        return id;
}

ComandoDescadastrarQuestao::ComandoDescadastrarQuestao(int id) {
        comandoSQL = "DELETE FROM Alternativas WHERE Questao_idQuestao = ";
        comandoSQL += to_string(id) + ";";
        comandoSQL += "DELETE FROM Questao WHERE idQuestao = ";
        comandoSQL += to_string(id) + ";";
}

ComandoEditarQuestao::ComandoEditarQuestao(Questao questao) {
        comandoSQL = "BEGIN;UPDATE Questao ";
        comandoSQL += "SET nomeQuestao = '" + questao.getNome();
        comandoSQL += "', textoQuestao = '" + questao.getTexto();
        comandoSQL += "', numAlternativas = " + to_string(questao.getAlternativas().size());
        comandoSQL += ", alternativaCorreta = " + to_string(questao.getRespostaCorreta());
        comandoSQL += " WHERE idQuestao = " + to_string(questao.getId()) + ";";

        comandoSQL += "DELETE FROM Alternativas WHERE Questao_idQuestao = ";
        comandoSQL += to_string(questao.getId()) + ";";

        list<string> alternativas = questao.getAlternativas();
        for(list<string>::iterator it = alternativas.begin(); it != alternativas.end(); it++) {
                comandoSQL += "INSERT INTO Alternativas (Questao_idQuestao, textoAlternativa) VALUES(";
                comandoSQL += to_string(questao.getId()) + ", ";
                comandoSQL += "'" + *it + "');";
        }

        comandoSQL += "COMMIT;";
}

ComandoConsultarQuestao::ComandoConsultarQuestao(int id) {
    comandoSQL = "SELECT * FROM Questao WHERE idQuestao = ";
    comandoSQL += to_string(id) + ";";
    comandoSQL += "SELECT * FROM Alternativas WHERE Questao_idQuestao = ";
    comandoSQL += to_string(id) + ";";
}

Questao ComandoConsultarQuestao::getResultado() {
        ElementoResultado resultado;
        Questao questao;

        if(listaResultado.size() < 7)
                throw EErroPersistencia("Lista de resultados vazia.");

        resultado = listaResultado.back();
        listaResultado.pop_back();
        questao.setId(stoi(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        questao.setNome(resultado.getValorColuna());

        resultado = listaResultado.back();
        listaResultado.pop_back();
        questao.setTexto(resultado.getValorColuna());

        //num alternativas
        listaResultado.pop_back();

        resultado = listaResultado.back();
        listaResultado.pop_back();
        questao.setRespostaCorreta(stoi(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        questao.setIdProf(stoi(resultado.getValorColuna()));

        //dnv idProf
        listaResultado.pop_back();

        list<string> alternativas;
        while (!listaResultado.empty()) {
                //id alternativa
                listaResultado.pop_back();

                resultado = listaResultado.back();
                listaResultado.pop_back();
                alternativas.push_back(resultado.getValorColuna());

                //id questao
                listaResultado.pop_back();
        }
        questao.setAlternativas(alternativas);
        return questao;       
}