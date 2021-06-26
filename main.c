#include <stdio.h>
#include <stdlib.h>
#include "pilePRIM.h"
#include "Fchaine.h"
char tmoscles[][17] = { "programme","var","integer","float","begin","end","if","then","else","while","do","while","read","readln","write","writeln","for" };
char mos[100000][200];
int compmos=0;
MATC tabA;
char tsymbole [][30]={"(",")",",",":=",";","==","<>","<=",">=","<",">","+","-","&&","||","*","/","%",":","{","}","++"};
int comment(char instr[]);
void suprime_espace(char T[]);
int moscle( char mot[] ) ;
int espace(char s[]);
int C_symb( char id[] );
int identificateur( char id[] );
int nombre( char id[] );
int oprmul( char id[] );
int opradd( char id[] );
int analyserInstruction(char instr[]);
int nbreLigne(char chaine[]);
void ajouter_espace(char T[],int pos);
void decal_symb(char T[]);
int analyserSource(char source[]);
void creat_t_A();
PILE empiler_p1(char source[],PILE p1);
int mosid( char mot[] );
int main()
{      creat_t_A();
       FILE *fp1;
       PILE p1;
       p1.top=-1;
      char ch[5000];
      int i=0;
    // ouvrir le fichier en lecture
    fp1 = fopen("D:\source.txt", "r");

    // Lire le contenu du fichier
    while((ch[i]= getc(fp1)) != EOF)
        {
        i++;}
        ch[i]='\0';
        fclose(fp1);
        decal_symb(ch);
        suprime_espace(ch);
        analyserSource(ch);
       p1= empiler_p1(ch,p1);
      // printf("\n %s \n",ch);
      // afficher(p1);

       if(analyse_syntaxique(p1)==-1)
         printf("\n Erreur dans le syntaxe");
       else printf ("\n Analyse sytaxique reussi");
    return 0;
}
//test d'un commentaire
int comment(char instr[]){
 if ( instr[0] == '*' && instr[strlen(instr)-1] == '*'  ) return 1;
 else return 0;
}
//Suppression des espaces multiples dans une instruction
void suprime_espace(char T[]){
        if( T[0] != '\0' ) {
  int j,i=0;
  while( (T[i] != ' ' || T[i+1] != ' ' ) && T[i] != '\0' ) i++;
  j=i;
  while( T[i] != '\0' ) {
   T[i] = T[i+1];
   i++;
  }
  suprime_espace(&T[j]);
 }
}
// Vérification d'un mot clé
int moscle( char mot[] ) {
 int i;
 for( i=0 ; i < 17 ; i++ ) if( strcmp(mot,tmoscles[i]) == 0 ) return 1;
 return 0;
}
// Vérification d'un symbole
int mossym( char mot[] ) {
 int i;
 for( i=0 ; i < 22 ; i++ ) if( strcmp(mot,tsymbole[i]) == 0 ) return 1;
 return 0;
}
//verification identificateur
int mosid( char mot[] ) {
 int i;
 for( i=0 ; i < compmos ; i++ )
 {
     if( strcmp(mot,mos[i]) == 0 ) return 1;

 }
 return 0;
}
// return 1 si la chaine s contien un espace , et 0 sinon
int espace(char s[]){
 int i=0;
 while( s[i] != '\0' ){
  if( s[i] == ' ') return 1;
  i++;
 }
 return 0;
}
//Contenir des symboles
int C_symb( char id[] ){
int i=0;
 while(((id[i]>='a' && id[i]<='z')|| (id[i]>='A' && id[i]<='Z')||( id[i] >='0' && id[i] <= '9' )) && id[i]!='\0')
        {
        i++;};
        if(i==strlen(id))
            return 0;
            else return 1;
 }
