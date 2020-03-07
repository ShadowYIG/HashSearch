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
	//百家姓-单姓
	string NA1[444] = { "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋", "沈", "韩", "杨", "朱", "秦", "尤", "许", "何", "吕", "施", "张", "孔", "曹", "严", "华", "金", "魏", "陶", "姜", "戚", "谢", "邹", "喻", "柏", "水", "窦", "章", "云", "苏", "潘", "葛", "奚", "范", "彭", "郎", "鲁", "韦", "昌", "马", "苗", "凤", "花", "方", "俞", "任", "袁", "柳", "酆", "鲍", "史", "唐", "费", "廉", "岑", "薛", "雷", "贺", "倪", "汤", "滕", "殷", "罗", "毕", "郝", "邬", "安", "常", "乐", "于", "时", "傅", "皮", "卞", "齐", "康", "伍", "余", "元", "卜", "顾", "孟", "平", "黄", "和", "穆", "萧", "尹", "姚", "邵", "湛", "汪", "祁", "毛", "禹", "狄", "米", "贝", "明", "臧", "计", "伏", "成", "戴", "谈", "宋", "茅", "庞", "熊", "纪", "舒", "屈", "项", "祝", "董", "梁", "杜", "阮", "蓝", "闵", "席", "季", "麻", "强", "贾", "路", "娄", "危", "江", "童", "颜", "郭", "梅", "盛", "林", "刁", "钟", "徐", "邱", "骆", "高", "夏", "蔡", "田", "樊", "胡", "凌", "霍", "虞", "万", "支", "柯", "昝", "管", "卢", "莫", "经", "房", "裘", "缪", "干", "解", "应", "宗", "丁", "宣", "贲", "邓", "郁", "单", "杭", "洪", "包", "诸", "左", "石", "崔", "吉", "钮", "龚", "程", "嵇", "邢", "滑", "裴", "陆", "荣", "翁", "荀", "羊", "於", "惠", "甄", "麴", "家", "封", "芮", "羿", "储", "靳", "汲", "邴", "糜", "松", "井", "段", "富", "巫", "乌", "焦", "巴", "弓", "牧", "隗", "山", "谷", "车", "侯", "宓", "蓬", "全", "郗", "班", "仰", "秋", "仲", "伊", "宫", "宁", "仇", "栾", "暴", "甘", "钭", "厉", "戎", "祖", "武", "符", "刘", "景", "詹", "束", "龙", "叶", "幸", "司", "韶", "郜", "黎", "蓟", "薄", "印", "宿", "白", "怀", "蒲", "邰", "从", "鄂", "索", "咸", "籍", "赖", "卓", "蔺", "屠", "蒙", "池", "乔", "阴", "郁", "胥", "能", "苍", "双", "闻", "莘", "党", "翟", "谭", "贡", "劳", "逄", "姬", "申", "扶", "堵", "冉", "宰", "郦", "雍", "舄", "璩", "桑", "桂", "濮", "牛", "寿", "通", "边", "扈", "燕", "冀", "郏", "浦", "尚", "农", "温", "别", "庄", "晏", "柴", "瞿", "阎", "充", "慕", "连", "茹", "习", "宦", "艾", "鱼", "容", "向", "古", "易", "慎", "戈", "廖", "庾", "终", "暨", "居", "衡", "步", "都", "耿", "满", "弘", "匡", "国", "文", "寇", "广", "禄", "阙", "东", "殴", "殳", "沃", "利", "蔚", "越", "夔", "隆", "师", "巩", "厍", "聂", "晁", "勾", "敖", "融", "冷", "訾", "辛", "阚", "那", "简", "饶", "空", "曾", "毋", "沙", "乜", "养", "鞠", "须", "丰", "巢", "关", "蒯", "相", "查", "後", "荆", "红", "游", "竺", "权", "逯", "盖", "益", "桓", "公", "仉", "督", "晋", "楚", "闫", "法", "汝", "鄢", "涂", "钦", "归", "海", "岳", "帅", "缑", "亢", "况", "后", "有", "琴", "商", "牟", "佘", "佴", "伯", "赏", "墨", "哈", "谯", "笪", "年", "爱", "阳", "佟", "言", "福" };
	//百家姓-复姓444+59=503
	string NA2[59] = { "万俟", "司马", "上官", "欧阳", "夏侯", "诸葛", "闻人", "东方", "赫连", "皇甫", "尉迟", "公羊", "澹台", "公冶", "宗政", "濮阳", "淳于", "单于", "太叔", "申屠", "公孙", "仲孙", "轩辕", "令狐", "钟离", "宇文", "长孙", "慕容", "鲜于", "闾丘", "司徒", "司空", "亓官", "司寇", "子车", "颛孙", "端木", "巫马", "公西", "漆雕", "乐正", "壤驷", "公良", "拓跋", "夹谷", "宰父", "谷梁", "百里", "东郭", "南门", "呼延", "羊舌", "微生", "梁丘", "左丘", "东门", "西门", "南宫", "第五" };
	//男性常用名
	string ME1m[140] = { "伟", "刚", "勇", "毅", "俊", "峰", "强", "军", "平", "保", "东", "文", "辉", "力", "明", "永", "健", "世", "广", "志", "义", "兴", "良", "海", "山", "仁", "波", "宁", "贵", "福", "生", "龙", "元", "全", "国", "胜", "学", "祥", "才", "发", "武", "新", "利", "清", "飞", "彬", "富", "顺", "信", "子", "杰", "涛", "昌", "成", "康", "星", "光", "天", "达", "安", "岩", "中", "茂", "进", "林", "有", "坚", "和", "彪", "博", "诚", "先", "敬", "震", "振", "壮", "会", "思", "群", "豪", "心", "邦", "承", "乐", "绍", "功", "松", "善", "厚", "庆", "磊", "民", "友", "裕", "河", "哲", "江", "超", "浩", "亮", "政", "谦", "亨", "奇", "固", "之", "轮", "翰", "朗", "伯", "宏", "言", "若", "鸣", "朋", "斌", "梁", "栋", "维", "启", "克", "伦", "翔", "旭", "鹏", "泽", "晨", "辰", "士", "以", "建", "家", "致", "树", "炎", "德", "行", "时", "泰", "盛" };
	//女性常用名140+165=305
	string ME1f[165] = { "秀", "娟", "英", "华", "慧", "巧", "美", "娜", "静", "淑", "惠", "珠", "翠", "雅", "芝", "玉", "萍", "红", "娥", "玲", "芬", "芳", "燕", "彩", "春", "菊", "兰", "凤", "洁", "梅", "琳", "素", "云", "莲", "真", "环", "雪", "荣", "爱", "妹", "霞", "香", "月", "莺", "媛", "艳", "瑞", "凡", "佳", "嘉", "琼", "勤", "珍", "贞", "莉", "桂", "娣", "叶", "璧", "璐", "娅", "琦", "晶", "妍", "茜", "秋", "珊", "莎", "锦", "黛", "青", "倩", "婷", "姣", "婉", "娴", "瑾", "颖", "露", "瑶", "怡", "婵", "雁", "蓓", "纨", "仪", "荷", "丹", "蓉", "眉", "君", "琴", "蕊", "薇", "菁", "梦", "岚", "苑", "筠", "柔", "竹", "霭", "凝", "晓", "欢", "霄", "枫", "芸", "菲", "寒", "欣", "滢", "伊", "亚", "宜", "可", "姬", "舒", "影", "荔", "枝", "思", "丽", "秀", "飘", "育", "馥", "琦", "晶", "妍", "茜", "秋", "珊", "莎", "锦", "黛", "青", "倩", "婷", "宁", "蓓", "纨", "苑", "婕", "馨", "瑗", "琰", "韵", "融", "园", "艺", "咏", "卿", "聪", "澜", "纯", "毓", "悦", "昭", "冰", "爽", "琬", "茗", "羽", "希" };

	string pho[43] = { "133", "149", "153", "173", "177", "180", "181", "189", "199", "130", "131", "132", "145", "155", "156", "166", "171", "175", "176", "185", "186", "166", "134", "135", "136", "137", "138", "139", "147", "150", "151", "152", "157", "158", "159", "172", "178", "182", "183", "184", "187", "188", "198" };
	string emails[14] = { "@gmail.com", "@yahoo.com", "@msn.com", "@hotmail.com", "@aol.com", "@ask.com", "@live.com", "@qq.com", "@0355.net", "@163.com", "@163.net", "@263.net", "@3721.net", "@yeah" };
	string adde[34] = { "北京市", "天津市", "上海市", "重庆市", "河北省", "山西省", "辽宁省", "吉林省", "黑龙江省", "江苏省", "浙江省", "安徽省", "福建省", "江西省", "山东省", "河南省", "湖北省", "湖南省", "广东省", "海南省", "四川省", "贵州省", "云南省", "陕西省", "甘肃省", "青海省", "台湾省", "内蒙古自治区", "广西壮族自治区", "西藏自治区", "宁夏回族自治区", "新疆维吾尔自治区", "香港特别行政区", "澳门特别行政区" };
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
		return 1;//暂时不考虑读不到路径的情况
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
		while (getline(ss, str, ','))// 按逗号分隔
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
			if (!H->BKDRbuilt) {//如果哈希表未建立返回false
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {//连地址法
			if (!LH->BKDRbuilt) {//如果哈希表未建立返回false
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {//连地址法
			if (!PH->BKDRbuilt) {//如果哈希表未建立返回false
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
			if (H->BKDRbuilt) {//如果哈希表已建立返回false
				return 0;
			}
			conrace.BKDRr = 0;
			break;
		}
		else if (con_sol == 2) {//连地址法
			if (LH->BKDRbuilt) {//如果哈希表已建立返回false
				return 0;
			}
			Liconrace.BKDRr = 0;
			break;
		}
		else if (con_sol == 3) {//公共溢出区法
			if (PH->BKDRbuilt) {//如果哈希表已建立返回false
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
			if (!H->BKDRbuilt) {//如果哈希表未建立返回false
				return 0;
			}
			break;
		}
		else if (con_sol == 2) {//连地址法
			if (!LH->BKDRbuilt) {//如果哈希表未建立返回false
				return 0;
			}
			break;
		}
		else if (con_sol == 3) {//建立公共溢出区法
			if (!PH->BKDRbuilt) {//如果哈希表未建立返回false
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

