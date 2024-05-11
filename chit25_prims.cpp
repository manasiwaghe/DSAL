        /*
 You have a business with several offices; you want to lease phone lines
 to connect them up with each other; and the phone company charges
 different amounts of money to connect different pairs of cities. You
 want a set of lines that connects all your offices with a minimum total
 cost. Solve the problem by suggesting appropriate data structures.
 */

#include <iostream>
#define INF 1e9

using namespace std;

class Graph
{
    int **adjMatrix; //2D array of integers representing the adjacency matrix of the graph.
    string *cities;
    int nv;

public:
    Graph(int nv)
    {
        this->nv = nv;
        adjMatrix = new int *[nv];
        cities = new string[nv];

        for (int i = 0; i < nv; i++)
        {
            adjMatrix[i] = new int[nv];

            for (int j = 0; j < nv; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }

    int getIndex(string city)
    {
        for (int i = 0; i < nv; i++)
        {
            if (cities[i] == city)
            {
                return i;
            }
        }
        return -1;
    }
    void addEdge(int src, int des, int weight)
    {
        adjMatrix[src][des] = weight;
        adjMatrix[des][src] = weight;
    }
    void initGraph()
    {
        string des;
        int weight;
        int desId, srcId;
        // take all cities
        for (int i = 0; i < nv; i++)
        {
            cout << "Enter city [" << i << "] : ";
            cin >> cities[i];
        }

        for (int i = 0; i < nv; i++)
        {
            for (int j = 0; j < nv - 1; j++)
            {
                cout << "Add city connected to " << cities[i] << " : ";
                cin >> des;
                desId = getIndex(des);
                srcId = getIndex(cities[i]);
                
                if (srcId == -1 || desId == -1)
                {
                    break;
                }

                cout << "Enter the cost of connection : ";
                cin >> weight;

                // add edge
                addEdge(srcId, desId, weight);
            }
        }
    }

    void displayGraph()
    {
        for (int i = 0; i < nv; i++)
        {
            cout << cities[i] << " : ";
            for (int j = 0; j < nv; j++)
            {
                cout << " ( " << cities[j] << "," << adjMatrix[i][j] << ")"
                     << " ";
            }
            cout << endl;
        }
    }

    int mincost(int cost[], bool mstSet[])
    {
        int min = INF, min_index;

        for (int i = 0; i < nv; i++)
        {
            if (mstSet[i] == false && cost[i] < min)
            {
                min = cost[i];
                min_index = i;
            }
        }
        return min_index;
    }

    void primsAlgo()
    {
        // declare arrays for state of mst
        int parent[nv]; //store the parent vertex of each vertex in the MST.
        int cost[nv];  //store the current cost of each vertex in the MST
        bool mstSet[nv]; // indicate whether a vertex has been included in the MST or not.

        for (int i = 0; i < nv; i++)
        {
            cost[i] = INF;
            mstSet[i] = false;
        }

        // select first cost
        cost[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < nv - 1; count++)
        {
            int u = this->mincost(cost, mstSet);

            mstSet[u] = true;
            for (int i = 0; i < nv; i++)
            {
                if (adjMatrix[u][i] && mstSet[i] == false && adjMatrix[u][i] < cost[i]) //adjMatrix[u][i] (the weight of the edge between u and i) is less than the current key value of vertex i
                {
                    parent[i] = u;
                    cost[i] = adjMatrix[u][i];
                } 
            }
        }
        printMST(parent);
    }

    void printMST(int parent[])
    {
        cout << "Minimum cost for connection is: " << endl;
        cout << "Edges\t\tWeight" << endl;
        int cost = 0;
        for (int i = 1; i < nv; i++)
        {
            cost += adjMatrix[i][parent[i]];
            cout << cities[parent[i]] << " - " << cities[i] << "\t " << adjMatrix[i][parent[i]] << endl;
        }
        cout << "Total Cost is :  " << cost << endl;
    }
};
int main()
{

    int nv;
    cout << "Enter the number of cities: ";
    cin >> nv;

    Graph g(nv);

    bool flag = true;
    int ch;

    while (flag)
    {
        cout << "1. Initlize Graph" << endl;
        cout << "2. Display graph " << endl;
        cout << "3. Prims Min Cost " << endl;
        cout << "4. Krushkals Min Cost " << endl;
        cout << "5. exit...." << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            g.initGraph();
            break;
        case 2:
            g.displayGraph();
            break;

        case 3:
            g.primsAlgo();
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
}