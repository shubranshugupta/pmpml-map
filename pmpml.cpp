#include <bits/stdc++.h>
#include "graph.h"

using namespace std;
using namespace GraphNS;

template<class _Key, class _Tp, class _Value=Edge<_Key, _Tp>>
class PMPMLMap: private Graph<_Key, _Tp, _Value>{
    private:
        string fname;
        int maxLength=INT_MIN, distOrTime=0;
        _Key src, dest;

        void centerWords(vector<_Key> &vec, const char& delimiter = '|'){
            int count=0;
            while(count<vec.size()){
                for(int i=0; i<4; i++){
                    cout << setw(maxLength) << vec[count].c_str() << delimiter;
                    // cout << setw((maxLength-vec[count].size())/2) << delimiter;
                    count++;
                }
                cout<<endl;
            }
        }

        void printMultiple(char c, int n, bool useEndl=false){
            for (int i = 0; i < n; i++){
                cout << c;
            }

            if(useEndl)
                cout << endl;
        }

        bool endsWith(const string &orignal, const string &compareto){
            if(orignal.size() < compareto.size())
                return false;
            return orignal.substr(orignal.size() - compareto.size(), compareto.size()) == compareto;
        }

        vector<vector<string>> readCSV(char delimiter=','){
            fstream file (this->fname, ios::in);
            vector<vector<string>> content;
            vector<string> row;
            string line, word;

            if(file.is_open()){
                while(getline(file, line)){
                    row.clear();
                    stringstream str(line);
                    
                    while(getline(str, word, delimiter)){
                        maxLength = max(maxLength, int(word.size()));
                        row.push_back(word);
                    }
                    content.push_back(row);
                }
            }else{
                throw "File not found";
            }

            return content;
        }

        void insertDataToGraph(vector<vector<string>> data){
            int count = 1;
            for (auto item : data){
                if(item.size() != 4){
                    cout << "Error: The data no. "<<count<<" is not in the correct format" << endl;
                }
                try{
                    this->addEdge(item[0], item[1], stoi(item[2]), stoi(item[3]));
                }catch(exception e){
                    cout << "Error: The data no. "<< count << endl;
                }
                count++;
            }
        }

    public:
        PMPMLMap(string fname){
            if(endsWith(fname, ".csv"))
                this->fname = fname;
            else
                throw invalid_argument("File name must end with .csv");
            
            insertDataToGraph(readCSV());
        }

        void display(){
            printMultiple('=', 50);
            cout<<" WELCOME To PMPML App ";
            printMultiple('=', 50, true);
            cout<<endl;
        }

        void displayStops(){
            printMultiple('=', 50);
            cout<< setw(13) <<" STOPS "<<setw(10);
            printMultiple('=', 50, true);

            vector<_Key> stops = this->getVertices();
            centerWords(stops);
            printMultiple('=', 122, true);
        }

        void takeInputs(){
            cout<<"Enter source stop: ";
            getline(cin, src);
            cout<<"Enter destination stop: ";
            getline(cin, dest);
            cout<<"Do you want minimum distance or time? (0 for distance, 1 for time): ";
            cin>>distOrTime;
            cout<<endl;
        }

        void findShortestPath(){
            cout<<"Finding shortest path..."<<endl;
            
            pair<vector<_Key>, _Tp> ans = this->dijkstraAlgo(src, dest, distOrTime);
            
            cout<<"Shortest path from "<<src<<" to "<<dest<<" is: "<<endl;    
            for(int i=0; i<ans.first.size(); i++){
                if(i==ans.first.size()-1){
                    cout<<ans.first[i]<<endl;
                }else{
                    cout<<ans.first[i]<<" -> ";
                }
            }
            cout<<endl;
            cout<<"Distance: "<<ans.second<<endl;

            printMultiple('=', 122, true);
        }

        void printTheEnd(){
            printMultiple('=', 45);
            cout<<" THANK YOU FOR USING PMPML APP ";
            printMultiple('=', 46, true);
        }
};

int main(){
    char choice;
    PMPMLMap<string, int> pmpml("pmpml.csv");
    pmpml.display();
    pmpml.displayStops();

    while(true){
        pmpml.takeInputs();
        pmpml.findShortestPath();
        cout<<"Do you want to continue? (y/n): ";
        cin>>choice;
        if(choice=='n' || choice=='N')
            break;
        cin.ignore();
    }

    pmpml.printTheEnd();
    return 0;
}