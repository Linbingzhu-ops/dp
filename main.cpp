#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<cmath>
using namespace std;
double wifi_min = 10000;
double t_min=10000;
 vector<char*> Split(string &lineStr);
char Resfilename[3][32]={"imu.txt","wifi.txt","gnss.txt"};
//int M,N;
 


void imu()
{


}
void wifi(string &lineStr)
{

    
    vector<char*> mac = {};
    mac.clear();
    long long int mac_sum=0;
    char *RSS;
    vector<char *> res_str=Split(lineStr);
    int Time=(strtod(res_str[2],NULL)-wifi_min)*1000;
    char *p=res_str[4]; // 分隔后的字符串
    p = strtok(res_str[res_str.size() - 2], ":");
    while(p!=NULL)
    {

        mac.push_back(p);
        p=strtok(NULL,":");
    }
    for(int i=0;i<6;i++)
    {
        long long int m=strtod(mac[i],NULL);
        
        int c=0;
        while(m!=0)
        {
            int a=m%10;
            m=floor(m/10);
            mac_sum +=a*pow(16,i);
            c++;
        
        }


    }
    if (res_str.size()==7)  RSS=res_str[6];
    else RSS=res_str[5];
    fstream fout(Resfilename[1],std::ostream::out | std::ostream::app);
    
    fout<<'['<<Time<<','<<mac_sum<<','<<RSS<<']'<<endl;
    fout.close();

   


}
void gnss()
{


}
//分割函数
vector<char*> Split(string &lineStr)
{

     vector<char *> res_str;
     res_str.clear();
     char *lineCharArray;
    const int len = lineStr.length();
    lineCharArray = new char[len + 1];
     strcpy(lineCharArray, lineStr.c_str());
                    
    char *p=NULL; // 分隔后的字符串
    p = strtok(lineCharArray, ";"); // 按照;分隔
    while(p!=NULL)
     {
    res_str.push_back(p);
     p=strtok(NULL,";");
     }
    return res_str;


}


//char buf[M][N];
int main()
{
    ifstream fin("data.txt");
    if(!fin.is_open())//判断文件是否打开
	{
		cout<<"Error opening file" << endl;
	}
    string lineStr;
    if(fin)
    {
        int i=0;
        double imu_min = 9999;
        
        while(getline(fin,lineStr))
        {
            if(lineStr[0]=='%') continue;
            else {
                if(lineStr.size() < 4) continue;
                if(lineStr.substr(0, 4)=="ACCE" | lineStr.substr(0, 4)=="GYRO" | lineStr.substr(0, 4)=="MAGN" | lineStr.substr(0, 4)=="PRES" | lineStr.substr(0, 4)=="AHRS")
                {
                    
                    vector<char*>res_str=Split(lineStr);
                    imu_min = min(imu_min, strtod(res_str[2],NULL));
                
                }
                if(lineStr.substr(0, 4)=="WIFI")
                {
                    vector<char*>res_str=Split(lineStr);
                    wifi_min = min(wifi_min, strtod(res_str[2],NULL));
                    wifi(lineStr);
                }
                if(lineStr.substr(0,4)=="GNSS")
                {
                    
                }
                
            }
            
        }
    }


    return 0;



}