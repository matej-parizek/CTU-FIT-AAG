#ifndef __PROGTEST__
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
using Symbol = char;
using Word = std::vector<Symbol>;

struct Grammar {
    std::set<Symbol> m_Nonterminals;
    std::set<Symbol> m_Terminals;
    std::vector<std::pair<Symbol, std::vector<Symbol>>> m_Rules;
    Symbol m_InitialSymbol;
};

#endif
struct CYK {
    Grammar grammar;
    std::map<std::pair<int, int>, std::vector<Symbol>> table;

    // constructor that initializes CYK instance with a grammar
    explicit CYK(Grammar  grammar) : grammar(std::move(grammar)) {}

    // function to run the CYK algorithm on a word
    bool run(const Word& word) {
        int n = word.size();

        //initialize the bottom level of the table with the input word
        for(int i = 0; i < n; i++) {
            for(auto rule : grammar.m_Rules) {
                if(rule.second.size() == 1 && rule.second[0] == word[i])
                    table[std::make_pair(i, i)].push_back(rule.first);
            }
        }

        // fill the rest of the table
        for(int l = 2; l <= n; l++) {
            for(int i = 0; i <= n-l; i++) {
                int j = i + l - 1;
                for(int k = i; k <= j-1; k++) {
                    for(auto rule : grammar.m_Rules) {
                        if(rule.second.size() == 2) {
                            auto& B = table[std::make_pair(i, k)];
                            auto& C = table[std::make_pair(k+1, j)];
                            if(std::find(B.begin(), B.end(), rule.second[0]) != B.end() &&
                               std::find(C.begin(), C.end(), rule.second[1]) != C.end())
                                table[std::make_pair(i, j)].push_back(rule.first);
                        }
                    }
                }
            }
        }

        // check if the initial symbol is in the topmost cell of the table
        return std::find(table[std::make_pair(0, n-1)].begin(),
                         table[std::make_pair(0, n-1)].end(),
                         grammar.m_InitialSymbol) != table[std::make_pair(0, n-1)].end();
    }

