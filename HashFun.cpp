#include "HashProcessing.h"

void hashpro::InitHashTable()
{
    int i;
    int prime[14] = { 17,37,79,163,331,673,1361,2729,5471,10949,21911,43853,87719,175447 };
    for (i = 0; i < 14; i++) {
        if (info_size < prime[i]) {
            tablesize = prime[i];
            break;
        }
    }
    H->count = tablesize;
    LH->count = tablesize;
    H->BKDRelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));//动态建立int数组用于存储指针
    LH->BKDRelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    PH->PuBKDRelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    PH->BKDRelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    H->BKDRbuilt = false;
    LH->BKDRbuilt = false;
    PH->BKDRbuilt = false;
    for (i = 0; i < tablesize; i++) {
        H->BKDRelem[i] = NULL;
        LH->BKDRelem[i] = NULL;
        PH->BKDRelem[i] = NULL;
        PH->PuBKDRelem[i] = NULL;
    }
        

    H->JSelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    H->JSbuilt = false;
    LH->JSelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    LH->JSbuilt = false;
    PH->JSelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    PH->PuJSelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    PH->JSbuilt = false;
    for (i = 0; i < tablesize; i++) {
        H->JSelem[i] = NULL;
        LH->JSelem[i] = NULL;
        PH->JSelem[i] = NULL;
        PH->PuJSelem[i] = NULL;
    }
        

    H->APelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    H->APbuilt = false;
    LH->APelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    LH->APbuilt = false;

    PH->APelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    PH->PuAPelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    PH->APbuilt = false;
    for (i = 0; i < tablesize; i++) {
        H->APelem[i] = NULL;
        LH->APelem[i] = NULL;
        PH->APelem[i] = NULL;
        PH->PuAPelem[i] = NULL;
    }
        

    H->RSelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    H->RSbuilt = false;
    LH->RSelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    LH->RSbuilt = false;

    PH->RSelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    PH->PuRSelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    PH->RSbuilt = false;
    for (i = 0; i < tablesize; i++) {
        H->RSelem[i] = NULL;
        LH->RSelem[i] = NULL;
        PH->RSelem[i] = NULL;
        PH->PuRSelem[i] = NULL;
    }
        

    H->SDBMelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    H->SDBMbuilt = false;
    LH->SDBMelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    LH->SDBMbuilt = false;

    PH->SDBMelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    PH->PuSDBMelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    PH->SDBMbuilt = false;
    for (i = 0; i < tablesize; i++) {
        H->SDBMelem[i] = NULL;
        LH->SDBMelem[i] = NULL;
        PH->SDBMelem[i] = NULL;
        PH->PuSDBMelem[i] = NULL;
    }


    H->PJWelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    H->PJWbuilt = false;
    LH->PJWelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    LH->PJWbuilt = false;
    PH->PJWelem = (perInfo**)malloc(tablesize * sizeof(perInfo*));
    PH->PuPJWelem = (LinkHash**)malloc(tablesize * sizeof(LinkHash*));
    PH->PJWbuilt = false;
    for (i = 0; i < tablesize; i++) {
        H->PJWelem[i] = NULL;
        LH->PJWelem[i] = NULL;
        PH->PJWelem[i] = NULL;
        PH->PuPJWelem[i] = NULL;
    }
        
}


void hashpro::InsertHash(const perInfo * key, const hash_type Htype, const conflict_solution con_sol)
{
    switch (con_sol)
    {
    case 1:
        OpInsertHash(key, Htype);
        break;
    case 2:
        LiInsertHash(key, Htype);
        break;
    case 3:
        PuInsertHash(key, Htype);
        break;
    }

}
bool hashpro::SearchHash(const string key, const hash_type Htype, perInfo& addr, const conflict_solution con_sol)
{
    switch (con_sol)
    {
    case 1:
        return OpSearchHash(key, Htype, addr);
        break;
    case 2:
        return LiSearchHash(key, Htype, addr);
        break;
    case 3:
        return PuSearchHash(key, Htype, addr);
        break;
    }
    return false;
}

