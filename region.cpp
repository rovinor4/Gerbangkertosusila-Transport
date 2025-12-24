#include "region.h"

void initRegionList(RegionList &L)
{
    L.head = nullptr;
}

bool isRegionEmpty(const RegionList &L)
{
    return L.head == nullptr;
}

bool validateRegionFields(int id, const string &name, const string &mainSpots)
{
    if (id <= 0)
        return false;
    if (name.empty())
        return false;
    if (mainSpots.empty())
        return false;
    return true;
}

RegionNode *createRegionNode(int id, const string &name, const string &mainSpots)
{
    RegionNode *p = new RegionNode;
    p->info.id = id;
    p->info.name = name;
    p->info.mainSpots = mainSpots;
    p->next = nullptr;
    p->relations = nullptr;
    return p;
}

void insertLastRegion(RegionList &L, RegionNode *p)
{
    if (p == nullptr)
        return;

    if (isRegionEmpty(L))
    {
        L.head = p;
        return;
    }

    RegionNode *cur = L.head;
    while (cur->next != nullptr)
    {
        cur = cur->next;
    }
    cur->next = p;
}

bool deleteLastRegion(RegionList &L, int &deletedId)
{
    if (isRegionEmpty(L))
        return false;

    if (L.head->next == nullptr)
    {
        RegionNode *p = L.head;
        deletedId = p->info.id;
        L.head = nullptr;
        delete p;
        return true;
    }

    RegionNode *prev = nullptr;
    RegionNode *cur = L.head;
    while (cur->next != nullptr)
    {
        prev = cur;
        cur = cur->next;
    }

    deletedId = cur->info.id;
    prev->next = nullptr;
    delete cur;
    return true;
}

RegionNode *findRegionById(const RegionList &L, int id)
{
    RegionNode *cur = L.head;
    while (cur != nullptr)
    {
        if (cur->info.id == id)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

void printRegion(const RegionInfo &r)
{
    cout << left
         << setw(6) << r.id
         << setw(18) << r.name
         << r.mainSpots
         << "\n";
}

void showAllRegions(const RegionList &L)
{
    if (isRegionEmpty(L))
    {
        cout << "Data daerah kosong.\n";
        return;
    }

    cout << left
         << setw(6) << "ID"
         << setw(18) << "NAMA DAERAH"
         << "TEMPAT UTAMA"
         << "\n";

    RegionNode *cur = L.head;
    while (cur != nullptr)
    {
        printRegion(cur->info);
        cur = cur->next;
    }
}