    std::vector<size_t> backTrace(const Symbol& startSymbol, const Word& word) {
        std::vector<size_t> ruleIndices;
        int n = word.size();

        std::function<void(const Symbol&, int, int)> _backTrace =
                [&] (const Symbol& symbol, int i, int j) {
                    if (i == j) {
                        for (size_t idx = 0; idx < grammar.m_Rules.size(); ++idx) {
                            const auto& rule = grammar.m_Rules[idx];
                            if (rule.first == symbol && rule.second.size() == 1 && rule.second[0] == word[i]) {
                                ruleIndices.insert(ruleIndices.begin(),idx);
                                return;
                            }
                        }
                    }
                    else {
                        for (size_t idx = 0; idx < grammar.m_Rules.size(); ++idx) {
                            const auto& rule = grammar.m_Rules[idx];
                            if (rule.first == symbol && rule.second.size() == 2) {
                                for (int k = i; k < j; ++k) {
                                    if ((std::find(table[std::make_pair(i, k)].begin(),
                                                   table[std::make_pair(i, k)].end(), rule.second[0]) != table[std::make_pair(i, k)].end()) &&
                                        (std::find(table[std::make_pair(k+1, j)].begin(),
                                                   table[std::make_pair(k+1, j)].end(), rule.second[1]) != table[std::make_pair(k+1, j)].end())) {
                                        _backTrace(rule.second[1], k+1, j);
                                        _backTrace(rule.second[0], i, k);
                                        ruleIndices.insert(ruleIndices.begin(),idx);
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
                ;

        _backTrace(startSymbol, 0, n-1);
        return ruleIndices;
    }


    bool isTerminal(const Word& word){
        for(Symbol symbol: word)
            if(grammar.m_Nonterminals.find(symbol)!= grammar.m_Nonterminals.end())
                return false;
        return all_of(word.begin(), word.end(),[this](const Symbol& symbol){
            return this->grammar.m_Nonterminals.find(symbol)== this->grammar.m_Nonterminals.end();
        });

    }
};


size_t emptyGrammar(const Grammar& grammar){
    auto symbol = grammar.m_InitialSymbol;
    for(size_t i=0 ; i<grammar.m_Rules.size(); i++){
        auto rule =grammar.m_Rules.at(i);
        if(rule.first==symbol && rule.second.empty())
            return i;
    }
    return -1;

}

std::vector<size_t> trace(const Grammar& grammar, const Word& word){

    CYK cyk = CYK(grammar);
     auto idx = emptyGrammar(grammar);
    if(word.empty() && (int) idx != -1 )
        return {idx};

    bool able = cyk.run(word);
    if(able) {
        std::vector<size_t> ruleIndices = cyk.backTrace(grammar.m_InitialSymbol, word);
        return ruleIndices;
    }
    return {};
}


#ifndef __PROGTEST__
int main()
{
    Grammar g0{
        {'A', 'B', 'C', 'S'},
        {'a', 'b'},
        {
            {'S', {'A', 'B'}},
            {'S', {'B', 'C'}},
            {'A', {'B', 'A'}},
            {'A', {'a'}},
            {'B', {'C', 'C'}},
            {'B', {'b'}},
            {'C', {'A', 'B'}},
            {'C', {'a'}},
        },
        'S'};

    assert(trace(g0, {'b', 'a', 'a', 'b', 'a'}) == std::vector<size_t>({0, 2, 5, 3, 4, 6, 3, 5, 7}));
    assert(trace(g0, {'b'}) == std::vector<size_t>({}));
    assert(trace(g0, {'a'}) == std::vector<size_t>({}));
    assert(trace(g0, {}) == std::vector<size_t>({}));
    assert(trace(g0, {'a', 'a', 'a', 'a', 'a'}) == std::vector<size_t>({1, 4, 6, 3, 4, 7, 7, 7, 7}));
    assert(trace(g0, {'a', 'b'}) == std::vector<size_t>({0, 3, 5}));
    assert(trace(g0, {'b', 'a'}) == std::vector<size_t>({1, 5, 7}));
    assert(trace(g0, {'c', 'a'}) == std::vector<size_t>({}));

    Grammar g1{
        {'A', 'B'},
        {'x', 'y'},
        {
            {'A', {}},
            {'A', {'x'}},
            {'B', {'x'}},
            {'A', {'B', 'B'}},
            {'B', {'B', 'B'}},
        },
        'A'};

    assert(trace(g1, {}) == std::vector<size_t>({0}));
    assert(trace(g1, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g1, {'x', 'x'}) == std::vector<size_t>({3, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2}));

    Grammar g2{
        {'A', 'B'},
        {'x', 'y'},
        {
            {'A', {'x'}},
            {'B', {'x'}},
            {'A', {'B', 'B'}},
            {'B', {'B', 'B'}},
        },
        'B'};

    assert(trace(g2, {}) == std::vector<size_t>({}));
    assert(trace(g2, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g2, {'x', 'x'}) == std::vector<size_t>({3, 1, 1}));
    assert(trace(g2, {'x', 'x', 'x'}) == std::vector<size_t>({3, 3, 1, 1, 1}));

    Grammar g3{
        {'A', 'B', 'C', 'D', 'E', 'S'},
        {'a', 'b'},
        {
            {'S', {'A', 'B'}},
            {'S', {'S', 'S'}},
            {'S', {'a'}},
            {'A', {'B', 'S'}},
            {'A', {'C', 'D'}},
            {'A', {'b'}},
            {'B', {'D', 'D'}},
            {'B', {'b'}},
            {'C', {'D', 'E'}},
            {'C', {'b'}},
            {'C', {'a'}},
            {'D', {'a'}},
            {'E', {'S', 'S'}},
        },
        'S'};

    assert(trace(g3, {}) == std::vector<size_t>({}));
    assert(trace(g3, {'b'}) == std::vector<size_t>({}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b'}) == std::vector<size_t>({1, 2, 0, 3, 7, 1, 2, 2, 7}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'a'}) == std::vector<size_t>({1, 1, 0, 4, 8, 11, 12, 0, 5, 6, 11, 11, 0, 4, 9, 11, 7, 11, 7, 2, 2}));
}
#endif

