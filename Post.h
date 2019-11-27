
ListePostes* init_ListePoste(){
	ListePostes* lp = (ListePostes*)malloc_p(sizeof(ListePostes));
	lp->tete = NULL;
	lp->taille = 0;
	return lp;
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

void Private_Public(Poste* p){
	int choix = 0;
	while(choix != 1 && choix != 2){
		printf("1 - Post Public\n2 - Post Privee\n");
		printf("Votre choix : \n");
		scanf("%d",&choix);
		switch(choix){
			case 1:
				p->public = 0;
				break;

			case 2:
				p->public = 1;
				break;

			default:
				choix = 0;
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


Poste* Select_poste(ListePostes* lp){
	int choix = 0;
	Afficher_ListePoste(lp);
	while(choix <1 && choix > lp->taille){
		printf("Entrez le numero du post\n");
		scanf("%d",&choix);
	}
	Poste* p = lp->tete;
	while(p->num != choix){
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

void menu_poste(ListePostes* lp){
	int choix = 0;
	while(choix >= 0 && choix < 3){
		printf("--------------------------VOS POSTS--------------------------\n");
		Afficher_ListePoste(lp);
		printf("1 - Creer un nouveau post\n2 - Supprimer un post\n3 - Revenir en arriere\n");
		printf("Votre choix : \n");
		scanf("%d",&choix);

		switch(choix){
			case 1:
				Ajout_post(lp);
				break;

			case 2:
				printf("Entre le numero du post a supprimer : \n");
				scanf("%d",&choix);
				suppPost(lp,choix);
				choix = 0;
				break;

			case 3:
				choix = 3;
				break;

			default:
				choix = 0;
				break;
		}
		system("clear");
	}
}

void menu_p_post(Poste* p,ListePostes* lp){
	int choix = 0;
	while(choix >= 0 && choix < 4){
		Afficher_ListePoste(lp);
        printf("1 - Liker le post\n2 - Disliker le post\n3 - Revenir en arriere\nVotre choix : ");
        scanf("%d", &choix);

        switch(choix){
        	case 1:
        		p->like+=1;
        		break;
        	case 2:
        		p->like-=1;
        		break;
        	case 3:
        		choix = 4;
        		break;

        }
	}
}