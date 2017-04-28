/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "cminus.y" /* yacc.c:339  */

//GLC para gerar parser para C-

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


#define YYDEBUG 0

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {statementK, expK} node_kind;
typedef enum {ifK, whileK, assignK, returnK, varK, vecK, funcK, funcvarK, funcvecK} statement_kind;
typedef enum {TypeK, RelOpK, ArithOpK, ConstK, IdK, VecIndexK, CallK} expression_kind;

union treeKind{
    statement_kind stmt;
    expression_kind exp;
};

typedef struct treeNode{
  char *str;
  char *name;
  int type;
  int value;
  int lineno;
  node_kind nodekind;
  char * scope;
  union treeKind kind;
  struct treeNode *child;
  struct treeNode *sibling;
}TreeNode;

int line_flag = 0;
int reference_line = 0;

TreeNode * tree;// Declaração da árvore
TreeNode * allocateToken(char const* token);
TreeNode * allocateNode(char const* node);
TreeNode * addChild(TreeNode* node, TreeNode* newChild);
TreeNode * addSibling(TreeNode* first, TreeNode* newSibling);

static int indentNo = 0;

#define YYSTYPE TreeNode *
#define INDENT indentNo+=2
#define UNINDENT indentNo-=2

static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
// char * strExp;
std::string strExp;



using namespace std;

extern "C"
{

  ofstream writeTree;
  int yylex();
  int yyparse();
	void abrirArq();
  void effPrintTree(TreeNode * tree);
  void printTree();
  int yywrap() {
    return 1;
  }
}


extern char* yytext;
extern int yylineno;
FILE *arq;

void yyerror(char*);

#line 153 "cminus.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "cminus.tab.h".  */
#ifndef YY_YY_CMINUS_TAB_H_INCLUDED
# define YY_YY_CMINUS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 300,
    FLOAT = 301,
    IF = 302,
    ELSE = 303,
    RETURN = 304,
    VOID = 305,
    WHILE = 306,
    PLUS = 307,
    MINUS = 308,
    TIMES = 309,
    OVER = 310,
    LT = 311,
    LET = 312,
    HT = 313,
    HET = 314,
    EQ = 315,
    NEQ = 316,
    ASSIGN = 317,
    SEMI = 318,
    COMMA = 319,
    LPAREN = 320,
    RPAREN = 321,
    LBRACK = 322,
    RBRACK = 323,
    LCAPSULE = 324,
    RCAPSULE = 325,
    NUMI = 326,
    NUMF = 327,
    ID = 328,
    NEWLINE = 329,
    ERROR = 331
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CMINUS_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 238 "cminus.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   332

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       2,    33,     2
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   123,   123,   124,   132,   136,   141,   144,   149,   155,
     206,   218,   231,   234,   240,   246,   251,   256,   267,   277,
     284,   287,   294,   297,   302,   307,   312,   317,   324,   331,
     339,   351,   368,   382,   391,   402,   410,   417,   423,   436,
     441,   448,   457,   463,   469,   475,   481,   487,   495,   502,
     508,   515,   521,   529,   536,   543,   549,   557,   566,   572,
     578,   584,   592,   605,   611,   616,   624
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "IF", "ELSE", "RETURN",
  "VOID", "WHILE", "PLUS", "MINUS", "TIMES", "OVER", "LT", "LET", "HT",
  "HET", "EQ", "NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN",
  "LBRACK", "RBRACK", "LCAPSULE", "RCAPSULE", "NUMI", "NUMF", "ID",
  "NEWLINE", "ERROR", "$accept", "programa", "declaration-list",
  "declaration", "var-declaration", "fun-declaration", "params",
  "param-list", "param", "compound-stmt", "local-declarations",
  "statement-list", "statement", "expression-stmt", "selection-stmt",
  "iteration-stmt", "return-stmt", "expression", "var",
  "simple-expression", "comparative-expression", "relop",
  "additive-expression", "addop", "term", "mulop", "factor", "call",
  "args", "arg-list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   332,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   331
};
# endif

