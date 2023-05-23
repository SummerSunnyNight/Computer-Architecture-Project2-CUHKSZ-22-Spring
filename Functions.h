#include<vector>
#include<fstream>
#include<bitset>
#include<set>
using namespace std;




set<int> init_checkpoints(char* checkpoint_file);
void checkpoint_memory(int ins_count, char* SixMbMemory, set<int>checkpoints);
void checkpoint_register(int ins_count, char* SixMbMemory, int* registers, int* PC, int* OtherRegisters, set<int>checkpoints);

extern int sign;

template<std::size_t B>
long bitset_to_long(const std::bitset<B>& b);

int ReadTextintoMemory(char* textstart, string binaryfilename);
void SplitStringIntoVector(string shuaige, vector<string>& CodeIn);
string CommaReplaceEraseSpace(string str);
char* ReadintoMemory(char* Data, string Filename);
string ClearTheComment(string shuaige);
string Trim(string shuaige);
string ClearTheComment(string shuaige);
void Process(int* registers, char*& PC, int* OtherRegisters, string machinecode, ifstream& shuaige1, ofstream& shuaige2, char* SixMbMemory, char*& dynamicdatapointer, int& times, int& flag);



