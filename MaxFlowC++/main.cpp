#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define V 12

using namespace std;

int maximumFlow(int [][V], int, int);
bool pathToSink(int [][V], int [], int, int);

int main()
{
    int graph[V][V] = { {0,1,1,1,1,1,0,0,0,0,0,0},
                        {0,0,0,0,0,0,1,1,1,0,0,0},
                        {0,0,0,0,0,0,0,1,0,0,0,0},
                        {0,0,0,0,0,0,1,1,0,0,0,0},
                        {0,0,0,0,0,0,0,0,1,0,1,0},
                        {0,0,0,0,0,0,0,0,0,1,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0}
                      };

    double start = double(clock()) / CLOCKS_PER_SEC;

    cout << "The maximum possible flow is "
         << maximumFlow(graph, 0, V - 1) << endl;

    double finish = double(clock()) / CLOCKS_PER_SEC;
    double elapsed = finish - start;

    cout << "Elapsed time was: " << elapsed << endl;

    return 0;
}

int maximumFlow(int graph[][V], int source, int sink)
{

    int residualGraph[V][V];

    // Construct our residual graph
    for(int v1 = 0; v1 < V; v1++)
    {
        for(int v2 = 0; v2 < V; v2++)
        {
            residualGraph[v1][v2] = graph[v1][v2];
        }
    }

    int maxFlow = 0;

    // This gets updated by pathToSink
    int parent[V];

    // Keep augmenting flow while there exists path from source to sink
    while(pathToSink(residualGraph, parent, source, sink))
    {
        int currentFlow = INT_MAX;

        // Find the bottleneck of the flow through the path
        for(int v2 = sink; v2 != source; v2 = parent[v2])
        {
            int v1 = parent[v2];
            currentFlow = min(currentFlow, residualGraph[v1][v2]);
        }

        // Update capacity of edges in residual graph
        for(int v2 = sink; v2 != source; v2 = parent[v2])
        {
            int v1 = parent[v2];
            residualGraph[v1][v2] -= currentFlow;
            residualGraph[v2][v1] += currentFlow;
        }

        maxFlow += currentFlow;
    }

    return maxFlow;
}

bool pathToSink(int residualGraph[][V], int parent[], int source, int sink)
{
    // All vertices are not visited initially
    bool visited[V];
    fill_n(visited, V, false);

    // Put the source node in queue initially
    // and visit it
    vector<int> queue;
    queue.push_back(source);
    visited[source] = true;

    // Do breadth-first search to see
    // if we can find a path to the sink
    // from the source node
    while(!queue.empty())
    {
        int v1 = queue.front();
        queue.erase(queue.begin());

        for(int v2 = 0; v2 < V; v2++)
        {
            if(residualGraph[v1][v2] > 0 and !visited[v2])
            {
                queue.push_back(v2);
                visited[v2] = true;
                parent[v2] = v1;
            }
        }
    }

    // Return if we were able to find a path
    return visited[sink];
}
