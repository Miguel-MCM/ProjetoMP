#include "Telas.h"
#include <string.h>
#include <iostream>

using std::list;
using std::vector;
using std::pair;

void Tela::mostrarLinhas(vector<string> linhas, int linha, int coluna, int p) {
    for (pair<vector<string>::iterator, int> it(linhas.begin(), p); it.first != linhas.end(); ++it.first, it.second++) {
        mvprintw(linha / 2 - 4 + (2 * it.second), (coluna - it.first->length()) / 2, "%s", it.first->c_str());
    }
}

void Tela::mostrarLinhas(vector<string> linhas, int linha, int coluna) {
    mostrarLinhas(linhas, linha, coluna, 0);
}

string TelaMenu::apresentar(string titulo, vector<string> opcoes) {
    int linha, coluna;
    char dado[20];
    string campo = "Selecione uma opcao: ";

    initscr();
    getmaxyx(stdscr, linha, coluna);
    mvprintw(linha / 2 - 6, (coluna - titulo.length()) / 2, "%s", titulo.c_str());
    mostrarLinhas(opcoes, linha, coluna);
    mvprintw(linha / 2 - 4 + 2 * (opcoes.size() + 1), (coluna - campo.length()) / 2, "%s", campo.c_str());
    getstr(dado);
    clear();
    endwin();

    return dado;
}

void TelaFormulario::apresentar(string titulo, vector<string> campos, string * entradas) {
    int linha, coluna;
    char dado[20];
    initscr();
    getmaxyx(stdscr, linha, coluna);
    mvprintw(linha / 2 - 6, (coluna - titulo.length()) / 2, "%s", titulo.c_str());
    for (pair<vector<string>::iterator, int> it(campos.begin(), 0); it.first != campos.end(); ++it.first, it.second++) {
        mvprintw(linha / 2 - 4 + (2 * it.second), (coluna - it.first->length()) / 2, "%s", it.first->c_str());
        getstr(dado);
        entradas[it.second] = dado;
    }
    clear();
    endwin();
}

void TelaMensagem::apresentar(string mensagem) {
    int linha, coluna;

    initscr();                                                                            // Iniciar curses.
    getmaxyx(stdscr, linha, coluna);                                                      // Armazenar quantidade de linhas e de colunas.
    mvprintw(linha / 2, (coluna - mensagem.length()) / 2, "%s", mensagem.c_str()); // Imprimir dado.
    noecho();                                                                             // Desabilitar eco.
    getch();                                                                              // Ler caracter digitado.
    echo();                                                                               // Habilitar eco.
    clear();
}

void TelaMensagens::apresentar(vector<string> mensagens) {
    int linha, coluna;

    initscr();                                                                          
    getmaxyx(stdscr, linha, coluna);                            
    
    mostrarLinhas(mensagens, linha, coluna);

    noecho();                                                                           
    getch();                                                                            
    echo();                                                                             
    clear();                                                                            
    endwin();
}

void TelaAutenticacao::apresentar(Usuario* usuario) {

    char campo1[]="Digite o email : ";
    char campo2[]="Digite a senha     : ";
    char dado1[80];
    char dado2[80];
    int linha, coluna;
    string senha;
    string email;

    initscr();
    getmaxyx(stdscr, linha, coluna);
    mvprintw(linha/2, (coluna-strlen(campo1))/2, "%s", campo1);
    getstr(dado1);
    mvprintw(linha/2 + 2, (coluna-strlen(campo2))/2, "%s", campo2);
    getstr(dado2);
    clear();
    endwin();

    email = dado1;
    senha = dado2;
    usuario->setEmail(dado1);
    usuario->setSenha(dado2);
}

