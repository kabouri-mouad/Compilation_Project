#include "fonctions.h"
#include<string.h>
Pile *initialiser()
{
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}
void empiler(Pile *pile, TOKEN nouveauToken)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->token = nouveauToken;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}
TOKEN depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    TOKEN token;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL)
    {
        token = elementDepile->token;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return token;
}
void init(char *path){
    fichier = fopen(path,"r");
}
void carSuivant(){
    carActuel = fgetc(fichier);
}
void carPrecedent(){
    fseek(fichier,-1,SEEK_CUR);
}
TOKEN lexicale(){
    int index=0,typeChaine = 8;
    number = 0;
    carSuivant();
    while(carActuel == ' ' || carActuel == '\n' ) 
    {
        if(carActuel == '\n') ligne++;
        carSuivant();
    }
    while(carActuel >= '0' && carActuel <= '9'){
        number = number * 10 + (carActuel - '0');
        carSuivant();
        typeChaine = 0;
    }
    if(carActuel >= 'a' && carActuel <= 'z'){
        while((carActuel >= 'a' && carActuel <= 'z') || carActuel=='_' || (carActuel >= '0' && carActuel <= '9')){
            chaine[index] = carActuel;
            index++;
            carSuivant();
            typeChaine = 1;
        }
        chaine[index] = '\0';
    }
    if(typeChaine == 0){
        carPrecedent();
        return NUM_TOKEN;
    }
    if(typeChaine == 1){
        carPrecedent();
        if(strcmp(chaine,"program")==0) return PROGRAM_TOKEN;
        else if(strcmp(chaine,"variables")==0) return VARIABLES_TOKEN;
        else if(strcmp(chaine,"main")==0) return MAIN_TOKEN;
        else if(strcmp(chaine,"int")==0) return INT_TOKEN;
        else if(strcmp(chaine,"float")==0) return FLOAT_TOKEN;
        else if(strcmp(chaine,"string")==0) return STRING_TOKEN;
        else if(strcmp(chaine,"bool")==0) return BOOL_TOKEN;
        else if(strcmp(chaine,"for")==0) return FOR_TOKEN;
        else if(strcmp(chaine,"in")==0) return IN_TOKEN;
        else if(strcmp(chaine,"while")==0) return WHILE_TOKEN;
        else if(strcmp(chaine,"true")==0) return TRUE_TOKEN;
        else if(strcmp(chaine,"false")==0) return FALSE_TOKEN;
        else if(strcmp(chaine,"AND")==0) return AND_TOKEN;
        else if(strcmp(chaine,"OR")==0) return OR_TOKEN;
        else if(strcmp(chaine,"if")==0) return IF_TOKEN;
        else if(strcmp(chaine,"else")==0) return ELSE_TOKEN;
        else if(strcmp(chaine,"end")==0) return END_TOKEN;
        else if(strcmp(chaine,"write")==0) return WRITE_TOKEN;
        else if(strcmp(chaine,"read")==0) return READ_TOKEN;
        else if(strcmp(chaine,"done")==0) return DONE_TOKEN;
        else return ID_TOKEN;
    }
    switch(carActuel){
        case '+': return PLS_TOKEN; break;
        case '-': return SOU_TOKEN; break;
        case '*': return MUL_TOKEN; break;
        case '/': return DIV_TOKEN; break;
        case '=': carSuivant(); carPrecedent(); // it solves single digit issue
            if(carActuel == '=') return EQ_TOKEN;
            else return AFF_TOKEN;
        break;
        case '!': carSuivant();
            if(carActuel == '=') return NEQ_TOKEN;
            else                 return ERROR_TOKEN;
        break;
        case '>': carSuivant(); carPrecedent(); // it solves single digit issue
            if(carActuel == '=') return SUPE_TOKEN;
            else                 return SUP_TOKEN;
        break;
        case '<': carSuivant(); carPrecedent(); // it solves single digit issue
            if(carActuel == '=') return INFE_TOKEN;
            else                 return INF_TOKEN;            
        break;
        case '(': return PO_TOKEN; break;
        case ')': return PF_TOKEN; break;
        case '{': return PBO_TOKEN; break;
        case '}': return PBF_TOKEN; break;
        case '[': return CRO_TOKEN; break;
        case ']': return CRF_TOKEN; break;
        case '.': return PNT_TOKEN; break;
        case ';': return PNTVIR_TOKEN; break;
        case ',': return VIR_TOKEN; break;
        case ':': return DPNT_TOKEN; break;
        case EOF: return EOF_TOKEN; break;
        default : return ERROR_TOKEN;
    }
}
void testerTokenCourant(TOKEN token,TOKEN tokenCourantP){
    tokenNum++;
    if (token != tokenCourantP)
    {
        ERROR("Syntaxe");
    } 
}
int testerRetourne(TOKEN token,TOKEN tokenCourantP){
    tokenNum++;
    if (token != tokenCourantP)
    {
        return 0;
    }else{
        return 1;
    }
}
void ERROR(char *err){
    printf("ligne %d : You've got an error in %s !\n",ligne,err);
    exit(EXIT_FAILURE);
}
void BOUCLEWHILE(){
    testerTokenCourant(WHILE_TOKEN,tokenCourant);
    CND();
    testerTokenCourant(DPNT_TOKEN,tokenCourant=lexicale());
    INSTRUCTIONSLIST();
    testerTokenCourant(END_TOKEN,tokenCourant);
}
void BF(){
    tokenCourant=lexicale();
    if(tokenCourant == ID_TOKEN){
        testerTokenCourant(ID_TOKEN,tokenCourant);
        testerTokenCourant(PNT_TOKEN,tokenCourant=lexicale());
        testerTokenCourant(PNT_TOKEN,tokenCourant=lexicale());
        testerTokenCourant(ID_TOKEN,tokenCourant=lexicale());
        testerTokenCourant(DPNT_TOKEN,tokenCourant=lexicale());
        INSTRUCTIONSLIST();
        testerTokenCourant(END_TOKEN,tokenCourant);
    }else if(tokenCourant == NUM_TOKEN){
        testerTokenCourant(NUM_TOKEN,tokenCourant);
        testerTokenCourant(PNT_TOKEN,tokenCourant=lexicale());
        testerTokenCourant(PNT_TOKEN,tokenCourant=lexicale());
        testerTokenCourant(NUM_TOKEN,tokenCourant=lexicale());
        testerTokenCourant(DPNT_TOKEN,tokenCourant=lexicale());
        INSTRUCTIONSLIST();
        testerTokenCourant(END_TOKEN,tokenCourant);
    }else{
        ERROR("Boucle for");
    }
}
void BOUCLEFOR(){
    testerTokenCourant(FOR_TOKEN,tokenCourant);
    testerTokenCourant(ID_TOKEN,tokenCourant=lexicale());
    testerTokenCourant(IN_TOKEN,tokenCourant=lexicale());
    BF();
}
void BOUCLE(){
    if(tokenCourant == FOR_TOKEN) BOUCLEFOR();
    else if(tokenCourant == WHILE_TOKEN) BOUCLEWHILE();
    else ERROR("BOUCLE");
}
void op(){
    int test = testerRetourne(PLS_TOKEN,tokenCourant)
             ||testerRetourne(SOU_TOKEN,tokenCourant)
             ||testerRetourne(MUL_TOKEN,tokenCourant)
             ||testerRetourne(DIV_TOKEN,tokenCourant);
    if(!test){
        ERROR("Operateur mathematique");
    }
}
void B(){
    if(tokenCourant == PO_TOKEN){
        testerTokenCourant(PO_TOKEN,tokenCourant=lexicale());
        EXPRMATH();
        testerTokenCourant(PF_TOKEN,tokenCourant=lexicale());
    }else{
        EXPRMATH();
    }
}
void A(){
    tokenCourant = lexicale();
    if(tokenCourant != PNTVIR_TOKEN ){
        op();
        EXPRMATH();    // You can use B();
    }
}
void D(){
    tokenCourant = lexicale();
    int test = testerRetourne(NUM_TOKEN,tokenCourant)
             ||testerRetourne(ID_TOKEN,tokenCourant);
    if(!test){
        ERROR("Expression mathematique");
    }
}
void EXPRMATH(){
    D();
    A();
}
void EXPRAFFECTATION(){
    testerTokenCourant(ID_TOKEN,tokenCourant);
    testerTokenCourant(AFF_TOKEN,tokenCourant=lexicale());
    EXPRMATH();
    testerTokenCourant(PNTVIR_TOKEN,tokenCourant); //Warning
}
void FONCTION_P(){
    tokenCourant=lexicale();
    if(tokenCourant==PF_TOKEN){
        testerTokenCourant(PF_TOKEN,tokenCourant);
    }
    else if(tokenCourant==ID_TOKEN){
        testerTokenCourant(ID_TOKEN,tokenCourant); // a modifier fonction(id)
        testerTokenCourant(PF_TOKEN,tokenCourant=lexicale()); 
    }else{
        ERROR("En arguments de la fonction");
    }
}
void FONCTION(){
    testerTokenCourant(ID_TOKEN,tokenCourant=lexicale());
    testerTokenCourant(PO_TOKEN,tokenCourant=lexicale());
    FONCTION_P();
}
void EXPFONCTION(){
    testerTokenCourant(ID_TOKEN,tokenCourant);
    testerTokenCourant(AFF_TOKEN,tokenCourant=lexicale());
    FONCTION();
    testerTokenCourant(PNTVIR_TOKEN,tokenCourant=lexicale()); //warning
}
void INSTS(){
    tokenCourant = lexicale();
    INSTRUCTIONSLIST();
}
void EXPIF_P(){
    if(tokenCourant==END_TOKEN){
        testerTokenCourant(END_TOKEN,tokenCourant);
    }else if(tokenCourant==ELSE_TOKEN){
        testerTokenCourant(ELSE_TOKEN,tokenCourant);
        INSTS();
        testerTokenCourant(END_TOKEN,tokenCourant=lexicale());
    }else{
        ERROR("If statement");
    }
}
void TF(){
    int test = testerRetourne(TRUE_TOKEN,tokenCourant)
             ||testerRetourne(FALSE_TOKEN,tokenCourant);
    if(!test){
        ERROR("Condition");
    }
}
void OPLOGIC(){
    tokenCourant = lexicale();
    int test = testerRetourne(SUP_TOKEN,tokenCourant)
        ||testerRetourne(INF_TOKEN,tokenCourant)
        ||testerRetourne(EQ_TOKEN,tokenCourant)
        ||testerRetourne(NEQ_TOKEN,tokenCourant)
        ||testerRetourne(SUPE_TOKEN,tokenCourant)
        ||testerRetourne(INFE_TOKEN,tokenCourant);
    if(!test){
        ERROR("Logical operator");
    }
}
void OP(){
    tokenCourant = lexicale();
    if(tokenCourant != DPNT_TOKEN){
        int test = testerRetourne(AND_TOKEN,tokenCourant)
                ||testerRetourne(OR_TOKEN,tokenCourant);
        if(!test){
            ERROR("Condition value");
        }
    }
}
void OPERATION(){
    if(tokenCourant == ID_TOKEN || tokenCourant == NUM_TOKEN){
        OP();
    }
}
void VAL(){
    testerTokenCourant(ID_TOKEN,tokenCourant);
    OPLOGIC();
    testerTokenCourant(ID_TOKEN,tokenCourant=lexicale());
}
void CON(){
    VAL(); //-
    OPERATION();
}
void CONDITION(){
    CON(); // no lexicale /-
    tokenCourant = lexicale();
    if(tokenCourant!=DPNT_TOKEN){
        CONDITION();
    }
}
void CND(){
    tokenCourant=lexicale();

    if(tokenCourant == ID_TOKEN || tokenCourant == NUM_TOKEN){
        CONDITION(); //-
    }else if(tokenCourant == TRUE_TOKEN || tokenCourant == FALSE_TOKEN){
        TF();
    }else{
        ERROR("Condition V2");
    }
}
void EXPIF(){
    testerTokenCourant(IF_TOKEN,tokenCourant);
    CND(); //-
    testerTokenCourant(DPNT_TOKEN,tokenCourant=lexicale());
    INSTS();
    EXPIF_P();
}
void INSTRUCTIONLIGNE(){ // first fonc no lexical
    if(tokenCourant == IF_TOKEN) EXPIF();
    else if(tokenCourant == ID_TOKEN || tokenCourant == FOR_TOKEN || tokenCourant == WHILE_TOKEN){ //condition
        if(tokenCourant == FOR_TOKEN || tokenCourant == WHILE_TOKEN) BOUCLE();
        else EXPRAFFECTATION();
        //EXPFONCTION();
    }
}
void INSTRUCTIONSLIST(){
    if(tokenCourant != ID_TOKEN && tokenCourant != IF_TOKEN && tokenCourant != FOR_TOKEN && tokenCourant != WHILE_TOKEN) tokenCourant = lexicale();
    INSTRUCTIONLIGNE();
    tokenCourant = lexicale(); // if *
    if(tokenCourant!=END_TOKEN){
        INSTRUCTIONSLIST();
    }
}
void INSTRUCTIONSLIST_MAIN(){
    if(tokenCourant != ID_TOKEN && tokenCourant != IF_TOKEN && tokenCourant != FOR_TOKEN && tokenCourant != WHILE_TOKEN) tokenCourant = lexicale();
    INSTRUCTIONLIGNE();
    tokenCourant = lexicale();
    if(tokenCourant!=PBF_TOKEN){
        INSTRUCTIONSLIST_MAIN();
    }
}
void MAIN(){
    testerTokenCourant(MAIN_TOKEN,tokenCourant);
    testerTokenCourant(PBO_TOKEN,tokenCourant=lexicale());
    if(tokenCourant==PBO_TOKEN){
        INSTRUCTIONSLIST_MAIN(); 
    }else if(tokenCourant==DPNT_TOKEN){
        INSTRUCTIONSLIST_MAIN(); //test
    }
    testerTokenCourant(PBF_TOKEN,tokenCourant);
}
void VARSNAME_P(){
    tokenCourant = lexicale();
    switch(tokenCourant){
        case VIR_TOKEN: VARSNAME(); break;
        case PNTVIR_TOKEN: testerTokenCourant(PNTVIR_TOKEN,tokenCourant); break; // for testing remove it after
        default: ERROR("Missing , or ;");
    }
}
void VARSNAME(){
    testerTokenCourant(ID_TOKEN,tokenCourant=lexicale());
    VARSNAME_P();
}
void TYPE(){
    int test=  testerRetourne(INT_TOKEN,tokenCourant) 
             ||testerRetourne(FLOAT_TOKEN,tokenCourant)
             ||testerRetourne(STRING_TOKEN,tokenCourant)
             ||testerRetourne(BOOL_TOKEN,tokenCourant);
    if(!test){
        ERROR("Type de variables");
    }
}
void VARSLIGNE(){
    TYPE();
    VARSNAME();
}
void VARLIST(){
    VARSLIGNE();
    tokenCourant = lexicale();
    if(tokenCourant!=PBF_TOKEN){
        VARLIST();
    }
}
void VARIABLES(){
    testerTokenCourant(VARIABLES_TOKEN,tokenCourant);
    testerTokenCourant(PBO_TOKEN,tokenCourant=lexicale());
    tokenCourant = lexicale();
    VARLIST();
    testerTokenCourant(PBF_TOKEN,tokenCourant); // lexical() deja fait dans la fonction VARLIST
}
void PROGRAM(){
    testerTokenCourant(PROGRAM_TOKEN,tokenCourant=lexicale());
    testerTokenCourant(ID_TOKEN,tokenCourant=lexicale());
    testerTokenCourant(PNTVIR_TOKEN,tokenCourant=lexicale());
    if((tokenCourant=lexicale()) == VARIABLES_TOKEN){
        VARIABLES();
        tokenCourant=lexicale();
    }
    MAIN();
}