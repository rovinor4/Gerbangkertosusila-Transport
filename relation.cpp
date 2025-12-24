#include "relation.h"

RelationNode *createRelationNode(TransportNode *t)
{
    RelationNode *p = new RelationNode;
    p->transport = t;
    p->next = nullptr;
    return p;
}

bool isRelated(const RegionNode *region, int transportId)
{
    if (region == nullptr)
        return false;

    RelationNode *cur = region->relations;
    while (cur != nullptr)
    {
        if (cur->transport != nullptr && cur->transport->info.id == transportId)
            return true;
        cur = cur->next;
    }
    return false;
}

bool addRelation(RegionNode *region, TransportNode *t)
{
    if (region == nullptr || t == nullptr)
        return false;
    if (isRelated(region, t->info.id))
        return false;

    RelationNode *p = createRelationNode(t);
    p->next = region->relations;
    region->relations = p;
    return true;
}

bool removeRelation(RegionNode *region, int transportId)
{
    if (region == nullptr)
        return false;

    RelationNode *prev = nullptr;
    RelationNode *cur = region->relations;

    while (cur != nullptr)
    {
        if (cur->transport != nullptr && cur->transport->info.id == transportId)
        {
            if (prev == nullptr)
            {
                region->relations = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            cur->next = nullptr;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

int countRelations(const RegionNode *region)
{
    if (region == nullptr)
        return 0;

    int cnt = 0;
    RelationNode *cur = region->relations;
    while (cur != nullptr)
    {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

void freeRelations(RegionNode *region)
{
    if (region == nullptr)
        return;

    RelationNode *cur = region->relations;
    while (cur != nullptr)
    {
        RelationNode *del = cur;
        cur = cur->next;
        del->next = nullptr;
        delete del;
    }
    region->relations = nullptr;
}

void removeAllRelationsToTransport(RegionList &regions, int transportId)
{
    RegionNode *r = regions.head;
    while (r != nullptr)
    {
        while (removeRelation(r, transportId))
        {
        }
        r = r->next;
    }
}

static void printTransportRow(const TransportInfo &t)
{
    cout << left
         << setw(6) << t.id
         << setw(22) << t.name
         << setw(10) << t.price
         << setw(8) << t.opStart
         << setw(8) << t.opEnd
         << "\n";
}

void showRegionWithTransports(const RegionNode *region)
{
    if (region == nullptr)
    {
        cout << "Daerah tidak ditemukan.\n";
        return;
    }

    cout << "Daerah: " << region->info.name << "\n";
    cout << "Tempat utama: " << region->info.mainSpots << "\n";

    if (region->relations == nullptr)
    {
        cout << "Tidak ada angkutan yang terhubung.\n";
        return;
    }

    cout << left
         << setw(6) << "ID"
         << setw(22) << "NAMA"
         << setw(10) << "TARIF"
         << setw(8) << "MULAI"
         << setw(8) << "AKHIR"
         << "\n";

    RelationNode *cur = region->relations;
    while (cur != nullptr)
    {
        if (cur->transport != nullptr)
        {
            printTransportRow(cur->transport->info);
        }
        cur = cur->next;
    }
}

void showAllRegionsWithTransports(const RegionList &regions)
{
    if (isRegionEmpty(regions))
    {
        cout << "Data daerah kosong.\n";
        return;
    }

    RegionNode *r = regions.head;
    while (r != nullptr)
    {
        cout << "\n"
             << string(25, '=') << endl;
        cout << "DETAIL DAERAH\n";
        cout << "\n"
             << string(25, '=') << endl;
        showRegionWithTransports(r);
        r = r->next;
    }
}

void showTransportWithRegions(const TransportNode *t, const RegionList &regions)
{
    if (t == nullptr)
    {
        cout << "Angkutan tidak ditemukan.\n";
        return;
    }

    cout << "Angkutan:\n";
    cout << left
         << setw(6) << "ID"
         << setw(22) << "NAMA"
         << setw(10) << "TARIF"
         << setw(8) << "MULAI"
         << setw(8) << "AKHIR"
         << "\n";
    printTransportRow(t->info);

    cout << "Daerah yang terhubung:\n";

    bool any = false;
    RegionNode *r = regions.head;
    while (r != nullptr)
    {
        if (isRelated(r, t->info.id))
        {
            any = true;
            cout << " - " << r->info.name << "\n";
        }
        r = r->next;
    }

    if (!any)
        cout << "Tidak ada.\n";
}

void showAllTransportsWithRegions(const TransportList &transports, const RegionList &regions)
{
    if (isTransportEmpty(transports))
    {
        cout << "Data angkutan kosong.\n";
        return;
    }

    TransportNode *t = transports.head;
    while (t != nullptr)
    {
        cout << string(25, '-') << endl;
        cout << "DETAIL ANGKUTAN\n";
        cout << string(25, '-') << endl;
        showTransportWithRegions(t, regions);
        t = t->next;
    }
}
