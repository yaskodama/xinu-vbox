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

/* Substitute the type names.  */
#define YYSTYPE         KXSTYPE
#define YYLTYPE         KXLTYPE
/* Substitute the variable and function names.  */
#define yyparse         kxparse
#define yylex           kxlex
#define yyerror         kxerror
#define yydebug         kxdebug
#define yynerrs         kxnerrs
#define yylval          kxlval
#define yychar          kxchar
#define yylloc          kxlloc

/* First part of user prologue.  */
#line 7 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"

#include <xinu.h>
#include "kxc.h"
#define YYMALLOC(n)	kx_alloc(n)
#define YYFREE(p)	((void)(p))
#define YYSTACK_USE_ALLOCA 0
#define YYMAXDEPTH	2000
int	kxlex(void);
void	kxerror(const char *);

#line 92 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"

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

#include "kxc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NAME = 3,                       /* NAME  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_K_DEFACTOR = 6,                 /* "というアクターを定義する。"  */
  YYSYMBOL_K_HAS = 7,                      /* "を持つ。"  */
  YYSYMBOL_K_INIT = 8,                     /* "の初期値は"  */
  YYSYMBOL_K_TOSHI = 9,                    /* "とし、"  */
  YYSYMBOL_K_TOSURU = 10,                  /* "とする。"  */
  YYSYMBOL_T_MSG = 11,                     /* "というメッセージ"  */
  YYSYMBOL_K_RECV = 12,                    /* "を受け取ったとき、"  */
  YYSYMBOL_KORE = 13,                      /* "これで"  */
  YYSYMBOL_K_ENDDEF = 14,                  /* "の定義を終わる。"  */
  YYSYMBOL_K_RUN = 15,                     /* "実行を始める。"  */
  YYSYMBOL_K_ENDRUN = 16,                  /* "実行を終わる。"  */
  YYSYMBOL_MARU = 17,                      /* "。"  */
  YYSYMBOL_TEN = 18,                       /* "、"  */
  YYSYMBOL_SONOATO = 19,                   /* "その後、"  */
  YYSYMBOL_NARABA = 20,                    /* "ならば、"  */
  YYSYMBOL_DENAKEREBA = 21,                /* "でなければ、"  */
  YYSYMBOL_YORICHIISA = 22,                /* "より小さければ、"  */
  YYSYMBOL_SOUDENAKEREBA = 23,             /* "そうでなければ、"  */
  YYSYMBOL_K_BLOCK = 24,                   /* "次のことを行う。"  */
  YYSYMBOL_IJOU = 25,                      /* "以上。"  */
  YYSYMBOL_KARA = 26,                      /* "から"  */
  YYSYMBOL_MADE_NITSUITE = 27,             /* "までの各番号について、"  */
  YYSYMBOL_WA = 28,                        /* "は"  */
  YYSYMBOL_TO = 29,                        /* "と"  */
  YYSYMBOL_GA = 30,                        /* "が"  */
  YYSYMBOL_NI = 31,                        /* "に"  */
  YYSYMBOL_WO = 32,                        /* "を"  */
  YYSYMBOL_NO = 33,                        /* "の"  */
  YYSYMBOL_NO_MATSUBI = 34,                /* "の末尾"  */
  YYSYMBOL_NO_SENTOU_KARA = 35,            /* "の先頭から"  */
  YYSYMBOL_NO_ZENIN = 36,                  /* "の全員"  */
  YYSYMBOL_BANME = 37,                     /* "番目"  */
  YYSYMBOL_SOREZORE = 38,                  /* "それぞれ"  */
  YYSYMBOL_T_MOJIRETSU = 39,               /* "という文字列"  */
  YYSYMBOL_T_ACTOR = 40,                   /* "というアクター"  */
  YYSYMBOL_ICHITSU = 41,                   /* "1つ"  */
  YYSYMBOL_HYOUJI_S = 42,                  /* "表示する"  */
  YYSYMBOL_HYOUJI_R = 43,                  /* "表示し"  */
  YYSYMBOL_OKURU_S = 44,                   /* "送る"  */
  YYSYMBOL_OKURU_R = 45,                   /* "送り"  */
  YYSYMBOL_HENKOU_S = 46,                  /* "変更する"  */
  YYSYMBOL_HENKOU_R = 47,                  /* "変更し"  */
  YYSYMBOL_KUWAE_S = 48,                   /* "加える"  */
  YYSYMBOL_KUWAE_R = 49,                   /* "加え"  */
  YYSYMBOL_KUWAETA = 50,                   /* "加えた数"  */
  YYSYMBOL_TSUIKA_S = 51,                  /* "追加する"  */
  YYSYMBOL_TSUIKA_R = 52,                  /* "追加し"  */
  YYSYMBOL_TORIDASU_S = 53,                /* "取り出す"  */
  YYSYMBOL_TORIDASU_R = 54,                /* "取り出し"  */
  YYSYMBOL_NAZUKE_S = 55,                  /* "名付ける"  */
  YYSYMBOL_NAZUKE_R = 56,                  /* "名付け"  */
  YYSYMBOL_SEISEI_R = 57,                  /* "生成し"  */
  YYSYMBOL_YOUI_R = 58,                    /* "用意し"  */
  YYSYMBOL_HIITA = 59,                     /* "引いた数"  */
  YYSYMBOL_WARIAMARI = 60,                 /* "で割った余り"  */
  YYSYMBOL_NO_YOUSOSU = 61,                /* "の要素数"  */
  YYSYMBOL_HAI = 62,                       /* "はい"  */
  YYSYMBOL_IIE = 63,                       /* "いいえ"  */
  YYSYMBOL_NASHI = 64,                     /* "なし"  */
  YYSYMBOL_SORA = 65,                      /* "空"  */
  YYSYMBOL_SORA_HAIRETSU = 66,             /* "空の配列"  */
  YYSYMBOL_JIBUN = 67,                     /* "自分"  */
  YYSYMBOL_JIBUN_JISHIN = 68,              /* "自分自身"  */
  YYSYMBOL_GENZAI = 69,                    /* "現在の番号"  */
  YYSYMBOL_SONO = 70,                      /* "その"  */
  YYSYMBOL_LP = 71,                        /* "（"  */
  YYSYMBOL_RP = 72,                        /* "）"  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_program = 74,                   /* program  */
  YYSYMBOL_defs = 75,                      /* defs  */
  YYSYMBOL_def = 76,                       /* def  */
  YYSYMBOL_decl = 77,                      /* decl  */
  YYSYMBOL_names = 78,                     /* names  */
  YYSYMBOL_items = 79,                     /* items  */
  YYSYMBOL_item = 80,                      /* item  */
  YYSYMBOL_init = 81,                      /* init  */
  YYSYMBOL_inits = 82,                     /* inits  */
  YYSYMBOL_initp = 83,                     /* initp  */
  YYSYMBOL_header = 84,                    /* header  */
  YYSYMBOL_stmts = 85,                     /* stmts  */
  YYSYMBOL_stmt = 86,                      /* stmt  */
  YYSYMBOL_body = 87,                      /* body  */
  YYSYMBOL_ifstmt = 88,                    /* ifstmt  */
  YYSYMBOL_part = 89,                      /* part  */
  YYSYMBOL_cond = 90,                      /* cond  */
  YYSYMBOL_loop = 91,                      /* loop  */
  YYSYMBOL_clause_s = 92,                  /* clause_s  */
  YYSYMBOL_clause_r = 93,                  /* clause_r  */
  YYSYMBOL_disp = 94,                      /* disp  */
  YYSYMBOL_send = 95,                      /* send  */
  YYSYMBOL_sendarg = 96,                   /* sendarg  */
  YYSYMBOL_chg = 97,                       /* chg  */
  YYSYMBOL_add = 98,                       /* add  */
  YYSYMBOL_push = 99,                      /* push  */
  YYSYMBOL_take = 100,                     /* take  */
  YYSYMBOL_bind = 101,                     /* bind  */
  YYSYMBOL_maker = 102,                    /* maker  */
  YYSYMBOL_exprs = 103,                    /* exprs  */
  YYSYMBOL_expr = 104,                     /* expr  */
  YYSYMBOL_term = 105,                     /* term  */
  YYSYMBOL_arith = 106,                    /* arith  */
  YYSYMBOL_idx = 107                       /* idx  */
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined KXLTYPE_IS_TRIVIAL && KXLTYPE_IS_TRIVIAL \
             && defined KXSTYPE_IS_TRIVIAL && KXSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   299

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72
};

