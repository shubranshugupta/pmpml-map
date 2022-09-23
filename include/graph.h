#pragma once
#include<map>
#include<iostream>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

namespace GraphNS{

template<class _Key, class _Tp>
class AdjNode{
    private:
        map<_Key, _Tp> adjNode;

    public:
        AdjNode();
        void addEdge(_Key key, _Tp value);
        void removeEdge(_Key key);
        void removeAllEdges();
        bool hasEdge(_Key key);
        _Tp getWeight(_Key key);
        void printAdjNode();
        typename map<_Key, _Tp>::iterator begin();
        typename map<_Key, _Tp>::iterator end();
};

template<class _Key, class _Tp>
class Graph{
    private:
        using _Value = AdjNode<_Key, _Tp>;
        map<_Key, _Value> graph;

    public:
        using _DijkstraOut = pair<_Tp, vector<_Key>>;
        using _PQTemp = pair<_Tp, _Key>;

        Graph();
        void addVertex(_Key key);
        void removeVertex(_Key key);
        bool hasVertex(_Key key);
        vector<_Key> getVertices();
        void addEdge(_Key src, _Key dest, _Tp weight);
        void removeEdge(_Key src, _Key dest);
        bool hasEdge(_Key src, _Key dest);
        _Tp getWeight(_Key src, _Key dest);
        void printGraph();
        _DijkstraOut dijkstra(_Key src, _Key dest);
};

}

#endif