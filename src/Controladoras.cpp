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

    if (!cntrServicoUsuario->editar(*usuario)) {
        telaMensagem.apresentar("Houve um erro na edicao do usuario");
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
                list<Turma> turmas;
                if (cargo == "aluno") {
                    if (!cntrServicoUsuario->listarTurmasAluno(usuario->getId(), &turmas)) {
                        telaMensagem.apresentar("Nao foi possivel listar suas turmas");
                    }
                } else if (cargo == "professor") {
                    if (!cntrServicoUsuario->listarTurmasProfessor(usuario->getId(), &turmas)) {
                        telaMensagem.apresentar("Nao foi possivel listar suas turmas");
                    }
                } else {
                    telaMensagem.apresentar("Voce nao possui turmas");
                }
                string turmaEscolhida = telaTurmas.apresentar(turmas);
                Turma* turma = new Turma();
                if (stoi(turmaEscolhida) == 0)
                    break;
                turma->setId(stoi(turmaEscolhida));
                if (!cntrServicoTurma->consultar(turma)) {
                    telaMensagem.apresentar("Turma nao encontrada");
                    continue;
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
                    cntrApresentacaoProva->executar(turma, *usuario);
                } else if (opcaoMenu2 == "2" && cargo != "aluno") {
                    editar(turma);
                } else if ((opcaoMenu2 == "2" && cargo == "aluno") || (opcaoMenu2 == "3")) {
                    break;
                } else {
                    telaMensagem.apresentar("Opcao invalida.");
                }
                delete turma;
                delete professor;
            }
        } else if (opcaoMenu == "2") {
            if (cargo == "professor") {
                vector<string> CAMPOS({
                    "Nome: ",
                    "Descricao: ",
                    "Aberta (s ou n): "
                });
                string entradas[3];
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
            list<Turma> turmas;
            if (!cntrServicoTurma->listarTurmas(&turmas)) {
                telaMensagem.apresentar("Nenhuma turma foi encontrada");
            } else {
                string _ = telaTurmas.apresentar(turmas);
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
    ComandoEntrarNaTurma cmdEntrar(idTurma, idUsuario);

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

void CntrApresentacaoProva::executar(Turma* turma, Usuario usuario) {
    TelaMenuProva telaMenuProva;
    TelaMensagem telaMensagem;
    TelaOpcoesProvas telaOpcoesProvas;
    TelaFormulario telaFormulario;
    TelaInfoProvas telaInfoProva;
    TelaCadastroProva telaCadastroProva;
    vector<string> pedido({"Digite o id da prova: "});
    string * id;
    int idProva;
    Prova prova;
    char opcao;
    list<Prova> listaProvas;

    while(true) {
        opcao = telaMenuProva.apresentar(usuario.getCargo());

        switch(opcao) {
            case '1': {                                                               //Consulta servico de provas
                
                if (!cntrServicoTurma->listarProvas(turma->getId(), &listaProvas)) {
                    telaMensagem.apresentar("Houve um erro ao listar as provas da turma");
                    continue;
                }
                if (usuario.getCargo() == "professor") {
                    try { 
                        idProva = telaOpcoesProvas.apresentar(listaProvas);
                        } catch(invalid_argument &e){
                            telaMensagem.apresentar("Formato de dado invalido.");
                        }
                        prova.setId(idProva);

                        gerenciar(&prova);
                } else {
                    telaInfoProva.apresentar(listaProvas);
                }
                break;
            }
            case '2': {                                                               //Cadastrar provas
                if (usuario.getCargo() == "aluno") {
                    telaFormulario.apresentar("Selecionar prova", pedido, id);
                    prova.setId(stoi(*id));
                    if (!cntrServicoProva->consultarProva(&prova)) {
                        telaMensagem.apresentar("Prova nao encontrada.");
                        continue;
                    }
                    consultar(&prova, turma, usuario);
                }else if (usuario.getCargo() == "professor") {
                    try{
                        telaCadastroProva.apresentar(prova, turma->getId());
                    }catch((invalid_argument &e)){
                        telaMensagem.apresentar("Formato de dado invalido.");
                    }
                    if (!cntrServicoProva->cadastrarProva(prova)){
                        telaMensagem.apresentar("Nao foi possivel cadastrar prova.");
                        continue;
                    }
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
                if (cntrServicoProva->consultarResposta(&resposta)) {               //retorna true se resposta ja existir, buscar no banco se ja existe resposta com mesmo id de prova e aluno
                    telaMensagem.apresentar("Voce ja realizou essa prova.");
                    continue;
                }
                if (!cntrServicoProva->getListaQuestoes(prova->getId(), questoes)) {  //retorna true se possivel assinar lista de questões à "questoes"
                    telaMensagem.apresentar("A prova nao tem questoes.");
                    continue;
                }
                resposta = telaRealizarProva.apresentar(*questoes);
                if (!cntrServicoProva->cadastrarResposta(resposta)) { //Retorna true se a resposta for cadastrada
                    telaMensagem.apresentar("Houve um erro ao cadastrar a resposta, tente novamente.");
                }
                break;
            }
            case '2': {
                Resposta resposta;
                list<int> * notas;
                resposta.setIdProva(prova->getId());
                resposta.setIdEstudante(usuario.getId());
                
                if (!cntrServicoProva->consultarResposta(&resposta)) {  //retorna true se resposta ja existir, buscar no banco se ja existe resposta com mesmo id de prova e aluno
                    telaMensagem.apresentar("Voce nao realizou essa prova.");
                    continue;
                }
                if (!cntrServicoProva->calcularResultado(resposta, notas)) {  //Transforma objeto notas, designando lista de inteiros, com 1 para resposta correta e 0 para resposta errada
                    telaMensagem.apresentar("Nao foi possivel calcular o resultado, tente novamente mais tarde");
                    continue;
                }
                list<Questao> * questoes;
                if (!cntrServicoProva->getListaQuestoes(prova->getId(), questoes)) {  //retorna true se possivel assinar lista de questões à "questoes"
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

void CntrApresentacaoProva::gerenciar(Prova* prova){
    TelaConsultaProva telaConsultaProva;
    TelaMensagem telaMensagem;
    TelaConsultaQuestao telaConsultaQuestao;
    list<Questao> *listaQuestao;
    TelaMostrarResultadosProva telaMostrarResultadosProva;

    int *qtdQuestoes;

    char opcao;

    while (true){
        if (!cntrServicoProva->getQtdQuestoes(*prova, qtdQuestoes)) {  //Pegar a quantidade de questoes
            telaMensagem.apresentar("Houve um erro ao consultar a turma");
            break;
        }
        opcao = telaConsultaProva.apresentar(prova);
        switch (opcao){
            case '1':
                editar(prova);
                break;
            case '2':
                if (!cntrServicoProva->descadastrarProva(prova->getId())) {   //descadastra a prova amem
                    telaMensagem.apresentar("Houve um erro ao descadastrar a turma");
                    continue;
                }
                telaMensagem.apresentar("Prova arquivada.");
                break;
            case '3':
                if (!cntrServicoProva->getListaQuestoes(prova->getId(), listaQuestao)) {
                    telaMensagem.apresentar("Houve um erro ao obter a lista de questoes da prova");
                    continue;
                }
                telaConsultaQuestao.apresentar(*listaQuestao);
                break;
            case '4': {
                list<int> * notas;
                list<Usuario> * usuarios;
                if (!cntrServicoProva->getListaRespostaAlunos(*prova, usuarios, notas)) {   //
                    telaMensagem.apresentar("Houve um erro ao obter os alunos que realizaram a prova.");
                    continue;
                }
                telaMostrarResultadosProva.apresentar(*prova, *usuarios, *notas);
                break;
            }
            case '5':
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
            if (!cntrServicoProva->editarProva(*prova)) {   //Edita prova
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
                                if (!cntrServicoProva->cadastrarQuestao(*questao)) {                 //Cadastra questao
                                    telaMensagem.apresentar("Houve um erro ao cadastrar a questao.");
                                    continue;
                                }
                                finalizou = true;
                                break;
                            }
                            case '2': {
                                telaCadastroQuestao.apresentarCriarCertoErrado(questao);
                                if (!cntrServicoProva->cadastrarQuestao(*questao)) {                //Cadastra questao
                                    telaMensagem.apresentar("Houve um erro ao cadastrar a questao.");
                                    continue;
                                }
                                finalizou = true;
                                break;
                            }
                            case '3': {
                                telaCadastroQuestao.apresentarCriarNumerico(questao);
                                if (!cntrServicoProva->cadastrarQuestao(*questao)) {              //Cadastra questao
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
                    if (!cntrServicoProva->getListaQuestoes(prova->getId(), listaQuestao)) {     
                        telaMensagem.apresentar("Houve um erro ao obter a lista das questoes");
                        continue;
                    }
                    int idQuestao = telaOpcoesQuestoes.apresentar(*listaQuestao);
                    if (!cntrServicoProva->descadastrarQuestao(idQuestao)) {                             //Descadastra questao
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
    } catch(invalid_argument &e){
        telaMensagem.apresentar("Formato de dado invalido.");
    }
}

bool CntrServicoProva::cadastrarProva(Prova prova){
    TelaMensagem telaMensagem;
    CadastrarProva cadastrarProva;
    int consulta;

    try {
        consulta = cadastrarProva.cadastrar(prova);
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoProva::consultarProva(Prova* prova){
    TelaMensagem telaMensagem;
    ComandoConsultarProva cmdConsultar(prova->getId());
    Prova consulta;

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

    *prova = consulta;

    return true;
}

//retorna true se resposta ja existir, buscar no banco se ja existe resposta com mesmo id de prova e aluno
bool CntrServicoProva::consultarResposta(Resposta* resposta){
    TelaMensagem telaMensagem;
    ComandoBuscarRespostaAluno cmdBuscar(resposta->getIdProva(), resposta->getIdEstudante());

    cmdBuscar.executar();
    if(cmdBuscar.getResultado()){
        return false;
    }
    return true;
}

//retorna true se possivel assinar lista de questões à "questoes"
bool CntrServicoProva::getListaQuestoes(int idProva, list<Questao>* listaQuestoes){
    TelaMensagem telaMensagem;
    ListarQuestoesProva listarQuestoes;

    try {
        listaQuestoes = listarQuestoes.executar(idProva);
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;    
}

bool CntrServicoProva::cadastrarResposta(Resposta resposta){
    TelaMensagem telaMensagem;    
    CadastrarResposta cadastrarResposta;
    int consulta;

    try {
        consulta = cadastrarResposta.cadastrar(resposta);
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoProva::calcularResultado(Resposta resposta, list<int>* notas){  //map int->idQuestao int->resposta dada
    TelaMensagem telaMensagem;    
    Questao questaoAcessada;
    ComandoConsultarQuestao *cmdConsultarQuestao;

    try{
        for (const auto& [key, value] : resposta.getResposta()){
            cmdConsultarQuestao = new ComandoConsultarQuestao(key);
            cmdConsultarQuestao->executar();
            questaoAcessada = cmdConsultarQuestao->getResultado();

            if(questaoAcessada.getRespostaCorreta() == value){
                notas->push_back(1);
            }else{
                notas->push_back(0);
            }
            delete cmdConsultarQuestao;
        }
    }catch (const EErroPersistencia &exp) {
        return false;
    }
    return true;
}

bool CntrServicoProva::getQtdQuestoes(Prova prova, int* qtdQuestoes){
    TelaMensagem telaMensagem;
    list<Questao> *listaQuestoes;
    getListaQuestoes(prova.getId(), listaQuestoes);

    qtdQuestoes = listaQuestoes->size();
    return true;
}

bool CntrServicoProva::descadastrarProva(int idProva){
    TelaMensagem telaMensagem;
    ComandoDescadastrarProva cmdDescadastrar(id);

    try {
        cmdDescadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoProva::getListaRespostaAlunos(Prova prova, list<Usuario>* listaAlunos, list<int>* notas){
    ListarAlunosTurma listarAlunosTurma;
    Resposta resposta;

    int somaNotas;
    listaAlunos = listarAlunosTurma.executar(prova.getIdTurma());

    for(list<Usuario>::iterator it=listaAlunos->begin(); it!=listaAlunos.end(); ++it){
        try{
            ComandoConsultarResposta comandoConsultarResposta(it->getId(), prova.getId());
        }catch(const EErroPersistencia &exp){
            return false;
        }
        list<int> *notaIndividual;

        comandoConsultarResposta.executar();
        try{
            resposta = comandoConsultarResposta.getResultado();
            calcularResultado(resultado, notaIndividual);
            notas->push_back(std::accumulate(notaIndividual.begin(), notaIndividual.end(), 0));
        }catch(const EErroPersistencia &exp){
            notas->push_back(0);
        }
        delete notaIndividual;
    }
    return true;
}

bool CntrServicoProva::editarProva(Prova prova){
    TelaMensagem telaMensagem;
    ComandoEditarProva cmdEditar(*prova);

    try {
        cmdEditar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoProva::cadastrarQuestao(Questao questao){
    TelaMensagem telaMensagem;
    CadastrarQuestao cadastrarQuestao;
    int consulta;

    try {
        consulta = cadastrarQuestao.cadastrar(questao);
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}

bool CntrServicoProva::descadastrarQuestao(int id){
    TelaMensagem telaMensagem;
    ComandoDescadastrarQuestao cmdDescadastrar(id);

    try {
        cmdDescadastrar.executar();
    } catch (const EErroPersistencia &exp) {
        return false;
    }

    return true;
}



