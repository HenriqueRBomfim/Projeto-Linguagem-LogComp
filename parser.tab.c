/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "blocks.h"

#define MAX_VARS 256
#define MAX_PERSONAGENS 64
#define MAX_ATTRS 32

typedef struct {
    char name[64];
    int value;
} VarEntry;

VarEntry var_table[MAX_VARS];
int var_count = 0;

typedef struct {
    char* nome;
} fn_data;

// Função para buscar variável
int get_var(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            return var_table[i].value;
        }
    }
    return 0;
}

// Função para definir variável
void set_var(const char* name, int value) {
    if (value < 0) value = 0;
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0) {
            var_table[i].value = value;
            return;
        }
    }
    if (var_count < MAX_VARS) {
        strncpy(var_table[var_count].name, name, 63);
        var_table[var_count].name[63] = '\0';
        var_table[var_count].value = value;
        var_count++;
    }
}

void print_slow(const char *txt, useconds_t delay_us) {
    for (const char *p = txt; *p; ++p) {
        putchar(*p);
        fflush(stdout);
        usleep(delay_us); // delay em microssegundos (ex: 30000 = 0.03s)
    }
    putchar('\n');
}

typedef struct {
    char nome[64];
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
    char* inventario;
} Personagem;

typedef struct {
    char nome[64];
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
    char* inventario;
} Monstro;

typedef struct {
    char nome[64];
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
} Item;

Personagem personagens[MAX_PERSONAGENS];
int personagem_count = 0;

Monstro monstros[MAX_PERSONAGENS];
int monstro_count = 0;

Item itens[MAX_PERSONAGENS];
int item_count = 0;

int get_personagem_attr(const char* nome_personagem, const char* nome_attr) {
    for (int i = 0; i < personagem_count; i++) {
        if (strcmp(personagens[i].nome, nome_personagem) == 0) {
            for (int j = 0; j < personagens[i].attr_count; j++) {
                if (strcmp(personagens[i].atributos[j].nome, nome_attr) == 0)
                    return personagens[i].atributos[j].valor;
            }
        }
    }
    return 0;
}

void set_personagem_attr(const char* nome_personagem, const char* nome_attr, int valor) {
    for (int i = 0; i < personagem_count; i++) {
        if (strcmp(personagens[i].nome, nome_personagem) == 0) {
            for (int j = 0; j < personagens[i].attr_count; j++) {
                if (strcmp(personagens[i].atributos[j].nome, nome_attr) == 0) {
                    personagens[i].atributos[j].valor = valor;
                    return;
                }
            }
            // Se não existe, adiciona
            if (personagens[i].attr_count < MAX_ATTRS) {
                strncpy(personagens[i].atributos[personagens[i].attr_count].nome, nome_attr, 63);
                personagens[i].atributos[personagens[i].attr_count].nome[63] = '\0';
                personagens[i].atributos[personagens[i].attr_count].valor = valor;
                personagens[i].attr_count++;
            }
            return;
        }
    }
}

typedef struct {
    struct {
        char nome[64];
        int valor;
    } atributos[MAX_ATTRS];
    int attr_count;
    char* inventario;
    int definido;
} PersonagemPadrao;
PersonagemPadrao padrao = { { { {0} } }, 0, NULL, 0 };

void criar_personagem(const char* nome, const PersonagemPadrao* padrao) {
    printf("[DEBUG] criar_personagem: nome=%s, padrao=%p\n", nome, (void*)padrao);
    printf("[DEBUG] padrao->attr_count=%d\n", padrao->attr_count);
    printf("[DEBUG] padrao->inventario=%s\n", padrao->inventario ? padrao->inventario : "(null)");

    if (personagem_count < MAX_PERSONAGENS) {
        // Cópia segura do nome
        strncpy(personagens[personagem_count].nome, nome, 63);
        personagens[personagem_count].nome[63] = '\0';

        // Cópia dos atributos
        for (int i = 0; i < padrao->attr_count; i++) {
            printf("[DEBUG] Copiando atributo %d: %s=%d\n", i, padrao->atributos[i].nome, padrao->atributos[i].valor);
            strncpy(personagens[personagem_count].atributos[i].nome, padrao->atributos[i].nome, 63);
            personagens[personagem_count].atributos[i].nome[63] = '\0';
            personagens[personagem_count].atributos[i].valor = padrao->atributos[i].valor;
        }
        personagens[personagem_count].attr_count = padrao->attr_count;

        // Cópia segura do inventário
        if (padrao->inventario) {
            personagens[personagem_count].inventario = strdup(padrao->inventario);
            printf("[DEBUG] Inventario copiado: %s\n", personagens[personagem_count].inventario);
        } else {
            personagens[personagem_count].inventario = NULL;
            printf("[DEBUG] Inventario NULL\n");
        }

        personagem_count++;
        printf("[DEBUG] personagem_count agora: %d\n", personagem_count);
    } else {
        printf("[DEBUG] Limite de personagens atingido!\n");
    }
}

void criar_monstro(const char* nome, const PersonagemPadrao* padrao) {
    printf("[DEBUG] criar_monstro: nome=%s\n", nome);

    if (monstro_count < MAX_PERSONAGENS) {
        strncpy(monstros[monstro_count].nome, nome, 63);
        monstros[monstro_count].nome[63] = '\0';

        for (int i = 0; i < padrao->attr_count; i++) {
            strncpy(monstros[monstro_count].atributos[i].nome, padrao->atributos[i].nome, 63);
            monstros[monstro_count].atributos[i].nome[63] = '\0';
            monstros[monstro_count].atributos[i].valor = padrao->atributos[i].valor;
        }
        monstros[monstro_count].attr_count = padrao->attr_count;

        if (padrao->inventario) {
            monstros[monstro_count].inventario = strdup(padrao->inventario);
        } else {
            monstros[monstro_count].inventario = NULL;
        }

        monstro_count++;
        printf("[DEBUG] monstro_count agora: %d\n", monstro_count);
    }
}

