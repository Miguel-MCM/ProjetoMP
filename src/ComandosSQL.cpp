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
        int id = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return id;
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
                ComandoCadastrarAlternativa cmdCadastrarAlternativa(id, *it);
                cmdCadastrarAlternativa.executar();
        }
        return id;
}

ComandoDescadastrarQuestao::ComandoDescadastrarQuestao(int id) {
        comandoSQL = "DELETE FROM Prova_has_Questao WHERE Questao_idQuestao = ";
        comandoSQL += to_string(id) + ";";
        comandoSQL += "DELETE FROM Alternativas WHERE Questao_idQuestao = ";
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

ComandoCadastrarProva::ComandoCadastrarProva(Prova prova) {
    comandoSQL = "BEGIN; INSERT INTO Prova (nomeProva, numQuestoes, Turma_idTurma) VALUES(";
    comandoSQL += "'" + prova.getNome() + "', ";
    comandoSQL += to_string(prova.getIdQuestoes().size()) + ", ";
    comandoSQL += to_string(prova.getIdTurma()) + "); SELECT last_insert_rowid();";
    comandoSQL += "COMMIT";
}

int ComandoCadastrarProva::getResultado() {
        int id = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return id;
}

ComandoAssociarQuestaoProva::ComandoAssociarQuestaoProva(int idProva, int idQuestao) {
        comandoSQL = "INSERT INTO Prova_has_Questao (Prova_idProva, Questao_idQuestao) VALUES(";
        comandoSQL += to_string(idProva) + ", ";
        comandoSQL += to_string(idQuestao) + ");";
}

int CadastrarProva::cadastrar(Prova prova) {
        ComandoCadastrarProva cmdCadastrar(prova);
        cmdCadastrar.executar();
        int id = cmdCadastrar.getResultado();

        list<int> idQuestoes = prova.getIdQuestoes();
        for (list<int>::iterator it = idQuestoes.begin(); it != idQuestoes.end(); it++) {
                ComandoAssociarQuestaoProva cmdAssociar(id, *it);
                cmdAssociar.executar();
        }
        return id;
}

ComandoDescadastrarProva::ComandoDescadastrarProva(int id) {
        comandoSQL = "DELETE FROM Prova_has_Questao WHERE Prova_idProva = ";
        comandoSQL += to_string(id) + ";";
        comandoSQL += "DELETE FROM Prova WHERE idProva = ";
        comandoSQL += to_string(id) + ";";
}

ComandoEditarProva::ComandoEditarProva(Prova prova) {
        comandoSQL = "BEGIN;UPDATE Prova ";
        comandoSQL += "SET nomeProva = '" + prova.getNome();
        comandoSQL += "', numQuestoes = " + to_string(prova.getIdQuestoes().size());
        comandoSQL += " WHERE idProva = " + to_string(prova.getId()) + ";";

        comandoSQL += "DELETE FROM Prova_has_Questao WHERE Prova_idProva = ";
        comandoSQL += to_string(prova.getId()) + ";";

        list<int> idQuestoes = prova.getIdQuestoes();
        for (list<int>::iterator it = idQuestoes.begin(); it != idQuestoes.end(); it++) {
            comandoSQL += "INSERT INTO Prova_has_Questao (Prova_idProva, Questao_idQuestao) VALUES(";
			comandoSQL += to_string(prova.getId()) + ", ";
			comandoSQL += to_string(*it) + ");";
        }
        comandoSQL += "COMMIT;";
}

ComandoConsultarProva::ComandoConsultarProva(int id) {
    comandoSQL = "SELECT * FROM Prova WHERE idProva = ";
    comandoSQL += to_string(id) + ";";
    comandoSQL += "SELECT * FROM Prova_has_Questao WHERE Prova_idProva = ";
    comandoSQL += to_string(id) + ";";
}

Prova ComandoConsultarProva::getResultado() {
	    ElementoResultado resultado;
        Prova prova;

        if(listaResultado.size() < 4)
                throw EErroPersistencia("Lista de resultados vazia.");

        resultado = listaResultado.back();
        listaResultado.pop_back();
        prova.setId(stoi(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        prova.setNome(resultado.getValorColuna());

        //num questoes
        listaResultado.pop_back();

        resultado = listaResultado.back();
        listaResultado.pop_back();
       	prova.setIdTurma(stoi(resultado.getValorColuna()));

        list<int> idQuestoes;
        while (!listaResultado.empty()) {
                //id Prova
                listaResultado.pop_back();

                resultado = listaResultado.back();
                listaResultado.pop_back();
                idQuestoes.push_back(stoi(resultado.getValorColuna()));
        }
		prova.setIdQuestoes(idQuestoes);
        return prova;
}

ComandoCadastrarResposta::ComandoCadastrarResposta(Resposta resposta) {
    comandoSQL = "BEGIN; INSERT INTO Resposta_Prova (Prova_idProva, Aluno_idAluno) VALUES(";
    comandoSQL += to_string(resposta.getIdProva()) + ", ";
    comandoSQL += to_string(resposta.getIdEstudante()) + "); SELECT last_insert_rowid();";
    comandoSQL += "COMMIT";
}

int ComandoCadastrarResposta::getResultado() {
        int id = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return id;
}

ComandoAssociarRespostaQuestaoRespostaProva::ComandoAssociarRespostaQuestaoRespostaProva(int idProva, int idQuestao, int numResposta) {
        comandoSQL = "INSERT INTO Resposta_questao (idResposta_Prova, idQuestao, resposta) VALUES(";
        comandoSQL += to_string(idProva) + ", ";
        comandoSQL += to_string(idQuestao) + ", ";
        comandoSQL += to_string(numResposta) + ");";
}

int CadastrarResposta::cadastrar(Resposta resposta) {
	ComandoCadastrarResposta cmdCadastrar(resposta);
	cmdCadastrar.executar();
	int id = cmdCadastrar.getResultado();

	map<int, int> respostasQuestoes = resposta.getResposta();
	for (map<int,int>::iterator it = respostasQuestoes.begin(); it != respostasQuestoes.end() ; it++) {
		ComandoAssociarRespostaQuestaoRespostaProva cmdAssociar(id, it->first, it->second);
		cmdAssociar.executar();
	}
        return id;
}

ComandoConsultarResposta::ComandoConsultarResposta(int id){
    comandoSQL = "SELECT * FROM Resposta_Prova WHERE idResposta_Prova = ";
    comandoSQL += to_string(id) + ";";
    comandoSQL += "SELECT * FROM Resposta_questao WHERE idResposta_Prova = ";
    comandoSQL += to_string(id) + ";";
}

ComandoConsultarResposta::ComandoConsultarResposta(int idAluno, int idProva){
    comandoSQL = "SELECT * FROM Resposta_Prova WHERE Prova_idProva = ";
    comandoSQL += to_string(idProva) + " AND Aluno_idAluno = ";
    comandoSQL += to_string(idAluno) + ";";
    comandoSQL += "SELECT * FROM Resposta_questao WHERE idResposta_Prova = ";
    comandoSQL += to_string(id) + ";";
}

Resposta ComandoConsultarResposta::getResultado() {
        ElementoResultado resultado;
        Resposta resposta;

        if(listaResultado.size() < 3)
                throw EErroPersistencia("Lista de resultados vazia.");

        resultado = listaResultado.back();
        listaResultado.pop_back();
		resposta.setId(stoi(resultado.getValorColuna()));

		resultado = listaResultado.back();
        listaResultado.pop_back();
		resposta.setIdProva(stoi(resultado.getValorColuna()));

	    resultado = listaResultado.back();
        listaResultado.pop_back();
		resposta.setIdEstudante(stoi(resultado.getValorColuna()));

        map<int, int> respostaQuestoes;
        while (!listaResultado.empty()) {
                //id Resposta questao
                listaResultado.pop_back();

                resultado = listaResultado.back();
                listaResultado.pop_back();
				int numResposta = stoi(resultado.getValorColuna());

				resultado = listaResultado.back();
                listaResultado.pop_back();
				int idQuestao = stoi(resultado.getValorColuna());

				respostaQuestoes.insert(std::make_pair(idQuestao, numResposta));
                
				// id Resposta Prova
				listaResultado.pop_back();
        }
		resposta.setResposta(respostaQuestoes);
        return resposta;
}


ComandoListarTurmas::ComandoListarTurmas(){
        comandoSQL = "SELECT * FROM Turma";
}

list<Turma> ComandoListarTurmas::getResultado(){
        ElementoResultado resultado;

        if (listaResultado.empty()){
                throw EErroPersistencia("Lista de resultados vazia.");
        }

        list<Turma> turmas;

        while (!listaResultado.empty()){
                Turma turma_atual;

                resultado = listaResultado.back();
                listaResultado.pop_back();
		turma_atual.setId(stoi(resultado.getValorColuna()));
                
                resultado = listaResultado.back();
                listaResultado.pop_back();
		turma_atual.setNome(resultado.getValorColuna());

                resultado = listaResultado.back();
                listaResultado.pop_back();
		turma_atual.setDescricao(resultado.getValorColuna());

                resultado = listaResultado.back();
                listaResultado.pop_back();
		if (resultado.getValorColuna() == "0"){
                        turma_atual.switchAberta();
                }
                
                // quantidade de alunos
                // resultado = listaResultado.back();
                // listaResultado.pop_back();

                resultado = listaResultado.back();
                listaResultado.pop_back();
                turma_atual.setIdProf(stoi(resultado.getValorColuna()));
                
                // id do usuario novamente
                resultado = listaResultado.back();
                listaResultado.pop_back();

                turmas.push_back(turma_atual);
        }

        return turmas;
}

ComandoListarProvas::ComandoListarProvas(int id) {
        comandoSQL = "SELECT * FROM Prova WHERE Turma_idTurma = ";
        comandoSQL += to_string(id) + ";";
}

list<Prova> ComandoListarProvas::getResultado(){
        ElementoResultado resultado;
        if (listaResultado.empty()){
                throw EErroPersistencia("Lista de resultados vazia.");
        }

        list<Prova> provas;
        list<ComandoConsultarProva> cmdsConsultarProva;
        while (!listaResultado.empty()){
                // Prova prova_atual;

                resultado = listaResultado.back();
                listaResultado.pop_back();
		int idProvaAtual = stoi(resultado.getValorColuna());

                resultado = listaResultado.back();
                listaResultado.pop_back();
                
                // numero de questoes
                resultado = listaResultado.back();
                listaResultado.pop_back();
		
                resultado = listaResultado.back();
                listaResultado.pop_back();

                ComandoConsultarProva cmdConsultar(idProvaAtual);
                cmdsConsultarProva.push_back(cmdConsultar);
                // cmdConsultar.executar();
                // prova_atual = cmdConsultar.getResultado();

                // provas.push_back(prova_atual);
        }
        for (list<ComandoConsultarProva>::iterator it = cmdsConsultarProva.begin(); it != cmdsConsultarProva.end(); ++it) {
                it->executar();
                Prova provaAtual = it->getResultado();
                provas.push_back(provaAtual);
        }

        return provas;
}

ComandoListarIDAlunosTurma::ComandoListarIDAlunosTurma(int id){
        comandoSQL = "SELECT * FROM Aluno WHERE Turma_idTurma = ";
        comandoSQL += to_string(id) + ";";
}

list<int> ComandoListarIDAlunosTurma::getResultado(){
        ElementoResultado resultado;
        if (listaResultado.empty()){
                throw EErroPersistencia("Lista de resultados vazia.");
        }

        list<int> id_Usuarios;
        while (!listaResultado.empty()){
                // idAluno
                resultado = listaResultado.back();
                listaResultado.pop_back();

                // Turma_idTurma
                resultado = listaResultado.back();
                listaResultado.pop_back();

                // Usuario_idUsuario
                resultado = listaResultado.back();
                listaResultado.pop_back();
                id_Usuarios.push_back(stoi(resultado.getValorColuna()));
        }

        return id_Usuarios;
}

list<Usuario> ListarAlunosTurma::executar(int id){
        ComandoListarIDAlunosTurma cmd_Listar(id);
        cmd_Listar.executar();
        list<int> id_Usuarios = cmd_Listar.getResultado();
        list<Usuario> usuarios;

        while (!id_Usuarios.empty()){
                int id_atual;
                Usuario usuario_atual;

                id_atual = id_Usuarios.back();
                id_Usuarios.pop_back();

                ComandoConsultarUsuario cmd_Consultar(id_atual);
                cmd_Consultar.executar();
                usuario_atual = cmd_Consultar.getResultado();

                usuarios.push_back(usuario_atual);
        }

        return usuarios;
}

ComandoListarIDQuestoesProva::ComandoListarIDQuestoesProva(int id){
        comandoSQL = "SELECT * FROM Prova_has_Questao WHERE Prova_idProva = ";
        comandoSQL += to_string(id) + ";";
}

list<int> ComandoListarIDQuestoesProva::getResultado(){
        ElementoResultado resultado;
        if (listaResultado.empty()){
                throw EErroPersistencia("Lista de resultados vazia.");
        }

        list<int> id_Questoes;
        while (!listaResultado.empty()){
                // Prova_idProva
                resultado = listaResultado.back();
                listaResultado.pop_back();

                // Questao_idQuestao
                resultado = listaResultado.back();
                listaResultado.pop_back();
                id_Questoes.push_back(stoi(resultado.getValorColuna()));
        }

        return id_Questoes;
}

list<Questao> ListarQuestoesProva::executar(int id){
        ComandoListarIDQuestoesProva cmd_Listar(id);
        cmd_Listar.executar();
        list<int> id_Questoes = cmd_Listar.getResultado();
        list<Questao> questoes;

        while (!id_Questoes.empty()){
                int id_atual;
                Questao questao_atual;

                id_atual = id_Questoes.back();
                id_Questoes.pop_back();

                ComandoConsultarQuestao cmd_Consultar(id_atual);
                cmd_Consultar.executar();
                questao_atual = cmd_Consultar.getResultado();

                questoes.push_back(questao_atual);
        }

        return questoes;
}

ComandoCountProva::ComandoCountProva() {
        comandoSQL = "SELECT COUNT(*) FROM Prova";
}

int ComandoCountProva::getResultado() {
        int numeroDeProvas = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return numeroDeProvas;
}

ComandoCountQuestao::ComandoCountQuestao() {
        comandoSQL = "SELECT COUNT(*) FROM Questao";
}

int ComandoCountQuestao::getResultado() {
        int numeroDeQuestoes = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return numeroDeQuestoes;
}

ComandoCountResposta::ComandoCountResposta() {
        comandoSQL = "SELECT COUNT(*) FROM Resposta_Prova";
}

int ComandoCountResposta::getResultado() {
        int numeroDeRespostas = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        return numeroDeRespostas;
}

ComandoListarIdTurmaAluno::ComandoListarIdTurmaAluno(int id){
        comandoSQL = "SELECT * FROM UsuarioTurma WHERE Usuario_idUsuario = ";
        comandoSQL += to_string(id) + ";";
}

list<int> ComandoListarIdTurmaAluno::getResultado() {
        ElementoResultado resultado;
        if (listaResultado.empty()){
                throw EErroPersistencia("Lista de resultados vazia.");
        }

        list<int> idTurmas;
        while (!listaResultado.empty()){
                // Usuario_idUsuario
                resultado = listaResultado.back();
                listaResultado.pop_back();

                // Turma_idTurma
                resultado = listaResultado.back();
                listaResultado.pop_back();
                idTurmas.push_back(stoi(resultado.getValorColuna()));
        }

        return idTurmas;
}

list<Turma> ListarTurmasAluno::executar(int id) {
        ComandoListarIdTurmaAluno cmdListar(id);
        cmdListar.executar();
        list<int> idTurmas = cmdListar.getResultado();
        list<Turma> turmas;

        while (!idTurmas.empty()) {
                int idAtual;
                Turma turmaAtual;

                idAtual = idTurmas.back();
                idTurmas.pop_back();

                ComandoConsultarTurma cmdConsultar(idAtual);
                cmdConsultar.executar();
                turmaAtual = cmdConsultar.getResultado();

                turmas.push_back(turmaAtual);
        }
        return turmas;
}

ComandoListarIdTurmasProfessor::ComandoListarIdTurmasProfessor(int id) {
        comandoSQL = "SELECT * FROM Turma WHERE Professor_Usuario_idUsuario = ";
        comandoSQL += to_string(id) + ";";
}

list<Turma> ComandoListarIdTurmasProfessor::getResultado() {
       ElementoResultado resultado;

        if (listaResultado.empty()){
                throw EErroPersistencia("Lista de resultados vazia.");
        }

        list<Turma> turmas;

        while (!listaResultado.empty()){
                Turma turma_atual;

                resultado = listaResultado.back();
                listaResultado.pop_back();
		turma_atual.setId(stoi(resultado.getValorColuna()));

                resultado = listaResultado.back();
                listaResultado.pop_back();
		turma_atual.setNome(resultado.getValorColuna());

                resultado = listaResultado.back();
                listaResultado.pop_back();
		turma_atual.setDescricao(resultado.getValorColuna());

                resultado = listaResultado.back();
                listaResultado.pop_back();
		if (resultado.getValorColuna() == "0"){
                        turma_atual.switchAberta();
                }
                
                // // quantidade de alunos
                // resultado = listaResultado.back();
                // listaResultado.pop_back();

                resultado = listaResultado.back();
                listaResultado.pop_back();
                turma_atual.setIdProf(stoi(resultado.getValorColuna()));
                
                // id do usuario novamente
                resultado = listaResultado.back();
                listaResultado.pop_back();

                turmas.push_back(turma_atual);
        }

        return turmas;
}

ComandoBuscarRespostaAluno::ComandoBuscarRespostaAluno(int idProva, int idAluno) {
        comandoSQL = "SELECT * FROM Resposta_Prova WHERE Prova_idProva = ";
        comandoSQL += to_string(idProva) + "and" + to_string(idAluno) + ";";
}

bool ComandoBuscarRespostaAluno::getResultado() {
        int numeroDeRespostas = stoi(listaResultado.back().getValorColuna());
        listaResultado.pop_back();
        if (numeroDeRespostas == 0) {
                return true;
        }
        return false;
}