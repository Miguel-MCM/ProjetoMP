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
                case '2':
                    ComandoIAProvaDescadastrarProva comandoDescadastrar;
                    if (comandoDescadastrar.executar(cntrServicoProva, *prova))
                        continuar = false;
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

bool ComandoIAProvaDescadastrarProva::executar(IServicoProva* cntrServicoProva, Prova prova) {
    TelaMensagem telaMensagem;
    bool resultado;
    char input;

    while(true) {

        TelaDescadastro telaDescadastro;
        input = telaDescadastro.apresentar();

        if (input == 'S' || input == 's') {
            resultado = cntrServicoProva->descadastrarProva(prova.getCodigo());
            break;
        }
        else if (input == 'N' || input == 'n') {
            resultado = false;
            return resultado;
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
    return resultado;
}


void ComandoIAProvaCadastrarQuestao::executar(IServicoProva* cntrServicoProva, Matricula* matricula) {

    Questao questao;
    questao.setUsuario(*matricula);

    TelaCadastroQuestao TelaCadastroQuestao;
    TelaMensagem telaMensagem;
    while(true) {
        try {
            TelaCadastroQuestao.apresentar(&questao);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    if (cntrServicoProva->cadastrarQuestao(questao)) {
        telaMensagem.apresentar("Questao cadastrada.");
    }
    else {
        telaMensagem.apresentar("Nao foi possivel realizar o cadastro");
    }
}

void ComandoIAProvaConsultarQuestao::executar(IServicoProva* cntrServicoProva, Matricula* matricula) {

    Questao* questao = new Questao();
    Codigo* codigo = new Codigo();
    TelaCodigo telaCodigo;
    TelaMensagem telaMensagem;

    questao->setUsuario(*matricula);
    while (true) {
        try {
            telaCodigo.apresentar(codigo);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Cogido Invalido.");
        }
    }
    questao->setCodigo(*codigo);

    if(cntrServicoProva->consultarQuestao(questao)){
        bool continuar = true;
        while(continuar) {
            TelaConsultaQuestao TelaConsultaQuestao;
            switch(TelaConsultaQuestao.apresentar(questao)) {
                case '1':
                    ComandoIAProvaEditarQuestao comando;
                    comando.executar(cntrServicoProva, *questao);
                    cntrServicoProva->consultarQuestao(questao);
                    break;
                case '2':
                    ComandoIAProvaDescadastrarQuestao comandoDescadastrar;
                    if (comandoDescadastrar.executar(cntrServicoProva, *questao))
                        continuar = false;
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
        telaMensagem.apresentar("Questao Nao Encontrada");
    }
    delete codigo;
    delete questao;
}

void ComandoIAProvaEditarQuestao::executar(IServicoProva* cntrServicoProva, Questao questao) {

    TelaEdicaoQuestao telaEdicaoQuestao;
    TelaMensagem telaMensagem;

    while(true) {
        try {
            telaEdicaoQuestao.apresentar(&questao);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    if (cntrServicoProva->editarQuestao(questao)) {
        telaMensagem.apresentar("Questao editada com sucesso.");
    }
    else {
        telaMensagem.apresentar("Ocorreu um erro durante a edicao da questao.");
    }
}

bool ComandoIAProvaDescadastrarQuestao::executar(IServicoProva* cntrServicoProva, Questao questao) {
    TelaMensagem telaMensagem;
    bool resultado;
    char input;

    while(true) {

        TelaDescadastro telaDescadastro;
        input = telaDescadastro.apresentar();

        if (input == 'S' || input == 's') {
            resultado = cntrServicoProva->descadastrarQuestao(questao.getCodigo());
            break;
        }
        else if (input == 'N' || input == 'n') {
            resultado = false;
            return resultado;
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
    return resultado;
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

bool ComandoISProvaDescadastrarProva::executar(Codigo codigo) {
    ContainerQuestao *containerQuestao = ContainerQuestao::getInstancia();
    if (!containerQuestao->removerPorProva(codigo))
        return false;
    ContainerProva *containerProva = ContainerProva::getInstancia();
    return containerProva->remover(codigo);
}

bool ComandoISProvaCadastrarQuestao::executar(Questao questao) {
    // Ver se o questao existe e pretence ao usuario
    ContainerProva *containerProva = ContainerProva::getInstancia();
    Prova prova;
    prova.SetUsuario(questao.getUsuario());
    prova.setCodigo(questao.getProva());
    if(!containerProva->pesquisar(&prova))
        return false;
    // cadastrar a tarefa
    ContainerQuestao *containerQuestao = ContainerQuestao::getInstancia();
    return containerQuestao->incluir(questao);
}

bool ComandoISProvaConsultarQuestao::executar(Questao* questao) {
    ContainerQuestao* container;
    container = ContainerQuestao::getInstancia();

    return container->pesquisar(questao);
}

bool ComandoISProvaEditarQuestao::executar(Questao questao) {
    ContainerQuestao* container;
    container = ContainerQuestao::getInstancia();

    return container->atualizar(questao);
}

bool ComandoISProvaDescadastarQuestao::executar(Codigo codigo) {
    ContainerQuestao* container;
    container = ContainerQuestao::getInstancia();

    return container->remover(codigo);
}