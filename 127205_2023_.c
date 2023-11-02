#include <stdio.h>
#include <stdlib.h>

void v()
{
    char sign;
    FILE *f = fopen("dataloger.txt", "r");
    char row;
    if (f == NULL)
    {
        printf("Neotvoreny subor\n");
    }
    if (f != NULL)
    {
        while (sign != EOF)
        {
            while (sign != '\n'){
                fscanf(f, "%c", &row);
                printf("ID. mer. modulu: %c\n", row);
                //printf("Pozícia modulu: %s\n",);
                //printf("Typ mer. veliciny: %s\n",);
                //printf("Hodnota: %s\n",);
                //printf("Cas merania: %s\n",);
                //printf("Datum merania: %s\n",);
                printf("\n");
            }
            
        }
    }
}

void n()
{
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
    /*case 'n':
        n();
        break;
    case 'c':
        c();
        break;
    }
    */
    }
}