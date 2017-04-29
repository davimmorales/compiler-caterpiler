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

using namespace std;

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

typedef enum {none_nK, statementK, expK} node_kind;
typedef enum {none_stK, ifK, whileK, assignK, returnK, varK, vecK, funcK, funcvarK, funcvecK} statement_kind;
typedef enum {none_expK, TypeK, RelOpK, ArithOpK, ConstK, IdK, VecIndexK, CallK} expression_kind;
typedef enum {none_typeK, intK, voidK, boolK} type_kind;
typedef int TokenType;

union treeKind{
    statement_kind stmt;
    expression_kind exp;
};

struct treeAttr{
    TokenType op;
    int value;
    char * name;
};

typedef struct treeNode{
  char *str;
  char *name;
  type_kind type;//where 0=none, 1=int and 2 = void
  int value;
  int lineno;
  node_kind nodekind;
  char * scope;
  union treeKind kind;
  struct treeAttr attr;
  struct treeNode *child;
  struct treeNode *sibling;
}TreeNode;

int line_flag = 0;
int reference_line = 0;

TreeNode * tree;// Declaração da árvore
TreeNode * allocateToken(char const* token);
TreeNode * allocateNode(char const* node, expression_kind ek, statement_kind sk);
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

#line 163 "cminus.tab.c" /* yacc.c:339  */

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

#line 248 "cminus.tab.c" /* yacc.c:358  */

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   122

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

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
       0,   133,   133,   134,   142,   146,   151,   154,   159,   168,
     222,   240,   259,   262,   266,   272,   277,   286,   302,   313,
     320,   323,   330,   333,   338,   343,   348,   353,   360,   367,
     375,   387,   404,   418,   428,   440,   448,   455,   462,   477,
     482,   489,   498,   508,   518,   528,   538,   547,   559,   566,
     572,   579,   589,   601,   608,   615,   625,   637,   646,   652,
     658,   672,   686,   692,   697,   705,   711,   715
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
  "NEWLINE", "ERROR", "$accept", "program", "declaration-list",
  "declaration", "var-declaration", "fun-declaration", "params",
  "param-list", "param", "compound-stmt", "local-declarations",
  "statement-list", "statement", "expression-stmt", "selection-stmt",
  "iteration-stmt", "return-stmt", "expression", "var",
  "simple-expression", "comparative-expression", "relop",
  "additive-expression", "addop", "term", "mulop", "factor", "call",
  "args", "arg-list", "id", "num", YY_NULLPTR
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

