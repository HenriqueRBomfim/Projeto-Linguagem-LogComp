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

Personagem personagens[MAX_PERSONAGENS];
int personagem_count = 0;

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

extern FILE *yyin;
void yyerror(const char *s);
int yylex(void);

#line 227 "parser.tab.c"

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
  YYSYMBOL_narrate_stmt = 62,              /* narrate_stmt  */
  YYSYMBOL_attr_access = 63,               /* attr_access  */
  YYSYMBOL_if_stmt = 64,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 65,                /* while_stmt  */
  YYSYMBOL_block = 66,                     /* block  */
  YYSYMBOL_expression = 67,                /* expression  */
  YYSYMBOL_bexpression = 68,               /* bexpression  */
  YYSYMBOL_bterm = 69,                     /* bterm  */
  YYSYMBOL_rexp = 70,                      /* rexp  */
  YYSYMBOL_expr = 71,                      /* expr  */
  YYSYMBOL_term = 72,                      /* term  */
  YYSYMBOL_factor = 73                     /* factor  */
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
#define YYLAST   175

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

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
       0,   198,   198,   209,   224,   229,   239,   249,   250,   251,
     252,   253,   254,   255,   256,   259,   261,   265,   276,   317,
     339,   340,   341,   345,   357,   358,   362,   386,   404,   406,
     424,   442,   461,   463,   481,   482,   483,   487,   501,   555,
     568,   576,   591,   615,   669,   673,   677,   678,   682,   683,
     687,   688,   689,   690,   691,   695,   696,   697,   701,   702,
     703,   707,   708,   709,   710,   711,   717,   726,   727,   728,
     734
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
  "narrate_stmt", "attr_access", "if_stmt", "while_stmt", "block",
  "expression", "bexpression", "bterm", "rexp", "expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-116)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   114,    29,   134,    24,    12,    18,    21,   -17,   145,
    -116,    16,  -116,  -116,  -116,  -116,  -116,  -116,  -116,     8,
    -116,  -116,  -116,    61,  -116,  -116,    54,   153,    55,    17,
      17,    53,    71,    52,  -116,  -116,    17,     1,    60,  -116,
    -116,  -116,    62,    48,    69,  -116,  -116,  -116,    17,    78,
      17,    17,    17,  -116,    81,    79,   100,  -116,    59,    44,
    -116,    83,   111,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
      17,  -116,  -116,   113,  -116,  -116,    90,   102,    17,    17,
      17,    17,    17,    17,    17,    17,    17,    17,   110,  -116,
       9,   116,   116,   116,  -116,   116,   107,  -116,  -116,   100,
    -116,    27,    27,    44,    44,    27,    27,  -116,  -116,  -116,
    -116,   135,  -116,   -11,    -2,  -116,   131,   131,  -116,   117,
    -116,  -116,  -116,   145,   115,   119,    80,   116,   116,   142,
    -116,   148,  -116,   132,  -116,    45,  -116,  -116,   149,   131,
    -116,   133,  -116
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     0,     0,     0,     0,     0,     4,
      23,     0,     6,    12,    11,    13,    14,     8,     7,     0,
       9,    10,     1,    20,    21,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     5,     0,     0,     0,    34,
      35,    36,     0,     0,    65,    64,    67,    68,     0,     0,
       0,     0,     0,    66,     0,    45,    46,    48,    50,    55,
      58,     0,     0,    37,    40,     3,    38,    15,    15,    15,
       0,    15,    63,     0,    61,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
       0,    18,    25,    25,    30,    39,     0,    70,    15,    47,
      49,    53,    54,    56,    57,    51,    52,    59,    60,    15,
      31,     0,    16,     0,     0,    69,     4,     4,    33,     0,
      15,    24,    15,    44,     0,     0,     0,    17,    19,    41,
      43,     0,    26,     0,    28,     0,    15,    27,     0,     4,
      29,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -116,  -116,     4,   -10,   -57,  -116,  -116,  -116,    77,  -116,
    -116,  -116,  -116,  -116,  -116,  -116,  -116,    -1,  -116,  -116,
    -115,   -27,  -116,    94,    95,    25,    35,   -33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,   123,    12,    91,    13,    26,    14,   113,   121,
     135,    15,    16,    90,    42,    17,    18,    53,    20,    21,
     124,    54,    55,    56,    57,    58,    59,    60
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      19,    35,   125,    61,    63,    11,     1,   119,    19,    66,
      19,    92,    93,    33,    95,    72,   119,    74,    75,    67,
      34,     3,    31,    35,   141,    76,     4,   120,    32,    22,
       5,     6,    19,     7,     8,    44,   122,    45,    68,    46,
      47,   116,    27,    94,    48,    49,    10,    36,    50,    51,
     110,   111,   117,   107,   108,    28,    65,     3,    82,    83,
      52,    29,     4,   127,    30,   128,     5,     6,    37,     7,
       8,    44,    38,    45,    43,    46,    47,    86,    87,   139,
      48,    49,    10,    80,    50,    51,   137,   138,    81,    64,
      82,    83,    71,    62,    84,    85,    52,    69,    44,   132,
      45,    70,    46,    47,    78,   101,   102,    48,    49,   105,
     106,    50,    51,    35,    32,    19,    19,   103,   104,     3,
     131,    73,    19,    52,     4,    77,    79,    88,     5,     6,
      89,     7,     8,    96,    97,     9,     3,   112,    19,    98,
      23,     4,    24,    25,    10,     5,     6,   109,     7,     8,
       3,   115,   112,   129,   118,     4,   126,   130,   133,     5,
       6,    10,     7,     8,    39,    40,    41,   134,   140,   136,
     114,   142,    99,     0,   100,    10
};

