#include <stdio.h>

void zad12()
{
    int x, y;

    printf("_________\n");
    for (int i=0; i<10; i++)
    {
        x = i+1;
        y = 2*x*x - 30*x + 10;
        printf("|%2d|%4i|\n", x, y);
    }
    printf("_________\n");
}

void zad13()
{
    printf("Select option:\n");
    printf("+ - * / \n");

    char option;
    scanf(" %c", &option);

    double first, second;

    printf("Enter two numbers: ");
    scanf(" %lf%lf", &first, &second);

    double result;

    switch (option)
    {
    case '+':
        {
            result = first + second;
            break;
        }
    case '-':
        {
            result = first - second;
            break;
        }
    case '*':
        {
            result = first*second;
            break;
        }
    case '/':
        {
            if (second == 0)
            {
                printf("Dividing by zero.");
                return;
            }
            result = first/second;
            break;
        }
    default:
        {
            printf("Unknown operation.");
            return;
        }
    }

    printf("%f %c %f = %f", first, option, second, result);
}

void zad14()
{
    char translations[6][3][10] =
    {
        { "tysiac", "tysiace", "tysiecy" },
        { "milion", "miliony", "milionow" },
        { "miliard", "miliardy", "miliardow" },
        { "bilion", "biliony", "bilionow" },
        { "biliard", "biliardy", "biliardow" },
        { "trylion", "tryliony", "trylionow" }
    };

    char hundreds[9][16] =
    {
        "sto", "dwiescie", "trzysta", "czterysta", "piecset",
        "szescset", "siedemset", "osiemset", "dziewiecset"
    };

    char tens[9][16] =
    {
        "dwadziescia", "trzydziesci", "czterdziesci", "piecdziesiat",
        "szescdziesiat", "siedemdziesiat", "osiemdziesiat", "dziewiedziesiat"
    };

    char singles[20][16] =
    {
        "zero", "jeden", "dwa", "trzy", "cztery", "piec", "szesc", "siedem",
        "osiem", "dziewiec", "dziesiec", "jedenascie", "dwanascie", "trzynascie",
        "czternascie", "pietnascie", "szesnascie", "siedemnascie", "osiemnascie", "dziewietnascie"
    };

    unsigned long long int number, temp;
    int size = 0;


    printf("Enter a number: ");

    scanf(" %llu", &number);
    temp = number;

    if (number<20)
    {
        printf("%s\n", singles[number]);
        return;
    }

    int threes[6] =
    {
        0, 0, 0, 0, 0, 0
    };

    while(temp)
    {
        threes[size] = temp % 1000;
        temp /= 1000;
        size ++;
    }

    int s, d, j;

    for(int i=5; i>=0; i--)
    {
        if (threes[i] == 0)
        {
            continue;
        }

        s = threes[i]/100;
        d = (threes[i]/10)%10;
        j = threes[i]%10;

        if(s)
        {
            printf("%s ", hundreds[s-1]);
        }
        if(d<=1)
        {
            printf("%s ", singles[threes[i]%100]);
        }
        else
        {
            printf("%s ", tens[d-2]);
            if(j)
            {
                printf("%s ", singles[j]);
            }
        }
        if(i>0)
        {
            if((s==0)&&(d==0)&&(j==1))
            {
                printf("%s ", translations[i-1][0]);
            }
            else if((j<5)&&(j>1))
            {
                printf("%s ", translations[i-1][1]);
            }
            else
            {
                printf("%s ", translations[i-1][2]);
            }
        }
    }


}

void zad17()
{
    int total_len = 0;
    char z = getchar();
    unsigned signs[128];
    for(int i=0; i<128; i++)
    {
        signs[i] = 0;
    }

    while (z != '\n')
    {
        signs[z] += 1;
        total_len++;
        z = getchar();
    }

    for (int i=0; i<128; i++)
    {
        if (signs[i])
        {
            printf("Procentowy udzial znaku %c to %f\n", i, (float)signs[i]/(float)total_len);
        }
    }
}

int main()
{
    //zad12();
    //zad13();
    //zad14();
    zad17();
    return 0;
}
