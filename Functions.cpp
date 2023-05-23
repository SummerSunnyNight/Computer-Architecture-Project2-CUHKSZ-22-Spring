#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include<iostream>
#include<map>
#include "Functions.h"
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<bitset>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<regex>
#include<cstdio>
#include<set>
using namespace std;
map<string, string> ResMap = { {"$zero","00000"},{"$at","00001"},{"$v0","00010"},{"$v1","00011"},{"$a0","00100"},{"$a1","00101"},{"$a2","00110"},{"$a3","00111"},{"$t0","01000"},{"$t1","01001"},{"$t2","01010"},{"$t3","01011"},{"$t4","01100"},{"$t5","01101"},{"$t6","01110"},{"$t7","01111"},{"$s0","10000"},{"$s1","10001"},{"$s2","10010"},{"$s3","10011"},{"$s4","10100"},{"$s5","10101"},{"$s6","10110"},{"$s7","10111"},{"$t8","11000"},{"$t9","11001"},{"$k0","11010"},{"$k1","11011"},{"$gp","11100"},{"$sp","11101"},{"$fp","11110"},{"$ra","11111"} };
//map<string,int>

set<int> init_checkpoints(char* checkpoint_file) {
	FILE* fp = fopen(checkpoint_file, "r");
	int tmp, i = 0;
	set<int>checkpoints;
	while (fscanf(fp, "%d", &tmp) != EOF) {
		checkpoints.insert(tmp);
	}
	return checkpoints;
}
void checkpoint_memory(int ins_count, char* SixMbMemory,set<int>checkpoints) {
	if (!checkpoints.count(ins_count))
		return;
	string name = "memory_" + std::to_string(ins_count) + ".bin";
	FILE* fp = fopen(name.c_str(), "wb");
	fwrite(SixMbMemory, 1, 0x600000, fp);
	fclose(fp);

}
void checkpoint_register(int ins_count, char* SixMbMemory, int* registers, int* PC, int* OtherRegisters, set<int>checkpoints) {
	if (!checkpoints.count(ins_count))
		return;
	std::string name = "register_" + std::to_string(ins_count) + ".bin";
	FILE* fp = fopen(name.c_str(), "wb");

	fwrite(registers, 4, 1, fp);
	fwrite(registers + 1, 4, 1, fp);
	fwrite(registers + 2, 4, 1, fp);
	fwrite(registers + 3, 4, 1, fp);
	fwrite(registers + 4, 4, 1, fp);
	fwrite(registers + 5, 4, 1, fp);
	fwrite(registers + 6, 4, 1, fp);
	fwrite(registers + 7, 4, 1, fp);
	fwrite(registers + 8, 4, 1, fp);
	fwrite(registers + 9, 4, 1, fp);
	fwrite(registers + 10, 4, 1, fp);
	fwrite(registers + 11, 4, 1, fp);
	fwrite(registers + 12, 4, 1, fp);
	fwrite(registers + 13, 4, 1, fp);
	fwrite(registers + 14, 4, 1, fp);
	fwrite(registers + 15, 4, 1, fp);
	fwrite(registers + 16, 4, 1, fp);
	fwrite(registers + 17, 4, 1, fp);
	fwrite(registers + 18, 4, 1, fp);
	fwrite(registers + 19, 4, 1, fp);
	fwrite(registers + 20, 4, 1, fp);
	fwrite(registers + 21, 4, 1, fp);
	fwrite(registers + 22, 4, 1, fp);
	fwrite(registers + 23, 4, 1, fp);
	fwrite(registers + 24, 4, 1, fp);

	fwrite(registers + 25, 4, 1, fp);
	fwrite(registers + 26, 4, 1, fp);
	fwrite(registers + 27, 4, 1, fp);
	fwrite(registers + 28, 4, 1, fp);
	fwrite(registers + 29, 4, 1, fp);
	fwrite(registers + 30, 4, 1, fp);
	fwrite(registers + 31, 4, 1, fp);
	fwrite(PC, 4, 1, fp);
	fwrite(OtherRegisters, 4, 1, fp);
	fwrite(OtherRegisters + 1, 4, 1, fp);
	fclose(fp);
}
template<std::size_t B>
long bitset_to_long(const std::bitset<B>& b) {
	struct { long x : B; } s;
	return s.x = b.to_ulong();
}

