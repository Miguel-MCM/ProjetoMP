#include <gtest/gtest.h>

#include "ComandosSQL.h"

//  Usuarios ja cadastrados no banco
const int ID_PROFESSOR_TESTE = 1;
const char EMAIL_PROFESSOR_TESTE[] = "email@professor"; 
const char NOME_PROFESSOR_TESTE[] = "Professor de Testes";
const char SENHA_PROFESSOR_TESTE[] = "senha123";

const int ID_ALUNO_TESTE = 2;
const char EMAIL_ALUNO_TESTE[] = "email@aluno"; 
const char NOME_ALUNO_TESTE[] = "Aluno de Teste Consulta";
const char SENHA_ALUNO_TESTE[] = "123456";

const int ID_ADMIN_TESTE = 3;
const char EMAIL_ADMIN_TESTE[] = "email@admin"; 
const char NOME_ADMIN_TESTE[] = "Admin";
const char SENHA_ADMIN_TESTE[] = "123456";


// Usuario ja cadastrado que sera editado
const int ID_USUARIO_EDITAR = 4;
const char EMAIL_USUARIO_EDITAR[] = "email@editar"; 
const char NOME_USUARIO_EDITAR[] = "Teste Editar";
const char SENHA_USUARIO_EDITAR[] = "123456";
const char CARGO_USUARIO_EDITAR[] = "aluno";

const char NOME_USUARIO_EDITAR_EDITADO[] = "TESTE JA EDITADO";
const char SENHA_USUARIO_EDITAR_EDITADO[] = "654321";
const char EMAIL_USUARIO_EDITAR_EDITADO[] = "editado@email";

// Usuario que será cadastrado e descadastrado
const char NOME_USUARIO[] = "Nome de Teste";
const char SENHA_USUARIO[] = "123456";
const char EMAIL_USUARIO[] = "outro10@teste.com";
const char CARGO_USUARIO[] = "aluno";


const char NOME_TURMA[] = "Nome da Turma";
const char DESCRICAO_TURMA[] = "Descricao da Turma";

const int ID_PROVA = 1;

const int ID_QUESTAO_1 = 1;
const char NOME_QUESTAO_1[] = "Questao 1";
const char TEXTO_QUESTAO_1[] = "Quanto e 1 + 1 ?";
const int NUM_ALTERNATIVAS_QUESTAO_1 = 3;
const int ALTERNATIVA_CORRETA_QUESTAO_1 = 2;



const int ID_QUESTAO_2 = 2;
const char NOME_QUESTAO_2[] = "Questao 2";
const char TEXTO_QUESTAO_2[] = "Alguma duvida?";
const int NUM_ALTERNATIVAS_QUESTAO_2 = 3;
const int ALTERNATIVA_CORRETA_QUESTAO_2 = 3;

TEST(testComandoSQL, consultarUsuarioPeloId) {
    int id = ID_ALUNO_TESTE;
    ComandoConsultarUsuario cmdConsultar(id);
    try {
        cmdConsultar.executar();
    }
    catch (EErroPersistencia &e) {
        FAIL() << "Erro ao executar\n" << e.what();
    }
    Usuario usuarioConsultado;
    try {
        usuarioConsultado = cmdConsultar.getResultado();
    }
    catch (EErroPersistencia &e) {
        FAIL() << "Erro em getResultado\n" << e.what();
    }
    catch (invalid_argument &e) {
        FAIL() << e.what();
    }

    EXPECT_EQ(usuarioConsultado.getId(), id);
    EXPECT_STREQ(usuarioConsultado.getNome().c_str(), NOME_ALUNO_TESTE);
    EXPECT_STREQ(usuarioConsultado.getSenha().c_str(), SENHA_ALUNO_TESTE);
    EXPECT_STREQ(usuarioConsultado.getEmail().c_str(), EMAIL_ALUNO_TESTE);
    EXPECT_STREQ(usuarioConsultado.getCargo().c_str(), "aluno");
}

TEST(testComandoSQL, consultarUsuarioPeloEmail) {
    string email = EMAIL_ALUNO_TESTE;
    ComandoConsultarUsuario cmdConsultar(email);
    try {
        cmdConsultar.executar();
    }
    catch (EErroPersistencia &e) {
        FAIL() << "Erro ao executar\n" << e.what();
    }
    Usuario usuarioConsultado;
    try {
        usuarioConsultado = cmdConsultar.getResultado();
    }
    catch (EErroPersistencia &e) {
        FAIL() << "Erro em getResultado\n" << e.what();
    }
    catch (invalid_argument &e) {
        FAIL() << e.what();
    }

    EXPECT_EQ(usuarioConsultado.getId(), ID_ALUNO_TESTE);
    EXPECT_STREQ(usuarioConsultado.getNome().c_str(), NOME_ALUNO_TESTE);
    EXPECT_STREQ(usuarioConsultado.getSenha().c_str(), SENHA_ALUNO_TESTE);
    EXPECT_STREQ(usuarioConsultado.getEmail().c_str(), EMAIL_ALUNO_TESTE);
    EXPECT_STREQ(usuarioConsultado.getCargo().c_str(), "aluno");
}

