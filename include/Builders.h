#ifndef INCLUDE_BUILDERS_H_
#define INCLUDE_BUILDERS_H_

#include "Interfaces.h"
#include "Controladoras.h"

/// @brief A classe Builder constroi o sistema, interligando os módulos através das interfaces

class BuilderSistema {
    private:
        /// @brief Atributo ponteiro do tipo CntrApresentacaoControle, que inicializa o sistema.
        CntrApresentacaoControle* cntrApresentacaoControle;
        /// @brief Atributo ponteiro do tipo IApresentacaoAutenticacao, que permite a autenticação no sistema.
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        /// @brief Atributo ponteiro do tipo IApresentacaoUsuario, que apresenta as opções de usuário.
        IApresentacaoUsuario* cntrApresentacaoUsuario;
        /// @brief Atributo ponteiro do tipo IApresentacaoProva, que apresenta as opções de prova.
        IApresentacaoProva* cntrApresentacaoProva;
        /// @brief Atributo ponteiro do tipo IApresentacaoAdmin, que apresenta as opções de administrador.
        IApresentacaoAdmin* cntrApresentacaoAdmin;
        /// @brief Atributo ponteiro do tipo IApresentacaoTurma, que apresenta as opções de turma.
        IApresentacaoTurma* cntrApresentacaoTurma;
        /// @brief Atributo ponteiro do tipo IServicoAutenticacao, que solicita  serviços de autenticação ao banco de dados.
        IServicoAutenticacao *cntrServicoAutenticacao;
        /// @brief Atributo ponteiro do tipo IServicoUsuario, que solicita  serviços de usuário ao banco de dados.
        IServicoUsuario *cntrServicoUsuario;
        /// @brief Atributo ponteiro do tipo IServicoAdmin, que solicita  serviços de administrador ao banco de dados.
        IServicoAdmin *cntrServicoAdmin;
        /// @brief Atributo ponteiro do tipo IServicoProva, que solicita  serviços de prova ao banco de dados.
        IServicoProva* cntrServicoProva;
        /// @brief Atributo ponteiro do tipo IServicoTurma, que solicita  serviços de turma ao banco de dados.
        IServicoTurma * cntrServicoTurma;
    public:
        /// @brief Método responsável por interligar as controladoras
        /// @return ponteiro do tipo CntrApresentacaoControle
        CntrApresentacaoControle* construir();
        /// @brief Método destrutor.
        ~BuilderSistema();
};

#endif // INCLUDE_BUILDERS_H_

