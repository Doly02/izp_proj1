//
//  main.c
//  t9search2
//
//  Created by Tomáš Dolák on 14.10.2022.
//  Login: xdolak09
#include "string.h"
#include "ctype.h"
#include <stdio.h>
#include <stdlib.h>
                    /* FUNKCE NA VYTAŽENÍ ŘÁDKU Z TEXTOVÉHO SOUBORU */

//funkce načítá postupně všechny znaky z řádku zastaví se EOFem nebo znakem konce řádku navíc kontroluje zda pole není přeplněné

int funkcion(char jeden_radek[])
{
    int index = 0;
    char znak = '0';
    while (1)
    {
        znak = getc(stdin);
        if (znak == '\n' || znak == EOF)
        {
            if (znak == EOF)
                return 0;
            break;
        }
        if (index > 100)
            return 0;
        jeden_radek[index] = znak;
        index++;
    }
    return 1;
}

                    /* FUNKCE NA PŘEVEDENÍ VŠECH VELKÝCH PÍSMEN VE JMÉNĚ NA MALÉ */

int convertor(char phone_name[])
{   for (int i = 0; i < 100; i++)
    {
        if ((phone_name[i] >= 65 && phone_name[i] <= 90)&&phone_name[i]!=46)
            phone_name[i] = phone_name[i] + 32;
    }
    return 0;
}

                    /* FUNKCE NA KONTROLOVÁNÍ ARGUMENTU */
//kontroluje zda argument obsahuje poze čísla
int kotrolaargumentu(char argument[])
{
    char *p_argument = argument;
    while (*p_argument != '\0')
    {
        if (*p_argument<'0' || *p_argument>'9')
        {
            return 0;
        }
        p_argument++;
    }
    return 1;
}

                    /* FUNKCE ČÍSLO - HLEDANÝ ŘETĚZEC*/
//pokud se čísla shodují, k indexu A se přičte číslo jedna, jestliže se čísla neshodují, porovná se jestli předchozí číslo se stále rovná číslu kontaktu (pokud ano index A se zachová pokud ne index se vynuluje)
//index I slouží pro přechod v číslech telefonního čísla
int ciselna_sekvence(char telefonni_cislo[],char kousek_cisla[])
{
    int a = 0;
    for (int i = 0; i < 99; i++)
    {
        if ((telefonni_cislo[i] == kousek_cisla[a])||(telefonni_cislo[i] == '+'&&kousek_cisla[a]=='0'))
        {   a++;
            if (kousek_cisla[a] == '\0')
                return 1;
        }
        else
        {
            if (kousek_cisla[a-1] != telefonni_cislo[i])
                a = 0; //poznámka: aby algoritmus poznal i sekvenci 112 v hledaném řetězci 11
        }
    }
    return 0;
}
                    /* FUNKCE JMÉNO KONTAKTU - HLEDANÝ ŘETĚZEC */

//jestliže se najde shoda k indexu A se přičte jednička a skončí na písmeno ve jméně kontaktu, jestliže ne index se vynuluje, jestliže znak ulozeny vhledane sekvenci se rovná \0 tak funkce ohlasi ze nasla shodu

int rozpoznani_cisla(char phone_name[],char kousek_cisla[])
{
    int a = 0;
    for (int i = 0;i < 100;i++)
    {
        switch(kousek_cisla[a])
        {
            case '2':
                if (phone_name[i] == 'a'|| phone_name[i] == 'b'|| phone_name[i] =='c')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '3':
                if (phone_name[i] == 'd'|| phone_name[i] == 'e'|| phone_name[i] =='f')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '4':
                if (phone_name[i] == 'g'|| phone_name[i] == 'h'|| phone_name[i]== 'i')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '5':
                if (phone_name[i] == 'j' || phone_name[i] == 'k' || phone_name[i] =='l')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '6':
                if (phone_name[i] == 'm' || phone_name[i] == 'n' || phone_name[i] == 'o')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '7':
                if (phone_name[i] == 'p' || phone_name[i] == 'q' || phone_name[i] =='r'||phone_name[i] =='s')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '8':
                if (phone_name[i] == 't' || phone_name[i] == 'u' || phone_name[i] =='v')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '9':
                if (phone_name[i] == 'w' || phone_name[i] == 'x' || phone_name[i] =='y' || phone_name[i] =='z')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            case '0':
                if (phone_name[i] == '+')
                {
                    a++;
                }
                else
                    a = 0;
                break;
            default:
                break;
        }
        if (kousek_cisla[a] == 0)
            return 1;
    }
    return 0;
}
                /* FUNKCE SPOJUJÍCÍ FUNKCE ČÍSLO-HLEDANÝ ŘETĚZEC A JMÉNO KONTAKTU-HLEDANÝ ŘETĚZEC */

// v případě že jedna z funkcí sekvence a nebo rozpoznani_cisla najde shodu, vyprintuje funkce shoda daný kontakt

int spojka (char polecislo[],char polejmeno[],char argument[])
{
    if (rozpoznani_cisla(polejmeno, argument) || ciselna_sekvence(polecislo, argument))
    {
        printf("%s, %s\n", polejmeno, polecislo);
        return 1;
    }
    return 0;
}

int main(int argc, char * argv[])
{
    //controller hlídá jestli se nějaký kontakt vyprintoval, jestli jeho hodnota na konci se rovná nule vyprintuje se "Not found"
    int controller = 0;

    while (1) {
        char phone_name[102] = {};
        char phone_number[102] = {};

        if (funkcion(phone_name) == 0)
        {
            if(getc(stdin) == EOF)
                if(controller == 0){
                    printf("Not found \n");
                    return 0;
                }
                return 0;
        }
        if (funkcion(phone_number) == 0)
            if(getc(stdin) == EOF)
            {
                if(controller == 0){
                    printf("Not found \n");
                    return 0;
                }
            }
        convertor(phone_name);
        
        if (argc == 2)
        {
            if(kotrolaargumentu(argv[1])==0)
            {
                fprintf(stderr,"error \n");
                return 1;
            }
            controller +=spojka(phone_number, phone_name, argv[1]);
        }
        
        if (argc == 1){
            printf("%s, %s\n",phone_name, phone_number);
            controller++;
        }
        if (argc > 2)
        {
            fprintf(stderr,"error \n");
            return 1;
        }
        
    }
    return 0;
}
