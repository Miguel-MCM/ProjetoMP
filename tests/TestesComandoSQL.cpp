#include <gtest/gtest.h>

#include "ComandosSQL.h"

const int ID_PROFESSOR = 1;

const char NOME_USUARIO[] = "Nome de Teste";
const char SENHA_USUARIO[] = "123456";
const char EMAIL_USUARIO[] = "outro7@teste.com";
const char CARGO_USUARIO[] = "aluno";



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

TEST(testComandoSQL, usuario) {
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
    cmdConsultar.executar();
    consulta = cmdConsultar.getResultado();
    int consulta_id = consulta.getId();

    ASSERT_EQ(consulta_id, id);
    ASSERT_STREQ(consulta.getNome().c_str(), usuario.getNome().c_str()) << consulta.getNome() + " != " + usuario.getNome()  ;
    ASSERT_STREQ(consulta.getSenha().c_str(), usuario.getSenha().c_str());
    ASSERT_STREQ(consulta.getEmail().c_str(), usuario.getEmail().c_str());
    ASSERT_STREQ(consulta.getCargo().c_str(), usuario.getCargo().c_str());

    ComandoDescadastrarUsuario cmdDescadastrar(id, CARGO_USUARIO);
    cmdDescadastrar.executar();

    try {
        cmdConsultar.executar();
    }
    catch(...) {

    }
    ASSERT_THROW(cmdConsultar.getResultado(), EErroPersistencia);
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
            EXPECT_EQ(it->getIdProf(), ID_PROFESSOR);
            EXPECT_STREQ(it->getNome().c_str(), NOME_QUESTAO_1);
            EXPECT_STREQ(it->getTexto().c_str(), TEXTO_QUESTAO_1);
            EXPECT_EQ(it->getRespostaCorreta(), ALTERNATIVA_CORRETA_QUESTAO_1);
            EXPECT_EQ(it->getAlternativas().size(), NUM_ALTERNATIVAS_QUESTAO_1);
            break;
        case ID_QUESTAO_2:
            EXPECT_EQ(it->getIdProf(), ID_PROFESSOR);
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