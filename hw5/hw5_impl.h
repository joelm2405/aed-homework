#ifndef HW5_IMPL_H
#define HW5_IMPL_H

#include <string>
#include <vector>

#include "hw5.h"

void add_edge(std::vector<std::vector<int>>& graph, int from, int to) {
  graph[from].push_back(to); 
  graph[to].push_back(from);
}


int n_vertices(std::vector<std::vector<int>> const& graph) {
  return graph.size();
}

int n_edges(std::vector<std::vector<int>> const& graph) {
  int edges = 0;
  for (const auto& adj_list : graph) {
    edges += adj_list.size(); 
  }
  return edges / 2; 
}

std::vector<int> BFS(std::vector<std::vector<int>> const& graph, int from) {
  std::vector<bool> visited(graph.size(), false);
  std::vector<int> ret; 
  std::queue<int> q;
  
  visited[from] = true;
  q.push(from);
  
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    ret.push_back(current); 
    
  for (int neighbor : graph[current]) {
    if (!visited[neighbor]) {
        visited[neighbor] = true;
        q.push(neighbor);
      }
    }
  }
  
  return ret;
}


void DFS_helper(const std::vector<std::vector<int>>& graph, int from, std::vector<bool>& visited, std::vector<int>& ret) {
  visited[from] = true;
  ret.push_back(from); 
  
  for (int neighbor : graph[from]) {
    if (!visited[neighbor]) {
      DFS_helper(graph, neighbor, visited, ret);
    }
  }
}

std::vector<int> DFS(std::vector<std::vector<int>> const& graph, int from) {
  std::vector<bool> visited(graph.size(), false);
  std::vector<int> ret;
  DFS_helper(graph, from, visited, ret);
  return ret;
}


std::vector<std::vector<int>> connected_components(std::vector<std::vector<int>> const& graph) {
  std::vector<bool> visited(graph.size(), false);
  std::vector<std::vector<int>> components;
  
  for (int i = 0; i < graph.size(); ++i) {
    if (!visited[i]) {
      std::vector<int> component;
      DFS_helper(graph, i, visited, component); 
      components.push_back(component);
    }
  }
  
  return components;
}

int n_connected_components(std::vector<std::vector<int>> const& graph) {
  std::vector<std::vector<int>> components = connected_components(graph);
  return components.size();
}


#endif
