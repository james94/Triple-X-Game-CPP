#include <ctime>
#include <string>
#include <iostream>

class Player {
    std::string Name;
    int Guess;

public:
    Player()
    {
        Name = "";
    }

    Player(std::string FullName)
    {
        Name = FullName;
    }

    void EnterName() {
        std::getline(std::cin, Name);
    }

    std::string GetName()
    {
        return Name;
    }

    int GuessCode()
    {
        std::cin >> Guess;
        return Guess;
    }
};

class TripleX {
    int Difficulty;
    const int MaxDifficulty;
    bool LevelComplete;
    Player *tripleXPlayer;

    void PrintStory()
    {
        std::cout << "\n\nHello " + tripleXPlayer->GetName();
        std::cout << "\nYou are a secret agent breaking into a level " << Difficulty;
        std::cout << " secure server room...\nYou need to enter the correct codes to continue...\n\n";
    }

    const int GenerateCode()
    {
        return rand() % Difficulty + Difficulty;
    }

    const int CalcCodeSum(const int CodeA, const int CodeB, const int CodeC)
    {
        return CodeA + CodeB + CodeC;
    }

    const int CalcCodeProduct(const int CodeA, const int CodeB, const int CodeC)
    {
        return CodeA * CodeB * CodeC;
    }

    void PrintExpResult(const int CodeSum, const int CodeProduct)
    {
        std::cout << "+ There are 3 numbers in the code\n";
        std::cout << "+ The codes add-up to: " << CodeSum << "\n";
        std::cout << "+ The codes multiply to give: " << CodeProduct << "\n";
    }

    bool isLevelCompleted(const int GuessSum, const int ExpCodeSum, const int GuessProduct, const int ExpCodeProduct)
    {
        if(GuessSum == ExpCodeSum && GuessProduct == ExpCodeProduct)
        {
            std::cout << "\n*** Well done agent! You have extracted a file! Keep going! ***";
            return true;
        }
        else
        {
            std::cout << "\n*** You entered the wrong code! Careful agent! Try again! ***";
            return false;
        }
    }

    bool PlayGame()
    {
        PrintStory();

        const int CodeA = GenerateCode();
        const int CodeB = GenerateCode();
        const int CodeC = GenerateCode();

        const int ExpCodeSum = CalcCodeSum(CodeA, CodeB, CodeC);
        const int ExpCodeProduct = CalcCodeProduct(CodeA, CodeB, CodeC);

        // Print CodeSum and CodeProduct to the terminal
        PrintExpResult(ExpCodeSum, ExpCodeProduct);

        // Store Player Guess
        const int GuessA = tripleXPlayer->GuessCode();
        const int GuessB = tripleXPlayer->GuessCode();
        const int GuessC = tripleXPlayer->GuessCode();

        const int GuessSum = CalcCodeSum(GuessA, GuessB, GuessC);
        const int GuessProduct = CalcCodeProduct(GuessA, GuessB, GuessC);

        // Check if the players guess is correct
        return isLevelCompleted(GuessSum, ExpCodeSum, GuessProduct, ExpCodeProduct);
    }

public:
    TripleX(int LevelDifficulty, const int MaxLevelDifficulty, Player *player) : 
        Difficulty(LevelDifficulty), MaxDifficulty(MaxLevelDifficulty), tripleXPlayer(player){}

    void run()
    {
        std::cout << "Welcome to TripleX" << std::endl;
        std::cout << "Enter your name to begin" << std::endl;
        tripleXPlayer->EnterName();
        srand(time(NULL)); // create new random sequence based on time of day
        while(Difficulty <= MaxDifficulty) // Loop game until all levels are completed
        {
            LevelComplete = PlayGame();
            std::cin.clear();
            std::cin.ignore();

            if(LevelComplete)
            {
                ++Difficulty;
            }
        }
        std::cout << "\n*** Great work agent! You got all the files! Now get out of there! ***\n";
    }
};

int main()
{
    Player gamePlayer;
    TripleX game(1, 5, &gamePlayer);

    game.run();

    return 0;
}