#define YYPACT_NINF -61

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-61)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      33,   -19,   -19,    22,    33,   -61,   -61,   -61,   -61,    70,
      14,   -61,   -61,   -61,    51,    31,    51,   -19,   -61,    32,
      45,   -61,   -61,    46,    53,    54,    65,    93,    79,    65,
      75,   -61,   -61,   -61,   -61,   -61,   -61,    99,   -19,   -61,
       4,   -15,    80,    -3,    81,   -61,   -61,   -61,    47,   -61,
     -61,   -61,   -61,   -61,   -61,   -61,    84,    87,   -61,   -61,
      71,    17,    86,   -61,   -61,    43,   -61,    47,   -61,    85,
      47,    88,   -61,    47,   -61,   -61,   -61,   -61,   -61,   -61,
      47,    17,   -61,    86,   -61,   -61,    17,    47,    47,    89,
      71,   -61,    90,   -61,   -61,    73,    86,   -61,   -61,    91,
      94,    82,    42,    42,   -61,    47,   -61,   103,   -61,   -61,
      42,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     3,     5,     6,     7,    66,     0,
       0,     1,     4,     8,     0,     0,     0,     0,    13,     0,
      12,    15,    67,     0,     0,    16,     0,     0,     0,     0,
       0,    20,    11,    14,     9,    10,    17,    22,     0,    19,
       0,     0,     0,     0,     0,    51,    52,    29,     0,    18,
      24,    21,    23,    25,    26,    27,     0,    58,    36,    39,
      40,     0,    50,    54,    59,    37,    60,     0,    33,     0,
       0,     0,    28,     0,    43,    42,    44,    45,    46,    47,
       0,     0,    58,    49,    55,    56,     0,    63,     0,     0,
       0,    34,     0,    57,    35,    41,    48,    53,    65,     0,
      62,     0,     0,     0,    61,     0,    38,    30,    32,    64,
       0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,   106,    74,   -61,   101,   -61,    92,    -5,
     -61,   -61,   -60,   -61,   -61,   -61,   -61,   -43,    -6,   -61,
      27,   -61,   -51,   -56,   -58,   -61,    34,   -61,   -61,   -61,
       0,   107
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    19,    20,    21,    50,
      37,    40,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    80,    60,    61,    62,    86,    63,    64,    99,   100,
      65,    66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      69,     9,    10,    83,    81,    71,    13,    45,    46,    42,
      15,    43,     8,    44,    45,    46,    90,    25,    68,    90,
      48,    32,    11,    96,    35,    47,    22,    48,     8,    95,
      94,    31,    49,    22,    81,     8,     1,    16,    41,    81,
      48,     2,   107,   108,    98,   101,    22,    42,     8,    43,
     111,    44,    45,    46,    17,    82,    26,    45,    46,    18,
      22,    82,   109,    47,    82,    48,    87,    27,    88,    31,
      48,    22,    28,     8,    82,    82,    22,    29,     8,    30,
      82,    45,    46,    45,    46,    74,    75,    76,    77,    78,
      79,    13,    31,    14,    89,    15,    17,    92,    84,    85,
      34,    36,    38,    67,    70,    72,    91,    73,   106,   110,
      12,    39,    93,   102,   103,   104,   105,    24,     0,    33,
      97,     0,    23
};

static const yytype_int8 yycheck[] =
{
      43,     1,     2,    61,    60,    48,    21,    10,    11,     5,
      25,     7,    31,     9,    10,    11,    67,    17,    21,    70,
      23,    26,     0,    81,    29,    21,    29,    23,    31,    80,
      73,    27,    28,    29,    90,    31,     3,    23,    38,    95,
      23,     8,   102,   103,    87,    88,    29,     5,    31,     7,
     110,     9,    10,    11,     3,    61,    24,    10,    11,     8,
      29,    67,   105,    21,    70,    23,    23,    22,    25,    27,
      23,    29,    26,    31,    80,    81,    29,    24,    31,    25,
      86,    10,    11,    10,    11,    14,    15,    16,    17,    18,
      19,    21,    27,    23,    67,    25,     3,    70,    12,    13,
      21,    26,     3,    23,    23,    21,    21,    20,    26,     6,
       4,    37,    24,    24,    24,    24,    22,    16,    -1,    27,
      86,    -1,    15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,    35,    36,    37,    38,    39,    31,    64,
      64,     0,    37,    21,    23,    25,    23,     3,     8,    40,
      41,    42,    29,    65,    40,    64,    24,    22,    26,    24,
      25,    27,    43,    42,    21,    43,    26,    44,     3,    38,
      45,    64,     5,     7,     9,    10,    11,    21,    23,    28,
      43,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      56,    57,    58,    60,    61,    64,    65,    23,    21,    51,
      23,    51,    21,    20,    14,    15,    16,    17,    18,    19,
      55,    57,    52,    58,    12,    13,    59,    23,    25,    54,
      56,    21,    54,    24,    51,    56,    58,    60,    51,    62,
      63,    51,    24,    24,    24,    22,    26,    46,    46,    51,
       6,    46
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
      60,    61,    62,    62,    63,    63,    64,    65
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
       1,     4,     1,     0,     3,     1,     1,     1
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
#line 135 "cminus.y" /* yacc.c:1646  */
    {
            (yyval) = allocateNode("programa", none_expK, none_stK);
            addChild((yyval),(yyvsp[0]));
            tree = (yyval);
          }
#line 1419 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 143 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration-list", none_expK, none_stK);
                   addChild((yyval),(yyvsp[-1]));
                   addChild((yyval),(yyvsp[0]));}
