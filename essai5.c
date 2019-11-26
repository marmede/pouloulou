#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct{
    int secondes;
    int minutes;
    int heures;
    int jour;
    int mois;
    int annee;
    int jour_test;
}Date;

typedef struct Poste Poste;
struct Poste{
	char *poste;
	int num;
	int like;
	int public;
	Date* date;
	Poste* suivant;
};

typedef struct ListePostes ListePostes;
struct ListePostes{
	Poste* tete;
	int taille;	
};

typedef struct Utilisateur Utilisateur;
struct Utilisateur{
	char* nom;
	char* prenom;
	char* login;
	char* password;
	int etat;//Booléen qui dit si l'utilateur est bloqué
	char* questions[2];
	int numquestion1;
	int numquestion2;
	char reponse1[50];
	char reponse2[50];
	ListePostes* lp;
	Utilisateur** la;
	int nb_amis;

	Utilisateur* suivant;
};

typedef struct ListeUser ListeUser;
struct ListeUser{
	Utilisateur* tete;
	int taille;
};

char *Listequestions[] = {"Quel est votre premier numero de telephone ?",
						"Quel est le nom de votre premier animal de compagnie ?",
						"Quel est votre couleur preferee ?",
						"Quel est votre lieu de naissance ?",
						"Quel est la marque de votre premiere voiture ?",
						"Quel est votre sport prefere ?"
						};

void* malloc_p(unsigned int s){
	void * p;
  	if(p=malloc(s)) return p;
  	else {perror("Erreur allocation\n");exit(EXIT_FAILURE);}
}

void* realloc_p(void* p, unsigned int s){
    if(p=realloc(p,s)) return p;
    else{perror("Erreur allocation"); exit(0);}
}

Date* Ajout_Date(Date* d){
    d = (Date*)malloc_p(sizeof(Date));
    time_t t = time(&t);
    struct tm* info;
    info = localtime(&t);

    d->annee = info->tm_year + 1900;
    d->mois = info->tm_mon + 1;
    d->jour = info->tm_mday;
    d->heures = info->tm_hour;
    d->minutes = info->tm_min;
    d->secondes = info->tm_sec;
    d->jour_test = info->tm_yday;

    return d;
}

void Afficher_Date(Date* d){
    printf("Date : %d/%d/%d  Heure : %d Heures %d Minutes %d Secondes\n",d->jour,d->mois,d->annee,d->heures,d->minutes,d->secondes);
}

ListeUser** init_Liste(){
	ListeUser** l = (ListeUser**)malloc_p(sizeof(ListeUser));
	*l = (ListeUser*)malloc_p(sizeof(ListeUser));
	(*l)->taille = 0;
	(*l)->tete = NULL;
	return l;
}

ListePostes* init_ListePoste(){
	ListePostes* lp = (ListePostes*)malloc_p(sizeof(ListePostes));
	lp->tete = NULL;
	lp->taille = 0;
	return lp;
}

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {c = getchar();}
}

int chaine_isdigit(char* chaine){
	for (int i = 0; i < strlen(chaine); ++i)
	{
		if(!isdigit(chaine[i])){
			return 0;
		}
	}
	return 1;
}

int ListePoste_estVide(ListePostes* lp){
	if(!lp){return 1;}
	else{return 0;}
}

Poste* init_Poste(Poste* p){
	p = (Poste*)malloc_p(sizeof(Poste));
	p->poste = NULL;
	p->num = 0;
	p->like = 0;
	p->public = 0;
	p->suivant = NULL;
	p->date = Ajout_Date(p->date);

	return p;
}

void fgets_m(char **pchaine,int n){
	*pchaine = (char*)malloc_p(sizeof(char)*n);
	fgets(*pchaine,n,stdin);
	*pchaine = realloc_p(*pchaine,strlen(*pchaine)+1);
	(*pchaine)[strlen(*pchaine)-1] = '\0';
}