void TelaCadastro::apresentar(Usuario *usuario) {

    char campo1[]="Digite o email : ";
    char campo2[]="Digite a senha     : ";
    char campo3[]="Digite o nome     : ";
    char dado1[80];
    char dado2[80];
    char dado3[80];
    int linha, coluna;

    initscr();
    getmaxyx(stdscr, linha, coluna);

    mvprintw(linha/3, (coluna-strlen(campo1))/2, "%s", campo1);
    getstr(dado1);
    mvprintw(linha/3 + 2, (coluna-strlen(campo2))/2, "%s", campo2);
    getstr(dado2);
    mvprintw(linha/3 + 4, (coluna-strlen(campo3))/2, "%s", campo3);
    getstr(dado3);
    clear();
    endwin();

    string email = dado1;
    string senha = dado2;
    string nome = dado3;
    usuario->setEmail(email);
    usuario->setSenha(senha);
    usuario->setNome(nome);
}

char TelaConsultaUsuario::apresentar(Usuario* usuario) {
    const string TITULO = "Usuario";
    const vector<string> DADOS({
        "Nome: " + usuario->getNome(),
        "Email: " + usuario->getEmail(),
        "Cargo: " + usuario->getCargo()
    });

    const vector<string> OPCOES({
        "1 - Editar",
        "2 - Descadastrar",
        "3 - Voltar",
        "Selecione uma opcao: "
    });

    char dado1[10];

    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);


    mvprintw(linha/2 - 6,(coluna-TITULO.length())/2,"%s",TITULO.c_str());
    mostrarLinhas(DADOS, linha, coluna);
    mostrarLinhas(OPCOES, linha, coluna, 5);

    getstr(dado1);

    clear();
    endwin();

    return dado1[0];
}

bool TelaConfirmacao::apresentar() {

    string campo1 = "Deseja confimar o descadastramento? (S/N) ";
    char dado1[80];
    bool confirmou;
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);
    while (true) {
        mvprintw(linha/2,(coluna-campo1.length())/2,"%s",campo1.c_str());
        getstr(dado1);
        if (dado1[0] == 's' || dado1[0] == 'S') {
            confirmou = true;
            break;
        }
        if (dado1[0] == 'n' || dado1[0] == 'N') {
            confirmou = false;
            break;
        }
        clear();
    }
    clear();
    endwin();

    
    return confirmou;
}

string TelaConsultarProvas::apresentar(list<Prova> provas) {
    const string TITULO = "Provas";
    vector<string> DADOS;

    char dado1[10];

    for (list<Prova>::iterator it = provas.begin(); it != provas.end();++it) {
        DADOS.insert(DADOS.end(), "Nome: " + it->getNome());
        string id;
        id = to_string(it->getId());
        
        DADOS.insert(DADOS.end(), "ID: " + id);
    }

    DADOS.insert(DADOS.end(), "Selecione uma opcao (para voltar digite 0): ");
        
    int linha,coluna;

    initscr();

    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2 - 6,(coluna-TITULO.length())/2,"%s",TITULO.c_str());
    mostrarLinhas(DADOS, linha, coluna);

    getstr(dado1);

    clear();
    endwin();

    return dado1;
}

void TelaInfoProvas::apresentar(list<Prova> provas) {
    const string TITULO = "Provas";
    vector<string> DADOS;

    for (list<Prova>::iterator it = provas.begin(); it != provas.end();++it) {
        DADOS.insert(DADOS.end(), "Nome: " + it->getNome());
        string id;
        id = to_string(it->getId());
        
        DADOS.insert(DADOS.end(), "ID: " + id);
    }
        
    int linha,coluna;

    initscr();

    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2 - 6,(coluna-TITULO.length())/2,"%s",TITULO.c_str());
    mostrarLinhas(DADOS, linha, coluna);
    getch();
    clear();
    endwin();
}

string TelaConsultarTurmas::apresentar(list<Turma> turmas) {
    const string TITULO = "Turma";
    vector<string> DADOS;

    char dado1[10];

    for (list<Turma>::iterator it = turmas.begin(); it != turmas.end(); ++it) {
        DADOS.insert(DADOS.end(), "Nome: " + it->getNome());

        if (it->taAberta()) {        
            DADOS.insert(DADOS.end(), "Status: Aberta");
        } else {
            DADOS.insert(DADOS.end(), "Status: Fechada");
        }

        string id;
        id = to_string(it->getId());

        DADOS.insert(DADOS.end(), "ID: " + id);
    }

    DADOS.insert(DADOS.end(), "Selecione uma opcao ou digite 0 para voltar: ");
        
    int linha,coluna;

    initscr();

    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2 - 6,(coluna-TITULO.length())/2,"%s",TITULO.c_str());
    mostrarLinhas(DADOS, linha, coluna);

    getstr(dado1);

    clear();
    endwin();

    return dado1;
}