void criar_item(const char* nome, const PersonagemPadrao* padrao) {
    printf("[DEBUG] criar_item: nome=%s\n", nome);

    if (item_count < MAX_PERSONAGENS) {
        strncpy(itens[item_count].nome, nome, 63);
        itens[item_count].nome[63] = '\0';

        for (int i = 0; i < padrao->attr_count; i++) {
            strncpy(itens[item_count].atributos[i].nome, padrao->atributos[i].nome, 63);
            itens[item_count].atributos[i].nome[63] = '\0';
            itens[item_count].atributos[i].valor = padrao->atributos[i].valor;
        }
        itens[item_count].attr_count = padrao->attr_count;

        item_count++;
        printf("[DEBUG] item_count agora: %d\n", item_count);
    }
}

extern FILE *yyin;
void yyerror(const char *s);
int yylex(void);

#line 296 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CAMPANHA = 3,                   /* CAMPANHA  */
  YYSYMBOL_FIM_CAMPANHA = 4,               /* FIM_CAMPANHA  */
  YYSYMBOL_CRIAR = 5,                      /* CRIAR  */
  YYSYMBOL_PERSONAGEM = 6,                 /* PERSONAGEM  */
  YYSYMBOL_PADRAO = 7,                     /* PADRAO  */
  YYSYMBOL_MONSTRO = 8,                    /* MONSTRO  */
  YYSYMBOL_ITEM = 9,                       /* ITEM  */
  YYSYMBOL_DEFINIR = 10,                   /* DEFINIR  */
  YYSYMBOL_INT = 11,                       /* INT  */
  YYSYMBOL_STRING = 12,                    /* STRING  */
  YYSYMBOL_BOOL = 13,                      /* BOOL  */
  YYSYMBOL_NARRAR = 14,                    /* NARRAR  */
  YYSYMBOL_SE = 15,                        /* SE  */
  YYSYMBOL_SENAO = 16,                     /* SENAO  */
  YYSYMBOL_ENQUANTO = 17,                  /* ENQUANTO  */
  YYSYMBOL_IDENTIFIER = 18,                /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 19,            /* STRING_LITERAL  */
  YYSYMBOL_INTEGER = 20,                   /* INTEGER  */
  YYSYMBOL_NEWLINE = 21,                   /* NEWLINE  */
  YYSYMBOL_VERDADEIRO = 22,                /* VERDADEIRO  */
  YYSYMBOL_FALSO = 23,                     /* FALSO  */
  YYSYMBOL_IGUAL = 24,                     /* IGUAL  */
  YYSYMBOL_OU = 25,                        /* OU  */
  YYSYMBOL_E = 26,                         /* E  */
  YYSYMBOL_NAO = 27,                       /* NAO  */
  YYSYMBOL_ROLAR_DADO = 28,                /* ROLAR_DADO  */
  YYSYMBOL_NEQ = 29,                       /* NEQ  */
  YYSYMBOL_OBSTACULO = 30,                 /* OBSTACULO  */
  YYSYMBOL_31_ = 31,                       /* '+'  */
  YYSYMBOL_32_ = 32,                       /* '-'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_35_ = 35,                       /* '<'  */
  YYSYMBOL_36_ = 36,                       /* '>'  */
  YYSYMBOL_37_ = 37,                       /* '{'  */
  YYSYMBOL_38_ = 38,                       /* '}'  */
  YYSYMBOL_39_ = 39,                       /* '='  */
  YYSYMBOL_40_ = 40,                       /* '['  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_statements = 48,                /* statements  */
  YYSYMBOL_statement = 49,                 /* statement  */
  YYSYMBOL_opt_newline = 50,               /* opt_newline  */
  YYSYMBOL_entity_decl = 51,               /* entity_decl  */
  YYSYMBOL_entity_type = 52,               /* entity_type  */
  YYSYMBOL_obstaculo_stmt = 53,            /* obstaculo_stmt  */
  YYSYMBOL_attribute_assigns = 54,         /* attribute_assigns  */
  YYSYMBOL_attribute_assign = 55,          /* attribute_assign  */
  YYSYMBOL_string_list = 56,               /* string_list  */
  YYSYMBOL_var_decl = 57,                  /* var_decl  */
  YYSYMBOL_jogadores_decl = 58,            /* jogadores_decl  */
  YYSYMBOL_name_list = 59,                 /* name_list  */
  YYSYMBOL_type_decl = 60,                 /* type_decl  */
  YYSYMBOL_assign_stmt = 61,               /* assign_stmt  */
  YYSYMBOL_narrate_expr = 62,              /* narrate_expr  */
  YYSYMBOL_narrate_stmt = 63,              /* narrate_stmt  */
  YYSYMBOL_attr_access = 64,               /* attr_access  */
  YYSYMBOL_if_stmt = 65,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 66,                /* while_stmt  */
  YYSYMBOL_block = 67,                     /* block  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_bexpression = 69,               /* bexpression  */
  YYSYMBOL_bterm = 70,                     /* bterm  */
  YYSYMBOL_rexp = 71,                      /* rexp  */
  YYSYMBOL_expr = 72,                      /* expr  */
  YYSYMBOL_term = 73,                      /* term  */
  YYSYMBOL_factor = 74                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    44,    33,    31,    42,    32,    45,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,    39,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   267,   267,   278,   293,   298,   308,   318,   319,   320,
     321,   322,   323,   324,   325,   328,   330,   334,   364,   365,
     366,   370,   382,   383,   387,   411,   429,   431,   449,   467,
     486,   488,   506,   507,   508,   512,   526,   546,   548,   561,
     567,   574,   585,   597,   605,   620,   644,   698,   702,   706,
     707,   711,   712,   716,   717,   718,   719,   720,   724,   725,
     726,   730,   731,   732,   736,   737,   738,   739,   740,   746,
     755,   756,   757,   763
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CAMPANHA",
  "FIM_CAMPANHA", "CRIAR", "PERSONAGEM", "PADRAO", "MONSTRO", "ITEM",
  "DEFINIR", "INT", "STRING", "BOOL", "NARRAR", "SE", "SENAO", "ENQUANTO",
  "IDENTIFIER", "STRING_LITERAL", "INTEGER", "NEWLINE", "VERDADEIRO",
  "FALSO", "IGUAL", "OU", "E", "NAO", "ROLAR_DADO", "NEQ", "OBSTACULO",
  "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'{'", "'}'", "'='", "'['",
  "']'", "','", "'('", "')'", "'.'", "$accept", "program", "statements",
  "statement", "opt_newline", "entity_decl", "entity_type",
  "obstaculo_stmt", "attribute_assigns", "attribute_assign", "string_list",
  "var_decl", "jogadores_decl", "name_list", "type_decl", "assign_stmt",
  "narrate_expr", "narrate_stmt", "attr_access", "if_stmt", "while_stmt",
  "block", "expression", "bexpression", "bterm", "rexp", "expr", "term",
  "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-42)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      13,   145,    31,   105,    -5,    -3,     5,     7,    10,   173,
    -112,    24,  -112,  -112,  -112,  -112,  -112,  -112,  -112,    -6,
    -112,  -112,  -112,  -112,  -112,  -112,    34,    62,    59,   125,
     125,    77,    48,    54,  -112,  -112,   125,    28,  -112,  -112,
    -112,    41,   -24,  -112,  -112,  -112,  -112,   125,    40,   125,
     125,   125,   -14,    -9,    25,   -15,  -112,    49,  -112,    26,
      60,    70,  -112,   169,    57,    84,  -112,  -112,  -112,  -112,
    -112,   125,  -112,    90,  -112,  -112,    74,    59,  -112,   125,
     125,   125,   125,    82,   125,   125,   125,   125,   125,   125,
      85,  -112,    47,   102,  -112,    81,  -112,  -112,   102,   -15,
     -15,  -112,  -112,  -112,    70,  -112,    25,    25,    25,    25,
    -112,  -112,   108,  -112,   -13,  -112,   159,   159,  -112,    91,
    -112,  -112,   173,    93,    94,   106,   102,   119,  -112,   120,
    -112,   103,  -112,    51,  -112,  -112,   122,   159,  -112,   104,
    -112
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     0,     0,     0,     0,     0,     4,
      21,     0,     6,    12,    11,    13,    14,     8,     7,     0,
       9,    10,     1,    18,    19,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     5,     0,     0,    32,    33,
      34,     0,    68,    37,    67,    70,    71,     0,     0,     0,
       0,     0,     0,    69,    39,    58,    61,    68,    69,     0,
      48,    49,    51,    53,     0,     0,    35,    43,     3,    36,
      15,     0,    66,     0,    64,    65,     0,     0,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,    23,    28,     0,    73,    38,    42,    59,
      60,    62,    63,    15,    50,    52,    56,    57,    54,    55,
      15,    29,     0,    16,     0,    72,     4,     4,    31,     0,
      15,    22,    47,     0,     0,     0,    17,    44,    46,     0,
      24,     0,    26,     0,    15,    25,     0,     4,    27,     0,
      45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -112,  -112,    36,   -10,   -67,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,    67,  -112,    -1,  -112,
    -112,  -111,   -27,  -112,    83,    66,   -26,    27,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,   122,    12,    93,    13,    26,    14,   114,   121,
     133,    15,    16,    92,    41,    17,    52,    18,    58,    20,
      21,   123,    59,    60,    61,    62,    63,    55,    56
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,    35,    54,    64,    66,   119,   124,   -40,    19,    69,
      19,    98,    72,    27,    74,    75,     1,    77,    81,    82,
     -40,    32,   -41,    35,    76,   120,   139,    53,    34,     3,
      78,    22,    19,    36,     4,   -41,   116,    11,     5,     6,
      28,     7,     8,   117,    94,    33,   101,   102,    29,    31,
      30,    54,    37,   126,    10,    32,    79,    80,    68,     3,
     106,   107,   108,   109,     4,    70,    67,   137,     5,     6,
      83,     7,     8,    38,    39,    40,    53,    42,    43,    44,
      71,    45,    46,    73,    10,    84,    47,    48,   111,   112,
      49,    50,   135,   136,    32,    57,    85,    44,   130,    45,
      46,    90,    51,    91,    47,    48,    99,   100,    49,    50,
      95,    23,    35,    24,    25,    19,    19,    65,    96,   103,
      51,    19,   110,   113,    57,   115,    44,   118,    45,    46,
     125,   127,   128,    47,    48,   131,    19,    49,    50,   132,
     134,   138,   140,    57,    97,    44,   129,    45,    46,    51,
       3,   105,    47,    48,     0,     4,    49,    50,     0,     5,
       6,     0,     7,     8,     3,     0,     9,   104,    51,     4,
       0,     0,     0,     5,     6,    10,     7,     8,     3,     0,
     113,     0,     0,     4,     0,     0,     0,     5,     6,    10,
       7,     8,     0,    86,     0,     0,     0,     0,    87,     0,
      79,    80,     0,    10,    88,    89
};

