#ifndef INCLUDE_BUILDERS_H_
#define INCLUDE_BUILDERS_H_

#include "Interfaces.h"
#include "Controladoras.h"

/// @brief A classe Builder constroi o sistema, interligando os módulos através das interfaces

class BuilderSistema {
    private:
        CntrApresentacaoControle* cntrApresentacaoControle;
        IApresentacaoAutenticacao* cntrApresentacaoAutenticacao;
        IApresentacaoUsuario* cntrApresentacaoUsuario;
        IApresentacaoProva* cntrApresentacaoProva;
        IApresentacaoAdmin* cntrApresentacaoAdmin;
        IApresentacaoTurma* cntrApresentacaoTurma;

        IServicoAutenticacao *cntrServicoAutenticacao;
        IServicoUsuario *cntrServicoUsuario;
        IServicoAdmin *cntrServicoAdmin;
        IServicoProva* cntrServicoProva;
        IServicoTurma * cntrServicoTurma;
    public:
        /// @brief Método responsável por interligar as controladoras
        /// @return ponteiro do tipo CntrApresentacaoControle
        CntrApresentacaoControle* construir();
        ~BuilderSistema();
};

#endif // INCLUDE_BUILDERS_H_