#define YYPACT_NINF -89

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-89)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      39,   -20,    13,    46,    39,   -89,   -89,   -89,    56,    27,
     -89,   -89,   -89,    40,    25,    40,    31,   -89,    34,    47,
     -89,    41,    49,    53,    68,    93,    82,    68,    79,   -89,
     -89,   -89,   -89,   -89,   -89,   101,    75,   -89,    -3,    11,
      84,    45,    85,   -89,   -89,   -89,    61,   -89,   -89,   -89,
     -13,   -89,   -89,   -89,   -89,   -89,   -89,    88,    90,   -89,
     -89,    83,   -14,    74,   -89,   -89,    61,   -89,    91,    61,
      87,    61,    61,   -89,    61,   -89,   -89,   -89,   -89,   -89,
     -89,    61,   -14,   -89,    74,   -89,   -89,   -14,    89,    83,
     -89,    92,   -89,   -89,    94,    95,    96,   -89,    78,    74,
     -89,    30,    30,   -89,    61,   -89,   108,   -89,   -89,    30,
     -89
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     3,     5,     6,     7,     0,     0,
       1,     4,     8,     0,     0,     0,     0,    13,     0,    12,
      15,     0,     0,    16,     0,     0,     0,     0,     0,    20,
      11,    14,     9,    10,    17,    22,     0,    19,     0,     0,
       0,     0,     0,    51,    52,    29,     0,    18,    60,    61,
      37,    24,    21,    23,    25,    26,    27,     0,    58,    36,
      39,    40,     0,    50,    54,    59,     0,    33,     0,     0,
       0,    64,     0,    28,     0,    43,    42,    44,    45,    46,
      47,     0,     0,    58,    49,    55,    56,     0,     0,     0,
      34,     0,    57,    66,     0,    63,     0,    35,    41,    48,
      53,     0,     0,    62,     0,    38,    30,    32,    65,     0,
      31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -89,   -89,   -89,   111,    86,   -89,   104,   -89,    98,    58,
     -89,   -89,   -88,   -89,   -89,   -89,   -89,   -41,   -17,   -89,
      14,   -89,   -47,   -60,   -59,   -89,    33,   -89,   -89,   -89
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    18,    19,    20,    51,
      35,    38,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    81,    61,    62,    63,    87,    64,    65,    94,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      68,    82,    40,    84,    41,    70,    42,    43,    44,    46,
      71,     8,    72,   106,   107,    48,    49,    50,    45,    89,
      46,   110,    89,    99,    29,    47,    48,    49,    50,    82,
      93,    96,    12,    97,    98,    40,    14,    41,    82,    42,
      43,    44,     1,    16,     9,    83,    10,     2,    17,    83,
      15,    45,    83,    46,    21,    43,    44,    29,    24,    48,
      49,    50,    23,   108,    83,    83,    67,    26,    46,    25,
      83,    43,    44,    27,    48,    49,    50,    12,    28,    13,
      88,    14,    30,    91,    46,    33,    85,    86,    43,    44,
      48,    49,    50,    43,    44,    29,    16,    75,    76,    77,
      78,    79,    80,    32,    36,    34,    39,    66,    69,    73,
      74,    92,    90,   101,   109,    11,   102,   104,   103,    22,
     100,    37,   105,    31
};

static const yytype_uint8 yycheck[] =
{
      41,    61,     5,    62,     7,    46,     9,    10,    11,    23,
      23,    31,    25,   101,   102,    29,    30,    31,    21,    66,
      23,   109,    69,    82,    27,    28,    29,    30,    31,    89,
      71,    72,    21,    74,    81,     5,    25,     7,    98,     9,
      10,    11,     3,     3,    31,    62,     0,     8,     8,    66,
      23,    21,    69,    23,    29,    10,    11,    27,    24,    29,
      30,    31,    31,   104,    81,    82,    21,    26,    23,    22,
      87,    10,    11,    24,    29,    30,    31,    21,    25,    23,
      66,    25,    24,    69,    23,    27,    12,    13,    10,    11,
      29,    30,    31,    10,    11,    27,     3,    14,    15,    16,
      17,    18,    19,    21,     3,    26,    31,    23,    23,    21,
      20,    24,    21,    24,     6,     4,    24,    22,    24,    15,
      87,    35,    26,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,    35,    36,    37,    38,    39,    31,    31,
       0,    37,    21,    23,    25,    23,     3,     8,    40,    41,
      42,    29,    40,    31,    24,    22,    26,    24,    25,    27,
      43,    42,    21,    43,    26,    44,     3,    38,    45,    31,
       5,     7,     9,    10,    11,    21,    23,    28,    29,    30,
      31,    43,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    56,    57,    58,    60,    61,    23,    21,    51,    23,
      51,    23,    25,    21,    20,    14,    15,    16,    17,    18,
      19,    55,    57,    52,    58,    12,    13,    59,    54,    56,
      21,    54,    24,    51,    62,    63,    51,    51,    56,    58,
      60,    24,    24,    24,    22,    26,    46,    46,    51,     6,
      46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    35,    36,    36,    37,    37,    38,    38,
      39,    39,    40,    40,    41,    41,    42,    42,    43,    44,
      44,    45,    45,    46,    46,    46,    46,    46,    47,    47,
      48,    48,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    55,    55,    55,    55,    55,    55,    56,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    60,
      60,    60,    61,    62,    62,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     1,     1,     3,     6,
       6,     6,     1,     1,     3,     1,     2,     4,     4,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     5,     2,     3,     3,     1,     1,     4,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     2,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     4,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 3:
#line 125 "cminus.y" /* yacc.c:1646  */
    {
            (yyval) = allocateNode("programa");
            addChild((yyval),(yyvsp[0]));
            tree = (yyval);
          }
#line 1407 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 133 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration-list");
                   addChild((yyval),(yyvsp[-1]));
                   addChild((yyval),(yyvsp[0]));}
