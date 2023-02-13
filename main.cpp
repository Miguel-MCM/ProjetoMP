#include <string.h>
#include <stdexcept>
#include <iostream>
#include "Interfaces.h"
#include "Controladoras.h"
#include "Builders.h"

#include "ComandosSQL.h"


int main() {
    Usuario usuario, outroUsuario;
    usuario.setNome("Miguel");
    usuario.setEmail("email@email.com");
    usuario.setSenha("123456");
    usuario.setCargo("aluno");

    CadastrarUsuario cmdCadastrar;
    ComandoConsultarUsuario cmdConsultar(1);
    usuario.setNome("Novo Nome");
    ComandoEditarUsuario cmdEditar(usuario);
    ComandoDescadastrarUsuario cmdDescadastrar(6, "professor");

    try {
        // cmdCadastrar.executar(usuario);
        cmdDescadastrar.executar();
    }
    catch(EErroPersistencia &e){
        std::cout << e.what() << std::endl;
    }

    // ComandoCadastrarUsuario cmd(usuario);
    // cmd.executar();
    // cmd.getResultado();

    /*
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
    */

    return 0;
}
