#include "common.h"
#include "transport.h"
#include "region.h"
#include "relation.h"


static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void pauseEnter() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void header(const string& title) {
    cout << "\n" << string(25,'=') << endl;
    cout << title;
    cout << "\n" << string(25,'=') << endl;
}

static int inputInt(const string& label) {
    int x;
    while (true) {
        cout << label;
        if (cin >> x) {
            clearInput();
            return x;
        }
        clearInput();
        cout << "Invalid input. Try again.\n";
    }
}

static string inputLine(const string& label) {
    string s;
    cout << label;
    getline(cin, s);
    return s;
}

static void seedDummyData(TransportList& transports, RegionList& regions) {
    insertFirstTransport(transports, createTransportNode(101, "Bus Antar Kota", 15000, 5, 22));
    insertFirstTransport(transports, createTransportNode(102, "Kereta Komuter", 8000, 4, 23));
    insertFirstTransport(transports, createTransportNode(103, "Mobil Shuttle", 25000, 6, 21));
    insertFirstTransport(transports, createTransportNode(104, "Bus Kota", 5000, 5, 21));


    insertLastRegion(regions, createRegionNode(201, "Surabaya", "Gubeng Station, Bungurasih Terminal"));
    insertLastRegion(regions, createRegionNode(202, "Sidoarjo", "Sidoarjo Station, Larangan Terminal"));
    insertLastRegion(regions, createRegionNode(203, "Gresik", "Gresik Terminal, Pelabuhan Gresik"));
    insertLastRegion(regions, createRegionNode(204, "Mojokerto", "Mojokerto Station, Mojokerto Terminal"));
    insertLastRegion(regions, createRegionNode(205, "Lamongan", "Lamongan Station, Lamongan Terminal"));

    RegionNode* surabaya = findRegionById(regions, 201);
    RegionNode* sidoarjo = findRegionById(regions, 202);
    RegionNode* gresik = findRegionById(regions, 203);
    RegionNode* mojokerto = findRegionById(regions, 204);
    RegionNode* lamongan = findRegionById(regions, 205);

    TransportNode* bus = findTransportById(transports, 101);
    TransportNode* train = findTransportById(transports, 102);
    TransportNode* van = findTransportById(transports, 103);
    TransportNode* city = findTransportById(transports, 104);

    addRelation(surabaya, bus);
    addRelation(surabaya, train);
    addRelation(surabaya, van);
    addRelation(surabaya, city);

    addRelation(sidoarjo, bus);
    addRelation(sidoarjo, train);
    addRelation(sidoarjo, van);

    addRelation(gresik, bus);
    addRelation(gresik, city);

    addRelation(mojokerto, bus);
    addRelation(mojokerto, train);

    addRelation(lamongan, bus);
    addRelation(lamongan, train);
}

static void featureAddTransport(TransportList& transports) {
    header("ADD TRANSPORT");

    int id = inputInt("ID: ");
    string name = inputLine("Name: ");
    int price = inputInt("Price: ");
    int startH = inputInt("Operating start hour (0..23): ");
    int endH = inputInt("Operating end hour (0..23): ");

    if (!validateTransportFields(id, name, price, startH, endH)) {
        cout << "Invalid transport fields.\n";
        return;
    }

    if (findTransportById(transports, id) != nullptr) {
        cout << "ID already exists.\n";
        return;
    }

    insertFirstTransport(transports, createTransportNode(id, name, price, startH, endH));
    cout << "Transport added.\n";
}

static void featureDeleteTransport(TransportList& transports, RegionList& regions) {
    header("DELETE FIRST TRANSPORT");

    int deletedId = -1;
    if (!deleteFirstTransport(transports, deletedId)) {
        cout << "Transport list is empty.\n";
        return;
    }

    removeAllRelationsToTransport(regions, deletedId);
    cout << "Deleted transport ID: " << deletedId << "\n";
    cout << "All related connections removed.\n";
}

static void featureAddRegion(RegionList& regions) {
    header("ADD REGION");

    int id = inputInt("ID: ");
    string name = inputLine("Name: ");
    string spots = inputLine("Main spots: ");

    if (!validateRegionFields(id, name, spots)) {
        cout << "Invalid region fields.\n";
        return;
    }

    if (findRegionById(regions, id) != nullptr) {
        cout << "ID already exists.\n";
        return;
    }

    insertLastRegion(regions, createRegionNode(id, name, spots));
    cout << "Region added.\n";
}

static void featureDeleteRegion(RegionList& regions) {
    header("DELETE LAST REGION");

    int deletedId = -1;
    if (!deleteLastRegion(regions, deletedId)) {
        cout << "Region list is empty.\n";
        return;
    }
    cout << "Deleted region ID: " << deletedId << "\n";
}