void Private_Public(Poste* p){
	char choix[10]="0"; 
	while(atoi(choix) != 1 && atoi(choix)!= 2){
		printf("1 - Post Public\n2 - Post Privee\n");
		printf("Votre choix : \n");
		scanf("%s",choix);
		int n = atoi(choix);
		switch(atoi(choix)){
			case 1:
				p->public = 0;
				break;

			case 2:
				p->public = 1;
				break;

			default:
				n = 0;
				break;
		}
	system("clear");
	}
}

void Post_dans_vide(ListePostes* lp){
	viderBuffer();
	printf("Entrez votre poste : \n");
	lp->tete = init_Poste(lp->tete);
	fgets_m(&lp->tete->poste,151);
	Private_Public(lp->tete);
	lp->taille++;
	lp->tete->num = lp->taille;
	lp->tete->suivant = NULL;
}

void Post_en_fin(ListePostes* lp){
	viderBuffer();
	printf("Entrez votre poste : \n");
	Poste* p = lp->tete;
	Poste* a = init_Poste(a);
	fgets_m(&a->poste,151);
	Private_Public(a);
	lp->taille++;
	a->num = lp->taille;
	while(p->suivant){
		p = p->suivant;
	}
	p->suivant = a;
	a->suivant = NULL;
}

void Afficher_User_Light(Utilisateur *u){
	printf("Nom : %s\n",u->nom);
	printf("Prenom : %s\n", u->prenom);
	printf("Login : %s\n\n", u->login);
}

Utilisateur** Ajout_Amis(Utilisateur** la,Utilisateur* a , int* nb_amis){
	if((*nb_amis) == 0){
		la = (Utilisateur**)malloc_p(sizeof(Utilisateur*));
		*la = a;
		(*nb_amis)++;
		return la;
	}

	else{
		(*nb_amis)++;
		la = (Utilisateur**)realloc_p(la,(*nb_amis) * sizeof(Utilisateur*));
		*(la + ((*nb_amis) - 1)) = a;
		return la;
	}
}

void Supp_amis(Utilisateur** la,Utilisateur* a, int* nb_amis){
	if (*nb_amis){
		int flag = 0,b = 0;
		Utilisateur* u;
		while(!flag && b < (*nb_amis)){
			u = *(la+b);
			if(strcmp(u->login,a->login) == 0){
				printf("A supprimer\n");
				// for(int i = a; i < (*nb_amis);i++){

				// }
			}
			b++;
		}

	}
	else{printf("Il faut avoir des amis pour les quitter.... #Triste\n");}
}

void Ajout_post(ListePostes* lp){
	if(lp->taille == 0){Post_dans_vide(lp);}
	else{Post_en_fin(lp);}
}

void Afficher_ListePoste(ListePostes* lp){
	if(lp->taille != 0){
	Poste* p = lp->tete;
	for(int i = 0;i < lp->taille;i++){
		printf("Poste %d : %s\n\t",p->num,p->poste );
		Afficher_Date(p->date);
		printf("\n");
		p = p->suivant;
	}}
	else{printf("Vous n'avez encore aucun post n'attendez plus ¯\\_(^^)_/¯\n");}
}

void suppPoste_debut(ListePostes* lp){
	Poste* p = lp->tete->suivant;
	free(lp->tete->poste);
	free(lp->tete->date);
	free(lp->tete);
	lp->tete = p;
	lp->taille--;
	for (int i = 0; i < lp->taille; i++)
	{
		p->num--;
		p = p->suivant;
	}
}

void suppPoste_fin(ListePostes *lp){
    Poste* p = lp->tete;
    while(p->suivant->suivant != NULL)
    {
        p = p->suivant;
    }
    free(p->suivant->poste);
	free(p->date);
    free(p->suivant);
    p->suivant = NULL;
    lp->taille--;
}

void suppPoste_milieu(ListePostes* lp, int n){
    Poste* p = lp->tete;
    Poste* q = lp->tete;
    while(p->suivant->num != n)
    {
        p = p->suivant;
        q = q->suivant;
    }
    q = q->suivant;
    p->suivant = q->suivant;
    free(q->poste);
    free(q->date);
    free(q);
    lp->taille--;
    for (int i = p->num; i < lp->taille; i++)
	{
	    p = p->suivant;
		p->num--;
	}
}

