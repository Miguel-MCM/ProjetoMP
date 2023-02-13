#include <string.h>
#include <stdexcept>
#include <iostream>
#include "Interfaces.h"
#include "Controladoras.h"
#include "Builders.h"

#include "ComandosSQL.h"


int main() {
    // Usuario usuario, consulta;
    // usuario.setNome("nome");
    // usuario.setEmail("email@email");
    // usuario.setSenha("123456");
    // usuario.setCargo("aluno");

    // ComandoCadastrarUsuario cmd(usuario);
    // cmd.executar();
    // cmd.getResultado();

    // ComandoDescadastrarUsuario cmdDescadastrar(1);
    // cmdDescadastrar.executar();

    // ComandoConsultarUsuario cmdConsultar(usuario.getEmail());
    // cmdConsultar.executar();
    // consulta = cmdConsultar.getResultado();

    // std::cout << consulta.getNome() << std::endl;

    // Instanciar Builder.

    BuilderSistema* builder;
    builder = new BuilderSistema();

    // Construir (build) sistema.

    CntrApresentacaoControle* cntrApresentacaoControle;
    cntrApresentacaoControle = builder->construir();

    // Solicitar servico de apresentacao.

    cntrApresentacaoControle->executar();

    // Destruir builder.

    delete builder;

    return 0;
}
