#include "stdafx.h"
#include "ChainGrammar.h"


void sort(vector<string> v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[j].length() > v[j - 1].length())
            {
                string tmp = v[j];
                v[j] = v[j - 1];
                v[j - 1] = tmp;
            }
        }
    }
}


ChainGrammar::ChainGrammar(vector<string> chains)
{
    sort(chains);
    BuildNonRecursive(chains);
    RemoveResidualNonTerminals();
    SimplyfyGrammar();
}


ChainGrammar::~ChainGrammar()
{

}


set<string> ChainGrammar::GenerateRandomChains(int n)
{
    set<string> randomChains;
    while (randomChains.size() < n)
    {
        auto chain = dynamic_pointer_cast<NonTerm>(_startSymbol)->GetRandomChain();
        if (randomChains.find(chain) == randomChains.end())
        {
            randomChains.insert(chain);
        }
    }
    return randomChains;
}


void ChainGrammar::BuildNonRecursive(vector<string> chains)
{
    int maxLen = chains[0].length();
    for each(string chain in chains)
    {
        AddChainToGrammar(chain, maxLen == chain.length());
    }
}


void ChainGrammar::RemoveResidualNonTerminals()
{

}


void ChainGrammar::SimplyfyGrammar()
{
    /*auto p = dynamic_pointer_cast<NonTerm>(_startSymbol);
    auto A1 = dynamic_pointer_cast<NonTerm>(p->GetDisclosures()[0].second);
    A1->GetDisclosures()[0].second = NonTerm::Ptr(A1.get(), [](NonTerm*) {});*/
    vector<NonTerm*> v;
    for each(char termVal in _termValues)
    {
        v.clear();
        dynamic_pointer_cast<NonTerm>(_startSymbol)->GetNonTermsWithDisclosureToTerm(termVal, v);
        if (v.size() > 1)
        {
            for (int i = 0; i < v.size(); i++)
            {
                for (int j = i + 1; j < v.size(); )
                {
                    if (v[i]->EqualTo(v[j]))
                    {
                        dynamic_pointer_cast<NonTerm>(_startSymbol)->ReplaceNonTermWith(v[j], v[i]);
                        v.erase(find(v.begin(), v.end(), v[j]));
                    }
                    else
                    {
                        j++;
                    }
                }
            }
        }
    }
}


void ChainGrammar::NonTerm::GetNonTermsWithDisclosureToTerm(const char term, vector<NonTerm*> &v)
{
    if (HasDisclosureToTerm(term))
    {
        v.push_back(this);
    }
    for each(Disclosure disclosure in _disclosures)
    {
        if (nullptr != disclosure.second &&
            !disclosure.second->IsTerm() &&
            disclosure.second.get() != this &&
            find(v.begin(), v.end(), disclosure.second.get()) == v.end())
        {
            dynamic_pointer_cast<NonTerm>(disclosure.second)->GetNonTermsWithDisclosureToTerm(term, v);
        }
    }
}


void ChainGrammar::AddChainToGrammar(string chain, bool maxLenChain/* = false*/)
{
    if (maxLenChain)
    {
        AddMaxLenChain(chain);
    }
    else
    {
        int chainLen = chain.length();
        Symbol::Disclosure disclosure;
        Symbol::Ptr currentSymbol = _startSymbol;
        for (int i = 0; i < chainLen; i++)
        {
            bool lastTerm = chainLen - 1 == i;
            Symbol::Disclosure* pSatisfyingDisclosure;
            if (pSatisfyingDisclosure = dynamic_pointer_cast<NonTerm>(currentSymbol)->GetSatisfyingDisclosure(chain[i], lastTerm))
            {
                currentSymbol = pSatisfyingDisclosure->second;
            }
            else
            {
                disclosure = AddDisclosureToNonTerm(dynamic_pointer_cast<NonTerm>(currentSymbol), chain, i);
                currentSymbol = disclosure.second;
            }
        }
    }
}


void ChainGrammar::AddMaxLenChain(string chain)
{
    if (nullptr == _startSymbol)
    {
        _startSymbol = Symbol::Ptr(new NonTerm());
    }
    Symbol::Disclosure disclosure;
    Symbol::Ptr currentSymbol = _startSymbol;
    int chainLen = chain.length();
    for (int i = 0; i < chainLen - 2; i++)
    {
        disclosure = AddDisclosureToNonTerm(dynamic_pointer_cast<NonTerm>(currentSymbol), chain, i);
        currentSymbol = disclosure.second;
    }
    AddResidualDisclosureToNonTerm(dynamic_pointer_cast<NonTerm>(currentSymbol), chain[chainLen - 2], chain[chainLen - 1]);
}


ChainGrammar::Symbol::Disclosure ChainGrammar::AddDisclosureToNonTerm(ChainGrammar::NonTerm::Ptr symbol, const string& chain, int termIndex)
{
    ChainGrammar::Symbol::Disclosure newDisclosure;
    CheckNewTerm(chain[termIndex]);
    newDisclosure.first = Symbol::Ptr(new Term(chain[termIndex]));
    if (chain.length() - 1 == termIndex)
    {
        newDisclosure.second = nullptr;
    }
    else
    {
        newDisclosure.second = Symbol::Ptr(new NonTerm());
    }
    symbol->AddDisclosure(newDisclosure);
    return newDisclosure;
}


