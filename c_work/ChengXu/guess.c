#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 100

int sercret_number;

void initialize_number_generator(void);
void choose_new_secret_number(void);
void read_guesses(void);

int main(void)
{
    char command;
    printf("Guess the sercret number between 1 and %d.\n\n", MAX_NUMBER);
    initialize_number_generator();
    do {
        choose_new_secret_number();
        printf("A new number has been chosen.\n");
        read_guesses();
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

void choose_new_secret_number(void)
{
    sercret_number = rand() % MAX_NUMBER + 1;
}

void read_guesses(void)
{
    int guess, num_guesses = 0;

    for (;;) {
        num_guesses++;
        printf("Enter guess: ");
        scanf("%d", &guess);
        if (guess == sercret_number) {
            printf("You won in %d guesses!\n\n", num_guesses);
            return;   // <-- 死循环用return退出
        }
        else if (guess < sercret_number) printf("Too low; try agian.\n");
        else printf("Too high; try again.\n");
    }
}