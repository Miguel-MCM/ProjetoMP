#include <string.h>
#include <stdexcept>

#include "Interfaces.h"
#include "Controladoras.h"
#include "Builders.h"


int main() {
    // Instanciar Builder.

    BuilderSistema* builder;
    builder = new BuilderSistema();

    // Construir (build) sistema.

    CntrApresentacaoControle* cntrApresentacaoControle;
    cntrApresentacaoControle = builder->construir();

    // Solicitar servico de apresentacao.

    cntrApresentacaoControle->executar();

    // Destruir builder.

    delete builder;
    
    return 0;
}
