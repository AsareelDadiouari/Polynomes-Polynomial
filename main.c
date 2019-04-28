#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "header/header.h"

int main()
{
    float coef;
    int deg, choix;

    do
    {
        menu();
        printf("choix : ");
        scanf("%d", &choix);
        fflush(stdin);

        switch (choix)
        {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
            break;
        case 6:
            /* code */
            break;
        case 7:
            /* code */
            break;
        case 8:
            /* code */
            break;
        case 9:
            /* code */
            break;
        case 10:
            /* code */
            break;
        case 11:
            /* code */
            break;
        case 12:
            /* code */
            break;
        case 13:
            /* code */
            break;
        case 14:
            /* code */
            break;
        case 15:
            printf("FIN DU PROGRAMME\n");
            break;

        default:
            printf("touche inconnue !\n");
            break;
        }
    } while (choix != 15);

    system("pause");
    return 0;
}
