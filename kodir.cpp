#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#define o_CP1251    1
#define CP1251_SYMBOL 0xee

#define o_CP866     2
#define CP866_SYMBOL  0xae

#define o_KOI8R     3
#define KOI8R_SYMBOL  0xcf

using namespace std;

static const unsigned char Cp1251ToCp866[ 128 ] = {

    0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
    0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f,
    0x90,  0x91,  0x92,  0x93,  0x94,  0xf9,  0x96,  0xc4,
    0x98,  0x99,  0x9a,  0x9b,  0x9c,  0x9d,  0x9e,  0x9f,
    0xff,  0xf6,  0xf7,  0xa3,  0xfd,  0xa5,  0xa6,  0xa7,
    0xf0,  0xa9,  0xf2,  0xab,  0xac,  0xad,  0xae,  0xf4,
    0xf8,  0xb1,  0xb2,  0xb3,  0xb4,  0xb5,  0xb6,  0xfa,
    0xf1,  0xfc,  0xf3,  0xbb,  0xbc,  0xbd,  0xbe,  0xf5,
    0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
    0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f,
    0x90,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,  0x97,
    0x98,  0x99,  0x9a,  0x9b,  0x9c,  0x9d,  0x9e,  0x9f,
    0xa0,  0xa1,  0xa2,  0xa3,  0xa4,  0xa5,  0xa6,  0xa7,
    0xa8,  0xa9,  0xaa,  0xab,  0xac,  0xad,  0xae,  0xaf,
    0xe0,  0xe1,  0xe2,  0xe3,  0xe4,  0xe5,  0xe6,  0xe7,
    0xe8,  0xe9,  0xea,  0xeb,  0xec,  0xed,  0xee,  0xef
};

static const unsigned char Cp1251ToKoi8R[ 128 ] = {

    0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
    0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f,
    0x90,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,  0x80,
    0x98,  0x99,  0x9a,  0x9b,  0x9c,  0x9d,  0x9e,  0x9f,
    0x9a,  0xa1,  0xa2,  0xa3,  0xa4,  0xa5,  0xa6,  0xa7,
    0xb3,  0xbf,  0xaa,  0xab,  0xac,  0xad,  0xae,  0xaf,
    0x9c,  0xb1,  0xb2,  0xb3,  0xb4,  0xb5,  0xb6,  0x9e,
    0xa3,  0xb9,  0xba,  0xbb,  0xbc,  0xbd,  0xbe,  0xbf,
    0xe1,  0xe2,  0xf7,  0xe7,  0xe4,  0xe5,  0xf6,  0xfa,
    0xe9,  0xea,  0xeb,  0xec,  0xed,  0xee,  0xef,  0xf0,
    0xf2,  0xf3,  0xf4,  0xf5,  0xe6,  0xe8,  0xe3,  0xfe,
    0xfb,  0xfd,  0xff,  0xf9,  0xf8,  0xfc,  0xe0,  0xf1,
    0xc1,  0xc2,  0xd7,  0xc7,  0xc4,  0xc5,  0xd6,  0xda,
    0xc9,  0xca,  0xcb,  0xcc,  0xcd,  0xce,  0xcf,  0xd0,
    0xd2,  0xd3,  0xd4,  0xd5,  0xc6,  0xc8,  0xc3,  0xde,
    0xdb,  0xdd,  0xdf,  0xd9,  0xd8,  0xdc,  0xc0,  0xd1
};

static const unsigned char Cp866ToCp1251[ 128 ] = {

    0xc0,  0xc1,  0xc2,  0xc3,  0xc4,  0xc5,  0xc6,  0xc7,
    0xc8,  0xc9,  0xca,  0xcb,  0xcc,  0xcd,  0xce,  0xcf,
    0xd0,  0xd1,  0xd2,  0xd3,  0xd4,  0xd5,  0xd6,  0xd7,
    0xd8,  0xd9,  0xda,  0xdb,  0xdc,  0xdd,  0xde,  0xdf,
    0xe0,  0xe1,  0xe2,  0xe3,  0xe4,  0xe5,  0xe6,  0xe7,
    0xe8,  0xe9,  0xea,  0xeb,  0xec,  0xed,  0xee,  0xef,
    0xb0,  0xb1,  0xb2,  0xb3,  0xb4,  0xb5,  0xb6,  0xb7,
    0xb8,  0xb9,  0xba,  0xbb,  0xbc,  0xbd,  0xbe,  0xbf,
    0xc0,  0xc1,  0xc2,  0xc3,  0x97,  0xc5,  0xc6,  0xc7,
    0xc8,  0xc9,  0xca,  0xcb,  0xcc,  0xcd,  0xce,  0xcf,
    0xd0,  0xd1,  0xd2,  0xd3,  0xd4,  0xd5,  0xd6,  0xd7,
    0xd8,  0xd9,  0xda,  0xdb,  0xdc,  0xdd,  0xde,  0xdf,
    0xf0,  0xf1,  0xf2,  0xf3,  0xf4,  0xf5,  0xf6,  0xf7,
    0xf8,  0xf9,  0xfa,  0xfb,  0xfc,  0xfd,  0xfe,  0xff,
    0xa8,  0xb8,  0xaa,  0xba,  0xaf,  0xbf,  0xa1,  0xa2,
    0xb0,  0x95,  0xb7,  0xfb,  0xb9,  0xa4,  0xfe,  0xa0
};

