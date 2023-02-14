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
            return false;
        }
    }

    resultado = cntrServicoAutenticacao->autenticar(usuario);

    return resultado;
}

bool CntrServicoAutenticacao::autenticar(Usuario *usuario) {
    TelaMensagem telaMensagem;
    ComandoConsultarUsuario cmdConsultar(usuario->getEmail());
    
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

    if (consulta.getSenha() == usuario->getSenha()) {
        *usuario = consulta;
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
    
    if(novosDados[0] != "")
        usuario->setNome(novosDados[0]);

    if(novosDados[1] != "")
        usuario->setEmail(novosDados[1]);

    if(novosDados[2] != "")
        usuario->setSenha(novosDados[2]);

    if (cntrServicoUsuario->editar(*usuario)) {
        telaMensagem.apresentar("Dado em Formato Incorreto.");
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
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoUsuario::descadastrar(int id, string cargo) {
    TelaMensagem telaMensagem;
    ComandoDescadastrarUsuario cmdDescadastrar(id, cargo);

    try {
        cmdDescadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoUsuario::editar(Usuario usuario) {
    TelaMensagem telaMensagem;
    ComandoEditarUsuario cmdEditar(usuario);

    try {
        cmdEditar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoUsuario::listarTurmasAluno(int idAluno, list<Turma> *turmas) {
    TelaMensagem telaMensagem;
    ListarTurmasAluno cmdListarTurmas;

    list<Turma> consulta;

    try {
        consulta = cmdListarTurmas.executar(idAluno);
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    *turmas = consulta;

    return true;
}

bool CntrServicoUsuario::listarTurmasProfessor(int idProfessor, list<Turma> *turmas) {
    TelaMensagem telaMensagem;
    ComandoListarIdTurmasProfessor cmdListarProfessor(idProfessor);

    list<Turma> consulta;

    try {
        cmdListarProfessor.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        consulta = cmdListarProfessor.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    *turmas = consulta;

    return true;
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
            while (true) {
                list<Turma> *turmas;
                if (cargo == "aluno") {
                    if (!cntrServicoUsuario->listarTurmasAluno(usuario->getId(), turmas)) {
                        telaMensagem.apresentar("Nao foi possivel listar suas turmas");
                    }
                } else if (cargo == "professor") {
                    if (!cntrServicoUsuario->listarTurmasProfessor(usuario->getId(), turmas)) {
                        telaMensagem.apresentar("Nao foi possivel listar suas turmas");
                    }
                } else {
                    telaMensagem.apresentar("Voce nao possui turmas");
                }
                string turmaEscolhida = telaTurmas.apresentar(*turmas);
                Turma* turma = new Turma();
                turma->setId(stoi(turmaEscolhida));
                if (!cntrServicoTurma->consultar(turma)) {
                    telaMensagem.apresentar("Turma nao encontrada");
                }
                Usuario* professor = new Usuario();
                professor->setId(turma->getIdProf());
                if (!cntrServicoUsuario->consultar(professor)) {
                    telaMensagem.apresentar("Profssor nao encontrado");
                }
                string status;
                if (turma->taAberta())
                    status = "Aberta";
                else
                    status = "Fechada";

                vector<string> dados;

                if (cargo == "aluno") {
                    dados = {
                        "Nome: " + turma->getNome(),
                        "Professor: " + professor->getNome(),
                        "Descricao: " + turma->getDescricao(),
                        "Status: " + status,
                        "",
                        "1 - Consultar Provas",
                        "2 - Voltar"
                    };
                } else {
                    dados = {
                        "Nome: " + turma->getNome(),
                        "Professor: " + professor->getNome(),
                        "Descricao: " + turma->getDescricao(),
                        "Status: " + status,
                        "",
                        "1 - Consultar Provas",
                        "2 - Editar Turma",
                        "3 - Voltar"
                    };
                }
                opcaoMenu2 = telaMenu.apresentar("Turma: " + to_string(turma->getId()), dados);
                if (opcaoMenu2 == "1"){
                    cntrApresentacaoProva->executar(turma);
                } else if (opcaoMenu2 == "2" && cargo != "aluno") {
                    editar(turma);
                } else if ((opcaoMenu2 == "2" && cargo == "aluno") || (opcaoMenu2 == "3")) {
                    break;
                } else {
                    telaMensagem.apresentar("Opcao invalida.");
                }
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
                if (!cntrServicoTurma->entrar(stoi(id), usuario->getId())) {
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
            if (!cntrServicoTurma->listarTurmas(turmas)) {
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

void CntrApresentacaoTurma::editar(Turma *turma) {
    TelaMensagem telaMensagem;
    TelaFormulario telaFormulario;
    const string TITULO = "Edicao de Usuario";
    const vector<string> DADOS({
        "Nome: ",
        "Descricao: ",
        "Esta aberta (s ou n): "
    });
    string novosDados[DADOS.size()];

    telaFormulario.apresentar(TITULO, DADOS, novosDados);
    
    if(novosDados[0] != "")
        turma->setNome(novosDados[0]);

    if(novosDados[1] != "")
        turma->setDescricao(novosDados[1]);

    if(novosDados[2] != "" && (novosDados[2] == "s" || novosDados[2] == "n"))
        turma->setAberta(novosDados[2] == "s");

    if (!cntrServicoTurma->editar(turma)) {
        telaMensagem.apresentar("Dado em Formato Incorreto.");
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
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
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
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoTurma::editar(Turma *turma) {
    TelaMensagem telaMensagem;
    ComandoEditarTurma cmdEditar(*turma);

    try {
        cmdEditar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoTurma::entrar(int idUsuario, int idTurma) {
    TelaMensagem telaMensagem;
    ComandoEntrarNaTurma cmdEntrar(idUsuario, idTurma);

    try {
        cmdEntrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoTurma::listarTurmas(list<Turma> *turmas) {
    TelaMensagem telaMensagem;
    ComandoListarTurmas cmdListarTurmas;

    list<Turma> consulta;

    try {
        cmdListarTurmas.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        consulta = cmdListarTurmas.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    *turmas = consulta;

    return true;
}

bool CntrServicoTurma::listarProvas(int idTurma, list<Prova> *provas) {
    TelaMensagem telaMensagem;
    ComandoListarProvas cmdListarProvas(idTurma);

    list<Prova> consulta;

    try {
        cmdListarProvas.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        consulta = cmdListarProvas.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    *provas = consulta;

    return true;
}

bool CntrServicoTurma::listarAlunos(int idTurma, list<Usuario> *alunos) {
    TelaMensagem telaMensagem;
    ListarAlunosTurma cmdListarAlunos;

    list<Usuario> consulta;

    try {
        consulta = cmdListarAlunos.executar(idTurma);
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    *alunos = consulta;

    return true;
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

    while (true) {
        opcaoMenu = telaMenu.apresentar(titulo, campos);
        if (opcaoMenu == "1") {
            vector<string> estatisticas;
            if (!cntrServicoAdmin->estatisticas(&estatisticas)) {
                telaMensagem.apresentar("Nao foi possivel exibir as estatisticas");
            } else {
                telaMensagens.apresentar(estatisticas);
            }
        } else if (opcaoMenu == "2") {
            string email = telaBusca.apresentar("Email");
            Usuario* usuario = new Usuario();
            usuario->setEmail(email);

            bool resultado = cntrServicoUsuario->consultar(usuario);
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

bool CntrServicoAdmin::estatisticas(vector<string> *vetor) {
    TelaMensagem telaMensagem;
    ComandoCountUsuarios cmdCountUsuario;
    ComandoCountProva cmdCountProvas;
    ComandoCountQuestao cmdCountQuestoes;
    ComandoCountResposta cmdCountRespostas;
    
    int nUsuarios;
    int nProvas;
    int nQuestoes;
    int nRespostas;

    try {
        nUsuarios = cmdCountUsuario.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        nProvas = cmdCountProvas.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        nQuestoes = cmdCountQuestoes.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    try {
        nRespostas = cmdCountRespostas.getResultado();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    *vetor = {
        "Numero de Usuarios: " + to_string(nUsuarios),
        "Numero de Provas: " + to_string(nProvas),
        "Numero de Questoes: " + to_string(nQuestoes),
        "Numero de Respostas: " + to_string(nRespostas),
    };

    return true;
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
                if(cntrServicoTurma->listarProvas(turma->getId(), listaProvas)) {
                    telaMensagem.apresentar("Nao foi possivel listar as provas.");
                } else {            
                    try{ 
                        idProva = telaOpcoesProvas.apresentar(*listaProvas);
                        prova = new Prova;
                        prova->setId(idProva);
                        gerenciar(prova);
                    }catch(invalid_argument &e){
                        telaMensagem.apresentar("Formato de dado invalido.");
                    }
                    break;
                }
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

