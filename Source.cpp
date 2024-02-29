#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
public:
    vector<vector<int>> adjacencyMatrix;
    vector<int> durations;
    vector<int> earliestStartTime;
    vector<int> latestFinishTime;
    vector<int> slack;
    int numVertices;
    int criticalPathLength;

    Graph(const vector<vector<int>>& adjacencyMatrix, const vector<int>& durations) {
        this->adjacencyMatrix = adjacencyMatrix;
        this->durations = durations;
        numVertices = adjacencyMatrix.size();
        criticalPathLength = 0;
    }

    void calculateEarliestStartTime() {
        queue<int> q;
        vector<int> inDegree(numVertices, 0);

        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    inDegree[j]++;
                }
            }
        }

        for (int i = 0; i < numVertices; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                earliestStartTime[i] = 0;
            }
        }

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int i = 0; i < numVertices; i++) {
                if (adjacencyMatrix[current][i] == 1) {
                    inDegree[i]--;
                    earliestStartTime[i] = max(earliestStartTime[i], earliestStartTime[current] + durations[current]);
                    if (inDegree[i] == 0) {
                        q.push(i);
                    }
                }
            }
        }
    }

    void calculateLatestFinishTime() {
        latestFinishTime[numVertices - 1] = earliestStartTime[numVertices - 1];

        for (int i = numVertices - 2; i >= 0; i--) {
            latestFinishTime[i] = INT_MAX;
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    latestFinishTime[i] = min(latestFinishTime[i], latestFinishTime[j] - durations[i]);
                }
            }
        }
    }

    void calculateSlack() {
        for (int i = 0; i < numVertices; i++) {
            slack[i] = latestFinishTime[i] - earliestStartTime[i];
        }
    }

    void calculateCriticalPathLength() {
        for (int i = 0; i < numVertices; i++) {
            if (slack[i] == 0) {
                criticalPathLength += durations[i];
            }
        }
    }

    /*void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }*/

    void printCriticalPath() {
        cout << "Critical Path: ";
        for (int i = 0; i < numVertices; i++) {
            if (slack[i] == 0) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    void printTable() {
        cout << "Vertex\tDuration\tEarly Start\tLate Finish\tSlack\n";
        for (int i = 0; i < numVertices; i++) {
            cout << i << "\t" << durations[i] << "\t\t" << earliestStartTime[i] << "\t\t" << latestFinishTime[i] << "\t\t" << slack[i] << endl;
        }
    }

    void printCriticalPathLength() {
        cout << "Critical Path Length: " << criticalPathLength << endl;
    }
};

int main() {
    int numVertices;
    cout << "Input example (with the number of vertices equal to 3): " << endl;
    cout << "1 0 0 " << endl;
    cout << "0 1 0 " << endl;
    cout << "0 0 1 " << endl;
    cout << "5 6 4  -  The duration of the work (the first number corresponds to the first job, etc.)" << endl;
    cout << endl;
    cout << endl;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the adjacency matrix (separated by a space), then enter the duration of the work on the next line (separated by a space): " << endl;

    vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices));
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cin >> adjacencyMatrix[i][j];
        }
    }

    vector<int> durations(numVertices);
    for (int i = 0; i < numVertices; i++) {
        cin >> durations[i];
    }

    Graph graph(adjacencyMatrix, durations);
    graph.earliestStartTime.resize(graph.numVertices);
    graph.latestFinishTime.resize(graph.numVertices);
    graph.slack.resize(graph.numVertices);

    graph.calculateEarliestStartTime();
    graph.calculateLatestFinishTime();
    graph.calculateSlack();
    graph.calculateCriticalPathLength();

    //graph.printGraph();
    graph.printCriticalPath();
    graph.printTable();
    graph.printCriticalPathLength();

    return 0;
}