void suppPost(ListePostes* lp, int n){
	if(n > 0 && n <= lp->taille){
		if(n == lp->taille && n > 1){
			suppPoste_fin(lp);
		}
		else if(n == 1){
			suppPoste_debut(lp);
		}
		else{
			suppPoste_milieu(lp,n);
		}
	}
	else{
		printf("Ce poste n'existe pas (O_O)\n");
	}
}

Poste* Select_poste(ListePostes* lp){
	char choix [10]="0";
	int n = atoi(choix);
	Afficher_ListePoste(lp);
	while(n <1 && n > lp->taille){
		printf("Entrez le numero du post\n");
		scanf("%s",choix);
	}
	Poste* p = lp->tete;
	while(p->num != n){
		p = p->suivant;
	}
	return p;
}

void Vider_ListePoste(ListePostes* lp){
	while(lp->taille){
		suppPoste_debut(lp);
	}
	free(lp);
}

int Liste_user_estVide(ListeUser** l){
	if((*l)->tete){return 1;}
	else{return 0;}
}

Utilisateur* find_user(ListeUser **l,char* login,char* password){
	if(Liste_user_estVide(l)){
		Utilisateur* u = (*l)->tete;
		while(u){
			if((strcmp(u->login,login) == 0) && password && (strcmp(u->password,password) == 0)){
				return u;
			}
			if((strcmp(u->nom,login) == 0) && password &&(strcmp(u->prenom,password) == 0)){
				return u;
			}
			else if(strcmp(u->login,login) == 0){
				return u;
			}
			u = u->suivant;
		}
		return NULL;
	}
	else{
		return NULL;
	}
}

void Set_Nom(Utilisateur* u){
	printf("Entrez votre nom : ");
	fgets_m(&u->nom,50);
	printf("\n");
}

void Set_Prenom(Utilisateur* u){
	printf("Entrez votre prenom : ");
	fgets_m(&u->prenom,50);
	printf("\n");
}

void Set_Login(ListeUser** l,Utilisateur* u){
	u->login = (char*)malloc_p(sizeof(char));
	do{
		u->login = realloc_p(u->login,sizeof(char)*50);
		printf("Entrez votre pseudo : ");
		fgets(u->login,50,stdin);
		u->login = realloc_p(u->login,strlen(u->login)+1);
		u->login[strlen(u->login)-1] = '\0';
		printf("\n");
		if(find_user(l,u->login,NULL)){printf("Ce pseudo est deja utilise\n");}
	}while(find_user(l,u->login,NULL));
}

void Set_Password(Utilisateur* u){
	u->password = (char*)malloc_p(sizeof(char));
	char password[30];
	do{
		u->password = realloc_p(u->password,sizeof(char)*50);
		printf("Entrez votre mot de passe : ");
		fgets(u->password,30,stdin);
		u->password = realloc_p(u->password,strlen(u->password)+1);
		u->password[strlen(u->password)-1] = '\0';
		printf("Confirmer votre mot de passe : ");
		scanf("%s",password);
		printf("\n");
		if(strcmp(u->password,password) != 0){printf("Erreur de confirmation veuillez recommencer\n");viderBuffer();}
	}while(strcmp(u->password,password) != 0);
}

