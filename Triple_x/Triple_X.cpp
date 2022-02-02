#include <iostream>
#include <ctime>

void PrintIntroduction(int LevelDifficulty)
{
    std::cout << "\n\nNew Level Started, Difficulty " << LevelDifficulty << "\n";
    std::cout << "Enter the correct code to continue\n\n";
}

bool PlayGame(int LevelDifficulty)
{
    PrintIntroduction(LevelDifficulty);

    const int A = rand() % LevelDifficulty + LevelDifficulty;
    const int B = rand() % LevelDifficulty + LevelDifficulty;
    const int C = rand() % LevelDifficulty + LevelDifficulty;

    /*
    */
    int Sum = A + B + C;
    float Product = (float) A * B * C;

    std::cout << "Code contain 3 numbers";
    std::cout << "\nSum of 3 numbers: " << Sum;
    std::cout << "\nProduct of 3 numbers: " << Product;
    
    int GuessA, GuessB, GuessC;

    std::cout << "\nEnter your code: ";
    std::cin >> GuessA >> GuessB >> GuessC;

    std::cout << "\nYour guess is: " << GuessA << GuessB << GuessC;
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    if (GuessSum == Sum && GuessProduct == Product)
    {
        std::cout << "\nYou win!";
        return true;
    }
    else
    {
        std::cout << "\nYou lose!";
        return false;
    }
}

int main()
{
    srand(time(NULL));

    int LevelDifficulty = 1;
    int const MaxDifficulty = 5;

    while (LevelDifficulty <= MaxDifficulty) 
    {
        bool LevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear();
        std::cin.ignore();

        if (LevelComplete) {
            ++LevelDifficulty;
        }
    }

    return 0;
}