#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <iostream>

int main(){

	std::vector<std::string> filePaths;

	const int BUFSIZE = 1024;
	char buffer[BUFSIZE+1] = {0};
	OPENFILENAME ofns = {0};
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = "Select DAT files";
	ofns.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	GetOpenFileName(&ofns);

	char* str = ofns.lpstrFile;

	std::string directory = buffer;
	str+=(directory.length()+1);
	filePaths.push_back(directory);

	while(*str){
		std::string filename = str;
		filePaths.push_back(filename);
		str+=(filename.length()+1);
	}

	std::string mascotDir = "D:\\inetpub\\mascot\\cgi\\";
	SetCurrentDirectory(mascotDir.c_str());

	for(int i=0, dirSize=filePaths[0].size(); i<dirSize; i++){
		if(filePaths[0][i]=='\\'){
			filePaths[0][i]='/';
			filePaths[0].insert(i,"/");
		}
	}

	for(int i=1, numFiles=filePaths.size(); i<numFiles; i++){
		std::string systemString = "export_dat_2.pl _ignoreionsscorebelow=5 _minpeplen=0 _server_mudpit_switch=99999999 _showsubsets=1 _sigthreshold=0.05 do_export=1 export_format=mzIdentML file=";
		systemString+=filePaths[0]+"//"+filePaths[i]+" pep_exp_mz=1 pep_isbold=1 pep_isunique=1 pep_query=1 pep_rank=1 peptide_master=1 prot_acc=1 prot_desc=1 prot_hit_num=1 report=1000000 sessionid=all_secdisabledsession show_pep_dupes=1 show_same_sets=1 > ";
		std::string mzidFile = filePaths[i].erase(filePaths[i].length()-3);
		mzidFile+=std::string("mzid");
		systemString+=filePaths[0]+"//"+mzidFile;
		std::cout << "\rConverting DAT file " << i << " / " << numFiles-1;
		system(systemString.c_str());
	}

	MessageBox(0, "Conversion finished!", "DAT Converter", MB_OK);

}