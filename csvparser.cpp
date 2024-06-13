#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<queue>
using namespace std;

unsigned int converttime(string& str)
{
    stringstream row(str);
    string hour = "";
    string minute = "";
    string second ="";

    getline(row, hour, ':');
    cout<<"type of hour"<<typeid(hour).name()<<""<<endl;
    unsigned int hr = stoi(hour);
    unsigned int hr_in_sec = hr*3600;
    
    
    
    getline(row, minute, ':');
    unsigned int mint = stoi(minute);
    unsigned int mint_in_sec = mint*60;

    getline(row, second, ':');
    unsigned int sec = stoi(second);
    
    unsigned int total_time_in_sec = hr_in_sec + mint_in_sec + sec;

    
    cout<<"hour : "<<hr<<" minute : "<<mint<<" second : "<<sec<<endl;
    
    return total_time_in_sec;
}

int main()
{

    ifstream myfile;
    myfile.open("karttimes.csv");
    string line ="";

    //map<string, vector<string>> analytical_mp;
    map<string, vector<unsigned int>>  fastestlapwinner_mp;

    int count = 0;
    while(getline(myfile, line))
    {
        if (count == 0 )
        {
            count = count +  1;
            continue;
        }
        stringstream row(line);
        string drivername;
        string driverlapsetime;
        getline(row, drivername, ',');
        getline(row, driverlapsetime, ',');
        unsigned int time_in_seconds = converttime(driverlapsetime);    
        fastestlapwinner_mp[drivername].push_back(time_in_seconds);
    }

map<string, vector<unsigned int>> race;
int no_of_lap = 4;
for(auto it=fastestlapwinner_mp.begin(); it!=fastestlapwinner_mp.end(); it++)
{
    cout<<"Driver name"<<it->first<<" ";
    auto itl = it->second.begin();
    auto itr = it->second.begin();
    itr++;
    unsigned int difftime = 0;
    unsigned int tot_time = 0;

    while(itr != it->second.end())
    {
        difftime = *itr - *itl;
        tot_time = tot_time + difftime;
        race[it->first].push_back(difftime);
        itr++;
        itl++;
    }
    race[it->first].push_back(tot_time);
    cout<<" "<<endl;

}

struct mycomparator
{
    bool operator()(pair<string,int>& a, pair<string,int>& b)
    {
        return a.second > b.second;
    }
};

priority_queue<pair<string,int>, vector<pair<string,int>>, mycomparator> k;

for(auto i = race.begin(); i!=race.end();i++)
{
    cout<<i->second.back()<<" ";
    int maxres = i->second.back();

    k.push(make_pair(i->first,maxres));
 
    cout<<endl;
}
auto topval = k.top();
int reftime = topval.second;
cout<<"Winer of the race"<<endl;
cout<<topval.first<<" "<<topval.second<<" "<<endl;
k.pop();
queue<pair<string,int>> q;
cout<<"Following are the laggers beaten by" <<endl;
while (!k.empty())
{
    /* code */
    auto topval = k.top();
    cout<<topval.first<<" "<<topval.second-reftime<<endl;
    q.push(make_pair(topval.first,topval.second-reftime));
    k.pop();
}

}