#if KXDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    52,    52,    55,    56,    60,    63,    65,    66,    68,
      69,    71,    72,    73,    75,    77,    78,    80,    83,    84,
      88,    89,    91,    92,    93,    94,    95,    97,    98,   100,
     101,   103,   104,   107,   108,   109,   111,   115,   115,   115,
     116,   116,   116,   117,   119,   119,   119,   120,   120,   120,
     121,   123,   125,   126,   127,   129,   130,   132,   134,   136,
     137,   139,   141,   143,   144,   148,   149,   151,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   171,   172,   173,   175,   176,
     177,   178
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "NUMBER",
  "STRING", "\"というアクターを定義する。\"", "\"を持つ。\"",
  "\"の初期値は\"", "\"とし、\"", "\"とする。\"", "\"というメッセージ\"",
  "\"を受け取ったとき、\"", "\"これで\"", "\"の定義を終わる。\"",
  "\"実行を始める。\"", "\"実行を終わる。\"", "\"。\"", "\"、\"",
  "\"その後、\"", "\"ならば、\"", "\"でなければ、\"",
  "\"より小さければ、\"", "\"そうでなければ、\"", "\"次のことを行う。\"",
  "\"以上。\"", "\"から\"", "\"までの各番号について、\"", "\"は\"",
  "\"と\"", "\"が\"", "\"に\"", "\"を\"", "\"の\"", "\"の末尾\"",
  "\"の先頭から\"", "\"の全員\"", "\"番目\"", "\"それぞれ\"",
  "\"という文字列\"", "\"というアクター\"", "\"1つ\"", "\"表示する\"",
  "\"表示し\"", "\"送る\"", "\"送り\"", "\"変更する\"", "\"変更し\"",
  "\"加える\"", "\"加え\"", "\"加えた数\"", "\"追加する\"", "\"追加し\"",
  "\"取り出す\"", "\"取り出し\"", "\"名付ける\"", "\"名付け\"",
  "\"生成し\"", "\"用意し\"", "\"引いた数\"", "\"で割った余り\"",
  "\"の要素数\"", "\"はい\"", "\"いいえ\"", "\"なし\"", "\"空\"",
  "\"空の配列\"", "\"自分\"", "\"自分自身\"", "\"現在の番号\"", "\"その\"",
  "\"（\"", "\"）\"", "$accept", "program", "defs", "def", "decl", "names",
  "items", "item", "init", "inits", "initp", "header", "stmts", "stmt",
  "body", "ifstmt", "part", "cond", "loop", "clause_s", "clause_r", "disp",
  "send", "sendarg", "chg", "add", "push", "take", "bind", "maker",
  "exprs", "expr", "term", "arith", "idx", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -106,    21,    16,  -106,    26,  -106,  -106,    42,    36,    47,
    -106,    71,  -106,    88,    99,   198,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,   120,   215,  -106,   111,  -106,   128,
    -106,  -106,   118,    11,    23,    31,    35,    45,    60,    61,
     119,    32,    22,   -27,  -106,   148,    76,   121,  -106,  -106,
     138,  -106,   -10,  -106,  -106,    -3,  -106,  -106,   139,   134,
      84,   198,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,   155,   215,   145,   159,
     215,   215,   156,   129,     5,  -106,  -106,    15,   158,  -106,
    -106,   116,  -106,   181,  -106,     4,    30,   124,  -106,   215,
     215,   215,   105,  -106,   128,  -106,   137,  -106,     3,   172,
     146,  -106,    -7,   152,    66,   149,   175,  -106,  -106,  -106,
     215,  -106,   150,  -106,   179,   174,   215,  -106,  -106,   215,
     228,   132,   173,   202,   144,  -106,  -106,  -106,   177,   224,
    -106,    83,   205,   128,  -106,  -106,  -106,  -106,   226,   -21,
    -106,  -106,  -106,  -106,     8,  -106,  -106,     7,  -106,   180,
     188,   168,   215,   209,   177,  -106,  -106,   177,  -106,     1,
     170,   182,  -106,  -106,  -106,   221,   223,  -106,   253,  -106,
    -106,  -106,  -106,   245,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     0,    20,     4,     0,     0,     0,
       9,    68,    70,    71,     0,     0,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,    21,     0,    24,     0,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    67,    84,     0,     0,     0,    72,     2,
       0,    25,    65,    69,    68,     0,    22,    20,     0,    29,
      65,     0,    37,    44,    38,    45,    39,    46,    40,    47,
      41,    48,    42,    49,    43,    50,     0,     0,     0,    51,
       0,     0,     0,     0,     0,    83,     7,     0,     0,    10,
      11,     0,    15,     0,    13,     0,    65,     0,    23,     0,
       0,     0,     0,    31,     0,    28,     0,    66,    71,     0,
       0,    64,     0,     0,     0,     0,     0,    81,    88,    89,
       0,    91,     0,     6,     0,     0,     0,    14,    12,     0,
       0,     0,     0,     0,     0,    32,    30,    62,    55,     0,
      58,    57,     0,     0,    33,    34,    35,    61,     0,     0,
      82,     8,     5,    16,     0,    65,    17,    71,    63,     0,
       0,     0,     0,     0,    55,    60,    36,    55,    90,     0,
       0,     0,    87,    56,    52,     0,     0,    18,     0,    86,
      85,    53,    54,     0,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
     133,  -106,   201,   -43,   -14,   255,  -100,  -106,  -106,  -106,
    -106,  -106,  -106,  -105,  -106,  -106,  -106,  -106,  -106,  -106,
     -44,    -8,  -106,   187,  -106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     6,    10,    87,    46,    89,    90,    91,
      92,    93,     8,    26,    27,    28,    59,    29,    30,    31,
      32,    33,    34,   163,    35,    36,    37,    38,    39,    40,
      41,    60,    43,    44,   122
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    50,    95,    94,   136,    99,    84,    52,   117,   118,
     100,   101,   129,   177,   138,    58,   129,    55,   169,     4,
      81,     3,   123,    99,   141,    82,    83,   142,   100,   101,
     178,     5,     7,    77,    85,    78,    79,    77,    96,    11,
      12,    13,    48,   166,   124,     9,    48,   105,    80,    14,
     128,   168,    81,    62,    63,    15,    80,    82,    83,   175,
     130,    77,   176,    78,    79,    82,    83,    64,    65,   107,
     110,   112,   113,   114,   119,    45,   120,    66,    67,    11,
      12,    13,   154,    68,    69,    42,   144,   145,   146,    88,
      58,   132,   133,   134,    42,    15,    70,    71,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    11,    12,
      13,    47,   149,    72,    73,    49,    74,    75,   155,    82,
      83,   156,   114,    53,    15,   126,   127,    48,    56,    58,
     135,    11,    12,    13,   -59,   -59,    61,    76,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    54,    12,
     108,    86,    57,    97,   173,    98,   103,   104,   106,   115,
     116,   125,    54,    12,    13,   131,   137,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,   139,   140,   143,
     148,   147,   151,   109,    11,    12,    13,   150,   152,   158,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      15,    11,    12,    13,   161,   159,   162,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,   111,    54,    12,
      13,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    54,    12,   157,   160,   164,   165,   167,   171,   170,
     172,   174,   179,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,   181,   180,   182,   183,   184,   102,   153,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      51,   121,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25
};

