#include "Builders.h"

CntrApresentacaoControle* BuilderSistema::construir(){

    // Instanciar controladoras da camada de apresenta��o.

    cntrApresentacaoControle = new CntrApresentacaoControle();
    cntrApresentacaoAutenticacao = new CntrApresentacaoAutenticacao();
    cntrApresentacaoUsuario = new CntrApresentacaoUsuario();
    cntrApresentacaoProjeto = new CntrApresentacaoProjeto();

    // Instanciar controladoras da camada de servi�o.

    cntrServicoUsuario = new CntrServicoUsuario();
    cntrServicoAutenticacao = new CntrServicoAutenticacao();
    cntrServicoProjeto = new CntrServicoProjeto();

    // Interligar as controladoras.

    cntrApresentacaoControle->setCntrApresentacaoAutenticacao(cntrApresentacaoAutenticacao);
    cntrApresentacaoControle->setCntrApresentacaoUsuario(cntrApresentacaoUsuario);
    cntrApresentacaoControle->setCntrlApresentacaoProjeto(cntrApresentacaoProjeto);
    cntrApresentacaoAutenticacao->setCntrServicoAutenticacao(cntrServicoAutenticacao);
    cntrApresentacaoUsuario->setCntrServicoUsuario(cntrServicoUsuario);
    cntrApresentacaoProjeto->setCntrServicoProjeto(cntrServicoProjeto);

    // Retornar refer�ncia para inst�ncia de CntrApresentacaoControle.

    return cntrApresentacaoControle;
}

BuilderSistema::~BuilderSistema(){
        delete cntrApresentacaoControle;
        delete cntrApresentacaoAutenticacao;
        delete cntrApresentacaoUsuario;
        delete cntrApresentacaoProjeto;
        delete cntrServicoAutenticacao;
        delete cntrServicoUsuario;
        delete cntrServicoProjeto;
}
