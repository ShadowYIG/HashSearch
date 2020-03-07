#include "HashProcessing.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <direct.h>
#include <QDebug>

hashpro::hashpro() 
{
	this->filename = "";
	this->info_size = 0;
	this->allname = "";
	this->allemail = "";
	this->allphone = "";
	this->tablesize = 0;
	this->strArray = new vector<perInfo*>();
	this->H = new HashTable();
	this->LH = new LinkHashTable();
	this->PH = new PuHashTable();
	this->tablesize = 175447;
	conrace = { 0,0,0,0,0,0 };
	Liconrace = { 0,0,0,0,0,0 };
	Puconrace = { 0,0,0,0,0,0 };
	builttime = { 0,0,0,0,0,0 };
	searchtime = { 0,0,0,0,0,0 };
	avsearchtime = { 0,0,0,0,0,0 };
	Libuilttime = { 0,0,0,0,0,0 };
	Liavsearchtime = { 0,0,0,0,0,0 };
	Pubuilttime = { 0,0,0,0,0,0 };
	Puavsearchtime = { 0,0,0,0,0,0 };
	//this->hextype = md5;
	//this->con_solu = aaa;
}

hashpro::hashpro(string& filename)
{
	this->filename = filename;
	this->info_size = 0;
	this->allname = "";
	this->allemail = "";
	this->allphone = "";
	this->tablesize = 0;
	this->strArray = new vector<perInfo*>();
	this->H = new HashTable();
	this->LH = new LinkHashTable();
	this->PH = new PuHashTable();
	this->tablesize = 175447;
	conrace = { 0,0,0,0,0,0 };
	Liconrace = { 0,0,0,0,0,0 };
	Puconrace = { 0,0,0,0,0,0 };
	builttime = { 0,0,0,0,0,0 };
	searchtime = { 0,0,0,0,0,0 };
	avsearchtime = { 0,0,0,0,0,0 };
	Libuilttime = { 0,0,0,0,0,0 };
	Liavsearchtime = { 0,0,0,0,0,0 };
	Pubuilttime = { 0,0,0,0,0,0 };
	Puavsearchtime = { 0,0,0,0,0,0 };
	readCsvFile();
	InitHashTable();
	//this->hextype = md5;
	//this->con_solu = aaa;
}

