#pragma once
#include "Lab.h"
#include "HierarchyGroup.h"
#include <vector>
#include "CoordinateSystem.h"


#define LAB6 6


class Lab6
    : public Lab
{
public:
    Lab6()
    {
        Labs::GetInstance()->SetActive(GetNumber());
    }
    virtual ~Lab6();
    HierarchyGroup::Ptr GetHierarchyGroup(int objectCount);
    void AddHierarchyGroupImageToCoordinateSystem(HierarchyGroup::Ptr top, StandardCoordinateSystem* sc, bool clearCoordSystem = true);
    int GetNumber()
    {
        return LAB6;
    }
private:
    #define LOGIC_DISTANCE_BETWEEN_OBJECTS 1
    #define LOGIC_VERT_AXIS_HIERARCHY_MARGIN 1
    LogicPoint RenderHierarchyGroup(HierarchyGroup::Ptr group, StandardCoordinateSystem *sc, double upGroupX, bool left = true);
    vector<HierarchyGroup::Ptr> GenerateHierarchyGroupList(int objectCount);
    void FillDistanceTable(TwoDimensionalArray<double>& distanceTable);
};