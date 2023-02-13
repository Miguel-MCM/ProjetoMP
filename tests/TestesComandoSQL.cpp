#include <gtest/gtest.h>

#include "ComandosSQL.h"


const char NOME_USUARIO[] = "Nome de Teste";
const char SENHA_USUARIO[] = "123456";
const char EMAIL_USUARIO[] = "outro7@teste.com";
const char CARGO_USUARIO[] = "aluno";


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

    // ASSERT_EQ(consulta_id, id);
    // ASSERT_STREQ(consulta.getNome().c_str(), usuario.getNome().c_str()) << consulta.getNome() + " != " + usuario.getNome()  ;
    ASSERT_STREQ(consulta.getSenha().c_str(), usuario.getSenha().c_str());
    // ASSERT_STREQ(consulta.getEmail().c_str(), usuario.getEmail().c_str());
    // ASSERT_STREQ(consulta.getCargo().c_str(), usuario.getCargo().c_str());

    ComandoDescadastrarUsuario cmdDescadastrar(id, CARGO_USUARIO);
    cmdDescadastrar.executar();

    try {
        cmdConsultar.executar();
    }
    catch(...) {

    }
    ASSERT_THROW(cmdConsultar.getResultado(), EErroPersistencia);
}