#line 1427 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 147 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration-list", none_expK, none_stK);
                   addChild((yyval),(yyvsp[0]));}
#line 1434 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 152 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration", none_expK, none_stK);
               addChild((yyval),(yyvsp[0]));}
#line 1441 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 155 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("declaration", none_expK, none_stK);
               addChild((yyval),(yyvsp[0]));}
#line 1448 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 160 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("var-declaration", TypeK, none_stK);
                 /*addChild($$,$1);*/
                 (yyvsp[-1])->nodekind = statementK;
                 (yyvsp[-1])->kind.stmt = varK;
                 (yyvsp[-1])->type = intK;
                 addChild((yyval),(yyvsp[-1]));
                 /*$3 = allocateNode("SEMI");
                 addChild($$,$3);}*/
               }
#line 1462 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 168 "cminus.y" /* yacc.c:1646  */
    {
                 (yyval) = allocateNode("var-declaration", TypeK, none_stK);
                 (yyvsp[-4])->nodekind = statementK;
                 (yyvsp[-4])->kind.stmt = varK;
                 (yyvsp[-4])->type = intK;
                 addChild((yyval),(yyvsp[-4]));
               }
#line 1474 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 223 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("fun-declaration", TypeK, none_stK);
                 (yyval)->type = voidK;//SEE THIS
                 /*addChild($$,$1);*/
                 /*$2 = allocateToken("ID");*/
                 /*$3 = allocateNode("LPAREN", none_expK, none_stK);*/
                 (yyvsp[-4])->nodekind = statementK;
                 (yyvsp[-4])->kind.stmt = funcK;
                 (yyvsp[-4])->type = voidK;
                 addChild((yyval),(yyvsp[-4]));
                 addChild((yyvsp[-4]),(yyvsp[-2]));
                 addChild((yyvsp[-4]),(yyvsp[0]));
                 /*addChild($$,$3);
                 addChild($$,$4);*/
                 /*$5 = allocateNode("RPAREN", none_expK, none_stK);*/
                 /*addChild($$,$5);
                 addChild($$,$6);*/
               }
#line 1496 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 241 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("fun-declaration", TypeK, none_stK);
                                  (yyval)->type = intK;//SEE THIS
                                  /*addChild($$,$1);*/
                                  /*$2 = allocateToken("ID");*/
                                  /*$3 = allocateNode("LPAREN", none_expK, none_stK);*/
                                  (yyvsp[-4])->nodekind = statementK;
                                  (yyvsp[-4])->kind.stmt = funcK;
                                  (yyvsp[-4])->type = intK;
                                  addChild((yyval),(yyvsp[-4]));
                                  addChild((yyvsp[-4]),(yyvsp[-2]));
                                  addChild((yyvsp[-4]),(yyvsp[0]));
                                  /*addChild($$,$3);
                                  addChild($$,$4);*/
                                  /*$5 = allocateNode("RPAREN", none_expK, none_stK);*/
                                  /*addChild($$,$5);
                                  addChild($$,$6);*/}
#line 1517 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 260 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("params", none_expK, none_stK);
         addChild((yyval),(yyvsp[0]));}
#line 1524 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 263 "cminus.y" /* yacc.c:1646  */
    {(yyval) = NULL;}
#line 1530 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 267 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param-list", none_expK, none_stK);
             addChild((yyval),(yyvsp[-2]));
             (yyvsp[-1]) = allocateNode("COMMA", none_expK, none_stK);
             addChild((yyval),(yyvsp[-1]));
             addChild((yyval),(yyvsp[0]));}
#line 1540 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 273 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param-list", none_expK, none_stK);
             addChild((yyval),(yyvsp[0]));}
#line 1547 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 278 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param", TypeK, none_stK);
            (yyval)->type = intK;
             /*addChild($$,$1);*/
             /*$2 = allocateToken("ID");*/
             (yyvsp[0])->nodekind = statementK;
             (yyvsp[0])->kind.stmt = funcvarK;
             (yyvsp[0])->type = intK;
             addChild((yyval),(yyvsp[0]));}
