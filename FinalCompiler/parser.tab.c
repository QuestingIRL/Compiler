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
#line 2 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "ast.h"
#include "tac.h"
#include "mips.h"
extern int yylex();
extern int yyparse();
extern FILE* yyin;

int computeEquation(struct AST* num1, struct AST* num2, char operator);
int evalCondition(struct AST* x, struct AST* y, char logOp[5]);
void yyerror(const char* s);
char currentScope[50] = "GLOBAL"; // global or the name of the function
char currReturnType[10];
int semanticCheckPassed = 1; // flags to record correctness of semantic checks
int goToElse = 0;	// is the condition of if() true?
int maxParam = 0; 	//max of 3 paramaters
int paramCount = 0;
int ifCount = 0;
int whileCount = 0;
int onWhile = 0;
int inFunction = 0;
int hasMath = 0;
char mathVal1[10]; char mathVal2[10];
char conditionString[50];

int stringCount = 0;



#line 105 "parser.tab.c"

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
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_DECIMAL = 5,                    /* DECIMAL  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_SEMICOLON = 7,                  /* SEMICOLON  */
  YYSYMBOL_EQ = 8,                         /* EQ  */
  YYSYMBOL_WRITE = 9,                      /* WRITE  */
  YYSYMBOL_SWRITE = 10,                    /* SWRITE  */
  YYSYMBOL_FUNC = 11,                      /* FUNC  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_TIMES = 17,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 18,                    /* DIVIDE  */
  YYSYMBOL_LOGIC = 19,                     /* LOGIC  */
  YYSYMBOL_LBRACKET = 20,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 21,                  /* RBRACKET  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_INT = 26,                       /* INT  */
  YYSYMBOL_CHAR = 27,                      /* CHAR  */
  YYSYMBOL_FLOAT = 28,                     /* FLOAT  */
  YYSYMBOL_RETURN = 29,                    /* RETURN  */
  YYSYMBOL_WRITELN = 30,                   /* WRITELN  */
  YYSYMBOL_CHARACTER = 31,                 /* CHARACTER  */
  YYSYMBOL_MULTIPLY = 32,                  /* MULTIPLY  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_Program = 34,                   /* Program  */
  YYSYMBOL_DeclList = 35,                  /* DeclList  */
  YYSYMBOL_Decl = 36,                      /* Decl  */
  YYSYMBOL_VarDecl = 37,                   /* VarDecl  */
  YYSYMBOL_FunDeclList = 38,               /* FunDeclList  */
  YYSYMBOL_FunDecl = 39,                   /* FunDecl  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_ParamDecList = 41,              /* ParamDecList  */
  YYSYMBOL_ParamDecListTail = 42,          /* ParamDecListTail  */
  YYSYMBOL_ParamDecl = 43,                 /* ParamDecl  */
  YYSYMBOL_Block = 44,                     /* Block  */
  YYSYMBOL_Type = 45,                      /* Type  */
  YYSYMBOL_StmtList = 46,                  /* StmtList  */
  YYSYMBOL_Stmt = 47,                      /* Stmt  */
  YYSYMBOL_IfStmt = 48,                    /* IfStmt  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_Else = 50,                      /* Else  */
  YYSYMBOL_WhileLoop = 51,                 /* WhileLoop  */
  YYSYMBOL_52_3 = 52,                      /* $@3  */
  YYSYMBOL_Condition = 53,                 /* Condition  */
  YYSYMBOL_ArrayExpr = 54,                 /* ArrayExpr  */
  YYSYMBOL_Expr = 55,                      /* Expr  */
  YYSYMBOL_FunCall = 56,                   /* FunCall  */
  YYSYMBOL_Primary = 57,                   /* Primary  */
  YYSYMBOL_MathExpr = 58,                  /* MathExpr  */
  YYSYMBOL_Trm = 59,                       /* Trm  */
  YYSYMBOL_Factor = 60,                    /* Factor  */
  YYSYMBOL_ParamList = 61,                 /* ParamList  */
  YYSYMBOL_62_4 = 62,                      /* $@4  */
  YYSYMBOL_UnaryOp = 63                    /* UnaryOp  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   134

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    89,    89,    95,   102,   107,   111,   113,   129,   168,
     215,   217,   227,   227,   297,   299,   311,   320,   332,   362,
     369,   370,   371,   376,   378,   387,   391,   393,   395,   400,
     431,   468,   477,   490,   490,   517,   519,   526,   526,   552,
     656,   690,   721,   723,   725,   727,   729,   743,   853,   869,
     873,   880,   887,   898,   900,   922,   944,   948,   962,   979,
     990,   996,  1003,  1004,  1004,  1034
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "DECIMAL", "STRING", "SEMICOLON", "EQ", "WRITE", "SWRITE", "FUNC", "IF",
  "ELSE", "WHILE", "PLUS", "MINUS", "TIMES", "DIVIDE", "LOGIC", "LBRACKET",
  "RBRACKET", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "INT", "CHAR",
  "FLOAT", "RETURN", "WRITELN", "CHARACTER", "MULTIPLY", "$accept",
  "Program", "DeclList", "Decl", "VarDecl", "FunDeclList", "FunDecl",
  "$@1", "ParamDecList", "ParamDecListTail", "ParamDecl", "Block", "Type",
  "StmtList", "Stmt", "IfStmt", "$@2", "Else", "WhileLoop", "$@3",
  "Condition", "ArrayExpr", "Expr", "FunCall", "Primary", "MathExpr",
  "Trm", "Factor", "ParamList", "$@4", "UnaryOp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,    -3,    38,   -87,   -87,    69,    80,   -17,    53,    68,
     -87,     4,   -87,   -87,   -87,    69,    41,   -87,    60,   -87,
      11,   -87,   -87,    81,    90,   -87,    49,   -87,   -87,   -87,
      87,   -87,   -87,    28,    14,   -87,    69,    79,    92,    26,
      91,    95,    96,    26,   -87,   -87,   -87,    54,    97,   -87,
     -87,   -87,   -87,    61,   -87,   -87,     4,     4,     4,     4,
     -87,    42,   -87,    82,   -87,   -87,   -87,    83,   -87,   -87,
      85,    86,    89,    26,   -87,   -87,   -87,   101,    14,    14,
     -87,   -87,   107,   104,    26,   -87,   -87,    93,    26,    98,
      94,    99,    26,   -87,   -17,    11,   -87,   -87,    93,   106,
     104,   -87,   100,   -87,   -17,   111,   102,   103,   -87,   -87,
      93,   -87,   -87,   -87,    93,   -87,   -87,   -87
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    59,    60,    50,    25,     0,     0,     0,     0,     0,
      65,     0,    20,    22,    21,     0,     0,    52,     0,     2,
       4,     6,     5,    10,     0,     7,    23,    27,    26,    44,
       0,    45,    42,    43,    53,    56,     0,     0,     0,    62,
       0,     0,     0,     0,    37,    59,    60,     0,     0,    31,
       1,     3,    11,     0,    24,    28,     0,     0,     0,     0,
      46,    59,    47,     0,    49,    51,    63,     0,    30,    32,
       0,     0,     0,     0,    61,    29,     8,     0,    55,    54,
      58,    57,     0,     0,    62,    48,    12,     0,     0,     0,
       0,     0,     0,    64,    14,     0,    33,    39,     0,     0,
      41,    40,     0,    15,    16,     0,     0,    35,    38,     9,
       0,    17,    18,    19,     0,    34,    13,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -87,   -87,   -19,   -87,   -87,   105,   -87,   -87,   -87,    15,
     -87,   -86,    -7,   108,   -87,   -87,   -87,   -87,   -87,   -87,
      45,   -87,    -2,   -87,   -37,   113,    10,    30,    46,   -87,
     -87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    18,    19,    20,    21,    22,    23,    94,   102,   103,
     104,    96,    24,    25,    26,    27,   107,   115,    28,    73,
      71,    29,    30,    31,    32,    33,    34,    35,    67,    84,
      36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      42,    51,    66,    40,   -49,    37,    72,    45,    46,    12,
      13,    14,   108,    48,     1,     2,     3,    38,     4,    39,
       5,     6,     7,     8,   116,     9,    11,    10,   117,    64,
      65,     3,    58,    11,    60,    62,    72,    12,    13,    14,
      15,    16,    17,    56,    57,   -51,    59,    66,    49,   -49,
      37,    97,     1,     2,     3,   101,     4,    17,     5,     6,
      50,     8,    82,     9,    39,    10,    78,    79,    76,    56,
      57,    11,     1,     2,     3,    43,   106,    74,    15,    16,
      17,    77,    61,     2,     3,    10,    41,   105,    80,    81,
      44,    11,     7,    53,    55,    10,    63,   105,    68,    70,
      17,    11,    69,    83,    75,    90,    85,    86,    88,    87,
      17,    91,    92,   109,   112,    99,   114,    95,    89,   111,
     100,    98,     0,   110,    47,     0,     0,   113,    52,     0,
      93,     0,     0,     0,    54
};

static const yytype_int8 yycheck[] =
{
       7,    20,    39,     5,     7,     8,    43,     3,     4,    26,
      27,    28,    98,    15,     3,     4,     5,    20,     7,    22,
       9,    10,    11,    12,   110,    14,    22,    16,   114,     3,
       4,     5,    18,    22,    36,    37,    73,    26,    27,    28,
      29,    30,    31,    15,    16,     7,    32,    84,     7,     7,
       8,    88,     3,     4,     5,    92,     7,    31,     9,    10,
       0,    12,    20,    14,    22,    16,    56,    57,     7,    15,
      16,    22,     3,     4,     5,    22,    95,    23,    29,    30,
      31,    20,     3,     4,     5,    16,     6,    94,    58,    59,
      22,    22,    11,     3,     7,    16,     4,   104,     7,     3,
      31,    22,     7,    21,     7,     4,    23,    22,    19,    23,
      31,     4,     8,     7,     3,    21,    13,    24,    73,   104,
      21,    23,    -1,    23,    11,    -1,    -1,    25,    23,    -1,
      84,    -1,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     7,     9,    10,    11,    12,    14,
      16,    22,    26,    27,    28,    29,    30,    31,    34,    35,
      36,    37,    38,    39,    45,    46,    47,    48,    51,    54,
      55,    56,    57,    58,    59,    60,    63,     8,    20,    22,
      55,     6,    45,    22,    22,     3,     4,    58,    55,     7,
       0,    35,    38,     3,    46,     7,    15,    16,    18,    32,
      55,     3,    55,     4,     3,     4,    57,    61,     7,     7,
       3,    53,    57,    52,    23,     7,     7,    20,    59,    59,
      60,    60,    20,    21,    62,    23,    22,    23,    19,    53,
       4,     4,     8,    61,    40,    24,    44,    57,    23,    21,
      21,    57,    41,    42,    43,    45,    35,    49,    44,     7,
      23,    42,     3,    25,    13,    50,    44,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    35,    36,    36,    37,    37,
      38,    38,    40,    39,    41,    41,    42,    42,    43,    44,
      45,    45,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    49,    48,    50,    50,    52,    51,    53,
      54,    54,    55,    55,    55,    55,    55,    55,    56,    57,
      57,    57,    57,    58,    58,    58,    59,    59,    59,    60,
      60,    60,    61,    62,    61,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     6,
       1,     2,     0,     8,     0,     1,     1,     2,     2,     3,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     3,
       3,     2,     3,     0,     7,     0,     2,     0,     6,     3,
       6,     6,     1,     1,     1,     1,     2,     3,     4,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     3,     1,
       1,     3,     0,     0,     3,     1
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
  switch (yykind)
    {
    case YYSYMBOL_ID: /* ID  */