void TelaListarAlunos::apresentar(list<Usuario> alunos) {
    const string TITULO = "Alunos";
    vector<string> DADOS;

    for (list<Usuario>::iterator it = alunos.begin(); it != alunos.end();++it) {
        DADOS.insert(DADOS.end(), "Nome: " + it->getNome());
    }
    int linha,coluna;

    initscr();

    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2 - 6,(coluna-TITULO.length())/2,"%s",TITULO.c_str());
    mostrarLinhas(DADOS, linha, coluna);

    clear();
    endwin();
}

string TelaBusca::apresentar(string id) {
    string pergunta = id + ": ";
    char dado1[80];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2,(coluna-pergunta.length())/2,"%s",pergunta);
    getstr(dado1);

    clear();
    endwin();

    return dado1;
}

char TelaDefinicaoTipoQuestao::apresentar() {
    char campo1[]="Tipos de questao a ser criada : ";
    char campo2[]="1 - Questao de multipla escolha";
    char campo3[]="2 - Questao de certo ou errado";
    char campo4[]="3 - Questao de resposta numerica";
    char campo5[]="Selecine um tipo : ";

    char dado1[1];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/3 - 2,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/3,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/3 + 2,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/3 + 4,(coluna-strlen(campo4))/2,"%s",campo4);

    mvprintw(linha/4 + 12,(coluna-strlen(campo5))/2,"%s",campo5);
    getstr(dado1);

    clear();
    endwin();

    return dado1[0];
}

void TelaCadastroQuestao::apresentarCriarMultiplaEscolha(Questao* questao) {
    char campo1[]="Digite o titulo da questao : ";
    char campo2[]="Digite o texto da questao : ";
    char campo3[]="Digite numero de alternativas (limite 5) : ";
    char campo4[]="Digite numero de alternativa correta : ";

    char campo5[]="Escreva as alternativas : ";

    char dado1[80];
    char dado2[80];
    char dado3[80];
    char dado4[80];
    
    list<string> alternativas;
        
    int contador = 6;
    int numAlternativas;
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/3,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);
    mvprintw(linha/3 + 2,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado2);
    mvprintw(linha/3 + 4,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado3);
    numAlternativas = std::stoi(dado3);
    
    mvprintw(linha/3,(coluna-strlen(campo1))/2,"%s",campo5);
    for(int i = 0; i < numAlternativas; i++) {
        mvprintw(linha/3 + contador,(coluna - (std::to_string(i+1) + ": ").length())/2,"%s", std::to_string(i+1) + ": ");
        getstr(dado3);
        alternativas.push_back(dado3);

        contador += 2;
    }

    mvprintw(linha/3 + 6,(coluna-strlen(campo4))/2,"%s",campo4);
    getstr(dado4);
    
    clear();
    endwin();

    questao->setNome(dado1);
    questao->setTexto(dado2);
    questao->setAlternativas(alternativas);    
    questao->setRespostaCorreta(std::stoi(dado4));
}

void TelaCadastroQuestao::apresentarCriarCertoErrado(Questao* questao) {
    char campo1[]="Digite o titulo da questao : ";
    char campo2[]="Digite o texto da questao : ";
    char campo3[]="Digite resposta da questão (0 para errado ou 1 para certo) : ";

    char dado1[80];
    char dado2[80];
    char dado3[80];

    int resposta;

    list<string> alternativas ({"0 - errado", "1 - certo"});

    int linha, coluna;
    initscr();
    getmaxyx(stdscr,linha,coluna);
    
    mvprintw(linha/3,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);
    mvprintw(linha/3 + 2,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado2);
    mvprintw(linha/3 + 4,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado3);
    resposta = std::stoi(dado3);

    questao->setNome(dado1);
    questao->setTexto(dado2);
    questao->setAlternativas(alternativas);    
    questao->setRespostaCorreta(resposta);
}

