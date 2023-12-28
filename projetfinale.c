#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define nb_voitures_max 100
#define nb_date 365
#define Max_Matricule 20

typedef struct {
    int j;
    int m;
} date;

typedef struct {
    char disc[512];
    char etat[512];
    char matr[Max_Matricule];
    int exi;
    int id;
} voiture;

voiture v[nb_voitures_max];

typedef struct {
    int id;
    date d;
    struct location* suiv;
} location;

void ajouterv(int id) {
    if (id >= 0 && id < nb_voitures_max) {
        if (v[id].exi == 1)
            puts("Cette voiture existe déjà ");
        else {
            v[id].id = id;
            v[id].exi = 1;
            puts("Donner la description du voiture :");
            scanf("%s", v[id].disc);
            puts("Donner l'etat du voiture :");
            scanf("%s", v[id].etat);
            puts("Donner la matricule du voiture :");
            scanf("%s", v[id].matr);
            puts("Votre voiture a été ajoutée avec succès");
        }
    } else
        puts("ID de la voiture non valide ");
}

void afficher_discription(int id) {
    if (id >= 0 && id < nb_voitures_max) {
        if (v[id].exi == 1)
            puts(v[id].disc);
        else
            puts("ID non valide");
    } else
        puts("ID non valide");
}

void afficher_etat(int id) {
    if (id >= 0 && id < nb_voitures_max) {
        if (v[id].exi == 1)
            puts(v[id].etat);
        else
            puts("ID non valide");
    } else
        puts("ID non valide");
}

void supprimerv(int id) {
    if (id >= 0 && id < nb_voitures_max) {
        if (v[id].exi == 1) {
            v[id].exi = 0;
            puts("La voiture a été supprimée avec succès");
        } else
            puts("ID non valide");
    } else
        puts("ID non valide");
}

location* louerv(int id, date da, location* tete) {
    if (v[id].exi!=1) puts("Voiture n'est pas valable ");
    else {
            if (!strcmp(v[id].etat, "disponible")) {
            location* r = (location*)malloc(sizeof(location));
            r->d = da;
            r->id = id;
            r->suiv = tete;
            tete = r;
            puts("La voiture a été louée avec succès ");
        } else
            puts("La voiture est indisponible");
    }
    

    return tete;  
}

void afficherHISTORIQUEjpj(location* tete, date d) {
    location* temp = tete;
    int found = 0;

    if (temp == NULL)
        puts("Aucune opération de location n'a été faite ");
    else {
        while (temp != NULL) {
            if (temp->d.j == d.j && temp->d.m == d.m) {
                printf("Location le %d/%d : Voiture %d\n", temp->d.j, temp->d.m, temp->id);
                found = 1;
            }
            temp = temp->suiv;
        }
        if (!found)
            puts("Aucune opération de location pour cette date");
    }
}

void afficherHISTORIQUEmpm(location* tete, date d) {
    location* temp = tete;
    int found = 0;

    if (temp == NULL)
        puts("Aucune opération de location n'a été faite ");
    else {
        while (temp != NULL) {
            if (temp->d.m == d.m) {
                printf("Location le %d/%d : Voiture %d\n", temp->d.j, temp->d.m, temp->id);
                found = 1;
            }
            temp = temp->suiv;
        }
        if (!found)
            puts("Aucune opération de location pour ce mois");
    }
}
bool estDateValide(int jour, int mois) {
    
    if ((mois >= 1 && mois <= 12) && (jour >= 1 && jour <= 31)) {
        
        return true;
    } else {
        return false;
    }
}
int main() {
    location* tete = NULL;
    int choix;
    
    puts("Bienvenue dans le menu de notre application  ");
    puts("1- Ajouter une voiture.");
    puts("2- Ajouter plusieurs voitures.");
    puts("3- Supprimer une voiture.");
    puts("4- Louer une voiture ");
    puts("5- Afficher l'historique pour une date donnée.");
    puts("6- Afficher l'historique pour un mois donné.");
    puts("7- Quitter l'application");
    puts("Votre choix:");
    
    scanf("%d", &choix);

    switch (choix) {
        case 1:
        {
            puts("Donner l'ID de la voiture que vous souhaitez ajouter");
            int id;
            scanf("%d", &id);
            while (!(id >= 0) || !(id < nb_voitures_max)) {
                puts("Identifiant non valide ");
                scanf("%d", &id);
            }
            ajouterv(id);
            break;
        }
       case 2 :
       {
           puts("donner le nombre des voitures ");
           int nbrv;
           scanf("%d",&nbrv);
           for(int i=0;i<nbrv;i++){
               puts("Donner l'ID de la voiture que vous souhaitez ajouter");
                int id;
                scanf("%d", &id);
                while (!(id >= 0) || !(id < nb_voitures_max)) {
                    puts("Identifiant non valide ");
                    scanf("%d", &id);
            }
            ajouterv(id);
           }
       }
       case 3 :
       {
           puts("Donner l'ID de la voiture que vous souhaitez supprimer :");
            int idSuppression;
            scanf("%d", &idSuppression);
            if (idSuppression >= 0 && idSuppression < nb_voitures_max) {
                supprimerv(idSuppression);
            } else {
                puts("ID non valide");
            }
            break;
       }
       case 4 :
       {
           puts("Donner l'ID de la voiture que vous souhaitez louer :");
            int idLocation;
            scanf("%d", &idLocation);
            if (idLocation >= 0 && idLocation < nb_voitures_max) {
                date d;
                puts("Donner le jour de la location :");
                scanf("%d", &d.j);
                puts("Donner le mois de la location :");
                scanf("%d", &d.m);
                if (estDateValide(d.j, d.m)) tete = louerv(idLocation, d, tete);
                else puts("Date non valide") ;
                
                
            } else {
                puts("ID non valide");
            }
            break;
       }
       case 5 :
       {
            date d;
            puts("Donner le jour pour afficher l'historique :");
            scanf("%d", &d.j);
            puts("Donner le mois pour afficher l'historique :");
            scanf("%d", &d.m);
            afficherHISTORIQUEjpj(tete, d);
            break;
       }
       case 6 :
       {
            date d;
            puts("Donner le mois pour afficher l'historique :");
            scanf("%d", &d.m);
            afficherHISTORIQUEmpm(tete, d);
            break;
       }
       case 7 :
       {
           puts("Fermeture du programme");
       }

        default:
            puts("Choix non valide");
            break;
    }

    return 0;
}
