/* --- The following code comes from C:\lcc\lib\wizard\textmode.tpl. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//static char ligne[200];

typedef struct {
	char numecr[5];
	char numpil[5];
	char nompil[80];
	char date [15];
	char typeoper[80];
	char credit[10];
	char debit[10];
}PILRECORD;

typedef struct {
	char typeoper[80];
	char comptadebit[15];
	char comptacredit[15];
}DICTIONNAIRE;

static DICTIONNAIRE dico[]={
"Licence federale et assurance", "728100", "728100",
"Licence courte duree 12 jours", "728101", "728101",
"Licence courte duree 3 jours", "728101", "728101",
"Licence courte duree 6 jours", "728101", "728101",
"Cotisation annuelle", "701100", "701100",
"Report annee anterieure", "0", "0", /* ne pas traiter */
"Participation aux frais de fonctionnement du club", "701104", "701104",
"Participation aux travaux d'hivers 6 jours de travail", "701105", "701105",
"Formule court sejour cotis + 2 euros jours + assurance annuelle", "706313", "706313",
"Formule 2 semaines  14 Vols ou 14 Heures + Licence FFVV", "706310", "706310",
"Stage 2 semaines-14 vols y compris licence annuelle \"\"Perfectionnement\"\"\"", "706310", "706310",
"Stage 2 semaines-21 vols y compris licence annuelle \"\"Perfectionnement\"\"\"", "706311", "706311",
"Formule 3 semaines 30 Vols + Licence", "706311", "706311",
"Formule Week-end","706313", "706313",
"Stage journee supplementaire", "706313", "706313",
"Formule Velivole 40 heures (K21 Ls4 Pegase et janus)", "706303", "706303",
"Formule Velivole 80 heures (K21 Ls4 Pegase et janus)", "706307", "706307",
"Formule decouverte BIA 5 jours","706309", "706309",
"Formule decouverte 5h + assurance journee (fractionnable)","706304","706304",
"Formule Velivole 150 heures (K21 Ls4 Pegase et janus)", "706306", "706306",
"Formule Velivole 200 heures (K21 Ls4 Pegase et janus)", "706302", "706302",
"Avance sur vol", "0", "0", /* ne pas traiter */
"Remboursement travaux d'hivers 6 jours de travail", "604101", "604101",
"Report annee anterieure (tx hiver)", "604102",  "604102",
"Manuel eleve pilote", "704403", "704403",
"Proprietaire de planeur hors hangar y compris 1/2 taxe faineant", "701103", "701103",
"Proprietaire de planeur de passage / jour", "701103","701103",
"Camping caravane /mois", "708400", "708400",
"Camping  tente", "708400", "708400",
"remb 1/2 acvl", "604104","604104",
"remb 1/2  acvl", "604104","604104",
"remb 1/2 famille", "604105","604105",
"Operation diverses", "410XXX", "410XXX",
"operation diverse", "410XXX", "410XXX",
"Operation diverse", "410XXX", "410XXX",
"Cotisation journaliere", "701102","701102",
"Camping","708400","708400",
"Carnet de vol","704405","704405",
"Formule decouverte  5h + assurance journee (fractionnable)", "706304","706304",
"Formule decouverte bIA 5 jours", "706309","706309",
"Carnet de vol", "704405","704405",
"Annulation frais club", "604102", "604102",
"Bourse au BPP FFVV","740103","740103",
"Bourse au lacher FFVV","740104","740104",
"Bourse aux 1000 km FFVV","740105","740105",
"Bourse au merite FFVV","740106","740106",
"Bourse CDVP","740102","740102",
"Bourse CFVP","740100","740100",
"Vol formation pilote remorqueur KL","706204","706204",
"Vol formation pilote remorqueur UP","706204","706204",
"Remb. partiel ou total licence","728100","728100",
"Remb. partiel ou total cotisation","701100","701100",
"Remb. Partiel ou total forfait 40H","706303","706303",
"Remb. Partiel ou total forfait 80H","706307","706307",
"Remb. Partiel ou total forfait 150H","706306","706306",
"Remb. Partiel ou total forfait 200H","706302","706302",
"Remb. partiel ou total stage BIA","706309","706309",
"Remb. partiel ou total SIPP","706304","706304",
"Remb. partiel ou total camping","708400","708400",
"Remb. vol impute par erreur","706104","706104",
"Upgrade 40H a 80H","706303","706303",
"Upgrade 80H a 150H","706307","706307",
"Upgrade 150H a 200H","706306","706306",
"Gratification exceptionnelle 8JF","628104","628104",
"Contribution exceptionnelle du club","670000","670000",
"Achat d'un badge","628102","628102",
"Stage decouverte 6 jours assur compris 6 vols 4h a 5h","706309","706309",
"Stage SIPP 6 vols 4h a 5h avec Licence assurance et remorques","706304","706304",
"Stage SIPP 6 vols 4h a 5h avec LA et remorques","706304","706304",
};

