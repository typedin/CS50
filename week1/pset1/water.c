#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // initialize the number of bottles per minute variable
	int bottles_minute = 12;
	
	// prompt the user for the length of his/her shower in minutes
	int user_shower_length;
	
	do
	{
		printf("minutes: ");
		user_shower_length = GetInt();

	} while (!(user_shower_length > 0));
	
	
	// calculation of the number of bottles used by the user
	int user_num_bottles = bottles_minute * user_shower_length;
	
	// print the result to the console
	printf("bottles: %d\n", user_num_bottles);

}