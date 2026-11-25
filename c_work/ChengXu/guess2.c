#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 100


void initialize_number_generator(void);
int choose_new_secret_number(void);
void read_guesses(int);

int main(void)
{
    char command;
    printf("Guess the sercret number between 1 and %d.\n\n", MAX_NUMBER);
    initialize_number_generator();
    do {
        int num = choose_new_secret_number();
        printf("A new number has been chosen.\n");
        read_guesses(num);
        printf("Play again? (Y/N) ");
        scanf(" %c", &command);   // <-- %c前面一定要有空格
        printf("\n");
    } while (command == 'y' || command == 'Y');

    return 0;
}
void initialize_number_generator(void)
{
    srand((unsigned) time(NULL));
}

int choose_new_secret_number(void)
{
    return rand() % MAX_NUMBER + 1;
}

void read_guesses(int num)
{
    int guess, num_guesses = 0;

    for (;;) {
        num_guesses++;
        printf("Enter guess: ");
        scanf("%d", &guess);
        if (guess == num) {
            printf("You won in %d guesses!\n\n", num_guesses);
            return;
        }
        else if (guess < num) printf("Too low; try agian.\n");
        else printf("Too high; try again.\n");
    }
}