void SplitStringIntoVector(string shuaige, vector<string>& CodeIn) {
	stringstream ss(shuaige);
	string tmp;

	while (getline(ss, tmp, ' ')) {
		CodeIn.push_back(tmp);

	}
}
string CommaReplaceEraseSpace(string str) {
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (str[i] == ',')
		{
			str[i] = ' ';
		}
	}
	for (int i = str.size() - 1; i >= 1; i--)
	{
		if (str[i] == ' ' && str[i] == str[i - 1])
		{
			str.erase(str.begin() + i);
		}
	}

	return str;
}
string Trim(string shuaige) {
	if (shuaige == "")return shuaige;
	shuaige = shuaige.substr(shuaige.find_first_not_of(" "), shuaige.find_last_not_of(" ") - shuaige.find_first_not_of(" ") + 1);
	for (int i = shuaige.size() - 1; i >= 0; i--)
	{
		if (shuaige[i] == '\t')
		{
			shuaige.erase(shuaige.begin() + i);
		}
	}

	return shuaige;
}
string ClearTheComment(string shuaige) {//clear the comment and \n 


	int kk = 0; // start of string counter
	int length = shuaige.length();
	string newstring = "";
	int i = 1;
	while (i < shuaige.length()) {
		if (shuaige[i - 1] == '\\' && shuaige[i] == 'n') {
			if (i == length - 2) {
				newstring = newstring + '\n' + shuaige[i + 1];
				i = i + 2;
			}
			else {
				newstring = newstring + '\n';
				i = i + 2;
			}

		}
		else {
			if (i == shuaige.length() - 1) {
				newstring = newstring + shuaige[i - 1] + shuaige[i];
				i = i + 1;
			}
			else {
				newstring = newstring + shuaige[i - 1];
				i = i + 1;
			}


		}
	}
	shuaige = newstring;

	// read the string word by word, stop if it reach the end or meet the comment
	while (kk < length && shuaige[kk] != '#') kk++;

	//delete the comment(if it has) and return
	return shuaige.substr(0, kk);
}
int ReadTextintoMemory(char* textstart, string binaryfilename) {
	ifstream fin;
	string shuaige;
	vector<vector<string>>Data;
	fin.open(binaryfilename);
	int textlines = 0;
	//First Scan:Load in the codes, clear the comments and blank lines

	/*10110000110000000000000100001000
	10101111101111110000000000001000*/

	int RelativeCounter = 1; //count the current location
	char* PC = textstart;
	while (std::getline(fin, shuaige)) {
		bitset<32> Toconvert(shuaige);
		string medium = Toconvert.to_string();
		char lowest = bitset_to_long(bitset<8>(medium.substr(24, 8)));
		char lower = bitset_to_long(bitset<8>(medium.substr(16, 8)));
		char higher = bitset_to_long(bitset<8>(medium.substr(8, 8)));
		char highest = bitset_to_long(bitset<8>(medium.substr(0, 8)));
		PC[0] = lowest;
		PC[1] = lower;
		PC[2] = higher;
		PC[3] = highest;
		PC = PC + 4;
		textlines = textlines + 1;
	}
	return textlines;
}
char* ReadintoMemory(char* DataPointer, string Filename) {
	ifstream fin;
	string shuaige;
	vector<vector<string>>Data;
	fin.open(Filename);

	//First Scan:Load in the codes, clear the comments and blank lines

	while (shuaige.find(".data") == -1)getline(fin, shuaige);//get to the location of the text



	int RelativeCounter = 1; //count the current location

	while (std::getline(fin, shuaige)) {//read till the end

		shuaige = ClearTheComment(shuaige);//clear the comments
		if (shuaige.find_first_not_of(' ') != string::npos) {//check whether it is empty line,if not,then load the codes

			vector<string> DataIn;//Load one line of Data into this vector

			shuaige = Trim(shuaige);
			if (shuaige.find(":") != -1) {//catch the label


				shuaige = shuaige.substr(shuaige.find(":") + 1);//filter the label from the line

			}
			shuaige = Trim(shuaige);//erase the outer spaces and /t
			//examine rest of line
			if (shuaige.find("ascii") != -1) {
				vector<string>temp;
				stringstream pp;
				pp << shuaige;
				string type;
				pp >> type;
				temp.push_back(type);
				string content = shuaige.substr(shuaige.find("\"") + 1, shuaige.rfind("\"") - shuaige.find("\"") - 1);
				temp.push_back(content);
				Data.push_back(temp);
			}


			else {
				shuaige = CommaReplaceEraseSpace(shuaige);
				if (shuaige.find(".text") != -1)break;
				if (shuaige.find_first_not_of(' ') != string::npos) {//if the line contain codes,then split the code into vector,PC+4. If the rest part contain nothing, pass
					SplitStringIntoVector(shuaige, DataIn); //split the code into vector
					Data.push_back(DataIn);//store this line vector into the general vector

				}
			}


		}

	}
	//Reading Start
	char* PC = DataPointer;

	for (vector<string> VecIter : Data) {
		if (VecIter[0] == ".ascii") {
			int RealLength = VecIter[1].size();
			int IntDivide = RealLength / 4;
			int Memorylength;
			if (IntDivide * 4 != RealLength) {
				Memorylength = (RealLength / 4 + 1) * 4;
			}
			else {
				Memorylength = RealLength;
			}

			for (int i = 0; i < RealLength; i++) {
				PC[i] = VecIter[1][i];
			}

			PC = PC + Memorylength;
		}
		else if (VecIter[0] == ".asciiz") {
			int RealLength = VecIter[1].size() + 1;
			int IntDivide = RealLength / 4;
			int Memorylength;
			if (IntDivide * 4 != RealLength) {
				Memorylength = (RealLength / 4 + 1) * 4;
			}
			else {
				Memorylength = RealLength;
			}

			for (int i = 0; i < RealLength - 1; i++) {
				PC[i] = VecIter[1][i];
			}
			PC[RealLength - 1] = 0;
			PC = PC + Memorylength;
		}
		else if (VecIter[0] == ".word") {
			int Finalwordindex = VecIter.size() - 1;
			for (int i = 1; i <= Finalwordindex; i++) {

				char lowest = stoi(VecIter[i]) % 0x1000000;
				char lower = stoi(VecIter[i]) % 0x10000 / 0x100;
				char higher = stoi(VecIter[i]) / 0x10000 % 0x100;
				char highest = stoi(VecIter[i]) / 0x1000000;
				PC[0] = lowest;
				PC[1] = lower;
				PC[2] = higher;
				PC[3] = highest;
				PC = PC + 4;
			}
		}
		else if (VecIter[0] == ".half") {
			int Finalhalfindex = VecIter.size() - 1;
			int Inword = (2 * (VecIter.size() - 1)) / 4;//Inword��byte size����4
			for (int i = 1; i <= Finalhalfindex; i++) {


				char low = stoi(VecIter[i]) % 0x100;
				char high = stoi(VecIter[i]) / 0x100;
				PC[0] = low;
				PC[1] = high;
				PC = PC + 2;
			}

			if (Inword * 4 < 2 * (VecIter.size() - 1))PC = PC + 2;
		}
		else if (VecIter[0] == ".byte") {
			int Finalhalfindex = VecIter.size() - 1;
			int Inword = (VecIter.size() - 1) / 4;//Inword��size����4

			for (int i = 1; i <= Finalhalfindex; i++) {

				char byte = stoi(VecIter[i]);

				PC[i - 1] = byte;

			}
			if (Inword * 4 == VecIter.size() - 1)PC = PC + VecIter.size() - 1;
			else if (Inword * 4 < VecIter.size() - 1)PC = PC + (Inword + 1) * 4;


		}

	}
	return PC;
}
void Process(int* registers, char*& PC, int* OtherRegisters, string machinecode, ifstream& shuaige1, ofstream& shuaige2, char* SixMbMemory, char*& dynamicdatapointer, int& times, int& flag) {
	times = times + 1;
	if (machinecode.substr(0, 6) == "000000") {//R type
		if (machinecode.substr(26, 6) == "100000") {//add

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = registers[rs] + registers[rt];
		}
		else if (machinecode.substr(26, 6) == "100001") {//addu
			//get the number of the registers
			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = registers[rs] + registers[rt];
		}
		else if (machinecode.substr(26, 6) == "100100") {//and

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = (registers[rs] & registers[rt]);
		}
		else if (machinecode.substr(26, 6) == "100111") {//nor

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = ~(registers[rs] | registers[rt]);
		}
		else if (machinecode.substr(26, 6) == "100101") {//or

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = (registers[rs] | registers[rt]);
		}
		else if (machinecode.substr(26, 6) == "101010") {//slt

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = (registers[rs] < registers[rt]);
		}
		else if (machinecode.substr(26, 6) == "101011") {//sltu

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = ((unsigned int)(registers[rs]) < (unsigned int)(registers[rt]));
		}
		else if (machinecode.substr(26, 6) == "100010") {//sub

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = registers[rs] - registers[rt];
		}
		else if (machinecode.substr(26, 6) == "100011") {//subu

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = registers[rs] - registers[rt];
		}
		else if (machinecode.substr(26, 6) == "100110") {//Xor

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = registers[rs] ^ registers[rt];
		}
		else if (machinecode.substr(26, 6) == "011010") {//div

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			//Hi
			OtherRegisters[0] = registers[rs] % registers[rt];
			//Lo
			OtherRegisters[1] = registers[rs] / registers[rt];

		}
		else if (machinecode.substr(26, 6) == "011011") {//divu

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			//Hi
			OtherRegisters[0] = registers[rs] % registers[rt];
			//Lo
			OtherRegisters[1] = registers[rs] / registers[rt];

		}
		else if (machinecode.substr(26, 6) == "011000") {//Mult

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			long long medium = registers[rs] * registers[rt];

			//Hi
			OtherRegisters[0] = int(medium / 0x10000);
			//Lo
			OtherRegisters[1] = int(medium);

		}
		else if (machinecode.substr(26, 6) == "011001") {//Multu

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			long long medium = registers[rs] * registers[rt];

			//Hi
			OtherRegisters[0] = int(medium / 0x10000);
			//Lo
			OtherRegisters[1] = int(medium);

		}
		else if (machinecode.substr(26, 6) == "001001") {//jalr

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();

			registers[rd] = int(PC - SixMbMemory + 0x400000);
			PC = (char*)(registers[rs] + SixMbMemory - 0x400000);

		}
		else if (machinecode.substr(26, 6) == "001000") {//jr

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();


			PC = (char*)(registers[rs] + SixMbMemory - 0x400000);

		}
		else if (machinecode.substr(26, 6) == "010000") {//mfhi

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();


			registers[rd] = OtherRegisters[0];

		}
		else if (machinecode.substr(26, 6) == "010001") {//mthi

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();


			OtherRegisters[1] = registers[rs];

		}
		else if (machinecode.substr(26, 6) == "010011") {//mtlo

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();


			OtherRegisters[0] = registers[rs];
		}
		else if (machinecode.substr(26, 6) == "000000") {//sll

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			int sa = bitset<5>(machinecode.substr(21, 5)).to_ullong();

			registers[rd] = registers[rt] << sa;
		}
		else if (machinecode.substr(26, 6) == "000100") {//sllv

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			int sa = bitset<5>(machinecode.substr(21, 5)).to_ullong();

			registers[rd] = registers[rt] << registers[rs];
		}
		else if (machinecode.substr(26, 6) == "000011") {//sra

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			int sa = bitset<5>(machinecode.substr(21, 5)).to_ullong();

			registers[rd] = registers[rt] >> sa;
		}
		else if (machinecode.substr(26, 6) == "000111") {//srav

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			int sa = bitset<5>(machinecode.substr(21, 5)).to_ullong();

			registers[rd] = registers[rt] >> registers[rs];
		}
		else if (machinecode.substr(26, 6) == "000010") {//srl

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			int sa = bitset<5>(machinecode.substr(21, 5)).to_ullong();

			registers[rd] = (unsigned int)(registers[rt]) >> sa;
		}
		else if (machinecode.substr(26, 6) == "000110") {//srlv

			int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
			int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
			int rd = bitset<5>(machinecode.substr(16, 5)).to_ullong();
			int sa = bitset<5>(machinecode.substr(21, 5)).to_ullong();

			registers[rd] = (unsigned int)(registers[rt]) >> registers[rs];
		}
		else if (machinecode.substr(26, 6) == "001100") {//syscall//

			if (registers[2] == 1) {
				shuaige2 << registers[4];


			}
			else if (registers[2] == 4) {//
				char* stringaddress = (char*)(registers[4] - 0x400000 + SixMbMemory);
				while (*stringaddress != '\0') {
					shuaige2 << *stringaddress;
					stringaddress += 1;

				}

			}
			else if (registers[2] == 5) {
				string kk;
				getline(shuaige1, kk);
				registers[2] = stoi(kk);
			}
			else if (registers[2] == 8) {
				string kk;
				getline(shuaige1, kk);

				string Readin = kk.substr(0, registers[5]);
				char* character = (char*)((registers[4] - 0x400000) + SixMbMemory);
				int i = 0;
				while (i < registers[5]) {
					if (Readin[i] == '\0')break;
					*character = Readin[i];
					character++;
					i++;
				}
				*character = '\0';
			}
			else if (registers[2] == 9) {//sbrk
				registers[2] = int(dynamicdatapointer - SixMbMemory + 0x400000);

				dynamicdatapointer = dynamicdatapointer + registers[4];
			}
			else if (registers[2] == 10) {
				flag = 1;
			}


			else if (registers[2] == 11) {

				shuaige2 << char(registers[4]);

			}
			else if (registers[2] == 12) {
				string kk;
				getline(shuaige1, kk);
				registers[2] = kk[0];

			}
			else if (registers[2] == 13) {
				const char* filename = (char*)(SixMbMemory + registers[4] - 0x400000);
				

				registers[4] = open(filename, registers[5], registers[6]);
			

			}
			else if (registers[2] == 14) {
				registers[4] = read(registers[4], (char*)(registers[5] + SixMbMemory - 0x400000), registers[6]);


			}
			else if (registers[2] == 15) {
				registers[4] = write(registers[4], (char*)(registers[5] + SixMbMemory - 0x400000), (registers[6]));


			}
			else if (registers[2] == 16) {
				close(registers[4]);


			}
			else if (registers[2] == 17) {
				flag = 1;


			}

		}
	}

	//I type start
	else if (machinecode.substr(0, 6) == "001000") {//addi
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		registers[rt] = registers[rs] + imme;
	}
	else if (machinecode.substr(0, 6) == "001001") {//addiu
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		registers[rt] = registers[rs] + imme;
	}
	else if (machinecode.substr(0, 6) == "001100") {//andi
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		registers[rt] = registers[rs] & imme;
	}
	else if (machinecode.substr(0, 6) == "000100") {//beq
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		if (registers[rs] == registers[rt])PC = PC + imme * 4;
	}
	else if (machinecode.substr(0, 6) == "000001" && machinecode.substr(11, 5) == "00001") {//bgez
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		if (registers[rs] >= 0)PC = PC + imme * 4;
	}
	else if (machinecode.substr(0, 6) == "000111" && machinecode.substr(11, 5) == "00000") {//bgtz
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		if (registers[rs] > 0)PC = PC + imme * 4;
	}
	else if (machinecode.substr(0, 6) == "000110" && machinecode.substr(11, 5) == "00000") {//blez
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		if (registers[rs] <= 0)PC = PC + imme * 4;
	}
	else if (machinecode.substr(0, 6) == "000001" && machinecode.substr(11, 5) == "00000") {//bltz
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		if (registers[rs] < 0)PC = PC + imme * 4;
	}
	else if (machinecode.substr(0, 6) == "000101") {//bne
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));


		if (registers[rs] != registers[rt])PC = PC + imme * 4;
	}
	else if (machinecode.substr(0, 6) == "100000") {//lb
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		registers[rt] = (*(int8_t*)(registers[rs] - 0x400000 + SixMbMemory + imme));


	}




	else if (machinecode.substr(0, 6) == "100100") {//lbu
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		unsigned int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		registers[rt] = *((uint8_t*)((registers[rs]) - 0x400000 + SixMbMemory + imme));


	}
	else if (machinecode.substr(0, 6) == "100001") {//lh
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		registers[rt] = (*(int16_t*)(registers[rs] - 0x400000 + SixMbMemory + imme));


	}

	else if (machinecode.substr(0, 6) == "100101") {//lhu
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		registers[rt] = *(uint16_t*)(registers[rs] - 0x400000 + SixMbMemory + imme);


	}
	else if (machinecode.substr(0, 6) == "001111") {//lui
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		imme = imme & 0xffff;
		imme = imme << 16;
		registers[rt] = imme;



	}
	else if (machinecode.substr(0, 6) == "100011") {//lw
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		registers[rt] = *((int*)(registers[rs] + SixMbMemory - 0x400000 + imme));



	}
	else if (machinecode.substr(0, 6) == "001101") {//ori
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		registers[rt] = registers[rs] | imme;
	}
	else if (machinecode.substr(0, 6) == "101000") {//sb
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		uint8_t medium = uint8_t(registers[rt]);
		*((char*)(registers[rs] - 0x400000 + SixMbMemory + imme)) = medium;

	}
	else if (machinecode.substr(0, 6) == "001010") {//slti
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		registers[rt] = (registers[rs] < imme);

	}

	else if (machinecode.substr(0, 6) == "001011") {//sltiu
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		unsigned int imme = bitset<16>(machinecode.substr(16, 16)).to_ullong();
		registers[rt] = (unsigned(registers[rs]) < imme);

	}
	else if (machinecode.substr(0, 6) == "101001") {//sh
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		*((int16_t*)(registers[rs] - 0x400000 + SixMbMemory + imme)) = uint16_t(registers[rt]);

	}
	else if (machinecode.substr(0, 6) == "101011") {//sw
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		*((int*)(registers[rs] - 0x400000 + SixMbMemory + imme)) = (registers[rt]);

	}
	else if (machinecode.substr(0, 6) == "001110") {//xori////////////////////////////////////////////zero extended
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset<16>(machinecode.substr(16, 16)).to_ullong();
		registers[rt] = registers[rs] ^ imme;

	}
	else if (machinecode.substr(0, 6) == "100010") {//lwl
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		int leftnumbers = 4 - int(registers[rs] + imme) % 4;
		for (int i = 0; i < leftnumbers; i++) {
			*((char*)(registers[rt] + i)) = *((char*)(registers[rs] + imme - 0x400000 + (SixMbMemory)+i));
		}
	}
	else if (machinecode.substr(0, 6) == "100110") {//lwr
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		int rightnumbers = int(registers[rs] + imme) % 4;
		for (int i = 0; i < rightnumbers; i++) {
			*((char*)(registers[rt] + 3 - i)) = *((char*)(registers[rs] + imme - 0x400000 + (SixMbMemory)-i));

		}
	}
	else if (machinecode.substr(0, 6) == "101010") {//swl
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		int leftnumbers = 4 - int(registers[rs] + imme) % 4;
		for (int i = 0; i < leftnumbers; i++) {
			*((char*)(registers[rs] + imme - 0x400000 + (SixMbMemory)+i)) = *((char*)(registers[rt] + i));
		}


	}
	else if (machinecode.substr(0, 6) == "101110") {//swr
		int rs = bitset<5>(machinecode.substr(6, 5)).to_ullong();
		int rt = bitset<5>(machinecode.substr(11, 5)).to_ullong();
		int imme = bitset_to_long(bitset<16>(machinecode.substr(16, 16)));
		int rightnumbers = int(registers[rs] + imme) % 4;
		for (int i = 0; i < rightnumbers; i++) {
			*((char*)(registers[rs] + imme - 0x400000 + (SixMbMemory)-i)) = *((char*)(registers[rt] + 3 - i));

		}

	}
	//J type start
	else if (machinecode.substr(0, 6) == "000010") {//j

		int target = bitset_to_long(bitset<26>(machinecode.substr(6, 26)));
		PC = SixMbMemory + target * 4 - 0x400000;
	}
	else if (machinecode.substr(0, 6) == "000011") {//jal

		int target = bitset_to_long(bitset<26>(machinecode.substr(6, 26)));
		registers[31] = PC - SixMbMemory + 0x400000;
		PC = SixMbMemory + target * 4 - 0x400000;
		int PC1 = PC - SixMbMemory;

	}
}
