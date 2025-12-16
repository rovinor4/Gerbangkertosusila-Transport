#ifndef REGION_H
#define REGION_H

#include "common.h"

struct RelationNode;

struct RegionInfo {
    int id;
    string name;
    string mainSpots;
};

struct RegionNode {
    RegionInfo info;
    RegionNode* next;
    RelationNode* relations;
};

struct RegionList {
    RegionNode* head;
};

void initRegionList(RegionList& L);
bool isRegionEmpty(const RegionList& L);

RegionNode* createRegionNode(int id, const string& name, const string& mainSpots);

void insertLastRegion(RegionList& L, RegionNode* p);
bool deleteLastRegion(RegionList& L, int& deletedId);

RegionNode* findRegionById(const RegionList& L, int id);
void printRegion(const RegionInfo& r);
void showAllRegions(const RegionList& L);

bool validateRegionFields(int id, const string& name, const string& mainSpots);

#endif
