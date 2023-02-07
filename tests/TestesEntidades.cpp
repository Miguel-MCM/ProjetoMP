#include <gtest/gtest.h>
#include "Entidades.h"

const char* STR_VAZIA = "";

const int ID_VALIDO = 1;
const char* USUARIO_NOME_VALIDO = "Joao Paulo";
const char* USUARIO_EMAIL_VALIDO = "email@email.com";
const char* USUARIO_SENHA_VALIDA = "123456";
const char* USUARIO_CARGO_VALIDO = "professor";

const char* USUARIO_EMAIL_INVALIDO = "email2email.com";
const char* USUARIO_SENHA_INVALIDA = "123";
const char* USUARIO_CARGO_INVALIDO = "diretor";

const char* TURMA_NOME_VALIDO = "Matematica";
const char* TURMA_DESCRICAO_VALIDA = "Provas de assuntos da materia da turma";

const char* QUESTAO_TEXTO = "Quanto e 1 + 1 ?";
const int   QUESTAO_RESP_CORRETA = 2;
const list<string> QUESTAO_ALTERNATIVAS({"1", "2", "3"});

const list<int> PROVA_ID_QUESTOES({1, 2, 3});

TEST(usuario, inserirDadosValido) {
    Usuario usuario;
    usuario.setId(ID_VALIDO);
    ASSERT_EQ(usuario.getId(), ID_VALIDO);

    usuario.setNome(USUARIO_NOME_VALIDO);
    ASSERT_STREQ(usuario.getNome().c_str(), USUARIO_NOME_VALIDO);

    usuario.setEmail(USUARIO_EMAIL_VALIDO);
    ASSERT_STREQ(usuario.getEmail().c_str(), USUARIO_EMAIL_VALIDO);

    usuario.setSenha(USUARIO_SENHA_VALIDA);
    ASSERT_STREQ(usuario.getSenha().c_str(), USUARIO_SENHA_VALIDA);

    usuario.setCargo(USUARIO_CARGO_VALIDO);
    ASSERT_STREQ(usuario.getCargo().c_str(), USUARIO_CARGO_VALIDO);
}

TEST(usuario, setDadosVazios) {
    Usuario usuario;

    EXPECT_THROW(usuario.setNome(STR_VAZIA), invalid_argument);
    EXPECT_THROW(usuario.setEmail(STR_VAZIA), invalid_argument);
    EXPECT_THROW(usuario.setSenha(STR_VAZIA), invalid_argument);
    EXPECT_THROW(usuario.setCargo(STR_VAZIA), invalid_argument);
}

TEST(usuario, setDadosInvalidos) {
    Usuario usuario;

    EXPECT_THROW(usuario.setEmail(USUARIO_EMAIL_INVALIDO), invalid_argument);
    EXPECT_THROW(usuario.setSenha(USUARIO_SENHA_INVALIDA), invalid_argument);
    EXPECT_THROW(usuario.setCargo(USUARIO_CARGO_INVALIDO), invalid_argument);

    ASSERT_STRNE(usuario.getEmail().c_str(), USUARIO_EMAIL_INVALIDO);
    ASSERT_STRNE(usuario.getSenha().c_str(), USUARIO_SENHA_INVALIDA);
    ASSERT_STRNE(usuario.getCargo().c_str(), USUARIO_CARGO_INVALIDO);
}

TEST(turma, setDadosValidos) {
    Turma turma;
    bool estavaAberta = turma.taAberta();

    turma.setId(ID_VALIDO);
    ASSERT_EQ(turma.getId(), ID_VALIDO);

    turma.setNome(TURMA_NOME_VALIDO);
    ASSERT_STREQ(turma.getNome().c_str(), TURMA_NOME_VALIDO);

    turma.setDescricao(TURMA_DESCRICAO_VALIDA);
    ASSERT_STREQ(turma.getDescricao().c_str(), TURMA_DESCRICAO_VALIDA);

    turma.switchAberta();
    ASSERT_NE(turma.taAberta(), estavaAberta);

    turma.setIdProf(ID_VALIDO);
    ASSERT_EQ(turma.getIdProf(), ID_VALIDO);
}

TEST(turma, setDescricaoVazia) {
    Turma turma;
    EXPECT_THROW(turma.setDescricao(STR_VAZIA), invalid_argument);
}

TEST(questao, setDadosValidos) {
    Questao questao;
    questao.setId(ID_VALIDO);
    ASSERT_EQ(questao.getId(), ID_VALIDO);

    questao.setIdProf(ID_VALIDO);
    ASSERT_EQ(questao.getIdProf(), ID_VALIDO);

    questao.setTexto(QUESTAO_TEXTO);
    ASSERT_STREQ(questao.getTexto().c_str(), QUESTAO_TEXTO);

    questao.setRespostaCorreta(QUESTAO_RESP_CORRETA);
    ASSERT_EQ(questao.getRespostaCorreta(), QUESTAO_RESP_CORRETA);

    questao.setAlternativas(QUESTAO_ALTERNATIVAS);
    ASSERT_EQ(questao.getAlternativas(), QUESTAO_ALTERNATIVAS);
}

TEST(prova, setDadosValidos) {
    Prova prova;
    prova.setIdTurma(ID_VALIDO);
    ASSERT_EQ(prova.getIdTurma(), ID_VALIDO);

    prova.setIdQuestoes(PROVA_ID_QUESTOES);
    ASSERT_EQ(prova.getIdQuestoes(), PROVA_ID_QUESTOES);
}

