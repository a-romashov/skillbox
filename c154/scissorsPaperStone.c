#include "stdio.h"
#include "scissorsPaperStone.h"
#include "../lib/SafeInput/SafeInput.h"

enum {
    CommandPlayGame = 1,
    CommandExit
};
typedef enum {
    Paper = 1,
    Scissors,
    Stone
} choice;

static char* choiceNames[4] = {"", "Paper", "Scissors", "Stone"};

char* choiceTitle(const choice c) {
    return choiceNames[c];
}

int areYaWinningSon(const choice computer, const choice player) {
    if (player == Paper) {
        return computer == Stone;
    }
    if (player == Stone) {
        return computer == Scissors;
    }
    return computer == Paper;
}

choice getComputerChoice(const choice playerChoice) {
    return (choice) (((int)playerChoice) % 3 + 1);
}

choice getPlayerChoice() {
    int result;

    again:
    printf("Enter your choice:\n");
    printf("%d) %s\n", Paper, choiceTitle(Paper));
    printf("%d) %s\n", Scissors, choiceTitle(Scissors));
    printf("%d) %s\n", Stone, choiceTitle(Stone));
    scanInteger("%d", &result, "wrong value, type again\n");
    if (result < 1 || result > 3) {
        goto again;
    }
    return (choice) result;
}

void playGame(const unsigned int wins) {
    unsigned short int computerWins = 0;
    unsigned short int playerWins = 0;
    //первой показываем бумагу
    choice computerChoice = Paper;
    choice playerChoice;

    while ((playerWins < wins) && (computerWins < wins)) {
        playerChoice = getPlayerChoice();

        printf("Your choice is %s\n", choiceTitle(playerChoice));
        printf("Computer choice is %s\n", choiceTitle(computerChoice));
        if (playerChoice == computerChoice) {
            //если ничья, то меняем значение на то которое побьет наш последний выбор
            computerChoice = getComputerChoice(computerChoice);
            printf("draw\n");
            continue;
        }
        if (areYaWinningSon(computerChoice, playerChoice)) {
            playerWins++;
            printf("you win\n");
            //если поражение, то меняем значение на то которое побьет выбор противника
            computerChoice = getComputerChoice(playerChoice);
        } else {
            printf("computer win\n");
            //затем если победное значение, его же и оставляем
            computerWins++;
        }

        printf("---------------\nSCORE\nCOMPUTER: %d PLAYER: %d\n\n", computerWins, playerWins);
    }
    if (computerWins > playerWins) {
        printf("Amazed by your failure. Next time...\n");
    } else {
        printf("Congratulation, you are win nothing.\n");
    }
}

int command(const unsigned int wins) {
    int command;
    menu:
    printf("ENTER MENU ITEM INDEX\n%d) %s\n%d) %s\n", CommandPlayGame, "NEW GAME", CommandExit, "EXIT");
    scanInteger("%d", &command, "wrong value, try again\n");
    switch (command) {
        case CommandPlayGame:
            playGame(wins);
            return 1;
        case CommandExit:
            printf("Goodbye!");
            return 0;
        default:
            printf("enter a valid menu item index\n");
            goto menu;
    }
}

void startGame(unsigned int wins) {
    while (command(wins));
}