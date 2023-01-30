#include "Builders.h"

CntrApresentacaoControle* BuilderSistema::construir(){

    // Instanciar controladoras da camada de apresenta��o.

    cntrApresentacaoControle = new CntrApresentacaoControle();
    cntrApresentacaoAutenticacao = new CntrApresentacaoAutenticacao();
    cntrApresentacaoUsuario = new CntrApresentacaoUsuario();
    cntrApresentacaoProva = new CntrApresentacaoProva();

    // Instanciar controladoras da camada de servi�o.

    cntrServicoUsuario = new CntrServicoUsuario();
    cntrServicoAutenticacao = new CntrServicoAutenticacao();
    cntrServicoProva = new CntrServicoProva();

    // Interligar as controladoras.

    cntrApresentacaoControle->setCntrApresentacaoAutenticacao(cntrApresentacaoAutenticacao);
    cntrApresentacaoControle->setCntrApresentacaoUsuario(cntrApresentacaoUsuario);
    cntrApresentacaoControle->setCntrlApresentacaoProva(cntrApresentacaoProva);
    cntrApresentacaoAutenticacao->setCntrServicoAutenticacao(cntrServicoAutenticacao);
    cntrApresentacaoUsuario->setCntrServicoUsuario(cntrServicoUsuario);
    cntrApresentacaoProva->setCntrServicoProva(cntrServicoProva);

    // Retornar refer�ncia para inst�ncia de CntrApresentacaoControle.

    return cntrApresentacaoControle;
}

BuilderSistema::~BuilderSistema(){
        delete cntrApresentacaoControle;
        delete cntrApresentacaoAutenticacao;
        delete cntrApresentacaoUsuario;
        delete cntrApresentacaoProva;
        delete cntrServicoAutenticacao;
        delete cntrServicoUsuario;
        delete cntrServicoProva;
}