/* obtention code du plan comptable */
int getcode(char *typeoper, char *comptadebit, char *comptacredit)
{

	static int n= sizeof(dico)/sizeof(DICTIONNAIRE);
	int i;

//	printf("Taille du dictionnaire = %ld\n", n);
	for(i=0; i<n; i++){
		if(!strcmp(typeoper, dico[i].typeoper)){
			strcpy(comptacredit, dico[i].comptacredit);
			strcpy(comptadebit, dico[i].comptadebit);
			return 0;
		}
	}
	return -1;
}

/* separation des champs */
void explode(char *buffer, char *numecr, char *numpil, char *nompil, char *date, char *typeoper, char *credit, char *debit)
{
	char *p=buffer;
	char *s;

	s= numecr;
	while (*p != ';') *s++ = *p++;
	*s=0;
	p++;

	s= numpil;
	while (*p != ';') *s++ = *p++;
	*s=0;
	p++;

	s=nompil;
	while (*p != ';') *s++ = *p++;
	*s=0;
	p++;

	s = date;
	while (*p != ';') *s++ = *p++;
	*s=0;
	p++;

	s=typeoper;
	while (*p != ';') *s++ = *p++;
	*s=0;
	p++;

	s=credit;
	while (*p != ';') *s++ = *p++;
	*s=0;
 	p++;

 	s=debit;
	while (*p != ';') *s++ = *p++;
	*s=0;
}