#line 79 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 855 "parser.tab.c"
        break;

    case YYSYMBOL_INTEGER: /* INTEGER  */
#line 80 "parser.y"
         { fprintf(yyoutput, "%d", ((*yyvaluep).number)); }
#line 861 "parser.tab.c"
        break;

      default:
        break;
    }
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
  case 2: /* Program: DeclList  */
#line 89 "parser.y"
                 {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1253 "parser.tab.c"
    break;

  case 3: /* DeclList: Decl DeclList  */
#line 95 "parser.y"
                      { 
		// printf("\nTest debug DECLDECLLIST\n");
		(yyvsp[-1].ast)->right = (yyvsp[0].ast);
		(yyval.ast) = (yyvsp[-1].ast);
		// printf("LINK DECLLIST\n");
		// printNode($$->right);
	}
#line 1265 "parser.tab.c"
    break;

  case 4: /* DeclList: Decl  */
#line 102 "parser.y"
               {
		(yyval.ast) = (yyvsp[0].ast);
		// printf("DECL\n");
	}
#line 1274 "parser.tab.c"
    break;

  case 6: /* Decl: VarDecl  */
#line 111 "parser.y"
                {}
#line 1280 "parser.tab.c"
    break;

  case 7: /* Decl: StmtList  */
#line 113 "parser.y"
                   {
	}
#line 1287 "parser.tab.c"
    break;

  case 8: /* VarDecl: Type ID SEMICOLON  */
#line 129 "parser.y"
                          {

		printf("\nRECOGNIZED RULE: VARIABLE declaration %s\n", (yyvsp[-1].string));


		// ----- SYMBOL TABLE ----- //
		symTabAccess();
		int inSymTab = found((yyvsp[-1].string), currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		

		// ------ SEMANTIC CHECKS ------ //
		if (inSymTab == 0)  {
			addItem((yyvsp[-1].string), "VAR", (yyvsp[-2].ast)->nodeType, currentScope);
			showSymTable();
		}
		else {
			printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", (yyvsp[-1].string));
			semanticCheckPassed = 0;
		}


		// ------  AST  ------ //
		if (semanticCheckPassed) {

			(yyval.ast) = AST_Type("TYPE", (yyvsp[-2].ast)->nodeType, (yyvsp[-1].string));


			// ---- CODE GENERATION ---- //
			// code generation occurs when variable 
			// recieves a value to save space
			
		}

		semanticCheckPassed = 1;
	}
#line 1328 "parser.tab.c"
    break;

  case 9: /* VarDecl: Type ID LBRACKET INTEGER RBRACKET SEMICOLON  */
#line 168 "parser.y"
                                                      {
		
		printf("\nRECOGNIZED RULE: ARRAY declaration %s\n\n", (yyvsp[-4].string));

		// ----- SYMBOL TABLE ----- //
		symTabAccess();

		int inSymTab = found((yyvsp[-4].string), currentScope);

		if (inSymTab == 0) {
			char arrIndex[12];
			for (int i = 0; i < (yyvsp[-2].number); i++) {
				sprintf(arrIndex, "%s[%d]", (yyvsp[-4].string), i);
				addItem(arrIndex, "ARRAY", (yyvsp[-5].ast)->nodeType, currentScope);				
			}

			showSymTable();
		} else {
			printf("SEMANTIC ERROR: Var %s is already in the symbol table\n", (yyvsp[-4].string));
		}


		// ----- AST ----- //
		char intVal[50]; 
		sprintf(intVal, "%d", (yyvsp[-2].number));
		(yyval.ast) = AST_assignment("ARR", intVal, (yyvsp[-4].string));


		// ----- CODE GENERATION ----- //
		
		// ---- IR CODE ---- //
		// emitArrayDecl($2, $4);


		// ---- MIPS CODE ---- //
		emitMIPSArrayDecl((yyvsp[-4].string), (yyvsp[-2].number));

		semanticCheckPassed = 1;
	}
#line 1372 "parser.tab.c"
    break;

  case 11: /* FunDeclList: FunDecl FunDeclList  */
#line 217 "parser.y"
                              {
		

	}
#line 1381 "parser.tab.c"
    break;

  case 12: /* $@1: %empty  */
#line 227 "parser.y"
                            {

		inFunction = 1;

		printf("\nRECOGNIZED RULE: Function Declaration \"%s\"\n\n" , (yyvsp[-1].string));
		printf("ID = %s\n", (yyvsp[-1].string));
		strcpy(currentScope, (yyvsp[-1].string));
		printf("\n------------------- Scope Change --> ");
		printf("%s", currentScope);
		printf(" -------------------\n");


		// ----- SYMBOL TABLE ----- //
		symTabAccess();
		int inSymTab = found((yyvsp[-1].string), currentScope);

		// ------ SEMANTIC CHECKS ------ //
 		if (inSymTab == 0) {
			
			addItem((yyvsp[-1].string), "FUNC", (yyvsp[-2].ast)->nodeType, currentScope);

		} 
		else {
			printf("SEMANTIC ERROR: Function %s is already in the symbol table\n", (yyvsp[-2].ast)->nodeType);
			semanticCheckPassed = 0;
		}

		// ---- MIPS CODE ---- //
		if (semanticCheckPassed) {
			emitMIPSFunc((yyvsp[-1].string));
		}

		semanticCheckPassed = 1;

	}
#line 1421 "parser.tab.c"
    break;

  case 13: /* FunDecl: FUNC Type ID LPAREN $@1 ParamDecList RPAREN Block  */
#line 263 "parser.y"
                                  {

		showSymTable(); //updates for function and parameters

		// ----- AST ----- //
		if (semanticCheckPassed) {
			(yyval.ast) = AST_assignment("FUNC", (yyvsp[-6].ast)->nodeType, (yyvsp[-5].string));		

			// printNode($$);

			// ---- CODE GENERATION ---- //

			// ---- IR CODE ---- //


		}

		// Leave Function in MIPScode.h
		endOfMIPSFunction((yyvsp[-5].string));
	
		semanticCheckPassed = 1;
		inFunction = 0;
		maxParam = 0;
		paramCount = 0;

	}
#line 1452 "parser.tab.c"
    break;

  case 14: /* ParamDecList: %empty  */
#line 297 "parser.y"
                            {printf("No ParamDeclList (EPSILON)\n\n");}
#line 1458 "parser.tab.c"
    break;

  case 15: /* ParamDecList: ParamDecListTail  */
#line 299 "parser.y"
                           {
		printf("Parameters Detected--->\n");
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1467 "parser.tab.c"
    break;

  case 16: /* ParamDecListTail: ParamDecl  */
#line 311 "parser.y"
                  {	

		if (maxParam < 4) {
			maxParam++;
		} else {
			printf("WARNING!! Too many parameters in FunDecl");
		}
	}
#line 1480 "parser.tab.c"
    break;

  case 17: /* ParamDecListTail: ParamDecl ParamDecListTail  */
#line 320 "parser.y"
                                     {
		(yyvsp[-1].ast)->right = (yyvsp[0].ast); 
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 1489 "parser.tab.c"
    break;

  case 18: /* ParamDecl: Type ID  */
#line 332 "parser.y"
                {

		printf("\nRECOGNIZED RULE: Parameter VARIABLE declaration %s\n\n", (yyvsp[0].string));

		//Asher's Semantic Checks
		// ---- Symbol Table ---- //
		// symTabAccess();

		//Var Decl Check
		int inSymTab = found((yyvsp[0].string), currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);

		if (inSymTab == 0) {
			addItem((yyvsp[0].string), "PARAM", (yyvsp[-1].ast)->nodeType, currentScope);
			showSymTable();
		} 
		else {
			printf("\nSEMANTIC ERROR: Var %s is already in the symbol table\n", (yyvsp[0].string));
		} 

		emitMIPSParameters((yyvsp[0].string), paramCount);
		paramCount++;

	}
#line 1518 "parser.tab.c"
    break;

  case 19: /* Block: LBRACE DeclList RBRACE  */
#line 362 "parser.y"
                               {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 1526 "parser.tab.c"
    break;

  case 20: /* Type: INT  */
#line 369 "parser.y"
          {}
#line 1532 "parser.tab.c"
    break;

  case 21: /* Type: FLOAT  */
#line 370 "parser.y"
                {}
#line 1538 "parser.tab.c"
    break;

  case 22: /* Type: CHAR  */
#line 371 "parser.y"
               {}
#line 1544 "parser.tab.c"
    break;

  case 24: /* StmtList: Stmt StmtList  */
#line 378 "parser.y"
                        {
		(yyvsp[-1].ast)->right = (yyvsp[0].ast);
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 1553 "parser.tab.c"
    break;

  case 25: /* Stmt: SEMICOLON  */
#line 387 "parser.y"
                  {
		printf("\nRECOGNIZED RULE: SEMICOLON %s\n", (yyvsp[0].string));	
	}
#line 1561 "parser.tab.c"
    break;

  case 26: /* Stmt: WhileLoop  */
#line 391 "parser.y"
                    {}
#line 1567 "parser.tab.c"
    break;

  case 27: /* Stmt: IfStmt  */
#line 393 "parser.y"
                 {}
#line 1573 "parser.tab.c"
    break;

  case 28: /* Stmt: Expr SEMICOLON  */
#line 395 "parser.y"
                         {
		hasMath = 0;
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 1582 "parser.tab.c"
    break;

  case 29: /* Stmt: RETURN Expr SEMICOLON  */
#line 400 "parser.y"
                                {		

		printf("RETURN Statement Recognized!\n");


		// ----- AST ----- //
		(yyval.ast) = AST_assignment("RETURN", "", (yyvsp[-1].ast)->RHS);

		char *returnType = (yyvsp[-1].ast)->nodeType;
		// printf("value test = %d\n", atoi($2->RHS));
		// printf("Return type: %s\n", returnType);

		// ---- SYMBOL TABLE ---- //
	
		char val[25];
		if (!strcmp(returnType, "id")) {
			strcpy(val, getValue((yyvsp[-1].ast)->RHS, currentScope));
		} else {
			strcpy(val, (yyvsp[-1].ast)->RHS);
		}
		setItemValue(currentScope, val, currentScope);

		if (strcmp(currentScope, "main")) {
			emitMIPSReturn((yyvsp[-1].ast)->RHS, returnType);
		}

		hasMath = 0;

	}
#line 1616 "parser.tab.c"
    break;

  case 30: /* Stmt: WRITE Expr SEMICOLON  */
#line 431 "parser.y"
                               {
		printf("\nRECOGNIZED RULE: Write Statement\n");


		// ---- AST ---- //
		(yyval.ast) = AST_Write("WRITE", "", (yyvsp[-1].ast)->RHS);


		// ---- CODE GENERATION ---- //

		// ------ IR CODE ------ //
		emitIRWriteId((yyvsp[-1].ast)->RHS, getVariableType((yyvsp[-1].ast)->RHS, currentScope));
		// ------ ¯\_(ツ)_/¯ ------ //

			// ---- MIPS CODE ---- //
		
		if (!strcmp((yyvsp[-1].ast)->nodeType,"id")) {

			emitMIPSWriteId((yyvsp[-1].ast)->RHS, getVariableType((yyvsp[-1].ast)->RHS, currentScope));

		}

		else if (!strcmp((yyvsp[-1].ast)->nodeType, "int")) {

			emitMIPSWriteInt(atoi((yyvsp[-1].ast)->RHS));

		}

		else if (!strcmp((yyvsp[-1].ast)->nodeType, "char")) {

			emitMIPSWriteId((yyvsp[-1].ast)->RHS, getVariableType((yyvsp[-1].ast)->RHS, currentScope));

		}
		
	}
#line 1656 "parser.tab.c"
    break;

  case 31: /* Stmt: WRITELN SEMICOLON  */
#line 468 "parser.y"
                            {

		printf("\nRECOGNIZED RULE: Write Line %s\n", (yyvsp[-1].string));

	 	(yyval.ast) = AST_assignment("WRITELN", "", "");

		emitMIPSNewLine();
	}
#line 1669 "parser.tab.c"
    break;

  case 32: /* Stmt: SWRITE STRING SEMICOLON  */
#line 477 "parser.y"
                                  {

		printf("\nRECOGNIZED RULE: Write String %s\n", (yyvsp[-1].string));

		emitMIPSString((yyvsp[-1].string), stringCount);

		stringCount++;

	}
#line 1683 "parser.tab.c"
    break;

  case 33: /* $@2: %empty  */
#line 490 "parser.y"
                                         {

		//skip mips else if condidtion is true
		emitMIPSEndOfIfBlock(ifCount);

		emitMIPSElseStmt(ifCount);
		

	}
#line 1697 "parser.tab.c"
    break;

  case 34: /* IfStmt: IF LPAREN Condition RPAREN Block $@2 Else  */
#line 498 "parser.y"
               {

		printf("IF STATEMENT RECOGNIZED ---->\n");
		(yyval.ast) = AST_assignment("IF", "COND", "BLOCK");
		(yyval.ast)->left = (yyvsp[-4].ast);
		(yyval.ast)->right = (yyvsp[-2].ast);

		emitMIPSPassElse(ifCount);

		ifCount++;

		semanticCheckPassed = 1;

	}
#line 1716 "parser.tab.c"
    break;

  case 35: /* Else: %empty  */
#line 517 "parser.y"
        {printf("NO ELSE STATEMENT\n\n");}
#line 1722 "parser.tab.c"
    break;

  case 36: /* Else: ELSE Block  */
#line 519 "parser.y"
                      {
		
	}
#line 1730 "parser.tab.c"
    break;

  case 37: /* $@3: %empty  */
#line 526 "parser.y"
                     {

		printf("WHILE LOOP FOUND\n");

		onWhile = 1;

		emitMIPSWhile(whileCount); //all this does is change the 'inLoop' value to true

	}
#line 1744 "parser.tab.c"
    break;

  case 38: /* WhileLoop: WHILE LPAREN $@3 Condition RPAREN Block  */
#line 534 "parser.y"
                                 {

		char type1[8]; char type2[8];
		char val1[10]; char val2[10];
		strcpy(type1, (yyvsp[-2].ast)->left->nodeType); 
		strcpy(type2, (yyvsp[-2].ast)->right->nodeType); 
		strcpy(val1, (yyvsp[-2].ast)->LHS);
		strcpy(val2, (yyvsp[-2].ast)->RHS);
		
		emitMIPSEndWhile(val1, val2, type1, type2, whileCount);

		printf("Emmiting end of while loop!\n");
		
	}
#line 1763 "parser.tab.c"
    break;

  case 39: /* Condition: Primary LOGIC Primary  */
#line 552 "parser.y"
                              {

		// ----- SEMANTIC CHECKS ----- //

		symTabAccess();

		int inSymTab = found((yyvsp[-2].ast), currentScope);
		int inSymTab2 = found((yyvsp[0].ast), currentScope);

		if (inSymTab != 0 && inSymTab2 != 0) {
			printf("\nSEMANTIC ERROR: ARR %s is NOT in the symbol table\n", (yyvsp[-1].string));
			semanticCheckPassed = 0;
		} else {
			printf("\nSEMANTIC CHECK PASSED\n");
			
			//emitArrayAssignment();
		}

		// get item types
		char type1[8]; char type2[8];
		char val1[10]; char val2[10];
		//if both primaries are id's ---->
		if (!strcmp((yyvsp[-2].ast)->nodeType, "id") && !strcmp((yyvsp[0].ast)->nodeType, "id")) {
			strcpy(type1, getVariableType((yyvsp[-2].ast)->RHS, currentScope));
			strcpy(type2, getVariableType((yyvsp[0].ast)->RHS, currentScope));
			strcpy(val1, getValue((yyvsp[-2].ast)->RHS, currentScope));
			strcpy(val2, getValue((yyvsp[0].ast)->RHS, currentScope));
		} 
		// if first primary is an id ---->
		else if (!strcmp((yyvsp[-2].ast)->nodeType, "id")) {
			strcpy(type1, getVariableType((yyvsp[-2].ast)->RHS, currentScope));
			strcpy(type2, (yyvsp[0].ast)->nodeType);
			strcpy(val1, getValue((yyvsp[-2].ast)->RHS, currentScope));
		}
		// if second primary is an id ---->
		else if (!strcmp((yyvsp[0].ast)->nodeType, "id")) {
			strcpy(type1, (yyvsp[-2].ast)->nodeType);
			strcpy(type2, getVariableType((yyvsp[0].ast)->RHS, currentScope));
			strcpy(val2, getValue((yyvsp[0].ast)->RHS, currentScope));
		} 


		//check if types match
		if (!strcmp(type1, type2)) {

			printf("TYPES ARE COMPATIBLE\n");

		} else {

			printf("ERROR TYPE MISMATCH: Attempting to compare %s to %s", type2, type1);
			// printf("\nTypes are %s", type1);
			// printf("\nTypes are %s", type2);
			printf("\n");
			semanticCheckPassed = 0;
		}

		// ---- AST ---- //
		(yyval.ast) = AST_assignment((yyvsp[-1].string), (yyvsp[-2].ast)->RHS, (yyvsp[0].ast)->RHS);
		(yyval.ast)->left = (yyvsp[-2].ast)->nodeType;
		(yyval.ast)->right = (yyvsp[0].ast)->nodeType;

		// may not need this if MIPS stuff works :) 
		// also... Riley wants to smash his computer screen
		// (Riley 2 weeks later) - MIPS works but we still need this
		// and my computer is disfunctional now *smile*.
		int cond = evalCondition((yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-1].string));

		printf("%s %s %s is ", (yyvsp[-2].ast)->RHS, (yyvsp[-1].string), (yyvsp[0].ast)->RHS);

		if (cond) {
			printf("TRUE\n");
			goToElse = 0;
		}
		 else {
			printf("FALSE\n");
			goToElse = 1;
		}

		// ---- CODE GEN ---- //

		if (semanticCheckPassed) {

			if (onWhile || inFunction) {
				loadMIPSVarCond((yyvsp[-2].ast)->RHS, (yyvsp[0].ast)->RHS, (yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType);
				emitMIPSCond(val1, val2, (yyvsp[-1].string), ifCount);	
				onWhile = 0;
			} 
			
			else if(!cond) {
				loadMIPSVarCond((yyvsp[-2].ast)->RHS, (yyvsp[0].ast)->RHS, (yyvsp[-2].ast)->nodeType, (yyvsp[0].ast)->nodeType);
				emitMIPSCond(val1, val2, (yyvsp[-1].string), ifCount);
			}
		} 

		semanticCheckPassed = 1;

	}
#line 1865 "parser.tab.c"
    break;

  case 40: /* ArrayExpr: ID LBRACKET INTEGER RBRACKET EQ Primary  */
#line 656 "parser.y"
                                                {

		printf("\nRECOGNIZED RULE: ARRAY assignment %s\n", (yyvsp[-5].string));

		//Asher's Semantic Checks
		symTabAccess();
		int inSymTab = found((yyvsp[-5].string), currentScope);

		if (inSymTab != 0) {
			printf("\nSEMANTIC ERROR: ARR %s is NOT in the symbol table\n", (yyvsp[-4].string));
			semanticCheckPassed = 0;
		} else {
			printf("\nSEMANTIC CHECK PASSED\n");
			
			//emitArrayAssignment();
		}
		// ------ SYMBOL TABLE ------ //

		// Setting array value in the symbol table
		char arrayStmt[10]; char newVal[10];
		sprintf(arrayStmt, "%s%s%d%s", (yyvsp[-5].string), (yyvsp[-4].string), (yyvsp[-3].number), (yyvsp[-2].string));
		// printf("setVal %s\n", $6);
		// sprintf(newVal, "%d", $6);
		setItemValue(arrayStmt, (yyvsp[0].ast)->RHS, currentScope);


		// ----- AST ----- //
		(yyval.ast) = AST_assignment("=", arrayStmt, newVal);		

		emitMIPSIntArrayAssign((yyvsp[-5].string), (yyvsp[-3].number), atoi((yyvsp[0].ast)->RHS));

	}
#line 1902 "parser.tab.c"
    break;

  case 41: /* ArrayExpr: ID EQ ID LBRACKET INTEGER RBRACKET  */
#line 690 "parser.y"
                                             {

		symTabAccess();
		int inSymTab = found((yyvsp[-5].string), currentScope);

		// Getting array value in the symbol table
		if (inSymTab) {

			char arrayStmt[10]; char newVal[10];
			sprintf(arrayStmt, "%s%s%d%s", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].number), (yyvsp[0].string));

			int arrayVal = atoi(getValue(arrayStmt, currentScope));
			sprintf(newVal, "%d", arrayVal);


			// ---- SYMBOL TABLE ---- //
			setItemValue((yyvsp[-5].string), newVal, currentScope);


			// ------ AST ------ //
			(yyval.ast) = AST_assignment("=", (yyvsp[-5].string), newVal);

			
		}

	}
#line 1933 "parser.tab.c"
    break;

  case 45: /* Expr: FunCall  */
#line 727 "parser.y"
                  {paramCount = 0; (yyval.ast) = (yyvsp[0].ast);}
#line 1939 "parser.tab.c"
    break;

  case 46: /* Expr: UnaryOp Expr  */
#line 729 "parser.y"
                       { 

		//Asher's Semantic Checls
		// ------- SYMBOL TABLE ------- //
		symTabAccess();
		int inSymTab = found((yyvsp[0].ast)->RHS, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		if (inSymTab == 0) {
			printf("\nSEMANTIC ERROR: Expr %s is NOT in the symbol table\n", (yyvsp[0].ast)->nodeType);
		}
		showSymTable();

	}
#line 1957 "parser.tab.c"
    break;

  case 47: /* Expr: ID EQ Expr  */
#line 743 "parser.y"
                     {
		
		printf("\nRECOGNIZED RULE: Assignment Statement ----> %s\n", (yyvsp[-2].string));
		int inSymTab = found((yyvsp[-2].string), currentScope);

		
		// Variable to tell if value has been assigned yet; 1 is true
		int isNullValue = !strcmp(getValue((yyvsp[-2].string), currentScope), "NULL");
		int isFuncCall = !strcmp((yyvsp[0].ast)->LHS, "RETURN");


		// ------ SEMANTIC CHECKS ------ //
		if (!inSymTab) {

			printf("\nSEMANTIC ERROR: Var %s is NOT in the symbol table\n", (yyvsp[-2].string));
			semanticCheckPassed = 0;

		} 		

		char *type1 = getVariableType((yyvsp[-2].string), currentScope);
		if (strcmp(getVariableType((yyvsp[-2].string), currentScope), (yyvsp[0].ast)->nodeType)) {

			printf("ERROR: TYPE MISMATCH ---> Attempting to assign %s to %s\n", (yyvsp[0].ast)->nodeType, type1);
			semanticCheckPassed = 0;

		} 

		// ------- SYMBOL TABLE ------- //
		if (semanticCheckPassed) {
			setItemValue((yyvsp[-2].string), (yyvsp[0].ast)->RHS, currentScope);
		}
		

		// ------ AST ------ //
		(yyval.ast) = AST_assignment("=", (yyvsp[-2].string), (yyvsp[0].ast)->RHS);


		// ------ CODE GENERATION ------ //

		if (semanticCheckPassed) {

			char *test = getVariableType((yyvsp[-2].string), currentScope);

			if (!strcmp(test, "char")) {

				// ---- IR CODE ---- // 
				emitIRCharDecl((yyvsp[-2].string), (yyvsp[0].ast)->RHS);

				if(isNullValue) { //if val isn't null
					setCharVar((yyvsp[-2].string), (yyvsp[0].ast)->RHS);
				} else {
					emitMIPSCharDecl((yyvsp[-2].string), (yyvsp[0].ast)->RHS);
				}

			}

				// ---- INT CODE ---- // 
			else if (!strcmp(test, "int")) {

				// ---- IR CODE ---- //

				emitIntVarIR((yyvsp[-2].string), atoi((yyvsp[0].ast)->RHS));


				// ---- MIPS CODE ---- //
				if(!isNullValue) { //if val isn't null

					if (inFunction && hasMath) {
						// printf("Setting new var for int\n");
						setIntVar((yyvsp[-2].string), "$s1");
					} 					

					else if (isFuncCall) {
						setIntVar((yyvsp[-2].string), "$v1");
					}

					else {
						setIntVar((yyvsp[-2].string), (yyvsp[0].ast)->RHS);
					}
					
				} else if (inFunction && hasMath) {

					// printf("Setting new var for int\n");
					emitIntVar((yyvsp[-2].string), (yyvsp[0].ast)->RHS);
					setIntVar((yyvsp[-2].string), "$s1");

				} else if (isFuncCall) {

					emitIntVar((yyvsp[-2].string), (yyvsp[0].ast)->RHS);
					setIntVar((yyvsp[-2].string), "$v1");
				
				} else {

					printf("generating mips var\n");
					emitIntVar((yyvsp[-2].string), (yyvsp[0].ast)->RHS);

				}
			}

		}

		semanticCheckPassed = 1;
	}
#line 2065 "parser.tab.c"
    break;

  case 48: /* FunCall: ID LPAREN ParamList RPAREN  */
#line 853 "parser.y"
                                   {

		printf("\nRECOGNIZED RULE: Function Call ----> %s\n", (yyvsp[-3].string));

		char returnVal[25];
		sprintf(returnVal, "%s", getValue((yyvsp[-3].string), (yyvsp[-3].string)));
		(yyval.ast) = AST_assignment("int", "RETURN", returnVal);
		emitMIPSFuncCall((yyvsp[-3].string));
		emitMIPSGetReturn();
		// ---- SEMANTIC CHECKS ---- //
		
	}
#line 2082 "parser.tab.c"
    break;

  case 49: /* Primary: ID  */
#line 869 "parser.y"
           {
		(yyval.ast) = AST_assignment("id", "" , (yyvsp[0].string));
	}
#line 2090 "parser.tab.c"
    break;

  case 50: /* Primary: DECIMAL  */
#line 873 "parser.y"
                  {
		// printf("float detected: %f\n", $1);
		char numVal[10];
		sprintf(numVal, "%f", (yyvsp[0].floatValue));
		(yyval.ast) = AST_assignment("float", "", numVal);
	}
#line 2101 "parser.tab.c"
    break;

  case 51: /* Primary: INTEGER  */
#line 880 "parser.y"
                  {
		// printf("int detected\n");
		char numVal[10];
		sprintf(numVal, "%d", (yyvsp[0].number));
		(yyval.ast) = AST_assignment("int", "", numVal);
	}
#line 2112 "parser.tab.c"
    break;

  case 52: /* Primary: CHARACTER  */
#line 887 "parser.y"
                      {

		(yyval.ast) = AST_assignment("char", "", (yyvsp[0].string));

	}
#line 2122 "parser.tab.c"
    break;

  case 54: /* MathExpr: MathExpr MINUS Trm  */
#line 900 "parser.y"
                             {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", (yyvsp[-1].string));

		// if (inFunction) {
		// 	emitMIPSEquation($1->RHS, $3->RHS, $2);
		// } 

		sprintf(newVal, "%d", computeEquation((yyvsp[-2].ast), (yyvsp[0].ast), opArray[0]));
		// sprintf(newVal, "%d", computeEquation(atoi($1->RHS), atoi($3->RHS), opArray[0]));

		// printf("newVal = %s\n", newVal);

		(yyval.ast) = AST_assignment("int", "", newVal);
		hasMath = 1;

	}
#line 2148 "parser.tab.c"
    break;

  case 55: /* MathExpr: MathExpr PLUS Trm  */
#line 922 "parser.y"
                            {
			
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", (yyvsp[-1].string));

		// printf("$1 = %s and $3 = %s\n", $1->RHS, $3->RHS);

		// if (inFf
		
		sprintf(newVal, "%d", computeEquation((yyvsp[-2].ast), (yyvsp[0].ast), opArray[0]));

		(yyval.ast) = AST_assignment("int", "", newVal);
		hasMath = 1;

	}
#line 2171 "parser.tab.c"
    break;

  case 56: /* Trm: Factor  */
#line 944 "parser.y"
               {
		
	}
#line 2179 "parser.tab.c"
    break;

  case 57: /* Trm: Trm MULTIPLY Factor  */
#line 948 "parser.y"
                              {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		//sprintf(opArray, "%s", $2);

		(yyval.ast) = AST_assignment("int", "", newVal);
		hasMath = 1;


	}
#line 2197 "parser.tab.c"
    break;

  case 58: /* Trm: Trm DIVIDE Factor  */
#line 962 "parser.y"
                            {
		
		char newVal[5];

		// Evaluate expression
		char opArray[3];
		sprintf(opArray, "%s", (yyvsp[-1].string));


		(yyval.ast) = AST_assignment("int", "", newVal);
		hasMath = 1;


	}
#line 2216 "parser.tab.c"
    break;

  case 59: /* Factor: ID  */
#line 979 "parser.y"
           {

		char val[25];
		strcpy(val, getValue((yyvsp[0].string), currentScope));
		if (!strcmp(val, "NULL")) {
			printf("ERROR: ID %s is null\n", (yyvsp[0].string));
			// exit;
		}
		(yyval.ast) = AST_assignment("id", (yyvsp[0].string) , val);
	}
#line 2231 "parser.tab.c"
    break;

  case 60: /* Factor: INTEGER  */
#line 990 "parser.y"
                  {
		char numVal[10];
		sprintf(numVal, "%d", (yyvsp[0].number));
		(yyval.ast) = AST_assignment("int", "", numVal);
	}
#line 2241 "parser.tab.c"
    break;

  case 61: /* Factor: LPAREN MathExpr RPAREN  */
#line 996 "parser.y"
                                 {
		// printf("Factor test\n");
		printf("MathExpr = %s\n", (yyvsp[-1].ast)->RHS);
		(yyval.ast) = AST_assignment("int", "", (yyvsp[-1].ast)->RHS);
	}
#line 2251 "parser.tab.c"
    break;

  case 62: /* ParamList: %empty  */
#line 1003 "parser.y"
                {}
#line 2257 "parser.tab.c"
    break;

  case 63: /* $@4: %empty  */
#line 1004 "parser.y"
                  {

		printf("\nRECOGNIZED RULE: Parameter\n");

		char *paramValue;
		if (!strcmp((yyvsp[0].ast)->nodeType, "id")) {
			char *idVal = getValue((yyvsp[0].ast)->RHS, currentScope);
			paramValue = malloc((int)strlen(idVal)+1);
			strcpy(paramValue, idVal);
			setMIPSParameters((yyvsp[0].ast)->RHS, paramCount);
		} 
		else {
			int size = sizeof((yyvsp[0].ast)->RHS) / sizeof((yyvsp[0].ast)->RHS)[0]; 
			paramValue = (char*)malloc(size*sizeof(char));
			strcpy(paramValue, (yyvsp[0].ast)->RHS);
			setMIPSParameters(paramValue, paramCount);
		}
		 
		printf("ParamValue = %s\n", paramValue);

		paramCount++;

	}
#line 2285 "parser.tab.c"
    break;

  case 64: /* ParamList: Primary $@4 ParamList  */
#line 1026 "parser.y"
                    {}
#line 2291 "parser.tab.c"
    break;

  case 65: /* UnaryOp: MINUS  */
#line 1034 "parser.y"
               {printf("\nRECOGNIZED RULE: Unary Operation, NEGATIVE VALUE %s\n", (yyvsp[0].string));}
#line 2297 "parser.tab.c"
    break;


#line 2301 "parser.tab.c"

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

#line 1042 "parser.y"


int evalCondition(struct AST* x, struct AST* y, char logOp[5]) {

	printf("Evaluating condition---->\n");

	int val1; int val2;
	if (!strcmp(x->nodeType, "id") && !strcmp(y->nodeType, "id")) {
		val1 = atoi(getValue(x->RHS, currentScope));
		val2 = atoi(getValue(y->RHS, currentScope));
	} 
	else if (!strcmp(x->nodeType, "id")) {
		val1 = atoi(getValue(x->RHS, currentScope));
		val2 = atoi(y->RHS);
	}
	else if (!strcmp(y->nodeType, "id")) {
		val1 = atoi(x->RHS);
		val2 = atoi(getValue(y->RHS, currentScope));
	} 

	if (!strcmp(logOp, "==")) {
		if (!strcmp(x->RHS, y->RHS) || val1 == val2) {
			return 1;
		}
	} 
	else if (!strcmp(logOp, "!=")) {
		if (val1 != val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, "<=")) {
		if (val1 <= val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, ">=")) {
		if (val1 >= val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, "<")) {
		if (val1 < val2) {
			return 1;
		}
	}
	else if (!strcmp(logOp, ">")) {
		if (val1 > val2) {
			return 1;
		}
	}

	return 0;
}

int computeEquation(struct AST* num1, struct AST* num2, char operator) {
	char mipsVal1[10];
	char mipsVal2[10];
	int val1; int val2;	
	val1 = atoi(num1->RHS);
	val2 = atoi(num2->RHS);
	
	if (!strcmp(num1->nodeType, "id")) {
		strcpy(mipsVal1, num1->LHS);
	} else {
		strcpy(mipsVal1, num1->RHS);
	}

	if (!strcmp(num2->nodeType, "id")) {
		strcpy(mipsVal2, num2->LHS);
	} else {
		strcpy(mipsVal2, num2->RHS);
	}
	if (inFunction) {
		emitMIPSEquation(mipsVal1, mipsVal2, operator);
	}

	int newVal;

	switch (operator) {
		case '+':
			newVal = val1 + val2;
			break;
		case '-':
			newVal = val1 - val2;
			break;
		case '*':
			newVal = val1 * val2;
			break;
		case '/':
			newVal = val1 / val2;
			break;
	}


}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int main(int argc, char**argv)
{


	printf("\n\n##### COMPILER STARTED #####\n\n");

	// Initialize IR File
	initIRcodeFile();
	// Initialize MIPS.h
	initAssemblyFile();
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();

	emitEndOfAssemblyCode();

	printf("\n##### IR CODE GENERATED #####\n\n");

	emitEndOfAssemblyCodeIR();
	printf("\n##### MIPS CODE GENERATED #####\n\n");

	// Merge data and main sections in MIPS
	appendFiles();

	printf("\n##### COMPILER ENDED #####\n\n");


	/* fprintf (GarbageMIPS, "syscall\n"); */
}
