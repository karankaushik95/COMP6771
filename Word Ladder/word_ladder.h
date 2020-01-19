#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <algorithm>
#include <deque>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Dictionary will contain all the words that are one letter different from a given word
using Dictionary = std::unordered_map<std::string, std::vector<std::string>>;
// Lexicon is just a namespace for the input words.txt file
using Lexicon = std::unordered_set<std::string>;

void GetWordCombinations(const Lexicon &, const std::string &, Dictionary &, std::deque<std::string> &);

std::vector<std::vector<std::string>>
FindLadder(const Lexicon &, const std::string &, const std::string &);

std::unordered_map<std::string, int>
BreadthFirstFind(const Dictionary &, const std::string &, const std::string &);

void DepthFirstFind(const std::string &,
                    const std::string &,
                    const Dictionary &,
                    const std::unordered_map<std::string, int> &,
                    std::vector<std::vector<std::string>> &,
                    std::vector<std::string>);

#endif // ASSIGNMENTS_WL_WORD_LADDER_H_