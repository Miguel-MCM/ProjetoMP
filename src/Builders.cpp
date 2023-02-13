#include "Builders.h"

CntrApresentacaoControle* BuilderSistema::construir(){

    // Instanciar controladoras da camada de apresenta��o.

    cntrApresentacaoControle = new CntrApresentacaoControle();
    cntrApresentacaoAutenticacao = new CntrApresentacaoAutenticacao();
    cntrApresentacaoUsuario = new CntrApresentacaoUsuario();
    cntrApresentacaoProva = new CntrApresentacaoProva();
    cntrApresentacaoAdmin = new CntrApresentacaoAdmin();
    cntrApresentacaoTurma = new CntrApresentacaoTurma();

    // Instanciar controladoras da camada de servi�o.

    cntrServicoUsuario = new CntrServicoUsuario();
    cntrServicoAutenticacao = new CntrServicoAutenticacao();
    cntrServicoProva = new CntrServicoProva();
    cntrServicoAdmin = new CntrServicoAdmin();
    cntrServicoTurma = new CntrServicoTurma();

    // Interligar as controladoras.

    cntrApresentacaoControle->setCntrApresentacaoAutenticacao(cntrApresentacaoAutenticacao);
    cntrApresentacaoControle->setCntrApresentacaoUsuario(cntrApresentacaoUsuario);
    cntrApresentacaoControle->setCntrApresentacaoProva(cntrApresentacaoProva);
    cntrApresentacaoControle->setCntrApresentacaoAdmin(cntrApresentacaoAdmin);
    cntrApresentacaoControle->setCntrApresentacaoTurma(cntrApresentacaoTurma);

    cntrApresentacaoAdmin->setCntrApresentacaoUsuario(cntrApresentacaoUsuario);
    cntrApresentacaoAdmin->setCntrApresentacaoProva(cntrApresentacaoProva);
    cntrApresentacaoAdmin->setCntrApresentacaoTurma(cntrApresentacaoTurma);

    cntrApresentacaoUsuario->setCntrApresentacaoTurma(cntrApresentacaoTurma);
    cntrApresentacaoUsuario->setCntrServicoUsuario(cntrServicoUsuario);
    cntrApresentacaoUsuario->setCntrServicoAdmin(cntrServicoAdmin);

    cntrApresentacaoAutenticacao->setCntrServicoAutenticacao(cntrServicoAutenticacao);
    cntrApresentacaoProva->setCntrServicoProva(cntrServicoProva);
    cntrApresentacaoAdmin->setCntrServicoAdmin(cntrServicoAdmin);
    cntrApresentacaoTurma->setCntrServicoTurma(cntrServicoTurma);
    cntrApresentacaoTurma->setCntrServicoUsuario(cntrServicoUsuario);

    // Retornar refer�ncia para inst�ncia de CntrApresentacaoControle.

    return cntrApresentacaoControle;
}

BuilderSistema::~BuilderSistema(){
        delete cntrApresentacaoControle;
        delete cntrApresentacaoAutenticacao;
        delete cntrApresentacaoUsuario;
        delete cntrApresentacaoProva;
        delete cntrApresentacaoAdmin;
        delete cntrApresentacaoTurma;

        delete cntrServicoAutenticacao;
        delete cntrServicoUsuario;
        delete cntrServicoProva;
        delete cntrServicoAdmin;
        delete cntrServicoTurma;
}
