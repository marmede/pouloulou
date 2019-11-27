#include "Prototype.h"
#include "Post.h"
#include "Utilisateur.h"
#include "Amis.h"

void* malloc_p(unsigned int s){
	void * p;
  	if(p=malloc(s)) return p;
  	else {perror("Erreur allocation\n");exit(EXIT_FAILURE);}
}

void* realloc_p(void* p, unsigned int s){
    if(p=realloc(p,s)) return p;
    else{perror("Erreur allocation"); exit(0);}
}

Date* Ajout_Date(){
    Date* d = (Date*)malloc_p(sizeof(Date));
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

void fgets_m(char **pchaine,int n){
	*pchaine = (char*)malloc_p(sizeof(char)*n);
	fgets(*pchaine,n,stdin);
	*pchaine = realloc_p(*pchaine,strlen(*pchaine)+1);
	(*pchaine)[strlen(*pchaine)-1] = '\0';
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
	u->numquestion1 = 0;
	u->numquestion2 = 0;
	u->etat = 0;
    u->lp = init_ListePoste();
    u->suivant = NULL;
    u->nb_amis = 0;
    u->la = NULL;

    init_Liste_Amis(&u->la);
    u->prenom = (char*)malloc_p(sizeof(char)*50);
	u->nom = (char*)malloc_p(sizeof(char)*50);
	u->login = (char*)malloc_p(sizeof(char)*50);
	u->password = (char*)malloc_p(sizeof(char)*30);
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
            fprintf(fichier, "%s\t%s\t%s\t%s\t%d\t%s\t%d\t%s\t%d\n", u->prenom, u->nom, u->login, u->password, u->numquestion1, u->reponse1, u->numquestion2, u->reponse2, u->etat);
            u = u->suivant;
        }
    }
    fclose(fichier);
}

void mkdir_m(){
    if(fork()==0){
    execl("/bin/mkdir","mkdir", "users",NULL);
    exit(0);
    }
    wait(NULL);
}

void load_rep(ListeUser **l)
{
    FILE *fichier;
    char rep[500];
    Utilisateur *u;

    fichier = fopen("users/users.txt", "r");
    if(!fichier)
    {
        printf("Pas de fichier de sauvegarde\n");
        mkdir_m();
    }
    else
    {
        while(fgets(rep,499,fichier) != 0)
        {
            u = Charger_user();
            if (fscanf(fichier,"%s %s %s %s %d %s %d %s %d", u->prenom, u->nom, u->login, u->password, &u->numquestion1, u->reponse1, &u->numquestion2, u->reponse2, &u->etat) != EOF)
            {
                u->questions[0] = Listequestions[u->numquestion1];
                u->questions[1] = Listequestions[u->numquestion2];
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
        fclose(fichier);
        Free_User(u);
    }

}

void menu_recherche(ListeUser** l,Utilisateur* u,Utilisateur* a){
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
				Ajout_Amis(l,u->la,u,a);
				break;

			case 2:
				printf("Unfollow\n");///////////////////////////////////////////////////////////
				Unfollow(u->la,u,a->login);
				break;

			case 3:
				if(a->lp->tete){
				Afficher_ListePoste(a->lp);}
				else{printf("Cet utilisateur n'as encore rien poste\n");}
				break;

			case 4:
				p = Select_poste(a->lp);
				menu_p_post(p,a->lp);
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

void super_menu(ListeUser** l,Utilisateur* u){
	char choix [10]="0";
	int n = atoi(choix);
	char nom[20],prenom[20];
	while(n >= 0 && n < 5){
		printf("--------------------------Bienvenue sur le Super Menu--------------------------\n");
		if(u->la->taille >0){
			Afficher_Liste_Amis(u->la);
		}
		printf("1 - Post\n2 - Chercher un utilisateur\n3 - Desinscription\n4 - Deconnexion\n");
		printf("Votre choix : ");
		scanf("%s",choix);

		switch(atoi(choix)){
			case 1:
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
						menu_recherche(l,u,a);
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
						menu_recherche(l,u,a);
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
		// system("clear");
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
			printf("Mot de passe incorrecte, il vous reste %d essais\n",compteur+1 );
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
		// system("clear");
	}
}

void main()
{

	ListeUser** l = init_Liste();
	load_rep(l);
	menu(l);
	printf("======================%d\n",(*l)->taille );
	save_rep(l);
	Vider_Liste_Users(l);
	free((*l));
	free(l);

}
