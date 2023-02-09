#ifndef INCLUDE_BUILDERS_H_
#define INCLUDE_BUILDERS_H_

#include "Interfaces.h"
#include "Controladoras.h"

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
        CntrApresentacaoControle* construir();
        ~BuilderSistema();
};

#endif // INCLUDE_BUILDERS_H_

