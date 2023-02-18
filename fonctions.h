#include<stdio.h>
#include<stdlib.h>
/* variables prédéfinies */
typedef enum {
    //keywords
    PROGRAM_TOKEN,
    VARIABLES_TOKEN,
    MAIN_TOKEN,
    FOR_TOKEN,
    IN_TOKEN,
    END_TOKEN,
    WHILE_TOKEN,
    DONE_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    INT_TOKEN,
    FLOAT_TOKEN,
    STRING_TOKEN,
    BOOL_TOKEN,
    TRUE_TOKEN,
    FALSE_TOKEN,
    //symbols
    PNTVIR_TOKEN,  // ;
    PNT_TOKEN,     // .
    DPNT_TOKEN,    // :
    VIR_TOKEN,     // ,
    PBO_TOKEN,     // {
    PBF_TOKEN,     // }
    PO_TOKEN,      // (
    PF_TOKEN,      // )
    DQTS_TOKEN,    // "
    SQTS_TOKEN,    // '
    CRO_TOKEN,     // [
    CRF_TOKEN,     // ]
    //operateurs
    AFF_TOKEN,     // =
    PLS_TOKEN,     // +
    SOU_TOKEN,     // -
    MUL_TOKEN,     // *
    DIV_TOKEN,     // /
    EQ_TOKEN,      // ==
    NEQ_TOKEN,     // !=
    INF_TOKEN,     // <
    SUP_TOKEN,     // >
    INFE_TOKEN,    // <=
    SUPE_TOKEN,    // >=
    AND_TOKEN,     // AND
    OR_TOKEN,      // OR
    //fonctions
    WRITE_TOKEN,   // write()
    READ_TOKEN,    // read()
    //autre
    IDVAL_TOKEN,
    NUM_TOKEN,
    ID_TOKEN,
    ERROR_TOKEN,
    EOF_TOKEN,
}TOKEN;
typedef struct Element Element;
struct Element
{
    TOKEN token;
    Element *suivant;
};
typedef struct Pile Pile;
struct Pile
{
    Element *premier;
};
/* Global variables */
FILE* fichier;
char carActuel;
char chaine[50];
int number;
static int tmp;
static int ligne;
TOKEN tokenCourant;
Pile *pileTokens;
static int tokenNum;
#define MAX_STR 50
#define MAX_ID_VALEUR 10

/*********PILE*************/
Pile *initialiser();
void empiler(Pile*,TOKEN);
TOKEN depiler(Pile*);
/**************************/

void init(char *);
TOKEN lexicale();
void carSuivant();
void carPrecedent();
void testerTokenCourant(TOKEN,TOKEN);
int testerRetourne(TOKEN,TOKEN);
void ERROR(char*);
void PROGRAM();
void VARIABLES();
void MAIN();
void VARLIST();
void VARSLIGNE();
void TYPE();
void VARSNAME();
void VARSNAME_P();
void INSTRUCTIONSLIST();
void INSTRUCTIONLIGNE();
void EXPRAFFECTATION();
void EXPRAFFECTATION();
/*Grammaire d'une expression arithmetique*/
void EXPRMATH();
void D();
void op();
void A();
void B();
/****************************************/
/*Grammaire d'une fonction*/
void EXPFONCTION();
void FONCTION();
void FONCTION_P();
/*Grammaire if else*/
void EXPIF();
void EXPIF_P();
/*Operation logique*/
void CND();
void CONDITION();
void CON();
void TF();
void VAL();
void OPERATION();
void OP();
void OPLOGIC();
/*Boucles*/
void BOUCLE();
void BOUCLEWHILE();
void BOUCLEFOR();
void BF();
