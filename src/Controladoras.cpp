#include "Controladoras.h"
#include "Telas.h"

void CntrApresentacaoUsuario::executar(Usuario* usuario) {
    
    TelaMensagem telaMensagem;
    TelaConsultaUsuario telaConsultaUsuario;

    bool finalizou = false;
    while(!finalizou) {
        cntrServicoUsuario->consultar(usuario);
        switch (telaConsultaUsuario.apresentar(usuario)) {
        case '1':
            editar(usuario);
            break;
        case '2':
            TelaConfirmacao telaConfirmacao;
            if(telaConfirmacao.apresentar()) {
                if(cntrServicoUsuario->descadastrar(usuario->getId()))
                    finalizou = true;
                else
                    telaMensagem.apresentar("Erro no Processo.");
            }
            break;
        case '3':
            finalizou = true;
            break;
        default:
            telaMensagem.apresentar("Opcao Invalida.");
            break;
        }
    }
}

void CntrApresentacaoUsuario::editar(Usuario* usuario) {
    TelaMensagem telaMensagem;
    TelaFormulario telaFormulario;
    const string TITULO = "Edicao de Usuario";
    const vector<string> DADOS({
        "Nome: ",
        "Email: ",
        "Senha: "
    });
    string novosDados[DADOS.size()];

    telaFormulario.apresentar(TITULO, DADOS, novosDados);
    
    try {
        if(novosDados[0] != "")
            usuario->setNome(novosDados[0]);

        if(novosDados[1] != "")
            usuario->setEmail(novosDados[1]);

        if(novosDados[2] != "")
            usuario->setSenha(novosDados[2]);

        cntrServicoUsuario->editar(*usuario);
    }
    catch (invalid_argument &e) {
        telaMensagem.apresentar("Dado em Formato Incorreto.");

    }
}

void CntrApresentacaoControle::executar(){

    TelaControle telaControle;
    TelaMensagem telaMensagem;
    char opcaoControle;
    char opcaoMenu;

    while(true){

        opcaoControle = telaControle.apresentar();

        if(opcaoControle == '1') {
            if (cntrApresentacaoAutenticacao->autenticar(&matricula)) {
                TelaMenu telaMenu;
                cntrApresentacaoUsuario->setStatusCadastro(true);
                while(cntrApresentacaoUsuario->getStatusCadastro()) {
                    opcaoMenu = telaMenu.apresentar();
                    if (opcaoMenu == '1') {
                        cntrApresentacaoUsuario->executar(&matricula);
                    }
                    else if (opcaoMenu == '2') {
                        cntrApresentacaoProva->executar(&matricula);
                        //cntrApresentacaoProjeto/Tarefa
                    }
                    else if (opcaoMenu == '3') {
                        break;
                    }
                    else {
                        telaMensagem.apresentar("Dado em formato incorreto");
                    }
                }
            }
            else {
                telaMensagem.apresentar("Falha na autenticacao");
            }
        }
        else if (opcaoControle == '2') {
            cntrApresentacaoUsuario->cadastrar();
        }
        else if (opcaoControle == '3') {
            return;
        }
        else {
            telaMensagem.apresentar("Opcao invalida.");
        }
    }
    return;
}

void CntrApresentacaoControle::menuAutenticado(Matricula *matricula) {

    TelaMenu telaMenu;
    char opcao;

    while(true) {
        opcao = telaMenu.apresentar();

        switch(opcao) {
        case '1':
            cntrApresentacaoUsuario->executar(matricula);
            break;
        case '2':
            cntrApresentacaoProva->executar(matricula);
            break;
        case '3':
            return;
        default:
            TelaMensagem telaMensagem;
            telaMensagem.apresentar("Opcao Invalida");
        }
    }
}

