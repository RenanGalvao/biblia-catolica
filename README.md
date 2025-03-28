# Bíblia Católica

Leia a palavra de Deus a partir de seu terminal.[^1]

## Uso

    uso: biblia [flags] [referência...]

    Flags
      -D num    mostra o número de versos de contexto após os versos correspondentes
      -A num    mostra o número de versos de contexto antes dos versos correspondentes
      -C        mostra os versos correspondentes no contexto do capítulo
      -e        destaca capítulos e números de versos
                (padrão quando a saída é um TTY)
      -p        saída para less com agrupamento de capítulos, espaçamento, recuo,
                e quebra de linha
                (padrão quando a saída é um TTY)
      -l        lista de livros
      -h        mostra essa ajuda

    Referência:
         <Livro>
             Livro individual
         <Livro>:<Capítulo>
             Capítulo individual de um livro
         <Livro>:<Capítulo>:<Verso>[,<Verso>]...
             Versículo(s) individual(ais) de um capítulo específico de um livro
         <Livro>:<Capítulo>-<Capítulo>
             Intervalo de capítulos em um livro
         <Livro>:<Capítulo>:<Verso>-<Verso>
             Intervalo de versos em um capítulo de livro
         <Livro>:<Capítulo>:<Verso>-<Capítulo>:<Verso>
             Intervalo de capítulos e versículos em um livro

         /<Pesquisa>
             Todos os versos que correspondem ao padrão
         <Livro>/<Pesquisa>
             Todos os versos de um livro que correspondem ao padrão
         <Livro>:<Capítulo>/<Pesquisa>
             Todos os versos em um capítulo de um livro que correspondem ao padrão

## Build

    git clone https://github.com/RenanGalvao/biblia-catolica.git
    cd biblia-catolica
    make
    sudo make install (opcional)

## License

[Public domain](LICENSE)

[^1]: Modificado a partir do projeto [kvj](https://github.com/layeh/kjv).
