#pragma once
#include <vector>
#include<map>
#include<string>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

namespace GraphNS{

/*
_Key: It is the adjacent vertex of the current vertex.
_Tp: It is the type of cost of the edge.
_Value: It is the pair which contain the time and distance as cost of the edge.
*/
template<class _Key, class _Tp, class _Value=pair<_Tp, _Tp>>
class Edge{
/*
It is the class for storing the Edge of the graph.
*/
    map<_Key, _Value> adj;

    public:

        void addEdge(_Key v, _Value cost){
            adj[v] = cost;
        }

        void delEdge(_Key v){
            adj.erase(v);
        }

        void delAllEdges(){
            adj.clear();
        }

        bool hasEdge(_Key v){
            return adj.find(v) != adj.end();
        }

        int getSize(){
            return adj.size();
        }

        _Tp getDistance(_Key v){
            return adj[v].first;
        }

        _Tp getTime(_Key v){
            return adj[v].second;
        }

        void printEdge(){
            for(auto i : adj){
                cout << i.first << "(" << i.second.first << ", "<< i.second.second << ") -> ";
            }
            cout<<"NULL";
        }

        typename map<_Key, _Value>::iterator begin(){
            return adj.begin();
        }

        typename map<_Key, _Value>::iterator end(){
            return adj.end();
        }
};


/*
_Key: The type of the vertex
_Tp: The type of the cost of the edge
_Value: The type of Edge class which has the adjacent vertex and the cost of the edge
*/
template<class _Key, class _Tp, class _Value=Edge<_Key, _Tp>>
class Graph{
/*
It is the class for storing the Graph.
*/
    protected:
        map<_Key, _Value> graph;

        _Tp compareTo(_Value a, _Key v, int edgeCost=0){
            if(edgeCost == 0){
                return a.getDistance(v);
            }
            
            return a.getTime(v);
        }

    public:
        void addVertex(_Key v){
            graph[v] = Edge<_Key, _Tp>();
        }

        void addEdge(_Key v, _Key u, _Tp distance, _Tp time){
            pair<_Tp, _Tp> p = make_pair(distance, time);
            graph[v].addEdge(u, p);
            graph[u].addEdge(v, p);
        }

        void delVertex(_Key v){
            graph[v].delAllEdges();
            graph.erase(v);
        }

        void delEdge(_Key v, _Key u){
            graph[v].delEdge(u);
            graph[u].delEdge(v);
        }

        bool hasVertex(_Key v){
            return graph.find(v) != graph.end();
        }

        bool hasEdge(_Key v, _Key u){
            return graph[v].hasEdge(u);
        }

        vector<_Key> getVertices(){
            vector<_Key> v;
            for(auto i : graph){
                v.push_back(i.first);
            }
            return v;
        }

        pair<_Key, _Value> getVertex(_Key v){
            return make_pair(v, graph[v]);
        }

        void printGraph(){
            for(auto i : graph){
                cout << i.first << ": ";
                i.second.printEdge();
                cout << endl;
            }
        }

        void printVertex(){
            for(auto i : graph){
                cout << i.first << " ";
            }
            cout << endl;
        }

        int totalVertex(){
            return graph.size();
        }

        int totalEdge(){
            int count = 0;
            for(auto i : graph){
                count += i.second.getSize();
            }
            return count/2;
        }

        pair<vector<_Key>, _Tp> dijkstraAlgo(_Key src, _Key dest, int edgeCost=0){
            priority_queue<pair<_Tp, _Key>> pq;     //It is used to store the vertex and the cost of the vertex.
            unordered_map<_Key, pair<_Tp, vector<_Key>>> distPath;  //It is used to store the distance and the path of the vertex.

            pq.push(make_pair(0, src));
            distPath[src] = pair<_Tp, vector<_Key>>(0, vector<_Key>());
            distPath[src].second.push_back(src);

            while(!pq.empty()){
                pair<_Tp, _Key> p = pq.top();
                pq.pop();

                pair<_Key, _Value> v = this->getVertex(p.second);

                for(auto edges=v.second.begin(); edges!=v.second.end(); edges++){
                    if(
                        distPath.find(edges->first) == distPath.end() ||
                        (distPath[edges->first].first > distPath[p.second].first + compareTo(v.second, edges->first, edgeCost))
                    ){
                        pair<_Tp, vector<_Key>> temp;
                        temp.first = distPath[p.second].first + compareTo(v.second, edges->first, edgeCost);
                        temp.second = distPath[p.second].second;
                        temp.second.push_back(edges->first);
                        distPath[edges->first] = temp;

                        pq.push(make_pair(distPath[edges->first].first, edges->first));
                    }
                }
            }
            
            pair<vector<_Key>, _Tp> result;
            result.first = distPath[dest].second;
            result.second = distPath[dest].first;

            return result;
        }
};

}

#endif // DIJKSTRA_HPP_INCLUDED