#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
double t_min=DBL_MAX;
 int imu_min=DBL_MAX;
 int wifi_min=DBL_MAX;


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
vector<char*> Split(string &lineStr)
{
     vector<char *> res_str;
     char *lineCharArray;
    const int len = lineStr.length();
    lineCharArray = new char[len + 1];
     strcpy(lineCharArray, lineStr.c_str());
                    
    char *p; // 分隔后的字符串
    p = strtok(lineCharArray, ";"); // 按照;分隔
    while(p!=NULL)
     {
    res_str.push_back(p);
     p=strtok(NULL,";");
     }
    return res_str;


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
                        int imu_min;
                        vector<char*>res_str=Split(lineStr);
                        if(imu_min>strtod(res_str[2],NULL)) imu_min=strtod(res_str[2],NULL);
                    
                    }
                    if(lineStr.substr(4)=="WIFI")
                    {
                        vector<char*>res_str=Split(lineStr);
                        if(wifi_min>strtod(res_str[2],NULL)) wifi_min=strtod(res_str[2],NULL);
                    
                        
                    }
                }
            
        }
    }


    return 0;



}