int main(int argc, char *argv[])
{
	char comptadebit[10], comptacredit[10], buffer[500], *p, logname[80];
	FILE *fexport, *fimport, *flog;
	PILRECORD r;
	int report=0, hiver=0, autres=0, linenumber=0, lineignore=0, linewarning=0, mois, m;
	double credit, debit;
	time_t currenttime;

	/* test nombre argument */
	if (argc != 3){
		printf("Mauvais appel de la commande !!!\n");
		printf("Syntaxe : %s <fichier export (source)> <fichier import (destination)>\n", argv[0]);
		return -1;
	}


	/* ouverture fichier export en lecture */
	if((fexport = fopen(argv[1], "r")) == NULL){
		printf("Impossible ouvrir fichier pilotes\n");
		return -1;
	}
	/* ouverture fichier import ecriture */
	if((fimport = fopen(argv[2], "w")) == NULL){
		printf("Impossible creer fichier Ciel\n");
		return -1;
	}

	/* ouvertur fichier log en écriture */
	strcpy(logname, argv[2]);
	strcpy(&logname[strlen(logname)-4], ".txt");
	if((flog = fopen(logname, "w")) == NULL){
		printf("Impossible creer fichier log %s\n", logname);
		return -1;
	}
	fprintf(flog,"Fichier d'entrée:%s Fichier de sortie:%s\r\n", argv[1], argv[2]);
	time(&currenttime);
	fprintf(flog, "Date et heure:%s\r\n",  ctime(&currenttime));
/*----------------------------------------------------------------*/
	/* saut ligne d'entête */
	if(!feof(fexport)){
		 fgets(buffer, 400, fexport);
		 linenumber=1;
	 }
	/* analyse */
	while (!feof(fexport)){
		if(fgets(buffer, 400, fexport)==NULL)
			break;
		linenumber++;
		/* Separation des champs */
		explode(buffer, (r.numecr), (r.numpil), (r.nompil), (r.date), (r.typeoper), (r.credit), (r.debit));
		/* Remplacer les tirets par des underscore dans la chaîne nompil et les munuscules par des majuscules*/
		p = r.nompil;
		while(*p){
			if(*p=='-')
				*p='_';
			*p = toupper(*p);
			p++;
		}
		/* Remplacer les virgules par des points décimaux dans les chaines credit et debit */
		p = r.credit;
		while(*p){
			if(*p==',')
				*p='.';
			p++;
		}
		p = r.debit;
		while(*p){
			if(*p==',')
				*p='.';
			p++;
		}

#if 1
		/* Remplacer les caracteres accentués par l'équivalent normal dans la chaîne nompil */
		/* non ca ne va pas : a retravailler */
		p = r.nompil;
		while(*p){
			if(*p =='©')
				*p= 'É';
			if(*p =='é')
				*p= 'É';
			else if (*p =='è')
				*p = 'È';
			else if (*p=='ë')
				*p = 'Ë';
			else if (*p =='ù')
				*p= 'Ù';
			else if (*p =='à')
				*p='À';
			else if (*p =='§')
				*p= 'Ç';
			else if (*p =='ç')
				*p= 'Ç';
			else if (*p == 'ï')
				*p= 'Ï';
			p++;
		}
#endif

#if 0
		/* faut-il traiter ? */
		m = ((r.date[3] - '0') * 10) + (r.date[4] - '0');
		if (mois != m)
			continue;
#endif

		/* Obtention du nom uniquement */
//		getname(r.nompil, nom);
//		changecase(nom, lownom);
		/* Obtention code plan comptable */
		if(getcode(r.typeoper, comptadebit, comptacredit) == -1){
			/*printf("Ligne %5d:operation inconnue:%s. Code 410XXX par defaut\n", linenumber, r.typeoper);*/
			fprintf(flog, "Attention: Ligne %5d:Operation inconnue: %s. Code 410XXX par defaut (%s)\r\n", linenumber, r.typeoper, r.nompil);
			linewarning++;
			strcpy(comptadebit, "410XXX");
			strcpy(comptacredit, "410XXX");
			/*continue;*/
		}
		/* suppression des lignes avec credit et  débit nul */
		debit=atof(r.debit);
		credit=atof(r.credit);
		if(debit == credit){
				/*printf("Ligne %5d ignoree : credit identique a debit  = %8.2f\n", linenumber, debit);*/
				fprintf(flog,"Erreur: Ligne %5d ignoree: credit identique a debit  = %8.2f (%s)\r\n", linenumber, debit, r.nompil);
				lineignore++;
				continue;
		}
		/* suppression des lignes de report année antérieure et avance sur vol */
		/* Obtention code plan comptable */
		if(!strcmp(comptadebit,"0")) {
			/*fprintf(flog,"Attention: Ligne %5d ignoree: %s  = %8.2f (%s)\r\n", linenumber, r.typeoper, credit ? credit : -debit, r.nompil);*/
			lineignore++;
			continue;
		}

/*-----------------------------------------------------------------*/
/* <code journal>;<N°compte>;<date>;<libellé compte>;<libellé>;<crédit> |;<débit> */
/* test si c'est une opération débitrice ou creditrice du compte pilote */
		if(debit == 0 && credit !=0){
			/* operation creditrice */
			fprintf(fimport,"PI;%s;%s;%s;%s %s;%8.2f;;ANALYTIQUE\r\n",
					comptacredit, r.date,r.typeoper, r.nompil, r.typeoper, credit);
			fprintf(fimport, "PI;419%03d;%s;%s;%s;;%8.2f;ANALYTIQUE\r\n",
					atoi(r.numpil), r.date, r.nompil, r.typeoper, credit);
		}
		else if (credit ==0 && debit !=0){
			/* operation débitrice */
			fprintf(fimport, "PI;419%03d;%s;%s;%s;%8.2f;;ANALYTIQUE\r\n",
					atoi(r.numpil), r.date, r.nompil, r.typeoper, debit);
			fprintf(fimport,"PI;%s;%s;%s;%s %s;;%8.2f;ANALYTIQUE\r\n",
					comptadebit, r.date, r.typeoper, r.nompil, r.typeoper, debit);
		}
		else{
			if (credit == debit){
				printf("Ligne %5d ignoree : debit = credit= %8.2f\n", linenumber, debit);
				fprintf(flog, "Erreur: Ligne %5d ignoree: debit = credit= %8.2f (%s)\r\n", linenumber, debit, r.nompil);
				continue;
			}
			else if (credit - debit >0){
				/* operation creditrice */
				fprintf(fimport, "PI;419%03d;%s;%s;%s;%8.2f;;ANALYTIQUE\r\n",
					atoi(r.numpil), r.date, r.nompil, r.typeoper, credit-debit);
				fprintf(fimport,"PI;%s;%s;%s;%s %s;;%8.2f;ANALYTIQUE\r\n",
					comptadebit, r.date, r.typeoper, r.nompil, r.typeoper, credit-debit);
				fprintf(flog,"Attention: Ligne %5d: credit=%8.2f debit=%8.2f. La somme %8.2f a été inscrite au credit du compte %s\r\n",
					linenumber, credit, debit, credit-debit, r.nompil);
			}
			else {
				/* operation debitrice */
			fprintf(fimport,"PI;%s;%s;%s;%s %s;%8.2f;;ANALYTIQUE\r\n",
					comptacredit, r.date, r.typeoper, r.nompil, r.typeoper, debit-credit);
			fprintf(fimport, "PI;419%03d;%s;%s;%s;;%8.2f;ANALYTIQUE\r\n",
					atoi(r.numpil), r.date, r.nompil, r.typeoper, debit-credit);
			fprintf(flog,"Attention: Ligne %5d: credit=%8.2f debit=%8.2f. La somme %8.2f a été inscrite au debit du compte %s\r\n",
					linenumber, credit, debit, debit-credit, r.nompil);
			}
			linewarning++;
		}

	}
	fprintf(flog, "\r\nFin: %5d lignes ont été traitées\r\n", linenumber);
	fprintf(flog, "Nombre de lignes ignorées : %5d\r\n", lineignore);
	fprintf(flog, "Nombre de lignes prises en compte mais à revoir : %5d\r\n", linewarning);
	fclose(flog);
	fclose (fimport);
	fclose(fexport);
	return 0;
}

