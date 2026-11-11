/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_KX_USERS_KODAMAY_KOTONOHA_XINU_KXC_KXC_TAB_H_INCLUDED
# define YY_KX_USERS_KODAMAY_KOTONOHA_XINU_KXC_KXC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef KXDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define KXDEBUG 1
#  else
#   define KXDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define KXDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined KXDEBUG */
#if KXDEBUG
extern int kxdebug;
#endif

/* Token kinds.  */
#ifndef KXTOKENTYPE
# define KXTOKENTYPE
  enum kxtokentype
  {
    KXEMPTY = -2,
    KXEOF = 0,                     /* "end of file"  */
    KXerror = 256,                 /* error  */
    KXUNDEF = 257,                 /* "invalid token"  */
    NAME = 258,                    /* NAME  */
    NUMBER = 259,                  /* NUMBER  */
    STRING = 260,                  /* STRING  */
    K_DEFACTOR = 261,              /* "というアクターを定義する。"  */
    K_HAS = 262,                   /* "を持つ。"  */
    K_INIT = 263,                  /* "の初期値は"  */
    K_TOSHI = 264,                 /* "とし、"  */
    K_TOSURU = 265,                /* "とする。"  */
    T_MSG = 266,                   /* "というメッセージ"  */
    K_RECV = 267,                  /* "を受け取ったとき、"  */
    KORE = 268,                    /* "これで"  */
    K_ENDDEF = 269,                /* "の定義を終わる。"  */
    K_RUN = 270,                   /* "実行を始める。"  */
    K_ENDRUN = 271,                /* "実行を終わる。"  */
    MARU = 272,                    /* "。"  */
    TEN = 273,                     /* "、"  */
    SONOATO = 274,                 /* "その後、"  */
    NARABA = 275,                  /* "ならば、"  */
    DENAKEREBA = 276,              /* "でなければ、"  */
    YORICHIISA = 277,              /* "より小さければ、"  */
    SOUDENAKEREBA = 278,           /* "そうでなければ、"  */
    K_BLOCK = 279,                 /* "次のことを行う。"  */
    IJOU = 280,                    /* "以上。"  */
    KARA = 281,                    /* "から"  */
    MADE_NITSUITE = 282,           /* "までの各番号について、"  */
    WA = 283,                      /* "は"  */
    TO = 284,                      /* "と"  */
    GA = 285,                      /* "が"  */
    NI = 286,                      /* "に"  */
    WO = 287,                      /* "を"  */
    NO = 288,                      /* "の"  */
    NO_MATSUBI = 289,              /* "の末尾"  */
    NO_SENTOU_KARA = 290,          /* "の先頭から"  */
    NO_ZENIN = 291,                /* "の全員"  */
    BANME = 292,                   /* "番目"  */
    SOREZORE = 293,                /* "それぞれ"  */
    T_MOJIRETSU = 294,             /* "という文字列"  */
    T_ACTOR = 295,                 /* "というアクター"  */
    ICHITSU = 296,                 /* "1つ"  */
    HYOUJI_S = 297,                /* "表示する"  */
    HYOUJI_R = 298,                /* "表示し"  */
    OKURU_S = 299,                 /* "送る"  */
    OKURU_R = 300,                 /* "送り"  */
    HENKOU_S = 301,                /* "変更する"  */
    HENKOU_R = 302,                /* "変更し"  */
    KUWAE_S = 303,                 /* "加える"  */
    KUWAE_R = 304,                 /* "加え"  */
    KUWAETA = 305,                 /* "加えた数"  */
    TSUIKA_S = 306,                /* "追加する"  */
    TSUIKA_R = 307,                /* "追加し"  */
    TORIDASU_S = 308,              /* "取り出す"  */
    TORIDASU_R = 309,              /* "取り出し"  */
    NAZUKE_S = 310,                /* "名付ける"  */
    NAZUKE_R = 311,                /* "名付け"  */
    SEISEI_R = 312,                /* "生成し"  */
    YOUI_R = 313,                  /* "用意し"  */
    HIITA = 314,                   /* "引いた数"  */
    WARIAMARI = 315,               /* "で割った余り"  */
    NO_YOUSOSU = 316,              /* "の要素数"  */
    HAI = 317,                     /* "はい"  */
    IIE = 318,                     /* "いいえ"  */
    NASHI = 319,                   /* "なし"  */
    SORA = 320,                    /* "空"  */
    SORA_HAIRETSU = 321,           /* "空の配列"  */
    JIBUN = 322,                   /* "自分"  */
    JIBUN_JISHIN = 323,            /* "自分自身"  */
    GENZAI = 324,                  /* "現在の番号"  */
    SONO = 325,                    /* "その"  */
    LP = 326,                      /* "（"  */
    RP = 327                       /* "）"  */
  };
  typedef enum kxtokentype kxtoken_kind_t;
#endif

/* Value type.  */
#if ! defined KXSTYPE && ! defined KXSTYPE_IS_DECLARED
union KXSTYPE
{
#line 20 "/Users/kodamay/kotonoha/xinu/kxc/kxc.y"
 const char *s; struct kxe *e; struct kxl *l; struct kxs *st; struct kxitem *it; struct kxdef *d; struct kxname *n; int32 i; 

#line 147 "/Users/kodamay/kotonoha/xinu/kxc/kxc.tab.h"

};
typedef union KXSTYPE KXSTYPE;
# define KXSTYPE_IS_TRIVIAL 1
# define KXSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined KXLTYPE && ! defined KXLTYPE_IS_DECLARED
typedef struct KXLTYPE KXLTYPE;
struct KXLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define KXLTYPE_IS_DECLARED 1
# define KXLTYPE_IS_TRIVIAL 1
#endif


extern KXSTYPE kxlval;
extern KXLTYPE kxlloc;

int kxparse (void);


#endif /* !YY_KX_USERS_KODAMAY_KOTONOHA_XINU_KXC_KXC_TAB_H_INCLUDED  */
