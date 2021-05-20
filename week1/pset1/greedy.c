#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

int main()
{
    
    float user_input;
    
    do
    {
        printf("O hai! How much change is owed?\n");
        user_input = GetFloat();
    } while (user_input < 0);
    
    /*
    *   first round the user input
    *   then convert to cents (multiply by 100)
    */
    
    int owed_sum = round(user_input * 100);
    
    // find the number of quarters
    int reminder = owed_sum % QUARTER;
    int nb_quarters = (owed_sum - reminder)/QUARTER;
    
    //  find the number of dimes
    owed_sum = reminder;
    reminder = owed_sum % DIME;
    int nb_dimes = (owed_sum - reminder)/DIME;
    
    //  find the number of nickels
    owed_sum = reminder;
    reminder = owed_sum % NICKEL;
    int nb_nickels = (owed_sum -reminder)/NICKEL;
    
    //  find the number of pennies
    owed_sum = reminder;
    reminder = owed_sum % PENNY;
    int nb_pennies = (owed_sum-reminder)/PENNY;
    
    //  output the minimum amount of coins
    int nb_coins = nb_quarters + nb_dimes + nb_nickels + nb_pennies;
    printf("%d\n", nb_coins);
    
}