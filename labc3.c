#include <stdio.h>

int n = 1;

void zad19()
{
    unsigned rozmiar = 16;
    char *tekst = (char*)malloc(rozmiar);

    if (tekst)
    {
        printf("Podaj tekst\n");
        unsigned i = 0;

        do
        {
            tekst[i] = getchar();
            if (tekst[i] == '\n') break;
            i++;
            if (i == (rozmiar - 1))
            {
                char* temp = realloc(tekst, rozmiar + 16);
                if (temp)
                {
                    tekst = temp;
                    rozmiar += 16;
                }
                else
                {
                    printf("Blad realloc.");
                    break;
                }
            }
        }while(1);
        tekst[i] = 0;
        printf("\n\n%s", tekst);
    }
    else
    {
        printf("Brak pamieci.");
    }
}

void zad20()
{
    int x = 3;
    printf("Poadaj rozmiar tablicy: ");
    scanf(" %d", &n);
    int tab[n];
    int y = x + n;
    char *tekst = malloc(n);
    printf("Adres x: %p\n", &x);
    printf("Adres y: %p\n", &y);
    printf("Adres tab: %p\n", &tab);
    printf("Adres tekst: %p\n", &tekst);
    printf("Adres n: %p\n", &n);
}

int main()
{
    zad20();
    return 0;
}
