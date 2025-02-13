#include <iostream>
#include <chrono> //it's not currently used, i used it for profiling 

/*

This C++ program processes multiple graphs by reading their adjacency lists, sorting their degree sequences,
and performing various graph analyses such as connectivity, bipartiteness, and graph coloring using different
heuristics (Greedy, LF, and SLF). It implements DFS for connected components, BFS for bipartiteness checks,
and quicksort for sorting degree sequences while also computing complement edges. Some features,
like eccentricity calculation, planarity check, and C4 subgraph counting, are placeholders and currently output "?".


The LFC and SLF colorization algorithms present the most significant challenge in terms of intellectual effort
and present the most convoluted logic. We leverage a stabilized quicksort to generate a map containing the
original indices sorted by their corresponding degree values. Both LFC and SLFC algorithms utilize this map.
The SLFC algorithm introduces a slightly more intricate approach. It tracks the prevalence of distinct saturation
levels and the maximum value. Subsequently, it "excludes" colored values from consideration and extracts the vertex
with a saturation level matching the maximum. This, while seemingly unorthodox, represents an attempt to optimize
time complexity. Initially, I pursued an approach that involved searching for the vertex with the highest
saturation/degree value across all iterations. Interestingly, this method did not yield a significant performance
improvement. The code itself could benefit from refactoring efforts, further optimization opportunities,
and implementation of the remaining functionalities.

*/


using namespace std;
using namespace std::chrono;


void custom_swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


struct Node {
    int vertex;
    Node* next;
};

struct Graph {
    int n;
    Node** adj;
    int* degree_sequence_cache;

    Graph(int vertices) : n(vertices) {
        adj = new Node * [n];
        for (int i = 0; i < n; ++i) {
            adj[i] = nullptr;
        }
        degree_sequence_cache = nullptr;
    }


    ~Graph() {
        delete[] degree_sequence_cache;

        for (int i = 0; i < n; ++i) {
            Node* node = adj[i];
            while (node != nullptr) {
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] adj;
    }

    Graph(const Graph& other) : n(other.n) {
        adj = new Node * [n];
        for (int i = 0; i < n; ++i) {
            adj[i] = nullptr;
            Node* node = other.adj[i];
            while (node != nullptr) {
                add_edge(i, node->vertex);
                node = node->next;
            }
        }
    }

    void add_edge(int u, int v) {
        Node* node = new Node;
        node->vertex = v;
        node->next = adj[u];
        adj[u] = node;
    }

    void quickSort(int* arr, int* original_indices, int low, int high) {
        if (low < high) {
            int pivot = partition(arr, original_indices, low, high);

            quickSort(arr, original_indices, low, pivot - 1);
            quickSort(arr, original_indices, pivot + 1, high);
        }
    }

    int partition(int* arr, int* original_indices, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j) {
            if (arr[j] > pivot || (arr[j] == pivot && original_indices[j] < original_indices[high])) {
                ++i;
                custom_swap(arr[i], arr[j]);
                custom_swap(original_indices[i], original_indices[j]);
            }
        }
        custom_swap(arr[i + 1], arr[high]);
        custom_swap(original_indices[i + 1], original_indices[high]);
        return (i + 1);
    }



    void sort_degree_sequence(int* degree_seq_sorted, int* original_indices) {
        quickSort(degree_seq_sorted, original_indices, 0, n - 1);
    }




    void dfs(int u, bool* visited) {
        visited[u] = true;
        Node* node = adj[u];
        while (node != nullptr) {
            int v = node->vertex;
            if (!visited[v]) {
                dfs(v, visited);
            }
            node = node->next;
        }
    }

