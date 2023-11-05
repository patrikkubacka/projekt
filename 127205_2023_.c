#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void v()
{
    char line[300];
    FILE *f = fopen("dataloger.txt", "r");
    int poc = 0;
    if (f == NULL)
    {
        printf("Neotvoreny subor\n");
    }
    if (f != NULL)
    {

        while (fgets(line, sizeof(line), f) != NULL)
        {
            switch (poc)
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
                poc = -1;
                break;
            }
            printf("%s", line);
            poc++;
        }
    }
}

void n()
{
    FILE *f = fopen("dataloger.txt", "r");
    char line[100];
    int count = 1;
    while (fgets(line, sizeof(line), f) != NULL) // ráta počet záznamov v subore dataloger
    {
        if (line[0] == '\n')
        {
            count++;
        }
    }
}

void c()
{
    int y;
    scanf("%d", &y);
    FILE *file = fopen("ciachovanie.txt", "r");
}

int main(void)
{
    char letter;
    scanf("%c", &letter);
    switch (letter)
    {
    case 'v':
        v();
        break;
    case 'n':
        n();
        break;
        /*
    case 'c':
        c();
        break;
    case 's':
        s();
        break;
    case 'h':
        h();
        break;
    case 'k':
        k();
        break;
        */
    }
}