void hashpro::OpInsertHash(const perInfo *key, const hash_type Htype)
{
    int addr=-1; //根据关键字求取地址
    /*enum hash_type { BKDR, JS, AP, RS, SDBM, PJW };
    enum conflict_solution { openaddr, linkaddr, reHash, overflawArea };*/
    char ch_str[] = { 0 };
    strcpy(ch_str, (key->name).c_str());
    perInfo* pperInfo = new perInfo(*key);
    int t = 0;
    switch (Htype) {
    case 1:
        addr = BKDRHash(ch_str) % tablesize;
        while (H->BKDRelem[addr] != NULL)//不为空则有冲突
        {
            addr = (addr + 1) % tablesize; //这里使用开放定址法的线性探测
            if (t == 0) {
                conrace.BKDRr++;
            }
            t++;
        }
        H->BKDRelem[addr] = pperInfo; //直到有空位后插入
        H->BKDRbuilt = true;
        break;
    case 2:
        addr = JSHash(ch_str) % tablesize;
        while (H->JSelem[addr] != NULL)//不为空则有冲突
        {
            addr = (addr + 1) % tablesize; //这里使用开放定址法的线性探测
            if (t == 0) {
                conrace.JSr++;
            }
            t++;
        }
        H->JSelem[addr] = pperInfo; //直到有空位后插入
        H->JSbuilt = true;
        break;
    case 3:
        addr = APHash(ch_str) % tablesize;
        while (H->APelem[addr] != NULL)//不为空则有冲突
        {
            addr = (addr + 1) % tablesize; //这里使用开放定址法的线性探测
            if (t == 0) {
                conrace.APr++;
            }
            t++;
        }
        H->APelem[addr] = pperInfo; //直到有空位后插入
        H->APbuilt = true;
        break;
    case 4:
        addr = RSHash(ch_str) % tablesize;
        while (H->RSelem[addr] != NULL)//不为空则有冲突
        {
            addr = (addr + 1) % tablesize; //这里使用开放定址法的线性探测
            if (t == 0) {
                conrace.RSr++;
            }
            t++;
        }
        H->RSelem[addr] = pperInfo; //直到有空位后插入
        H->RSbuilt = true;
        break;
    case 5:
        addr = SDBMHash(ch_str) % tablesize;
        while (H->SDBMelem[addr] != NULL)//不为空则有冲突
        {
            addr = (addr + 1) % tablesize; //这里使用开放定址法的线性探测
            if (t == 0) {
                conrace.SDBr++;
            }
            t++;
        }
        H->SDBMelem[addr] = pperInfo; //直到有空位后插入
        H->SDBMbuilt = true;
        break;
    case 6:
        addr = PJWHash(ch_str) % tablesize;
        while (H->PJWelem[addr] != NULL)//不为空则有冲突
        {
            addr = (addr + 1) % tablesize; //这里使用开放定址法的线性探测
            if (t == 0) {
                conrace.PJWr++;
            }
            t++;
        }
        H->PJWelem[addr] = pperInfo; //直到有空位后插入
        H->PJWbuilt = true;
        break;

    }
    
}


bool hashpro::OpSearchHash(const string key, const hash_type Htype, perInfo &addr)
{
    char ch_str[] = { 0 };
    unsigned int index = 0;
    strcpy(ch_str, (key).c_str()); 
    switch (Htype)
    {
    case 1:
        index = BKDRHash(ch_str) % tablesize;
        while (H->BKDRelem[index]!=NULL) //如果不为key，则存在冲突
        {
            if (H->BKDRelem[index]->name != key) {
                index = (index + 1) % tablesize;  //开发定址法的线性探测
            }
            else {
                addr = *(H->BKDRelem[index]);
                return 1;
            }
        }
        break;
    case 2:
        index = JSHash(ch_str) % tablesize;
        while (H->JSelem[index] != NULL) //如果不为key，则存在冲突
        {
            if (H->JSelem[index]->name != key) {
                index = (index + 1) % tablesize;  //开发定址法的线性探测
            }
            else {
                addr = *(H->JSelem[index]);
                return 1;
            }
        }
        break;
    case 3:
        index = APHash(ch_str) % tablesize;
        while (H->JSelem[index] != NULL) //如果不为key，则存在冲突
        {
            if (H->JSelem[index]->name != key) {
                index = (index + 1) % tablesize;  //开发定址法的线性探测
            }
            else {
                addr = *(H->JSelem[index]);
                return 1;
            }
        }
        break;
    case 4:
        index = RSHash(ch_str) % tablesize;
        while (H->RSelem[index] != NULL) //如果不为key，则存在冲突
        {
            if (H->RSelem[index]->name != key) {
                index = (index + 1) % tablesize;  //开发定址法的线性探测
            }
            else {
                addr = *(H->RSelem[index]);
                return 1;
            }
        }
        break;
    case 5:
        index = SDBMHash(ch_str) % tablesize;
        while (H->SDBMelem[index] != NULL) //如果不为key，则存在冲突
        {
            if (H->SDBMelem[index]->name != key) {
                index = (index + 1) % tablesize;  //开发定址法的线性探测
            }
            else {
                addr = *(H->SDBMelem[index]);
                return 1;
            }
        }
        break;
    case 6:
        index = PJWHash(ch_str) % tablesize;
        while (H->PJWelem[index] != NULL) //如果不为key，则存在冲突
        {
            if (H->PJWelem[index]->name != key) {
                index = (index + 1) % tablesize;  //开发定址法的线性探测
            }
            else {
                addr = *(H->PJWelem[index]);
                return 1;
            }
        }
        break;
    }
    
    return 0; //查找失败返回
}

