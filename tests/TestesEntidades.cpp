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


