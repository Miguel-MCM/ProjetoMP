#ifndef INCLUDE_ENTIDADES_H_

#define INCLUDE_ENTIDADES_H_

#include <string>
#include <stdexcept>
#include <list>

using std::string;
using std::invalid_argument;
using std::list;

class Entidade {
 protected:
    string nome;
    int id;
 public:
    void setNome(string);
    string const getNome();
    int const getId();
    void setId(int);
};

inline int const Entidade::getId() {return id;}

inline void Entidade::setId(int id) {this->id = id;}

inline string const Entidade::getNome() {return nome;}

inline void Entidade::setNome(string nome) {
    if (nome.length() == 0) {
        throw invalid_argument("Nome invalido");
    }
    this->nome = nome;
}

class Usuario:public Entidade {
 protected:
    static int qtd_usuarios;
    string email;
    string senha;
    string cargo;
 public:
    string const getEmail();
    void setEmail(string);
    string const getSenha();
    void setSenha(string);
    string const getCargo();
    virtual ~Usuario() {}
};

inline string const Usuario::getEmail() {return email;}

inline void Usuario::setEmail(string email) {
    if (email.length() == 0 || email.find('@') == string::npos) {
        throw invalid_argument("Email invalido");
    }
    this->email = email;
}

inline string const Usuario::getSenha() {return senha;}

inline void Usuario::setSenha(string senha) {
    if (senha.length() < 4) {
        throw invalid_argument("Senha invalido");
    }
    this->senha = senha;
}

inline string const Usuario::getCargo() {return cargo;}

class Turma:public Entidade {
 private:
    static int qtd_alunos;
    string descricao;
    bool aberta;
    int id_prof;
 public:
    string const getDescricao();
    void setDescricao(string);
    bool const taAberta();
    void switchAberta();
    int const getIdProf();
    void setIdProf(int);
};

inline string const Turma::getDescricao() {return descricao;}

inline void Turma::setDescricao(string descricao) {
    if (descricao.length() == 0) {
        throw invalid_argument("Descricao invalida");
    }
    this->descricao = descricao;
}

inline bool const Turma::taAberta() {return aberta;}

inline void Turma::switchAberta() {aberta = !aberta;}

inline int const Turma::getIdProf() {return id_prof;}

inline void Turma::setIdProf(int id_prof) {this->id_prof = id_prof;}

class Questao:public Entidade {
 private:
    string texto;
    int id_prof;
    int reposta_correta;
    static const int LIMITE_ALTERNATIVAS = 5;
    string * alternativas;
 public:
    string getTexto() const;
    void setTexto(string);
    int getIdProf() const;
    void setIdProf(int);
    int getRespostaCorreta() const;
    void setRespostaCorreta(int);
    string * getAlternativas() const;
    void setAlternativas(string *);
};

inline int Questao::getIdProf() const {return id_prof;}

inline void Questao::setIdProf(int id_prof) {this->id_prof = id_prof;}

inline void Questao::setTexto(string texto) {this->texto = texto;}

inline string Questao::getTexto() const  {return texto;}

inline int Questao::getRespostaCorreta() const {return reposta_correta;}

inline void Questao::setRespostaCorreta(int resposta_correta) {
    this->reposta_correta = resposta_correta;
}

inline string * Questao::getAlternativas() const {return alternativas;}

inline void Questao::setAlternativas(string * alternativas) {
    this->alternativas = alternativas;
}

class Prova:public Entidade {
 private:
    list<int> id_questoes;
    int id_turma;
 public:
    list<int> getIdQuestoes() const;
    void setIdQuestoes(list<int>);
    int getIdTurma() const;
    void setIdTurma(int);
};

inline list<int> Prova::getIdQuestoes() const {return id_questoes;}

inline void Prova::setIdQuestoes(list<int> id_questoes) {
    this->id_questoes = id_questoes;
}

inline int Prova::getIdTurma() const {return id_turma;}

inline void Prova::setIdTurma(int id_turma) {this->id_turma = id_turma;}

