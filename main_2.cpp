#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "binary.h"
#include <ctime>
#include <byteswap.h>

using namespace std;

int main() {
	
	clock_t start;
	double duration;
	
	start = clock();
	

	// Open fasta and stocking the sequence in a string
	
    fstream file;
    file.open("P00533.fasta", ios::in);
    string sequence;
    if(file.is_open()){
        string line;
        int i = 0;
        while(getline(file, line)){
            if(i>0) {
                sequence.append(line);
            }
            i++;
        }
    }
    file.close();
    
     
	// Converting the string into a table of byts
	
	int8_t *sequence_request = new int8_t[sequence.size()];
	int request_size = sequence.size();
	int i = 0;
	for (i = 0; i < request_size; i++){
		Binary letter;
		letter.setBinary(sequence[i]);
		sequence_request[i] = letter.getBinary_letter();
	}
	
	/*
	for (int i = 0; i<request_size; i+=1){
		cout << bitset<8>(sequence_request[i]) << endl;
	}
	*/

	

	
	// Open the psq file and stocking it in a table of byts
	
	ifstream database("uniprot_sprot.fasta.psq",ios::binary | ios::ate);											
	streampos dbsize ;
	
	if(!(database.is_open())){
		cout << "Error while opening the database" << endl;
		exit (EXIT_FAILURE);
	}
	cout<< "Database opened successfully !! " <<endl;
	dbsize=database.tellg();     			
	int8_t *db = new int8_t[dbsize];
	if(db!=NULL)
	{
		database.seekg(0,ios::beg); 
		for(int b=0;b<dbsize;b++)
		{							
			database.read((char*)(&db[b]),sizeof(int8_t));
		}
		database.close();  	
	}
	
	//cout << bitset<8>(db[dbsize]) << endl;
	
	
	// Open the pin file and stocking offset header and offset sequence in 2 tables of byts
	
	ifstream pin("uniprot_sprot.fasta.pin",ios::binary);
	if(!(pin.is_open())){
		cout << "Error while opening pin file" << endl;
		exit (EXIT_FAILURE);
	}

	pin.seekg(56); // for direct going to the number of sequences
	int32_t Number_sequences_BE;
	int32_t N;  // Number of sequence little endian
	pin.read((char*)(&Number_sequences_BE),sizeof(int32_t));
	N=bswap_32(Number_sequences_BE);
	cout<< "Number of sequences :"<< N <<endl;
	
	pin.seekg(72); // for direct going to the header table
	int32_t *header_offset = new int32_t[N+1];
	int32_t *sequence_offset = new int32_t[N+1];	
	
	if(header_offset !=NULL)
	{
		for(int l=0;l<(N+1);l++)
		{
			pin.read((char*)(&header_offset[l]),sizeof(int32_t));
			int temp2=bswap_32(header_offset[l]);
			header_offset[l]=temp2;
		}
			
		if(sequence_offset !=NULL)
		{
			for(int m=0;m<(N+1);m++)
			{
				pin.read((char*)(&sequence_offset[m]),sizeof(int32_t));
				int temp3 ;
				temp3=bswap_32(sequence_offset[m]);
				sequence_offset[m]=temp3;
			}
					
		}	
	}	
	pin.close();
	

	
	
	//cout << bitset<8>(db[sequence_offset[0]+2]) << endl;

	for (int i=1; i<N; i+=1 ){
		
		int size_sequence = sequence_offset[i+1]-sequence_offset[i]-1;
		
		if ( size_sequence == request_size ) {
			cout << "lsiwfhqiduhfmijk" << endl;
			int j = 0;
			int same = 1; 
			while ( j < request_size && same == 1){
				if (db[sequence_offset[i]+j] != sequence_request[j]){
					same=0;
				}
				j+=1;
			}
			
			if ( same == 1){
				cout << "Trouvé !! Indice : " << i << "\n sequence offset : " << sequence_offset[i] << endl;
				break;
			}
		
		}	

	}
	
	
	
	for (int i = 0; i < request_size; i+=1){
		cout << bitset<8>(db[sequence_offset[117028]+i]) << endl;
	}
	
	



	
	
	duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
	cout << "TEMPS TOTAL: " << duration << " sec" << endl;
	
	
	
		
		
    return 0;
}