bool hashpro::LiInsertHash(const perInfo* key, const hash_type Htype)
{
    char ch_str[] = { 0 };
    int addr = -1;
    strcpy(ch_str, (key->name).c_str());
    perInfo* pperInfo = new perInfo(*key);
    LinkHash* node = new LinkHash();
    LinkHash* temp;
    int t = 0;
    switch (Htype) {
    case 1:
        addr = BKDRHash(ch_str) % tablesize;
        temp = LH->BKDRelem[addr];
        if(temp != NULL && temp->info->name != key->name)//不为空则有冲突
        {
            Liconrace.BKDRr++;
        }
        node->info = pperInfo;
        node->next = temp;
        LH->BKDRelem[addr] = node;
        LH->BKDRbuilt = true;
        break;
    case 2:
        addr = JSHash(ch_str) % tablesize;
        temp = LH->JSelem[addr];
        if (temp != NULL && temp->info->name != key->name)//不为空则有冲突
        {
            Liconrace.JSr++;
        }
        node->info = pperInfo;
        node->next = temp;
        LH->JSelem[addr] = node;
        LH->JSbuilt = true;
        break;
    case 3:
        addr = APHash(ch_str) % tablesize;
        temp = LH->APelem[addr];
        if (temp != NULL && temp->info->name != key->name)//不为空则有冲突
        {
            Liconrace.APr++;
        }
        node->info = pperInfo;
        node->next = temp;
        LH->APelem[addr] = node;
        LH->APbuilt = true;
        break;
    case 4:
        addr = RSHash(ch_str) % tablesize;
        temp = LH->RSelem[addr];
        if (temp != NULL && temp->info->name != key->name)//不为空则有冲突
        {
            Liconrace.RSr++;
        }
        node->info = pperInfo;
        node->next = temp;
        LH->RSelem[addr] = node;
        LH->RSbuilt = true;
        break;
    case 5:
        addr = SDBMHash(ch_str) % tablesize;
        temp = LH->SDBMelem[addr];
        if (temp != NULL && temp->info->name != key->name)//不为空则有冲突
        {
            Liconrace.SDBr++;
        }
        node->info = pperInfo;
        node->next = temp;
        LH->SDBMelem[addr] = node;
        LH->SDBMbuilt = true;
        break;
    case 6:
        addr = PJWHash(ch_str) % tablesize;
        temp = LH->PJWelem[addr];
        if (temp != NULL && temp->info->name != key->name)//不为空则有冲突
        {
            Liconrace.PJWr++;
        }
        node->info = pperInfo;
        node->next = temp;
        LH->PJWelem[addr] = node;
        LH->PJWbuilt = true;
        break;
    }
    return 1;
}

bool hashpro::LiSearchHash(const string key, const hash_type Htype, perInfo& addr)
{
    char ch_str[] = { 0 };
    unsigned int index = 0;
    strcpy(ch_str, (key).c_str());
    LinkHash* temp;
    switch (Htype) {
    case 1:
        index = BKDRHash(ch_str) % tablesize;
        temp = LH->BKDRelem[index];
        while (temp != NULL)
        {
            if (temp->info->name == key) {
                addr = *(temp->info);
                return true;
            }
            temp = temp->next;
        }
        break;
    case 2:
        index = JSHash(ch_str) % tablesize;
        temp = LH->JSelem[index];
        while (temp != NULL)
        {
            if (temp->info->name == key) {
                addr = *(temp->info);
                return true;
            }
            temp = temp->next;
        }
        break;
    case 3:
        index = APHash(ch_str) % tablesize;
        temp = LH->APelem[index];
        while (temp != NULL)
        {
            if (temp->info->name == key) {
                addr = *(temp->info);
                return true;
            }
            temp = temp->next;
        }
        break;
    case 4:
        index = RSHash(ch_str) % tablesize;
        temp = LH->RSelem[index];
        while (temp != NULL)
        {
            if (temp->info->name == key) {
                addr = *(temp->info);
                return true;
            }
            temp = temp->next;
        }
        break;
    case 5:
        index = SDBMHash(ch_str) % tablesize;
        temp = LH->SDBMelem[index];
        while (temp != NULL)
        {
            if (temp->info->name == key) {
                addr = *(temp->info);
                return true;
            }
            temp = temp->next;
        }
        break;
    case 6:
        index = PJWHash(ch_str) % tablesize;
        temp = LH->PJWelem[index];
        while (temp != NULL)
        {
            if (temp->info->name == key) {
                addr = *(temp->info);
                return true;
            }
            temp = temp->next;
        }
        break;
    }
    return false;
}