void TelaCadastroQuestao::apresentarCriarNumerico(Questao* questao) {
    char campo1[]="Digite o titulo da questao : ";
    char campo2[]="Digite o texto da questao : ";
    char campo3[]="Digite resposta numerica da questão : ";

    char dado1[80];
    char dado2[80];
    char dado3[80];

    int resposta;

    list<string> alternativas;

    int linha, coluna;
    initscr();
    getmaxyx(stdscr,linha,coluna);
    
    mvprintw(linha/3,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);
    mvprintw(linha/3 + 2,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado2);
    mvprintw(linha/3 + 4,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado3);
    resposta = std::stoi(dado3);

    questao->setNome(dado1);
    questao->setTexto(dado2);
    questao->setAlternativas(alternativas);    
    questao->setRespostaCorreta(resposta);
}

void TelaConsultaQuestao::apresentar(list<Questao> listaQuestao) {
    string campo1 = "Resposta correta: ";

    std::vector<Questao> vectorQuestoes(listaQuestao.begin(), listaQuestao.end());

    int linha, coluna;
    string campo;
    char dado;

    initscr();
    getmaxyx(stdscr, linha, coluna);

    for (int i = 0; i < vectorQuestoes.size(); i++) {
        mvprintw(linha / 2 - 6, (coluna - vectorQuestoes[i].getTexto().length()) / 2, "%s", vectorQuestoes[i].getTexto().c_str());
        if (vectorQuestoes[i].getAlternativas().size() != 0) {
            campo = "Escolha um numero de alternativa: ";
            for (pair<list<string>::iterator, int> it(vectorQuestoes[i].getAlternativas().begin(), 0); it.first != vectorQuestoes[i].getAlternativas().end(); ++it.first, it.second++) {
                mvprintw(linha / 2 - 4 + (2 * it.second), (coluna - it.first->length()) / 2, "%s", it.first->c_str());
            }
            mvprintw(linha / 2 - 4 + 2 * (vectorQuestoes[i].getAlternativas().size() + 1), (coluna - campo.length()) / 2, "%s", campo.c_str());
        } else {
            campo = "Digite sua resposta (apenas aperte enter para ir a proxima): ";
            mvprintw(linha / 2 - 4 + 2 * (vectorQuestoes[i].getAlternativas().size() + 1), (coluna - campo.length()) / 2, "%s", campo.c_str());        
        }

        mvprintw(linha - 3, (coluna - (campo1 + std::to_string(vectorQuestoes[i].getRespostaCorreta())).length()), (campo1 + std::to_string(vectorQuestoes[i].getRespostaCorreta())).c_str());

        getch();

        clear();
    }
    
    endwin();   
}

int TelaOpcoesQuestoes::apresentar(list<Questao> listaQuestao) {
    string campo1 = "Questao: ";
    string campo2 = "ID: ";
    char campo3[] = "Digite o ID da questao que deseja acessar: ";
    char dado1[30];
    int linha, coluna;

    initscr();
    getmaxyx(stdscr, linha, coluna);
    
    int contador = 3;
    list<Questao>::iterator it;
    for(it = listaQuestao.begin(); it != listaQuestao.end(); ++it) {
        mvprintw(linha/contador, (coluna-((campo1 + it->getNome()).length()))/2, "%s", (campo1 + it->getNome()).c_str());
        //mvprintw(linha/contador, (coluna-it->getNome().length())/1, "%s", it->getNome());
        mvprintw(linha/contador + 2, (coluna-((campo2 + std::to_string(it->getId())).length()))/2, "%s", (campo2 + std::to_string(it->getId())).c_str());
        //mvprintw(linha/contador + 2, (coluna-(std::to_string(it->getId()).length()))/1, "%s", (std::to_string(it->getId()).length()));             
        contador += 3;
    }
    
    mvprintw(linha/16,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado1);
     
    clear();
    endwin();

    int id = std::stoi(dado1);
    return id;    
}


