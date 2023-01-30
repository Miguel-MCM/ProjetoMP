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
    // A seguir, incluir c�digo de intera��o com o usu�rio.

    // Solicitar servi�o.
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

    // A seguir, incluir c�digo de intera��o com o usu�rio.

    // Solicitar servi�o.

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

void ComandoIAProvaConsultarProva::executar(IServicoProva* cntrServicoProva, Matricula* matricula) {

    Prova* prova = new Prova();
    Codigo* codigo = new Codigo();
    TelaCodigo telaCodigo;
    TelaMensagem telaMensagem;

    prova->SetUsuario(*matricula);
    while (true) {
        try {
            telaCodigo.apresentar(codigo);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Cogido Invalido.");
        }
    }
    prova->setCodigo(*codigo);

    if(cntrServicoProva->consultarProva(prova)){
        bool continuar = true;
        while(continuar) {
            TelaConsultaProva telaConsultaProva;
            switch(telaConsultaProva.apresentar(prova)) {
                case '1':
                    ComandoIAProvaEditarProva comando;
                    comando.executar(cntrServicoProva, *prova);
                    cntrServicoProva->consultarProva(prova);
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
        telaMensagem.apresentar("Prova Nao Encontrado");
    }
    delete codigo;
    delete prova;
}

void ComandoIAProvaCadastrarProva::executar(IServicoProva* cntrServicoProva, Matricula* matricula) {

    Prova prova;
    prova.SetUsuario(*matricula);

    TelaCadastroProva telaCadastroProva;
    TelaMensagem telaMensagem;
    while(true) {
        try {
            telaCadastroProva.apresentar(&prova);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    if (cntrServicoProva->cadastrarProva(prova)) {
        telaMensagem.apresentar("Prova cadastrado.");
    }
    else {
        telaMensagem.apresentar("Ocorreu um erro durante o cadastramento");
    }
}

void ComandoIAProvaEditarProva::executar(IServicoProva* cntrServicoProva, Prova prova) {

    TelaEdicaoProva telaEdicaoProva;
    TelaMensagem telaMensagem;

    while(true) {
        try {
            telaEdicaoProva.apresentar(&prova);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    if (cntrServicoProva->editarProva(prova)) {
        telaMensagem.apresentar("Prova editado com sucesso.");
    }
    else {
        telaMensagem.apresentar("Ocorreu um erro durante a edicao do prova.");
    }
}

// ISProjetos

bool ComandoISProvaConsultarProva::executar(Prova* prova) {
    ContainerProva* container;
    container = ContainerProva::getInstancia();

    return container->pesquisar(prova);
}

bool ComandoISProvaCadastrarProva::executar(Prova prova) {
    ContainerProva* container;
    container = ContainerProva::getInstancia();

    return container->incluir(prova);
}

bool ComandoISProvaEditarProva::executar(Prova prova) {
    ContainerProva* container;
    container = ContainerProva::getInstancia();

    return container->atualizar(prova);
}