bool hashpro::PuInsertHash(const perInfo* key, const hash_type Htype)
{
    char ch_str[] = { 0 };
    int addr = -1;
    strcpy(ch_str, (key->name).c_str());
    perInfo* pperInfo = new perInfo(*key);
    LinkHash* node = new LinkHash();
    LinkHash* temp;
    int t = 0;
    switch (Htype) {
    case 1:
        addr = BKDRHash(ch_str) % tablesize;
        temp = PH->PuBKDRelem[addr];
        if (PH->BKDRelem[addr] != NULL && PH->BKDRelem[addr]->name != key->name)//不为空则有冲突
        {
            node->info = pperInfo;
            node->next = temp;
            PH->PuBKDRelem[addr] = node;
            PH->BKDRbuilt = true;
            Puconrace.BKDRr++;
        }
        else {
            PH->BKDRelem[addr] = pperInfo; //直到有空位后插入
            PH->BKDRbuilt = true;
        }
        
        break;
    case 2:
        addr = JSHash(ch_str) % tablesize;
        temp = PH->PuJSelem[addr];
        if (PH->JSelem[addr] != NULL && PH->JSelem[addr]->name != key->name)//不为空则有冲突
        {
            node->info = pperInfo;
            node->next = temp;
            PH->PuJSelem[addr] = node;
            PH->JSbuilt = true;
            Puconrace.JSr++;
        }
        else {
            PH->JSelem[addr] = pperInfo; //直到有空位后插入
            PH->JSbuilt = true;
        }

        break;
    case 3:
        addr = APHash(ch_str) % tablesize;
        temp = PH->PuAPelem[addr];
        if (PH->APelem[addr] != NULL && PH->APelem[addr]->name != key->name)//不为空则有冲突
        {
            node->info = pperInfo;
            node->next = temp;
            PH->PuAPelem[addr] = node;
            PH->APbuilt = true;
            Puconrace.APr++;
        }
        else {
            PH->APelem[addr] = pperInfo; //直到有空位后插入
            PH->APbuilt = true;
        }

        break;
    case 4:
        addr = RSHash(ch_str) % tablesize;
        temp = PH->PuBKDRelem[addr];
        if (PH->RSelem[addr] != NULL && PH->RSelem[addr]->name != key->name)//不为空则有冲突
        {
            node->info = pperInfo;
            node->next = temp;
            PH->PuRSelem[addr] = node;
            PH->RSbuilt = true;
            Puconrace.RSr++;
        }
        else {
            PH->RSelem[addr] = pperInfo; //直到有空位后插入
            PH->RSbuilt = true;
        }

        break;
    case 5:
        addr = SDBMHash(ch_str) % tablesize;
        temp = PH->PuBKDRelem[addr];
        if (PH->SDBMelem[addr] != NULL && PH->SDBMelem[addr]->name != key->name)//不为空则有冲突
        {
            node->info = pperInfo;
            node->next = temp;
            PH->PuSDBMelem[addr] = node;
            PH->SDBMbuilt = true;
            Puconrace.SDBr++;
        }
        else {
            PH->SDBMelem[addr] = pperInfo; //直到有空位后插入
            PH->SDBMbuilt = true;
        }

        break;
    case 6:
        addr = PJWHash(ch_str) % tablesize;
        temp = PH->PuPJWelem[addr];
        if (PH->PJWelem[addr] != NULL && PH->PJWelem[addr]->name != key->name)//不为空则有冲突
        {
            node->info = pperInfo;
            node->next = temp;
            PH->PuPJWelem[addr] = node;
            PH->PJWbuilt = true;
            Puconrace.PJWr++;
        }
        else {
            PH->PJWelem[addr] = pperInfo; //直到有空位后插入
            PH->PJWbuilt = true;
        }

        break;
    
    }
    return true;
}

