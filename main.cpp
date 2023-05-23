
#include "Functions.h"
#include<iostream>
#include<map>

#include<bitset>
#include<fstream>
using namespace std;


int main(int argc, char** argv) {


	//Store the port for file to file interaction
	string assemblycodesname;
	string binarycodesname;
	string checkpointsname;
	string IOoperations;
	string outputname;

	/*a-plus-b.asm
	a-plus-b.txt
	a-plus-b.in
	a-plus-b.out*/
	/*fib.asm
	fib.txt
	fib.in
	fib.out*/
	/*lw_sw.asm
	lw_sw.txt
	lw_sw.in
	lw_sw.out*/
	/*many.asm
	many.txt
	many_checkpts.txt
	many.in
	many.out*/
	/*memcpy-hello-world.asm
	memcpy-hello-world.txt
	memcpy-hello-world.in
	memcpy-hello-world.out*/


	//cin>>assemblycodesname;
	//cin >> binarycodesname;
	///*cin >> checkpoints = argv[3];*/
	//cin >> IOoperations;
	//cin >> outputname ;

	assemblycodesname = argv[1];
	binarycodesname = argv[2];
	checkpointsname = argv[3];
	IOoperations = argv[4];
	outputname = argv[5];

	//Setting Memory and Register

	int MemorySize = 6 * 1024 * 1024;
	char* SixMbMemory = new char[MemorySize]();
	//store the data in the int form
	char* DataStart = (SixMbMemory + 1024 * 1024);


	int RegisterSize = 32;
	int* Registers = new int[RegisterSize]();

	int OtherRegistersize = 2;
	int* OtherRegisters = new int[OtherRegistersize];
	//set the pointing register 
	//global pointer
	Registers[28] = int(0x508000);
	//stack pointer
	Registers[29] = int(0xa00000);
	//frame pointer
	Registers[30] = 0xa00000;

	//Set zero  registers
	Registers[0] = 0;

	//Set other registers
	char* PC;
	int* Hi = OtherRegisters;
	int* Lo = OtherRegisters + 1;


	//Read the data into the preserved memory
	char* dynamicdatapointer = ReadintoMemory(DataStart, assemblycodesname);
	//Read the binary file into the preserved memory
	int textlines = ReadTextintoMemory(SixMbMemory, binarycodesname);

	string machinecodeline;
	PC = SixMbMemory;
	//Perform the machine cycle
	//open the output file and the input file
	ifstream shuaige1(IOoperations);//shuaige1 represent the syscalls
	ofstream shuaige2(outputname);//shuaige2 represent the output
	
	//Used to exit
	/*int sign = 0;*/
	int times = 0;
	set<int>checkpoints = init_checkpoints((char*)checkpointsname.c_str());
	while (true) {
		int* PC1 = new int;
		int kk = (PC - SixMbMemory + 0x400000);
		PC1 = &kk;
		checkpoint_memory(times, SixMbMemory, checkpoints);
		checkpoint_register(times, SixMbMemory, Registers,PC1,OtherRegisters ,checkpoints);
		
		bitset<8>k4(PC[0]);
		bitset<8>k3(PC[1]);
		bitset<8>k2(PC[2]);
		bitset<8>k1(PC[3]);
		string machinecode = k1.to_string() + k2.to_string() + k3.to_string() + k4.to_string();
		PC = PC + 4;
		int flag = 0;
		Process(Registers, PC, OtherRegisters, machinecode, shuaige1, shuaige2, SixMbMemory, dynamicdatapointer, times, flag);
		if (flag == 1)break;



	}
	//close the outputfile and input file
	shuaige1.close();
	shuaige2.close();


}