//Validité d'un identificateur
int identificateur( char id[] ){
 if(( id[0] < '0' || id[0] > '9' ) && moscle(id) == 0 && C_symb(id)==0) return 1;
 else return 0;
}
//Validité d'un nombre
int nombre( char id[] ){
int i=0;
 while(( id[i] >='0' && id[i] <= '9' ) && id[i]!='\0')
        {
        i++;};
        if(i==strlen(id))
            return 1;
            else return 0;
}
//Validité d'une operateur de multiplication
int oprmul( char id[] ){
 if(( strcmp(id,"*")==0||strcmp(id,"%")==0||strcmp(id,"/")==0 || strcmp(id,"&&")==0) && espace(id) == 0 ) return 1;
 else return 0;
}
//Validité d'une operateur d'addition
int opradd( char id[] ){
 if(( strcmp(id,"+")==0 || strcmp(id,"-")==0 || strcmp(id,"||")==0)  && espace(id) == 0 ) return 1;
 else return 0;}
 //validite des operateur relationnel
int oprel( char id[] ){
 if( strcmp(id,"==")==0 || strcmp(id,"<=")==0 || strcmp(id,">=")==0 ||strcmp(id,"<")==0||strcmp(id,">")==0 || strcmp(id,"<>")==0 ) return 1;
 else return 0;}

//Analyse d'une instruction
int analyserInstruction(char instr[]){
    int i=0;
 if ( comment(instr) == 1 ) return 1;
 else {
   while(i<strlen(instr) )
 {

  int k=0;
  char mot[20]="";
  while( instr[i] != ' ' && instr[i] != '\0' ){
   mot[k] = instr[i];
   i++;
   k++;

  }
  mot[k]='\0';
  if(( identificateur(mot)==0 && !mossym(mot) && !moscle(mot)&&!nombre(mot)&& strcmp(mot,"")!=0) )
     return 0;
  if(strcmp(mot,"")!=0&&!moscle(mot)&&!mossym(mot)&& identificateur(mot) )
     {strcpy(mos[compmos],mot);

      compmos++;
     }
     i++;
 }
 return 1;
 }
}
//  calcule le nombre des lignes dans une chaine
int nbreLigne(char chaine[]){
 int i=0,nbr=1;
 while( chaine[i] != '\0' ) {
  if ( chaine[i] == '\n' ) nbr++;
  i++;
 }
 return nbr;

}
//decaler espace
void ajouter_espace(char T[],int pos){
    char temp;
        if( T[0] != '\0' ) {
  int i=pos+1;

  while( T[i] != '\0' )
  {   temp=T[i];
      T[i]=T[pos];
      T[pos]=temp;
    i++;
  }
  T[i]=T[pos];
  T[pos]=' ';
  T[i+1]='\0';
 }


}
// decaler les symbole
void decal_symb(char T[])

{

    int i=0;
    char temp[3];
    while( T[i+1] != '\0' )
    {   temp[0]=T[i];
        temp[1]=T[i+1];
        temp[2]='\0';
        if(mossym(temp))
            {ajouter_espace(T,i);
             ajouter_espace(T,i+3);
             i+=3;
            }
         else
         {temp[1]='\0';
          if(mossym(temp))
             {ajouter_espace(T,i);
             ajouter_espace(T,i+2);
             i+=2;
            }

         }
     i++;
    }
}