static const yytype_int16 yycheck[] =
{
       8,    15,    46,    46,   104,    26,    33,    15,     3,     4,
      31,    32,     8,    12,    11,    29,     8,    25,    11,     3,
      30,     0,     7,    26,    31,    35,    36,    34,    31,    32,
      29,    15,     6,    29,    61,    31,    32,    29,    46,     3,
       4,     5,    39,   143,    29,     3,    39,    61,    26,    13,
      93,    72,    30,    42,    43,    19,    26,    35,    36,   164,
      30,    29,   167,    31,    32,    35,    36,    44,    45,    77,
      78,    79,    80,    81,    69,    28,    71,    46,    47,     3,
       4,     5,   126,    48,    49,    93,    20,    21,    22,    13,
     104,    99,   100,   101,   102,    19,    51,    52,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     3,     4,
       5,    40,   120,    53,    54,    16,    55,    56,   126,    35,
      36,   129,   130,     3,    19,     9,    10,    39,    17,   143,
      25,     3,     4,     5,    51,    52,    18,    18,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     3,     4,
       5,     3,    24,    32,   162,    17,    17,    23,     3,     3,
      31,     3,     3,     4,     5,    41,    29,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,     5,    32,    27,
       5,    32,     3,    38,     3,     4,     5,    37,    14,    57,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      19,     3,     4,     5,    60,    32,    29,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    58,     3,     4,
       5,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,     3,     4,     5,    32,    11,    31,    11,    50,    59,
      72,    32,    72,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    32,    72,    32,     3,    12,    57,   126,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      15,    84,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,    75,     0,     3,    15,    76,     6,    85,     3,
      77,     3,     4,     5,    13,    19,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    86,    87,    88,    90,
      91,    92,    93,    94,    95,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,    28,    79,    40,    39,    16,
      87,    88,   104,     3,     3,   104,    17,    24,    87,    89,
     104,    18,    42,    43,    44,    45,    46,    47,    48,    49,
      51,    52,    53,    54,    55,    56,    18,    29,    31,    32,
      26,    30,    35,    36,    33,    61,     3,    78,    13,    80,
      81,    82,    83,    84,    86,   103,   104,    32,    17,    26,
      31,    32,    85,    17,    23,    87,     3,   104,     5,    38,
     104,    58,   104,   104,   104,     3,    31,     3,     4,    69,
      71,   106,   107,     7,    29,     3,     9,    10,    86,     8,
      30,    41,   104,   104,   104,    25,    89,    29,    11,     5,
      32,    31,    34,    27,    20,    21,    22,    32,     5,   104,
      37,     3,    14,    83,   103,   104,   104,     5,    57,    32,
      32,    60,    29,    96,    11,    31,    89,    11,    72,    11,
      59,    50,    72,   104,    32,    96,    96,    12,    29,    72,
      72,    32,    32,     3,    12
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    75,    75,    76,    77,    78,    78,    79,
      79,    80,    80,    80,    81,    82,    82,    83,    84,    84,
      85,    85,    86,    86,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    90,    90,    90,    91,    92,    92,    92,
      92,    92,    92,    92,    93,    93,    93,    93,    93,    93,
      93,    94,    95,    95,    95,    96,    96,    97,    98,    99,
      99,   100,   101,   102,   102,   103,   103,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   106,   106,   106,   107,   107,
     107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     7,     4,     1,     3,     0,
       2,     1,     2,     1,     2,     1,     3,     3,     5,     7,
       0,     2,     2,     3,     1,     2,     1,     1,     3,     2,
       4,     2,     3,     4,     4,     4,     5,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     6,     7,     7,     0,     2,     4,     4,     4,
       5,     4,     4,     5,     3,     1,     3,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     2,     1,     7,     7,     6,     1,     1,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = KXEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == KXEMPTY)                                        \
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
   Use KXerror or KXUNDEF. */