Resposta TelaRealizarProva::apresentar(list<Questao> listaQuestao) {
    int linha, coluna;
    Resposta resposta;
    char * dado;
    string campo;
    map<int, int> respostas;
    map<int, int>::iterator it2;
    int id;

    std::vector<Questao> questoes(listaQuestao.begin(), listaQuestao.end());

    initscr();
    getmaxyx(stdscr, linha, coluna);

    for (int i = 0; i < questoes.size(); i++) {
        mvprintw(linha / 2 - 6, (coluna - questoes[i].getTexto().length()) / 2, "%s", questoes[i].getTexto().c_str());
        if (questoes[i].getAlternativas().size() != 0) {
            campo = "Escolha um numero de alternativa: ";
            for (pair<list<string>::iterator, int> it(questoes[i].getAlternativas().begin(), 0); it.first != questoes[i].getAlternativas().end(); ++it.first, it.second++) {
                mvprintw(linha / 2 - 4 + (2 * it.second), (coluna - it.first->length()) / 2, "%s", it.first->c_str());
            }
            mvprintw(linha / 2 - 4 + 2 * (questoes[i].getAlternativas().size() + 1), (coluna - campo.length()) / 2, "%s", campo.c_str());
        } else {
            campo = "Digite sua resposta (apenas aperte enter para ir a proxima): ";
            mvprintw(linha / 2 - 4 + 2 * (questoes[i].getAlternativas().size() + 1), (coluna - campo.length()) / 2, "%s", campo.c_str());        
        }

        getstr(dado);
        // cppcheck-suppress literalWithCharPtrCompare
        if (dado == "") {
            respostas.insert(pair<int, int>(questoes[i].getId(), std::stoi(dado)));
        } else {
            respostas.insert(pair<int, int>(questoes[i].getId(), 0));
        }

        it2++;

        clear();
    }
    
    endwin();

    resposta.setResposta(respostas);

    return resposta;
}

char TelaMenuProva::apresentar(string cargo) {
    char campo1[]="Gerenciamento de Prova";
    char campo2[]="1. Consultar";
    string campo3;
    if (cargo == "professor") {
        campo3 = "2. Cadastrar";
    } else {
        campo3 = "2. Selecionar uma prova";
    }
//    char campo4[]="Gerenciamento de Questão";
//    char campo5[]="3. Consultar";
//    char campo6[]="4. Cadastrar";

    char campo7[]="3. Voltar";

    char campo8[]="Selecione uma opcao: ";
    char dado1[1];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/4,(coluna-strlen(campo1))/4,"%s",campo1);
    mvprintw(linha/4 + 2,(coluna-strlen(campo2))/4,"%s",campo2);
    mvprintw(linha/4 + 4,(coluna - (campo3.length()))/4,"%s",campo3.c_str());

//    mvprintw(linha/4,3*(coluna-strlen(campo4))/4,"%s",campo4);
//    mvprintw(linha/4 + 2,3*(coluna-strlen(campo5))/4,"%s",campo5);
//    mvprintw(linha/4 + 4,3*(coluna-strlen(campo6))/4,"%s",campo6);

    mvprintw(linha/4 + 6,(coluna-strlen(campo7))/2,"%s",campo7);
    mvprintw(linha/4 + 12,(coluna-strlen(campo8))/2,"%s",campo8);

    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

int TelaOpcoesProvas::apresentar(list<Prova> listaProvas) {
    string campo1 = "Prova: ";
    string campo2 = "ID: ";
    char campo3[] = "Digite o ID da prova que deseja acessar: ";
    char dado1[30];
    int linha, coluna;

    initscr();
    getmaxyx(stdscr, linha, coluna);
    
    int contador = 3;
    list<Prova>::iterator it;
    for(it = listaProvas.begin(); it != listaProvas.end(); ++it) {
        mvprintw(linha/contador, (coluna-(campo1 + it->getNome()).length())/2, "%s", (campo1 + it->getNome()).c_str());
        //mvprintw(linha/contador, (coluna-it->getNome().length())/1, "%s", it->getNome());
        mvprintw(linha/contador + 2, (coluna-(campo2 + std::to_string(it->getId())).length())/2, "%s", (campo2 + std::to_string(it->getId())).c_str());
        //mvprintw(linha/contador + 2, (coluna-(std::to_string(it->getId()).length()))/1, "%s", (std::to_string(it->getId()).length()));             
        contador += 3;
    }
    
    mvprintw(linha/16,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado1);
     
    clear();
    endwin();

    int id = std::stoi(dado1);
    return id;    
}