void ChainGrammar::CheckNewTerm(char term)
{
    if (find(_termValues.begin(), _termValues.end(), term) == _termValues.end())
    {
        _termValues.push_back(term);
    }
}


ChainGrammar::Symbol::Disclosure ChainGrammar::AddResidualDisclosureToNonTerm(ChainGrammar::NonTerm::Ptr symbol, char t1, char t2)
{
    ChainGrammar::Symbol::Disclosure newDisclosure;
    CheckNewTerm(t1);
    CheckNewTerm(t2);
    newDisclosure.first = Symbol::Ptr(new Term(t1));
    newDisclosure.second = Symbol::Ptr(new Term(t2));
    symbol->AddDisclosure(newDisclosure);
    return newDisclosure;
}


string ChainGrammar::NonTerm::GetRandomChain()
{
    int r = rand() % _disclosures.size();
    string term = string(1, dynamic_pointer_cast<ChainGrammar::Term>(_disclosures[r].first)->GetValue());
    if (nullptr == _disclosures[r].second)
    {
        return term;
    }
    else
    {
        if (_disclosures[r].second->IsTerm())
        {
            return term + string(1, dynamic_pointer_cast<ChainGrammar::Term>(_disclosures[r].second)->GetValue());
        }
        else
        {
            return term + dynamic_pointer_cast<ChainGrammar::NonTerm>(_disclosures[r].second)->GetRandomChain();
        }
    }
}


ChainGrammar::Symbol::Disclosure* ChainGrammar::NonTerm::GetRandomDisclosure()
{
    return &_disclosures[rand() % _disclosures.size()];
}


ChainGrammar::Symbol::Disclosure* ChainGrammar::NonTerm::GetSatisfyingDisclosure(const char term, bool last/* = false*/)
{
    for(int i = 0; i < _disclosures.size(); i++)
    {
        if (term == dynamic_pointer_cast<Term>(_disclosures[i].first)->GetValue())
        {
            if (!last || (last && nullptr == _disclosures[i].second))
            {
                return &_disclosures[i];
            }
        }
    }
    return nullptr;
}


bool ChainGrammar::NonTerm::HasDisclosureToTerm(const char term, bool last/* = false*/)
{
    for (int i = 0; i < _disclosures.size(); i++)
    {
        if (_disclosures[i].first->IsTerm() &&
            term == dynamic_pointer_cast<Term>(_disclosures[i].first)->GetValue())
        {
            return last ? nullptr == _disclosures[i].second : true;
        }
    }
    return false;
}


void ChainGrammar::NonTerm::AddDisclosure(ChainGrammar::Symbol::Disclosure newDiscloser)
{
    if (find(_disclosures.begin(), _disclosures.end(), newDiscloser) == _disclosures.end())
    {
        _disclosures.push_back(newDiscloser);
    }
}


void ChainGrammar::NonTerm::AddRecursiveToDiclosureStartingWith(const char term)
{
    Disclosure recDisclosure;
    recDisclosure.first = Symbol::Ptr(new Term(term));
    recDisclosure.second = Symbol::Ptr(this);
    _disclosures.push_back(recDisclosure);
}


bool ChainGrammar::NonTerm::IsResidual()
{
    for each(Disclosure disclos in _disclosures)
    {
        if (disclos.first->IsTerm() && nullptr != disclos.second && disclos.second->IsTerm())
        {
            return true;
        }
    }
    return false;
}


vector<ChainGrammar::Symbol::Disclosure> ChainGrammar::NonTerm::GetDisclosures() const
{
    return _disclosures;
}


bool NonTerminalsDisclosuresEqual(const ChainGrammar::Symbol::Disclosure& a, const ChainGrammar::Symbol::Disclosure& b, const ChainGrammar::NonTerm* nonTermA, const ChainGrammar::NonTerm* nonTermB)
{
    if (a.first->IsTerm() == b.first->IsTerm())
    {
        if (dynamic_pointer_cast<ChainGrammar::Term>(a.first)->GetValue() == dynamic_pointer_cast<ChainGrammar::Term>(b.first)->GetValue())
        {
            if (nullptr == a.second && nullptr == b.second)
            {
                return true;
            }
            else
            {
                if (a.second->IsTerm() == b.second->IsTerm())
                {
                    if (a.second == b.second || 
                       (a.second.get() == nonTermA && b.second.get() == nonTermB) ||
                       (a.second.get() == nonTermB && b.second.get() == nonTermA))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void ChainGrammar::NonTerm::ReplaceNonTermWith(ChainGrammar::NonTerm* src, ChainGrammar::NonTerm* dest)
{
    for (int i = 0; i < _disclosures.size(); i++)
    {
        if (nullptr != _disclosures[i].second)
        {
            if (_disclosures[i].second.get() == src)
            {
                _disclosures[i].second.reset(dest, [](NonTerm*) {});
            }
            else
            {
                if (this != _disclosures[i].second.get())
                {
                    dynamic_pointer_cast<ChainGrammar::NonTerm>(_disclosures[i].second)->ReplaceNonTermWith(src, dest);
                }
            }
        }
    }
}