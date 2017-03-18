#include "stdafx.h"
#include "HierarchyGroup.h"
#include <algorithm>
using namespace std;


HierarchyGroup::~HierarchyGroup()
{

}


double HierarchyGroup::DistanceTo(Ptr other, const TwoDimensionalArray<double>& distanceTable) const
{
    if (_hasSubGroups)
    {
        return min(
            _subGroups.first->DistanceTo(other, distanceTable), 
            _subGroups.second->DistanceTo(other, distanceTable)
            );
    }
    else
    {
        return other->DistanceTo(_objectNumber, distanceTable);
    }
}


double HierarchyGroup::DistanceTo(int otherIndex, const TwoDimensionalArray<double>& distanceTable) const
{
    if (_hasSubGroups)
    {
        return min(
            _subGroups.first->DistanceTo(otherIndex, distanceTable),
            _subGroups.second->DistanceTo(otherIndex, distanceTable)
        );
    }
    else
    {
        return distanceTable[_objectNumber][otherIndex];
    }
}


int HierarchyGroup::GetLevel()
{
    if (_hasSubGroups)
    {
        return max(_subGroups.first->GetLevel(), _subGroups.second->GetLevel()) + 1;
    }
    else
    {
        return 1;
    }
}