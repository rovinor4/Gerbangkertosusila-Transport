#ifndef RELATION_H
#define RELATION_H

#include "region.h"
#include "transport.h"

struct RelationNode {
    TransportNode* transport;
    RelationNode* next;
};

RelationNode* createRelationNode(TransportNode* t);

bool isRelated(const RegionNode* region, int transportId);
bool addRelation(RegionNode* region, TransportNode* t);
bool removeRelation(RegionNode* region, int transportId);

int countRelations(const RegionNode* region);

void freeRelations(RegionNode* region);
void removeAllRelationsToTransport(RegionList& regions, int transportId);

void showRegionWithTransports(const RegionNode* region);
void showAllRegionsWithTransports(const RegionList& regions);

void showTransportWithRegions(const TransportNode* t, const RegionList& regions);
void showAllTransportsWithRegions(const TransportList& transports, const RegionList& regions);

#endif