bool CntrApresentacaoAutenticacao::autenticar(Matricula* matricula){

    bool resultado;
    Senha* senha = new Senha();

    while(true) {

        try {
            TelaAutenticacao telaAutenticacao;
            telaAutenticacao.apresentar(matricula, senha);
            break;
        }
        catch (const invalid_argument &exp) {
            TelaMensagem telaMensagem;
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    resultado = cntrServicoAutenticacao->autenticar(*matricula,*senha);

    return resultado;
};

void CntrApresentacaoUsuario::executar(Matricula* matricula){

    ComandoIAUsuario* comando;
    TelaMenuUsuario telaMenuUsuario;
    TelaMensagem telaMensagem;
    char opcao;
    bool notDone = true;
    while (notDone) {
        opcao = telaMenuUsuario.apresentar();

        switch(opcao){
            case '1': {
                comando = new ComandoIAUsuarioConsultar();
                comando->executar(cntrServicoUsuario,matricula);
                delete comando;
                return;
            }
            case '2': {
                comando = new ComandoIAUsuarioDescadastrar();
                comando->executar(cntrServicoUsuario,matricula);
                cadastro = false;
                delete comando;
                return;
            }
            case '3': {
                comando = new ComandoIAUsuarioEditar();
                comando->executar(cntrServicoUsuario,matricula);
                delete comando;
                return;
            }
            case '4':
                return;
            default:
                telaMensagem.apresentar("Escolha uma opcao valida");
        }
    }
};

void CntrApresentacaoUsuario::cadastrar() {

    bool resultado;
    Usuario* usuario = new Usuario();
    TelaMensagem telaMensagem;
    TelaCadastro telaCadastro;

    while(true) {

        try {
            telaCadastro.apresentar(usuario);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    resultado = cntrServicoUsuario->cadastrar(*usuario);

    if (resultado) {
        telaMensagem.apresentar("Cadastro realizado com sucesso.");
    }
    else {
        telaMensagem.apresentar("Falha no cadastro.");
    }
}

void CntrApresentacaoProva::executar(Matricula* matricula) {

    TelaMenuProva telaMenuProva;
    char opcao;
    ComandoIAProva* comando;

    while(true) {
        opcao = telaMenuProva.apresentar();

        switch(opcao) {
            case '1':
                comando = new ComandoIAProvaConsultarProva();
                comando->executar(cntrServicoProva, matricula);
                delete comando;
                break;
            case '2':
                comando = new ComandoIAProvaCadastrarProva();
                comando->executar(cntrServicoProva, matricula);
                delete comando;
                break;
            case '3':
                comando = new ComandoIAProvaConsultarQuestao();
                comando->executar(cntrServicoProva, matricula);
                delete comando;
                break;
            case '4':
                comando = new ComandoIAProvaCadastrarQuestao();
                comando->executar(cntrServicoProva, matricula);
                delete comando;
                break;
            case '5':
                return;
            default:
                TelaMensagem telaMensagem;
                telaMensagem.apresentar("Opcao invalida.");
        }
    }
}

bool CntrServicoAutenticacao::autenticar(Matricula matricula, Senha senha) {

    Usuario usuario;
    usuario.setMatricula(matricula);
    usuario.setSenha(senha);

    ContainerUsuario* container = ContainerUsuario::getInstancia();

    return container->autenticar(usuario);
}

bool CntrServicoUsuario::cadastrar(Usuario usuario) {

    ContainerUsuario* container;
    container = ContainerUsuario::getInstancia();

    return container->incluir(usuario);
}

bool CntrServicoUsuario::descadastrar(Matricula matricula) {

    ContainerUsuario* container;
    container = ContainerUsuario::getInstancia();

    return container->remover(matricula);
}

bool CntrServicoUsuario::editar(Usuario usuario) {

    ContainerUsuario* container;
    container = ContainerUsuario::getInstancia();

    return container->atualizar(usuario);
}

bool CntrServicoUsuario::consultar(Usuario* usuario) {

    ContainerUsuario* container;
    container = ContainerUsuario::getInstancia();

    return container->pesquisar(usuario);
}

bool CntrServicoProva::consultarProva(Prova* prova) {
    ComandoISProvaConsultarProva comando;
    return comando.executar(prova);
}

bool CntrServicoProva::cadastrarProva(Prova prova){
    ComandoISProvaCadastrarProva comando;
    return comando.executar(prova);
}

bool CntrServicoProva::descadastrarProva(Codigo codigo){
    ComandoISProvaDescadastrarProva comando;
    return comando.executar(codigo);
}

bool CntrServicoProva::editarProva(Prova prova){
    ComandoISProvaEditarProva comando;
    return comando.executar(prova);
}

bool CntrServicoProva::cadastrarQuestao(Questao questao){
    ComandoISProvaCadastrarQuestao comando;
    return comando.executar(questao);
}

bool CntrServicoProva::descadastrarQuestao(Codigo codigo){
    ComandoISProvaDescadastarQuestao comando;
    return comando.executar(codigo);
}

bool CntrServicoProva::editarQuestao(Questao questao){
    ComandoISProvaEditarQuestao comando;
    return comando.executar(questao);
}

bool CntrServicoProva::consultarQuestao(Questao* questao){
    ComandoISProvaConsultarQuestao comando;
    return comando.executar(questao);
}