static const yytype_int16 yycheck[] =
{
       1,    11,   117,    30,    31,     1,     3,    18,     9,    36,
      11,    68,    69,     9,    71,    48,    18,    50,    51,    18,
       4,     5,    39,    33,   139,    52,    10,    38,    45,     0,
      14,    15,    33,    17,    18,    18,    38,    20,    37,    22,
      23,    98,    18,    70,    27,    28,    30,    39,    31,    32,
      41,    42,   109,    86,    87,    43,     4,     5,    31,    32,
      43,    43,    10,   120,    43,   122,    14,    15,     7,    17,
      18,    18,    18,    20,    19,    22,    23,    33,    34,   136,
      27,    28,    30,    24,    31,    32,    41,    42,    29,    18,
      31,    32,    44,    40,    35,    36,    43,    37,    18,   126,
      20,    39,    22,    23,    25,    80,    81,    27,    28,    84,
      85,    31,    32,   123,    45,   116,   117,    82,    83,     5,
      40,    43,   123,    43,    10,    44,    26,    44,    14,    15,
      19,    17,    18,    20,    44,    21,     5,    21,   139,    37,
       6,    10,     8,     9,    30,    14,    15,    37,    17,    18,
       5,    44,    21,    38,    19,    10,    39,    38,    16,    14,
      15,    30,    17,    18,    11,    12,    13,    19,    19,    37,
      93,    38,    78,    -1,    79,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    47,     5,    10,    14,    15,    17,    18,    21,
      30,    48,    49,    51,    53,    57,    58,    61,    62,    63,
      64,    65,     0,     6,     8,     9,    52,    18,    43,    43,
      43,    39,    45,    48,     4,    49,    39,     7,    18,    11,
      12,    13,    60,    19,    18,    20,    22,    23,    27,    28,
      31,    32,    43,    63,    67,    68,    69,    70,    71,    72,
      73,    67,    40,    67,    18,     4,    67,    18,    37,    37,
      39,    44,    73,    43,    73,    73,    67,    44,    25,    26,
      24,    29,    31,    32,    35,    36,    33,    34,    44,    19,
      59,    50,    50,    50,    67,    50,    20,    44,    37,    69,
      70,    71,    71,    72,    72,    71,    71,    73,    73,    37,
      41,    42,    21,    54,    54,    44,    50,    50,    19,    18,
      38,    55,    38,    48,    66,    66,    39,    50,    50,    38,
      38,    40,    67,    16,    19,    56,    37,    41,    42,    50,
      19,    66,    38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    50,    50,    51,    51,    51,
      52,    52,    52,    53,    54,    54,    55,    55,    56,    56,
      57,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    64,    64,    65,    66,    67,    68,    68,    69,    69,
      70,    70,    70,    70,    70,    71,    71,    71,    72,    72,
      72,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     4,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     8,     5,     8,
       1,     1,     1,     1,     2,     0,     3,     5,     1,     3,
       5,     5,     1,     3,     1,     1,     1,     3,     3,     5,
       3,     8,    13,     8,     1,     1,     1,     3,     1,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     2,     2,     2,     1,     1,     1,     1,     1,     4,
       3
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
#line 199 "src/parser.y"
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
#line 1396 "parser.tab.c"
    break;

  case 3: /* program: CAMPANHA NEWLINE statements FIM_CAMPANHA  */
#line 210 "src/parser.y"
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
#line 1411 "parser.tab.c"
    break;

  case 4: /* statements: %empty  */
#line 224 "src/parser.y"
        {
            block_list_t* bl = malloc(sizeof(block_list_t));
            bl->count = 0;
            (yyval.block_list) = bl;
        }
#line 1421 "parser.tab.c"
    break;

  case 5: /* statements: statements statement  */
#line 230 "src/parser.y"
        {
            block_list_t* bl = (yyvsp[-1].block_list);
            if ((yyvsp[0].block_fn)) {
                if (bl->count < 1024) {
                    bl->fns[bl->count++] = (yyvsp[0].block_fn);
                }
            }
            (yyval.block_list) = bl;
        }
#line 1435 "parser.tab.c"
    break;

  case 6: /* statements: statement  */
#line 240 "src/parser.y"
        {
            block_list_t* bl = malloc(sizeof(block_list_t));
            bl->count = 0;
            if ((yyvsp[0].block_fn)) bl->fns[bl->count++] = (yyvsp[0].block_fn);
            (yyval.block_list) = bl;
        }
#line 1446 "parser.tab.c"
    break;

  case 7: /* statement: narrate_stmt  */
#line 249 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1452 "parser.tab.c"
    break;

  case 8: /* statement: assign_stmt  */
#line 250 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1458 "parser.tab.c"
    break;

  case 9: /* statement: if_stmt  */
#line 251 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1464 "parser.tab.c"
    break;

  case 10: /* statement: while_stmt  */
#line 252 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1470 "parser.tab.c"
    break;

  case 11: /* statement: obstaculo_stmt  */
#line 253 "src/parser.y"
                     { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1476 "parser.tab.c"
    break;

  case 12: /* statement: entity_decl  */
#line 254 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1482 "parser.tab.c"
    break;

  case 13: /* statement: var_decl  */
#line 255 "src/parser.y"
                   { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1488 "parser.tab.c"
    break;

  case 14: /* statement: jogadores_decl  */
#line 256 "src/parser.y"
                     { (yyval.block_fn) = (yyvsp[0].block_fn); }
#line 1494 "parser.tab.c"
    break;

  case 17: /* entity_decl: CRIAR PERSONAGEM PADRAO '{' opt_newline attribute_assigns '}' opt_newline  */
#line 266 "src/parser.y"
        {
            // Nenhum IDENTIFIER de nome aqui, apenas define o padrão.
            // A lógica de attribute_assigns já lida com os IDENTIFIERs de atributos.
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement entity_decl 1\n");
                padrao.definido = 1;
                print_slow("Padrão de personagem definido!", 10000);
            }
            (yyval.block_fn) = fn;
        }
#line 1509 "parser.tab.c"
    break;

  case 18: /* entity_decl: CRIAR PERSONAGEM PADRAO IDENTIFIER opt_newline  */
#line 277 "src/parser.y"
        {
            // Cria uma struct para guardar o nome, única para cada bloco
            typedef struct { char* nome; } bloco_nome_t;
            bloco_nome_t* bloco = malloc(sizeof(bloco_nome_t));
            bloco->nome = strdup((yyvsp[-1].str));
            free((yyvsp[-1].str));

            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement entity_decl 2\n");
                if (padrao.definido) {
                    criar_personagem(bloco->nome, &padrao);
                    char buffer[256];
                    snprintf(buffer, sizeof(buffer), "Personagem %s criado com padrão.", bloco->nome);
                    print_slow(buffer, 10000);
                    int idx = personagem_count - 1;
                    for (int i = 0; i < personagens[idx].attr_count; i++) {
                        snprintf(buffer, sizeof(buffer), "  [DEBUG] %s = %d", personagens[idx].atributos[i].nome, personagens[idx].atributos[i].valor);
                        print_slow(buffer, 10000);
                    }
                    if (personagens[idx].inventario) {
                        snprintf(buffer, sizeof(buffer), "  [DEBUG] Inventario: [%s]", personagens[idx].inventario);
                        print_slow(buffer, 10000);
                    }
                    for (int i = 0; i < padrao.attr_count; i++) {
                        snprintf(buffer, sizeof(buffer), "  - %s = %d", padrao.atributos[i].nome, padrao.atributos[i].valor);
                        print_slow(buffer, 10000);
                    }
                    if (padrao.inventario) {
                        snprintf(buffer, sizeof(buffer), "Inventario: [%s]", padrao.inventario);
                        print_slow(buffer, 10000);
                    }
                } else {
                    print_slow("Erro: padrão de personagem não definido!", 10000);
                }
                free(bloco->nome);
                free(bloco);
            }
            (yyval.block_fn) = fn;
        }
#line 1553 "parser.tab.c"
    break;

  case 19: /* entity_decl: CRIAR entity_type IDENTIFIER '{' opt_newline attribute_assigns '}' opt_newline  */
#line 318 "src/parser.y"
        {
            char* tipo_entidade_copiado = (yyvsp[-6].str); 
            char* nome_entidade_copiado = (yyvsp[-5].str); 
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement entity_Decl 3\n");
                char buffer[128];
                // Aqui você implementaria a lógica para criar a entidade genérica
                // Por exemplo, adicionando a uma lista de entidades, etc.
                // A função attribute_assigns já deve ter configurado os atributos
                // em alguma estrutura temporária ou diretamente na entidade se ela já foi "pré-criada".
                // Para este exemplo, apenas imprimimos.
                snprintf(buffer, sizeof(buffer), "Entidade criada: %s (%s)", nome_entidade_copiado, tipo_entidade_copiado);
                print_slow(buffer, 10000);
                // Se tipo_entidade_copiado fosse de um malloc/strdup, liberar aqui: free(tipo_entidade_copiado);
                free(nome_entidade_copiado); // Libera a cópia do nome da entidade
            }
            (yyval.block_fn) = fn;
        }