static const yytype_int16 yycheck[] =
{
       1,    11,    28,    30,    31,    18,   117,    31,     9,    36,
      11,    78,    47,    18,    49,    50,     3,    31,    33,    34,
      44,    45,    31,    33,    51,    38,   137,    28,     4,     5,
      44,     0,    33,    39,    10,    44,   103,     1,    14,    15,
      43,    17,    18,   110,    71,     9,    81,    82,    43,    39,
      43,    77,    18,   120,    30,    45,    31,    32,     4,     5,
      86,    87,    88,    89,    10,    37,    18,   134,    14,    15,
      44,    17,    18,    11,    12,    13,    77,    18,    19,    20,
      39,    22,    23,    43,    30,    25,    27,    28,    41,    42,
      31,    32,    41,    42,    45,    18,    26,    20,   125,    22,
      23,    44,    43,    19,    27,    28,    79,    80,    31,    32,
      20,     6,   122,     8,     9,   116,   117,    40,    44,    37,
      43,   122,    37,    21,    18,    44,    20,    19,    22,    23,
      39,    38,    38,    27,    28,    16,   137,    31,    32,    19,
      37,    19,    38,    18,    77,    20,    40,    22,    23,    43,
       5,    85,    27,    28,    -1,    10,    31,    32,    -1,    14,
      15,    -1,    17,    18,     5,    -1,    21,    84,    43,    10,
      -1,    -1,    -1,    14,    15,    30,    17,    18,     5,    -1,
      21,    -1,    -1,    10,    -1,    -1,    -1,    14,    15,    30,
      17,    18,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,
      31,    32,    -1,    30,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    47,     5,    10,    14,    15,    17,    18,    21,
      30,    48,    49,    51,    53,    57,    58,    61,    63,    64,
      65,    66,     0,     6,     8,     9,    52,    18,    43,    43,
      43,    39,    45,    48,     4,    49,    39,    18,    11,    12,
      13,    60,    18,    19,    20,    22,    23,    27,    28,    31,
      32,    43,    62,    64,    72,    73,    74,    18,    64,    68,
      69,    70,    71,    72,    68,    40,    68,    18,     4,    68,
      37,    39,    74,    43,    74,    74,    68,    31,    44,    31,
      32,    33,    34,    44,    25,    26,    24,    29,    35,    36,
      44,    19,    59,    50,    68,    20,    44,    62,    50,    73,
      73,    74,    74,    37,    70,    71,    72,    72,    72,    72,
      37,    41,    42,    21,    54,    44,    50,    50,    19,    18,
      38,    55,    48,    67,    67,    39,    50,    38,    38,    40,
      68,    16,    19,    56,    37,    41,    42,    50,    19,    67,
      38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    50,    50,    51,    52,    52,
      52,    53,    54,    54,    55,    55,    56,    56,    57,    58,
      59,    59,    60,    60,    60,    61,    61,    62,    62,    62,
      62,    62,    63,    64,    65,    65,    66,    67,    68,    69,
      69,    70,    70,    71,    71,    71,    71,    71,    72,    72,
      72,    73,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     4,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     8,     1,     1,
       1,     1,     2,     0,     3,     5,     1,     3,     5,     5,
       1,     3,     1,     1,     1,     3,     3,     1,     3,     1,
       1,     1,     5,     3,     8,    13,     8,     1,     1,     1,
       3,     1,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     2,     2,     2,     1,     1,     1,
       1,     1,     4,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: CAMPANHA statements FIM_CAMPANHA  */
#line 268 "src/parser.y"
        {
            block_list_t* bl = (yyvsp[-1].block_list);
            for (int i = 0; i < bl->count; i++) {
                printf("[DEBUG] Executando bloco %d\n", i);
                bl->fns[i]();
            }
            //free(bl);
            printf("Campanha finalizada!\n");
            printf("[DEBUG] Fim do programa\n");
        }
#line 1473 "parser.tab.c"
    break;

  case 3: /* program: CAMPANHA NEWLINE statements FIM_CAMPANHA  */
#line 279 "src/parser.y"
        {
            block_list_t* bl = (yyvsp[-1].block_list);
            for (int i = 0; i < bl->count; i++) {
                printf("[DEBUG] Executando bloco %d\n", i);
                bl->fns[i]();
            }
            free(bl);
            printf("Campanha finalizada!\n");
            printf("[DEBUG] Fim do programa\n");
        }
#line 1488 "parser.tab.c"
    break;

  case 4: /* statements: %empty  */
#line 293 "src/parser.y"
        {
            block_list_t* bl = malloc(sizeof(block_list_t));
            bl->count = 0;
            (yyval.block_list) = bl;
        }
#line 1498 "parser.tab.c"
    break;

  case 5: /* statements: statements statement  */
#line 299 "src/parser.y"
        {
            block_list_t* bl = (yyvsp[-1].block_list);
            if ((yyvsp[0].block_fn)) {
                if (bl->count < 1024) {
                    bl->fns[bl->count++] = (yyvsp[0].block_fn);
                }
            }
            (yyval.block_list) = bl;
        }
#line 1512 "parser.tab.c"
    break;

  case 6: /* statements: statement  */
#line 309 "src/parser.y"
        {
            block_list_t* bl = malloc(sizeof(block_list_t));
            bl->count = 0;
            if ((yyvsp[0].block_fn)) bl->fns[bl->count++] = (yyvsp[0].block_fn);
            (yyval.block_list) = bl;
        }
#line 1523 "parser.tab.c"
    break;

  case 7: /* statement: narrate_stmt  */
#line 318 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1529 "parser.tab.c"
    break;

  case 8: /* statement: assign_stmt  */
#line 319 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1535 "parser.tab.c"
    break;

  case 9: /* statement: if_stmt  */
#line 320 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1541 "parser.tab.c"
    break;

  case 10: /* statement: while_stmt  */
#line 321 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1547 "parser.tab.c"
    break;

  case 11: /* statement: obstaculo_stmt  */
#line 322 "src/parser.y"
                     { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1553 "parser.tab.c"
    break;

  case 12: /* statement: entity_decl  */
#line 323 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1559 "parser.tab.c"
    break;

  case 13: /* statement: var_decl  */
#line 324 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1565 "parser.tab.c"
    break;

  case 14: /* statement: jogadores_decl  */
#line 325 "src/parser.y"
                     { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1571 "parser.tab.c"
    break;

  case 17: /* entity_decl: CRIAR entity_type IDENTIFIER '{' opt_newline attribute_assigns '}' opt_newline  */
#line 335 "src/parser.y"
        {
            // Processa imediatamente durante o parsing
            padrao.definido = 1;
            
            if (strcmp((yyvsp[-6].str), "personagem") == 0) {
                criar_personagem((yyvsp[-5].str), &padrao);
                printf("Personagem %s criado!\n", (yyvsp[-5].str));
            } else if (strcmp((yyvsp[-6].str), "monstro") == 0) {
                criar_monstro((yyvsp[-5].str), &padrao);
                printf("Monstro %s criado!\n", (yyvsp[-5].str));
            } else if (strcmp((yyvsp[-6].str), "item") == 0) {
                criar_item((yyvsp[-5].str), &padrao);
                printf("Item %s criado!\n", (yyvsp[-5].str));
            }
            
            // Limpa o padrao global para próxima entidade
            memset(&padrao, 0, sizeof(padrao));
            
            free((yyvsp[-6].str));
            free((yyvsp[-5].str));
            
            // Retorna uma função vazia
            void fn(void) {
                // Função vazia - o processamento já foi feito
            }
            (yyval.block_fn) = fn;
        }
#line 1603 "parser.tab.c"
    break;

  case 18: /* entity_type: PERSONAGEM  */
#line 364 "src/parser.y"
                 { (yyval.str) = strdup("personagem"); }
#line 1609 "parser.tab.c"
    break;

  case 19: /* entity_type: MONSTRO  */
#line 365 "src/parser.y"
                 { (yyval.str) = strdup("monstro"); }
#line 1615 "parser.tab.c"
    break;

  case 20: /* entity_type: ITEM  */
#line 366 "src/parser.y"
                 { (yyval.str) = strdup("item"); }
#line 1621 "parser.tab.c"
    break;

  case 21: /* obstaculo_stmt: OBSTACULO  */
#line 371 "src/parser.y"
        {
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement obstaculo\n");
                print_slow("Um obstáculo apareceu! Pressione Enter para continuar...", 10000);
                getchar();
            }
            (yyval.block_fn) = fn;
        }
#line 1634 "parser.tab.c"
    break;

  case 24: /* attribute_assign: IDENTIFIER '=' expression  */
#line 388 "src/parser.y"
        {
            char* attr_name = (yyvsp[-2].str); // Captura o nome do atributo (strdup'd pelo lexer)
            char buffer[128];

            // Adiciona/atualiza atributo no padrao
            int found = 0;
            for (int i = 0; i < padrao.attr_count; i++) {
                if (strcmp(padrao.atributos[i].nome, attr_name) == 0) {
                    padrao.atributos[i].valor = (yyvsp[0].int_val);
                    found = 1;
                    break;
                }
            }
            if (!found && padrao.attr_count < MAX_ATTRS) {
                strncpy(padrao.atributos[padrao.attr_count].nome, attr_name, 63);
                padrao.atributos[padrao.attr_count].nome[63] = '\0';
                padrao.atributos[padrao.attr_count].valor = (yyvsp[0].int_val);
                padrao.attr_count++;
            }
            snprintf(buffer, sizeof(buffer), "  - Atributo %s definido.", attr_name);
            print_slow(buffer, 10000);
            free(attr_name); // Libera o nome do atributo
        }
#line 1662 "parser.tab.c"
    break;

  case 25: /* attribute_assign: IDENTIFIER '=' '[' string_list ']'  */
#line 412 "src/parser.y"
        {
            char* attr_name = (yyvsp[-4].str); // Captura o nome do atributo (strdup'd pelo lexer)
            char* sl_value = (yyvsp[-1].str);  // Captura o valor da string_list
            char buffer[128];

            if (padrao.definido && strcmp(attr_name, "inventario") == 0) {
                if (padrao.inventario) free(padrao.inventario);
                padrao.inventario = strdup(sl_value); // padrao.inventario faz sua própria cópia
            }
            snprintf(buffer, sizeof(buffer), "  - Atributo %s definido (lista: %s).", attr_name, sl_value);
            print_slow(buffer, 10000);
            free(attr_name); // Libera o nome do atributo
            free(sl_value);  // Libera a string retornada por string_list
        }
#line 1681 "parser.tab.c"
    break;

  case 26: /* string_list: STRING_LITERAL  */
#line 430 "src/parser.y"
        { (yyval.str) = (yyvsp[0].str); }
#line 1687 "parser.tab.c"
    break;

  case 27: /* string_list: string_list ',' STRING_LITERAL  */
#line 432 "src/parser.y"
        {
            char* prev_list = (yyvsp[-2].str);
            char* new_item = (yyvsp[0].str);
            size_t len = strlen(prev_list) + strlen(new_item) + 3; // para ", " e '\0'
            (yyval.str) = malloc(len);
            if ((yyval.str)) {
                snprintf((yyval.str), len, "%s, %s", prev_list, new_item);
            } else {
                yyerror("malloc failed in string_list concatenation");
                (yyval.str) = strdup(""); // Evitar NULL
            }
            free(prev_list); // Libera a lista anterior
            free(new_item);  // Libera o novo item (que veio do lexer)
        }
#line 1706 "parser.tab.c"
    break;

  case 28: /* var_decl: DEFINIR IDENTIFIER type_decl '=' expression  */
#line 450 "src/parser.y"
        {
            char* var_name = (yyvsp[-3].str); // Captura o nome da variável (strdup'd pelo lexer)
            char* type_name = (yyvsp[-2].str); // String literal de type_decl, não precisa de free
            int val_expr = (yyvsp[0].int_val);
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement var_decl\n");
                char buffer[128];
                set_var(var_name, val_expr); // set_var faz sua própria cópia (strncpy)
                snprintf(buffer, sizeof(buffer), "Variável definida: %s (%s)", var_name, type_name);
                print_slow(buffer, 10000);
                free(var_name); // Libera o nome da variável
            }
            (yyval.block_fn) = fn;
        }
#line 1725 "parser.tab.c"
    break;

  case 29: /* jogadores_decl: IDENTIFIER '=' '[' name_list ']'  */
#line 468 "src/parser.y"
        {
            char* lista_nome = (yyvsp[-4].str); // Captura o nome da lista (strdup'd pelo lexer)
            char* nomes_jogadores = (yyvsp[-1].str); // String de name_list (malloc'd)
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement jogadores\n");
                char buffer[128];
                // Se 'lista_nome' fosse usado para armazenar a lista em algum lugar,
                // a lógica de free seria diferente. Aqui, assumimos que é apenas para o print.
                snprintf(buffer, sizeof(buffer), "Jogadores definidos para a lista '%s': %s", lista_nome, nomes_jogadores);
                print_slow(buffer, 10000);
                free(lista_nome); // Libera o nome da lista
                free(nomes_jogadores); // Libera a string concatenada de name_list
            }
            (yyval.block_fn) = fn;
        }
