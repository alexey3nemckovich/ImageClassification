#pragma once
#include <vector>
#include <set>
#include <memory>
#include <string>
#include <deque>
#include <functional>
using namespace std;


class ChainGrammar
{
public:
    ///grammar symbols
    class Symbol
    {
    public:
        Symbol() = default;
        virtual ~Symbol() = default;
        typedef shared_ptr<Symbol> Ptr;
        typedef pair<Ptr, Ptr> Disclosuer;
        virtual bool IsTerm() const = 0;
    };
    class Term
        : public Symbol
    {
    public:
        typedef shared_ptr<Term> Ptr;
        Term(char value) : Symbol()
        {
            this->_val = value;
        }
        virtual ~Term() = default;
        char GetValue() { return _val; }
        virtual bool IsTerm() const override{ return true; }
    private:
        char _val;
    };
    class NonTerm
        : public Symbol
    {
    public:
        //main interface
        NonTerm() = default;
        virtual ~NonTerm()/* = default;*/
        {
            __noop();
        }
        typedef shared_ptr<NonTerm> Ptr;
        typedef function<bool(NonTerm*)> SearchCondition;
        string GetRandomChain();
    public:
        //getters
        Disclosuer* GetRandomDisclosuer();
        vector<Disclosuer> GetDisclosuers() const;
        Disclosuer* GetSatisfyingDisclosuer(const char, bool last = false);
        void GetNonTermsWithCondition(vector<NonTerm*>&, SearchCondition condition, deque<NonTerm*> stack = deque<NonTerm*>());
    public:
        //info
        bool IsResidual() const;
        bool HasDisclosuerToTerm(const char, bool = false) const;
        virtual bool IsTerm() const override { return false; }
        bool EqualTo(const NonTerm* other) const;
    public:
        void ReplaceNonTermWith(NonTerm *src, NonTerm *dest, deque<NonTerm*> stack = deque<NonTerm*>());
        void AddRecursiveToDiclosureStartingWith(const char);
        void AddDisclosuer(Disclosuer);
        friend bool NonTerminalsDisclosuersEqual(const Disclosuer& a, const Disclosuer& b, const NonTerm* nonTermA, const NonTerm* nonTermB);
    protected:
        vector<Disclosuer> _disclosuers;
    };
    class ResidualNonTerm
        : public NonTerm
    {
    public:
        ResidualNonTerm(char t1, char t2)
        {
            AddDisclosuer(Disclosuer(new Term(t1), new Term(t2)));
        }
        pair<char, char> GetResidualTermsValues()
        {
            pair<char, char> res;
            for each(NonTerm::Disclosuer disc in _disclosuers)
            {
                if (nullptr != disc.second)
                {
                    res.first = dynamic_pointer_cast<Term>(disc.first)->GetValue();
                    res.second = dynamic_pointer_cast<Term>(disc.second)->GetValue();
                }
            }
            return res;
        }
    };
    ///
    ChainGrammar(vector<string> chains);
    set<string> GenerateRandomChains(int n);
    ~ChainGrammar();
private://methods
    //FIRST step
    void BuildNonRecursive(vector<string> chains);
    void AddChainToGrammar(string chain, bool maxLenChain = false);
    void AddMaxLenChain(string chain);
    //SECOND step
    void RemoveResidualNonTerminals();
    //THIRD step
    void SimplyfyGrammar();
    //support functions
    void RemoveEqualNonTerminals(vector<NonTerm*>&);
    Symbol::Disclosuer AddDisclosuerToNonTerm(NonTerm::Ptr symbol, char term, char t1, char t2);
    Symbol::Disclosuer AddDisclosuerToNonTerm(NonTerm::Ptr symbol, char term, bool lastTerm);
    void CheckNewTerm(char term);
private://members
    NonTerm::Ptr _startSymbol;
    vector<char> _termValues;
    const NonTerm::SearchCondition residualSearchCond = [](NonTerm* nonTerm)-> bool {return nonTerm->IsResidual(); };
};