#line 1560 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 287 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("param", TypeK, none_stK);
            (yyval)->type = intK;
            (yyvsp[-2])->nodekind = statementK;
            (yyvsp[-2])->kind.stmt = funcvecK;
            (yyvsp[-2])->type = intK;
             /*addChild($$,$1);*/
             /*$2 = allocateToken("ID");*/
             /*$3 = allocateNode("LBRACK", none_expK, none_stK);
             $4 = allocateNode("RBRACK", none_expK, none_stK);*/
             addChild((yyval),(yyvsp[-2]));
             /*addChild($$,$3);
             addChild($$,$4);*/
           }
#line 1578 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 303 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("compound-stmt", none_expK, none_stK);
               /*$1 = allocateNode("LCAPSULE", none_expK, none_stK);*/
               /*addChild($$,$1);*/
               addChild((yyval),(yyvsp[-2]));
               addChild((yyval),(yyvsp[-1]));
               /*$4 = allocateNode("RCAPSULE", none_expK, none_stK);*/
               /*addChild($$,$4);*/
             }
#line 1591 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 314 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("local-declarations", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1601 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 320 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("local-declarations", none_expK, none_stK);}
#line 1607 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 324 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement-list", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1617 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 330 "cminus.y" /* yacc.c:1646  */
    {(yyval) = allocateNode("statement-list", none_expK, none_stK);}
#line 1623 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 334 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1632 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 339 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1641 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 344 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1650 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 349 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1659 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 354 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("statement", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1668 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 361 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("expression-stmt", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-1]));
                        /*$2 = allocateNode("SEMI", none_expK, none_stK);
                        addChild($$,$2);*/
                      }
#line 1679 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 368 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("expression-stmt", none_expK, none_stK);
                        $1 = allocateNode("SEMI", none_expK, none_stK);
                        addChild($$,$1);*/
                      }
#line 1689 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 376 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("selection-stmt", none_expK, ifK);
                        /*$1 = allocateNode("IF", none_expK, none_stK);
                        addChild($$,$1);*/
                        /*$2 = allocateNode("LPAREN", none_expK, none_stK);
                        addChild($$,$2);*/
                        addChild((yyval),(yyvsp[-2]));
                        /*$4 = allocateNode("RPAREN", none_expK, none_stK);
                        addChild($$,$4);*/
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1705 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 388 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("selection-stmt", none_expK, ifK);
                        /*$1 = allocateNode("IF", none_expK, none_stK);*/
                        /*addChild($$,$1);
                        $2 = allocateNode("LPAREN", none_expK, none_stK);
                        addChild($$,$2);*/
                        addChild((yyval),(yyvsp[-4]));
                        /*$4 = allocateNode("RPAREN", none_expK, none_stK);
                        addChild($$,$4);*/
                        addChild((yyval),(yyvsp[-2]));
                        /*$6 = allocateNode("ELSE", none_expK, none_stK);
                        addChild($$,$6);*/
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1724 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 405 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("iteration-stmt", none_expK, whileK);
                        /*$1 = allocateNode("WHILE", none_expK, none_stK);
                        addChild($$,$1);
                        $2 = allocateNode("LPAREN", none_expK, none_stK);
                        addChild($$,$2);*/
                        addChild((yyval),(yyvsp[-2]));
                        /*$4 = allocateNode("RPAREN", none_expK, none_stK);
                        addChild($$,$4);*/
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1740 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 419 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("return-stmt", none_expK, returnK);
                        (yyval)->type = voidK;
                        /*$1 = allocateNode("RETURN", none_expK, none_stK);
                        addChild($$,$1);
                        $2 = allocateNode("SEMI", none_expK, none_stK);
                        addChild($$,$2);*/
                      }
#line 1753 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 429 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("return-stmt", none_expK, returnK);
                        /*$1 = allocateNode("RETURN", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval)->type = (yyvsp[-1])->type;
                        addChild((yyval),(yyvsp[-1]));
                        /*$3 = allocateNode("SEMI", none_expK, none_stK);
                        addChild($$,$3);*/
                      }