    int number_of_components() {
        bool* visited = new bool[n];
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }
        int components = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++components;
                dfs(i, visited);
            }
        }

        delete[] visited;
        return components;
    }

    bool is_bipartite() {
        int* color = new int[n];
        for (int i = 0; i < n; ++i) {
            color[i] = -1;
        }
        int* q = new int[n];
        int front = 0, rear = 0;

        for (int i = 0; i < n; ++i) {
            if (color[i] == -1) {
                color[i] = 0;
                q[rear++] = i;

                while (front != rear) {
                    int u = q[front++];
                    Node* node = adj[u];

                    while (node != nullptr) {
                        int v = node->vertex;
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q[rear++] = v;
                        }
                        else if (color[v] == color[u]) {
                            delete[] color;
                            delete[] q;
                            return false;
                        }
                        node = node->next;
                    }
                }
            }
        }

        delete[] color;
        delete[] q;
        return true;
    }

    int* greedy_coloring() {
        int* color = new int[n];
        bool* available = new bool[n];

        for (int i = 0; i < n; ++i) {
            color[i] = -1;
        }

        color[0] = 1;

        for (int u = 1; u < n; ++u) {
            for (int i = 0; i < n; ++i) {
                available[i] = true;
            }

            Node* node = adj[u];
            while (node != nullptr) {
                int v = node->vertex;
                if (color[v] != -1) {
                    available[color[v]] = false;
                }
                node = node->next;
            }

            int cr;
            for (cr = 1; cr < n + 1; cr++) {
                if (available[cr]) {
                    break;
                }
            }

            color[u] = cr;
        }

        delete[] available;

        return color;
    }



    void LF_coloring(int* colors, int* original_indices) {
        for (int i = 0; i < n; ++i) {
            colors[i] = 0;
        }

        bool* available = new bool[n + 1];

        for (int i = 0; i < n; ++i) {
            int max_degree = -1;
            int vertex = -1;

            vertex = original_indices[i];

            if (vertex == -1) break;

            for (int j = 0; j < n + 1; ++j) {
                available[j] = true;
            }

            Node* node = adj[vertex];
            while (node != nullptr) {
                int v = node->vertex;
                if (colors[v] != 0) {
                    available[colors[v]] = false;
                }
                node = node->next;
            }

            int cr;
            for (cr = 1; cr <= n; ++cr) {
                if (available[cr]) {
                    break;
                }
            }

            colors[vertex] = cr;
        }

        delete[] available;
    }

    void SLF_coloring(int* colors, int* original_indices) {


        for (int i = 0; i < n; ++i) {
            colors[i] = 0;
        }

        int* saturation = new int[n];
        int* saturation_count = new int[n];
        int max_sat = 0;

        int* degree = new int[n];
        for (int i = 0; i < n; ++i) {
            saturation[i] = 0;
            saturation_count[i] = 0;

        }
        saturation_count[0] = n;


        for (int i = 0; i < n; ++i) {
            int max_saturation_vertex = -1;
            int max_saturation = -1;
            int max_degree = -1;

            for (int j = 0; j < n; ++j) {
                int p = original_indices[j];
                if (colors[p] == 0) {
                    if (saturation[p] == max_sat) {
                        max_saturation = saturation[p];
                        max_saturation_vertex = p;
                        break;
                    }
                }
            }
            int saturationmaxsat = saturation_count[max_sat];

            colors[max_saturation_vertex] = find_first_available_color(max_saturation_vertex, colors);
            saturation_count[saturation[max_saturation_vertex]]--;
            if (saturation_count[max_sat] == 0) {
                int search = saturation[max_saturation_vertex] - 1;
                while (saturation_count[search] == 0 && search != 0) {
                    search--;
                }
                max_sat = search;
            }


            Node* node = adj[max_saturation_vertex];
            while (node != nullptr) {
                int v = node->vertex;
                if (colors[v] == 0) {
                    bool found = false;
                    Node* node2 = adj[v];
                    while (node2 != nullptr) {
                        if (colors[node2->vertex] == colors[max_saturation_vertex] && node2->vertex != max_saturation_vertex) {
                            found = true;
                            break;
                        }
                        node2 = node2->next;
                    }
                    if (!found) {
                        saturation[v]++;
                        saturation_count[saturation[v]]++;
                        saturation_count[saturation[v] - 1]--;

                        if (saturation[v] > max_sat) {
                            max_sat = saturation[v];
                        }
                    }
                }
                node = node->next;
            }
        }

        delete[] saturation;
        delete[] degree;
    }



    int find_first_available_color(int vertex, int* colors) {
        bool* used_colors = new bool[n + 1];
        for (int i = 0; i <= n; ++i) {
            used_colors[i] = false;
        }

        Node* node = adj[vertex];
        while (node != nullptr) {
            int v = node->vertex;
            if (colors[v] != 0) {
                used_colors[colors[v]] = true;
            }
            node = node->next;
        }

        int cr;
        for (cr = 1; cr <= n; cr++) {
            if (!used_colors[cr]) {
                break;
            }
        }

        delete[] used_colors;
        return cr;
    }

};

int main() {
    int k;
    scanf_s("%d", &k);

    for (int graph_idx = 0; graph_idx < k; ++graph_idx) {
        int n;
        scanf_s("%d", &n);
        int* degree_seq = new int[n];
        int* degree_seq_sorted = new int[n];
        int* original_indices = new int[n];
        int* original_indices2 = new int[n];


        Graph g(n);
        int possible = n * (n - 1);
        int actual = 0;
        // Read degree sequence and build graph
        for (int i = 0; i < n; ++i) {
            cin >> degree_seq[i];
            actual += degree_seq[i];
            original_indices[i] = i;
            for (int j = 0; j < degree_seq[i]; ++j) {
                int neighbour;
                cin >> neighbour;
                g.add_edge(i, neighbour - 1);
            }
        }

        // Sort degree sequence and create map of original indices
        g.sort_degree_sequence(degree_seq, original_indices);
        int complement_edges = (possible - actual) / 2;


        for (int i = 0; i < n; ++i) {
            printf("%d ", degree_seq[i]);
        }
        printf("\n");





        // Number of Components
        int num_components = g.number_of_components();
        printf("%d\n", num_components);

        // Bipartiteness
        bool bipartite = g.is_bipartite();
        printf("%s\n", bipartite ? "T" : "F");

        // Eccentricities
        printf("?\n");

        // Plan
        printf("?\n");

        // Greedy Coloring
        int* greedy_colors = g.greedy_coloring();
        for (int i = 0; i < n; ++i) {
            printf("%d ", greedy_colors[i]);
        }
        printf("\n");
        delete[] greedy_colors;

        // LF Coloring
        int* lf_colors = new int[n];
        g.LF_coloring(lf_colors, original_indices);
        for (int i = 0; i < n; ++i) {
            printf("%d ", lf_colors[i]);
        }
        printf("\n");
        delete[] lf_colors;

        // SLF Coloring
        int* slf_colors = new int[n];
        g.SLF_coloring(slf_colors, original_indices);
        for (int i = 0; i < n; ++i) {
            printf("%d ", slf_colors[i]);
        }
        printf("\n");
        delete[] slf_colors;
        delete[] degree_seq;


        // Count C4 subgraphs
        printf("?\n");

        // Count complement edges
        printf("%d\n", complement_edges);
    }

    return 0;
}