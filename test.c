#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {c = getchar();}
}

void* malloc_p(unsigned int s){
	void * p;
  	if(p=malloc(s)) return p;
  	else {perror("Erreur allocation\n");exit(EXIT_FAILURE);}
}

void* realloc_p(void* p, unsigned int s){
    if(p=realloc(p,s)) return p;
    else{perror("Erreur allocation"); exit(0);}
}

void fgets_m(char **pchaine,int n){
	*pchaine = (char*)malloc_p(sizeof(char)*n);
	fgets(*pchaine,n,stdin);
	*pchaine = realloc_p(*pchaine,strlen(*pchaine)+1);
	(*pchaine)[strlen(*pchaine)-1] = '\0';
}

typedef struct Utilisateur Utilisateur;
void Afficher_User_Light(Utilisateur *u);
//######################################################
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

void init_Liste_Amis(Liste_Amis** la){
	(*la) = (Liste_Amis*)malloc_p(sizeof(Liste_Amis));
	(*la)->taille = 0;
	(*la)->tete = NULL;

}

void Ajout_Amis_Vide(Liste_Amis* la, Utilisateur* u){
	la->tete = (Amis*)malloc_p(sizeof(Amis));
	la->tete->Utilisateur = u;
	la->tete->suivant = NULL;
	la->taille++;
}

void Ajout_Amis_Fin(Liste_Amis* la, Utilisateur* u){
	Amis* a = la->tete;
	Amis* b = (Amis*)malloc_p(sizeof(Amis));
	while(a->suivant){
		a = a->suivant;
	}
	b->Utilisateur = u; 
	b->suivant = NULL;
	a->suivant = b;
	la->taille++;
}

void Ajout_Amis(Liste_Amis* la,Utilisateur* u){
	//si ce n'est pas l'user actuel

	if(la->taille){
		Ajout_Amis_Fin(la,u);}
	else{Ajout_Amis_Vide(la,u);}
}

void Supp_Amis_Debut(Liste_Amis* la){
	Amis* a = la->tete->suivant;
	free(la->tete);
	la->tete = a;
	la->taille--; 
}

void Supp_Amis_Fin(Liste_Amis* la){
	Amis* a = la->tete;
	while(a->suivant){
		a = a->suivant;
	}
	la->taille--;
	free(a);
}

void Supp_Amis_Milieu(Liste_Amis* la,int n){
	Amis* a = la->tete;
	Amis* c = a->suivant;
	int flag = 0,i = 0;
	while(!flag){
		if(i == n){
			a->suivant = c->suivant;
			free(a);
			flag = 1;
		}
		c = a;
		a = a->suivant;
		i++;
	}
}

void Vider_Liste_Amis(Liste_Amis* la){
		for(int i = 0;i < la->taille+1;i++){
			Supp_Amis_Debut(la);
		}
		free(la);
}

void Afficher_Liste_Amis(Liste_Amis* la){
		if(la->taille){
		Amis* a = la->tete;
		for(int i = 0;i < la->taille;i++){
			printf("Numero %d \n",i+1);
			Afficher_User_Light(a->Utilisateur);
			a = a->suivant;
			printf("\n");
		}
	}
	else{printf("Pas d'amis... Mais Bashlink s'occupe de ca pour vous\n");}
}

//######################################################

struct Utilisateur{
	char* nom;
	char* prenom;
	char* login;
	char* password;
	int etat;//Booléen qui dit si l'utilateur est bloqué
	char* questions[2];
	int numquestion1;
	int numquestion2;
	int nb_amis;
	Liste_Amis* la;

	Utilisateur* suivant;
};

void Afficher_User_Light(Utilisateur *u){
	printf("Nom : %s\n",u->nom);
	printf("Prenom : %s\n", u->prenom);
	printf("Login : %s\n\n", u->login);
}

void Free_User(Utilisateur* u){
	free(u->login);
	free(u->nom);
	free(u->prenom);
	free(u);
}

void main(){
	Utilisateur* u = (Utilisateur*)malloc_p(sizeof(Utilisateur));
	Utilisateur* b = (Utilisateur*)malloc_p(sizeof(Utilisateur));
	init_Liste_Amis(&u->la);

	fgets_m(&u->nom,30);
	fgets_m(&u->prenom,30);
	fgets_m(&u->login,30);
	Afficher_User_Light(u);

	fgets_m(&b->nom,30);
	fgets_m(&b->prenom,30);
	fgets_m(&b->login,30);
	Afficher_User_Light(b);

	Ajout_Amis(u->la,b);
	Ajout_Amis(u->la,u);
	Ajout_Amis(u->la,b);

	Afficher_Liste_Amis(u->la);
	Supp_Amis_Milieu(u->la,2);
	Afficher_Liste_Amis(u->la);


	Vider_Liste_Amis(u->la);


	Afficher_User_Light(b);


	Free_User(u);
	Free_User(b);
}