//Creation table analyse
void creat_t_A()
{   int i, j;
    for (i = 0 ; i < 20 ; i++)
    for (j = 0 ; j < 35 ; j++)
    {
        strcpy(tabA.tab[i].tabc[j],"Erreur");
    }
   strcpy(tabA.tab[0].tabc[1],"programme");
   strcpy(tabA.tab[0].tabc[2],"id");
   strcpy(tabA.tab[0].tabc[3],";");
   strcpy(tabA.tab[0].tabc[4],"var");
   strcpy(tabA.tab[0].tabc[5],":");
   strcpy(tabA.tab[0].tabc[6],",");
   strcpy(tabA.tab[0].tabc[7],"integer");
   strcpy(tabA.tab[0].tabc[8],"char");
   strcpy(tabA.tab[0].tabc[9],"float");
   strcpy(tabA.tab[0].tabc[10],"begin");
   strcpy(tabA.tab[0].tabc[11],"end");
   strcpy(tabA.tab[0].tabc[12],"for");
   strcpy(tabA.tab[0].tabc[13],"if");
   strcpy(tabA.tab[0].tabc[14],"then");
   strcpy(tabA.tab[0].tabc[15],"while");
   strcpy(tabA.tab[0].tabc[16],"do");
   strcpy(tabA.tab[0].tabc[17],"(");
   strcpy(tabA.tab[0].tabc[18],")");
   strcpy(tabA.tab[0].tabc[19],"{");
   strcpy(tabA.tab[0].tabc[20],"read");
   strcpy(tabA.tab[0].tabc[21],"readln");
   strcpy(tabA.tab[0].tabc[22],"write");
   strcpy(tabA.tab[0].tabc[23],"writeln");
   strcpy(tabA.tab[0].tabc[24],"else");
   strcpy(tabA.tab[0].tabc[25],"while");
   strcpy(tabA.tab[0].tabc[26],"oprel");
   strcpy(tabA.tab[0].tabc[27],"opadd");
   strcpy(tabA.tab[0].tabc[28],"opmul");
   strcpy(tabA.tab[0].tabc[29],"nb");
   strcpy(tabA.tab[0].tabc[30],"}");
   //////////
   strcpy(tabA.tab[1].tabc[0],"P");
   strcpy(tabA.tab[1].tabc[1],"programme id ; Dcl Ins_composee");

   strcpy(tabA.tab[2].tabc[0],"Dcl");
   strcpy(tabA.tab[2].tabc[4],"Dcl2");
   strcpy(tabA.tab[2].tabc[10],"");

   strcpy(tabA.tab[3].tabc[0],"Dcl2");
   strcpy(tabA.tab[3].tabc[4],"var Liste_id : Type ; Dcl2");
   strcpy(tabA.tab[3].tabc[10],"");

   strcpy(tabA.tab[4].tabc[0],"Type");
   strcpy(tabA.tab[4].tabc[7],"integer");
   strcpy(tabA.tab[4].tabc[8],"char");
   strcpy(tabA.tab[4].tabc[9],"float");

   strcpy(tabA.tab[5].tabc[0],"Liste_id");
   strcpy(tabA.tab[5].tabc[2],"id Liste_id2");

   strcpy(tabA.tab[6].tabc[0],"Liste_id2");
   strcpy(tabA.tab[6].tabc[6],", id Liste_id2");
   strcpy(tabA.tab[6].tabc[5],"");

   strcpy(tabA.tab[7].tabc[0],"Ins_composee");
   strcpy(tabA.tab[7].tabc[10],"begin Ins end");

   strcpy(tabA.tab[8].tabc[0],"Ins");
   strcpy(tabA.tab[8].tabc[2],"Liste_ins");
   strcpy(tabA.tab[8].tabc[11],"");
   strcpy(tabA.tab[8].tabc[12],"Liste_ins");
   strcpy(tabA.tab[8].tabc[13],"Liste_ins");
   strcpy(tabA.tab[8].tabc[20],"Liste_ins");
   strcpy(tabA.tab[8].tabc[21],"Liste_ins");
   strcpy(tabA.tab[8].tabc[22],"Liste_ins");
   strcpy(tabA.tab[8].tabc[23],"Liste_ins");
   strcpy(tabA.tab[8].tabc[25],"Liste_ins");

   strcpy(tabA.tab[9].tabc[0],"Liste_ins");
   strcpy(tabA.tab[9].tabc[2],"I Liste_ins2");
   strcpy(tabA.tab[9].tabc[12],"I Liste_ins2");
   strcpy(tabA.tab[9].tabc[13],"I Liste_ins2");
   strcpy(tabA.tab[9].tabc[20],"I Liste_ins2");
   strcpy(tabA.tab[9].tabc[21],"I Liste_ins2");
   strcpy(tabA.tab[9].tabc[22],"I Liste_ins2");
   strcpy(tabA.tab[9].tabc[23],"I Liste_ins2");
   strcpy(tabA.tab[9].tabc[25],"I Liste_ins2");

   strcpy(tabA.tab[10].tabc[0],"Liste_ins2");
   strcpy(tabA.tab[10].tabc[3],"; I Liste_ins2");
   strcpy(tabA.tab[10].tabc[11],"");

   strcpy(tabA.tab[11].tabc[0],"I");
   strcpy(tabA.tab[11].tabc[2],"id := Exp_simple");
   strcpy(tabA.tab[11].tabc[12],"for ( id := nb ; id oprel id ; id ++ ) { I }");
   strcpy(tabA.tab[11].tabc[13],"if Exp then I2");
   strcpy(tabA.tab[11].tabc[20],"read ( id )");
   strcpy(tabA.tab[11].tabc[21],"readln ( id )");
   strcpy(tabA.tab[11].tabc[22],"write ( id )");
   strcpy(tabA.tab[11].tabc[23],"writeln ( id )");
   strcpy(tabA.tab[11].tabc[25],"while Exp do I");

   strcpy(tabA.tab[12].tabc[0],"I2");
   strcpy(tabA.tab[12].tabc[3],"");
   strcpy(tabA.tab[12].tabc[11],"");
   strcpy(tabA.tab[12].tabc[19],"");
   strcpy(tabA.tab[12].tabc[24],"else I");

   strcpy(tabA.tab[13].tabc[0],"Exp");
   strcpy(tabA.tab[13].tabc[2],"Exp_simple Exp2");
   strcpy(tabA.tab[13].tabc[29],"Exp_simple Exp2");
   strcpy(tabA.tab[13].tabc[17],"Exp_simple Exp2");

   strcpy(tabA.tab[14].tabc[0],"Exp2");
   strcpy(tabA.tab[14].tabc[14],"");
   strcpy(tabA.tab[14].tabc[26],"oprel Exp_simple");
   strcpy(tabA.tab[14].tabc[16],"");

   strcpy(tabA.tab[15].tabc[0],"Exp_simple");
   strcpy(tabA.tab[15].tabc[2],"Terme Exp_simple2");
   strcpy(tabA.tab[15].tabc[17],"Terme Exp_simple2");
   strcpy(tabA.tab[15].tabc[29],"Terme Exp_simple2");

   strcpy(tabA.tab[16].tabc[0],"Exp_simple2");
   strcpy(tabA.tab[16].tabc[3],"");
   strcpy(tabA.tab[16].tabc[11],"");
   strcpy(tabA.tab[16].tabc[14],"");
   strcpy(tabA.tab[16].tabc[16],"");
   strcpy(tabA.tab[16].tabc[18],"");
   strcpy(tabA.tab[16].tabc[30],"");
   strcpy(tabA.tab[16].tabc[26],"");
   strcpy(tabA.tab[16].tabc[27],"opadd Terme Exp_simple2");

   strcpy(tabA.tab[17].tabc[0],"Terme");
   strcpy(tabA.tab[17].tabc[2],"Facteur Terme2");
   strcpy(tabA.tab[17].tabc[17],"Facteur Terme2");
   strcpy(tabA.tab[17].tabc[29],"Facteur Terme2");

   strcpy(tabA.tab[18].tabc[0],"Terme2");
   strcpy(tabA.tab[18].tabc[3],"");
   strcpy(tabA.tab[18].tabc[11],"");
   strcpy(tabA.tab[18].tabc[14],"");
   strcpy(tabA.tab[16].tabc[16],"");
   strcpy(tabA.tab[18].tabc[18],"");
   strcpy(tabA.tab[18].tabc[30],"");
   strcpy(tabA.tab[18].tabc[26],"");
   strcpy(tabA.tab[18].tabc[27],"");
   strcpy(tabA.tab[18].tabc[28],"opmul Facteur Terme2");


   strcpy(tabA.tab[19].tabc[0],"Facteur");
   strcpy(tabA.tab[19].tabc[2],"id");
   strcpy(tabA.tab[19].tabc[17],"(Exp_simple");
   strcpy(tabA.tab[19].tabc[29],"nb");




}
//empiler une chaine dans le pile
PILE empiler_p1(char source[],PILE p1)
{

 int i=strlen(source)-1;
 int j=0;
 char temp[100];
 while(i>=0)
 {
     if(source[i]!=' '&& source[i]!='\n')
     {
         temp[j]=source[i];
     j++;}
     else

     {                  temp[j]='\0';
         if(i!=strlen(source)-1&&strcmp(temp,"" )!=0)
          {
              strrev(temp);
           if(mosid(temp))
              strcpy(temp,"id");
           else if (oprel(temp))
              strcpy(temp,"oprel");
           else if (nombre(temp))
              strcpy(temp,"nb");
           else if (oprmul(temp))
              strcpy(temp,"opmul");
           else if (opradd(temp))
              strcpy(temp,"opadd");

           p1=Empiler(temp,p1);
          }
        strcpy(temp,"");

        j=0;

     }
i--;
 }    temp[j]='\0';
      strrev(temp);
      p1=Empiler(temp,p1);

;
return p1;
}
//analyse syntaxique
int analyse_syntaxique(PILE p1)
{PILE p2;
int pos1,pos2;
char temp[200];
  p2.top=-1;
  p2=Empiler("P",p2);
  while(p2.top!=-1)
  {if(strcmp(p1.tab[p1.top],p2.tab[p2.top])!=0)
  {
  pos1=cherche_motp1(p1.tab[p1.top]);
  pos2=cherche_motp2(p2.tab[p2.top]);
  //printf(" \n %d  %d \n",pos1,pos2);
  if(pos1>0&&pos2>0)
    {p2=Depiler(p2,temp);
     if(strcasecmp(tabA.tab[pos2].tabc[pos1],"")!=0)
     p2=empiler_p1(tabA.tab[pos2].tabc[pos1],p2);
    }
   else return -1;}
   else
   {p1=Depiler(p1,temp);
    p2=Depiler(p2,temp);
   }
   printf("\n P1=");
   afficher(p1);
   printf("\n P2=");
   afficher(p2);
  }
return 1;
}
//chercher le mot au sommet de p1
int cherche_motp1(char mot [])
{
 int i;
 for( i=1 ; i < 31 ; i++ ) if( strcmp(mot,tabA.tab[0].tabc[i]) == 0 ) return i;
 return -1;
}
//cher le mot au sommet de p2
int cherche_motp2(char mot [])
{
 int i;
 for( i=1 ; i < 20 ; i++ ) if( strcmp(mot,tabA.tab[i].tabc[0]) == 0 ) return i;
 return -1;
}
// Analyse d'un fichier source
int analyserSource(char source[]){

 int k;

 // declaration de la chaine copiée de source
 char* sourceCopy = NULL;
 sourceCopy = ( char * ) malloc( sizeof(char) * strlen(source) );

 // des parametres qu'on va les utilisés
 int nbrL = nbreLigne(source),i=0,j=1;
 // declaration et initialisation du tableau ou on va noté les lignes d'erreurs
 int* erreurs = NULL;
 erreurs = ( int* ) malloc( sizeof(int) * nbrL );
 for(k=0; k < nbrL ; k++ ) erreurs[k] = 1;

 // declaration du tableau de pointeurs sur les ligne;
 char** ligne = NULL;
 ligne = ( char ** )malloc( sizeof(char*) * nbrL );

 // le copiage et le chainage
 ligne[0] = sourceCopy;
 while( source[i] != '\0' ){
  sourceCopy[i] = source[i];
  if( sourceCopy[i] == '\n' ) { sourceCopy[i] = '\0'; ligne[j] = sourceCopy + i + 1; j++; }
  i++;
 }
 sourceCopy[i] = '\0';

 // analyse ligne par ligne
 for(k=0; k < nbrL ; k++ ) if( analyserInstruction(ligne[k]) == 0 ) erreurs[k] = 0;

 // ecriture des lignes d'erreur
 i=0;
 for(k=0; k < nbrL ; k++ ) if ( erreurs[k] == 0 ) { printf(" Erreur ligne %d",k+1); i++; }

 // succée
 if ( i == 0 ) { printf("Analyse lexical reussie \n"); return 1; }
 else return 0;

}
