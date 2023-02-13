#include "Telas.h"
#include <string.h>
#include <iostream>

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
    mvprintw(linha / 2, (coluna - strlen(mensagem.c_str())) / 2, "%s", mensagem.c_str()); // Imprimir dado.
    noecho();                                                                             // Desabilitar eco.
    getch();                                                                              // Ler caracter digitado.
    echo();                                                                               // Habilitar eco.
    clear();                                                                              // Limpar janela.
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

char TelaMenuProva::apresentar() {
    char campo1[]="Gerenciamento de Prova";
    char campo2[]="1. Consultar";
    char campo3[]="2. Cadastrar";

    char campo4[]="Gerenciamento de Questão";
    char campo5[]="3. Consultar";
    char campo6[]="4. Cadastrar";

    char campo7[]="5. Voltar";

    char campo8[]="Selecione uma opcao: ";
    char dado1[1];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/4,(coluna-strlen(campo1))/4,"%s",campo1);
    mvprintw(linha/4 + 2,(coluna-strlen(campo2))/4,"%s",campo2);
    mvprintw(linha/4 + 4,(coluna-strlen(campo3))/4,"%s",campo3);

    mvprintw(linha/4,3*(coluna-strlen(campo4))/4,"%s",campo4);
    mvprintw(linha/4 + 2,3*(coluna-strlen(campo5))/4,"%s",campo5);
    mvprintw(linha/4 + 4,3*(coluna-strlen(campo6))/4,"%s",campo6);

    mvprintw(linha/4 + 10,(coluna-strlen(campo7))/2,"%s",campo7);
    mvprintw(linha/4 + 12,(coluna-strlen(campo8))/2,"%s",campo8);

    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

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

    codigo->setValor(dado1);
}

*/

int TelaOpcoesProvas::apresentar(list<Prova> listaProvas) {
    char campo1[] = "Prova: ";
    char campo2[] = "ID: ";
    char campo3[] = "Digite o ID da prova que deseja acessar";
    char dado1[30];
    int linha, coluna;

    initscr();
    getmaxyx(stdscr, linha, coluna);
    
    char *teste;
    int contador = 3;
    list<Prova>::iterator it;
    for(it = listaProvas.begin(); it != listaProvas.end(); ++it) {
        mvprintw(linha/contador, (coluna-strlen(campo1))/2, "%s", campo1);
        mvprintw(linha/contador, (coluna-it->getNome().length())/1, "%s", it->getNome());
        mvprintw(linha/contador + 2, (coluna-strlen(campo2))/2, "%s", campo2);
        mvprintw(linha/contador + 2, (coluna-(std::to_string(it->getId()).length()))/1, "%s", (std::to_string(it->getId()).length()));             
        contador += 3;
    }
    
    mvprintw(linha/16,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado1);
     
    clear();
    endwin();

    int id = std::stoi(dado1);
    return id;    
}

char TelaConsultaProva::apresentar(Prova* prova, int qtdQuestoes) {
    char campo1[]="Dados de Prova";

    char campo2[]="1 - Editar";
    char campo3[]="2 - Descadastrar";
    char campo4[]="3 - Voltar";
    char campo5[]="Selecione uma opcao: ";
    char dado1[10];

    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 10,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 6,coluna/5,"Nome: %s",prova->getNome());
    mvprintw(linha/2 - 4,coluna/5,"ID: %s",std::to_string(prova->getId()));
    mvprintw(linha/2 - 2,coluna/5,"Numero de Questoes: %s",std::to_string(qtdQuestoes));

    mvprintw(linha/2 + 2,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/2 + 4,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/2 + 6,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/2 + 8,(coluna-strlen(campo5))/2,"%s",campo5);

    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