#line 1576 "parser.tab.c"
    break;

  case 20: /* entity_type: PERSONAGEM  */
#line 339 "src/parser.y"
                 { (yyval.str) = "personagem"; }
#line 1582 "parser.tab.c"
    break;

  case 21: /* entity_type: MONSTRO  */
#line 340 "src/parser.y"
                 { (yyval.str) = "monstro"; }
#line 1588 "parser.tab.c"
    break;

  case 22: /* entity_type: ITEM  */
#line 341 "src/parser.y"
                 { (yyval.str) = "item"; }
#line 1594 "parser.tab.c"
    break;

  case 23: /* obstaculo_stmt: OBSTACULO  */
#line 346 "src/parser.y"
        {
            void fn(void) {
                printf("[DEBUG] Entrou no fn do statement obstaculo\n");
                print_slow("Um obstáculo apareceu! Pressione Enter para continuar...", 10000);
                getchar();
            }
            (yyval.block_fn) = fn;
        }
#line 1607 "parser.tab.c"
    break;

  case 26: /* attribute_assign: IDENTIFIER '=' expression  */
#line 363 "src/parser.y"
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
#line 1635 "parser.tab.c"
    break;

  case 27: /* attribute_assign: IDENTIFIER '=' '[' string_list ']'  */
#line 387 "src/parser.y"
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
#line 1654 "parser.tab.c"
    break;

  case 28: /* string_list: STRING_LITERAL  */
