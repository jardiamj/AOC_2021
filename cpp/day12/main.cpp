#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <memory>

using namespace std;
// Type definitions for graph nomenclature
typedef string vertex;
typedef vector<vertex> edge_list;
typedef shared_ptr<vector<vertex>> edges_ptr;
typedef unordered_map<vertex, edges_ptr> connections;
typedef unordered_set<vertex> vertex_set;

void add_connections(string& line,
                     connections& cave_map,
                     unordered_set<vertex>& s_caves);

void print_map(connections& cave_map);

int get_all_paths(connections& cave_map,
                  const vertex& start,
                  vertex_set visited,
                  int& total_paths,
                  vertex small_cave,
                  string path);


int main(int argc, char* argv[]) {
    string file_name = "cave_input.txt";
    ifstream in_file(file_name);

    if (!in_file.good()) {
        cerr << "File " << file_name << " Couldn't be opened.\n";
        exit(EXIT_FAILURE);
    }

    // Read cave map from file
    connections cave_map;
    unordered_set<vertex> small_caves;
    string line;
    while(in_file >> line) {
        add_connections(line, cave_map, small_caves);
    }

    print_map(cave_map);
    cout << "Small caves: ";
    for (vertex c : small_caves) {
        cout << c << ", ";
    }
    cout << endl;

    int total_paths = 0;
    vertex v_empy = "";
    string path = "";
    int no_repeat = get_all_paths(cave_map, "start", {}, total_paths, v_empy, path);

    int second_visits = no_repeat;
    for (vertex cave : small_caves) {
        cout << "visiting " << cave << " twice.\n";
        path = "";
        total_paths = 0;
        int tmp = get_all_paths(cave_map, "start", {}, total_paths, cave, path);
        cout << "Total here: " << tmp << endl;
        second_visits += tmp - no_repeat;
    }
    vertex small_v = "b";
    
    cout << "Total Paths: " << second_visits << endl;
}

void add_connections(string& line,
                     connections& cave_map,
                     unordered_set<vertex>& s_caves)
{
    size_t separator_pos = line.find('-');
    vertex v1 = line.substr(0, separator_pos);
    vertex v2 = line.substr(separator_pos + 1, string::npos);

    if (cave_map.find(v1) == cave_map.end()) {
        cave_map[v1] = edges_ptr(new edge_list);
    }

    if (cave_map.find(v2) == cave_map.end()) {
        cave_map[v2] = edges_ptr(new edge_list);
    }

    // Connection v1 -> v2
    cave_map[v1]->push_back(v2);

    // Connection v2 -> v1
    cave_map[v2]->push_back(v1);

    if (islower(v1[0]) && v1 != "start" && v1 != "end") s_caves.insert(v1);
    if (islower(v2[0]) && v2 != "start" && v2 != "end") s_caves.insert(v2);
}

void print_map(connections& cave_map) {
    for (auto it = cave_map.begin(); it != cave_map.end(); it++) {
        cout << it->first << " -> ";
        auto e_it = it->second->begin();
        cout << "[" << *e_it++;
        for (; e_it != it->second->end(); e_it++) {
            cout << ", " << *e_it;
        }
        cout << "]\n";
    }
}

// visited set is passed by copy because we need a local copy per stack call
// in order to get all possible paths.
int get_all_paths(connections& cave_map,
                  const vertex& start,
                  vertex_set visited,
                  int& total_paths,
                  vertex small_cave,
                  string path)
{
    path += "->" + start;
    if (start == "end") {
        total_paths++;
        // cout << path << '\n';
        return total_paths;
    }

    if (islower(start[0])) { // lower case can only be visited once
        if (start == small_cave) { // second visit
            small_cave = "";
        } else {
            visited.insert(start);
        }
    }

    edges_ptr cur_edges_ptr = cave_map[start];
    for (vertex v : *cur_edges_ptr) {
        if (visited.find(v) == visited.end()) { // not visited
            get_all_paths(cave_map, v, visited, total_paths, small_cave, path);
        }
    }

    return total_paths;
}