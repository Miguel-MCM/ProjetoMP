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
    cntrApresentacaoControle->setCntrlApresentacaoProva(cntrApresentacaoProva);
    cntrApresentacaoControle->setCntrlApresentacaoAdmin(cntrApresentacaoAdmin);
    cntrApresentacaoControle->setCntrlApresentacaoTurma(cntrApresentacaoTurma);

    cntrApresentacaoAdmin->setCntrApresentacaoUsuario(cntrApresentacaoUsuario);
    cntrApresentacaoAdmin->setCntrlApresentacaoProva(cntrApresentacaoProva);
    cntrApresentacaoAdmin->setCntrlApresentacaoTurma(cntrApresentacaoTurma);

    cntrApresentacaoUsuario->setCntrlApresentacaoTurma(cntrApresentacaoTurma);

    cntrApresentacaoAutenticacao->setCntrServicoAutenticacao(cntrServicoAutenticacao);
    cntrApresentacaoUsuario->setCntrServicoUsuario(cntrServicoUsuario);
    cntrApresentacaoProva->setCntrServicoProva(cntrServicoProva);
    cntrApresentacaoAdmin->setCntrServicoAdmin(cntrServicoAdmin);
    cntrApresentacaoTurma->setCntrServicoTurma(cntrServicoTurma);

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