#line 1415 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 137 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration-list");
                   addChild((yyval),(yyvsp[0]));}
#line 1422 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 142 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration");
               addChild((yyval),(yyvsp[0]));}
#line 1429 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 145 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration");
               addChild((yyval),(yyvsp[0]));}
#line 1436 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 150 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("var-declaration");
                 /*addChild($$,$1);*/
                 addChild((yyval),(yyvsp[-1]));
                 /*$3 = allocateNode("SEMI");
                 addChild($$,$3);}*/
               }
#line 1447 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 155 "cminus.y" /* yacc.c:1646  */
    {
                 (yyval) = allocateNode("var-declaration");
                 addChild((yyval),(yyvsp[-4]));
               }
#line 1456 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 207 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("fun-declaration");
                 addChild((yyval),(yyvsp[-5]));
                 (yyvsp[-4]) = allocateToken("ID");
                 (yyvsp[-3]) = allocateNode("LPAREN");
                 addChild((yyval),(yyvsp[-4]));
                 addChild((yyval),(yyvsp[-3]));
                 addChild((yyval),(yyvsp[-2]));
                 (yyvsp[-1]) = allocateNode("RPAREN");
                 addChild((yyval),(yyvsp[-1]));
                 addChild((yyval),(yyvsp[0]));
               }
#line 1472 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 219 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("fun-declaration");
                                  addChild((yyval),(yyvsp[-5]));
                                  (yyvsp[-4]) = allocateToken("ID");
                                  (yyvsp[-3]) = allocateNode("LPAREN");
                                  addChild((yyval),(yyvsp[-4]));
                                  addChild((yyval),(yyvsp[-3]));
                                  addChild((yyval),(yyvsp[-2]));
                                  (yyvsp[-1]) = allocateNode("RPAREN");
                                  addChild((yyval),(yyvsp[-1]));
                                  addChild((yyval),(yyvsp[0]));}
#line 1487 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 232 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("params");
         addChild((yyval),(yyvsp[0]));}
#line 1494 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 235 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("params");
         (yyvsp[0]) = allocateNode("VOID");
         addChild((yyval),(yyvsp[0]));}
#line 1502 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 241 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param-list");
             addChild((yyval),(yyvsp[-2]));
             (yyvsp[-1]) = allocateNode("COMMA");
             addChild((yyval),(yyvsp[-1]));
             addChild((yyval),(yyvsp[0]));}
#line 1512 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 247 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param-list");
             addChild((yyval),(yyvsp[0]));}
#line 1519 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 252 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param");
             addChild((yyval),(yyvsp[-1]));
             (yyvsp[0]) = allocateToken("ID");
             addChild((yyval),(yyvsp[0]));}
#line 1528 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 257 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param");
             addChild((yyval),(yyvsp[-3]));
             (yyvsp[-2]) = allocateToken("ID");
             (yyvsp[-1]) = allocateNode("LBRACK");
             (yyvsp[0]) = allocateNode("RBRACK");
             addChild((yyval),(yyvsp[-2]));
             addChild((yyval),(yyvsp[-1]));
             addChild((yyval),(yyvsp[0]));}
#line 1541 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 268 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("compound-stmt");
               (yyvsp[-3]) = allocateNode("LCAPSULE");
               addChild((yyval),(yyvsp[-3]));
               addChild((yyval),(yyvsp[-2]));
               addChild((yyval),(yyvsp[-1]));
               (yyvsp[0]) = allocateNode("RCAPSULE");
               addChild((yyval),(yyvsp[0]));}
