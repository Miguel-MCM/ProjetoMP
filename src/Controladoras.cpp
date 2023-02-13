#include "Controladoras.h"
#include "Telas.h"
#include <string>
#include <iostream>

using std::list;

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
            if(usuario->getCargo() != "admin") {
                TelaConfirmacao telaConfirmacao;
                if(telaConfirmacao.apresentar()) {
                    if(cntrServicoUsuario->descadastrar(usuario->getId()))
                        finalizou = true;
                    else
                        telaMensagem.apresentar("Erro no Processo.");
                }
            } else {
                telaMensagem.apresentar("O administrador nao pode se descadastrar.");
            }
            break;
        case '3':
            cntrApresentacaoTurma->executar(usuario);
            break;
        case '4':
            if (usuario->getCargo() == "professor")
                cntrApresentacaoTurma->cadastrar(usuario);
            else if (usuario->getCargo() == "aluno")
                cntrApresentacaoTurma->entrar(usuario);
            else
                telaMensagem.apresentar("Somente os professores podem criar turma");
            break;
        case '5':
            finalizou = true;
            break;
        default:
            telaMensagem.apresentar("Opcao Invalida.");
            break;
        }
    }
}


void CntrApresentacaoTurma::executar(Usuario* usuario) {
    string cargo = usuario->getCargo();
    string opcao

    if (cargo == "professor") {
        opcao = "2 - Cadastrar"
    } else if (cargo == "aluno") {
        opcao = "2 - Entrar"
    } else {
        opcao = "2 - Descadastrar"
    }

    string titulo = "Menu de Turmas!";
    vector<string> campos({
        "1 - Turmas", 
        opcao, 
        "3 - Provas",
        "4 - Editar",
        "5 - Alunos",
    });
    TelaMenu telaMenu;
    string opcaoMenu;

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

void CntrApresentacaoControle::executar() {
    string titulo1 = "Aprenda comigo!";
    vector<string> campos1({"1 - Login", "2 - Cadastrar", "3 - Fechar programa"});
    TelaMenu telaControle;
    string opcaoControle;

    string titulo2 = "Tela Menu";
    vector<string> campos2({"1 - Meu Usuario", "2 - Turmas", "3 - Sair"});
    TelaMenu telaMenu;
    string opcaoMenu;

    string titulo3 = "Tela Menu";
    vector<string> campos3({"1 - Meu Usuario", "2 - Administracao", "3 - Sair"});
    TelaMenu telaMenuAdmin;
    string opcaoMenuAdmin;

    TelaMensagem telaMensagem;

    while (true) {
        opcaoControle = telaControle.apresentar(titulo1, campos1);

        if (opcaoControle == "1") {
            if (cntrApresentacaoAutenticacao->autenticar(&usuario)) {
                cntrApresentacaoUsuario->setStatusCadastro(true);
                if (usuario.getCargo() != "admin") {
                    while (cntrApresentacaoUsuario->getStatusCadastro()) {
                        opcaoMenu = telaMenu.apresentar(titulo2, campos2);
                        if (opcaoMenu == "1") {
                            cntrApresentacaoUsuario->executar(&usuario);
                        } else if (opcaoMenu == "2") {
                            cntrApresentacaoTurma->executar(&usuario);
                        } else if (opcaoMenu == "3") {
                            break;
                        } else {
                            telaMensagem.apresentar("Dado em formato incorreto");
                        }
                    }
                } else {
                    while (cntrApresentacaoUsuario->getStatusCadastro()) {
                        opcaoMenuAdmin = telaMenuAdmin.apresentar(titulo3, campos3);
                        if (opcaoMenuAdmin == "1") {
                            cntrApresentacaoUsuario->executar(&usuario);
                        } else if (opcaoMenuAdmin == "2") {
                            cntrApresentacaoAdmin->executar(&usuario);
                        } else if (opcaoMenuAdmin == "3") {
                            break;
                        } else {
                            telaMensagem.apresentar("Dado em formato incorreto");
                        }
                    }
                }
            } else {
                telaMensagem.apresentar("Falha na autenticacao");
            }
        } else if (opcaoControle == "2") {
            cntrApresentacaoUsuario->cadastrar();
        } else if (opcaoControle == "3") {
            return;
        } else {
            telaMensagem.apresentar("Opcao invalida.");
        }
    }
    return;
}

bool CntrApresentacaoAutenticacao::autenticar(Usuario* usuario) {

    bool resultado;

    while (true) {
        try {
            TelaAutenticacao telaAutenticacao;
            telaAutenticacao.apresentar(usuario);
            break;
        }
        catch (const invalid_argument &exp) {
            TelaMensagem telaMensagem;
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    resultado = cntrServicoAutenticacao->autenticar(*usuario);

    return resultado;
}

void CntrApresentacaoUsuario::cadastrar() {
    bool resultado;
    Usuario usuario = new Usuario();
    TelaMensagem telaMensagem;
    TelaCadastro telaCadastro;
    string titulo = "Qual o seu cargo?";
    vector<string> campos({"1 - Aluno", "2 - Professor"});
    TelaMenu telaCargo;
    string cargo;

    while (true) {
        try {
            telaCadastro.apresentar(usuario);
            break;
        }
        catch (const invalid_argument &exp) {
            telaMensagem.apresentar("Dado em formato incorreto.");
        }
    }

    while (true) {
        cargo = telaCargo.apresentar(titulo, campos);
        if (cargo == "1") {
            usuario->setCargo("aluno");
        } else if (cargo == "2") {
            usuario->setCargo("professor");
        } else {
            telaMensagem.apresentar("Dado em formato incorreto");
        }
    }

    resultado = cntrServicoUsuario->cadastrar(*usuario);

    if (resultado) {
        telaMensagem.apresentar("Cadastro realizado com sucesso.");
    } else {
        telaMensagem.apresentar("Falha no cadastro.");
    }
}

void CntrApresentacaoAdmin::executar(Usuario* usuario) {
    string titulo = "Menu de administracao";
    vector<string> campos({
        "1 - Estatisticas ", 
        "2 - Gerenciar usuarios", 
        "3 - Gerenciar turmas", 
        "4 - Voltar"
    });
    TelaMenu telaMenu;
    string opcaoMenu;

    TelaMensagem telaMensagem;
    TelaMensagens telaMensagens;

    TelaBusca telaBusca;

    string *pnUsuarios;
    string *pnProvas;
    string *pnQuestoes;
    string *pnRespostas;


    while (true) {
        opcaoMenu = telaMenu.apresentar(titulo, campos);
        if (opcaoMenu == "1") {
            cntrServicoAdmin->numeroDeUsuarios(pnUsuarios);
            cntrServicoAdmin->numeroDeProvas(pnProvas);
            cntrServicoAdmin->numeroDeQuestoes(pnQuestoes);
            cntrServicoAdmin->numeroDeRespostas(pnRespostas);

            vector<string> estatisticas({
                "Numero de Usuarios: " + *pnUsuarios,
                "Numero de Provas: " + *pnProvas,
                "Numero de Questoes: " + *pnQuestoes,
                "Numero de Respostas: " + *pnRespostas,
            });
            telaMensagens.apresentar(estatisticas);
        } else if (opcaoMenu == "2") {
            string email = telaBusca.apresentar("Email");
            Usuario* usuario = new Usuario();
            usuario->setEmail(email);

            bool resultado = cntrServicoAdmin->consultarUsuario(usuario);
            if (!resultado) {
                telaMensagem.apresentar("Usuario nao encontrado.");
            } else {    
                cntrApresentacaoUsuario->executar(usuario);
            }
        } else if (opcaoMenu == "3") {
            string idTurma = telaBusca.apresentar("Id Turma");
            Turma* turma = new Turma();
            turma->setId(stoi(idTurma));

            bool resultado = cntrServicoAdmin->consultarTurma(turma);
            if (!resultado) {
                telaMensagem.apresentar("Turma nao encontrada.");
            } else {   
                list<int> intTurmaId;
                intTurmaId.insert(0, stoi(idTurma));
                usuario->setIdTurmas(intTurmaId);
                cntrApresentacaoTurma->executar(usuario);
            }
        } else if (opcaoMenu == "4") {
            return;
        } else {
            telaMensagem.apresentar("Dado em formato incorreto");
        }
    }
}

void CntrApresentacaoProva::gerenciar(Prova* prova) {
    TelaConsultaProva telaConsultaProva;
    TelaMensagem telaMensagem;
    
    int *qtdQuestoes;
    cntrServicoProva->getQtdQuestoes(*prova, qtdQuestoes);
    char opcao;

    while (true){
        opcao = telaConsultaProva.apresentar(prova, *qtdQuestoes);
        switch (opcao){
        case '1':
            try{
                cntrServicoProva->editarProva(*prova);
            }catch(invalid_argument &e){
                telaMensagem.apresentar("Formato de dado invalido.");
            }
            break;
        case '2':
            cntrServicoProva->descadastrarProva(prova->getId());
            telaMensagem.apresentar("Prova arquivada.");
            break;
        default:
            break;
        }
    }
    
}

bool CntrServicoAutenticacao::autenticar(Usuario usuario) {
    ContainerUsuario* container = ContainerUsuario::getInstancia();

    return container->autenticar(usuario);
}


/*

void CntrApresentacaoProva::executar(Matricula* matricula) {

void CntrApresentacaoProva::executar(Turma* turma) {
    TelaMenuProva telaMenuProva;
    TelaMensagem telaMensagem;
    TelaOpcoesProvas telaOpcoesProvas;
    TelaCadastroProva telaCadastroProva;
    char opcao;
    list<Prova> *listaProvas = nullptr;

    while(true) {
        opcao = telaMenuProva.apresentar();

        switch(opcao) {
            case '1':
                cntrServicoTurma->listarProvas(turma->getId(), listaProvas);
                try{ 
                    int idProva = telaOpcoesProvas.apresentar(*listaProvas);
                    Prova *prova = new Prova;
                    prova->setId(idProva);
                    gerenciar(prova);
                }catch(invalid_argument &e){
                    telaMensagem.apresentar("Formato de dado invalido.");
                }
                break;
            case '2':
                Prova *prova = new Prova;
                try{
                    telaCadastroProva.apresentar(prova , turma->getId());
                    cntrServicoProva->cadastrarProva(prova);
                }catch(invalid_argument &e){
                    telaMensagem.apresentar("Formato de dado invalido.");
                }
                break;
            case '3':

                break;
            case '4':

                break;
            case '5':
                return;
            default:
                TelaMensagem telaMensagem;
                telaMensagem.apresentar("Opcao invalida.");
        }
    }
}

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

*/

//bool CntrServicoProva::getQtdQuestoes(Prova prova, int *qtdQuestoes){
//    return false;
//}