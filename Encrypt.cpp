#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <random>
#include <time.h>


int main(){

	std::string in, out, line, char_pool, mess, str = "";
	char choice;
	
	std::ofstream fout;
	unsigned int seed;
	char_pool = " qwertyuiopasdfghjlkzxcvbnmQWERTYUIOPASDFGHJKLZXCVNBM1234567890-=_+|\\`~!@#$%^&*()[]{};:,<.>/?";
	
	
	std::cout << "Encrypt (E) or Decrypt (D)\n";
	std::cin >> choice;
	
	std::cout<< "Enter In File name:";
	std::cin >> in;
	std::ifstream fin(in);

	if (!fin) {
		std::cerr << "Unable to open " << in << "\nMake sure file is in same directory\n";
	}

	else{
		std::cout<< "Enter Out File name:";
		std::cin >> out;
		fout.open(out);
	
		std::cout << "Enter seed:";
		std::cin >> seed;
		std::srand(seed);										//generates how many fake charaters inserted per character

		std::default_random_engine eng((unsigned int) time(0));
		std::uniform_int_distribution<int> dis(0, char_pool.size()-1);	//generates ramdom char_pool index
	
		if (choice == 'E'){
			while (std::getline(fin, line)){
				mess = "";	//the encrypted line that gets ouputted to file

				for (unsigned int i = 0; i <= line.size(); i++){
					str = "";
					int j =	rand()%(1000-2+1)+2;				//decide how many random character to insert

					for (int k = 0; k < j; k++)   
						str += char_pool[dis(eng)];				//Append j fake characters to string

					if (i < line.size())
						str += line[i];

					mess += str;								//Append correct char + fake chars to output line
				}
				fout << mess << std::endl;
			}
		}


		if (choice == 'D'){
			while (std::getline(fin, line)){
				mess = "";										
				std::string sub = "";
				unsigned int start = 0;

				while (start < line.size()){
					int j = rand()%(1000-2+1)+2;				//determine how many fake characters separate the real ones

					if (start == 0){							//finds first correct character and appends it
						start = j;
						sub += line.substr(j, 1);
					}

					else{
						sub += line.substr(start + j + 1, 1);	//Locate and append every following correct character
						start = start + j + 1;
					}
				}
				mess += sub;
				fout << mess << std::endl;
			}
		}

		fin.close();
		fout.close();
	}

	return 0;
}

