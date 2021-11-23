#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <iostream>

int main(){

	std::vector<std::string> filePaths;

	// Theoretical max number of files if file path length = MAX_PATH
	// Set max to 1000
	const int BUFSIZE = 1000*(MAX_PATH+1)+1;
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

	//Iterate through the char pointer containing the file paths and store the paths in a vector
	while(*str){
		std::string filename = str;
		filePaths.push_back(filename);
		str+=(filename.length()+1);
	}

	//We want to set the current directory to the Mascot cgi folder so that the export_data_2.pl script runs correctly
	std::string mascotDir = "C:\\inetpub\\mascot\\cgi\\";
	SetCurrentDirectory(mascotDir.c_str());

	//The export_dat_2.pl script seems to only like double forward slashes in the DAT file paths. So we replace every backslash and insert 2 forward slashes
	for(int i=0; i<filePaths[0].size(); i++){
		if(filePaths[0][i]=='\\'){
			filePaths[0][i]='/';
			filePaths[0].insert(i,"/");
		}
	}

	for(int i=1, numFiles=filePaths.size(); i<numFiles; i++){
		std::string systemString = "C:\\inetpub\\mascot\\perl64\\bin\\perl.exe export_dat_2.pl _ignoreionsscorebelow=0.1 _minpeplen=0 _server_mudpit_switch=99999999 _showsubsets=1 _sigthreshold=1 do_export=1 export_format=pepXML file=";
		systemString+=filePaths[0]+"//"+filePaths[i]+" group_family=0 pep_exp_mz=1 pep_isbold=1 pep_isunique=1 pep_query=1 pep_rank=1 peptide_master=1 prot_acc=1 prot_desc=1 prot_hit_num=1 report=1000000 sessionid=all_secdisabledsession show_pep_dupes=1 show_same_sets=1 > ";
		std::string mzidFile = filePaths[i].erase(filePaths[i].length()-3);
		mzidFile+=std::string("pepXML");
		systemString+=filePaths[0]+"//"+mzidFile;
		std::cout << "\rConverting DAT file " << i << " / " << numFiles-1;
		system(systemString.c_str());
	}

	MessageBox(0, "Conversion finished!", "DAT Converter", MB_OK);

}
