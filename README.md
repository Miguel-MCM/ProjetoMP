# Projeto MP
  Esse projeto foi desenvolvido em c++ usando a lib NCusers para a interface visual. 
  Obs: Não é possivel executar diretamente no windows, somente em WSL ou Linux.
  ## Como Executar o Projeto:
    - Tenha instalado o CMake e o GCC para compilar o projeto.
    - Com o terminal aberto na raiz do projeto execute os seguintes comandos:
      - mkdir build
      - cd build
      - cmake ..
      - make
      - Copie o arquivo "Banco.db" da pasta raiz e cole dentro da pasta build
      - ./ProjetoMP
  ## Como executar os testes:
    - Dentro da pasta build, após os comandos para compilar acima digite "ctest"
  ## Verificadores:
    - Para o cppLint execute na raiz: cpplint --recursive --exclude=ncurses-6.4/* --exclude=build/* --exclude=include/sqlite3.h --exclude=include/curses h .
    - Para o cppCheck execute na raiz: cppcheck -incurses-6.4 -ibuild .
  ## Documentação:
    - Abrir arquivo index.html na pasta doxygen

## Links:
  - <a href="https://github.com/Miguel-MCM/ProjetoMP">GitHub do Projeto</a>
  - <a href="https://trello.com/b/nEPNqSi7/projeto-de-mp">Trello</a>