#line 1745 "parser.tab.c"
    break;

  case 30: /* name_list: STRING_LITERAL  */
#line 487 "src/parser.y"
        { (yyval.str) = (yyvsp[0].str); }
#line 1751 "parser.tab.c"
    break;

  case 31: /* name_list: name_list ',' STRING_LITERAL  */
#line 489 "src/parser.y"
        {
            char* prev_list = (yyvsp[-2].str);
            char* new_item = (yyvsp[0].str);
            size_t len = strlen(prev_list) + strlen(new_item) + 3; // para ", " e '\0'
            (yyval.str) = malloc(len);
            if ((yyval.str)) {
                snprintf((yyval.str), len, "%s, %s", prev_list, new_item);
            } else {
                yyerror("malloc failed in name_list concatenation");
                (yyval.str) = strdup(""); // Evitar NULL
            }
            free(prev_list); // Libera a lista anterior
            free(new_item);  // Libera o novo item (que veio do lexer e foi copiado para $$)
        }
#line 1770 "parser.tab.c"
    break;

  case 32: /* type_decl: INT  */
#line 506 "src/parser.y"
           { (yyval.str) = "int"; }
#line 1776 "parser.tab.c"
    break;

  case 33: /* type_decl: STRING  */
#line 507 "src/parser.y"
             { (yyval.str) = "string"; }