class Resposta:public Entidade {
 private:
    int resposta;
    int id_estudante;
    int id_prova;
 public:
    int getIdEstudante() const;
    void setIdEstudante(int);
    int getIdProva() const;
    void setIdProva(int);
    int getResposta() const;
    void setResposta(int);
};

inline int Resposta::getIdEstudante() const {return id_estudante;}

inline void Resposta::setIdEstudante(int id_estudante) {
    this->id_estudante = id_estudante;
}

inline int Resposta::getIdProva() const {return id_prova;}

inline void Resposta::setIdProva(int id_prova) {this->id_prova = id_prova;}

inline int Resposta::getResposta() const {return resposta;}

inline void Resposta::setResposta(int resposta) {this->resposta = resposta;}

/*
using namespace std;

///@brief Um prova é um esforço temporário que tem como finalidade um resultado único e possui recursos delimitados; é identificado no sistema por um código, e possui um nome e uma descrição.
class Prova {
    private:
            Texto nome;
            Codigo codigo;
            Texto descricao;
            Matricula usuario;
    public:
            /// @brief Armazena o nome do Prova caso o parâmetro passado seguir corretamente a formatação do domínio Texto.
            /// @param -Texto nome
            /// @throw -invalid_argument : se o valor passado não cumprir as regras de formatação
            void setNome(const Texto&);
            /// @brief Retorna o nome do Prova.
            /// @return -Texto nome
            Texto getNome() const;
            /// @brief Armazena o código do Prova caso o parâmetro passado seguir corretamente a formatação do domínio Código.
            /// @param -Codigo codigo
            /// @throw -invalid_argument : se o valor passado não cumprir as regras de formatação
            void setCodigo(const Codigo&);
            /// @brief Retorna o código do Prova.
            /// @return -Codigo codigo
            Codigo getCodigo() const;
            /// @brief Armazena a descrição do Prova caso o parâmetro passado seguir corretamente a formatação do domínio Texto.
            /// @param -Texto descricao
            /// @throw -invalid_argument : se o valor passado não cumprir as regras de formatação
            void setDescricao(const Texto&);
            /// @brief Retorna a descrição do Prova.
            /// @return -Texto descricao
            Texto getDescricao() const;
            void SetUsuario(const Matricula&);
            Matricula getUsuario() const;
};

inline void Prova::setNome(const Texto &nome){
    this->nome = nome;
}

inline Texto Prova::getNome() const{
    return nome;
}

inline void Prova::setCodigo(const Codigo &codigo){
    this->codigo = codigo;
}

inline Codigo Prova::getCodigo() const{
    return codigo;
}

inline void Prova::setDescricao(const Texto &descricao){
    this->descricao = descricao;
}

inline Texto Prova::getDescricao() const{
    return descricao;
}

inline void Prova::SetUsuario(const Matricula &usuario){
    this->usuario = usuario;
}

inline Matricula Prova::getUsuario() const {
    return usuario;
}

///@brief Entidade que representa um trabalho realizado de uma certa disciplina dentro de um prazo determinado.
//por: Anita Garcia Lagos OLiveira (211068243)
class Questao {
    private:
            Texto nome;
            Codigo codigo;
            Data inicio;
            Data termino;
            Disciplina disciplina;
            Codigo prova;
            Matricula usuario;
    public:
            ///@brief Armazena o nome da Questao caso o parâmetro passado seguir corretamente a formatação do domínio Texto.
            /// @param - Texto nome
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setNome(const Texto&);
            ///@brief Retorna o nome da Questao.
            /// @return - Texto nome
            Texto getNome() const;

            ///@brief Armazena o código da Questao caso o parâmetro passado seguir corretamente a formatação do domínio Código.
            /// @param - Codigo codigo
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setCodigo(const Codigo&);
            /// @brief Retorna o código da Questao.
            /// @return - Codigo codigo
            Codigo getCodigo() const;

            /// @brief Armazena a data de início da Questao caso o parâmetro passado seguir corretamente a formatação do domínio Data.
            /// @param - Data inicio
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setInicio(const Data&);
            /// @brief Retorna a data de início da Questao.
            /// @return - Data inicio
            Data getInicio() const;

            /// @brief Armazena a data de término da Questao caso o parâmetro passado seguir corretamente a formatação do domínio Data.
            /// @param - Data termino
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setTermino(const Data&);

            /// @brief Retorna a data de término da Questao.
            /// @return - Data termino
            Data getTermino() const;

            /// @brief Armazena a disciplina da Questao caso o parâmetro passado seguir corretamente a formatação do domínio Disciplina.
            /// @param - Disciplina discipllina
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setDisciplina(const Disciplina&);
            /// @brief Retorna a disciplina da Questao.
            /// @return - Disciplina disciplina
            Disciplina getDisciplina() const;
            void setProva(const Codigo);
            Codigo getProva() const;
            Matricula getUsuario() const;
            void setUsuario(const Matricula);
};

inline void Questao::setUsuario(const Matricula usuario) {
    this->usuario = usuario;
}

inline void Questao::setProva(const Codigo prova) {
    this->prova = prova;
}

inline Codigo Questao::getProva() const {
    return prova;
}

inline Matricula Questao::getUsuario() const {
    return usuario;
}

inline void Questao::setNome(const Texto &nome){
    this->nome = nome;
}

inline Texto Questao::getNome() const{
    return nome;
}

inline void Questao::setCodigo(const Codigo &codigo){
    this->codigo = codigo;
}

inline Codigo Questao::getCodigo() const{
    return codigo;
}

inline void Questao::setInicio(const Data &inicio){
    this->inicio = inicio;
}

inline Data Questao::getInicio() const{
    return inicio;
}

inline void Questao::setTermino(const Data &termino){
    this->termino = termino;
}

inline Data Questao::getTermino() const{
    return termino;
}

inline void Questao::setDisciplina(const Disciplina &disciplina){
    this->disciplina = disciplina;
}

inline Disciplina Questao::getDisciplina() const{
    return disciplina;
}


///@brief Usuários são agentes externos ao sistema que usufruem da tecnologia para realizar determinado prova.
///Cada usuário pode cadastrar uma conta informando nome, matrícula e senha.
class Usuario {
    private:
            Nome nome;
            Matricula matricula;
            Senha senha;
    public:
            /// @brief Armazena o nome do Usuário caso o parâmetro passado seguir corretamente a formatação do domínio Nome.
            /// @param - Nome nome
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setNome(const Nome&);
            /// @brief Retorna o nome do Usuário.
            /// @return - Nome nome
            Nome getNome() const;

            /// @brief Armazena a matrícula do Usuário caso o parâmetro passado seguir corretamente a formatação do domínio Matricula.
            /// @param - Matricula matricula
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setMatricula(const Matricula&);
            /// @brief Retorna a matrícula do Usuário.
            /// @return - Matricula matricula
            Matricula getMatricula() const;

            /// @brief Armazena a senha do Usuário caso o parâmetro passado seguir corretamente a formatação do domínio Senha.
            /// @param - Senha senha
            /// @throw - invalid_argument : se o valor passado não cumprir as regras de formatação
            void setSenha(const Senha&);
            /// @brief Retorna a senha do Usuário.
            /// @return - Senha senha
            Senha getSenha() const;
};

inline void Usuario::setNome(const Nome &nome){
    this->nome = nome;
}

inline Nome Usuario::getNome() const{
    return nome;
}

inline void Usuario::setMatricula(const Matricula &matricula){
    this->matricula = matricula;
}

inline Matricula Usuario::getMatricula() const{
    return matricula;
}

inline void Usuario::setSenha(const Senha &senha){
    this->senha = senha;
}

inline Senha Usuario::getSenha() const{
    return senha;
}
*/


#endif  // INCLUDE_ENTIDADES_H_
