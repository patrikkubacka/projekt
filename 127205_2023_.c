#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void v(FILE **f, int pressed_n, int *pressed_v, char **ID_mer_mod, char **Poz_mod, char **Typ_mer_vel, double *Hodnota, char **Cas_mer, char **Dat_mer)
{
    char line[300];
    *f = fopen("dataloger.txt", "r");
    int counter = 0;
    if (*pressed_v == 0) // ak nebolo stlacene "v" vypise neotvoreny subor
    {
        if (*f == NULL)
        {
            printf("Neotvoreny subor\n");
        }
        if (*f != NULL)
        {
            *pressed_v = 1;
        }
    }
    if (*pressed_v == 1) // ak bolo stlacene "v" tak postupuje podla toho ci bolo stlacene aj "n"
    {
        if (pressed_n == 0) // ak nebolo stlacene "n" program vypíše záznamy zo suboru
        {
            while (fgets(line, sizeof(line), *f) != NULL)
            {
                switch (counter)
                {
                case 0:
                    printf("ID. mer. modulu: ");
                    break;
                case 1:
                    printf("Pozícia modulu: ");
                    break;
                case 2:
                    printf("Typ mer. veliciny: ");
                    break;
                case 3:
                    printf("Hodnota: ");
                    break;
                case 4:
                    printf("Cas merania: ");
                    break;
                case 5:
                    printf("Datum merania: ");
                    break;
                case 6:
                    counter = -1;
                    break;
                }
                printf("%s", line);
                counter++;
            }
        }
        if (pressed_n == 1) // ak bolo stlacene "n" tak vypise zaznamy z dyn. polí
        {
            for (int i = 0; i < 10; i++)
            {
                printf("Id mer. modulu: ");
                printf("%s\n", ID_mer_mod[i]);
                printf("Pozícia modulu:");
                printf("%s\n", Poz_mod[i]);
                printf("Typ mer. veliciny: ");
                printf("%s\n", Typ_mer_vel[i]);
                printf("Hodnota: ");
                printf("%g\n", Hodnota[i]);
                printf("Cas merania: ");
                printf("%s\n", Cas_mer[i]);
                printf("\n");
            }
        }
    }
    fseek(*f, 0, SEEK_SET);
}

void n(FILE *f, int *pressed_n, int pressed_v, char ***ID_mer_mod, char ***Poz_mod, char ***Typ_mer_vel, double **Hodnota, char ***Cas_mer, char ***Dat_mer)
{
    if (pressed_v == 0) // ak nebolo stlacene v tak subor nebol otvoreny
    {
        printf("Neotvoreny subor.\n");
        *pressed_n = 0;
    }

    if (pressed_v == 1)
    {
        char line[100];
        int counter = 1;
        fseek(f, 0, SEEK_SET);
        while (fgets(line, sizeof(line), f) != NULL) // ráta počet záznamov v subore dataloger
        {
            if (line[0] == '\n')
            {
                counter++;
            }
        }
        *ID_mer_mod = (char **)malloc(counter * sizeof(char *));
        *Poz_mod = (char **)malloc(counter * sizeof(char *));
        *Typ_mer_vel = (char **)malloc(counter * sizeof(char *));
        *Hodnota = (double *)malloc(counter * sizeof(double));
        *Cas_mer = (char **)malloc(counter * sizeof(char *));
        *Dat_mer = (char **)malloc(counter * sizeof(char *));

        char row[100];
        double cislo;
        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < counter; i++)
        {
            fgets(row, sizeof(row), f); // nacita prvy riadok suboru a ulozi do row
            (*ID_mer_mod)[i] = (char *)malloc(6 * sizeof(char));
            row[5] = '\0';
            (char *)strcpy(((*ID_mer_mod)[i]), row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita druhy riadok zo suboru a ulozi do row
            (*Poz_mod)[i] = (char *)malloc(15 * sizeof(char));
            row[14] = '\0';
            (char *)strcpy((*Poz_mod)[i], row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita treti riadok zo suboru a ulozi do row
            (*Typ_mer_vel)[i] = (char *)malloc(3 * sizeof(char));
            row[2] = '\0';
            (char *)strcpy((*Typ_mer_vel)[i], row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita stvrty riadok zo suboru a ulozi do row
            cislo = atof(row);
            (*Hodnota)[i] = cislo; // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita piaty riadok zo suboru a ulozi do row
            (*Cas_mer)[i] = (char *)malloc(5 * sizeof(char));
            row[4] = '\0';
            (char *)strcpy((*Cas_mer)[i], row); // skopiruje obsah row do dyn. pola
            (*Cas_mer)[i][4] = '\0';

            fgets(row, sizeof(row), f); // nacita siesty riadok zo suboru a ulozi do row
            (*Dat_mer)[i] = (char *)malloc(9 * sizeof(char));
            row[8] = '\0';
            (char *)strcpy((*Dat_mer)[i], row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f);
        }
        *pressed_n = 1;
    }
}

void c()
{
    int y;
    scanf("%d", &y); // nacita pocet mesiacov zo vstupu
    FILE *file = fopen("ciachovanie.txt", "r");
}

int main(void)
{
    FILE *f;
    int pressed_v = 0; // stlacenie "v" a "n" nastavi na 0
    int pressed_n = 0;
    char **ID_mer_mod = NULL, **Poz_mod = NULL, **Typ_mer_vel = NULL, **Cas_mer = NULL, **Dat_mer = NULL;
    double *Hodnota = NULL;
    char letter;
    do
    {
        scanf("%c", &letter); // nacita pismeno zo vstupu
        switch (letter)       
        {
        case 'v':
            v(&f, pressed_n, &pressed_v, ID_mer_mod, Poz_mod, Typ_mer_vel, Hodnota, Cas_mer, Dat_mer); //pošle parametra funkcii 'v' a vyvola ju
            break;

        case 'n':
            n(f, &pressed_n, pressed_v, &ID_mer_mod, &Poz_mod, &Typ_mer_vel, &Hodnota, &Cas_mer, &Dat_mer); //pošle parametra funkcii 'n' a vyvola ju
            break;

        case 'c':
            c();
            break;
            /*
        case 's':
            s();
            break;
        case 'h':
            h();
            break;
            */
        case 'k':
            free(ID_mer_mod);
            ID_mer_mod = NULL;
            free(Poz_mod);
            Poz_mod = NULL;
            free(Typ_mer_vel);
            Typ_mer_vel = NULL;
            free(Hodnota);
            Hodnota = NULL;
            free(Cas_mer);
            Cas_mer = NULL;
            free(Dat_mer);
            Dat_mer = NULL;
            break;
        }
    } while (letter != 'k');
}