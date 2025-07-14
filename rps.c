#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COMPUTER_WIN 02
#define PLAYER_WIN 01
#define TIE 00

#define computer_choice() ((unsigned int) rand() % 3)

unsigned int parse_user_input(char *p);
unsigned int battle_logic(unsigned int c, unsigned int p);

struct packed_choices {
    unsigned int playerChoice : 02;
    unsigned int computerChoice : 02;
};

int playerScore = 0;
int computerScore = 0;

int main() {
    time_t sysTime = time(0);
    srand(sysTime);
    printf("Rock Paper Scissors\n");
    char playerChoice;
    while(1 == 1) {
        printf("\n Computer: %d Player: %d\n", computerScore, playerScore);
        printf("\n------------------------\n");
        printf("Rock, Paper, Scissors? ");
        scanf(" %c", &playerChoice);
        unsigned int score =  battle_logic(computer_choice(), parse_user_input(&playerChoice));
        playerScore += score & 01;
        computerScore += score >> 1; 
    }
}

unsigned int parse_user_input(char *userInput) {
    if (*userInput == 'r') return 0;
    if (*userInput == 'p') return 1;
    if (*userInput == 's') return 2;
    return 4;
}

unsigned int battle_logic(unsigned int computer, unsigned int player) {
    if (player >> 2) {
        printf("\nnot a move\n");
        return TIE;
    }
    printf("\nComputer Chose ");
    switch (computer) {
        case 0: 
            printf("Rock\n");
            break;
        case 1: 
            printf("Paper\n");
            break;
        case 2: 
            printf("Scissors\n");
            break;
        default:
            break;
    }
    if (computer == player) return TIE;
    
    struct packed_choices choices;
    memset(&choices, 0, sizeof(choices));
    choices.playerChoice = player;
    choices.computerChoice = computer;
    uint8_t choices_int = *(uint8_t *)&choices; 
    if (choices_int == 1 || choices_int == 6 || choices_int == 8) {
        printf("YOU WIN !!!\n");
        return PLAYER_WIN;
    }
    printf("YOU LOSE :( \n");
    return COMPUTER_WIN;
}
