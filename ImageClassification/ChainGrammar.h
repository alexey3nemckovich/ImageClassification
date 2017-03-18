#pragma once
#include <vector>
#include <set>
#include <memory>
#include <string>
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
        typedef pair<Ptr, Ptr> Disclosure;
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
        NonTerm() = default;
        virtual ~NonTerm()/* = default;*/
        {
            __noop();
        }
        typedef shared_ptr<NonTerm> Ptr;
        string GetRandomChain();
        vector<Disclosure> GetDisclosures() const;
        Disclosure* GetRandomDisclosure();
        Disclosure* GetSatisfyingDisclosure(const char, bool last = false);
        void GetNonTermsWithDisclosureToTerm(const char, vector<NonTerm*>&);
        void ReplaceNonTermWith(NonTerm *src, NonTerm *dest);
        void RemoveResidualNonTerminals();
        void AddRecursiveToDiclosureStartingWith(const char);
        void AddDisclosure(Disclosure);
        bool IsResidual();
        bool HasDisclosureToTerm(const char, bool = false);
        virtual bool IsTerm() const override { return false; }
        bool EqualTo(const NonTerm* other) const
        {
            vector<Disclosure> otherDisclousers = other->GetDisclosures();
            if (_disclosures.size() == otherDisclousers.size())
            {
                for (int i = 0; i < _disclosures.size(); i++)
                {
                    if (!NonTerminalsDisclosuresEqual(_disclosures[i], otherDisclousers[i], this, other))
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        friend bool NonTerminalsDisclosuresEqual(const Disclosure& a, const Disclosure& b, const NonTerm* nonTermA, const NonTerm* nonTermB);
    private:
        vector<Disclosure> _disclosures;
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
    //THIRD step
    void SimplyfyGrammar();
    //support functions
    Symbol::Disclosure AddDisclosureToNonTerm(NonTerm::Ptr symbol, const string& chain, int termIndex);
    Symbol::Disclosure AddResidualDisclosureToNonTerm(NonTerm::Ptr symbol, char t1, char t2);
    void CheckNewTerm(char term);
private://members
    Symbol::Ptr _startSymbol;
    vector<char> _termValues;
};