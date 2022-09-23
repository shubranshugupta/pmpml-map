#include <bits/stdc++.h>
#include "graph.h"

using namespace std;
using namespace GraphNS;



// Implementing AdjNode class
template<class _Key, class _Tp>
AdjNode<_Key, _Tp>::AdjNode(){}

template<class _Key, class _Tp>
void AdjNode<_Key, _Tp>::addEdge(_Key key, _Tp value){
    adjNode[key] = value;
}

template<class _Key, class _Tp>
void AdjNode<_Key, _Tp>::removeEdge(_Key key){
    adjNode.erase(key);
}

template<class _Key, class _Tp>
void AdjNode<_Key, _Tp>::removeAllEdges(){
    adjNode.clear();
}

template<class _Key, class _Tp>
bool AdjNode<_Key, _Tp>::hasEdge(_Key key){
    return adjNode.find(key) != adjNode.end();
}

template<class _Key, class _Tp>
_Tp AdjNode<_Key, _Tp>::getWeight(_Key key){
    return adjNode[key];
}

template<class _Key, class _Tp>
void AdjNode<_Key, _Tp>::printAdjNode(){
    for(auto it = adjNode.begin(); it != adjNode.end(); it++){
        cout << it->first << "[" << it->second << "] -> ";
    }
    cout << "NULL" << endl;
}

template<class _Key, class _Tp>
typename map<_Key, _Tp>::iterator AdjNode<_Key, _Tp>::begin(){
    return adjNode.begin();
}

template<class _Key, class _Tp>
typename map<_Key, _Tp>::iterator AdjNode<_Key, _Tp>::end(){
    return adjNode.end();
}



//Implementing Graph class
template<class _Key, class _Tp>
Graph<_Key, _Tp>::Graph(){}

template<class _Key, class _Tp>
void Graph<_Key, _Tp>::addVertex(_Key key){
    graph[key] = AdjNode<_Key, _Tp>();
}

template<class _Key, class _Tp>
void Graph<_Key, _Tp>::removeVertex(_Key key){
    graph.erase(key);
}

template<class _Key, class _Tp>
bool Graph<_Key, _Tp>::hasVertex(_Key key){
    return graph.find(key) != graph.end();
}

template<class _Key, class _Tp>
vector<_Key> Graph<_Key, _Tp>::getVertices(){
    vector<_Key> vertices;
    for(auto it = graph.begin(); it != graph.end(); it++){
        vertices.push_back(it->first);
    }
    return vertices;
}

template<class _Key, class _Tp>
void Graph<_Key, _Tp>::addEdge(_Key src, _Key dest, _Tp weight){
    graph[src].addEdge(dest, weight);
    graph[dest].addEdge(src, weight);
}

template<class _Key, class _Tp>
void Graph<_Key, _Tp>::removeEdge(_Key src, _Key dest){
    graph[src].removeEdge(dest);
}

template<class _Key, class _Tp>
bool Graph<_Key, _Tp>::hasEdge(_Key src, _Key dest){
    return graph[src].hasEdge(dest);
}

template<class _Key, class _Tp>
_Tp Graph<_Key, _Tp>::getWeight(_Key src, _Key dest){
    return graph[src].getWeight(dest);
}

template<class _Key, class _Tp>
void Graph<_Key, _Tp>::printGraph(){
    for(auto it = graph.begin(); it != graph.end(); it++){
        cout << it->first << ": ";
        it->second.printAdjNode();
    }
}

template<class _Key, class _Tp>
typename Graph<_Key, _Tp>::_DijkstraOut Graph<_Key, _Tp>::dijkstra(_Key src, _Key dest){
    priority_queue<_PQTemp, vector<_PQTemp>, greater<_PQTemp>> pq;
    vector<_Key> vertices = getVertices();
    map<_Key, _Tp> dist;
    map<_Key, bool> visited;
    map<_Key, _Key> parent;

    for(auto it = vertices.begin(); it != vertices.end(); it++){
        dist[*it] = INT_MAX;
        visited[*it] = false;
        parent[*it] = "";
    }

    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()){
        _PQTemp temp = pq.top();
        _Key u = temp.second;
        _Tp w = temp.first;
        pq.pop();

        for(auto it = graph[u].begin(); it != graph[u].end(); it++){
            _Key v = it->first;
            _Tp weight = it->second;

            if(!visited[v] && dist[v]>(dist[u]+weight)){
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }

        visited[u] = true;
    }

    _DijkstraOut out;
    out.first = dist[dest];

    _Key temp = dest;
    while(temp != src){
        out.second.push_back(temp);
        temp = parent[temp];
    }
    out.second.push_back(src);
    reverse(out.second.begin(), out.second.end());

    return out;
}


template<class _Key, class _Tp>
class PMPMLMap: public Graph<_Key, _Tp>{
    private:
        string fname;
        int maxLength=INT_MIN;
        _Key src, dest;

        void centerWords(vector<_Key> &vec, const char& delimiter = '|'){
            int count=0, flag=1;
            while(count<vec.size() && flag){
                for(int i=0; i<4; i++){
                    if(count<vec.size()){
                        cout << setw(maxLength) << vec[count].c_str() << delimiter;
                        count++;
                    }else{
                        flag=0;
                        break;
                    }
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
                if(item.size() != 3){
                    cout << "Error: The data no. "<<count<<" is not in the correct format" << endl;
                }
                try{
                    this->addEdge(item[0], item[1], stoi(item[2]));
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
            
            try{
                vector<vector<string>> data = readCSV();
                insertDataToGraph(data);
            }catch(const char* msg){
                cout << msg << endl;
            }
        }

        void displayWelcome(){
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
            cout<<endl;
        }

        void findShortestPath(){
            cout<<"Finding shortest path..."<<endl;
            
            typename Graph<_Key, _Tp>::_DijkstraOut ans = this->dijkstra(src, dest);
            
            if(ans.second.size() == 0){
                cout<<"No path found"<<endl;
            }else{
                cout<<"Shortest path from "<<src<<" to "<<dest<<" is: "<<endl;    
                for(int i=0; i<ans.second.size(); i++){
                    if(i==ans.second.size()-1){
                        cout<<ans.second[i]<<endl;
                    }else{
                        cout<<ans.second[i]<<" -> ";
                    }
                }
                cout<<endl;
                cout<<"Distance: "<<ans.first<<" M"<<endl;
            }

            printMultiple('=', 122, true);
        }

        void displayEnd(){
            printMultiple('=', 45);
            cout<<" THANK YOU FOR USING PMPML APP ";
            printMultiple('=', 46, true);
        }
};

int main(){
    char choice;
    PMPMLMap<string, int> pmpml("pmpml.csv");
    pmpml.displayWelcome();
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

    pmpml.displayEnd();

    return 0;
}