TEST(testComandoSQL, cadastrarDescadastrarUsuario) {
    Usuario usuario;
    usuario.setNome(NOME_USUARIO);
    usuario.setSenha(SENHA_USUARIO);
    usuario.setEmail(EMAIL_USUARIO);
    usuario.setCargo(CARGO_USUARIO);

    CadastrarUsuario cadastrar;
    int id;
    try {
        id = cadastrar.executar(usuario);
    }
    catch (EErroPersistencia &e) {
        FAIL() << e.what();
    }

    Usuario consulta;
    ComandoConsultarUsuario cmdConsultar(id);

    try {
        cmdConsultar.executar();
        consulta = cmdConsultar.getResultado();
    }
    catch(EErroPersistencia &e) {
        FAIL() << e.what() << " " << id;
    }
    catch(invalid_argument &e) {
        FAIL() << e.what() << " " << id;
    }
    int consulta_id = consulta.getId();

    EXPECT_EQ(consulta_id, id);
    EXPECT_STREQ(consulta.getNome().c_str(), usuario.getNome().c_str()) << consulta.getNome() + " != " + usuario.getNome()  ;
    EXPECT_STREQ(consulta.getSenha().c_str(), usuario.getSenha().c_str());
    EXPECT_STREQ(consulta.getEmail().c_str(), usuario.getEmail().c_str());
    EXPECT_STREQ(consulta.getCargo().c_str(), usuario.getCargo().c_str());

    ComandoDescadastrarUsuario cmdDescadastrar(id, CARGO_USUARIO);
    cmdDescadastrar.executar();
    cmdConsultar.executar();
    ASSERT_THROW(cmdConsultar.getResultado(), EErroPersistencia);
}

TEST(testComandoSQL, editarUsuario) {
    int id = ID_USUARIO_EDITAR;
    ComandoConsultarUsuario cmdConsultar(id);
    cmdConsultar.executar();
    Usuario usuarioEditar = cmdConsultar.getResultado();

    usuarioEditar.setNome(NOME_USUARIO_EDITAR_EDITADO);
    usuarioEditar.setEmail(EMAIL_USUARIO_EDITAR_EDITADO);
    usuarioEditar.setSenha(SENHA_USUARIO_EDITAR_EDITADO);
    ComandoEditarUsuario cmdEditar(usuarioEditar);
    try {
        cmdEditar.executar();
    }
    catch (EErroPersistencia &e) {
        FAIL() << e.what();
    }

    cmdConsultar.executar();
    Usuario usuarioEditado = cmdConsultar.getResultado();
    
    EXPECT_EQ(usuarioEditado.getId(), ID_USUARIO_EDITAR);
    EXPECT_STREQ(usuarioEditado.getNome().c_str(), NOME_USUARIO_EDITAR_EDITADO);
    EXPECT_STREQ(usuarioEditado.getSenha().c_str(), SENHA_USUARIO_EDITAR_EDITADO);
    EXPECT_STREQ(usuarioEditado.getEmail().c_str(), EMAIL_USUARIO_EDITAR_EDITADO);
    EXPECT_STREQ(usuarioEditado.getCargo().c_str(), "aluno");

    Usuario usuarioReeditar = usuarioEditado;
    usuarioReeditar.setNome(NOME_USUARIO_EDITAR);
    usuarioReeditar.setEmail(EMAIL_USUARIO_EDITAR);
    usuarioReeditar.setSenha(SENHA_USUARIO_EDITAR);

    ComandoEditarUsuario cmdReeditar(usuarioReeditar);
    cmdReeditar.executar();
}

TEST(testComandosSQLListar, listarProva) {
    int id = ID_PROVA;
    ListarQuestoesProva listarQuestoesProva;
    list<Questao> questoes;
    try {
        questoes = listarQuestoesProva.executar(id);
    }
    catch (EErroPersistencia &e) {
        FAIL() << e.what();
    }
    catch (invalid_argument &e) {
        FAIL() << e.what();
    }

    for(list<Questao>::iterator it = questoes.begin(); it != questoes.end() ; it++) {
        int idQuestao = it->getId();
        switch (idQuestao) {
        case ID_QUESTAO_1:
            EXPECT_EQ(it->getIdProf(), ID_PROFESSOR_TESTE);
            EXPECT_STREQ(it->getNome().c_str(), NOME_QUESTAO_1);
            EXPECT_STREQ(it->getTexto().c_str(), TEXTO_QUESTAO_1);
            EXPECT_EQ(it->getRespostaCorreta(), ALTERNATIVA_CORRETA_QUESTAO_1);
            EXPECT_EQ(it->getAlternativas().size(), NUM_ALTERNATIVAS_QUESTAO_1);
            break;
        case ID_QUESTAO_2:
            EXPECT_EQ(it->getIdProf(), ID_PROFESSOR_TESTE);
            EXPECT_STREQ(it->getNome().c_str(), NOME_QUESTAO_2);
            EXPECT_STREQ(it->getTexto().c_str(), TEXTO_QUESTAO_2);
            EXPECT_EQ(it->getRespostaCorreta(), ALTERNATIVA_CORRETA_QUESTAO_2);
            EXPECT_EQ(it->getAlternativas().size(), NUM_ALTERNATIVAS_QUESTAO_2);
            break;
        default:
            FAIL() << "Questao com id errado: " << idQuestao;
            break;
        }
    }
}