bool hashpro::PuSearchHash(const string key, const hash_type Htype, perInfo& addr)
{
    char ch_str[] = { 0 };
    unsigned int index = 0;
    strcpy(ch_str, (key).c_str());
    LinkHash* temp;
    switch (Htype)
    {
    case 1:
        index = BKDRHash(ch_str) % tablesize;
        if (PH->BKDRelem[index] != NULL && PH->BKDRelem[index]->name != key) //如果不为key，则存在冲突
        {
            index = (index + 1) % tablesize;  //开发定址法的线性探测
            temp = PH->PuBKDRelem[index];
            while (temp != NULL)
            {
                if (temp->info->name == key) {
                    addr = *(temp->info);
                    return true;
                }
                temp = temp->next;
            }
        }
        else {
            addr = *(PH->BKDRelem[index]);
            return true;
        }
        break;
    case 2:
        index = JSHash(ch_str) % tablesize;
        if (PH->JSelem[index] != NULL && PH->JSelem[index]->name != key) //如果不为key，则存在冲突
        {
            index = (index + 1) % tablesize;  //开发定址法的线性探测
            temp = PH->PuJSelem[index];
            while (temp != NULL)
            {
                if (temp->info->name == key) {
                    addr = *(temp->info);
                    return true;
                }
                temp = temp->next;
            }
        }
        else {
            addr = *(PH->JSelem[index]);
            return true;
        }
        break;
    case 3:
        index = APHash(ch_str) % tablesize;
        if (PH->APelem[index] != NULL && PH->APelem[index]->name != key) //如果不为key，则存在冲突
        {
            index = (index + 1) % tablesize;  //开发定址法的线性探测
            temp = PH->PuAPelem[index];
            while (temp != NULL)
            {
                if (temp->info->name == key) {
                    addr = *(temp->info);
                    return true;
                }
                temp = temp->next;
            }
        }
        else {
            addr = *(PH->APelem[index]);
            return true;
        }
        break;
    case 4:
        index = RSHash(ch_str) % tablesize;
        if (PH->RSelem[index] != NULL && PH->RSelem[index]->name != key) //如果不为key，则存在冲突
        {
            index = (index + 1) % tablesize;  //开发定址法的线性探测
            temp = PH->PuRSelem[index];
            while (temp != NULL)
            {
                if (temp->info->name == key) {
                    addr = *(temp->info);
                    return true;
                }
                temp = temp->next;
            }
        }
        else {
            addr = *(PH->RSelem[index]);
            return true;
        }
        break;
    case 5:
        index = SDBMHash(ch_str) % tablesize;
        if (PH->SDBMelem[index] != NULL && PH->SDBMelem[index]->name != key) //如果不为key，则存在冲突
        {
            index = (index + 1) % tablesize;  //开发定址法的线性探测
            temp = PH->PuSDBMelem[index];
            while (temp != NULL)
            {
                if (temp->info->name == key) {
                    addr = *(temp->info);
                    return true;
                }
                temp = temp->next;
            }
        }
        else {
            addr = *(PH->SDBMelem[index]);
            return true;
        }
        break;
    case 6:
        index = PJWHash(ch_str) % tablesize;
        if (PH->PJWelem[index] != NULL && PH->PJWelem[index]->name != key) //如果不为key，则存在冲突
        {
            index = (index + 1) % tablesize;  //开发定址法的线性探测
            temp = PH->PuPJWelem[index];
            while (temp != NULL)
            {
                if (temp->info->name == key) {
                    addr = *(temp->info);
                    return true;
                }
                temp = temp->next;
            }
        }
        else {
            addr = *(PH->PJWelem[index]);
            return true;
        }
        break;
    }
    return false;
}

unsigned int hashpro::BKDRHash(char* str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

unsigned int hashpro::JSHash(char* str)
{
    unsigned int hash = 1315423911;

    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

unsigned int hashpro::APHash(char* str)
{
    unsigned int hash = 0;
    int i;
    for (i = 0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }
    return (hash & 0x7FFFFFFF);
}

unsigned int hashpro::RSHash(char* str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }
    return (hash & 0x7FFFFFFF);
}

unsigned int hashpro::SDBMHash(char* str)
{
    unsigned int hash = 0;

    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

unsigned int hashpro::PJWHash(char* str)
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int)((BitsInUnignedInt * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;

    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters))& (~HighBits));
        }
    }
    return (hash & 0x7FFFFFFF);
}

