#include "Comandos.h"

void ComandoIAUsuarioDescadastrar::executar(IServicoUsuario* cntrServicoUsuario, Matricula* matricula){

    TelaMensagem telaMensagem;
    bool resultado;
    char input;

    while(true) {

        TelaDescadastro telaDescadastro;
        input = telaDescadastro.apresentar();

        if (input == 'S' || input == 's') {
            resultado = cntrServicoUsuario->descadastrar(*matricula);
            break;
        }
        else if (input == 'N' || input == 'n') {
            resultado = false;
            return;
        }
        else {
            TelaMensagem telaMensagem;
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    if(resultado){
        telaMensagem.apresentar("Sucesso na execucao da operacao.");
    }
    else {
        telaMensagem.apresentar("Falha na execucao da operacao");
    }
}

void ComandoIAUsuarioEditar::executar(IServicoUsuario* cntrServicoUsuario, Matricula* matricula){

    bool resultado;
    Usuario usuario;
    usuario.setMatricula(*matricula);
    TelaEdicaoUsuario telaEdicaoUsuario;
    // A seguir, incluir código de interação com o usuário.

    // Solicitar serviço.
    telaEdicaoUsuario.apresentar(&usuario);
    resultado = cntrServicoUsuario->editar(usuario);

    // Criticar resultado e apresentar mensagem correspondente.
    TelaMensagem telaMensagem;
    if(resultado){
         telaMensagem.apresentar("Sucesso na execucao da operacao");
    }
    else {

        //cout << "Falha na execucao da operacao" << endl;
        telaMensagem.apresentar("Falha na execucao da operacao");
    }
}

void ComandoIAUsuarioConsultar::executar(IServicoUsuario* cntrServicoUsuario, Matricula* matricula){

    bool resultado;
    Usuario * usuario = new Usuario();
    usuario->setMatricula(*matricula);

    // A seguir, incluir código de interação com o usuário.

    // Solicitar serviço.

    resultado = cntrServicoUsuario->consultar(usuario);

    // Criticar resultado e apresentar mensagem correspondente.

    if(resultado){
         //cout << "Sucesso na execucao da operacao" << endl;
        TelaConsultarUsuario telaConsultarUsuario;
        telaConsultarUsuario.apresentar(*usuario);
    }
    else {
        //cout << "Falha na execucao da operacao" << endl;
        TelaMensagem telaMensagem;
        telaMensagem.apresentar("Falha na execucao da operacao");
    }
}

//IAProjetos

void ComandoIAProjetoConsultarProjeto::executar(IServicoProjeto* cntrServicoProjeto, Matricula* matricula) {

    Projeto* projeto = new Projeto();
    Codigo* codigo = new Codigo();
    TelaCodigo telaCodigo;
    TelaMensagem telaMensagem;

    projeto->SetUsuario(*matricula);
    while (true) {
        try {
            telaCodigo.apresentar(codigo);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Cogido Invalido.");
        }
    }
    projeto->setCodigo(*codigo);

    if(cntrServicoProjeto->consultarProjeto(projeto)){
        bool continuar = true;
        while(continuar) {
            TelaConsultaProjeto telaConsultaProjeto;
            switch(telaConsultaProjeto.apresentar(projeto)) {
                case '1':
                    ComandoIAProjetoEditarProjeto comando;
                    comando.executar(cntrServicoProjeto, *projeto);
                    cntrServicoProjeto->consultarProjeto(projeto);
                    break;
                case '3':
                    continuar = false;
                    break;
                default:
                    telaMensagem.apresentar("Opcao Invalida");
            }
        }
    }
    else {
        telaMensagem.apresentar("Projeto Nao Encontrado");
    }
    delete codigo;
    delete projeto;
}

void ComandoIAProjetoCadastrarProjeto::executar(IServicoProjeto* cntrServicoProjeto, Matricula* matricula) {

    Projeto projeto;
    projeto.SetUsuario(*matricula);

    TelaCadastroProjeto telaCadastroProjeto;
    TelaMensagem telaMensagem;
    while(true) {
        try {
            telaCadastroProjeto.apresentar(&projeto);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    if (cntrServicoProjeto->cadastrarProjeto(projeto)) {
        telaMensagem.apresentar("Projeto cadastrado.");
    }
    else {
        telaMensagem.apresentar("Ocorreu um erro durante o cadastramento");
    }
}

void ComandoIAProjetoEditarProjeto::executar(IServicoProjeto* cntrServicoProjeto, Projeto projeto) {

    TelaEdicaoProjeto telaEdicaoProjeto;
    TelaMensagem telaMensagem;

    while(true) {
        try {
            telaEdicaoProjeto.apresentar(&projeto);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    if (cntrServicoProjeto->editarProjeto(projeto)) {
        telaMensagem.apresentar("Projeto editado com sucesso.");
    }
    else {
        telaMensagem.apresentar("Ocorreu um erro durante a edicao do projeto.");
    }
}

// ISProjetos

bool ComandoISProjetoConsultarProjeto::executar(Projeto* projeto) {
    ContainerProjeto* container;
    container = ContainerProjeto::getInstancia();

    return container->pesquisar(projeto);
}

bool ComandoISProjetoCadastrarProjeto::executar(Projeto projeto) {
    ContainerProjeto* container;
    container = ContainerProjeto::getInstancia();

    return container->incluir(projeto);
}

bool ComandoISProjetoEditarProjeto::executar(Projeto projeto) {
    ContainerProjeto* container;
    container = ContainerProjeto::getInstancia();

    return container->atualizar(projeto);
}

