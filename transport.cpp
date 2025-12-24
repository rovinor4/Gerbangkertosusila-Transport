#include "transport.h"

void initTransportList(TransportList &L)
{
    L.head = nullptr;
    L.tail = nullptr;
}

bool isTransportEmpty(const TransportList &L)
{
    return L.head == nullptr;
}

bool validateHour(int h)
{
    return h >= 0 && h <= 23;
}

bool validateTransportFields(int id, const string &name, int price, int opStart, int opEnd)
{
    if (id <= 0)
        return false;
    if (name.empty())
        return false;
    if (price < 0)
        return false;
    if (!validateHour(opStart) || !validateHour(opEnd))
        return false;
    return true;
}

TransportNode *createTransportNode(int id, const string &name, int price, int opStart, int opEnd)
{
    TransportNode *p = new TransportNode;
    p->info.id = id;
    p->info.name = name;
    p->info.price = price;
    p->info.opStart = opStart;
    p->info.opEnd = opEnd;
    p->prev = nullptr;
    p->next = nullptr;
    return p;
}

void insertFirstTransport(TransportList &L, TransportNode *p)
{
    if (p == nullptr)
        return;

    if (isTransportEmpty(L))
    {
        L.head = p;
        L.tail = p;
        return;
    }

    p->next = L.head;
    L.head->prev = p;
    L.head = p;
}

bool deleteFirstTransport(TransportList &L, int &deletedId)
{
    if (isTransportEmpty(L))
        return false;

    TransportNode *p = L.head;
    deletedId = p->info.id;

    if (L.head == L.tail)
    {
        L.head = nullptr;
        L.tail = nullptr;
        delete p;
        return true;
    }

    L.head = L.head->next;
    L.head->prev = nullptr;
    p->next = nullptr;
    delete p;
    return true;
}

TransportNode *findTransportById(const TransportList &L, int id)
{
    TransportNode *cur = L.head;
    while (cur != nullptr)
    {
        if (cur->info.id == id)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

void printTransport(const TransportInfo &t)
{
    cout << left
         << setw(6) << t.id
         << setw(22) << t.name
         << setw(10) << t.price
         << setw(8) << t.opStart
         << setw(8) << t.opEnd
         << "\n";
}

void showAllTransport(const TransportList &L)
{
    if (isTransportEmpty(L))
    {
        cout << "Data angkutan kosong.\n";
        return;
    }

    cout << left
         << setw(6) << "ID"
         << setw(22) << "NAMA"
         << setw(10) << "TARIF"
         << setw(8) << "MULAI"
         << setw(8) << "AKHIR"
         << "\n";

    TransportNode *cur = L.head;
    while (cur != nullptr)
    {
        printTransport(cur->info);
        cur = cur->next;
    }
}