char TelaConsultaProva::apresentar(Prova* prova) {
    char campo1[]="Dados de Prova";

    char campo2[]="1 - Editar.";
    char campo3[]="2 - Descadastrar.";
    char campo4[]="3 - Acessar questoes.";
    char campo5[]="4 - Ver resultados.";
    char campo6[]="5 - Voltar.";
    char campo7[]="Selecione uma opcao: ";
    char dado1[1];

    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);
    
    mvprintw(linha/2 - 10,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 6,coluna/5,"Nome: %s",prova->getNome().c_str());
    mvprintw(linha/2 - 4,coluna/5,"ID: %s",std::to_string(prova->getId()).c_str());
    mvprintw(linha/2 - 2,coluna/5,"Numero de Questoes: %s",std::to_string(prova->getIdQuestoes().size()).c_str());

    mvprintw(linha/2 + 2,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/2 + 4,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/2 + 6,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/2 + 8,(coluna-strlen(campo5))/2,"%s",campo5);
    mvprintw(linha/2 + 8,(coluna-strlen(campo6))/2,"%s",campo6);
    
    mvprintw(linha/2 + 10,(coluna-strlen(campo7))/2,"%s",campo7);
    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

void TelaCadastroProva::apresentar(Prova* prova, int idTurma) {
    char campo1[]="Digite o titulo de prova : ";
    char dado1[80];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/3,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);
    clear();
    endwin();

    prova->setNome(dado1);
    prova->setIdTurma(idTurma);
}


char TelaEdicaoProva::apresentar(Prova* prova) {
    char campo1[]="Deixe o campo em branco para manter-lo igual.";
    char campo2[]="Digite novo titulo de prova : ";
   
    char campo3[]="1 - Adicionar questao a prova.";
    char campo4[]="2 - Remover questao da prova.";
    char campo5[]="3 - Retornar.";
    
    char campo6[]="Selecione uma opcao: ";

    char dado1[80];
    char dado2[1];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/3 - 2,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/3,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado1);
    
    mvprintw(linha/3 + 4,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/3 + 6,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/3 + 8,(coluna-strlen(campo5))/2,"%s",campo5);

    mvprintw(linha/4 + 12,(coluna-strlen(campo6))/2,"%s",campo6);
    getstr(dado2);
    
    clear();
    endwin();

    if (dado1[0] != '\0'){
        prova->setNome(dado1);
    }

    return dado2[0];
}

void TelaMostrarResultados::apresentar(list<Questao> questoes, list<int> notas) {
    TelaMensagens telaMensagens;
    vector<string> campos;
    int notaTotal = 0;
    string acertouErrou;

    for (pair<list<Questao>::iterator, list<int>::iterator> it(questoes.begin(), notas.begin()); it.second != notas.end(); ++it.first, ++it.second) {
        if (*(it.second) == 0)
            acertouErrou = "X - Resposta correta: " + to_string(it.first->getRespostaCorreta());
        else
            acertouErrou = "O";
        campos.push_back(it.first->getNome() + ": " + to_string(*(it.second)) + " " + acertouErrou);
        notaTotal += *(it.second);
    }

    campos.push_back("Nota total: " + to_string(notaTotal));

    telaMensagens.apresentar(campos);
}

void TelaMostrarResultadosProva::apresentar(Prova prova, list<Usuario> alunos, list<int> notas) {
    TelaMensagens telaMensagens;
    vector<string> campos;
    int notaTotalTurma = 0;

    for (pair<list<Usuario>::iterator, list<int>::iterator> it(alunos.begin(), notas.begin()); it.second != notas.end(); ++it.first, ++it.second) {
        campos.push_back(it.first->getNome() + ": " + to_string(*(it.second)));
        notaTotalTurma += *(it.second);
    }

    campos.push_back("Nota media: " + to_string(notaTotalTurma / alunos.size()));

    telaMensagens.apresentar(campos);
}

