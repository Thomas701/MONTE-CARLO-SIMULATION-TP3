#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mt.h"

#define M_PI 3.14159265358979323846

/**
 * \fn double simPi(int n)
 * \brief Approximer la valeur de PI avec un nombre n de points
 * 
 * \param[in] int n : Nombre de points que l'on va générer
 * 
 * \return double : Retourne l'approximation de PI
 * 
 * \author DUPOIS Thomas
 */
double simPi(int n)
{
    double x, y;
    int point_cercle = 0;
    for (int i = 0; i < n; i++)
    {
        x = genrand_real1();
        y = genrand_real1();
        if (x * x + y * y <= 1.0)
            point_cercle++;
    }
    return 4 * ((double) point_cercle / (double) n);
}

/**
 * \fn double * estimated_PIs(int n, int n2)
 * \brief Faire un nombre n d'expériences indépendante afin d'obtenir 
 *        différentes approximation de pi qui seront stockés dans un tableau
 * 
 * \param[in] int n : Nombre d'expériences indépendantes
 * \param[in] int n2 : Nombre de points générés par expérience
 * 
 * \return double * : Retourne le tableau contenant l'ensemble des approximation de PI
 * 
 * \author DUPOIS Thomas
 */
double * estimated_PIs(int n, int n2)
{
    double * tab = (double*) malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
        tab[i] = simPi(n2);
    return tab;
}

/**
 * \fn double moyenne_PI(double * tab, int size)
 * \brief Retourne la moyenne des doubles contenus dans un tableau
 * 
 * \param[in] double * tab : Tableau contenant les approximation de PI de chaque expérience
 * \param[in] int size : taille du tableau ( nombre d'expériences aléatoires)
 * 
 * \return double : Retourne la moyenne des approximations de PI contenu dans le tableau 
 * 
 * \author DUPOIS Thomas
 */
double moyenne_PI(double * tab, int size)
{
    double total = 0.0;
    for (int i = 0; i < size; i++)
        total = total + tab[i];
    return total / size;
}

/**
 * \fn double variance_calc(double * tab, double moyenne, int size)
 * \brief Retourne l'approximation de la variance
 * 
 * \param[in] double * tab : Tableau contenant les approximation de PI de chaque expérience
 * \param[in] double moyenne : moyenne des approximations de PI
 * \param[in] int size : taille du tableau (nombre d'expériences indépendantes)
 * 
 * \return double : Retourne la'approximation de la variance'
 * 
 * \author DUPOIS Thomas
 */
double variance_calc(double * tab, double moyenne, int size)
{
    double somme = 0.0;
    for (int i = 0; i < size; i++)
        somme = somme + ((tab[i] - moyenne) * (tab[i] - moyenne));
    return somme / (size - 1);
}

/**
 * \fn double r_calc(double t, double variance, double n)
 * \brief Retourne le rayon de confiance
 * 
 * \param[in] double t : Introdcution de la loi de Student pour corriger 
 *                       le fait que l'on utilise une approximation de la variance
 * \param[in] double variance : approximation de la variance
 * \param[in] double n : Nombre d'expériences indépendantes
 * 
 * \return double : Retourne la valeur du rayon de confiance
 * 
 * \author DUPOIS Thomas
 */
double r_calc(double t, double variance, double n)
{
    return t * (sqrt(variance / n));
}

/**
 * \fn void intervalle_confiance(int experiment, double t, int point)
 * \brief Affiche l'intervalle de confiance
 * 
 * \param[in] int experiment : Nombre d'expériences indépéndantes
 * \param[in] double t : Loi de Student, correction de l'approximation de la variance
 * 
 * \return void : Ne retourne rien, affiche l'intervalle de confiance
 * 
 * \author DUPOIS Thomas
 */
void intervalle_confiance(int experiment, double t, int point)
{
    double * tab = estimated_PIs(experiment, point);
    double moyenne = moyenne_PI(tab, experiment);
    double var = variance_calc(tab, moyenne, experiment);
    double r = r_calc( t, var, experiment);
    printf("L'intervalle de confiance obtenu avec %d experiences independantes et %d points pour chaque tirage est:\n\n", experiment, point);
    printf("Moyenne:%lf\n", moyenne);
    printf("Variance:%lf\n", var);
    printf("R = %lf\n", r);
    printf("Intervalle de confiance: [%lf;%lf]\n", moyenne-r, moyenne+r);
    free(tab);
}

int main(int argc, char const *argv[])
{
    /*Initialisation Mersenne Twister*/
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    double pi, moyenne;
    double * tab;
    int n;

    /*CERTAINES PARTIES DU MAIN PRENNENT UN TEMPS IMPORTANT AVANT D'AVOIR TERMINE LEUR EXECUTION*/
    /*POUR OBTENIR DIRECTEMENT LES RESULTATS, CONSULTEZ LE RAPPORT*/

    // printf("-------COMPLEMENT: Observation de la convergence de PI-------\n\n");
    // for (int i = 0; i < 1000; i = i+10)
    //     printf("nbr points: %d, valeur pi: %lf\n", i, simPi(i));
    
    // printf("----------------QUESTION 1----------------\n\n");
    // pi = simPi(1000);
    // printf("Approximation de PI pour 1000 points:\n");
    // printf("%lf\n", pi);
    // pi = simPi(1000000);
    // printf("Approximation de PI pour 1_000_000 points:\n");
    // printf("%lf\n", pi);
    // pi = simPi(1000000000);
    // printf("Approximation de PI pour 1_000_000_000 points:\n");
    // printf("%lf\n", pi);

    // printf("----------------QUESTION 2----------------\n\n");
    // n = 10;
    // int tab_exp[3] = {1000, 1000000, 1000000000};
    // for (int i = 0; i < 3; i++)
    // {
    //     tab = estimated_PIs(n, tab_exp[i]);
    //     printf("Estimation de PI pour %d expériences indépendantes et %d points à chaque expérience:\n", n, tab_exp[i]);
    //     moyenne = moyenne_PI(tab, n);
    //     printf("%lf\n", moyenne);
    //     free(tab);
    //     printf("Erreur absolu:\n");
    //     printf("%lf\n", fabs(M_PI - moyenne));
    //     printf("Erreur relative:\n");
    //     printf("%lf\n", (moyenne/M_PI));
    // }

    // printf("----------------QUESTION 3----------------\n\n");
    // printf("Intervalle de confiance avec niveau de confiance alpha=0.05\n");
    // intervalle_confiance(10, 2.228, 1000000);
    // intervalle_confiance(20, 2.086, 1000000);
    // intervalle_confiance(30, 2.042, 1000000);
    // intervalle_confiance(40, 2.021, 1000000);
    // printf("Intervalle de confiance avec niveau de confiance alpha=0.01\n");
    // intervalle_confiance(10, 2.764, 1000000);
    // intervalle_confiance(20, 2.528, 1000000);
    // intervalle_confiance(30, 2.457, 1000000);
    // intervalle_confiance(40, 2.423, 1000000);
    // printf("Intervalle de confiance avec niveau de confiance alpha=0.0005\n");
    // intervalle_confiance(10, 4.587, 1000000);
    // intervalle_confiance(20, 3.850, 1000000);
    // intervalle_confiance(30, 3.646, 1000000000);
    // intervalle_confiance(40, 3.373, 1000000000);

    return 0;
}
