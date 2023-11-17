#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void v(FILE **f, int pressed_n, int *pressed_v, char **ID_mer_mod, char **Poz_mod, char **Typ_mer_vel, double *Hodnota, char **Cas_mer, char **Dat_mer, int number)
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
            fseek(*f, 0, SEEK_SET);
        }
        if (pressed_n == 1) // ak bolo stlacene "n" tak vypise zaznamy z dyn. polí
        {
            for (int i = 0; i < number; i++)
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
                printf("Datum merania: ");
                printf("%s\n", Dat_mer[i]);
                printf("\n");
            }
        }
    }
    printf("\n");
}

void n(FILE *f, int *pressed_n, int pressed_v, char ***ID_mer_mod, char ***Poz_mod, char ***Typ_mer_vel, double **Hodnota, char ***Cas_mer, char ***Dat_mer, int *number)
{
    if (pressed_v == 0) // ak nebolo stlacene 'v' tak subor nebol otvoreny
    {
        printf("Neotvoreny subor.\n");
        *pressed_n = 0;
    }

    if (pressed_v == 1)
    {
        char line[100];
        int counter = 1;
        fseek(f, 0, SEEK_SET);
        if (*pressed_n == 1)
        {
            free(*ID_mer_mod);
            *ID_mer_mod = NULL;
            free(*Poz_mod);
            *Poz_mod = NULL;
            free(*Typ_mer_vel);
            *Typ_mer_vel = NULL;
            free(*Hodnota);
            *Hodnota = NULL;
            free(*Cas_mer);
            *Cas_mer = NULL;
            free(*Dat_mer);
            *Dat_mer = NULL;
        }

        while (fgets(line, sizeof(line), f) != NULL) // ráta počet záznamov v subore dataloger
        {
            if (line[0] == '\n')
            {
                counter++;
            }
        }

        *ID_mer_mod = (char **)malloc(counter * sizeof(char *));
        *Poz_mod = (char **)malloc(counter * sizeof(char *));
        *Typ_mer_vel = (char **)malloc(counter * sizeof(char *)); // vytvorí dyn. polia
        *Hodnota = (double *)malloc(counter * sizeof(double));
        *Cas_mer = (char **)malloc(counter * sizeof(char *));
        *Dat_mer = (char **)malloc(counter * sizeof(char *));

        char row[100];
        double cislo;
        fseek(f, 0, SEEK_SET); // posunie sa na zaciatok suboru

        for (int i = 0; i < counter; i++)
        {

            fgets(row, sizeof(row), f); // nacita prvy riadok suboru a ulozi do row
            (*ID_mer_mod)[i] = (char *)malloc(6 * sizeof(char));
            row[5] = '\0';                           // za posledny znak v row da prazdny znak
            (char *)strcpy(((*ID_mer_mod)[i]), row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita druhy riadok zo suboru a ulozi do row
            (*Poz_mod)[i] = (char *)malloc(15 * sizeof(char));
            row[14] = '\0';                     // za posledny znak v row da prazdny znak
            (char *)strcpy((*Poz_mod)[i], row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita treti riadok zo suboru a ulozi do row
            (*Typ_mer_vel)[i] = (char *)malloc(3 * sizeof(char));
            row[2] = '\0';                          // za posledny znak v row da prazdny znak
            (char *)strcpy((*Typ_mer_vel)[i], row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita stvrty riadok zo suboru a ulozi do row
            cislo = atof(row);          // konvertuje char na double
            (*Hodnota)[i] = cislo;      // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita piaty riadok zo suboru a ulozi do row
            (*Cas_mer)[i] = (char *)malloc(5 * sizeof(char));
            row[4] = '\0';                      // za posledny znak v row da prazdny znak
            (char *)strcpy((*Cas_mer)[i], row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita siesty riadok zo suboru a ulozi do row
            (*Dat_mer)[i] = (char *)malloc(9 * sizeof(char));
            row[8] = '\0';                      // za posledny znak v row da prazdny znak
            (char *)strcpy((*Dat_mer)[i], row); // skopiruje obsah row do dyn. pola

            fgets(row, sizeof(row), f); // nacita prazdny riadok za blokom zaznamu
        }
        *pressed_n = 1;
        *number = counter;
    }
    printf("\n");
}

void c(char **ID_mer_mod, int number, char **Dat_mer, int pressed_n)
{
    int y;
    char ID[50];
    char line[50];
    char Date[50];
    int count = 1;
    int was_ciach = 0;
    int correct = 1;

    if (pressed_n == 0)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }

    else
    {
        scanf("%d", &y); // nacita pocet mesiacov zo vstupu
        FILE *file = fopen("ciachovanie.txt", "r");
        while (fgets(line, sizeof(line), file) != NULL) // ráta počet záznamov v subore ciachovanie
        {
            if (line[0] == '\n')
            {
                count++;
            }
        }
        fseek(file, 0, SEEK_SET);

        for (int j = 0; j < number; j++)
        {
            for (int i = 0; i < count; i++)
            {
                fgets(ID, sizeof(ID), file);
                ID[5] = '\0';
                fgets(Date, sizeof(Date), file);
                Date[8] = '\0';
                if (strcmp(ID, ID_mer_mod[j]) == 0)
                {
                    was_ciach++;
                    int mes_ciach = ((atol(Date) / 100) % 100); // atol konvertuje string na long
                    int mes_datalog = ((atol(Dat_mer[j]) / 100) % 100);
                    int after_ciach = mes_datalog - mes_ciach;
                    if (after_ciach > 0 && after_ciach > y)
                    {
                        printf("%s je %d mesiacov po ciachovani.\n", ID, (after_ciach - y));
                        correct = 0;
                    }
                }
                fgets(ID, sizeof(ID), file);
            }
            if (was_ciach == 0)
            {
                printf("%s nie je ciachovaný.\n", ID_mer_mod[j]);
                correct = 0;
            }
            was_ciach = 0;
            fseek(file, 0, SEEK_SET);
        }
        if (correct == 1)
        {
            printf("Data su korektné.");
        }
        printf("\n");
    }
}

int compare(char *first_c, char *second_c) // porovna dva stringy a zisti ci sa rovnaju
{
    while (*first_c != '\0' && *second_c != '\0')
    {
        if (*first_c != *second_c)
        {
            return 0;
        }
        first_c++;
        second_c++;
    }
    if (*first_c == '\0' && *second_c == '\0')
    {
        return 1;
    }
    return 0;
}

void s(char **ID_mer_mod, char **Typ_mer_vel, int number, int pressed_n, double *Hodnota, char **Poz_mod, char **Cas_mer, char **Dat_mer)
{
    char ID[6];
    char TYP[3];
    int c = 0;
    scanf("%s %s", ID, TYP);

    if (pressed_n == 0)
    {
        printf("polia nie su vytvorene.\n");
        return;
    }

    else
    {
        ID_mer_mod = (char **)malloc(c * sizeof(char *));
        Poz_mod = (char **)malloc(c * sizeof(char *));
        Typ_mer_vel = (char **)malloc(c * sizeof(char *));
        Hodnota = (double *)malloc(c * sizeof(double));
        Cas_mer = (char **)malloc(c * sizeof(char *));
        Dat_mer = (char **)malloc(c * sizeof(char *));
        for (int i = 0; i < number; i++) // ráta pocet zaznamov v subore rovnakych so vstupom
        {
            if (compare(ID_mer_mod[i], ID) == 1)
            {
                if (compare(Typ_mer_vel[i], TYP) == 1)
                {
                    c += 1;
                }
                else
                {
                    printf("Pre dany vstup neexistuju zaznamy.\n");
                }
            }
        }

        FILE *vystup = fopen("vystup_S.txt", "w");
        if (fclose(vystup) == 0)
        {
            printf("pre dany vstup je vytvoreny txt subor.\n");
        }
        else
        {
            printf("pre dany vstup nie je vytvoreny txt subor.\n");
        }
        if (c == 0)
        { // ak nie su ziadne rovnake zaznamy ako vstup tak vypise ze neexistuju
            printf("Pre dany vstup neexistuju zaznamy.");
            return;
        }
    }
}

void h(int pressed_n, char **Typ_mer_vel, int number, double *Hodnota)
{
    int count_field[6] = {0};  // pole pre pocitanie zaznamov
    double max_field[6] = {0}; // pole na maximum
    double min_field[6] = {0}; // pole na minimum
    char *typ_field[6] = {"RM", "RD", "RO", "PI", "PE", "PA"};

    if (pressed_n == 0)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    else
    {
        for (int i = 0; i < number; i++)
        {
            if (compare(Typ_mer_vel[i], "RM") == 1) // zistuje pocet zaznamov 'RM'
            {
                count_field[0]++;
                if (count_field[0] == 1)
                {
                    max_field[0] = min_field[0] = Hodnota[i]; // nastavi min aj max na prvu hodnotu ktoru bude neskor prepisovat
                }
                else
                {
                    if (max_field[0] < Hodnota[i]) // zistuje max a min hodnotu
                    {
                        max_field[0] = Hodnota[i];
                    }
                    if (min_field[0] > Hodnota[i])
                    {
                        min_field[0] = Hodnota[i];
                    }
                }
            }
            if (compare(Typ_mer_vel[i], "RD") == 1) // zistuje pocet zaznamov 'RD'
            {
                count_field[1]++;
                if (count_field[1] == 1)
                {
                    max_field[1] = min_field[1] = Hodnota[i];
                }
                else
                {
                    if (max_field[1] < Hodnota[i]) // zistuje max a min hodnotu
                    {
                        max_field[1] = Hodnota[i];
                    }
                    if (min_field[1] > Hodnota[i])
                    {
                        min_field[1] = Hodnota[i];
                    }
                }
            }
            if (compare(Typ_mer_vel[i], "RO") == 1) // zistuje pocet zaznamov 'RO'
            {
                count_field[2]++;
                if (count_field[2] == 1)
                {
                    max_field[2] = min_field[2] = Hodnota[i];
                }
                else
                {
                    if (max_field[2] < Hodnota[i]) // zistuje max a min hodnotu
                    {
                        max_field[2] = Hodnota[i];
                    }
                    if (min_field[2] > Hodnota[i])
                    {
                        min_field[2] = Hodnota[i];
                    }
                }
            }
            if (compare(Typ_mer_vel[i], "PI") == 1) // zistuje pocet zaznamov 'PI'
            {
                count_field[3]++;
                if (count_field[3] == 1)
                {
                    max_field[3] = min_field[3] = Hodnota[i];
                }
                else
                {
                    if (max_field[3] < Hodnota[i]) // zistuje max a min hodnotu
                    {
                        max_field[3] = Hodnota[i];
                    }
                    if (min_field[3] > Hodnota[i])
                    {
                        min_field[3] = Hodnota[i];
                    }
                }
            }
            if (compare(Typ_mer_vel[i], "PE") == 1) // zistuje pocet zaznamov 'PE'
            {
                count_field[4]++;
                if (count_field[4] == 1)
                {
                    max_field[4] = min_field[4] = Hodnota[i];
                }
                else
                {
                    if (max_field[4] < Hodnota[i]) // zistuje max a min hodnotu
                    {
                        max_field[4] = Hodnota[i];
                    }
                    if (min_field[4] > Hodnota[i])
                    {
                        min_field[4] = Hodnota[i];
                    }
                }
            }
            if (compare(Typ_mer_vel[i], "PA") == 1) // zistuje pocet zaznamov 'PA'
            {
                count_field[5]++;
                if (count_field[5] == 1)
                {
                    max_field[5] = min_field[5] = Hodnota[i];
                }
                else
                {
                    if (max_field[5] < Hodnota[i]) // zistuje max a min hodnotu
                    {
                        max_field[5] = Hodnota[i];
                    }
                    if (min_field[5] > Hodnota[i])
                    {
                        min_field[5] = Hodnota[i];
                    }
                }
            }
        }
        printf("Typ \t\t Pocetnost \t Minimum \t\t Maximum\n");
        for (int i = 0; i < 6; i++) // vypisuje vystup
        {
            if (count_field[i] != 0)
            {
                printf("%s \t\t %d \t\t %lf \t\t %lf\n", typ_field[i], count_field[i], min_field[i], max_field[i]);
            }
        }
        printf("\n");
    }
}

void z(int pressed_n, int *number, char ***ID_mer_mod, char ***Poz_mod, char ***Typ_mer_vel, double **Hodnota, char ***Cas_mer, char ***Dat_mer)
{
    char ID[6];
    int poc = 0;

    if (pressed_n == 0)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }

    else
    {
        double *temp_hodnota = (double *)malloc((*number) * sizeof(double)); // vytvaram docasne polia
        char **temp_id = (char **)malloc((*number) * sizeof(char *));
        char **temp_typ = (char **)malloc((*number) * sizeof(char *));
        char **temp_poz = (char **)malloc((*number) * sizeof(char *));
        char **temp_cas = (char **)malloc((*number) * sizeof(char *));
        char **temp_dat = (char **)malloc((*number) * sizeof(char *));

        for (int i = 0; i < *number; i++)
        {
            temp_hodnota[i] = (*Hodnota)[i]; // prepisujem data do docasnych poli
            temp_id[i] = (*ID_mer_mod)[i];
            temp_typ[i] = (*Typ_mer_vel)[i];
            temp_poz[i] = (*Poz_mod)[i];
            temp_cas[i] = (*Cas_mer)[i];
            temp_dat[i] = (*Dat_mer)[i];
        }
        free(*Hodnota);
        free(*ID_mer_mod);
        free(*Typ_mer_vel); // vymazavam data z poli
        free(*Cas_mer);
        free(*Dat_mer);
        free(*Poz_mod);

        scanf("%s", ID);
        for (int i = 0; i < *number; i++)
        {
            if (compare(temp_id[i], ID) == 1) // zistujem pocet dat ktore neboli vymazane
            {
                poc++;
            }
        }
        *Hodnota = (double *)malloc(((*number) - poc) * sizeof(double));
        *ID_mer_mod = (char **)malloc(((*number) - poc) * sizeof(char *));
        *Poz_mod = (char **)malloc(((*number) - poc) * sizeof(char *)); // vytvaram nove polia bez vymazanych dat
        *Typ_mer_vel = (char **)malloc(((*number) - poc) * sizeof(char *));
        *Cas_mer = (char **)malloc(((*number) - poc) * sizeof(char *));
        *Dat_mer = (char **)malloc(((*number) - poc) * sizeof(char *));

        int x = 0;
        for (int i = 0; i < *number; i++)
        {
            if (compare(temp_id[i], ID) != 1)
            {

                (*ID_mer_mod)[x] = (temp_id)[i];
                (*Poz_mod)[x] = (temp_poz)[i];
                (*Typ_mer_vel)[x] = (temp_typ)[i]; // plnim nevymazane polia
                (*Hodnota)[x] = (temp_hodnota)[i];
                (*Cas_mer)[x] = (temp_cas)[i];
                (*Dat_mer)[x] = (temp_dat)[i];
                x++;
            }
        }

        free(temp_id);
        free(temp_hodnota);
        free(temp_cas);
        free(temp_dat);
        free(temp_typ);
        free(temp_poz);

        printf("Vymazalo sa: %d zaznamov!\n", poc);
        printf("\n");

        *number = *number - poc;
    }
}

int main(void)
{
    FILE *f;
    int pressed_v = 0; // stlacenie "v" a "n" nastavi na 0
    int pressed_n = 0;
    char **ID_mer_mod = NULL, **Poz_mod = NULL, **Typ_mer_vel = NULL, **Cas_mer = NULL, **Dat_mer = NULL;
    double *Hodnota = NULL;
    int number = 0;
    char letter;
    do
    {
        scanf("%c", &letter); // nacita pismeno zo vstupu
        switch (letter)
        {
        case 'v':
            v(&f, pressed_n, &pressed_v, ID_mer_mod, Poz_mod, Typ_mer_vel, Hodnota, Cas_mer, Dat_mer, number); // pošle parametra funkcii 'v' a vyvola ju
            break;

        case 'n':
            n(f, &pressed_n, pressed_v, &ID_mer_mod, &Poz_mod, &Typ_mer_vel, &Hodnota, &Cas_mer, &Dat_mer, &number); // pošle parametra funkcii 'n' a vyvola ju
            break;

        case 'c':
            c(ID_mer_mod, number, Dat_mer, pressed_n);
            break;

        case 's':
            s(ID_mer_mod, Typ_mer_vel, number, pressed_n, Hodnota, Poz_mod, Cas_mer, Dat_mer);
            break;

        case 'h':
            h(pressed_n, Typ_mer_vel, number, Hodnota);
            break;

        case 'z':
            z(pressed_n, &number, &ID_mer_mod, &Poz_mod, &Typ_mer_vel, &Hodnota, &Cas_mer, &Dat_mer);
            break;

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