static void featureConnect(TransportList& transports, RegionList& regions) {
    header("CONNECT REGION AND TRANSPORT");

    int regionId = inputInt("Region ID: ");
    int transportId = inputInt("Transport ID: ");

    RegionNode* r = findRegionById(regions, regionId);
    TransportNode* t = findTransportById(transports, transportId);

    if (r == nullptr) {
        cout << "Region not found.\n";
        return;
    }
    if (t == nullptr) {
        cout << "Transport not found.\n";
        return;
    }

    if (!addRelation(r, t)) {
        cout << "Connection failed. Possibly duplicate.\n";
        return;
    }

    cout << "Connected.\n";
}

static void featureDisconnect(RegionList& regions) {
    header("DISCONNECT REGION AND TRANSPORT");

    int regionId = inputInt("Region ID: ");
    int transportId = inputInt("Transport ID: ");

    RegionNode* r = findRegionById(regions, regionId);
    if (r == nullptr) {
        cout << "Region not found.\n";
        return;
    }

    if (!removeRelation(r, transportId)) {
        cout << "Connection not found.\n";
        return;
    }

    cout << "Disconnected.\n";
}

static void featureShowEasyHard(const RegionList& regions) {
    header("EASIEST AND HARDEST REGION");

    if (isRegionEmpty(regions)) {
        cout << "No region data.\n";
        return;
    }

    RegionNode* easiest = nullptr;
    RegionNode* hardest = nullptr;

    RegionNode* cur = regions.head;
    while (cur != nullptr) {
        if (easiest == nullptr || countRelations(cur) > countRelations(easiest)) easiest = cur;
        if (hardest == nullptr || countRelations(cur) < countRelations(hardest)) hardest = cur;
        cur = cur->next;
    }

    cout << "Easiest region: " << easiest->info.name << " (connections: " << countRelations(easiest) << ")\n";
    cout << "Hardest region: " << hardest->info.name << " (connections: " << countRelations(hardest) << ")\n";
}

int main() {
    TransportList transports;
    RegionList regions;

    initTransportList(transports);
    initRegionList(regions);

    seedDummyData(transports, regions);

    while (true) {
        header("MAIN MENU");
        cout << "1. Show all transport\n";
        cout << "2. Show all regions\n";
        cout << "3. Add transport\n";
        cout << "4. Delete first transport\n";
        cout << "5. Add region\n";
        cout << "6. Delete last region\n";
        cout << "7. Connect region and transport\n";
        cout << "8. Disconnect region and transport\n";
        cout << "9. Show regions with transports\n";
        cout << "10. Show transports with regions\n";
        cout << "11. Easiest and hardest region\n";
        cout << "0. Exit\n";

        int choice = inputInt("Choose: ");

        if (choice == 0) {
            header("EXIT");
            cout << "Good luck.\n";
            break;
        }

        if (choice == 1) {
            header("SHOW ALL TRANSPORT");
            showAllTransport(transports);
            pauseEnter();
        } else if (choice == 2) {
            header("SHOW ALL REGIONS");
            showAllRegions(regions);
            pauseEnter();
        } else if (choice == 3) {
            featureAddTransport(transports);
            pauseEnter();
        } else if (choice == 4) {
            featureDeleteTransport(transports, regions);
            pauseEnter();
        } else if (choice == 5) {
            featureAddRegion(regions);
            pauseEnter();
        } else if (choice == 6) {
            featureDeleteRegion(regions);
            pauseEnter();
        } else if (choice == 7) {
            featureConnect(transports, regions);
            pauseEnter();
        } else if (choice == 8) {
            featureDisconnect(regions);
            pauseEnter();
        } else if (choice == 9) {
            header("REGIONS WITH TRANSPORTS");
            showAllRegionsWithTransports(regions);
            pauseEnter();
        } else if (choice == 10) {
            header("TRANSPORTS WITH REGIONS");
            showAllTransportsWithRegions(transports, regions);
            pauseEnter();
        } else if (choice == 11) {
            featureShowEasyHard(regions);
            pauseEnter();
        } else {
            cout << "Invalid menu.\n";
            pauseEnter();
        }
    }

    while (!isTransportEmpty(transports)) {
        int deletedId = -1;
        deleteFirstTransport(transports, deletedId);
        removeAllRelationsToTransport(regions, deletedId);
    }

    while (!isRegionEmpty(regions)) {
        int deletedId = -1;
        deleteLastRegion(regions, deletedId);
    }

    return 0;
}