void Set_Questions(Utilisateur* u){
	int confirmation[2]={0};
	char choix1[10],choix2[10],confirmation1[10],confirmation2[10];
	// char *Listequestions[] = {"Quel est votre premier numero de telephone ?",
	// 					"Quel est le nom de votre premier animal de compagnie ?",
	// 					"Quel est votre couleur preferee ?",
	// 					"Quel est votre lieu de naissance ?",
	// 					"Quel est la marque de votre premiere voiture ?",
	// 					"Quel est votre sport prefere ?"
	// 					};

	do{
		do{
			for(int i = 0;i < 6;i++){
				printf("%d- %s\n\n",i+1,Listequestions[i] );}
			printf("Choississez votre premiere question secrete : \n");
			// scanf("%d",&choix[0]);
			scanf("%s",choix1);
			if(atoi(choix1) > 6 || atoi(choix1) < 1 ){printf("**************************Erreur de selection de la question 1 recommencez************************** \n\n");}
		}while((atoi(choix1) > 6 || atoi(choix1) < 1 ) );

		while(confirmation[0] != 1){
			printf("Saisissez votre reponse (1 mot): ");
			scanf("%s",u->reponse1);
			printf("Votre réponse est :  %s\n",u->reponse1 );
			do{
				printf("Etes vous sur : \n1- Oui\n2- Non\nVotre choix : ");
				scanf("%d",&confirmation[0]);
			}while(confirmation[0] != 1 && confirmation[0] != 2);
			if (confirmation[0] != 1){printf("\n\n");}
		}

		do{
			for(int i = 0;i < 6;i++){
				printf("%d- %s\n\n",i+1,Listequestions[i] );}
			printf("Choississez votre seconde question secrete : \n");
			scanf("%s",choix2);
			if((atoi(choix2) > 6 || atoi(choix2) < 1) || atoi(choix1) == atoi(choix2)){printf("**************************Erreur de selection de la question 2 recommencez************************** \n\n");}
		}while(((atoi(choix2) > 6 || atoi(choix2) < 1) || atoi(choix1) == atoi(choix2)));

		while(confirmation[1] != 1){
			printf("Saisissez votre reponse (1 mot): ");
			scanf("%s",u->reponse2);
			printf("Votre réponse est :  %s\n",u->reponse2 );
			do{
				printf("Etes vous sur : \n1- Oui\n2- Non\nVotre choix : ");
				scanf("%d",&confirmation[1]);
			}while((confirmation[1] != 1 && confirmation[1] != 2));
			if (confirmation[1] != 1){printf("\n\n");}
		}

		if(atoi(choix1) == atoi(choix2)){printf("**************************Veuillez choisir deux questions DIFFERENTES**************************\n\n");}
	}while((atoi(choix1) == atoi(choix2)));

	u->questions[0] = Listequestions[atoi(choix1)-1];
	u->questions[1] = Listequestions[atoi(choix2)-1];

	u->numquestion1 = atoi(choix1)-1;
	u->numquestion2 = atoi(choix2)-1;
}

Utilisateur* Ajout_user(ListeUser** l){
	Utilisateur* u = (Utilisateur*)malloc_p(sizeof(Utilisateur));
	u->prenom = NULL;
	u->nom = NULL;
	u->login = NULL;
	u->password = NULL;
	u->questions[0] = NULL;
	u->questions[1] = NULL;
	Set_Prenom(u);
	Set_Nom(u);
	Set_Login(l,u);
	Set_Password(u);
	Set_Questions(u);
    u->etat = 1;
    u->lp = NULL;
    u->la = NULL;
    u->nb_amis = 0;
    u->numquestion1 = 0;
    u->numquestion2 = 0;
    u->suivant = NULL;


    return u;
}

void Vider_Liste_Amis(Utilisateur** la,int nb_amis){
		if(nb_amis){
		for(int i = nb_amis;i >= 0;i--){
			free(*(la + i));
		}
	}
	else{printf("Pas d'amis...\n");}
}

void Free_User(Utilisateur* u){
	free(u->prenom);
	free(u->nom);
	free(u->login);
	free(u->password);
	if(u->lp){
		Vider_ListePoste(u->lp);
	}
	if(u->la){
		free(u->la);
	}
	free(u);
}

void Afficher_User_All(Utilisateur* u){
	printf("Nom : %s\n",u->nom);
	printf("Prenom : %s\n", u->prenom);
	printf("Login : %s\n", u->login);
	printf("Mot de Passe : %s\n", u->password);
	printf("Etat : %d\n", u->etat);
	printf("Question 1 : %s\n",u->questions[0]);
	printf("Reponse 1 : %s\n",u->reponse1);
	printf("Question 2 : %s\n",u->questions[1]);
	printf("Reponse 2 : %s\n\n",u->reponse2);
}