#line 1767 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 441 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("expression", none_expK, assignK);
                        addChild((yyval),(yyvsp[-2]));
                        /*$1 = allocateNode("ASSIGN", none_expK, none_stK);*/
                        /*addChild($$,$2);*/
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1779 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 449 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("expression", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1788 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 456 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("var", none_expK, none_stK);
                        /*$1 = allocateToken("ID");*/
                        (yyval)->type = intK;
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1799 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 463 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("var", none_expK, none_stK);
                        (yyval)->type = intK;
                        (yyval)->kind.exp = VecIndexK;
                        /*$1 = allocateToken("ID");*/
                        addChild((yyval),(yyvsp[-3]));
                        /*$2 = allocateNode("LBRACK", none_expK, none_stK);
                        addChild($$,$2);*/
                        addChild((yyval),(yyvsp[-1]));
                        /*$4 = allocateNode("RBRACK", none_expK, none_stK);
                        addChild($$,$4);*/
                      }
#line 1816 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 478 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("simple-expression", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1825 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 483 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("simple-expression", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1834 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 490 "cminus.y" /* yacc.c:1646  */
    {
                          (yyval) = allocateNode("comparative-expression", none_expK, none_stK);
                          addChild((yyval),(yyvsp[-2]));
                          addChild((yyval),(yyvsp[-1]));
                          addChild((yyval),(yyvsp[0]));
                        }
#line 1845 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 499 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("relop", RelOpK, none_stK);
                        $1 = allocateNode("LET", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("relop", RelOpK, none_stK);
                        (yyval)->attr.op = LET;
                        (yyval)->attr.name = "<=";
                        (yyval)->type = boolK;
                      }
#line 1859 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 509 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("relop", RelOpK, none_stK);
                        $1 = allocateNode("LT", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("relop", RelOpK, none_stK);
                        (yyval)->attr.op = LT;
                        (yyval)->attr.name = "<";
                        (yyval)->type = boolK;
                      }
#line 1873 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 519 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("relop", RelOpK, none_stK);
                        $1 = allocateNode("HT", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("relop", RelOpK, none_stK);
                        (yyval)->attr.op = HT;
                        (yyval)->attr.name = ">";
                        (yyval)->type = boolK;
                      }
#line 1887 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 529 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("relop", RelOpK, none_stK);
                        $1 = allocateNode("HET", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("relop", RelOpK, none_stK);
                        (yyval)->attr.op = HET;
                        (yyval)->attr.name = ">=";
                        (yyval)->type = boolK;
                      }
#line 1901 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 539 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("relop", RelOpK, none_stK);
                        (yyval)->attr.op = EQ;
                        (yyval)->attr.name = "==";
                        (yyval)->type = boolK;
                        /*$1 = allocateNode("EQ", none_expK, none_stK);
                        addChild($$,$1);*/
                      }
#line 1914 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 548 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("relop", RelOpK, none_stK);
                        $1 = allocateNode("NEQ", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("relop", RelOpK, none_stK);
                        (yyval)->attr.op = NEQ;
                        (yyval)->attr.name = "!=";
                        (yyval)->type = boolK;
                      }
#line 1928 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 560 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("additive-expression", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1939 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 567 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("additive-expression", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1949 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 573 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("additive-expression", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1958 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 580 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("addop", ArithOpK, none_stK);
                        $1 = allocateNode("PLUS", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("addop", ArithOpK, none_stK);
                        (yyval)->attr.op = PLUS;
                        (yyval)->attr.name = "+";
                        (yyval)->type = intK;
                      }
#line 1972 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 590 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("addop", ArithOpK, none_stK);
                        $1 = allocateNode("MINUS", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("addop", ArithOpK, none_stK);
                        (yyval)->attr.op = MINUS;
                        (yyval)->attr.name = "-";
                        (yyval)->type = intK;
                      }
