#include "Controladoras.h"
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

bool CntrServicoAutenticacao::autenticar(Usuario usuario) {
    TelaMensagem telaMensagem;
    ComandoConsultarUsuario cmdConsultar(usuario.getEmail());
    
    Usuario consulta;
    try {
        cmdConsultar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    try {
        consulta = cmdConsultar.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    if (consulta.getSenha() == usuario.getSenha()) {
        return true;
    } 

    return false;
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
            break;
        } else if (cargo == "2") {
            usuario->setCargo("professor");
            break;
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
        if (cntrServicoUsuario->consultar(usuario)) {
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
                        if(cntrServicoUsuario->descadastrar(usuario->getId(), usuario->getCargo())) {
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
        } else {
            telaMensagem.apresentar("Nenhum usuario encontrado.");
        }
    }
}

bool CntrServicoUsuario::consultar(Usuario *usuario) {
    TelaMensagem telaMensagem;
    ComandoConsultarUsuario cmdConsultar(usuario->getId());
    
    Usuario consulta;
    try {
        cmdConsultar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    try {
        consulta = cmdConsultar.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }
    
    *usuario = consulta;

    return true;
}

bool CntrServicoUsuario::cadastrar(Usuario usuario) {
    TelaMensagem telaMensagem;
    CadastrarUsuario cmdCadastrar;
    int consulta;

    try {
        consulta = cmdCadastrar.executar(usuario);
        return true;
    } catch (const EErroPersistencia &exp) {
        return false;
    }
}

bool CntrServicoUsuario::descadastrar(int id, string cargo) {
    TelaMensagem telaMensagem;
    ComandoDescadastrarUsuario cmdDescadastrar(id, cargo);

    try {
        cmdDescadastrar.executar();
        return true;
    } catch (const EErroPersistencia &exp) {
        return false;
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

bool CntrServicoUsuario::editar(Usuario usuario) {
    TelaMensagem telaMensagem;
    ComandoEditarUsuario cmdEditar(usuario);

    try {
        cmdEditar.executar();
        return true;
    } catch (const EErroPersistencia &exp) {
        return false;
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

void CntrApresentacaoProva::executar(Turma* turma) {
    TelaMenuProva telaMenuProva;
    TelaMensagem telaMensagem;
    TelaOpcoesProvas telaOpcoesProvas;
    TelaCadastroProva telaCadastroProva;
    int idProva;
    Prova * prova;
    char opcao;
    list<Prova> *listaProvas = nullptr;

    while(true) {
        opcao = telaMenuProva.apresentar();

        switch(opcao) {
            case '1':                                                               //Consulta servico de provas
                cntrServicoTurma->listarProvas(turma->getId(), listaProvas);            
                try{ 
                    idProva = telaOpcoesProvas.apresentar(*listaProvas);
                    prova = new Prova;
                    prova->setId(idProva);
                    gerenciar(prova);
                }catch(invalid_argument &e){
                    telaMensagem.apresentar("Formato de dado invalido.");
                }
                break;
            case '2':                                                                //Cadastrar provas
                prova = new Prova;
                try{
                    prova->setIdProf(turma->getIdProf());
                    telaCadastroProva.apresentar(prova , turma->getId());
                    cntrServicoProva->cadastrarProva(*prova);
                } catch(invalid_argument &e){
                    telaMensagem.apresentar("Formato de dado invalido.");
                }
                break;
            case '3':
                return;
            default:
                TelaMensagem telaMensagem;
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
                cntrServicoTurma->consultar(turma);
                Usuario* professor = new Usuario();
                professor->setId(turma->getIdProf());
                cntrServicoUsuario->consultar(professor);

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
                    cntrApresentacaoProva->executar(turma);
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
    cntrServicoProva->getQtdQuestoes(*prova, qtdQuestoes);
    char opcao;

    while (true){
        opcao = telaConsultaProva.apresentar(prova, *qtdQuestoes);
        switch (opcao){
        case '1':
            editar(prova);                             
            break;
        case '2':
            cntrServicoProva->descadastrarProva(prova->getId());   //não implementado
            telaMensagem.apresentar("Prova arquivada.");
            break;
        case '3':
            cntrServicoProva->getListaQuestoes(prova->getIdQuestoes(), listaQuestao);
            telaConsultaQuestao.apresentar(*listaQuestao);        
            break;
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
            cntrServicoProva->editarProva(*prova);
            switch (opcao1){
                case '1': {
                    while(!finalizou){    
                        Questao *questao = new Questao;
                        questao->setIdProf(prova->getIdProf());
                        opcao2 = telaDefinicaoTipoQuestao.apresentar();
                        switch (opcao2){
                            case '1': {
                                telaCadastroQuestao.apresentarCriarMultiplaEscolha(questao);
                                cntrServicoProva->cadastrarQuestao(*questao);
                                finalizou = true;
                                break;
                            }
                            case '2': {
                                telaCadastroQuestao.apresentarCriarCertoErrado(questao);
                                cntrServicoProva->cadastrarQuestao(*questao);
                                finalizou = true;
                                break;
                            }
                            case '3': {
                                telaCadastroQuestao.apresentarCriarNumerico(questao);
                                cntrServicoProva->cadastrarQuestao(*questao);
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
                    cntrServicoProva->getListaQuestoes(prova->getIdQuestoes(), listaQuestao);
                    int idQuestao = telaOpcoesQuestoes.apresentar(*listaQuestao);
                    cntrServicoProva->descadastrarQuestao(idQuestao);
                    return;
                }
                case '3': {
                    return;
                }    
                default:
                    telaMensagem.apresentar("Opcao Invalida.");
            }
        }
    } catch(invalid_argument &e){
        telaMensagem.apresentar("Formato de dado invalido.");
    }
}


bool CntrServicoTurma::cadastrar(Turma turma) {
    TelaMensagem telaMensagem;
    ComandoCadastrarTurma cmdCadastrar(turma);
    int consulta;

    try {
        cmdCadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        consulta = cmdCadastrar.getResultado();
        return true;
    } catch (const EErroPersistencia &exp) {
        return false;
    }
}

bool CntrServicoTurma::consultar(Turma *turma) {
    TelaMensagem telaMensagem;
    ComandoConsultarTurma cmdConsultar(turma->getId());
    Turma consulta;

    try {
        cmdConsultar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        consulta = cmdConsultar.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    *turma = consulta;

    return true;
}

bool CntrServicoTurma::descadastrar(int id) {
    TelaMensagem telaMensagem;
    ComandoDescadastrarTurma cmdDescadastrar(id);

    try {
        cmdDescadastrar.executar();
        return true;
    } catch (const EErroPersistencia &exp) {
        return false;
    }
}

bool CntrServicoTurma::editar(Turma turma) {
    TelaMensagem telaMensagem;
    ComandoEditarTurma cmdEditar(turma);

    try {
        cmdEditar.executar();
        return true;
    } catch (const EErroPersistencia &exp) {
        return false;
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