// void Afficher_User_Light(Utilisateur *u){
// 	printf("Nom : %s\n",u->nom);
// 	printf("Prenom : %s\n", u->prenom);
// 	printf("Login : %s\n\n", u->login);
// }

void Afficher_liste_user(ListeUser** l){
	if(Liste_user_estVide(l)){
		Utilisateur *u = (*l)->tete;
		printf("------------------------------LISTE----------------------------\n\n");
		while(u){
			// Afficher_User_Light(u);##################################################
			Afficher_User_All(u);
			u = u->suivant;
		}
	}
	else{printf("Liste vide\n");}
}

void Afficher_liste_amis(Utilisateur** la,int nb_amis){
	if(nb_amis){
		for(int i = 0;i < nb_amis;i++){
			Afficher_User_Light(*(la + i));
			printf("\n");
		}
	}
	else{printf("Pas d'amis... Mais Bashlink s'occupe de ca pour vous\n");}
}

void ins_dans_vide(ListeUser **l,Utilisateur *u){
    (*l)->tete = u;
    (*l)->taille++;
}

void ins_debut(ListeUser **l,Utilisateur* u){
    Utilisateur *n = (*l)->tete;
    (*l)->tete = u;
    u->suivant = n;
    (*l)->taille++;
    viderBuffer();
}

void ins_fin(ListeUser **l,Utilisateur* u){
    Utilisateur *n = (*l)->tete;
    while(n->suivant){
        n = n->suivant;
    }
    (*l)->taille++;
    n->suivant = u;
    viderBuffer();
}

void ins_tri(ListeUser **l){
    if(Liste_user_estVide(l)){
    // viderBuffer();
    Utilisateur *e = (*l)->tete;
    Utilisateur *a = NULL;
    Utilisateur *b = Ajout_user(l);
    int flag = 0;

    if(strcmp(b->login,e->login) < 0){
        ins_debut(l,b);
        flag = 1;
    }
        while(flag == 0){
            if(e->suivant){
                if(find_user(l,b->login,NULL)){
                    printf("Ce contact existe deja\n");
                    flag = -1;}

                else if(a){
                    if(strcmp(b->login,a->login) == 0){
                        printf("Ce contact existe deja\n");
                        flag = -1;
                    }
                }
                if ((strcmp(b->login,e->login) > 0) && (strcmp(b->login,e->suivant->login)) < 0){
                    b->suivant = e->suivant;
                    e->suivant = b;
                    flag = 1;
                    (*l)->taille++;
                }
            }
                a = e;
                e = e->suivant;

                if(!e){
                    if (flag == 0){flag =3 ;}
                    else {flag = 2;}
                }

        }
        if ((!e && !a->suivant) && (strcmp(a->login,b->login)!=0)){
            if (flag != 2)
                {ins_fin(l,b);}
        }
	}
	else{Utilisateur* u = Ajout_user(l); ins_dans_vide(l,u);}
}

Utilisateur* Charger_user()
{
    Utilisateur* u = (Utilisateur*)malloc_p(sizeof(Utilisateur));
	u->prenom = NULL;
	u->nom = NULL;
	u->login = NULL;
	u->password = NULL;
	u->questions[0] = NULL;
	u->questions[1] = NULL;
	u->etat = 1;
    u->lp = NULL;
    u->suivant = NULL;

    u->prenom = (char*)malloc_p(sizeof(char)*50);
	u->nom = (char*)malloc_p(sizeof(char)*50);
	u->login = (char*)malloc_p(sizeof(char)*50);
	u->password = (char*)malloc_p(sizeof(char)*30);
	u->questions[0] = (char*)malloc_p(sizeof(char)*70);
	u->questions[1] = (char*)malloc_p(sizeof(char)*70);
    return u;
}

