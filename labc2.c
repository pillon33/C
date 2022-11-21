#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void zad15(int n){
    int tab[n][n];
    int elements = n*n;
    int x = 0;
    int y = 0;
    int range = n-1;
    int step = 0;
    int el = 0;
    while (el < elements)
    {
        while(x<=range)
        {
            tab[y][x++] = el++;
        }
        x--;
        y++;
        if(el>=elements)
        {
            break;
        }

        while(y<=range)
        {
            tab[y++][x] = el++;
        }
        y--;
        x--;
        if(el>=elements)
        {
            break;
        }

        range--;

        while(x>=step)
        {
            tab[y][x--] = el++;
        }
        x++;
        y--;
        if(el>=elements)
        {
            break;
        }

        step++;

        while (y>=step)
        {
            tab[y--][x] = el++;
        }
        y++;
        x++;
    }

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            printf("%6d", tab[i][j]);
        }
        printf("\n");
    }
}

void zad16(int n){
    int tab[n];
    for (int i=0; i<n; i++)
    {
        tab[i] = 0;
    }
    int p = 2;
    int i = p;
    while (p<n)
    {
        if (tab[p] > 0)
        {
            p++;
            continue;
        }

        i = 2*p;

        while (i<n)
        {
            tab[i] = 1;
            i += p;
        }

        p++;
    }

    for (int i=0; i<n; i++)
    {
        if (tab[i] == 0)
        {
            printf("%4d", i);
        }
    }
}


void zad18(){
    char kostka[5][6] =
    {
        {218, 196, 196, 196, 191, '\n'},
        {179, ' ', ' ', ' ', 179, '\n'},
        {179, ' ', ' ', ' ', 179, '\n'},
        {179, ' ', ' ', ' ', 179, '\n'},
        {192, 196, 196, 196, 217, 0}
    };

    int n;
    int odp;

    do{
        n = rand()%6 + 1;

        switch(n){
        case 1:
            kostka[2][2] = '*';
            break;
        case 2:
            kostka[1][1] = '*';
            kostka[3][3] = '*';
            break;
        case 3:
            kostka[1][1] = '*';
            kostka[2][2] = '*';
            kostka[3][3] = '*';
            break;
        case 4:
            kostka[1][1] = '*';
            kostka[3][1] = '*';
            kostka[1][3] = '*';
            kostka[3][3] = '*';
            break;
        case 5:
            kostka[1][1] = '*';
            kostka[3][1] = '*';
            kostka[1][3] = '*';
            kostka[3][3] = '*';
            kostka[2][2] = '*';
            break;
        case 6:
            kostka[1][1] = '*';
            kostka[2][1] = '*';
            kostka[3][1] = '*';
            kostka[2][1] = '*';
            kostka[2][2] = '*';
            kostka[2][3] = '*';
            break;
        }

        printf("%s\n", kostka);
        scanf(" %c", &odp);
        for (int i=1; i<=3; i++)
        {
            for (int j=1; j<=3; j++)
            {
                kostka[i][j] = ' ';
            }
        }
    }while( odp != 'k' );
}
int main(){
    srand(time(NULL));
    int n;
    printf("Wprowadz n: ");
    scanf(" %d", &n);
    //zad15(n);
    //zad16(n);
    zad18();
    return 0;
}