/*
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


void TelaEdicaoProva::apresentar(Prova* prova) {
    char campo1[]="Deixe o campo em branco para manter-lo igual.";
    char campo2[]="Digite novo titulo de prova : ";
    char dado1[80];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/3 - 2,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/3,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado1);
    clear();
    endwin();

    if (dado1[0] != '\0'){
        prova->setNome(dado1);
    }
}

/*
void TelaEdicaoUsuario::apresentar(Usuario * usuario) {
    char campo1[]="Edicao do usuario";
    char campo2[]="Digite o nome: ";
    char campo3[]="Digite a senha: ";
    char dado1[80], dado2[80];
    int linha,coluna;
    Senha senha;
    Nome nome;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado1);
    nome.setValor(dado1);

    mvprintw(linha/2,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado2);
    senha.setValor(dado2);

    clear();
    endwin();

    usuario->setNome(nome);
    usuario->setSenha(senha);
}

void TelaCadastroQuestao::apresentar(Questao* questao) {
    char campo1[]="Digite o codigo : ";
    char campo2[]="Digite o nome : ";
    char campo3[]="Digite o codigo do prova : ";
    char campo4[]="Digite a data de inicio : ";
    char campo5[]="Digite a data de termino : ";
    char campo6[]="Digite a disciplina : ";
    char dado1[80];
    char dado2[80];
    char dado3[80];
    char dado4[80];
    char dado5[80];
    char dado6[80];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/3,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);
    mvprintw(linha/3 + 2,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado2);
    mvprintw(linha/3 + 4,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado3);
    mvprintw(linha/3 + 6,(coluna-strlen(campo4))/2,"%s",campo4);
    getstr(dado4);
    mvprintw(linha/3 + 8,(coluna-strlen(campo5))/2,"%s",campo5);
    getstr(dado5);
    mvprintw(linha/3 + 10,(coluna-strlen(campo6))/2,"%s",campo6);
    getstr(dado6);
    clear();
    endwin();

    Codigo codigo;
    codigo.setValor(dado1);
    questao->setCodigo(codigo);

    Texto nome;
    nome.setValor(dado2);
    questao->setNome(nome);

    Codigo prova;
    prova.setValor(dado3);
    questao->setProva(prova);

    Data inicio;
    inicio.setValor(dado4);
    questao->setInicio(inicio);

    Data termino;
    termino.setValor(dado5);
    questao->setTermino(termino);

    Disciplina disciplina;
    disciplina.setValor(dado6);
    questao->setDisciplina(disciplina);
}

char TelaConsultaQuestao::apresentar(Questao* questao) {
    char campo1[]="Consulta de Questao";

    char campo2[]="1 - Editar";
    char campo3[]="2 - Descadastrar";
    char campo4[]="3 - Voltar";
    char campo5[]="Selecione uma opcao: ";
    char dado1[10];

    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 12,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 8,coluna/5,"Nome: %s",questao->getNome().getValor().c_str());
    mvprintw(linha/2 - 6,coluna/5,"Codigo: %s",questao->getCodigo().getValor().c_str());
    mvprintw(linha/2 - 4,coluna/5,"Codigo do Prova: %s",questao->getProva().getValor().c_str());
    mvprintw(linha/2 - 2,coluna/5,"Inicio: %s",questao->getInicio().getValor().c_str());
    mvprintw(linha/2,coluna/5,"Termino: %s",questao->getTermino().getValor().c_str());
    mvprintw(linha/2 + 2,coluna/5,"Disciplina: %s",questao->getDisciplina().getValor().c_str());


    mvprintw(linha/2 + 4,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/2 + 6,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/2 + 8,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/2 + 10,(coluna-strlen(campo5))/2,"%s",campo5);

    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

void TelaEdicaoQuestao::apresentar(Questao* questao) {
    char campo1[]="Deixe o campo em branco para manter-lo igual.";
    char campo2[]="Digite o nome : ";
    char campo3[]="Digite a data de inicio : ";
    char campo4[]="Digite a data de termino : ";
    char campo5[]="Digite a disciplina : ";

    char dado1[80];
    char dado2[80];
    char dado3[80];
    char dado4[80];

    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/3 - 2,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/3,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado1);
    mvprintw(linha/3 + 2,(coluna-strlen(campo3))/2,"%s",campo3);
    getstr(dado2);
    mvprintw(linha/3 + 4,(coluna-strlen(campo4))/2,"%s",campo4);
    getstr(dado3);
    mvprintw(linha/3 + 6,(coluna-strlen(campo5))/2,"%s",campo5);
    getstr(dado4);
    clear();
    endwin();

    if (dado1[0] != '\0'){
        Texto nome;
        nome.setValor(dado1);
        questao->setNome(nome);
    }

    if (dado2[0] != '\0'){
        Data inicio;
        inicio.setValor(dado2);
        questao->setInicio(inicio);
    }

    if (dado3[0] != '\0'){
        Data termino;
        termino.setValor(dado3);
        questao->setTermino(termino);
    }

    if (dado4[0] != '\0'){
        Disciplina disciplina;
        disciplina.setValor(dado4);
        questao->setDisciplina(disciplina);
    }

}

//TELA DE DADOS
//TELA DE EDITAR NOME E SENHA
*/
