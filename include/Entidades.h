#ifndef INCLUDE_ENTIDADES_H_

#define INCLUDE_ENTIDADES_H_

#include <string>
#include <stdexcept>
#include <list>
#include <map>


using std::string;
using std::invalid_argument;
using std::list;
using std::map;

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
    string email;
    string senha;
    string cargo;
    list<int> id_turmas;
 public:
    string const getEmail();
    void setEmail(string);
    string const getSenha();
    void setSenha(string);
    string const getCargo();
    void setCargo(string);
    list<int> const getIdTurmas();
    void setIdTurmas(list<int>);
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

inline void Usuario::setCargo(string cargo) {
    if (cargo != "aluno" && cargo != "professor" && cargo != "admin") {
        throw invalid_argument("Cargo deve ser 'aluno' ou 'professor' ou 'admin'.");
    }
    this->cargo = cargo;
}

inline list<int> const Usuario::getIdTurmas() {return id_turmas;}

inline void Usuario::setIdTurmas(list<int> id_turmas) {this->id_turmas = id_turmas;}

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
    list<string> alternativas;
 public:
    string getTexto() const;
    void setTexto(string);
    int getIdProf() const;
    void setIdProf(int);
    int getRespostaCorreta() const;
    void setRespostaCorreta(int);
    list<string> getAlternativas() const;
    void setAlternativas(list<string>);
};

inline int Questao::getIdProf() const {return id_prof;}

inline void Questao::setIdProf(int id_prof) {this->id_prof = id_prof;}

inline void Questao::setTexto(string texto) {this->texto = texto;}

inline string Questao::getTexto() const  {return texto;}

inline int Questao::getRespostaCorreta() const {return reposta_correta;}

inline void Questao::setRespostaCorreta(int resposta_correta) {
    this->reposta_correta = resposta_correta;
}

inline list<string> Questao::getAlternativas() const {return alternativas;}

inline void Questao::setAlternativas(list<string> alternativas) {
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
    map<int, int> resposta;
    int id_estudante;
    int id_prova;
    static const int NULL_RESPONSE = INT32_MIN;
 public:
    int getIdEstudante() const;
    void setIdEstudante(int);
    int getIdProva() const;
    void setIdProva(int);
    map<int, int> getResposta() const;
    void setResposta(map<int, int>);
};

inline int Resposta::getIdEstudante() const {return id_estudante;}

inline void Resposta::setIdEstudante(int id_estudante) {
    this->id_estudante = id_estudante;
}

inline int Resposta::getIdProva() const {return id_prova;}

inline void Resposta::setIdProva(int id_prova) {this->id_prova = id_prova;}

inline map<int, int> Resposta::getResposta() const {return resposta;}

inline void Resposta::setResposta(map<int, int> resposta) {this->resposta = resposta;}

#endif  // INCLUDE_ENTIDADES_H_
