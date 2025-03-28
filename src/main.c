/*
biblia: Read the Word of God from your terminal

License: Public domain
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

#include "config.h"
#include "data.h"
#include "ref.h"
#include "render.h"
#include "strutil.h"

const char *
usage = "uso: biblia [flags] [referência...]\n"
    "\n"
    "Flags:\n"
    " -D num    mostra o número de versos de contexto após os versos correspondentes\n"
    " -A num    mostra o número de versos de contexto antes dos versos correspondentes\n"
    " -C        mostra os versos correspondentes no contexto do capítulo\n"
    " -e        destaca capítulos e números de versos\n"
    "           (padrão quando a saída é um TTY)\n"
    " -p        saída para less com agrupamento de capítulos, espaçamento, recuo,\n"
    "           e quebra de linha\n"
    "           (padrão quando a saída é um TTY)\n"
    " -l        lista de livros\n"
    " -h        mostra essa ajuda\n"
    "\n"
    "Referência:\n"
    "    <Livro>\n"
    "        Livro individual\n"
    "    <Livro>:<Capítulo>\n"
    "        Capítulo individual de um livro\n"
    "    <Livro>:<Capítulo>:<Verso>[,<Verso>]...\n"
    "        Versículo(s) individual(ais) de um capítulo específico de um livro\n"
    "    <Livro>:<Capítulo>-<Capítulo>\n"
    "        Intervalo de capítulos em um livro\n"
    "    <Livro>:<Capítulo>:<Verso>-<Verso>\n"
    "        Intervalo de versos em um capítulo de livro\n"
    "    <Livro>:<Capítulo>:<Verso>-<Capítulo>:<Verso>\n"
    "        Intervalo de capítulos e versículos em um livro\n"
    "\n"
    "    /<Pesquisa>\n"
    "        Todos os versos que correspondem ao padrão\n"
    "    <Livro>/<Pesquisa>\n"
    "        Todos os versos de um livro que correspondem ao padrão\n"
    "    <Livro>:<Capítulo>/<Pesquisa>\n"
    "        Todos os versos em um capítulo de um livro que correspondem ao padrão\n";

int
main(int argc, char *argv[])
{
    bool is_atty = isatty(STDOUT_FILENO) == 1;
    config config = {
        .highlighting = is_atty,
        .pretty = is_atty,

        .maximum_line_length = 80,

        .context_before = 0,
        .context_after = 0,
        .context_chapter = false,
    };

    bool list_books = false;

    opterr = 0;
    for (int opt; (opt = getopt(argc, argv, "D:A:CeplWh")) != -1; ) {
        char *endptr;
        switch (opt) {
        case 'D':
            config.context_after = strtol(optarg, &endptr, 10);
            if (endptr[0] != '\0') {
                fprintf(stderr, "biblia: valor de flag inválida para -D\n\n%s", usage);
                return 1;
            }
            break;
        case 'A':
            config.context_before = strtol(optarg, &endptr, 10);
            if (endptr[0] != '\0') {
                fprintf(stderr, "biblia: valor de flag inválida para -A\n\n%s", usage);
                return 1;
            }
            break;
        case 'C':
            config.context_chapter = true;
            break;
        case 'e':
            config.highlighting = true;
            break;
        case 'p':
            config.pretty = true;
            break;
        case 'l':
            list_books = true;
            break;
        case 'h':
            printf("%s", usage);
            return 0;
        case '?':
            fprintf(stderr, "biblia: flag inválida -%c\n\n%s", optopt, usage);
            return 1;
        }
    }

    if (list_books) {
        for (int i = 0; i < books_length; i++) {
            book *book = &books[i];
            printf("%s (%s)\n", book->name, book->abbr);
        }
        return 0;
    }

    struct winsize ttysize;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ttysize) == 0 && ttysize.ws_col > 0) {
        config.maximum_line_length = ttysize.ws_col;
    }

    signal(SIGPIPE, SIG_IGN);

    if (argc == optind) {
        using_history();
        while (true) {
            char *input = readline("biblia> ");
            if (input == NULL) {
                break;
            }
            add_history(input);
            ref *ref = newref();
            int success = parseref(ref, input);
            free(input);
            if (success == 0) {
                render(ref, &config);
            }
            freeref(ref);
        }
    } else {
        char *ref_str = str_join(argc-optind, &argv[optind]);
        ref *ref = newref();
        int success = parseref(ref, ref_str);
        free(ref_str);
        if (success == 0) {
            render(ref, &config);
        }
        freeref(ref);
    }

    return 0;
}
