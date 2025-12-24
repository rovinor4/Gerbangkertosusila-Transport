#include "common.h"
#include "transport.h"
#include "region.h"
#include "relation.h"

void seedDummyData(TransportList &transports, RegionList &regions)
{
    insertFirstTransport(transports, createTransportNode(101, "Bus Antar Kota", 15000, 5, 22));
    insertFirstTransport(transports, createTransportNode(102, "Kereta Komuter", 8000, 4, 23));
    insertFirstTransport(transports, createTransportNode(103, "Mobil Shuttle", 25000, 6, 21));
    insertFirstTransport(transports, createTransportNode(104, "Bus Kota", 5000, 5, 21));

    insertLastRegion(regions, createRegionNode(201, "Surabaya", "Gubeng Station, Bungurasih Terminal"));
    insertLastRegion(regions, createRegionNode(202, "Sidoarjo", "Sidoarjo Station, Larangan Terminal"));
    insertLastRegion(regions, createRegionNode(203, "Gresik", "Gresik Terminal, Pelabuhan Gresik"));
    insertLastRegion(regions, createRegionNode(204, "Mojokerto", "Mojokerto Station, Mojokerto Terminal"));
    insertLastRegion(regions, createRegionNode(205, "Lamongan", "Lamongan Station, Lamongan Terminal"));

    RegionNode *surabaya = findRegionById(regions, 201);
    RegionNode *sidoarjo = findRegionById(regions, 202);
    RegionNode *gresik = findRegionById(regions, 203);
    RegionNode *mojokerto = findRegionById(regions, 204);
    RegionNode *lamongan = findRegionById(regions, 205);

    TransportNode *bus = findTransportById(transports, 101);
    TransportNode *train = findTransportById(transports, 102);
    TransportNode *van = findTransportById(transports, 103);
    TransportNode *city = findTransportById(transports, 104);

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

void featureAddTransport(TransportList &transports)
{
    header("TAMBAH ANGKUTAN");

    int id = inputInt("ID: ");
    string name = inputLine("Nama: ");
    int price = inputInt("Tarif: ");
    int startH = inputInt("Jam mulai operasional (0..23): ");
    int endH = inputInt("Jam akhir operasional (0..23): ");

    if (!validateTransportFields(id, name, price, startH, endH))
    {
        cout << "Data angkutan tidak valid.\n";
        return;
    }

    if (findTransportById(transports, id) != nullptr)
    {
        cout << "ID sudah terdaftar.\n";
        return;
    }

    insertFirstTransport(transports, createTransportNode(id, name, price, startH, endH));
    cout << "Angkutan berhasil ditambahkan.\n";
}

void featureDeleteTransport(TransportList &transports, RegionList &regions)
{
    header("HAPUS ANGKUTAN PERTAMA");

    int deletedId = -1;
    if (!deleteFirstTransport(transports, deletedId))
    {
        cout << "Data angkutan kosong.\n";
        return;
    }

    removeAllRelationsToTransport(regions, deletedId);
    cout << "Angkutan dengan ID " << deletedId << " berhasil dihapus.\n";
    cout << "Seluruh relasi terkait telah dihapus.\n";
}

void featureAddRegion(RegionList &regions)
{
    header("TAMBAH DAERAH");

    int id = inputInt("ID: ");
    string name = inputLine("Nama: ");
    string spots = inputLine("Tempat utama: ");

    if (!validateRegionFields(id, name, spots))
    {
        cout << "Data daerah tidak valid.\n";
        return;
    }

    if (findRegionById(regions, id) != nullptr)
    {
        cout << "ID sudah terdaftar.\n";
        return;
    }

    insertLastRegion(regions, createRegionNode(id, name, spots));
    cout << "Daerah berhasil ditambahkan.\n";
}

void featureDeleteRegion(RegionList &regions)
{
    header("HAPUS DAERAH TERAKHIR");

    int deletedId = -1;
    if (!deleteLastRegion(regions, deletedId))
    {
        cout << "Data daerah kosong.\n";
        return;
    }
    cout << "Daerah dengan ID " << deletedId << " berhasil dihapus.\n";
}

void featureConnect(TransportList &transports, RegionList &regions)
{
    header("HUBUNGKAN DAERAH DAN ANGKUTAN");

    int regionId = inputInt("ID Daerah: ");
    int transportId = inputInt("ID Angkutan: ");

    RegionNode *r = findRegionById(regions, regionId);
    TransportNode *t = findTransportById(transports, transportId);

    if (r == nullptr)
    {
        cout << "Daerah tidak ditemukan.\n";
        return;
    }
    if (t == nullptr)
    {
        cout << "Angkutan tidak ditemukan.\n";
        return;
    }

    if (!addRelation(r, t))
    {
        cout << "Gagal menghubungkan. Mungkin sudah terhubung.\n";
        return;
    }

    cout << "Berhasil dihubungkan.\n";
}

void featureDisconnect(RegionList &regions)
{
    header("PUTUSKAN HUBUNGAN DAERAH DAN ANGKUTAN");

    int regionId = inputInt("ID Daerah: ");
    int transportId = inputInt("ID Angkutan: ");

    RegionNode *r = findRegionById(regions, regionId);
    if (r == nullptr)
    {
        cout << "Daerah tidak ditemukan.\n";
        return;
    }

    if (!removeRelation(r, transportId))
    {
        cout << "Relasi tidak ditemukan.\n";
        return;
    }

    cout << "Relasi berhasil diputuskan.\n";
}

void featureShowEasyHard(const RegionList &regions)
{
    header("DAERAH PALING MUDAH & SULIT DIAKSES");

    if (isRegionEmpty(regions))
    {
        cout << "Data daerah kosong.\n";
        return;
    }

    RegionNode *easiest = nullptr;
    RegionNode *hardest = nullptr;

    RegionNode *cur = regions.head;
    while (cur != nullptr)
    {
        if (easiest == nullptr || countRelations(cur) > countRelations(easiest))
            easiest = cur;
        if (hardest == nullptr || countRelations(cur) < countRelations(hardest))
            hardest = cur;
        cur = cur->next;
    }

    cout << "Daerah paling mudah diakses: " << easiest->info.name << " (jumlah relasi: " << countRelations(easiest) << ")\n";
    cout << "Daerah paling sulit diakses: " << hardest->info.name << " (jumlah relasi: " << countRelations(hardest) << ")\n";
}

int main()
{
    TransportList transports{};
    RegionList regions{};

    initTransportList(transports);
    initRegionList(regions);

    seedDummyData(transports, regions);

    while (true)
    {
        header("MENU UTAMA");
        cout << "1. Tambah data alat angkutan\n";
        cout << "2. Tambah data daerah\n";
        cout << "3. Hubungkan alat angkutan dan daerah\n";
        cout << "4. Hapus data alat angkutan tertentu\n";
        cout << "5. Hapus data daerah tertentu\n";
        cout << "6. Tampilkan semua alat angkutan beserta daerah yang bisa dikunjungi\n";
        cout << "7. Tampilkan semua daerah yang bisa dilalui alat angkutan tertentu\n";
        cout << "8. Tampilkan semua alat angkutan yang bisa mengunjungi daerah tertentu\n";
        cout << "9. Tampilkan daerah paling mudah & paling sulit sarana transportasinya\n";
        cout << "0. Keluar\n";

        int choice = inputInt("Pilih menu: ");

        switch (choice)
        {
        case 0:
            header("KELUAR");
            cout << "Semoga sukses.\n";
            break;
        case 1:
            featureAddTransport(transports);
            pauseEnter();
            break;
        case 2:
            featureAddRegion(regions);
            pauseEnter();
            break;
        case 3:
            featureConnect(transports, regions);
            pauseEnter();
            break;
        case 4:
        {
            header("HAPUS ANGKUTAN BERDASARKAN ID");
            int id = inputInt("Masukkan ID angkutan yang akan dihapus: ");
            TransportNode *t = findTransportById(transports, id);
            if (!t)
            {
                cout << "Angkutan tidak ditemukan.\n";
            }
            else
            {
                TransportNode *curr = transports.head;
                TransportNode *prev = nullptr;
                while (curr && curr->info.id != id)
                {
                    prev = curr;
                    curr = curr->next;
                }
                if (curr)
                {
                    if (prev)
                        prev->next = curr->next;
                    else
                        transports.head = curr->next;
                    if (curr == transports.tail)
                        transports.tail = prev;
                    removeAllRelationsToTransport(regions, id);
                    delete curr;
                    cout << "Angkutan berhasil dihapus.\n";
                }
            }
            pauseEnter();
            break;
        }
        case 5:
        {
            header("HAPUS DAERAH BERDASARKAN ID");
            int id = inputInt("Masukkan ID daerah yang akan dihapus: ");
            RegionNode *prev = nullptr;
            RegionNode *curr = regions.head;
            while (curr && curr->info.id != id)
            {
                prev = curr;
                curr = curr->next;
            }
            if (!curr)
            {
                cout << "Daerah tidak ditemukan.\n";
            }
            else
            {
                if (prev)
                    prev->next = curr->next;
                else
                    regions.head = curr->next;
                freeRelations(curr);
                delete curr;
                cout << "Daerah berhasil dihapus.\n";
            }
            pauseEnter();
            break;
        }
        case 6:
            header("SEMUA ANGKUTAN BESERTA DAERAH YANG BISA DIKUNJUNGI");
            showAllTransportsWithRegions(transports, regions);
            pauseEnter();
            break;
        case 7:
            header("DAERAH YANG BISA DILALUI ANGKUTAN TERTENTU");
            {
                int id = inputInt("Masukkan ID angkutan: ");
                TransportNode *t = findTransportById(transports, id);
                showTransportWithRegions(t, regions);
            }
            pauseEnter();
            break;
        case 8:
            header("ANGKUTAN YANG BISA MENGUNJUNGI DAERAH TERTENTU");
            {
                int id = inputInt("Masukkan ID daerah: ");
                RegionNode *r = findRegionById(regions, id);
                showRegionWithTransports(r);
            }
            pauseEnter();
            break;
        case 9:
            featureShowEasyHard(regions);
            pauseEnter();
            break;
        default:
            cout << "Menu tidak valid.\n";
            pauseEnter();
            break;
        }
    }

    while (!isTransportEmpty(transports))
    {
        int deletedId = -1;
        deleteFirstTransport(transports, deletedId);
        removeAllRelationsToTransport(regions, deletedId);
    }

    while (!isRegionEmpty(regions))
    {
        int deletedId = -1;
        deleteLastRegion(regions, deletedId);
    }

    return 0;
}