#line 1553 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 278 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("local-declarations");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1563 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 284 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("local-declarations");}
#line 1569 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 288 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement-list");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1579 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 294 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("statement-list");}
#line 1585 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 298 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1594 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 303 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1603 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 308 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1612 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 313 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1621 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 318 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1630 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 325 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("expression-stmt");
                        addChild((yyval),(yyvsp[-1]));
                        (yyvsp[0]) = allocateNode("SEMI");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1641 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 332 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("expression-stmt");
                        (yyvsp[0]) = allocateNode("SEMI");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1651 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 340 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("selection-stmt");
                        (yyvsp[-4]) = allocateNode("IF");
                        addChild((yyval),(yyvsp[-4]));
                        (yyvsp[-3]) = allocateNode("LPAREN");
                        addChild((yyval),(yyvsp[-3]));
                        addChild((yyval),(yyvsp[-2]));
                        (yyvsp[-1]) = allocateNode("RPAREN");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1667 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 352 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("selection-stmt");
                        (yyvsp[-6]) = allocateNode("IF");
                        addChild((yyval),(yyvsp[-6]));
                        (yyvsp[-5]) = allocateNode("LPAREN");
                        addChild((yyval),(yyvsp[-5]));
                        addChild((yyval),(yyvsp[-4]));
                        (yyvsp[-3]) = allocateNode("RPAREN");
                        addChild((yyval),(yyvsp[-3]));
                        addChild((yyval),(yyvsp[-2]));
                        (yyvsp[-1]) = allocateNode("ELSE");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1686 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 369 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("iteration-stmt");
                        (yyvsp[-4]) = allocateNode("WHILE");
                        addChild((yyval),(yyvsp[-4]));
                        (yyvsp[-3]) = allocateNode("LPAREN");
                        addChild((yyval),(yyvsp[-3]));
                        addChild((yyval),(yyvsp[-2]));
                        (yyvsp[-1]) = allocateNode("RPAREN");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1702 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 383 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("return-stmt");
                        (yyvsp[-1]) = allocateNode("RETURN");
                        addChild((yyval),(yyvsp[-1]));
                        (yyvsp[0]) = allocateNode("SEMI");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1714 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 392 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("return-stmt");
                        (yyvsp[-2]) = allocateNode("RETURN");
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        (yyvsp[0]) = allocateNode("SEMI");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1727 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 403 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("expression");
                        addChild((yyval),(yyvsp[-2]));
                        (yyvsp[-2]) = allocateNode("ASSIGN");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1739 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 411 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("expression");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1748 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 418 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("var");
                        (yyvsp[0]) = allocateToken("ID");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1758 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 424 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("var");
                        (yyvsp[-3]) = allocateToken("ID");
                        addChild((yyval),(yyvsp[-3]));
                        (yyvsp[-2]) = allocateNode("LBRACK");
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        (yyvsp[0]) = allocateNode("RBRACK");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1773 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 437 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("simple-expression");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1782 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 442 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("simple-expression");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1791 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 449 "cminus.y" /* yacc.c:1646  */
    {
                          (yyval) = allocateNode("comparative-expression");
                          addChild((yyval),(yyvsp[-2]));
                          addChild((yyval),(yyvsp[-1]));
                          addChild((yyval),(yyvsp[0]));
                        }
