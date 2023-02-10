#include "Controladoras.h"
#include "ComandosSQL.h"
#include "Telas.h"
#include <string>
#include <iostream>

using std::list;

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
    Usuario* usuario = new Usuario();
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

void CntrApresentacaoUsuario::executar(Usuario* usuario) {
    
    TelaMensagem telaMensagem;
    TelaConsultaUsuario telaConsultaUsuario;

    bool finalizou = false;
    while(!finalizou) {
        if (!cntrServicoUsuario->consultar(usuario)) {
            telaMensagem.apresentar("Houve um erro na consulta do usuario");
            break;
        }
        switch (telaConsultaUsuario.apresentar(usuario)) {
        case '1':
            try {
                editar(usuario);
            } catch (invalid_argument &e) {
                telaMensagem.apresentar("Formato de dado invalido.");
            }
            break;
        case '2':
            if(usuario->getCargo() != "admin") {
                TelaConfirmacao telaConfirmacao;
                if(telaConfirmacao.apresentar()) {
                    if(cntrServicoUsuario->descadastrar(usuario->getId())) {
                        setStatusCadastro(false);
                        finalizou = true;
                    } else {
                        telaMensagem.apresentar("Erro no Processo.");
                    }
                }
            } else {
                telaMensagem.apresentar("O administrador nao pode se descadastrar.");
            }
            break;
        case '3':
            cntrApresentacaoTurma->executar(usuario);
            break;
        case '4':
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

        if (!cntrServicoUsuario->editar(*usuario)) {
            telaMensagem.apresentar("Houve um erro na edicao do usuario");
        }
    }
    catch (invalid_argument &e) {
        telaMensagem.apresentar("Dado em Formato Incorreto.");

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

    string nUsuarios = "Erro";
    string nProvas = "Erro";
    string nQuestoes = "Erro";
    string nRespostas = "Erro";


    while (true) {
        opcaoMenu = telaMenu.apresentar(titulo, campos);
        if (opcaoMenu == "1") {
            cntrServicoAdmin->numeroDeUsuarios(&nUsuarios);
            cntrServicoAdmin->numeroDeProvas(&nProvas);
            cntrServicoAdmin->numeroDeQuestoes(&nQuestoes);
            cntrServicoAdmin->numeroDeRespostas(&nRespostas);

            vector<string> estatisticas({
                "Numero de Usuarios: " + nUsuarios,
                "Numero de Provas: " + nProvas,
                "Numero de Questoes: " + nQuestoes,
                "Numero de Respostas: " + nRespostas,
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
            string idTurma = telaBusca.apresentar("Id da Turma");
            Turma* turma = new Turma();
            turma->setId(stoi(idTurma));

            bool resultado = cntrServicoTurma->consultar(turma);
            if (!resultado) {
                telaMensagem.apresentar("Turma nao encontrada.");
            } else {   
                list<int> intTurmaId({stoi(idTurma)});
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

void CntrApresentacaoProva::executar(Turma* turma, Usuario usuario) {
    TelaMenuProva telaMenuProva;
    TelaMensagem telaMensagem;
    TelaOpcoesProvas telaOpcoesProvas;
    TelaFormulario telaFormulario;
    TelaInfoProvas telaInfoProva;
    vector<string> pedido({"Digite o id da prova: "});
    string * id;
    int idProva;
    Prova * prova;
    char opcao;
    list<Prova> *listaProvas;

    while(true) {
        opcao = telaMenuProva.apresentar(usuario.getCargo());

        switch(opcao) {
            case '1': {                                                               //Consulta servico de provas
                
                if (!cntrServicoTurma->listarProvas(turma->getId(), listaProvas)) {
                    telaMensagem.apresentar("Houve um erro ao listar as provas da turma");
                    continue;
                }
                if (usuario.getCargo() == "professor") {
                    try { 
                        idProva = telaOpcoesProvas.apresentar(*listaProvas);
                        } catch(invalid_argument &e){
                            telaMensagem.apresentar("Formato de dado invalido.");
                        }
                        prova = new Prova;
                        prova->setId(idProva);

                        gerenciar(prova);
                } else {
                    telaInfoProva.apresentar(*listaProvas);
                }
                break;
            }
            case '2': {                                                               //Cadastrar provas
                if (usuario.getCargo() == "aluno") {
                    telaFormulario.apresentar("Selecionar prova", pedido, id);
                    prova->setId(stoi(*id));
                    if (!cntrServicoProva->consultarProva(prova)) {
                        telaMensagem.apresentar("Prova nao encontrada.");
                        continue;
                    }
                    consultar(prova, turma, usuario);
                }
                break;
            }
            case '3':
                return;
            default:
                TelaMensagem telaMensagem;
                telaMensagem.apresentar("Opcao invalida.");
        }
    }
}

void CntrApresentacaoProva::consultar(Prova* prova, Turma* turma, Usuario usuario) {
    string opcao;
    TelaMenu telaMenu;
    TelaMensagem telaMensagem;
    TelaRealizarProva telaRealizarProva;
    TelaMostrarResultados telaMostrarResultados;
    vector<string> opcoes({
        "1 - Realizar prova",
        "2 - Ver resultado"
    });

    while (true) {
        opcao = telaMenu.apresentar("Menu de consulta", opcoes);
        list<Questao> * questoes;

        switch(opcao.c_str()[0]) {
            case '1': {
                Resposta resposta;
                resposta.setIdProva(prova->getId());
                resposta.setIdEstudante(usuario.getId());
                if (cntrServicoProva->consultarResposta(&resposta)) {
                    telaMensagem.apresentar("Voce ja realizou essa prova.");
                    continue;
                }
                if (!cntrServicoProva->getListaQuestoes(prova->getIdQuestoes(), questoes)) {
                    telaMensagem.apresentar("A prova nao tem questoes.");
                    continue;
                }
                resposta = telaRealizarProva.apresentar(*questoes);
                if (!cntrServicoProva->cadastrarResposta(resposta)) {
                    telaMensagem.apresentar("Houve um erro ao cadastrar a resposta, tente novamente.");
                }
                break;
            }
            case '2': {
                Resposta resposta;
                list<int> * notas;
                resposta.setIdProva(prova->getId());
                resposta.setIdEstudante(usuario.getId());
                
                if (!cntrServicoProva->consultarResposta(&resposta)) {
                    telaMensagem.apresentar("Voce nao realizou essa prova.");
                    continue;
                }
                if (!cntrServicoProva->calcularResultado(resposta, notas)) {
                    telaMensagem.apresentar("Nao foi possivel calcular o resultado, tente novamente mais tarde");
                    continue;
                }
                list<Questao> * questoes;
                if (!cntrServicoProva->getListaQuestoes(prova->getIdQuestoes(), questoes)) {
                    telaMensagem.apresentar("Houve um erro ao obter as questoes.");
                    continue;
                }
                telaMostrarResultados.apresentar(*questoes, *notas);
                break;
            }
            default:
                telaMensagem.apresentar("Opcao invalida.");
        }
    }
}

void CntrApresentacaoTurma::executar(Usuario* usuario) {
    string cargo = usuario->getCargo();
    string opcao;

    if (cargo == "professor") {
        opcao = "2 - Cadastrar Turma";
    } else if (cargo == "aluno") {
        opcao = "2 - Entrar em Turma";
    } else {
        opcao = "2 - Descadastrar Turma";
    }

    string titulo = "Menu de Turmas!";
    vector<string> campos({
        "1 -  Minhas Turmas", 
        opcao, 
        "3 - Todas as Turmas",
        "4 - Voltar" 
    });
  

    TelaMenu telaMenu;
    TelaConsultarTurmas telaTurmas;
    TelaFormulario telaFormulario;
    TelaMensagem telaMensagem;
    TelaBusca telaBusca;
    TelaMensagens telaMensagens;

    string opcaoMenu;
    string opcaoMenu2;

    bool finalizou = false;
    while(!finalizou) {
        opcaoMenu = telaMenu.apresentar(titulo, campos);
        if (opcaoMenu == "1") {
            list<Turma> *turmas;
            if (cntrServicoUsuario->listarTurmas(usuario->getId(), turmas)) {
                string turmaEscolhida = telaTurmas.apresentar(*turmas);
                Turma* turma = new Turma();
                turma->setId(stoi(turmaEscolhida));

                if (!cntrServicoTurma->consultar(turma)) {
                    telaMensagem.apresentar("Houve um erro ao consultar a turma");
                    continue;
                }
                Usuario* professor = new Usuario();
                professor->setId(turma->getIdProf());
                if (!cntrServicoUsuario->consultar(professor)) {
                    telaMensagem.apresentar("Houve um erro ao consultar o professor");
                    continue;
                }

                string status;
                if (turma->taAberta())
                    status = "Aberta";
                else
                    status = "Fechada";

                vector<string> dados({
                    "Nome: " + turma->getNome(),
                    "Professor: " + professor->getNome(),
                    "Descricao: " + turma->getDescricao(),
                    "Status: " + status,
                    "",
                    "1 - Consultar Provas",
                    "2 - Voltar"
                });
                opcaoMenu2 = telaMenu.apresentar("Turma: " + to_string(turma->getId()), dados);
                if (opcaoMenu2 == "1"){
                    cntrApresentacaoProva->executar(turma, *usuario);
                } else if (opcaoMenu2 == "2"){
                } else {
                    telaMensagem.apresentar("Opcao invalida.");
                }
            } else {
                telaMensagem.apresentar("Voce nao possui turmas.");
            }
        } else if (opcaoMenu == "2") {
            if (cargo == "professor") {
                vector<string> CAMPOS({
                    "Nome: ",
                    "Descricao: ",
                    "Aberta (s ou n): "
                });
                string * entradas;
                telaFormulario.apresentar("Cadastro de turma", CAMPOS, entradas);
                Turma turma;
                turma.setIdProf(usuario->getId());
                turma.setNome(entradas[0]);
                turma.setDescricao(entradas[1]);
                if ("s" == entradas[2]) 
                    turma.setAberta(true);
                else
                    turma.setAberta(false);
                if (cntrServicoTurma->cadastrar(turma))
                    telaMensagem.apresentar("Cadastro realizado com sucesso!");
                else
                    telaMensagem.apresentar("Nao foi possivel realizar o cadastro.");
            } else if (cargo == "aluno") {
                string id = telaBusca.apresentar("Id da turma");
                Turma turma;
                turma.setId(stoi(id));
                if (!cntrServicoTurma->entrar(turma)) {
                    telaMensagem.apresentar("Falha ao entrar na turma.");
                }
            } else {
                string id = telaBusca.apresentar("Id da turma");
                if (!cntrServicoTurma->descadastrar(stoi(id))) {
                    telaMensagem.apresentar("Falha ao descadastrar a turma.");
                }
            }
        } else if (opcaoMenu == "3") {
            list<Turma> * turmas;
            if (!cntrServicoTurma->listarAbertas(turmas)) {
                telaMensagem.apresentar("Nenhuma turma foi encontrada");
            } else {
                string _ = telaTurmas.apresentar(*turmas);
            }
        } else if (opcaoMenu == "4") {
            finalizou = true;
        } else {
            telaMensagem.apresentar("Opcao invalida.");
        }
    }
}

void CntrApresentacaoProva::gerenciar(Prova* prova){
    TelaConsultaProva telaConsultaProva;
    TelaMensagem telaMensagem;
    TelaConsultaQuestao telaConsultaQuestao;
    list<Questao> *listaQuestao;
    
    int *qtdQuestoes;

    char opcao;

    while (true){
        if (!cntrServicoProva->getQtdQuestoes(*prova, qtdQuestoes)) {
            telaMensagem.apresentar("Houve um erro ao consultar a turma");
            break;
        }
        opcao = telaConsultaProva.apresentar(prova);
        switch (opcao){
            case '1':
                editar(prova);                             
                break;
            case '2':
                if (!cntrServicoProva->descadastrarProva(prova->getId())) {   //não implementado
                    telaMensagem.apresentar("Houve um erro ao descadastrar a turma");
                    continue;
                }
                telaMensagem.apresentar("Prova arquivada.");
                break;
            case '3':
                if (!cntrServicoProva->getListaQuestoes(prova->getIdQuestoes(), listaQuestao)) {
                    telaMensagem.apresentar("Houve um erro ao obter a lista de questoes da prova");
                    continue;
                }
                telaConsultaQuestao.apresentar(*listaQuestao);
                break;
            case '4':
                return;
            default:
                telaMensagem.apresentar("Dado Invalido");
        }
    }   
}

void CntrApresentacaoProva::editar(Prova* prova){
    TelaEdicaoProva telaEdicaoProva;
    TelaMensagem telaMensagem;
    TelaDefinicaoTipoQuestao telaDefinicaoTipoQuestao;
    TelaCadastroQuestao telaCadastroQuestao;
    TelaOpcoesQuestoes telaOpcoesQuestoes;
    list<Questao> *listaQuestao;
    bool finalizou = false;

    char opcao1, opcao2;
    try{
        while(true){
            opcao1 = telaEdicaoProva.apresentar(prova);
            if (!cntrServicoProva->editarProva(*prova)) {
                telaMensagem.apresentar("Nao foi possivel editar a prova, tente novamente");
                break;
            }
            switch (opcao1){
                case '1': {
                    while(!finalizou){    
                        Questao *questao = new Questao;
                        questao->setIdProf(prova->getIdProf());
                        opcao2 = telaDefinicaoTipoQuestao.apresentar();
                        switch (opcao2){
                            case '1': {
                                telaCadastroQuestao.apresentarCriarMultiplaEscolha(questao);
                                if (!cntrServicoProva->cadastrarQuestao(*questao)) {
                                    telaMensagem.apresentar("Houve um erro ao cadastrar a questao.");
                                    continue;
                                }
                                finalizou = true;
                                break;
                            }
                            case '2': {
                                telaCadastroQuestao.apresentarCriarCertoErrado(questao);
                                if (!cntrServicoProva->cadastrarQuestao(*questao)) {
                                    telaMensagem.apresentar("Houve um erro ao cadastrar a questao.");
                                    continue;
                                }
                                finalizou = true;
                                break;
                            }
                            case '3': {
                                telaCadastroQuestao.apresentarCriarNumerico(questao);
                                if (!cntrServicoProva->cadastrarQuestao(*questao)) {
                                    telaMensagem.apresentar("Houve um erro ao cadastrar a questao.");
                                    continue;
                                }
                                finalizou = true;
                                break;
                            }
                            default:
                                telaMensagem.apresentar("Opcao Invalida.");
                        }
                    }
                    break;
                }
                case '2': {
                    if (!cntrServicoProva->getListaQuestoes(prova->getIdQuestoes(), listaQuestao)) {
                        telaMensagem.apresentar("Houve um erro ao obter a lista das questoes");
                        continue;
                    }
                    int idQuestao = telaOpcoesQuestoes.apresentar(*listaQuestao);
                    if (!cntrServicoProva->descadastrarQuestao(idQuestao)) {
                        telaMensagem.apresentar("Houve um erro ao descadastrar a questao");
                        continue;
                    }
                    return;
                }
                case '3': {
                    return;
                }
                default:
                    telaMensagem.apresentar("Opcao Invalida.");
            }
        }
    }catch(invalid_argument &e){
        telaMensagem.apresentar("Formato de dado invalido.");
    }
}

// bool CntrServicoAutenticacao::autenticar(Usuario usuario) {
//     ContainerUsuario* container = ContainerUsuario::getInstancia();
// }


/*

void CntrApresentacaoProva::executar(Matricula* matricula) {


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