bool hashpro::randomCsvFile(int amount)
{
	ofstream outFile;
	outFile.open("data.csv", ios::out);
	if (!outFile) {
		return 0;
	}
	//�ټ���-����
	string NA1[444] = { "��", "Ǯ", "��", "��", "��", "��", "֣", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʩ", "��", "��", "��", "��", "��", "��", "κ", "��", "��", "��", "л", "��", "��", "��", "ˮ", "�", "��", "��", "��", "��", "��", "��", "��", "��", "��", "³", "Τ", "��", "��", "��", "��", "��", "��", "��", "��", "Ԭ", "��", "ۺ", "��", "ʷ", "��", "��", "��", "�", "Ѧ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʱ", "��", "Ƥ", "��", "��", "��", "��", "��", "Ԫ", "��", "��", "��", "ƽ", "��", "��", "��", "��", "��", "Ҧ", "��", "տ", "��", "��", "ë", "��", "��", "��", "��", "��", "�", "��", "��", "��", "��", "̸", "��", "é", "��", "��", "��", "��", "��", "��", "ף", "��", "��", "��", "��", "��", "��", "ϯ", "��", "��", "ǿ", "��", "·", "¦", "Σ", "��", "ͯ", "��", "��", "÷", "ʢ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "֧", "��", "��", "��", "¬", "Ī", "��", "��", "��", "��", "��", "��", "Ӧ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʯ", "��", "��", "ť", "��", "��", "��", "��", "��", "��", "½", "��", "��", "��", "��", "�", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ɽ", "��", "��", "��", "�", "��", "ȫ", "ۭ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ղ", "��", "��", "Ҷ", "��", "˾", "��", "۬", "��", "��", "��", "ӡ", "��", "��", "��", "��", "ۢ", "��", "��", "��", "��", "��", "��", "׿", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "˫", "��", "ݷ", "��", "��", "̷", "��", "��", "��", "��", "��", "��", "��", "Ƚ", "��", "۪", "Ӻ", "��", "�", "ɣ", "��", "�", "ţ", "��", "ͨ", "��", "��", "��", "��", "ۣ", "��", "��", "ũ", "��", "��", "ׯ", "��", "��", "��", "��", "��", "Ľ", "��", "��", "ϰ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "»", "��", "��", "Ź", "�", "��", "��", "ε", "Խ", "��", "¡", "ʦ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ɳ", "ؿ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "Ȩ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "۳", "Ϳ", "��", "��", "��", "��", "˧", "��", "��", "��", "��", "��", "��", "��", "Ĳ", "��", "٦", "��", "��", "ī", "��", "��", "��", "��", "��", "��", "١", "��", "��" };
	//�ټ���-����444+59=503
	string NA2[59] = { "��ٹ", "˾��", "�Ϲ�", "ŷ��", "�ĺ�", "���", "����", "����", "����", "�ʸ�", "ξ��", "����", "�̨", "��ұ", "����", "���", "����", "����", "̫��", "����", "����", "����", "��ԯ", "���", "����", "����", "����", "Ľ��", "����", "����", "˾ͽ", "˾��", "����", "˾��", "�ӳ�", "���", "��ľ", "����", "����", "���", "����", "����", "����", "�ذ�", "�й�", "�׸�", "����", "����", "����", "����", "����", "����", "΢��", "����", "����", "����", "����", "�Ϲ�", "����" };
	//���Գ�����
	string ME1m[140] = { "ΰ", "��", "��", "��", "��", "��", "ǿ", "��", "ƽ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "־", "��", "��", "��", "��", "ɽ", "��", "��", "��", "��", "��", "��", "��", "Ԫ", "ȫ", "��", "ʤ", "ѧ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "˳", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ï", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "׳", "��", "˼", "Ⱥ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ԣ", "��", "��", "��", "��", "��", "��", "��", "ǫ", "��", "��", "��", "֮", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ά", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʿ", "��", "��", "��", "��", "��", "��", "��", "��", "ʱ", "̩", "ʢ" };
	//Ů�Գ�����140+165=305
	string ME1f[165] = { "��", "��", "Ӣ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "֥", "��", "Ƽ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "÷", "��", "��", "��", "��", "��", "��", "ѩ", "��", "��", "��", "ϼ", "��", "��", "ݺ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�", "Ҷ", "�", "�", "�", "��", "��", "��", "��", "��", "ɺ", "ɯ", "��", "��", "��", "ٻ", "��", "�", "��", "�", "�", "ӱ", "¶", "��", "��", "�", "��", "��", "��", "��", "��", "��", "��", "ü", "��", "��", "��", "ޱ", "ݼ", "��", "�", "Է", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ܿ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "Ӱ", "��", "֦", "˼", "��", "��", "Ʈ", "��", "�", "��", "��", "��", "��", "��", "ɺ", "ɯ", "��", "��", "��", "ٻ", "��", "��", "��", "��", "Է", "�", "ܰ", "�", "��", "��", "��", "԰", "��", "ӽ", "��", "��", "��", "��", "ع", "��", "��", "��", "ˬ", "��", "��", "��", "ϣ" };

	string pho[43] = { "133", "149", "153", "173", "177", "180", "181", "189", "199", "130", "131", "132", "145", "155", "156", "166", "171", "175", "176", "185", "186", "166", "134", "135", "136", "137", "138", "139", "147", "150", "151", "152", "157", "158", "159", "172", "178", "182", "183", "184", "187", "188", "198" };
	string emails[14] = { "@gmail.com", "@yahoo.com", "@msn.com", "@hotmail.com", "@aol.com", "@ask.com", "@live.com", "@qq.com", "@0355.net", "@163.com", "@163.net", "@263.net", "@3721.net", "@yeah" };
	string adde[34] = { "������", "�����", "�Ϻ���", "������", "�ӱ�ʡ", "ɽ��ʡ", "����ʡ", "����ʡ", "������ʡ", "����ʡ", "�㽭ʡ", "����ʡ", "����ʡ", "����ʡ", "ɽ��ʡ", "����ʡ", "����ʡ", "����ʡ", "�㶫ʡ", "����ʡ", "�Ĵ�ʡ", "����ʡ", "����ʡ", "����ʡ", "����ʡ", "�ຣʡ", "̨��ʡ", "���ɹ�������", "����׳��������", "����������", "���Ļ���������", "�½�ά���������", "����ر�������", "�����ر�������" };
	string str = "1234567890qwertyuioplkjhgfdsazxcvbnm";

	//outFile << "name" << ',' << "phone" << ',' << "email" << ',' << "address" << endl;
	srand((int)time(0));
	int temp = 0;
	//string allname = "", allemail = "", allphone = "";
	for (int i = 0; i < amount; i++) {
		string name = "", phone = "", email = "", address = "";
		temp = rand() % 503;
		if (temp > 444) {
			temp -= 444;
			name = NA2[temp];
		}
		else {
			name = NA1[temp];
		}
		temp = rand() % 305;
		if (temp > 140) {
			temp -= 140;
			name = name + ME1f[temp];
		}
		else {
			name = name + ME1m[temp];
		}
		if ((rand() % 10) % 2 == 0) {
			temp = rand() % 305;
			if (temp > 140) {
				temp -= 140;
				name = name + ME1f[temp];
			}
			else {
				name = name + ME1m[temp];
			}
		}
		if (allname.find(name) != string::npos) {
			i = i - 1;
			continue;
		}
		allname = allname + ',' + name;
		//phone
		phone = pho[rand() % 43];
		for (int j = 0; j < 8; j++) {
			phone = phone + to_string(rand() % 10);
		}
		if (allphone.find(phone) != string::npos) {
			i = i - 1;
			continue;
		}
		allphone = allphone + ',' + phone;
		//email
		temp = (rand() % 11) + 5;
		for (int j = 0; j < temp; j++) {
			email = email + str.at(rand() % 36);
		}
		email = email + emails[rand() % 14];
		if (allemail.find(email) != string::npos) {
			i = i - 1;
			continue;
		}
		allemail = allemail + ',' + email;
		//addres
		address = adde[rand() % 33];
		cout << name << ',' << phone << ',' << email << ',' << address << endl;
		outFile << name << ',' << phone << ',' << email << ',' << address << endl;
	}
	outFile.close();
	char filepath[256];
	if (_getcwd(filepath, 256)==NULL) {
		return 1;//��ʱ�����Ƕ�����·�������
	}
	filename = (string)filepath+"\\data.csv";
	readCsvFile();
	InitHashTable();
	return 1;
}


bool hashpro::readCsvFile()
{
	ifstream inFile(filename, ios::in);
	string lineStr;
	//vector<vector<string>> strArray;
	if (!inFile) {
		return 0;
	}
	while (getline(inFile, lineStr))
	{

		//cout << lineStr << endl;
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		perInfo *pperInfo = new perInfo();
		int i = 0;
		while (getline(ss, str, ','))// �����ŷָ�
		{
			switch (i) {
				case 0:
					pperInfo->name = str;
				case 1:
					pperInfo->phone = str;
				case 2:
					pperInfo->email = str;
				case 3:
					pperInfo->address = str;
			}
			i++;
		}	
		info_size++;
		strArray->push_back(pperInfo);
	}
	inFile.close();
	return 1;
}

bool hashpro::addCsvDate(string &name, string &phone, string &email, string& address)
{
	ofstream outFile;
	if (filename == "") {
		return 0;
	}
	outFile.open(filename, ios::app);
	if (!outFile) {
		return 0;
	}
	if (allname.find(name) != string::npos) {
		return 0;
	}
	outFile << name << ',' << phone << ',' << email << ',' << address << endl;
	outFile.close();
	perInfo *pperInfo=new perInfo();
	pperInfo->name = name;
	pperInfo->phone = phone;
	pperInfo->email = email;
	pperInfo->address = address;
	allname = allname + ',' + name;
	strArray->push_back(pperInfo);
	if (H->BKDRbuilt) {
		perInfo* persionInfo = new perInfo(*pperInfo);
		OpInsertHash(persionInfo, BKDR);
	}
	if (H->JSbuilt) {
		perInfo* persionInfo = new perInfo(*pperInfo);
		OpInsertHash(persionInfo, JS);
	}
	if (H->APbuilt) {
		perInfo* persionInfo = new perInfo(*pperInfo);
		OpInsertHash(persionInfo, AP);
	}
	if (H->RSbuilt) {
		perInfo* persionInfo = new perInfo(*pperInfo);
		OpInsertHash(persionInfo, RS);
	}
	if (H->SDBMbuilt) {
		perInfo* persionInfo = new perInfo(*pperInfo);
		OpInsertHash(persionInfo, SDBM);
	}
	if (H->PJWbuilt) {
		perInfo* persionInfo = new perInfo(*pperInfo);
		OpInsertHash(persionInfo, PJW);
	}
	info_size++;
	return 1;
}

string hashpro::getFileName() 
{
	return filename;
}

void hashpro::PutFileName(string& filename)
{
	this->filename = filename;
}


Stime hashpro::getbuilttime(conflict_solution con_sol)
{
	if (con_sol == 1) {
		return builttime;
	}
	else if (con_sol == 2) {
		return Libuilttime;
	}
	else if (con_sol == 3) {
		return Pubuilttime;
	}
	return builttime;
}

Stime hashpro::getsearchtime()
{
	return searchtime;
}

Stime hashpro::getavgsearchtime(conflict_solution con_sol)
{
	if (con_sol == 1) {
		return avsearchtime;
	}
	else if (con_sol == 2) {
		return Liavsearchtime;
	}
	else if (con_sol == 3) {
		return Puavsearchtime;
	}
	return avsearchtime;
}

Sconrace hashpro::getConflictRate(conflict_solution con_sol)
{
	if (con_sol == 1) {
		return conrace;
	}
	else if (con_sol == 2) {
		return Liconrace;
	}
	else if (con_sol == 3) {
		return Puconrace;
	}
	return conrace;

}

int hashpro::getInfoSize()
{
	return info_size;
}

int hashpro::SearchInfo(const string& name, hash_type hex_type, conflict_solution con_sol, perInfo& persionInfo)
{
	MyTimer timer;
	switch (hex_type) {
	case 1:
		if (con_sol == 1) {
			if (!H->BKDRbuilt) {//�����ϣ��δ��������false
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {//����ַ��
			if (!LH->BKDRbuilt) {//�����ϣ��δ��������false
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {//����ַ��
			if (!PH->BKDRbuilt) {//�����ϣ��δ��������false
				return 0;
			}
			break;
		}

	case 2:
		if (con_sol == 1) {
			if (!H->JSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->JSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->JSbuilt) {
				return 0;
			}
			break;
		}

	case 3:
		if (con_sol == 1) {
			if (!H->APbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->APbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->APbuilt) {
				return 0;
			}
			break;
		}

	case 4:
		if (con_sol == 1) {
			if (!H->RSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->RSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->RSbuilt) {
				return 0;
			}
			break;
		}

	case 5:
		if (con_sol == 1) {
			if (!H->SDBMbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->SDBMbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->SDBMbuilt) {
				return 0;
			}
			break;
		}

	case 6:
		if (con_sol == 1) {
			if (!H->PJWbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->PJWbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->PJWbuilt) {
				return 0;
			}
			break;
		}


	}
	if (hex_type >= 0 && hex_type <= 6) {
		timer.Start();
		if (!SearchHash(name, hex_type, persionInfo, con_sol)) {
			return -1;
		}
		timer.End();
	}
	else {
		return 0;
	}
	switch (hex_type) {
	case 1:
		searchtime.BKDRtime = timer.costTime;
		break;
	case 2:
		searchtime.JStime = timer.costTime;
		break;
	case 3:
		searchtime.APtime = timer.costTime;
		break;
	case 4:
		searchtime.RStime = timer.costTime;
		break;
	case 5:
		searchtime.SDBMtime = timer.costTime;
		break;
	case 6:
		searchtime.PJWtime = timer.costTime;
		break;
	}
	return 1;
}

bool hashpro::BuiltTable(hash_type hex_type, conflict_solution con_sol)
{
	MyTimer timer;
	switch (hex_type) {
	case 1:
		if (con_sol == 1) {
			if (H->BKDRbuilt) {//�����ϣ���ѽ�������false
				return 0;
			}
			conrace.BKDRr = 0;
			break;
		}
		else if (con_sol == 2) {//����ַ��
			if (LH->BKDRbuilt) {//�����ϣ���ѽ�������false
				return 0;
			}
			Liconrace.BKDRr = 0;
			break;
		}
		else if (con_sol == 3) {//�����������
			if (PH->BKDRbuilt) {//�����ϣ���ѽ�������false
				return 0;
			}
			Puconrace.BKDRr = 0;
			break;
		}
		
	case 2:
		if (con_sol == 1) {
			if (H->JSbuilt) {
				return 0;
			}
			conrace.JSr = 0;
			break;
		}
		else if(con_sol == 2){
			if (LH->JSbuilt) {
				return 0;
			}
			Liconrace.JSr = 0;
			break;
		}
		else if (con_sol == 3) {
			if (PH->JSbuilt) {
				return 0;
			}
			Puconrace.JSr = 0;
			break;
		}
		
	case 3:
		if (con_sol == 1) {
			if (H->APbuilt) {
				return 0;
			}
			conrace.APr = 0;
			break;
		}
		else if (con_sol == 2) {
			if (LH->APbuilt) {
				return 0;
			}
			Liconrace.APr = 0;
			break;
		}
		else if (con_sol == 3) {
			if (PH->APbuilt) {
				return 0;
			}
			Puconrace.APr = 0;
			break;
		}
		
	case 4:
		if (con_sol == 1) {
			if (H->RSbuilt) {
				return 0;
			}
			conrace.RSr = 0;
			break;
		}
		else if (con_sol == 2) {
			if (LH->RSbuilt) {
				return 0;
			}
			Liconrace.RSr = 0;
			break;
		}
		else if (con_sol == 3) {
			if (PH->RSbuilt) {
				return 0;
			}
			Puconrace.RSr = 0;
			break;
		}
		
	case 5:
		if (con_sol == 1) {
			if (H->SDBMbuilt) {
				return 0;
			}
			conrace.SDBr = 0;
			break;
		}
		else if (con_sol == 2) {
			if (LH->SDBMbuilt) {
				return 0;
			}
			Liconrace.SDBr = 0;
			break;
		}
		else if (con_sol == 3) {
			if (PH->SDBMbuilt) {
				return 0;
			}
			Puconrace.SDBr = 0;
			break;
		}
		
	case 6:
		if (con_sol == 1) {
			if (H->PJWbuilt) {
				return 0;
			}
			conrace.PJWr = 0;
			break;
		}
		else if (con_sol == 2) {
			if (LH->PJWbuilt) {
				return 0;
			}
			Liconrace.PJWr = 0;
			break;
		}
		else if (con_sol == 3) {
			if (PH->PJWbuilt) {
				return 0;
			}
			Puconrace.PJWr = 0;
			break;
		}
	}
	if (hex_type >= 0 && hex_type <= 6) {
		timer.Start();
		for (vector<perInfo*>::iterator it = strArray->begin(); it != strArray->end(); it++) {
			InsertHash(*it, hex_type, con_sol);
		}
		timer.End();
	}
	else {
		return 0;
	}
	switch (hex_type) {
	case 1:
		if (con_sol == 1) {
			builttime.BKDRtime = timer.costTime;
		}
		else if(con_sol == 2) {
			Libuilttime.BKDRtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Pubuilttime.BKDRtime = timer.costTime;
		}
		break;
	case 2:
		if (con_sol == 1) {
			builttime.JStime = timer.costTime;
		}
		else if (con_sol == 2) {
			Libuilttime.JStime = timer.costTime;
		}
		else if (con_sol == 3) {
			Pubuilttime.JStime = timer.costTime;
		}
		break;
	case 3:
		if (con_sol == 1) {
			builttime.APtime = timer.costTime;
		}
		else if (con_sol == 2) {
			Libuilttime.APtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Pubuilttime.APtime = timer.costTime;
		}
		
		break;
	case 4:
		if (con_sol == 1) {
			builttime.RStime = timer.costTime;
		}
		else if (con_sol == 2) {
			Libuilttime.RStime = timer.costTime;
		}
		else if (con_sol == 3) {
			Pubuilttime.RStime = timer.costTime;
		}
		
		break;
	case 5:
		if (con_sol == 1) {
			builttime.SDBMtime = timer.costTime;
		}
		else if (con_sol == 2) {
			Libuilttime.SDBMtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Pubuilttime.SDBMtime = timer.costTime;
		}
		
		break;
	case 6:
		if (con_sol == 1) {
			builttime.PJWtime = timer.costTime;
		}
		else if (con_sol == 2) {
			Libuilttime.PJWtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Pubuilttime.PJWtime = timer.costTime;
		}
		break;
	}
	return 1;
}

bool hashpro::avgSearchTime(hash_type hex_type, conflict_solution con_sol)
{
	MyTimer timer;
	switch (hex_type) {
	case 1:
		if (con_sol == 1) {
			if (!H->BKDRbuilt) {//�����ϣ��δ��������false
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {//����ַ��
			if (!LH->BKDRbuilt) {//�����ϣ��δ��������false
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {//���������������
			if (!PH->BKDRbuilt) {//�����ϣ��δ��������false
				return 0;
			}
			break;
		}

	case 2:
		if (con_sol == 1) {
			if (!H->JSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->JSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->JSbuilt) {
				return 0;
			}
			break;
		}

	case 3:
		if (con_sol == 1) {
			if (!H->APbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->APbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->APbuilt) {
				return 0;
			}
			break;
		}

	case 4:
		if (con_sol == 1) {
			if (!H->RSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->RSbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->RSbuilt) {
				return 0;
			}
			break;
		}

	case 5:
		if (con_sol == 1) {
			if (!H->SDBMbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->SDBMbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->SDBMbuilt) {
				return 0;
			}
			break;
		}

	case 6:
		if (con_sol == 1) {
			if (!H->PJWbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {
			if (!LH->PJWbuilt) {
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {
			if (!PH->PJWbuilt) {
				return 0;
			}
			break;
		}
	}
	perInfo persionInfo;
	if (hex_type >= 0 && hex_type <= 6) {
		timer.Start();
		for (vector<perInfo*>::iterator it = strArray->begin(); it != strArray->end(); it++) {
			SearchHash((*it)->name, hex_type, persionInfo, con_sol);
		}
		timer.End();
	}
	else {
		return 0;
	}
	switch (hex_type) {
	case 1:
		if (con_sol == 1) {
			avsearchtime.BKDRtime = timer.costTime;
		}
		else if (con_sol == 2) {
			Liavsearchtime.BKDRtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Puavsearchtime.BKDRtime = timer.costTime;
		}
		
		break;
	case 2:
		if (con_sol == 1) {
			avsearchtime.JStime = timer.costTime;
		}
		else if (con_sol == 2) {
			Liavsearchtime.JStime = timer.costTime;
		}
		else if (con_sol == 3) {
			Puavsearchtime.JStime = timer.costTime;
		}

		
		break;
	case 3:
		if (con_sol == 1) {
			avsearchtime.APtime = timer.costTime;
		}
		else if (con_sol == 2) {
			Liavsearchtime.APtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Puavsearchtime.APtime = timer.costTime;
		}
		
		break;
	case 4:
		if (con_sol == 1) {
			avsearchtime.RStime = timer.costTime;
		}
		else if (con_sol == 2) {
			Liavsearchtime.RStime = timer.costTime;
		}
		else if (con_sol == 3) {
			Puavsearchtime.RStime = timer.costTime;
		}
		
		break;
	case 5:
		if (con_sol == 1) {
			avsearchtime.SDBMtime = timer.costTime;
		}
		else if (con_sol == 2) {
			Liavsearchtime.SDBMtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Puavsearchtime.SDBMtime = timer.costTime;
		}
		
		break;
	case 6:
		if (con_sol == 1) {
			avsearchtime.PJWtime = timer.costTime;
		}
		else if (con_sol == 2) {
			Liavsearchtime.PJWtime = timer.costTime;
		}
		else if (con_sol == 3) {
			Puavsearchtime.PJWtime = timer.costTime;
		}
		
		break;
	}
	return 1;
}