#line 1802 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 458 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("relop");
                        (yyvsp[0]) = allocateNode("LET");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1812 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 464 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("relop");
                        (yyvsp[0]) = allocateNode("LT");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1822 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 470 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("relop");
                        (yyvsp[0]) = allocateNode("HT");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1832 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 476 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("relop");
                        (yyvsp[0]) = allocateNode("HET");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1842 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 482 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("relop");
                        (yyvsp[0]) = allocateNode("EQ");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1852 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 488 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("relop");
                        (yyvsp[0]) = allocateNode("NEQ");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1862 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 496 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("additive-expression");
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1873 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 503 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("additive-expression");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1883 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 509 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("additive-expression");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1892 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 516 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("addop");
                        (yyvsp[0]) = allocateNode("PLUS");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1902 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 522 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("addop");
                        (yyvsp[0]) = allocateNode("MINUS");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1912 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 530 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("term");
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1923 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 537 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("term");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1932 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 544 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("mulop");
                        (yyvsp[0]) = allocateNode("TIMES");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1942 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 550 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("mulop");
                        (yyvsp[0]) = allocateNode("OVER");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1952 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 558 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor");
                        (yyvsp[-2]) = allocateNode("LPAREN");
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        (yyvsp[0]) = allocateNode("RPAREN");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1965 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 567 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor");
                        (yyvsp[0]) = allocateNode("var");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1975 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 573 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor");
                        (yyvsp[0]) = allocateNode("call");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1985 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 579 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor");
                        (yyvsp[0]) = allocateToken("NUMI");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1995 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 585 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor");
                        (yyvsp[0]) = allocateToken("NUMF");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2005 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 593 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("call");
                        (yyvsp[-3]) = allocateToken("ID");
                        addChild((yyval),(yyvsp[-3]));
                        (yyvsp[-2]) = allocateNode("LPAREN");
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        (yyvsp[0]) = allocateNode("RPAREN");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2020 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 606 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("args");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2029 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 611 "cminus.y" /* yacc.c:1646  */
    {
                  		(yyval) = allocateNode("args");
                  	}
#line 2037 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 617 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("arg-list");
                        addChild((yyval),(yyvsp[-2]));
                        (yyvsp[-1]) = allocateNode("COMMA");
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2049 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 625 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("arg-list");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2058 "cminus.tab.c" /* yacc.c:1646  */
    break;


#line 2062 "cminus.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 631 "cminus.y" /* yacc.c:1906  */



// void reset(char arg[]) //100%
// {
// 	int i, max = strlen(arg);
//
// 	for(i = 0; i < max; i++)
// 		arg[i] = '\0';
// }


TreeNode * allocateToken(char const *token)
{
	//reset(strExp);
	//strncpy(strExp, yytext, sizeof(strExp));
  strExp.erase();
  strExp = yytext;
	TreeNode *branch = allocateNode(token);
	//puts( yytext );
//	sprintf(strExp, "%s", yytext);
	TreeNode *leaf = allocateNode(strExp.c_str());//because it must be a char const*
  // TreeNode *leaf = allocateNode("galeto");
//	addChild(branch, leaf);
	return branch;
}

TreeNode * allocateNode(char const *node)
{

  if(line_flag==0){
    reference_line = yylineno;
    line_flag = 1;
  }

	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->lineno = yylineno - reference_line;
  /*newNode->name = strcpy(newNode->name, yylex());*/

	newNode->str = (char*) calloc(sizeof(char),20);
	strcpy(newNode->str, node);

	newNode->child = NULL;
	newNode->sibling = NULL;
  /*printf("alocou no str->%s\n", newNode->str);*/
	return newNode;
}

TreeNode* addSibling(TreeNode* first, TreeNode* newSibling){
	if(first->sibling == NULL){first->sibling = newSibling;}
	else{first->sibling = addSibling(first->sibling, newSibling);}
	return first;
}

TreeNode* addChild(TreeNode* node, TreeNode* childNode){
	if(node->child!=NULL){node->child = addSibling(node->child, childNode);}
	else{node->child = childNode;}
	return node;
}

TreeNode* freeTree(TreeNode * tree){
	if(tree != NULL)
	{
		if(tree->sibling != NULL){tree->sibling = freeTree(tree->sibling);}

		if(tree->child != NULL){tree->child = freeTree(tree->child);}

		if(tree->child == NULL && tree->sibling == NULL)
		{
			free(tree);
			return NULL;
		}
	}
}

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
	int i;
  	for (i=0;i<indentNo;i++)
	{
		//fprintf(arq, "	");
		printf("_");
	}
}

/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
void effPrintTree(TreeNode * tree)
{
	INDENT;
	while (tree != NULL)
	{
		printSpaces();
		//fprintf(arq, "%s\n",tree->str);
    printf("%s %d\n",tree->str, tree->lineno);

		tree = tree->child;

		while(tree != NULL)
		{
			effPrintTree(tree);
			tree = tree->sibling;
		}
	  	UNINDENT;
	}
}

void printTree()
{
  printf("Imprimindo árvore sintática...\n");
	arq = fopen("syntaticTree.xls", "w");
	effPrintTree(tree);
	fclose(arq);
}

void yyerror (char* s)  /* Called by yyparse on error */
{
	extern char* yytext;
	cout << s << ": " << yytext << endl << "At line: " << yylineno <<  endl;
  strExp = (char*) calloc(sizeof(char),40);
}
