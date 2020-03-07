#pragma once
#include <vector>
#include <array>
#include <string>
#include "mytime.h"
#define TABLESIZE 10000
using namespace std;

struct perInfo {
    string name;
    string phone;
    string email;
    string address;
};

struct HashTable{
    perInfo** BKDRelem;  //数据元素存储的基址，动态分配数组
    bool BKDRbuilt;
    perInfo** JSelem;
    bool JSbuilt;
    perInfo** APelem;
    bool APbuilt;
    perInfo** RSelem;
    bool RSbuilt;
    perInfo** SDBMelem;
    bool SDBMbuilt;
    perInfo** PJWelem;
    bool PJWbuilt;
    int count;
};

typedef struct LinkHash
{
    perInfo* info;
    LinkHash* next;
}LinkHash;

struct PuHashTable {
    LinkHash** PuBKDRelem;
    perInfo** BKDRelem;
    bool BKDRbuilt;
    LinkHash** PuJSelem;
    perInfo** JSelem;
    bool JSbuilt;
    LinkHash** PuAPelem;
    perInfo** APelem;
    bool APbuilt;
    LinkHash** PuRSelem;
    perInfo** RSelem;
    bool RSbuilt;
    LinkHash** PuSDBMelem;
    perInfo** SDBMelem;
    bool SDBMbuilt;
    LinkHash** PuPJWelem;
    perInfo** PJWelem;
    bool PJWbuilt;
    int count;
};

struct LinkHashTable {
    LinkHash** BKDRelem;
    bool BKDRbuilt;
    LinkHash** JSelem;
    bool JSbuilt;
    LinkHash** APelem;
    bool APbuilt;
    LinkHash** RSelem;
    bool RSbuilt;
    LinkHash** SDBMelem;
    bool SDBMbuilt;
    LinkHash** PJWelem;
    bool PJWbuilt;
    int count;
};

struct Stime {
    long BKDRtime;
    long JStime;
    long APtime;
    long RStime;
    long SDBMtime;
    long PJWtime;
};

struct Sconrace {
    int BKDRr;
    int JSr;
    int APr;
    int RSr;
    int SDBr;
    int PJWr;
};

enum hash_type{BKDR=1, JS, AP, RS, SDBM, PJW};
enum conflict_solution{openaddr=1, linkaddr, overflawArea};

class hashpro
{
private:
    vector<perInfo*> *strArray;
    HashTable *H;
    LinkHashTable* LH;
    PuHashTable* PH;
    string filename;
    string allname, allemail, allphone;
    Sconrace conrace;
    Sconrace Liconrace;
    Sconrace Puconrace;
    Stime builttime;
    Stime searchtime;
    Stime avsearchtime;
    Stime Libuilttime;
    Stime Liavsearchtime;
    Stime Pubuilttime;
    Stime Puavsearchtime;
    int info_size;
    int tablesize;
    bool readCsvFile();//√

    //哈希函数
    unsigned int BKDRHash(char* str);//√
    unsigned int JSHash(char* str);//√
    unsigned int APHash(char* str);//√
    unsigned int RSHash(char* str);//√
    unsigned int SDBMHash(char* str);//√
    unsigned int PJWHash(char* str);//√
    //unsigned long blizzardHash(char* lpszFileName, unsigned long dwHashType);

    void InitHashTable();//√
    void InsertHash(const perInfo* key, const hash_type Htype, const conflict_solution con_sol);
    bool SearchHash(const string key, const hash_type Htype, perInfo& addr, const conflict_solution con_sol);//√
    void OpInsertHash(const perInfo* key, const hash_type Htype);//√
    bool OpSearchHash(const string key, const hash_type Htype, perInfo& addr);//√
    bool LiInsertHash(const perInfo* key, const hash_type Htype);
    bool LiSearchHash(const string key, const hash_type Htype, perInfo& addr);
    bool PuInsertHash(const perInfo* key, const hash_type htype);
    bool PuSearchHash(const string key, const hash_type Htype, perInfo& addr);

public:
    hashpro();//√
    hashpro(string& filename);//√
    bool randomCsvFile(int amount);//√
    string getFileName();//√
    void PutFileName(string& filename);//√
    bool addCsvDate(string& name, string& phone, string& email, string& address);//√
    //bool deleteCsvDate();
    int SearchInfo(const string &name, hash_type hex_type, conflict_solution con_sol, perInfo &persionInfo);//√
    bool avgSearchTime(hash_type hex_type, conflict_solution con_sol);
    bool BuiltTable(hash_type hex_type, conflict_solution con_sol);//√
    Stime getbuilttime(conflict_solution con_sol);//√
    Stime getsearchtime();//√
    Stime getavgsearchtime(conflict_solution con_sol);//√
    Sconrace getConflictRate(conflict_solution con_sol);//√
    int getInfoSize();

};
    