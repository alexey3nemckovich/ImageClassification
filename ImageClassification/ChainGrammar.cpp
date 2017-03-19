#include "stdafx.h"
#include "ChainGrammar.h"


void sort(vector<string> &v)
{
    for (int i = v.size() - 1; i > 0; i--)
    {
        for (int j = i; j > 0; j--)
        {
            if (v[j].length() > v[j-1].length())
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
    srand(time(NULL));
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
    vector<NonTerm*> residuals;
    _startSymbol->GetNonTermsWithCondition(residuals, residualSearchCond);
    RemoveEqualNonTerminals(residuals);
    for each(ResidualNonTerm* residual in residuals)
    {
        auto residualTerms = residual->GetResidualTermsValues();
        char firstResidualTerm = residualTerms.first;
        vector<NonTerm*> candidates;
        _startSymbol->GetNonTermsWithCondition(candidates,
            [firstResidualTerm](NonTerm* nonTerm)-> 
            bool {return nonTerm->HasDisclosuerToTerm(firstResidualTerm) && !nonTerm->IsResidual(); }
        );
        //shouldn't replace residual with start symbol
        //reason: nobody can't point to start symbol
        vector<NonTerm*>::iterator it;
        if (candidates.end() != (it = find(candidates.begin(), candidates.end(), _startSymbol.get())))
        {
            candidates.erase(it);
        }
        for each(NonTerm* candidate in candidates)
        {
            bool residualReplaced = false;
            auto disclosuers = candidate->GetDisclosuers();
            for each(NonTerm::Disclosuer disc in disclosuers)
            {
                if (nullptr != disc.second && dynamic_pointer_cast<NonTerm>(disc.second)->HasDisclosuerToTerm(residualTerms.second, true))
                {
                    if (!candidate->HasDisclosuerToTerm(residualTerms.second))
                    {
                        candidate->AddDisclosuer(NonTerm::Disclosuer(Term::Ptr(new Term(residualTerms.second)), nullptr));
                    }
                    _startSymbol->ReplaceNonTermWith(residual, candidate);
                    residualReplaced = true;
                    break;
                }
            }
            if (residualReplaced) break;
        }
    }
}


void ChainGrammar::SimplyfyGrammar()
{
    vector<NonTerm*> v;
    for each(char termVal in _termValues)
    {
        v.clear();
        _startSymbol->GetNonTermsWithCondition(
            v,
            [termVal](NonTerm* nonTerm)->
            bool {return nonTerm->HasDisclosuerToTerm(termVal); }
        );
        if (v.size() > 1)
        {
            RemoveEqualNonTerminals(v);
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
        Symbol::Disclosuer disclosuer;
        Symbol::Ptr currentSymbol = _startSymbol;
        for (int i = 0; i < chainLen; i++)
        {
            bool lastTerm = chainLen - 1 == i;
            Symbol::Disclosuer* pSatisfyingDisclosuer;
            if (pSatisfyingDisclosuer = dynamic_pointer_cast<NonTerm>(currentSymbol)->GetSatisfyingDisclosuer(chain[i], lastTerm))
            {
                currentSymbol = pSatisfyingDisclosuer->second;
            }
            else
            {
                disclosuer = AddDisclosuerToNonTerm(dynamic_pointer_cast<NonTerm>(currentSymbol), chain[i], lastTerm);
                currentSymbol = disclosuer.second;
            }
        }
    }
}


void ChainGrammar::AddMaxLenChain(string chain)
{
    if (nullptr == _startSymbol)
    {
        _startSymbol = NonTerm::Ptr(new NonTerm());
    }
    Symbol::Disclosuer disclosuer;
    Symbol::Ptr currentSymbol = _startSymbol;
    int chainLen = chain.length();
    for (int i = 0; i < chainLen - 2; i++)
    {
        if (chainLen - 3 == i)
        {
            disclosuer = AddDisclosuerToNonTerm(dynamic_pointer_cast<NonTerm>(currentSymbol), chain[i], chain[i+1], chain[i+2]);
        }
        else
        {
            disclosuer = AddDisclosuerToNonTerm(dynamic_pointer_cast<NonTerm>(currentSymbol), chain[i], false);
        }
        currentSymbol = disclosuer.second;
    }
}


void ChainGrammar::RemoveEqualNonTerminals(vector<NonTerm*>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i + 1; j < v.size(); )
        {
            if (v[i]->EqualTo(v[j]))
            {
                auto src = v[j];
                v.erase(find(v.begin(), v.end(), src));
                _startSymbol->ReplaceNonTermWith(src, v[i]);
            }
            else
            {
                j++;
            }
        }
    }
}


ChainGrammar::Symbol::Disclosuer ChainGrammar::AddDisclosuerToNonTerm(NonTerm::Ptr symbol, char term, char t1, char t2)
{
    ChainGrammar::Symbol::Disclosuer newdisclosuer;
    newdisclosuer.first = Symbol::Ptr(new Term(term));
    newdisclosuer.second = Symbol::Ptr(new ResidualNonTerm(t1, t2));
    symbol->AddDisclosuer(newdisclosuer);
    return newdisclosuer;
}


ChainGrammar::Symbol::Disclosuer ChainGrammar::AddDisclosuerToNonTerm(ChainGrammar::NonTerm::Ptr symbol, char term, bool lastTerm)
{
    ChainGrammar::Symbol::Disclosuer newdisclosuer;
    CheckNewTerm(term);
    newdisclosuer.first = Symbol::Ptr(new Term(term));
    if (lastTerm)
    {
        newdisclosuer.second = nullptr;
    }
    else
    {
        newdisclosuer.second = Symbol::Ptr(new NonTerm());
    }
    symbol->AddDisclosuer(newdisclosuer);
    return newdisclosuer;
}


void ChainGrammar::CheckNewTerm(char term)
{
    if (find(_termValues.begin(), _termValues.end(), term) == _termValues.end())
    {
        _termValues.push_back(term);
    }
}


string ChainGrammar::NonTerm::GetRandomChain()
{
    int r = rand() % _disclosuers.size();
    string term = string(1, dynamic_pointer_cast<ChainGrammar::Term>(_disclosuers[r].first)->GetValue());
    if (nullptr == _disclosuers[r].second)
    {
        return term;
    }
    else
    {
        if (_disclosuers[r].second->IsTerm())
        {
            return term + string(1, dynamic_pointer_cast<ChainGrammar::Term>(_disclosuers[r].second)->GetValue());
        }
        else
        {
            return term + dynamic_pointer_cast<ChainGrammar::NonTerm>(_disclosuers[r].second)->GetRandomChain();
        }
    }
}


ChainGrammar::Symbol::Disclosuer* ChainGrammar::NonTerm::GetRandomDisclosuer()
{
    return &_disclosuers[rand() % _disclosuers.size()];
}


vector<ChainGrammar::Symbol::Disclosuer> ChainGrammar::NonTerm::GetDisclosuers() const
{
    return _disclosuers;
}


ChainGrammar::Symbol::Disclosuer* ChainGrammar::NonTerm::GetSatisfyingDisclosuer(const char term, bool last/* = false*/)
{
    for(int i = 0; i < _disclosuers.size(); i++)
    {
        if (term == dynamic_pointer_cast<Term>(_disclosuers[i].first)->GetValue())
        {
            if (!last || (last && nullptr == _disclosuers[i].second))
            {
                return &_disclosuers[i];
            }
        }
    }
    return nullptr;
}


void ChainGrammar::NonTerm::GetNonTermsWithCondition(vector<NonTerm*>& v, NonTerm::SearchCondition condition, deque<NonTerm*> stack/* = deque<NonTerm*>()*/)
{
    stack.push_back(this);
    if(condition(this))
    {
        if (find(v.begin(), v.end(), this) == v.end())
        {
            v.push_back(this);
        }
    }
    for each(Disclosuer disclosuer in _disclosuers)
    {
        if (nullptr != disclosuer.second &&
            !disclosuer.second->IsTerm() &&
            find(stack.begin(), stack.end(), disclosuer.second.get()) == stack.end())
        {
            dynamic_pointer_cast<NonTerm>(disclosuer.second)->GetNonTermsWithCondition(v, condition, stack);
        }
    }
    stack.pop_back();
}


bool ChainGrammar::NonTerm::IsResidual() const
{
    for each(Disclosuer disclos in _disclosuers)
    {
        if (disclos.first->IsTerm() && nullptr != disclos.second && disclos.second->IsTerm())
        {
            return true;
        }
    }
    return false;
}


bool ChainGrammar::NonTerm::HasDisclosuerToTerm(const char term, bool last/* = false*/) const
{
    for (int i = 0; i < _disclosuers.size(); i++)
    {
        if (_disclosuers[i].first->IsTerm() &&
            term == dynamic_pointer_cast<Term>(_disclosuers[i].first)->GetValue())
        {
            return last ? nullptr == _disclosuers[i].second : true;
        }
    }
    return false;
}


bool ChainGrammar::NonTerm::EqualTo(const ChainGrammar::NonTerm* other) const
{
    vector<Disclosuer> otherdisclosuers = other->GetDisclosuers();
    if (_disclosuers.size() == otherdisclosuers.size())
    {
        for (int i = 0; i < _disclosuers.size(); i++)
        {
            if (!NonTerminalsDisclosuersEqual(_disclosuers[i], otherdisclosuers[i], this, other))
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


void ChainGrammar::NonTerm::ReplaceNonTermWith(ChainGrammar::NonTerm* src, ChainGrammar::NonTerm* dest, deque<NonTerm*> stack/* = deque<NonTerm*>()*/)
{
    stack.push_back(this);
    for (int i = 0; i < _disclosuers.size(); i++)
    {
        if (nullptr != _disclosuers[i].second)
        {
            if (_disclosuers[i].second.get() == src)
            {
                _disclosuers[i].second.reset(dest, [](NonTerm*) {});
            }
            else
            {
                if (!_disclosuers[i].second->IsTerm() &&
                    find(stack.begin(), stack.end(), _disclosuers[i].second.get()) == stack.end())
                {
                    dynamic_pointer_cast<ChainGrammar::NonTerm>(_disclosuers[i].second)->ReplaceNonTermWith(src, dest, stack);
                }
            }
        }
    }
    stack.pop_back();
}


void ChainGrammar::NonTerm::AddRecursiveToDiclosureStartingWith(const char term)
{
    Disclosuer recdisclosuer;
    recdisclosuer.first = Symbol::Ptr(new Term(term));
    recdisclosuer.second = Symbol::Ptr(this);
    _disclosuers.push_back(recdisclosuer);
}


void ChainGrammar::NonTerm::AddDisclosuer(ChainGrammar::Symbol::Disclosuer newDiscloser)
{
    if (find(_disclosuers.begin(), _disclosuers.end(), newDiscloser) == _disclosuers.end())
    {
        _disclosuers.push_back(newDiscloser);
    }
}


bool NonTerminalsDisclosuersEqual(const ChainGrammar::Symbol::Disclosuer& a, const ChainGrammar::Symbol::Disclosuer& b, const ChainGrammar::NonTerm* nonTermA, const ChainGrammar::NonTerm* nonTermB)
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
                if ((nullptr == a.second) == (nullptr == b.second) &&
                    a.second->IsTerm() == b.second->IsTerm())
                {
                    if (a.second == b.second ||
                        (a.second.get() == nonTermA && b.second.get() == nonTermB) ||
                        (a.second.get() == nonTermB && b.second.get() == nonTermA))
                    {
                        return true;
                    }
                    else if (a.second->IsTerm() &&
                        dynamic_pointer_cast<ChainGrammar::Term>(a.second)->GetValue() == dynamic_pointer_cast<ChainGrammar::Term>(b.second)->GetValue())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}