#line 405 "src/parser.y"
        { (yyval.str) = (yyvsp[0].str); }
#line 1660 "parser.tab.c"
    break;

  case 29: /* string_list: string_list ',' STRING_LITERAL  */
#line 407 "src/parser.y"
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
#line 1679 "parser.tab.c"
    break;

  case 30: /* var_decl: DEFINIR IDENTIFIER type_decl '=' expression  */
#line 425 "src/parser.y"
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
#line 1698 "parser.tab.c"
    break;

  case 31: /* jogadores_decl: IDENTIFIER '=' '[' name_list ']'  */
#line 443 "src/parser.y"
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
#line 1718 "parser.tab.c"
    break;

  case 32: /* name_list: STRING_LITERAL  */
#line 462 "src/parser.y"
        { (yyval.str) = (yyvsp[0].str); }
#line 1724 "parser.tab.c"
    break;

  case 33: /* name_list: name_list ',' STRING_LITERAL  */
#line 464 "src/parser.y"
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
#line 1743 "parser.tab.c"
    break;

  case 34: /* type_decl: INT  */
#line 481 "src/parser.y"
           { (yyval.str) = "int"; }
#line 1749 "parser.tab.c"
    break;

  case 35: /* type_decl: STRING  */
#line 482 "src/parser.y"
             { (yyval.str) = "string"; }
