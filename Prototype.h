#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct Date Date;
struct Date{
    int secondes;
    int minutes;
    int heures;
    int jour;
    int mois;
    int annee;
    int jour_test;
};

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
typedef struct Amis Amis;
struct Amis{
	Utilisateur* Utilisateur;
	Amis* suivant;
};

typedef struct Liste_Amis Liste_Amis;
struct Liste_Amis{
	Amis* tete;
	int taille;
};

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
	Liste_Amis* la;
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

void* malloc_p(unsigned int s);
void* realloc_p(void* p, unsigned int s);
void Set_Questions(Utilisateur* u);
Date* Ajout_Date(Date* d);
void Afficher_Date(Date* d);
ListeUser** init_Liste();
ListePostes* init_ListePoste();
void viderBuffer();
int chaine_isdigit(char* chaine);
int ListePoste_estVide(ListePostes* lp);
Poste* init_Poste(Poste* p);
void fgets_m(char **pchaine,int n);
void Private_Public(Poste* p);
void Post_dans_vide(ListePostes* lp);
void Post_en_fin(ListePostes* lp);
void Afficher_User_Light(Utilisateur *u);
void init_Liste_Amis(Liste_Amis** la);
void Ajout_Amis_Vide(Liste_Amis* la, Utilisateur* u);
void Ajout_Amis_Fin(Liste_Amis* la, Utilisateur* u);
void Ajout_Amis(Liste_Amis* la,Utilisateur* m,Utilisateur* u);
void Supp_Amis_Debut(Liste_Amis* la);
void Supp_Amis_Fin(Liste_Amis* la);
void Supp_Amis_Milieu(Liste_Amis* la,int n);
void Vider_Liste_Amis(Liste_Amis* la);
void Afficher_Liste_Amis(Liste_Amis* la);
void Ajout_post(ListePostes* lp);
void Afficher_ListePoste(ListePostes* lp);
void suppPoste_debut(ListePostes* lp);
void suppPoste_fin(ListePostes *lp);
void suppPoste_milieu(ListePostes* lp, int n);
void suppPost(ListePostes* lp, int n);
Poste* Select_poste(ListePostes* lp);
void Vider_ListePoste(ListePostes* lp);
int Liste_user_estVide(ListeUser** l);
Utilisateur* find_user(ListeUser **l,char* login,char* password);
void Set_Nom(Utilisateur* u);
void Set_Prenom(Utilisateur* u);
void Set_Login(ListeUser** l,Utilisateur* u);
void Set_Password(Utilisateur* u);
void Set_Questions(Utilisateur* u);
void Vider_ListePoste(ListePostes* lp);
int Liste_user_estVide(ListeUser** l);
Utilisateur* find_user(ListeUser **l,char* login,char* password);
void Set_Nom(Utilisateur* u);
void Set_Prenom(Utilisateur* u);
void Set_Login(ListeUser** l,Utilisateur* u);
void Set_Password(Utilisateur* u);
void Set_Questions(Utilisateur* u);
Utilisateur* Ajout_user(ListeUser** l);
void Free_User(Utilisateur* u);
void Afficher_User_All(Utilisateur* u);
void Afficher_liste_user(ListeUser** l);
void ins_dans_vide(ListeUser **l,Utilisateur *u);
void ins_debut(ListeUser **l,Utilisateur* u);
void ins_fin(ListeUser **l,Utilisateur* u);
void ins_tri(ListeUser **l);
Utilisateur* Charger_user();
void mkdir_m();
void save_rep(ListeUser** l);
void load_rep(ListeUser **l);
void supp_debut(ListeUser** l);
void suppUser(ListeUser **l,Utilisateur* u);
void Vider_Liste_Users(ListeUser** l);
int choix_recherche();
void menu_p_post(Poste* p,ListePostes* lp);
void menu_recherche(Utilisateur* u,Utilisateur* a);
void menu_poste(ListePostes* lp);
void super_menu(ListeUser** l,Utilisateur* u);
void Connexion(ListeUser** l,Utilisateur* u);
void menu(ListeUser** l);
