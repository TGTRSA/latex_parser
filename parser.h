#ifndef PARSER
#define PARSER
#include "lexer.h"
#include <stdlib.h>
#pragma once
//return (
        //     "\\documentclass{article}\n"
        //     "\\usepackage[utf8]{inputenc}\n"
        //     "\\usepackage{amsmath}\n"        
        //     "\\usepackage{amssymb}\n"
        //     "\\usepackage{tikz}\n"
        //     "\\usepackage{pgfplots}\n"
        //     "\\usepackage{chemfig}"
        //     "\\usepackage{geometry}\n"
        //     "\\begin{document}\n"
        //     f"{body}\n"
        //     "\\end{document}"
        // )


void compile_tex(token_container* tokens);

#endif