void save_rep(ListeUser** l)
{
    FILE *fichier;
    Utilisateur *u = (*l)->tete;

    fichier = fopen("users/users.txt", "w");
    if(fichier==NULL)
    {
        perror("Vide");
    }
    else
    {
        fprintf(fichier, "\tREPERTOIRE\n");
        while(u != NULL)
        {
            fprintf(fichier, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n", u->prenom, u->nom, u->login, u->password, u->questions[0], u->reponse1, u->questions[1], u->reponse2, u->etat);
            u = u->suivant;
        }
    }
    fclose(fichier);
}

void load_rep(ListeUser **l)
{
    FILE *fichier;
    char rep[500];
    //char lourd[90] = "";

    //snprintf(lourd, sizeof lourd, "users/%s.txt", u->login);

    fichier = fopen("users/users.txt", "r");
    if(!fichier)
    {
        printf("C'est vide timal");
    }
    else
    {
        while(fgets(rep,499,fichier) != 0)
        {
            Utilisateur *u = Charger_user();
            if (fscanf(fichier,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n", u->prenom, u->nom, u->login, u->password, u->questions[0], u->reponse1, u->questions[1], u->reponse2, &u->etat) != EOF)
            {
                if((*l)->tete == NULL)
                {
                    ins_dans_vide(l, u);
                }
                else
                {
                    ins_fin(l, u);
                }
            }
        }
    }
    fclose(fichier);
}

void supp_debut(ListeUser** l){
    Utilisateur *n = (*l)->tete->suivant;
    Utilisateur *u = (*l)->tete;
    Free_User(u);
    (*l)->tete = n;
    (*l)->taille--;
}

void suppUser(ListeUser **l,Utilisateur* u){
    Utilisateur *e = (*l)->tete;
    Utilisateur *a = NULL;
    int flag = 0;
    while(e && flag == 0){

        if(strcmp(u->login,e->login) == 0){
            if(!a){supp_debut(l);}
            else if(!e->suivant){
                Free_User(u);
                a->suivant = NULL;
            }
            else if(strcmp(u->password,e->password) == 0){
                a->suivant = e->suivant;
                Free_User(u);
            }
            flag = 1;
        }
        if((*l)->taille>1){
        a = e;
        e = e->suivant;}
    }
    if(flag == 1){printf("Utilisateur supprime avec succes\n");}
    else{printf("Utilisateur inexistant\n");}
}

void Vider_Liste_Users(ListeUser** l){
	for(int i = (*l)->taille;i>0;i--){
        supp_debut(l);
    }
}

int choix_recherche(){
	char choix[10];
	do{
		printf("Voulez vous rechercher l'utilisateur grace a :\n1 - Son Nom et son Prenom\n2 - Son Pseudo\n");
		printf("Votre choix : ");
		scanf("%s",choix);
		if(atoi (choix) != 1 && atoi(choix) != 2){printf("Erreur de selection\n\n");}
	}while(atoi(choix) != 1 && atoi(choix) != 2);
	return (atoi(choix)-1);
}

void menu_p_post(Poste* p,ListePostes* lp){
	char choix [10]="0";
	int n = atoi(choix); 
	while(n >= 0 && n < 4){
		Afficher_ListePoste(lp);
        printf("1 - Liker le post\n2 - Disliker le post\n3 - Revenir en arriere\nVotre choix : ");
        scanf("%s", choix);

        switch(atoi(choix)){
        	case 1:
        		p->like+=1;
        		break;
        	case 2:
        		p->like-=1;
        		break;
        	case 3:
        		n = 4;
        		break;

        }
	}
}

void menu_recherche(Utilisateur* u,Utilisateur* a){
	char choix [10]="0";
	int n = atoi(choix);
	Poste* p = NULL;
	while(n >= 0 && n < 6){
		printf("--------------------------Sous Menu de Recherche--------------------------\n");
		printf("1 - Suivre cet utilisateur\n2 - Unfollow\n3 - Afficher le menu des post \n4 - Selectionner un post\n5 - Revenir en arriere\n");
		printf("Votre choix : ");
		scanf("%s",choix);

		switch(atoi(choix)){
			case 1:
				u->la = Ajout_Amis(u->la,a,&u->nb_amis);
				break;

			case 2:
				printf("Unfollow\n");///////////////////////////////////////////////////////////
				break;

			case 3:
				Afficher_ListePoste(u->lp);
				break;

			case 4:
				p = Select_poste(u->lp);
				menu_p_post(p,u->lp);
				break;
			case 5:
				n = 6;
				printf("\n\n");
				break;

			default:
				n = 0;
				break;
		}
		system("clear");
	}
}

void menu_poste(ListePostes* lp){
	char choix[10]="0";
	int n = atoi(choix);
	while(n >= 0 && n < 3){
		printf("--------------------------VOS POSTS--------------------------\n");
		Afficher_ListePoste(lp);
		printf("1 - Creer un nouveau post\n2 - Supprimer un post\n3 - Revenir en arriere\n");
		printf("Votre choix : \n");
		scanf("%s",choix);

		switch(atoi(choix)){
			case 1:
				Ajout_post(lp);
				break;

			case 2:
				printf("Entre le numero du post a supprimer : \n");
				scanf("%s",choix);
				suppPost(lp,n);
				n = 0;
				break;

			case 3:
				n = 3;
				break;

			default:
				n = 0;
				break;
		}
		system("clear");
	}
}

void super_menu(ListeUser** l,Utilisateur* u){
	char choix [10]="0";
	int n = atoi(choix);
	char nom[20],prenom[20];
	while(n >= 0 && n < 5){
		printf("--------------------------Bienvenue sur le Super Menu--------------------------\n");
		if(u->nb_amis>0){
			Afficher_liste_amis(u->la,u->nb_amis);
		}
		printf("1 - Post\n2 - Chercher un utilisateur\n3 - Desinscription\n4 - Deconnexion\n");
		printf("Votre choix : ");
		scanf("%s",choix);

		switch(atoi(choix)){
			case 1:
				u->lp = init_ListePoste();		
				menu_poste(u->lp);
				break;

			case 2:
				if (!choix_recherche()){
					printf("Entrez le nom : ");
					scanf("%s",nom);
					printf("Entrez le prenom : ");
					scanf("%s",prenom);
					printf("\n");
					Utilisateur* a = find_user(l,nom,prenom);
					if(a && strcmp(a->nom,nom) == 0 && strcmp(a->prenom,prenom) == 0){
						Afficher_User_Light(a);
						menu_recherche(u,a);
					}
					else{printf("Cet utilisateur n'existe pas (x__x)\n");}
				}
				else{
					printf("Entrez le Pseudo : ");
					scanf("%s",nom);
					printf("\n");
					Utilisateur* a = find_user(l,nom,NULL);
					if(a && strcmp(a->login,nom) == 0){
						Afficher_User_Light(a);
						menu_recherche(u,a);
					}
					else{printf("Cet utilisateur n'existe pas (x__x)\n");}
				}
				break;

			case 3:
				printf("Entrez votre mot de passe afin de vous desinscrire : \n");
				scanf("%s",prenom);
				if (strcmp(prenom,u->password) == 0){
					printf("Merci d'avoir utilise BashLink\n");
					suppUser(l,u);
					n = 5;
				}
				else{
					printf("Mote de passe incorrecte\n");
				}
				
				break;

			case 4:
				n = 5;
				break;

			default:
				n = 0;
				break;
		}
		system("clear");
	}
}

void Connexion(ListeUser** l,Utilisateur* u){
	char login[20],password[30];
	int compteur = 2;
	if(u){
	if(u->etat){
		printf("Entrez votre mot de passe : ");
		scanf("%s",password);
		while(strcmp(password,u->password) != 0 && compteur){
			compteur--;
			printf("Mot de passe incorrecte, il vous reste %d essais\n",compteur );
			printf("Entrez votre mot de passe : ");
			scanf("%s",password);
		}
		if(!compteur){
			u->etat = 0;
		}
		else{
			printf("Connexion\n");
			system("clear");
			super_menu(l,u);
		}
		compteur = 3;
	}
	else{
		printf("############### Votre compte est bloque ###############\n");
		printf("Afin de debloquer votre compte vous allez repondre a vos deux quetions secretes\n");
		printf("%s\n",u->questions[0] );
		scanf("%s",login);
		printf("%s\n",u->questions[1] );
		scanf("%s",password);

		if(!strcmp(login,u->reponse1) && !strcmp(password,u->reponse2)){
			printf("Votre compte a ete debloque avec succes\n");
			u->etat = 1;
			printf("Votre mot de passe est : %s\n",u->password );
		}
		else{
			printf("Echec du deblocage de votre compte\n");
		}
	}
	}
	else{
		printf("Utilisateur non existant, veuillez vous inscrire\n");}
}

void menu(ListeUser** l){
	char choix [10]="0";
	int n= atoi(choix);
	char login[20];
	while(n >= 0 && n < 4){
		printf("--------------------------Bienvenue sur BashLink--------------------------\n");
		printf("1 - Se Connecter\n2 - S'inscrire\n3 - Sortir\n");
		printf("Votre choix : ");
		scanf("%s",choix);
		printf("\n");

		switch(atoi(choix)){
			case 1:
				printf("Entrez votre pseudo : ");
				scanf("%s",login);
				Utilisateur* u = find_user(l,login,NULL);
				Connexion(l,u);
				break;
			case 2:
				viderBuffer();
				ins_tri(l);
				break;
			case 3:
				n = 4;
				break;
		}
		system("clear");
	}
}

void main()
{

	ListeUser** l = init_Liste();

	menu(l);
	Vider_Liste_Users(l);
	free((*l));
	free(l);

}

	// ListeUser** l = init_Liste();
	// ins_tri(l);
	// // ins_tri(l);
	// // ins_tri(l);
	// Afficher_liste_user(l);
	// menu(l);
	// Vider_Liste_Users(l);
	// // Free_User(a);
	// // menu();
	// // free((*l)->tete->nom);
	// // free((*l)->tete->prenom);
	// // free((*l)->tete);
	// free((*l));
	// free(l);


	// Utilisateur* u = Ajout_user();
	// viderBuffer();
	// Utilisateur* a=Ajout_user();
	// viderBuffer();
	// Utilisateur* b = Ajout_user();

	// Afficher_User_All(u);
	// Afficher_User_All(b);
	// Afficher_User_All(a);



	// Utilisateur** a =  (Utilisateur**)malloc_p(sizeof(Utilisateur*));
	// Utilisateur* b = Ajout_user(l);
	// viderBuffer();
	// Utilisateur* c = Ajout_user(l);
	// viderBuffer();
	// Utilisateur* d = Ajout_user(l);
	// viderBuffer();
	// Utilisateur* e = Ajout_user(l);


	// (*l)->tete = b;
	// (*l)->tete->suivant = c;
	// (*l)->tete->suivant->suivant = d;
	// (*l)->tete->suivant->suivant->suivant = e;
	// *a = (*l)->tete;

	// a =(Utilisateur**)realloc_p(a,sizeof(Utilisateur*)*2);
	// *(a+1) = (*l)->tete->suivant;

	// a =(Utilisateur**)realloc_p(a,sizeof(Utilisateur*)*3);
	// *(a+2) = (*l)->tete->suivant->suivant;

	// a =(Utilisateur**)realloc_p(a,sizeof(Utilisateur*)*4);
	// *(a+3) = (*l)->tete->suivant->suivant->suivant;

	// Afficher_User_All(*(a+0));
	// printf("############ LOGIN ========= %s\n",(*(a+0))->login );

	// printf("2 ===========\n");

	// Afficher_User_All(*(a+1));

	// printf("3 ===========\n");

	// Afficher_User_All(*(a+2));

	// printf("4 ===========\n");

	// Afficher_User_All(*(a+3));


	// free(a);
	// Afficher_User_All(b);

	// printf("##############################################\n");
	// Afficher_liste_user(l);


	// Free_User(e);
	// Free_User(d);
	// Free_User(c);
	// Free_User(b);
	// free((*l));
	// free(l);