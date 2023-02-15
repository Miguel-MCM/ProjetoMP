#include "Builders.h"

CntrApresentacaoControle* BuilderSistema::construir(){

    // Instanciar controladoras da camada de apresentasao.

    cntrApresentacaoControle = new CntrApresentacaoControle();
    cntrApresentacaoAutenticacao = new CntrApresentacaoAutenticacao();
    cntrApresentacaoUsuario = new CntrApresentacaoUsuario();
    cntrApresentacaoProva = new CntrApresentacaoProva();
    cntrApresentacaoAdmin = new CntrApresentacaoAdmin();
    cntrApresentacaoTurma = new CntrApresentacaoTurma();

    // Instanciar controladoras da camada de servico.

    cntrServicoUsuario = new CntrServicoUsuario();
    cntrServicoAutenticacao = new CntrServicoAutenticacao();
    // cntrServicoProva = new CntrServicoProva();
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
    cntrApresentacaoAdmin->setCntrServicoAdmin(cntrServicoAdmin);

    cntrApresentacaoUsuario->setCntrApresentacaoTurma(cntrApresentacaoTurma);
    cntrApresentacaoUsuario->setCntrServicoUsuario(cntrServicoUsuario);

    cntrApresentacaoAutenticacao->setCntrServicoAutenticacao(cntrServicoAutenticacao);
    cntrApresentacaoProva->setCntrServicoProva(cntrServicoProva);
    cntrApresentacaoProva->setCntrServicoTurma(cntrServicoTurma);

    cntrApresentacaoTurma->setCntrServicoTurma(cntrServicoTurma);
    cntrApresentacaoTurma->setCntrServicoUsuario(cntrServicoUsuario);
    cntrApresentacaoTurma->setCntrApresentacaoProva(cntrApresentacaoProva);

    // Retornar referencia para instancia de CntrApresentacaoControle.

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
