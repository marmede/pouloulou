ListeUser** init_Liste(){
	ListeUser** l = (ListeUser**)malloc_p(sizeof(ListeUser));
	*l = (ListeUser*)malloc_p(sizeof(ListeUser));
	(*l)->taille = 0;
	(*l)->tete = NULL;
	return l;
}

void Afficher_User_Light(Utilisateur *u){
	printf("Nom : %s\n",u->nom);
	printf("Prenom : %s\n", u->prenom);
	printf("Login : %s\n\n", u->login);
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

void Afficher_liste_user(ListeUser** l){
	if(Liste_user_estVide(l)){
		Utilisateur *u = (*l)->tete;
		printf("------------------------------LISTE----------------------------\n\n");
		while(u){
			Afficher_User_All(u);
			u = u->suivant;
		}
	}
	else{printf("Liste vide\n");}
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
    //viderBuffer();
}

void ins_tri(ListeUser **l){
    if(Liste_user_estVide(l)){
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
                {
                    ins_fin(l,b);
                    viderBuffer();
                }
        }
	}
	else{Utilisateur* u = Ajout_user(l); ins_dans_vide(l,u);}
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
	int choix = 0;
	do{
		printf("Voulez vous rechercher l'utilisateur grace a :\n1 - Son Nom et son Prenom\n2 - Son Pseudo\n");
		printf("Votre choix : ");
		scanf("%d",&choix);
		if(choix != 1 && choix != 2){printf("Erreur de selection\n\n");}
	}while(choix != 1 && choix != 2);
	return (choix-1);
}

int Liste_user_estVide(ListeUser** l){
	if((*l)->tete){return 1;}
	else{return 0;}
}