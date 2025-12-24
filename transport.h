#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "common.h"

struct TransportInfo
{
    int id;
    string name;
    int price;
    int opStart;
    int opEnd;
};

struct TransportNode
{
    TransportInfo info;
    TransportNode *prev{};
    TransportNode *next{};
};

struct TransportList
{
    TransportNode *head;
    TransportNode *tail;
};

void initTransportList(TransportList &L);
bool isTransportEmpty(const TransportList &L);

TransportNode *createTransportNode(int id, const string &name, int price, int opStart, int opEnd);

void insertFirstTransport(TransportList &L, TransportNode *p);
bool deleteFirstTransport(TransportList &L, int &deletedId);

TransportNode *findTransportById(const TransportList &L, int id);
void printTransport(const TransportInfo &t);
void showAllTransport(const TransportList &L);

bool validateHour(int h);
bool validateTransportFields(int id, const string &name, int price, int opStart, int opEnd);

#endif
