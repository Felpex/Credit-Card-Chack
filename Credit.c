#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//prototipo
bool verificacionInput ( long long card);
bool verificacionNumero (long long card, int digitos);
void franquicia(long long card);


int main (void)
{
    printf(ANSI_COLOR_YELLOW"El siguiente programa determina si un número dado es (o no) una tarjeta de crédito.\n");
    printf("Explica paso a paso el proceso de verificación e imprime como última línea la franquicia a la que pertenece o si es un número invalido\n" ANSI_COLOR_RESET);
    printf("\n");
    printf(ANSI_COLOR_RESET "Número de tarjeta de crédito: " ANSI_COLOR_GREEN);
    long long card = GetLongLong();
    printf(ANSI_COLOR_RESET);

//Verificacion de dígitos
    if(verificacionInput(card))
    {
        franquicia(card);
    } else
    {
        printf(ANSI_COLOR_RED "Número inválido\n" ANSI_COLOR_RESET);
    }
    return 0;
}

bool verificacionInput (long long card)
{
    bool v;
    int digitos = 0;
    digitos = floor(log10(llabs(card))) + 1;
    if (digitos < 13 || digitos > 16)
    {
        v = false;
    } else
    {
        if(verificacionNumero (card, digitos))
        {
            v = true;
        } else
        {
            v = false;
        }
    }
    return v;
}

bool verificacionNumero (long long card, int digitos)
{
    bool v;
    int cardArray[digitos-1], sumaDeParesArray[digitos-1], sumaDeParesArray2[digitos-1], sumaDeImparesArray[digitos-1];
    int sumaDePares = 0, sumaTotalPares = 0, sumaDeImpares = 0, sumaTotalImpares = 0, sumaTotal = 0;
    long long n = card;

//Asignacion en array

    for (int i = 0; i <= (digitos-1); i++)
    {
        cardArray[i]= (int)(n % 10);
        n /= 10;
        //test
        //printf("%d", cardArray[i]);
    }
    //test
    //printf("\n");
    printf("\n");
    printf("Paso 1: Multiplicar por 2 cada 2 dígitos, contando del penúltimo hacia atrás:");
    printf("\n");
    for (int i = 1; i <= (digitos-1); i = i+2)
    {
        sumaDeParesArray[sumaDePares] = cardArray[i]*2;
        printf("%d ", sumaDeParesArray[sumaDePares]);
        sumaDePares++;
    }
    printf("\n");
    printf("\n");
    //printf("Tamaño del array: %d\n", sumaDePares);
   // printf("\n");
    printf("Paso 2: Sumar cada dígito (Y no el resultado de cada multiplicación)\n");
    for (int i = 0, j = 0; i <= (sumaDePares-1); i++, j++)
    {
        if (sumaDeParesArray[i] >= 10)
        {
            sumaDeParesArray2[j] = sumaDeParesArray[i] % 10;
            sumaDeParesArray[i] /= 10;
            sumaTotalPares = sumaTotalPares + sumaDeParesArray2[j];
            printf("%d + ", sumaDeParesArray2[j]);
            j++;
            sumaDeParesArray2[j] = sumaDeParesArray[i] % 10;
            sumaDeParesArray[i] /= 10;
            sumaTotalPares = sumaTotalPares + sumaDeParesArray2[j];
            printf("%d + ", sumaDeParesArray2[j]);
        } else if (sumaDeParesArray[i] <= 0)
        {
            sumaDeParesArray2[j] = 0;
            sumaTotalPares = sumaTotalPares + sumaDeParesArray2[j];
            printf("%d + ", sumaDeParesArray2[j]);
        } else
        {
            sumaDeParesArray2[j] = sumaDeParesArray[i] % 10;
            sumaDeParesArray[i] /= 10;
            sumaTotalPares = sumaTotalPares + sumaDeParesArray2[j];
            printf("%d + ", sumaDeParesArray2[j]);
        }
    }
    printf("0 = %d\n", sumaTotalPares);
    printf("\n");
    printf("Paso 3: Sumar los números no multiplicados\n");
    for (int i = 0; i <= (digitos-1); i = i+2)
    {
        sumaDeImparesArray[sumaDeImpares] = cardArray[i];
        sumaTotalImpares = sumaTotalImpares + sumaDeImparesArray[sumaDeImpares];
        printf("%d + ", sumaDeImparesArray[sumaDeImpares]);
        sumaDeImpares++;
    }
    printf("0 = %d \n", sumaTotalImpares);
    printf("\n");
    printf("\n");
    printf("Paso 4: ahora sumamos los dos valores y verificamos que el último dígito sea igual a 0\n");
    sumaTotal = sumaTotalImpares + sumaTotalPares;
    printf("Suma Total = %d\n", sumaTotal);
    printf("\n");
    if ( sumaTotal % 10 == 0)
    {
        v = true;
    } else
    {
        v = false;
       // printf("Número inválido\n");
    }
    return v;
}

void franquicia (long long card)
{
    int digitos = floor(log10(llabs(card))) + 1;
    int cardArray[digitos];
    long long n = card;
    for (int i = 0; i <= (digitos-1); i++)
    {
        cardArray[i]= (int)(n % 10);
        n /= 10;
    }
    printf(ANSI_COLOR_YELLOW "El número es válido y la franquicia es: " ANSI_COLOR_GREEN);
    if(cardArray[digitos-1]==3 && (cardArray[digitos-2]==4 || cardArray[digitos-2]==7))
    {
        printf("AMERICAN EXPRESS");
    } else if (cardArray[digitos-1]==4)
    {
        printf("VISA");
    } else if (cardArray[digitos-1]==5 && (cardArray[digitos-2]>=1 || cardArray[digitos-2]<=5))
    {
        printf("MASTER CARD");
    } else
    {
        printf(" Otra diferente a AMEX, VISA y MASTER"ANSI_COLOR_RESET);
    }
    printf(ANSI_COLOR_RESET"\n");
}