#line 1782 "parser.tab.c"
    break;

  case 34: /* type_decl: BOOL  */
#line 508 "src/parser.y"
             { (yyval.str) = "bool"; }
#line 1788 "parser.tab.c"
    break;

  case 35: /* assign_stmt: IDENTIFIER '=' expression  */
#line 513 "src/parser.y"
        {
            char* var_name = (yyvsp[-2].str); // Captura o nome da variável (strdup'd pelo lexer)
            int val_expr = (yyvsp[0].int_val);
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement assign_stmt 1\n");
                char buffer[128];
                set_var(var_name, val_expr); // set_var faz sua própria cópia (strncpy)
                snprintf(buffer, sizeof(buffer), "Variável %s atualizada.", var_name);
                print_slow(buffer, 10000);
                free(var_name); // Libera o nome da variável
            }
            (yyval.block_fn) = fn;
        }
#line 1806 "parser.tab.c"
    break;

  case 36: /* assign_stmt: attr_access '=' expression  */
#line 527 "src/parser.y"
        {
            // $1 é par_nome_attr. $1.personagem e $1.atributo são strdup'd pelo lexer
            char* p_nome = (yyvsp[-2].par_nome_attr).personagem;
            char* a_nome = (yyvsp[-2].par_nome_attr).atributo;
            int val_expr = (yyvsp[0].int_val);
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement assign_stmt 2\n");
                char buffer[128];
                set_personagem_attr(p_nome, a_nome, val_expr); // set_personagem_attr faz cópias (strncpy)
                snprintf(buffer, sizeof(buffer), "Atributo %s de %s atualizado.", a_nome, p_nome);
                print_slow(buffer, 10000);
                free(p_nome); // Libera o nome do personagem
                free(a_nome);   // Libera o nome do atributo
            }
            (yyval.block_fn) = fn;
        }