/* teste as telas
int main() {
    
    // teste do menu e apresentar tela
    string titulo = "Menu de teste";
    vector<string> campos({"Opcao 1", "Opcao 2", "Opcao 3"});
    TelaMenu tela_menu;
    string entrada;
    entrada = tela_menu.apresentar(titulo, campos);
    std::cout << entrada << std::endl;
    

    
    // teste do formulario
    string titulo = "Formulario de teste";
    vector<string> perguntas({"Nome: ", "Email: ", "Senha: "});
    string respostas[3];
    TelaFormulario tela_formulario;
    tela_formulario.apresentar(titulo, perguntas, respostas);
    for (int i = 0; i < 3; i++) {
        std::cout << *(respostas + i) << std::endl;
    }
    
    return 0;
}
*/

/*
void TelaMensagem::apresentar(string mensagem) {

    int linha,coluna;

    initscr();                                                                      // Iniciar curses.
    getmaxyx(stdscr,linha,coluna);                                                  // Armazenar quantidade de linhas e de colunas.
    mvprintw(linha/2,(coluna-strlen(mensagem.c_str()))/2,"%s", mensagem.c_str());   // Imprimir dado.
    noecho();                                                                       // Desabilitar eco.
    getch();                                                                        // Ler caracter digitado.
    echo();                                                                         // Habilitar eco.
    clear();                                                                        // Limpar janela.
    endwin();
}

char TelaMenuUsuario::apresentar() {

    char campo1[]="Gerenciamento de Usuario";
    char campo2[]="1 - Consultar";
    char campo3[]="2 - Descadastrar";
    char campo4[]="3 - Editar";
    char campo5[]="4 - Retornar a Tela Inicial";
    char campo6[]="Selecione uma opcao: ";
    char dado1[10];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/2,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/2 + 2,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/2 + 4,(coluna-strlen(campo5))/2,"%s",campo5);
    mvprintw(linha/2 + 6,(coluna-strlen(campo6))/2,"%s",campo6);
    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

char TelaDescadastro::apresentar() {

    char campo1[]="Deseja confimar o descadastramento? (S/N) ";
    char dado1[80];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

char TelaControle::apresentar() {

    char campo1[]="Seja bem-vindo";
    char campo2[]="1 - Acessar sistema.";
    char campo3[]="2 - Cadastrar usuario.";
    char campo4[]="3 - Encerrar execucao.";
    char campo5[]="Selecione uma opcao: ";
    char dado1[10];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/2,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/2 + 2,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/2 + 4,(coluna-strlen(campo5))/2,"%s",campo5);
    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}
*/





/*
char TelaMenu::apresentar(){

    char campo1[]="Tela inicial: ";
    char campo2[]="1 - Servicos de Usuario";
    char campo3[]="2 - Servicos de Prova e Questão";
    char campo4[]="3 - Sair da conta.";
    char campo5[]="Selecione uma opcao: ";
    char dado1[10];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/2,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/2 + 2,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/2 + 4,(coluna-strlen(campo5))/2,"%s",campo5);
    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

void TelaCodigo::apresentar(Codigo* codigo) {
    char campo1[]="Codigo: ";
    char dado1[15];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);

    clear();
    endwin();

}


char TelaConsultarUsuario::apresentar(Usuario usuario) {
    char campo1[] = "Consultar usuario";
    char campo2[]="Matricula: ";
    char campo3[]="Nome: ";
    char campo4[]="Aperte qualquer tecla para retornar";
    string matricula = usuario.getMatricula().getValor(), nome = usuario.getNome().getValor();

    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2, campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2)-matricula.length())/2, "Matricula: %s", matricula.c_str());
    mvprintw(linha/2,(coluna-strlen(campo3)-nome.length())/2, "Nome: %s", nome.c_str());
    mvprintw(linha/2 + 4,(coluna-strlen(campo4))/2, campo4);
    getch();
    clear();
    endwin();
}
*/

