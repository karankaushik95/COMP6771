#include <string>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main()
{
    auto lexicon = GetLexicon("assignments/wl/words.txt");

    std::string source;
    std::string destination;
    while (true)
    {
        std::cout << "Enter start word (RETURN to quit): ";
        getline(std::cin, source);
        if (source.empty())
            break;
        std::cout << "Enter destination word: ";
        getline(std::cin, destination);

        std::vector<std::vector<std::string>> all_paths = FindLadder(lexicon, source, destination);

        if (all_paths.empty())
            std::cout << "No ladder found.\n";
        else
        {
            std::cout << "Found ladder: ";
            for (const auto &ladder : all_paths)
            {
                for (const auto &word : ladder)
                {
                    std::cout << word << " ";
                }
                std::cout << "\n";
            }
        }
    }
}