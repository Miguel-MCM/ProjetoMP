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

/// @brief Classe que serve como base para todas as entidades.
class Entidade {
 protected:
    /// @brief Atributo da classe que representa o nome do objeto.
    string nome;
    /// @brief Atributo da classe que representa o id do objeto, que será usado no banco de dados.
    int id;
 public:
    /// @brief Armazena o valor em nome da string passada se ela seguir as regras de formatação.
    /// @param -parametro do tipo string: string que se quer armazenar no atributo nome, esse valor deve seguir as regras de formatação da classe.
    /// @throw invalid_argument
    void setNome(string);
    /// @brief Retorna a string, com formatação válida, armazenada em nome.
    /// @return string nome
    string const getNome();
    /// @brief Retorna um inteiro armazenado em id.
    /// @return int const
    int const getId();
    /// @brief Armazena o valor do inteiro passado.
    /// @param -parametro do tipo int: inteiro que se quer armazenar no atributo id.
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

/// @brief Classe que representa um usuario do sistema
class Usuario:public Entidade {
 protected:
    /// @brief Atributo de classe do tipo string que representa o email do usuario.
    string email;
    /// @brief Atributo de classe do tipo string que representa a senha do usuario.
    string senha;
    /// @brief Atributo de classe do tipo string que representa o cargo do usuario, o qual vai definir suas operações no sistema.
    string cargo;
    /// @brief Atributo de classe do tipo lista de inteiros que representa as turmas às quais o usuário está associado.
    list<int> id_turmas;
 public:
    /// @brief Retorna uma string constante, com formatação válida, armazenada em nome.
    /// @return string nome
    string const getEmail();
    /// @brief Armazena o valor em email da string passada se ela seguir as regras de formatação.
    /// @param -parametro do tipo string: string que se quer armazenar no atributo email, esse valor deve seguir as regras de formatação da classe.
    /// @throw invalid_argument
    void setEmail(string);
    /// @brief Retorna uma string constante, com formatação válida, armazenada em senha.
    /// @return string senha
    string const getSenha();
    /// @brief Armazena o valor em senha da string passada se ela seguir as regras de formatação.
    /// @param -parametro do tipo string: string que se quer armazenar no atributo senha, esse valor deve seguir as regras de formatação da classe.
    /// @throw invalid_argument
    void setSenha(string);
    /// @brief Retorna uma string constante, com formatação válida, armazenada em cargo.
    /// @return string cargo
    string const getCargo();
    /// @brief Armazena o valor em cargo da string passada se ela seguir as regras de formatação.
    /// @param -parametro do tipo string: string que se quer armazenar no atributo cargo.
    /// @throw invalid_argument
    void setCargo(string);
    /// @brief Retorna uma lista de inteiros constante, com formatação válida, armazenada em id_turmas.
    /// @return string nome
    list<int> const getIdTurmas();
    /// @brief Armazena o valor em id_turmas da lista de inteiros passada.
    /// @param -parametro do lista de inteiros: lista que se quer armazenar no atributo id_turmas.
    void setIdTurmas(list<int>);
    /// @brief Método destrutor da classe Usuario.
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

inline void Usuario::setIdTurmas(list<int> id_turmas) {
    this->id_turmas = id_turmas;
}
/// @brief Classe que representa uma turma no sistema
class Turma:public Entidade {
 private:
    /// @brief Atributo de classe que representa a quantidade de alunos da turma.
    static int qtd_alunos;
    /// @brief Atributo de classe que representa a descrição da turma.
    string descricao;
    /// @brief Atributo de classe que representa o status da turma, ou seja, se está aberta ou fechada.
    bool aberta;
    /// @brief Atributo de classe que representa o id do professor responsável pela turma.
    int id_prof;
 public:
    /// @brief Retorna uma string constante, com formatação válida, armazenada em descricao.
    /// @return string const descricao.
    string const getDescricao();
    /// @brief Armazena o valor em descrição da string passada se ela seguir as regras de formatação.
    /// @param -parametro do tipo string: string que se quer armazenar no atributo descrição.
    /// @throw invalid_argument
    void setDescricao(string);
    /// @brief Retorna um booleano que representa o status da turma.
    /// @return bool constante status.
    bool const taAberta();
    /// @brief Muda o status da turma para o contrário.
    void switchAberta();
    /// @brief Armazena o valor em descrição do booleano passado.
    /// @param -parametro do tipo bool: bool que se quer armazenar no atributo status.
    void setAberta(bool);
    /// @brief Retorna um inteiro que representa o id do professor da turma.
    /// @return inteiro constante id_prof.
    int const getIdProf();
    /// @brief Armazena o valor em id_prof do inteiro passado.
    /// @param -parametro do tipo inteiro: inteiro que se quer armazenar no atributo id_prof.
    void setIdProf(int);
    /// @brief Construtor que define o estado inicial da turma como true, ou seja, aberto
    Turma() {
        aberta = true;
    }
};

inline string const Turma::getDescricao() {return descricao;}

inline void Turma::setDescricao(string descricao) {
    if (descricao.length() == 0) {
        throw invalid_argument("Descricao invalida");
    }
    this->descricao = descricao;
}

inline void Turma::setAberta(bool aberta) {this->aberta = aberta;}

inline bool const Turma::taAberta() {return aberta;}

inline void Turma::switchAberta() {aberta = !aberta;}

inline int const Turma::getIdProf() {return id_prof;}

inline void Turma::setIdProf(int id_prof) {this->id_prof = id_prof;}

/// @brief Classe que representa uma questão no sistema.
class Questao:public Entidade {
 private:
    /// @brief Atributo de classe que representa o texto da questão.
    string texto;
    /// @brief Atributo de classe que representa o id do professor responsável pela turma.
    int id_prof;
    /// @brief Atributo de classe que representa a resposta correta da questão.
    int reposta_correta;
    /// @brief Atributo de classe constante que representa o limite de alternativas de uma questão.
    static const int LIMITE_ALTERNATIVAS = 5;
    /// @brief Atributo de classe que representa o texto das alternativas de uma questão.
    list<string> alternativas;
 public:
    /// @brief Retorna uma string que representa texto da questão.
    /// @return string texto.
    string getTexto() const;
    /// @brief Armazena o valor em texto da string passada.
    /// @param -parametro do tipo string: string que se quer armazenar no atributo texto.
    void setTexto(string);
    /// @brief Retorna um inteiro que representa o id do professor criador da questão.
    /// @return inteiro constante id_prof.
    int getIdProf() const;
    /// @brief Armazena o valor em id_prof do inteiro passado.
    /// @param -parametro do tipo inteiro: inteiro que se quer armazenar no atributo id_prof.
    void setIdProf(int);
    /// @brief Retorna um inteiro que representa a resposta correta da questão.
    /// @return inteiro constante reposta_correta.
    int getRespostaCorreta() const;
    /// @brief Armazena o valor em reposta_correta do inteiro passado.
    /// @param -parametro do tipo inteiro: inteiro que se quer armazenar no atributo reposta_correta.
    void setRespostaCorreta(int);
    /// @brief Retorna uma lista de strings que representam os textos das alternativas da questão.
    /// @return lista de inteiros alternativas.
    list<string> getAlternativas() const;
    /// @brief Armazena o valor em alternativas da lista de strings passada.
    /// @param -parametro do tipo lista de strings: lista de strings que se quer armazenar no atributo alternativas.
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
/// @brief Classe que representa uma classe no sistema.
class Prova:public Entidade {
 private:
    /// @brief Atributo de classe que representa as questões de uma prova.
    list<int> id_questoes;
    /// @brief Atributo de classe que representa o id da turma à qual a prova está associada.
    int id_turma;
    /// @brief Atributo de classe que representa o id do professor que criou a prova.
    int id_prof;
 public:
    /// @brief Retorna uma lista de inteiros que representam os ids das questão da prova.
    /// @return lista de inteiros id_questoes.
    list<int> getIdQuestoes() const;
    /// @brief Armazena o valor em id_questoes da lista de inteiros passada.
    /// @param -parametro do tipo lista de inteiros: lista de inteiros que se quer armazenar no atributo id_questoes.
    void setIdQuestoes(list<int>);
    /// @brief Retorna um inteiro que representa o id da turma à qual a prova está associada.
    /// @return inteiro id_turma.
    int getIdTurma() const;
    /// @brief Armazena o valor id_turma do inteiro passado.
    /// @param -parametro do tipo inteiro: inteiro que se quer armazenar no atributo id_turma.
    void setIdTurma(int);
    /// @brief Retorna um inteiro constante que representa o id do professor ao qual a prova está associada.
    /// @return inteiro id_prof.
    int getIdProf() const;
    /// @brief Armazena o valor id_prof do inteiro passado.
    /// @param -parametro do tipo inteiro: inteiro que se quer armazenar no atributo id_prof.  
    void setIdProf(int);
};

inline list<int> Prova::getIdQuestoes() const {return id_questoes;}

inline void Prova::setIdQuestoes(list<int> id_questoes) {
    this->id_questoes = id_questoes;
}

inline int Prova::getIdTurma() const {return id_turma;}

inline void Prova::setIdTurma(int id_turma) {this->id_turma = id_turma;}

inline int Prova::getIdProf() const {return id_prof;}

inline void Prova::setIdProf(int id_prof) {this->id_prof = id_prof;}
/// @brief Classe que representa uma resposta a uma prova de um aluno.
class Resposta:public Entidade {
 private:
    /// @brief Atributo que representa uma resposta a uma prova de um aluno.
    map<int, int> resposta;
    /// @brief Atributo que representa o id do estudante ao qual pertence a resposta.
    int id_estudante;
    /// @brief Atributo que representa o id da prova à qual está associada as resposta.
    int id_prova;
    /// @brief Atributo para uma resposta nula.
    static const int NULL_RESPONSE = INT32_MIN;
 public:
    /// @brief Retorna um inteiro que representa o id do estudante ao qual a resposta está associada.
    /// @return inteiro id_estudante.
    int getIdEstudante() const;
    /// @brief Armazena o valor id_estudante do inteiro passado.
    /// @param -parametro do tipo inteiro: inteiro que se quer armazenar no atributo id_estudante.
    void setIdEstudante(int);
    /// @brief Retorna um inteiro que representa o id da prova à qual a resposta está associada.
    /// @return inteiro id_prova.
    int getIdProva() const;
    /// @brief Armazena o valor id_prova do inteiro passado.
    /// @param -parametro do tipo inteiro: inteiro que se quer armazenar no atributo id_prova.
    void setIdProva(int);
    /// @brief Retorna um map com chave e valor de tipo inteiro que representa a resposta.
    /// @return map com chave e valor de tipo inteiro resposta.
    map<int, int> getResposta() const;
    /// @brief Armazena o valor resposta do map com chave e valor de tipo inteiro passado.
    /// @param -parametro do tipo map com chave e valor de tipo inteiro: armazená-lo no atributo resposta.
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
