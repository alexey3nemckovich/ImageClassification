#pragma once
#include <string>
#include <memory>
#include <sstream>
#include "TwoDimensionalArray.h"
using namespace std;


class HierarchyGroup
{
public:
    typedef shared_ptr<HierarchyGroup> Ptr;
    HierarchyGroup() = delete;
    HierarchyGroup(int objectNumber)
    {
        _objectNumber = objectNumber;
        ostringstream ostream;
        ostream << "x" << objectNumber + 1;
        _name = ostream.str();
        _hasSubGroups = false;
        _hasUpGroup = false;
        _countGroupObjects = 1;
    }
    HierarchyGroup(string name, Ptr subGroup1, Ptr subGroup2, double subGroupDistance)
    {
        _hasUpGroup = false;
        _subGroups.first = subGroup1;
        _subGroups.second = subGroup2;
        _subGroupsDistance = subGroupDistance;
        _name = name;
        _hasSubGroups = true;
        _objectNumber = INT_MIN;
        subGroup1->_hasUpGroup = subGroup2->_hasUpGroup = true;
        _countGroupObjects = 0;
        _countGroupObjects += subGroup1->GetCountObjects();
        _countGroupObjects += subGroup2->GetCountObjects();
    }
    ~HierarchyGroup();
    bool HasSubGroups()
    {
        return _hasSubGroups;
    }
    bool HasUpGroup()
    {
        return _hasUpGroup;
    }
    double GetSubGroupsDistance()
    {
        return _subGroupsDistance;
    }
    int GetCountObjects()
    {
        return _countGroupObjects;
    }
    pair<Ptr, Ptr> GetSubGroups()
    {
        return _subGroups;
    }
    string GetName()
    {
        return _name;
    }
    const char* GetCName()
    {
        return _name.c_str();
    }
    int GetLevel();
    double DistanceTo(Ptr, const TwoDimensionalArray<double>& distanceTable) const;
    double DistanceTo(int, const TwoDimensionalArray<double>& distanceTable) const;
private:
    bool _hasSubGroups;
    bool _hasUpGroup;
    string _name;
    int _objectNumber;
    int _countGroupObjects;
    double _subGroupsDistance;
    pair<Ptr, Ptr> _subGroups;
};