#line 1755 "parser.tab.c"
    break;

  case 36: /* type_decl: BOOL  */
#line 483 "src/parser.y"
             { (yyval.str) = "bool"; }
#line 1761 "parser.tab.c"
    break;

  case 37: /* assign_stmt: IDENTIFIER '=' expression  */
#line 488 "src/parser.y"
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
#line 1779 "parser.tab.c"
    break;

  case 38: /* assign_stmt: attr_access '=' expression  */
#line 502 "src/parser.y"
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
#line 1800 "parser.tab.c"
    break;

  case 39: /* narrate_stmt: NARRAR '(' STRING_LITERAL ')' opt_newline  */
#line 556 "src/parser.y"
    {
        char* texto = strdup((yyvsp[-2].str));  // DUPLICA AQUI
        void fn(void) {
            printf("[DEBUG] Entrou no fn do statement narrate\n");
            print_slow(texto, 10000);
            free(texto);  // Libera apenas sua própria cópia
        }
        (yyval.block_fn) = fn;
        free((yyvsp[-2].str));  // Libera o original vindo do lexer
    }
#line 1815 "parser.tab.c"
    break;

  case 40: /* attr_access: IDENTIFIER '.' IDENTIFIER  */
#line 569 "src/parser.y"
        {
            (yyval.par_nome_attr).personagem = (yyvsp[-2].str);
            (yyval.par_nome_attr).atributo = (yyvsp[0].str);
        }
#line 1824 "parser.tab.c"
    break;

  case 41: /* if_stmt: SE '(' expression ')' '{' opt_newline block '}'  */
#line 577 "src/parser.y"
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
#line 1843 "parser.tab.c"
    break;

  case 42: /* if_stmt: SE '(' expression ')' '{' opt_newline block '}' SENAO '{' opt_newline block '}'  */
#line 592 "src/parser.y"
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
#line 1868 "parser.tab.c"
    break;

  case 43: /* while_stmt: ENQUANTO '(' expression ')' '{' opt_newline block '}'  */
