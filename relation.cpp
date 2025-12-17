#include "relation.h"

RelationNode* createRelationNode(TransportNode* t) {
    RelationNode* p = new RelationNode;
    p->transport = t;
    p->next = nullptr;
    return p;
}

bool isRelated(const RegionNode* region, int transportId) {
    if (region == nullptr) return false;

    RelationNode* cur = region->relations;
    while (cur != nullptr) {
        if (cur->transport != nullptr && cur->transport->info.id == transportId) return true;
        cur = cur->next;
    }
    return false;
}

bool addRelation(RegionNode* region, TransportNode* t) {
    if (region == nullptr || t == nullptr) return false;
    if (isRelated(region, t->info.id)) return false;

    RelationNode* p = createRelationNode(t);
    p->next = region->relations;
    region->relations = p;
    return true;
}

bool removeRelation(RegionNode* region, int transportId) {
    if (region == nullptr) return false;

    RelationNode* prev = nullptr;
    RelationNode* cur = region->relations;

    while (cur != nullptr) {
        if (cur->transport != nullptr && cur->transport->info.id == transportId) {
            if (prev == nullptr) {
                region->relations = cur->next;
            } else {
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

int countRelations(const RegionNode* region) {
    if (region == nullptr) return 0;

    int cnt = 0;
    RelationNode* cur = region->relations;
    while (cur != nullptr) {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

void freeRelations(RegionNode* region) {
    if (region == nullptr) return;

    RelationNode* cur = region->relations;
    while (cur != nullptr) {
        RelationNode* del = cur;
        cur = cur->next;
        del->next = nullptr;
        delete del;
    }
    region->relations = nullptr;
}

void removeAllRelationsToTransport(RegionList& regions, int transportId) {
    RegionNode* r = regions.head;
    while (r != nullptr) {
        while (removeRelation(r, transportId)) {
        }
        r = r->next;
    }
}

static void printTransportRow(const TransportInfo& t) {
    cout << left
         << setw(6)  << t.id
         << setw(22) << t.name
         << setw(10) << t.price
         << setw(8)  << t.opStart
         << setw(8)  << t.opEnd
         << "\n";
}

void showRegionWithTransports(const RegionNode* region) {
    if (region == nullptr) {
        cout << "Region not found.\n";
        return;
    }

    cout << "Region: " << region->info.name << "\n";
    cout << "Main spots: " << region->info.mainSpots << "\n";

    if (region->relations == nullptr) {
        cout << "No connected transport.\n";
        return;
    }

    cout << left
         << setw(6)  << "ID"
         << setw(22) << "NAME"
         << setw(10) << "PRICE"
         << setw(8)  << "START"
         << setw(8)  << "END"
         << "\n";

    RelationNode* cur = region->relations;
    while (cur != nullptr) {
        if (cur->transport != nullptr) {
            printTransportRow(cur->transport->info);
        }
        cur = cur->next;
    }
}

void showAllRegionsWithTransports(const RegionList& regions) {
    if (isRegionEmpty(regions)) {
        cout << "No region data.\n";
        return;
    }

    RegionNode* r = regions.head;
    while (r != nullptr) {
        cout << "\n" << string(25,'=') << endl;
        cout << "REGION DETAIL\n";
        cout << "\n" << string(25,'=') << endl;
        showRegionWithTransports(r);
        r = r->next;
    }
}

void showTransportWithRegions(const TransportNode* t, const RegionList& regions) {
    if (t == nullptr) {
        cout << "Transport not found.\n";
        return;
    }

    cout << "Transport:\n";
    cout << left
         << setw(6)  << "ID"
         << setw(22) << "NAME"
         << setw(10) << "PRICE"
         << setw(8)  << "START"
         << setw(8)  << "END"
         << "\n";
    printTransportRow(t->info);

    cout << "Connected regions:\n";

    bool any = false;
    RegionNode* r = regions.head;
    while (r != nullptr) {
        if (isRelated(r, t->info.id)) {
            any = true;
            cout << " - " << r->info.name << "\n";
        }
        r = r->next;
    }

    if (!any) cout << "None.\n";
}

void showAllTransportsWithRegions(const TransportList& transports, const RegionList& regions) {
    if (isTransportEmpty(transports)) {
        cout << "No transport data.\n";
        return;
    }

    TransportNode* t = transports.head;
    while (t != nullptr) {
        cout << "\n" << string(25,'=') << endl;
        cout << "TRANSPORT DETAIL\n";
        cout << "\n" << string(25,'=') << endl;
        showTransportWithRegions(t, regions);
        t = t->next;
    }
}