#line 1827 "parser.tab.c"
    break;

  case 37: /* narrate_expr: STRING_LITERAL  */
#line 547 "src/parser.y"
        { (yyval.str) = (yyvsp[0].str); }
#line 1833 "parser.tab.c"
    break;

  case 38: /* narrate_expr: narrate_expr '+' narrate_expr  */
#line 549 "src/parser.y"
        {
            size_t len = strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 1;
            (yyval.str) = malloc(len);
            if ((yyval.str)) {
                snprintf((yyval.str), len, "%s%s", (yyvsp[-2].str), (yyvsp[0].str));
            } else {
                yyerror("malloc failed in narrate_expr concatenation");
                (yyval.str) = strdup("");
            }
            free((yyvsp[-2].str));
            free((yyvsp[0].str));
        }
#line 1850 "parser.tab.c"
    break;

  case 39: /* narrate_expr: expr  */
#line 562 "src/parser.y"
        {
            char buffer[128];
            sprintf(buffer, "%d", (yyvsp[0].int_val)); // $1 é o valor da expressão aritmética
            (yyval.str) = strdup(buffer);
        }
#line 1860 "parser.tab.c"
    break;

  case 40: /* narrate_expr: IDENTIFIER  */
#line 568 "src/parser.y"
        {
            char buffer[128];
            sprintf(buffer, "%d", get_var((yyvsp[0].str)));
            (yyval.str) = strdup(buffer);
            free((yyvsp[0].str));
        }
