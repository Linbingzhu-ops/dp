#include<iostream>
#include<fstream>
#include<string>
using namespace std;


void imu()
{


}
void wifi()
{


}
void gnss()
{


}
//分割函数
char Spilit(string &str)
{
    char *lineCharArray;
    const int len = str.length();
    lineCharArray = new char[len + 1];
    strcpy(lineCharArray, str.c_str());
 
    char *p; // 分隔后的字符串
    p = strtok(lineCharArray, ";"); // 按照;分隔
    return *p;


}
const char *filename="data.txt";
char   Resfilename[3][32]={"imu.txt","wifi.txt","gnss.txt"};
//int M,N;
//char buf[M][N];
int main()
{
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open())//判断文件是否打开
	{
		cout<<"Error opening file" << endl;
	}
    string lineStr;
    if(fin)
    {
        int i=0;
        while(getline(fin,lineStr))
        {
            if(lineStr[0]=='%') continue;
            else
                {
                    if(lineStr.substr(4)=="ACCE" | lineStr.substr(4)=="GYRO" | lineStr.substr(4)=="MAGN" | lineStr.substr(4)=="PRES" | lineStr.substr(4)=="AHRS")
                    {
                        Spilit(lineStr);

                    }
                }
            
        }
    }


    return 0;



}