#define YYERRCODE KXUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if KXDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined KXLTYPE_IS_TRIVIAL && KXLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !KXDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !KXDEBUG */


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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined KXLTYPE_IS_TRIVIAL && KXLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = KXEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  if (yychar == KXEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= KXEOF)
    {
      yychar = KXEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == KXerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = KXUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = KXEMPTY;
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: defs "実行を始める。" stmts "これで" "実行を終わる。"  */
#line 53 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
            { kx_prog.defs = (yyvsp[-4].d); kx_prog.main = (yyvsp[-2].st); kx_prog.mline = (yylsp[-3]).first_line; kx_prog.mend = (yylsp[0]).first_line; }
#line 1731 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 3: /* defs: %empty  */
#line 55 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                            { (yyval.d) = NULL; }
#line 1737 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 4: /* defs: defs def  */
#line 56 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                            { (yyval.d) = kx_defappend((yyvsp[-1].d), (yyvsp[0].d)); }
#line 1743 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 5: /* def: NAME "というアクターを定義する。" decl items "これで" NAME "の定義を終わる。"  */
#line 61 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
            { (yyval.d) = kx_def((yyvsp[-6].s), (yyvsp[-4].n), (yyvsp[-3].it), (yyvsp[-1].s), (yylsp[-6]).first_line, (yylsp[0]).first_line); if (!(yyval.d)) YYABORT; }
#line 1749 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 6: /* decl: NAME "は" names "を持つ。"  */
#line 63 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.n) = (yyvsp[-1].n); }
#line 1755 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 7: /* names: NAME  */
#line 65 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.n) = kx_name((yyvsp[0].s), NULL); }
#line 1761 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 8: /* names: names "と" NAME  */
#line 66 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.n) = kx_name((yyvsp[0].s), (yyvsp[-2].n)); }
#line 1767 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 9: /* items: %empty  */
#line 68 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = NULL; }
#line 1773 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 10: /* items: items item  */
#line 69 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = kx_itemappend((yyvsp[-1].it), (yyvsp[0].it)); }
#line 1779 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 11: /* item: init  */
#line 71 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = (yyvsp[0].it); }
#line 1785 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 12: /* item: header stmt  */
#line 72 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = kx_item(1, (yyvsp[-1].s), (yyvsp[0].st), (yylsp[-1]).first_line, (yylsp[0]).last_line); }
#line 1791 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 13: /* item: stmt  */
#line 73 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = kx_item(2, NULL, (yyvsp[0].st), (yylsp[0]).first_line, (yylsp[0]).last_line); }
#line 1797 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 14: /* init: inits "とする。"  */
#line 75 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = (yyvsp[-1].it); }
#line 1803 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 15: /* inits: initp  */
#line 77 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = (yyvsp[0].it); }
#line 1809 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 16: /* inits: inits "とし、" initp  */
#line 78 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = kx_itemappend((yyvsp[-2].it), (yyvsp[0].it)); }
#line 1815 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 17: /* initp: exprs "の初期値は" expr  */
#line 80 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.it) = kx_inits((yyvsp[-2].l), (yyvsp[0].e), (yylsp[-2]).first_line); if (!(yyval.it)) YYABORT; }
#line 1821 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 18: /* header: expr "が" STRING "というメッセージ" "を受け取ったとき、"  */
#line 83 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                   { (yyval.s) = kx_header((yyvsp[-2].s), NULL); }
#line 1827 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 19: /* header: expr "が" STRING "というメッセージ" "と" NAME "を受け取ったとき、"  */
#line 84 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                   { (yyval.s) = kx_header((yyvsp[-4].s), (yyvsp[-1].s)); }
#line 1833 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 20: /* stmts: %empty  */
#line 88 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = NULL; }
#line 1839 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 21: /* stmts: stmts stmt  */
#line 89 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = kx_stappend((yyvsp[-1].st), (yyvsp[0].st)); }
#line 1845 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 22: /* stmt: body "。"  */
#line 91 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = (yyvsp[-1].st); }
#line 1851 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 23: /* stmt: "その後、" body "。"  */
#line 92 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = (yyvsp[-1].st); }
#line 1857 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 24: /* stmt: ifstmt  */
#line 93 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = (yyvsp[0].st); }
#line 1863 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 25: /* stmt: "その後、" ifstmt  */
#line 94 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = (yyvsp[0].st); }
#line 1869 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 26: /* stmt: loop  */
#line 95 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = (yyvsp[0].st); }
#line 1875 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 27: /* body: clause_s  */
#line 97 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = (yyvsp[0].st); }
#line 1881 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 28: /* body: clause_r "、" body  */
#line 98 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.st) = kx_stappend((yyvsp[-2].st), (yyvsp[0].st)); }
#line 1887 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 29: /* ifstmt: cond part  */
#line 100 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                            { (yyval.st) = kx_if((yyvsp[-1].e), (yyvsp[0].st), NULL, (yylsp[-1]).first_line); }
#line 1893 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 30: /* ifstmt: cond part "そうでなければ、" part  */
#line 101 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                            { (yyval.st) = kx_if((yyvsp[-3].e), (yyvsp[-2].st), (yyvsp[0].st), (yylsp[-3]).first_line); }
#line 1899 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 31: /* part: body "。"  */
#line 103 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                    { (yyval.st) = (yyvsp[-1].st); }
#line 1905 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 32: /* part: "次のことを行う。" stmts "以上。"  */
#line 104 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                    { (yyval.st) = (yyvsp[-1].st); }
#line 1911 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 33: /* cond: expr "が" expr "ならば、"  */
#line 107 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                    { (yyval.e) = kx_e2(E_EQ, (yyvsp[-3].e), (yyvsp[-1].e), NULL); }
#line 1917 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 34: /* cond: expr "が" expr "でなければ、"  */
#line 108 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                    { (yyval.e) = kx_e2(E_NE, (yyvsp[-3].e), (yyvsp[-1].e), NULL); }
#line 1923 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 35: /* cond: expr "が" expr "より小さければ、"  */
#line 109 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                    { (yyval.e) = kx_e2(E_LT, (yyvsp[-3].e), (yyvsp[-1].e), NULL); }
#line 1929 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 36: /* loop: expr "から" expr "までの各番号について、" part  */
#line 111 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                              { (yyval.st) = kx_loop((yyvsp[-4].e), (yyvsp[-2].e), (yyvsp[0].st), (yylsp[-4]).first_line); }
#line 1935 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 37: /* clause_s: disp "表示する"  */
#line 115 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                          { (yyval.st) = (yyvsp[-1].st); }
#line 1941 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 38: /* clause_s: send "送る"  */
#line 115 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                         { (yyval.st) = (yyvsp[-1].st); }
#line 1947 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 39: /* clause_s: chg "変更する"  */
#line 115 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                                                     { (yyval.st) = (yyvsp[-1].st); }
#line 1953 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 40: /* clause_s: add "加える"  */
#line 116 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                          { (yyval.st) = (yyvsp[-1].st); }
#line 1959 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 41: /* clause_s: push "追加する"  */
#line 116 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                         { (yyval.st) = (yyvsp[-1].st); }
#line 1965 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 42: /* clause_s: take "取り出す"  */
#line 116 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                                                        { (yyval.st) = (yyvsp[-1].st); }
#line 1971 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 43: /* clause_s: bind "名付ける"  */
#line 117 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                          { (yyval.st) = (yyvsp[-1].st); }
#line 1977 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 44: /* clause_r: disp "表示し"  */
#line 119 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                          { (yyval.st) = (yyvsp[-1].st); }
#line 1983 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 45: /* clause_r: send "送り"  */
#line 119 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                         { (yyval.st) = (yyvsp[-1].st); }
#line 1989 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 46: /* clause_r: chg "変更し"  */
#line 119 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                                                     { (yyval.st) = (yyvsp[-1].st); }
#line 1995 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 47: /* clause_r: add "加え"  */
#line 120 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                          { (yyval.st) = (yyvsp[-1].st); }
#line 2001 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 48: /* clause_r: push "追加し"  */
#line 120 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                         { (yyval.st) = (yyvsp[-1].st); }
#line 2007 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 49: /* clause_r: take "取り出し"  */
#line 120 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                                                        { (yyval.st) = (yyvsp[-1].st); }
#line 2013 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 50: /* clause_r: bind "名付け"  */
#line 121 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                          { (yyval.st) = (yyvsp[-1].st); }
#line 2019 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 51: /* disp: exprs "を"  */
#line 123 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_DISP, (yyvsp[-1].l), NULL, NULL, NULL, (yylsp[-1]).first_line); }
#line 2025 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 52: /* send: exprs "に" STRING "というメッセージ" sendarg "を"  */
#line 125 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_SEND, (yyvsp[-5].l), (yyvsp[-1].e), NULL, (yyvsp[-3].s), (yylsp[-5]).first_line); }
#line 2031 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 53: /* send: exprs "に" "それぞれ" STRING "というメッセージ" sendarg "を"  */
#line 126 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_SEND, (yyvsp[-6].l), (yyvsp[-1].e), NULL, (yyvsp[-3].s), (yylsp[-6]).first_line); }
#line 2037 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 54: /* send: expr "の全員" "に" STRING "というメッセージ" sendarg "を"  */
#line 127 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_ZENIN, NULL, (yyvsp[-6].e), (yyvsp[-1].e), (yyvsp[-3].s), (yylsp[-6]).first_line); }
#line 2043 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 55: /* sendarg: %empty  */
#line 129 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = NULL; }
#line 2049 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 56: /* sendarg: "と" expr  */
#line 130 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = (yyvsp[0].e); }
#line 2055 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 57: /* chg: exprs "を" expr "に"  */
#line 132 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_CHG, (yyvsp[-3].l), (yyvsp[-1].e), NULL, NULL, (yylsp[-3]).first_line); }
#line 2061 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 58: /* add: exprs "に" expr "を"  */
#line 134 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_ADD, (yyvsp[-3].l), (yyvsp[-1].e), NULL, NULL, (yylsp[-3]).first_line); }
#line 2067 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 59: /* push: exprs "を" expr "に"  */
#line 136 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_PUSH, (yyvsp[-3].l), (yyvsp[-1].e), NULL, NULL, (yylsp[-3]).first_line); }
#line 2073 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 60: /* push: exprs "を" expr "の末尾" "に"  */
#line 137 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_PUSH, (yyvsp[-4].l), (yyvsp[-2].e), NULL, NULL, (yylsp[-4]).first_line); }
#line 2079 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 61: /* take: expr "の先頭から" NAME "を"  */
#line 139 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_st(S_TAKE, NULL, kx_e(E_NAME, (yyvsp[-1].s)), (yyvsp[-3].e), NULL, (yylsp[-3]).first_line); }
#line 2085 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 62: /* bind: maker "、" NAME "と"  */
#line 141 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.st) = kx_bind((yyvsp[-3].e), (yyvsp[-1].s), (yylsp[-3]).first_line); }
#line 2091 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 63: /* maker: NAME "というアクター" "を" "1つ" "生成し"  */
#line 143 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.e) = kx_e(E_NEW, (yyvsp[-4].s)); }
#line 2097 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 64: /* maker: exprs "を" "用意し"  */
#line 144 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                                     { (yyval.e) = (yyvsp[-2].l)->e; }
#line 2103 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 65: /* exprs: expr  */
#line 148 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.l) = kx_list((yyvsp[0].e), NULL); }
#line 2109 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 66: /* exprs: exprs "と" expr  */
#line 149 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.l) = kx_list((yyvsp[0].e), (yyvsp[-2].l)); }
#line 2115 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 67: /* expr: term  */
#line 151 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = (yyvsp[0].e); }
#line 2121 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 68: /* term: NAME  */
#line 153 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_NAME, (yyvsp[0].s)); }
#line 2127 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 69: /* term: "その" NAME  */
#line 154 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_NAME, (yyvsp[0].s)); }
#line 2133 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 70: /* term: NUMBER  */
#line 155 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_NUM, (yyvsp[0].s)); }
#line 2139 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 71: /* term: STRING  */
#line 156 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_STR, (yyvsp[0].s)); }
#line 2145 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 72: /* term: STRING "という文字列"  */
#line 157 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_STR, (yyvsp[-1].s)); }
#line 2151 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 73: /* term: "はい"  */
#line 158 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_TRUE, "はい"); }
#line 2157 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 74: /* term: "いいえ"  */
#line 159 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_FALSE, "いいえ"); }
#line 2163 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 75: /* term: "なし"  */
#line 160 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_NONE, "なし"); }
#line 2169 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 76: /* term: "空"  */
#line 161 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_ARR, "空"); }
#line 2175 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 77: /* term: "空の配列"  */
#line 162 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_ARR, "空の配列"); }
#line 2181 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 78: /* term: "自分"  */
#line 163 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_SELF, "自分"); }
#line 2187 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 79: /* term: "自分自身"  */
#line 164 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_SELF, "自分"); }
#line 2193 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 80: /* term: "現在の番号"  */
#line 165 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_CUR, "現在の番号"); }
#line 2199 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 81: /* term: term "の" NAME  */
#line 166 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e2(E_FIELD, (yyvsp[-2].e), kx_e(E_NAME, (yyvsp[0].s)), "の"); }
#line 2205 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 82: /* term: term "の" idx "番目"  */
#line 167 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e2(E_INDEX, (yyvsp[-3].e), (yyvsp[-1].e), "番目"); }
#line 2211 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 83: /* term: term "の要素数"  */
#line 168 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e2(E_LEN, (yyvsp[-1].e), NULL, "の要素数"); }
#line 2217 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 84: /* term: arith  */
#line 169 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = (yyvsp[0].e); }
#line 2223 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 85: /* arith: "（" expr "に" expr "を" "加えた数" "）"  */
#line 171 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                            { (yyval.e) = kx_e2(E_ADD, (yyvsp[-5].e), (yyvsp[-3].e), "足す"); }
#line 2229 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 86: /* arith: "（" expr "から" expr "を" "引いた数" "）"  */
#line 172 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                            { (yyval.e) = kx_e2(E_SUB, (yyvsp[-5].e), (yyvsp[-3].e), "引く"); }
#line 2235 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 87: /* arith: "（" expr "を" expr "で割った余り" "）"  */
#line 173 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                            { (yyval.e) = kx_e2(E_MOD, (yyvsp[-4].e), (yyvsp[-2].e), "で割った余り"); }
#line 2241 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 88: /* idx: NUMBER  */
#line 175 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_NUM, (yyvsp[0].s)); }
#line 2247 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 89: /* idx: "現在の番号"  */
#line 176 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = kx_e(E_CUR, "現在の番号"); }
#line 2253 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 90: /* idx: "（" expr "）"  */
#line 177 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = (yyvsp[-1].e); }
#line 2259 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;

  case 91: /* idx: arith  */
#line 178 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
                                { (yyval.e) = (yyvsp[0].e); }
#line 2265 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"
    break;


#line 2269 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.c"

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
  *++yylsp = yyloc;

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
  yytoken = yychar == KXEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= KXEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == KXEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = KXEMPTY;
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  if (yychar != KXEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 180 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"