#line 1871 "parser.tab.c"
    break;

  case 41: /* narrate_expr: attr_access  */
#line 575 "src/parser.y"
        {
            char buffer[128];
            sprintf(buffer, "%d", get_personagem_attr((yyvsp[0].par_nome_attr).personagem, (yyvsp[0].par_nome_attr).atributo));
            (yyval.str) = strdup(buffer);
            free((yyvsp[0].par_nome_attr).personagem);
            free((yyvsp[0].par_nome_attr).atributo);
        }
#line 1883 "parser.tab.c"
    break;

  case 42: /* narrate_stmt: NARRAR '(' narrate_expr ')' opt_newline  */
#line 586 "src/parser.y"
    {
        char* texto = (yyvsp[-2].str); // $3 já é malloc'd e pronto para uso

        void fn(void) {
            printf("[DEBUG] Entrou no fn do statement narrate\n");
            print_slow(texto, 10000);
        }
        (yyval.block_fn) = fn;
    }
#line 1897 "parser.tab.c"
    break;

  case 43: /* attr_access: IDENTIFIER '.' IDENTIFIER  */
#line 598 "src/parser.y"
        {
            (yyval.par_nome_attr).personagem = (yyvsp[-2].str);
            (yyval.par_nome_attr).atributo = (yyvsp[0].str);
        }
#line 1906 "parser.tab.c"
    break;

  case 44: /* if_stmt: SE '(' expression ')' '{' opt_newline block '}'  */
#line 606 "src/parser.y"
        {
            int cond = (yyvsp[-5].int_val);
            block_list_t* if_block = (yyvsp[-1].block_list); // Captura o block_list_t*
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement if 1\n");
                if (cond) {
                    for (int i = 0; i < if_block->count; i++) {
                        if_block->fns[i]();
                    }
                }
                free(if_block); // Libera o block_list_t do corpo do if
            }
            (yyval.block_fn) = fn;
        }
#line 1925 "parser.tab.c"
    break;

  case 45: /* if_stmt: SE '(' expression ')' '{' opt_newline block '}' SENAO '{' opt_newline block '}'  */
#line 621 "src/parser.y"
        {
            int cond = (yyvsp[-10].int_val);
            block_list_t* if_block = (yyvsp[-6].block_list);   // Captura o block_list_t* do if
            block_list_t* else_block = (yyvsp[-1].block_list); // Captura o block_list_t* do else
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement if 2\n");
                if (cond) {
                    for (int i = 0; i < if_block->count; i++) {
                        if_block->fns[i]();
                    }
                } else {
                    for (int i = 0; i < else_block->count; i++) {
                        else_block->fns[i]();
                    }
                }
                free(if_block);   // Libera o block_list_t do corpo do if
                free(else_block); // Libera o block_list_t do corpo do else
            }
            (yyval.block_fn) = fn;
        }
#line 1950 "parser.tab.c"
    break;

  case 46: /* while_stmt: ENQUANTO '(' expression ')' '{' opt_newline block '}'  */
