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
    enum class Criterion
    {
        MIN,
        MAX
    };
    Lab6()
    {
        Labs::GetInstance()->SetActive(GetNumber());
    }
    virtual ~Lab6();
    HierarchyGroup::Ptr GetHierarchyGroup(int, Criterion);
    void AddHierarchyGroupImageToCoordinateSystem(HierarchyGroup::Ptr, StandardCoordinateSystem*, bool clearCoordSystem = true);
    int GetNumber()
    {
        return LAB6;
    }
private:
    #define LOGIC_DISTANCE_BETWEEN_OBJECTS 1
    #define LOGIC_VERT_AXIS_HIERARCHY_MARGIN 1
private:
    LogicPoint RenderHierarchyGroup(HierarchyGroup::Ptr, StandardCoordinateSystem*, double upGroupX, bool left = true);
    vector<HierarchyGroup::Ptr> GenerateHierarchyGroupList(int);
    void FillDistanceTable(TwoDimensionalArray<double>&, double, double);
    void ReplaceValuesToOpposite(TwoDimensionalArray<double>&);
};