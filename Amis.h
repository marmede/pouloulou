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

Amis* find_Amis(Liste_Amis* la,char* login){
	if(la->tete){
	Amis* a = la->tete;
	while(a){
		if(strcmp(a->Utilisateur->login,login) == 0){
			return a;
		}
		a = a->suivant;
	}
	return NULL;
}
return NULL;
}

void Ajout_Amis(ListeUser** l,Liste_Amis* la,Utilisateur* m,Utilisateur* u){
	if(strcmp(u->login,m->login) == 0){
		printf("Ne soyez autant narcissique :/\n");
	}
	else if(!find_Amis(la,u->login)){

		if(la->taille){
			Ajout_Amis_Fin(la,u);}
		else{Ajout_Amis_Vide(la,u);}
	}
	else{printf("Nous voyons que vous apprecie beaucoup cette personne mais vous etes deja amis avec elle\n");}
}

void Supp_Amis_Debut(Liste_Amis* la){
	if(la->taille){
	Amis* a = la->tete->suivant;
	free(la->tete);
	la->tete = a;
	la->taille--; 
	}
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

int find_Amis_num(Liste_Amis* la,Utilisateur* u,char* login){
	if(strcmp(u->login,login) == 0){
		printf("Ne soyez autant auto-destructeur :/\n");
	}
	else if(find_Amis(la,login)){
		Amis* a = la->tete;
		int i = 1;
		while(a){
			if(strcmp(login,a->Utilisateur->login) == 0){
				return i;
			}
			i++;
		}
	}else{printf("Cet amis n'existe pas\n");}
}

void Supp_Amis(Liste_Amis* la,int n){
	if(n > 0 && n <= la->taille){
		if(n == 1){
			Supp_Amis_Debut(la);
		}
		else if(n == la->taille){
			Supp_Amis_Fin(la);
		}
		else{Supp_Amis_Milieu(la,n);}
	}
	else{printf("Erreur num =========== %d ET %d\n",n,la->taille);}
}

void Unfollow(Liste_Amis* la,Utilisateur* u,char* login){
	int num = find_Amis_num(la,u,login);
	Supp_Amis(la,num);
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