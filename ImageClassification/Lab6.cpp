#include "stdafx.h"
#include "Lab6.h"
#include "TwoDimensionalArray.h"
using namespace std;


typedef vector<HierarchyGroup::Ptr> HierarchyGroupList;


Lab6::~Lab6()
{

}


void Lab6::AddHierarchyGroupImageToCoordinateSystem(HierarchyGroup::Ptr top, StandardCoordinateSystem* sc, bool clearCoordSystem/* = true*/)
{
    int totalObjectsCount = top->GetCountObjects();
    if (clearCoordSystem)
    {
        sc->Clear();
    }
    sc->SetLogicBounds(CRect(-1, top->GetSubGroupsDistance() + 1, totalObjectsCount + 1, -1));
    double hierarchyHeadLogicX;
    if (top->HasSubGroups())
    {
        hierarchyHeadLogicX = (top->GetSubGroups().first->GetCountObjects() - 0.5) * LOGIC_DISTANCE_BETWEEN_OBJECTS + LOGIC_VERT_AXIS_HIERARCHY_MARGIN;
    }
    else
    {
        hierarchyHeadLogicX = LOGIC_VERT_AXIS_HIERARCHY_MARGIN;
    } 
    RenderHierarchyGroup(top, sc, hierarchyHeadLogicX);
}


LogicPoint Lab6::RenderHierarchyGroup(HierarchyGroup::Ptr group, StandardCoordinateSystem *sc, double upGroupX, bool left/* = true*/)
{
    #define COLOR RGB(255, 0, 0)
    double x, y;
    if (group->HasSubGroups())
    {
        y = group->GetSubGroupsDistance();
        if (group->HasUpGroup())
        {
            if (left)
            {
                int rightSubGroupObjectsCount = group->GetSubGroups().second->GetCountObjects();
                x = upGroupX - rightSubGroupObjectsCount * LOGIC_DISTANCE_BETWEEN_OBJECTS;
            }
            else
            {
                int leftSubGroupObjectsCount = group->GetSubGroups().first->GetCountObjects();
                x = upGroupX + leftSubGroupObjectsCount * LOGIC_DISTANCE_BETWEEN_OBJECTS;
            }
        }
        else
        {   
            x = upGroupX;
        }
        vector<LogicPoint> v(4);
        v[0] = RenderHierarchyGroup(group->GetSubGroups().first, sc, x, true);
        v[3] = RenderHierarchyGroup(group->GetSubGroups().second, sc, x, false);
        v[1] = LogicPoint(v[0].x, y);
        v[2] = LogicPoint(v[3].x, y);
        sc->AddPlot(Plot(v));
    }
    else
    {
        y = 0;
        if (left)
        {
            x = upGroupX - 0.5 * LOGIC_DISTANCE_BETWEEN_OBJECTS;
        }
        else
        {
            x = upGroupX + 0.5 * LOGIC_DISTANCE_BETWEEN_OBJECTS;
        }
    }
    LogicPoint groupSCPoint = LogicPoint(x, y);
    if (0 == y)
    {
        sc->AddLogicPoint(groupSCPoint, COLOR);
    }
    else
    {
        sc->AddLogicPoint(groupSCPoint, COLOR, false, true, false, false);
    }
    //sc->RenderText(sc, groupSCPoint, CString(group->GetCName()));
    return LogicPoint(x, y);
}


HierarchyGroup::Ptr Lab6::GetHierarchyGroup(int objectsCount, Criterion criterion)
{
    TwoDimensionalArray<double> distanceTable(objectsCount, objectsCount);
    //example
    /*distanceTable[0][1] = distanceTable[1][0] = 5;
    distanceTable[0][2] = distanceTable[2][0] = 0.5;
    distanceTable[0][3] = distanceTable[3][0] = 2;
    distanceTable[1][2] = distanceTable[2][1] = 1;
    distanceTable[1][3] = distanceTable[3][1] = 0.6;*/
    if (Criterion::MAX == criterion)
    {
        FillDistanceTable(distanceTable, 0, 1);
        ReplaceValuesToOpposite(distanceTable);
    }
    else
    {
        FillDistanceTable(distanceTable, 1, 10);
    }
    HierarchyGroupList hierarchyGroupList = GenerateHierarchyGroupList(objectsCount);
    char name = 'a';
    while (1 != hierarchyGroupList.size())
    {
        HierarchyGroup::Ptr a, b;
        HierarchyGroupList::iterator pa, pb;
        int c = hierarchyGroupList.size();
        double minDistance = INT_MAX;
        double distance;
        for (auto i = hierarchyGroupList.begin(); hierarchyGroupList.end() != i; i++)
        {
            for (auto j = i + 1; hierarchyGroupList.end() != j; j++)
            {
                if ((distance = (*i)->DistanceTo(*j, distanceTable)) < minDistance)
                {
                    minDistance = distance;
                    a = *i;
                    pa = i;
                    b = *j;
                    pb = j;
                }
            }
        }
        HierarchyGroup::Ptr newGroup = HierarchyGroup::Ptr(new HierarchyGroup(string(1, name), a, b, minDistance));
        name++;
        hierarchyGroupList.erase(pb);
        hierarchyGroupList.erase(pa);
        hierarchyGroupList.push_back(newGroup);
    }
    return hierarchyGroupList[0];
}


void Lab6::FillDistanceTable(TwoDimensionalArray<double>& distanceTable, double minVal, double maxVal)
{
    int size = distanceTable.Size();
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (i != j)
            {
                double randDouble;
                do
                {
                    randDouble = RandomDouble(minVal, maxVal);
                } while (0 == randDouble && distanceTable.Contains(randDouble));
                distanceTable[i][j] = distanceTable[j][i] = randDouble;
            }
            else
            {
                distanceTable[i][j] = 0;
            }
        }
    }
}


HierarchyGroupList Lab6::GenerateHierarchyGroupList(int objectCount)
{
    HierarchyGroupList hierarchyGroupList;
    for (int i = 0; i < objectCount; i++)
    {
        hierarchyGroupList.push_back(HierarchyGroup::Ptr(new HierarchyGroup(i)));
    }
    return hierarchyGroupList;
}


void Lab6::ReplaceValuesToOpposite(TwoDimensionalArray<double>& arr)
{
    for (int i = 0; i < arr.Size(); i++)
    {
        for (int j = 0; j < arr.Size(false); j++)
        {
            if (i != j)
            {
                arr[i][j] = 1 / arr[i][j];
            }
        }
    }
}