#line 616 "src/parser.y"
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
#line 1923 "parser.tab.c"
    break;

  case 44: /* block: statements  */
#line 669 "src/parser.y"
               { (yyval.block_list) = (yyvsp[0].block_list); }
#line 1929 "parser.tab.c"
    break;

  case 56: /* expr: expr '+' term  */
#line 696 "src/parser.y"
                    { (yyval.int_val) = (yyvsp[-2].int_val) + (yyvsp[0].int_val); }
#line 1935 "parser.tab.c"
    break;

  case 57: /* expr: expr '-' term  */
#line 697 "src/parser.y"
                    { (yyval.int_val) = (yyvsp[-2].int_val) - (yyvsp[0].int_val); }
#line 1941 "parser.tab.c"
    break;

  case 59: /* term: term '*' factor  */
#line 702 "src/parser.y"
                      { (yyval.int_val) = (yyvsp[-2].int_val) * (yyvsp[0].int_val); }
#line 1947 "parser.tab.c"
    break;

  case 60: /* term: term '/' factor  */
#line 703 "src/parser.y"
                      { (yyval.int_val) = (yyvsp[-2].int_val) / (yyvsp[0].int_val); }
#line 1953 "parser.tab.c"
    break;

  case 61: /* factor: '+' factor  */
#line 707 "src/parser.y"
                       { (yyval.int_val) = +(yyvsp[0].int_val); }
#line 1959 "parser.tab.c"
    break;

  case 62: /* factor: '-' factor  */
#line 708 "src/parser.y"
                       { (yyval.int_val) = -(yyvsp[0].int_val); }
#line 1965 "parser.tab.c"
    break;

  case 63: /* factor: NAO factor  */
#line 709 "src/parser.y"
                       { (yyval.int_val) = !(yyvsp[0].int_val); }
#line 1971 "parser.tab.c"
    break;

  case 64: /* factor: INTEGER  */
#line 710 "src/parser.y"
                       { (yyval.int_val) = (yyvsp[0].int_val); }
#line 1977 "parser.tab.c"
    break;

  case 65: /* factor: IDENTIFIER  */
#line 712 "src/parser.y"
        {
            char* name = (yyvsp[0].str); // strdup'd pelo lexer
            (yyval.int_val) = get_var(name);
            free(name); // Libera o nome da variável
        }
#line 1987 "parser.tab.c"
    break;

  case 66: /* factor: attr_access  */
#line 718 "src/parser.y"
        {
            // $1 é par_nome_attr. $1.personagem e $1.atributo são strdup'd pelo lexer
            char* p_nome = (yyvsp[0].par_nome_attr).personagem;
            char* a_nome = (yyvsp[0].par_nome_attr).atributo;
            (yyval.int_val) = get_personagem_attr(p_nome, a_nome);
            free(p_nome); // Libera o nome do personagem
            free(a_nome);   // Libera o nome do atributo
        }
#line 2000 "parser.tab.c"
    break;

  case 67: /* factor: VERDADEIRO  */
#line 726 "src/parser.y"
                       { (yyval.int_val) = 1; }
#line 2006 "parser.tab.c"
    break;

  case 68: /* factor: FALSO  */
#line 727 "src/parser.y"
                       { (yyval.int_val) = 0; }
#line 2012 "parser.tab.c"
    break;

  case 69: /* factor: ROLAR_DADO '(' INTEGER ')'  */
#line 729 "src/parser.y"
        {
            int resultado = (rand() % (yyvsp[-1].int_val)) + 1;
            printf("Rolagem de dado d%d: %d\n", (yyvsp[-1].int_val), resultado);
            (yyval.int_val) = resultado;
        }
#line 2022 "parser.tab.c"
    break;

  case 70: /* factor: '(' expression ')'  */
#line 734 "src/parser.y"
                         { (yyval.int_val) = (yyvsp[-1].int_val); }
#line 2028 "parser.tab.c"
    break;


#line 2032 "parser.tab.c"

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

#line 737 "src/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