static const unsigned char Cp866ToKoi8R[ 128 ] = {

    0xe1,  0xe2,  0xf7,  0xe7,  0xe4,  0xe5,  0xf6,  0xfa,
    0xe9,  0xea,  0xeb,  0xec,  0xed,  0xee,  0xef,  0xf0,
    0xf2,  0xf3,  0xf4,  0xf5,  0xe6,  0xe8,  0xe3,  0xfe,
    0xfb,  0xfd,  0xff,  0xf9,  0xf8,  0xfc,  0xe0,  0xf1,
    0xc1,  0xc2,  0xd7,  0xc7,  0xc4,  0xc5,  0xd6,  0xda,
    0xc9,  0xca,  0xcb,  0xcc,  0xcd,  0xce,  0xcf,  0xd0,
    0x90,  0x91,  0x92,  0x81,  0x87,  0xb2,  0xb4,  0xa7,
    0xa6,  0xb5,  0xa1,  0xa8,  0xae,  0xad,  0xac,  0x83,
    0x84,  0x89,  0x88,  0x86,  0x80,  0x8a,  0xaf,  0xb0,
    0xab,  0xa5,  0xbb,  0xb8,  0xb1,  0xa0,  0xbe,  0xb9,
    0xba,  0xb6,  0xb7,  0xaa,  0xa9,  0xa2,  0xa4,  0xbd,
    0xbc,  0x85,  0x82,  0x8d,  0x8c,  0x8e,  0x8f,  0x8b,
    0xd2,  0xd3,  0xd4,  0xd5,  0xc6,  0xc8,  0xc3,  0xde,
    0xdb,  0xdd,  0xdf,  0xd9,  0xd8,  0xdc,  0xc0,  0xd1,
    0xb3,  0xa3,  0xf2,  0xf3,  0xf4,  0xf5,  0xf6,  0xf7,
    0x9c,  0x95,  0x9e,  0x96,  0xfc,  0xfd,  0x94,  0x9a
};

static const unsigned char Koi8RToCp1251[ 128 ] = {

    0x97,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
    0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f,
    0x90,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,  0x97,
    0x98,  0x99,  0xa0,  0x9b,  0xb0,  0x9d,  0xb7,  0x9f,
    0xa0,  0xa1,  0xa2,  0xb8,  0xa4,  0xa5,  0xa6,  0xa7,
    0xa8,  0xa9,  0xaa,  0xab,  0xac,  0xad,  0xae,  0xaf,
    0xb0,  0xb1,  0xb2,  0xa8,  0xb4,  0xb5,  0xb6,  0xb7,
    0xb8,  0xb9,  0xba,  0xbb,  0xbc,  0xbd,  0xbe,  0xa9,
    0xfe,  0xe0,  0xe1,  0xf6,  0xe4,  0xe5,  0xf4,  0xe3,
    0xf5,  0xe8,  0xe9,  0xea,  0xeb,  0xec,  0xed,  0xee,
    0xef,  0xff,  0xf0,  0xf1,  0xf2,  0xf3,  0xe6,  0xe2,
    0xfc,  0xfb,  0xe7,  0xf8,  0xfd,  0xf9,  0xf7,  0xfa,
    0xde,  0xc0,  0xc1,  0xd6,  0xc4,  0xc5,  0xd4,  0xc3,
    0xd5,  0xc8,  0xc9,  0xca,  0xcb,  0xcc,  0xcd,  0xce,
    0xcf,  0xdf,  0xd0,  0xd1,  0xd2,  0xd3,  0xc6,  0xc2,
    0xdc,  0xdb,  0xc7,  0xd8,  0xdd,  0xd9,  0xd7,  0xda
};

