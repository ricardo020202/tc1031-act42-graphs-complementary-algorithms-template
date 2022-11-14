#ifndef ACTIVITY_H
#define ACTIVITY_H

// =========================================================
// File: actitivy.h
// Author: José Ricardo Rosales Castañeda - A01709449
// Author: Uri Gopar - Axxxxxxxxx
// Date: 13/11/2022
// =========================================================

#include "ugraph.h"

// =========================================================
// Function: dfs2
// Parameters: v - vertex to start the search
// @param graph: graph to be traversed
// @param reached: array of visited nodes
// @param TS: stack of nodes
// @complexity O(n)
// =========================================================
template <class Vertex>
void dfs2(Vertex v, const UnweightedGraph<Vertex>* graph, std::vector<bool> &reached, std::stack<Vertex> &TS) {
  typename std::set<Vertex>::iterator itr;
  reached[v] = true;

  std::set<Vertex> connected = graph->getConnectionFrom(v);
  for (itr = connected.begin(); itr != connected.end(); itr++) {
    if (!reached[*itr]){
      dfs2(*itr, graph, reached, TS);
    }
  }
  TS.push(v);
}

// =========================================================
// Function: topologicalSort
// Parameters: graph - graph to be sorted
// @return: string with the sorted graph
// @complexity O(n)
// =========================================================
template <class Vertex>
std::string topologicalSort(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  std::stringstream aux;
  std::vector<bool> reached(graph->getVertexes().size(), false);
  std::stack<Vertex> TS;

  for (auto v : graph->getVertexes()){
    if (!reached[v]){
      dfs2(v, graph, reached, TS);
    }
  }

  aux << "[";
  while (!TS.empty()){
    aux << TS.top();
    TS.pop();
    if (TS.size() != 0){
      aux << " ";
    }
  }
  aux << "]";
 
  return aux.str();
}

// =========================================================
// Function: isBipartite
// Parameters: graph - graph to be checked
// @return: true if the graph is bipartite, false otherwise
// @complexity O(n)
// =========================================================
template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  typename std::set<Vertex>::iterator j;
  std::vector<bool> reached(graph->getVertexes().size(), false);
  std::vector<bool> color(graph->getVertexes().size(), false);
  std::queue<Vertex> Q;

  for (auto vertex : graph->getVertexes()){
    if (!reached[vertex]){
      Q.push(vertex);
      reached[vertex] = true;
      color[vertex] = true;
      while (!Q.empty()){
        Vertex u = Q.front();
        Q.pop();
        for (auto vertexAlt : graph->getConnectionFrom(u)){
          if (!reached[vertexAlt]){
            Q.push(vertexAlt);
            reached[vertexAlt] = true;
            color[vertexAlt] = !color[u];
          }
          else if (color[vertexAlt] == color[u]){
            return false;
          }
        }
      }
    }
  }
  return true;
}

// =========================================================
// Function: isCyclic
// Parameters: v - vertex to start the search
// @param graph: graph to be traversed
// @param reached: array of visited nodes
// @param parent: array of parent nodes
// @return: true if the graph is cyclic, false otherwise
// @complexity O(n)
// =========================================================
template <class Vertex>
bool isCyclic(Vertex v, const UnweightedGraph<Vertex>* graph, std::set<Vertex> &reached, Vertex parent) {
  typename std::set<Vertex>::iterator itr;
  reached.insert(v);
  std::set<Vertex> connected = graph->getConnectionFrom(v);
  for (itr = connected.begin(); itr != connected.end(); itr++) {
    if (reached.find(*itr) == reached.end()){
      if (isCyclic(*itr, graph, reached, v)){
        return true;
      }
    }
    else if (*itr != parent){
      return true;
    }
  }
  return false;
}

// =========================================================
// Function: isTree
// Parameters: graph - graph to be checked
// @return: true if the graph is a tree, false otherwise
// @complexity O(n)
// =========================================================
template <class Vertex>
bool isTree(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  std::set<Vertex> reached;
  for (auto vertex : graph->getVertexes()){
    if (reached.find(vertex) == reached.end()){
      if (isCyclic(vertex, graph, reached, -1)){
        return false;
      }
    }
  }
  return true;
}

#endif /* ACTIVITY_H */
