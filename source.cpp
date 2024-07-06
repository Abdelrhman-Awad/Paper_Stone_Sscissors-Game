#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enGameChoice
{
    Stone = 1,
    Paper = 2,
    Scissors = 3
};

enum enWinner
{
    Player1 = 1,
    Computer = 2,
    Draw = 3
};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
    string Player1ChoiceName;
    string ComputerChoiceName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1Wins = 0;
    short ComputerWins = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName;
};

int RandomNumber(int From, int To)
{
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

short HowManyRound()
{
    short Round = 1;
    do
    {
        cout << "How Many Rounds 1 to 10\n";
        cin >> Round;
    } while (Round < 1 || Round > 10);

    return Round;
}

enGameChoice ReadPlayer1Choice()
{
    short Choice = 0;
    do
    {
        cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner Winner(stRoundInfo Round)
{
    if (Round.Player1Choice == Round.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (Round.Player1Choice)
    {
    case enGameChoice::Paper:
        if (Round.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (Round.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Stone:
        if (Round.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{
    string ArrGameChoices[3] = {"Stone", "Paper", "Scissors"};
    return ArrGameChoices[(int)Choice - 1];
}

string WinnerName(enWinner Winner)
{

    string WinnerName[3] = {"Player1", "Computer", "Draw"};
    return WinnerName[(int)Winner - 1];
}

enWinner GameWinner(short PlayerWinTimes, short computerWinTimes)
{
    if (PlayerWinTimes > computerWinTimes)
        return enWinner::Player1;
    else if (computerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string Tabs(short NumberOfTab)
{
    string T = "";
    for (int i = 1; i <= NumberOfTab; i++)
    {
        T += "\t";
    }
    return T;
}

void SetWinnerScreenColor(enWinner Winner)
{

    if (Winner == enWinner::Player1)
    {

        system("COLOR 2F");
    }
    else if (Winner == enWinner::Computer)
    {
        system("COLOR 4F");
        cout << "\a";
    }
    else
    {
        system("COLOR 6F");
    }
}

void ShowRoundResult(stRoundInfo Round)
{
    cout << "________________Round [" << Round.RoundNumber << "]________________\n\n";
    cout << "Player1  Choice: " << Round.Player1ChoiceName << endl;
    cout << "Computer Choice: " << Round.ComputerChoiceName << endl;
    cout << "Round Winner   : [" << Round.WinnerName << "]" << endl;
    cout << "__________________________________________\n\n";
    SetWinnerScreenColor(Round.Winner);
}

void PrintGameOverScreen()
{

    cout << Tabs(3) << "___________________________________________\n\n";
    cout << Tabs(4) << "+++ G a m e O v e r +++\n\n";
    cout << Tabs(3) << "___________________________________________\n\n";
}

stGameResults FillGameResults(short RoundsNumber, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.ComputerWins = ComputerWinTimes;
    GameResults.Player1Wins = Player1WinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameRounds = RoundsNumber;
    GameResults.GameWinner = GameWinner(GameResults.Player1Wins, GameResults.ComputerWins);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo Round;
    // short Rounds = HowManyRound();
    short ComputerWinsTimes = 0, Player1WinsTimes = 0, DrawTimes = 0;
    for (int RoundNumber = 1; RoundNumber <= HowManyRounds; RoundNumber++)
    {
        Round.RoundNumber = RoundNumber;
        Round.Player1Choice = ReadPlayer1Choice();
        Round.Player1ChoiceName = ChoiceName(Round.Player1Choice);
        Round.ComputerChoice = GetComputerChoice();
        Round.ComputerChoiceName = ChoiceName(Round.ComputerChoice);
        Round.Winner = Winner(Round);
        Round.WinnerName = WinnerName(Round.Winner);

        if (Round.Winner == enWinner::Player1)
        {
            Player1WinsTimes++;
        }
        else if (Round.Winner == enWinner::Computer)
        {
            ComputerWinsTimes++;
        }
        else
        {
            DrawTimes++;
        }
        ShowRoundResult(Round);
    }
    return FillGameResults(Round.RoundNumber, Player1WinsTimes, ComputerWinsTimes, DrawTimes);
}

void PrintGameResults(stGameResults GameResults)
{
    cout << Tabs(3) << "_____________ [ Game Results ]_____________\n\n";
    cout << Tabs(3) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(3) << "Player1 won times  : " << GameResults.Player1Wins << endl;
    cout << Tabs(3) << "Computer won times : " << GameResults.ComputerWins << endl;
    cout << Tabs(3) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(3) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(3) << "___________________________________________\n\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}

void ResetScreen()
{
    system("cls");
    system("COLOR 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(HowManyRound());
        PrintGameOverScreen();
        PrintGameResults(GameResults);
        SetWinnerScreenColor(GameResults.GameWinner);

        cout << Tabs(3) << "Do You want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{

    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}