#line 1986 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 602 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("term", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-2]));
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 1997 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 609 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2006 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 616 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("mulop", ArithOpK, none_stK);
                        $1 = allocateNode("TIMES", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("mulop", ArithOpK, none_stK);
                        (yyval)->attr.op = TIMES;
                        (yyval)->attr.name = "*";
                        (yyval)->type = intK;
                      }
#line 2020 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 626 "cminus.y" /* yacc.c:1646  */
    {
                        /*$$ = allocateNode("mulop", ArithOpK, none_stK);
                        $1 = allocateNode("OVER", none_expK, none_stK);
                        addChild($$,$1);*/
                        (yyval) = allocateNode("mulop", ArithOpK, none_stK);
                        (yyval)->attr.op = OVER;
                        (yyval)->attr.name = "/";
                        (yyval)->type = intK;
                      }
#line 2034 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 638 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor", none_expK, none_stK);
                        /*$1 = allocateNode("LPAREN", none_expK, none_stK);
                        addChild($$,$1);*/
                        addChild((yyval),(yyvsp[-1]));
                        /*$3 = allocateNode("RPAREN", none_expK, none_stK);
                        addChild($$,$3);*/
                      }
#line 2047 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 647 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor", none_expK, none_stK);
                        (yyvsp[0]) = allocateNode("var", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2057 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 653 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor", none_expK, none_stK);
                        (yyvsp[0]) = allocateNode("call", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2067 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 659 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("factor", none_expK, none_stK);
                        (yyvsp[0]) = allocateToken("NUMI");
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2077 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 673 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("call", none_expK, none_stK);
                        (yyval)->kind.exp = CallK;
                        /*$1 = allocateToken("ID");*/
                        addChild((yyval),(yyvsp[-3]));
                        /*$2 = allocateNode("LPAREN", none_expK, none_stK);
                        addChild($$,$2);*/
                        addChild((yyval),(yyvsp[-1]));
                        /*$4 = allocateNode("RPAREN", none_expK, none_stK);
                        addChild($$,$4);*/
                      }
#line 2093 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 687 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("args", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2102 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 692 "cminus.y" /* yacc.c:1646  */
    {
                  		(yyval) = allocateNode("args", none_expK, none_stK);
                  	}
#line 2110 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 698 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("arg-list", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-2]));
                        (yyvsp[-1]) = allocateNode("COMMA", none_expK, none_stK);
                        addChild((yyval),(yyvsp[-1]));
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2122 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 706 "cminus.y" /* yacc.c:1646  */
    {
                        (yyval) = allocateNode("arg-list", none_expK, none_stK);
                        addChild((yyval),(yyvsp[0]));
                      }
#line 2131 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 711 "cminus.y" /* yacc.c:1646  */
    {
  (yyval) = allocateNode("ID", IdK, none_stK);
  addChild((yyval),(yyvsp[0]));
}
#line 2140 "cminus.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 715 "cminus.y" /* yacc.c:1646  */
    {
  (yyval) = allocateNode("NUM", ConstK, none_stK);
  addChild((yyval),(yyvsp[0]));
}
#line 2149 "cminus.tab.c" /* yacc.c:1646  */
    break;


#line 2153 "cminus.tab.c" /* yacc.c:1646  */
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
#line 720 "cminus.y" /* yacc.c:1906  */



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
	TreeNode *branch = allocateNode(token, none_expK, none_stK);
	//puts( yytext );
//	sprintf(strExp, "%s", yytext);
	TreeNode *leaf = allocateNode(strExp.c_str(), none_expK, none_stK);//because it must be a char const*
  // TreeNode *leaf = allocateNode("galeto");
//	addChild(branch, leaf);
	return branch;
}

TreeNode * allocateNode(char const *node, expression_kind ek, statement_kind sk)/*, type_kind type, statement_kind sk)*/
{

  if(line_flag==0){
    reference_line = yylineno;
    line_flag = 1;
  }

	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->lineno = yylineno - reference_line;


  newNode->kind.exp = ek;
  newNode->kind.stmt = sk;
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
    printf("%s %d %d %d\n",tree->str, tree->lineno, tree->kind.exp, tree->type);


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