static const unsigned char Koi8RToCp866[ 128 ] = {

    0xc4,  0xb3,  0xda,  0xbf,  0xc0,  0xd9,  0xc3,  0xb4,
    0xc2,  0xc1,  0xc5,  0xdf,  0xdc,  0xdb,  0xdd,  0xde,
    0xb0,  0xb1,  0xb2,  0x93,  0xfe,  0xf9,  0xfb,  0x97,
    0x98,  0x99,  0xff,  0x9b,  0xf8,  0x9d,  0xfa,  0x9f,
    0xcd,  0xba,  0xd5,  0xf1,  0xd6,  0xc9,  0xb8,  0xb7,
    0xbb,  0xd4,  0xd3,  0xc8,  0xbe,  0xbd,  0xbc,  0xc6,
    0xc7,  0xcc,  0xb5,  0xf0,  0xb6,  0xb9,  0xd1,  0xd2,
    0xcb,  0xcf,  0xd0,  0xca,  0xd8,  0xd7,  0xce,  0xbf,
    0xee,  0xa0,  0xa1,  0xe6,  0xa4,  0xa5,  0xe4,  0xa3,
    0xe5,  0xa8,  0xa9,  0xaa,  0xab,  0xac,  0xad,  0xae,
    0xaf,  0xef,  0xe0,  0xe1,  0xe2,  0xe3,  0xa6,  0xa2,
    0xec,  0xeb,  0xa7,  0xe8,  0xed,  0xe9,  0xe7,  0xea,
    0x9e,  0x80,  0x81,  0x96,  0x84,  0x85,  0x94,  0x83,
    0x95,  0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,
    0x8f,  0x9f,  0x90,  0x91,  0x92,  0x93,  0x86,  0x82,
    0x9c,  0x9b,  0x87,  0x98,  0x9d,  0x99,  0x97,  0x9a
};
class recoder
{
	unsigned short count[128];
	int way[4];
	int recodes=0;
	unsigned char mostfrequent;
	int original_code;
 public:
	recoder() {
		for(int i=0;i<4;i++)
			{
			way[i]=0;
			}
		for(int i=0;i<128;i++)
			{
			count[i]=0;
			}
		recodes=0;
		}
	int readfile(const char* iFileName) {
		char ch;
		ifstream iFile;
		iFile.open(iFileName);
		if(!iFile)
			{
			cout<<"Файл"<<iFileName<<"отсутствует"<<endl;
			return 0;
			}
		while(!iFile.eof())
			{
			iFile.get(ch);
			if(ch&0x80)count[ch&0x7f]++;
			}
		return 1;
		}
	int findpopular() {
		int i;
		for(i=0;i<128;i++)
			{
			if(count[mostfrequent]<count[i])mostfrequent=i;
			}
		mostfrequent=mostfrequent|0x80;
		return 1;
		}
	void translate(unsigned char& simvol, int algoritm) {
	        switch (algoritm) {
	                case 0:
	                    simvol = Cp1251ToCp866 [simvol&0x7f];
	                    break;
	                case 1:
	                    simvol = Cp1251ToKoi8R [simvol&0x7f];
	                    break;
	                case 2:
	                    simvol = Cp866ToCp1251 [simvol&0x7f];
	                    break;
	                case 3:
	                    simvol = Cp866ToKoi8R  [simvol&0x7f];
	                    break;
	                case 4:
	                    simvol = Koi8RToCp1251 [simvol&0x7f];
	                    break;
	                case 5:
	                    simvol = Koi8RToCp866  [simvol&0x7f];
			break;
				}
		}
	int findway() {
		int j,i,r,t,q;
		unsigned char * simvol[4];
		simvol[0] = new unsigned char (mostfrequent);
		if(mostfrequent==CP1251_SYMBOL){cout<<"Кодировка cp1251"<<endl;return 0;}
		if(mostfrequent==CP866_SYMBOL){cout<<"Кодировка cp866"<<endl;return 0;}
		if(mostfrequent==KOI8R_SYMBOL){cout<<"Кодировка koi8-r"<<endl;return 0;}
		for(j=1;j<4;j++)
			{
			t=(int)pow(6,j);
			simvol[j]=new unsigned char[t];
			r=0;	
			while(r<t)
		  		{for(i=0;i<6;i++)
					{
					for(q=j;q>0;q--)
						{
						way[q]=(r/(int)(pow(6,(q-1))))%6;
						}
					simvol[j][r]=simvol[j-1][r/6];
					translate(simvol[j][r], i);
						if(simvol[j][r]==CP1251_SYMBOL){cout<<"Кодировка cp1251"<<endl;recodes=j;return 1;}
						if(simvol[j][r]==CP866_SYMBOL){cout<<"Кодировка cp866"<<endl;recodes=j;return 1;}
						if(simvol[j][r]==KOI8R_SYMBOL){cout<<"Кодировка koi8-r"<<endl;recodes=j;return 1;}
					r++;
					}
		  		}
			}
        		for (int i = 0; i < j + 1 ; i++) {
      			delete [] simvol[i];}	
			return 0;
		}
	int writefile(const char* iFileName , const char* oFileName) {
		int i;
		char ch;
		unsigned char b;
		ifstream iFile;
        	ofstream oFile;
        	iFile.open (iFileName);
		oFile.open (oFileName);
		while(!iFile.eof())
			{
			iFile.get(ch);
			if(ch&0x80)
				{b=(unsigned char)ch;
				for(i=0;i<recodes;i++)
					{
					translate(b, way[i+1]);
					}
				}
			oFile << (char)b;
			}
		return 1;
		}
};
int main (int argc, char *argv[]) {
	recoder ob;
	if (argc < 3) {
        	cout << "Not enough files for work." << endl;
        	return 0;
		}
	ob.readfile(argv[1]);
	ob.findpopular();
	ob.findway();
	ob.writefile(argv[1] ,argv[2]);
	return 0;
	}