#line 645 "src/parser.y"
        {
            // A expressão $3 pode precisar ser reavaliada a cada iteração.
            // Se a expressão em si não aloca memória que precisa ser liberada por iteração,
            // e os IDENTIFIERs dentro dela são tratados pelo 'factor', está OK.
            // O $7 é o block_list_t* do corpo.
            block_list_t* loop_block = (yyvsp[-1].block_list); // Captura o block_list_t*
            // Para reavaliar a condição, precisaríamos de uma forma de re-executar a lógica de $3.
            // A forma como 'expression' está definida (retornando int_val) não permite
            // reavaliação direta sem re-parsear ou ter uma função para a expressão.
            // Assumindo que $3 é avaliado uma vez para o propósito desta estrutura de `fn`.
            // Para um `while` real, a condição ($3) precisaria ser uma função ou re-avaliada.
            // Para simplificar e manter a estrutura atual de `fn`:
            // Esta implementação de while com `fn` só executará o loop com base na avaliação inicial de $3.
            // Para um while dinâmico, a estrutura da ação precisaria ser diferente,
            // possivelmente não retornando uma única `fn` para o statement list,
            // ou a `fn` precisaria de acesso para re-avaliar a expressão.

            // Dada a estrutura atual, vamos focar em liberar o loop_block.
            // A lógica do while em si, com reavaliação da condição, é mais complexa
            // de implementar com este padrão de `void fn(void)`.
            // A correção abaixo foca na memória do bloco.
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement while\n");
                // Esta é uma simplificação. Um while real precisaria reavaliar $3.
                // if ($3) { // Executa uma vez se a condição inicial for verdadeira
                //    for (int i = 0; i < loop_block->count; i++) {
                //        loop_block->fns[i]();
                //    }
                // }
                // Para um while que realmente itera, a lógica seria:
                // while (evaluate_expression_again_somehow($3_original_syntax_tree_or_function)) { // Placeholder
                //     for (int i = 0; i < loop_block->count; i++) {
                //         loop_block->fns[i]();
                //     }
                //}
                // Como não temos evaluate_expression_again_somehow, e $3 é só um int aqui:
                // A implementação atual do while só pode verificar a condição uma vez.
                // Se você quer um loop real, a gramática/ações para 'expression' e 'while_stmt'
                // precisariam ser mais sofisticadas (ex: expression retorna uma função que avalia).

                // Focando na memória do bloco $7:
                // Se o while fosse executado, o bloco seria usado.
                // Independentemente de quantas vezes (ou se) o loop roda, o bloco precisa ser liberado.
                // A lógica de execução do loop está comentada porque $3 é um int fixo aqui.
                // Se você tem uma forma de reavaliar a expressão, descomente e adapte.
                // Por agora, apenas liberamos o bloco.
                free(loop_block);
            }
            (yyval.block_fn) = fn;
        }
#line 2005 "parser.tab.c"
    break;

  case 47: /* block: statements  */
#line 698 "src/parser.y"
               { (yyval.block_list) = (yyvsp[0].block_list); }
#line 2011 "parser.tab.c"
    break;

  case 59: /* expr: expr '+' term  */
#line 725 "src/parser.y"
                    { (yyval.int_val) = (yyvsp[-2].int_val) + (yyvsp[0].int_val); }
#line 2017 "parser.tab.c"
    break;

  case 60: /* expr: expr '-' term  */
#line 726 "src/parser.y"
                    { (yyval.int_val) = (yyvsp[-2].int_val) - (yyvsp[0].int_val); }
#line 2023 "parser.tab.c"
    break;

  case 62: /* term: term '*' factor  */
#line 731 "src/parser.y"
                      { (yyval.int_val) = (yyvsp[-2].int_val) * (yyvsp[0].int_val); }
#line 2029 "parser.tab.c"
    break;

  case 63: /* term: term '/' factor  */
#line 732 "src/parser.y"
                      { (yyval.int_val) = (yyvsp[-2].int_val) / (yyvsp[0].int_val); }
#line 2035 "parser.tab.c"
    break;

  case 64: /* factor: '+' factor  */
#line 736 "src/parser.y"
                       { (yyval.int_val) = +(yyvsp[0].int_val); }
#line 2041 "parser.tab.c"
    break;

  case 65: /* factor: '-' factor  */
#line 737 "src/parser.y"
                       { (yyval.int_val) = -(yyvsp[0].int_val); }
#line 2047 "parser.tab.c"
    break;

  case 66: /* factor: NAO factor  */
#line 738 "src/parser.y"
                       { (yyval.int_val) = !(yyvsp[0].int_val); }
#line 2053 "parser.tab.c"
    break;

  case 67: /* factor: INTEGER  */
#line 739 "src/parser.y"
                       { (yyval.int_val) = (yyvsp[0].int_val); }
#line 2059 "parser.tab.c"
    break;

  case 68: /* factor: IDENTIFIER  */
#line 741 "src/parser.y"
        {
            char* name = (yyvsp[0].str); // strdup'd pelo lexer
            (yyval.int_val) = get_var(name);
            free(name); // Libera o nome da variável
        }
#line 2069 "parser.tab.c"
    break;

  case 69: /* factor: attr_access  */
#line 747 "src/parser.y"
        {
            // $1 é par_nome_attr. $1.personagem e $1.atributo são strdup'd pelo lexer
            char* p_nome = (yyvsp[0].par_nome_attr).personagem;
            char* a_nome = (yyvsp[0].par_nome_attr).atributo;
            (yyval.int_val) = get_personagem_attr(p_nome, a_nome);
            free(p_nome); // Libera o nome do personagem
            free(a_nome);   // Libera o nome do atributo
        }
#line 2082 "parser.tab.c"
    break;

  case 70: /* factor: VERDADEIRO  */
#line 755 "src/parser.y"
                       { (yyval.int_val) = 1; }
#line 2088 "parser.tab.c"
    break;

  case 71: /* factor: FALSO  */
#line 756 "src/parser.y"
                       { (yyval.int_val) = 0; }
#line 2094 "parser.tab.c"
    break;

  case 72: /* factor: ROLAR_DADO '(' INTEGER ')'  */
#line 758 "src/parser.y"
        {
            int resultado = (rand() % (yyvsp[-1].int_val)) + 1;
            printf("Rolagem de dado d%d: %d\n", (yyvsp[-1].int_val), resultado);
            (yyval.int_val) = resultado;
        }
#line 2104 "parser.tab.c"
    break;

  case 73: /* factor: '(' expression ')'  */
#line 763 "src/parser.y"
                         { (yyval.int_val) = (yyvsp[-1].int_val); }
#line 2110 "parser.tab.c"
    break;


#line 2114 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 766 "src/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
