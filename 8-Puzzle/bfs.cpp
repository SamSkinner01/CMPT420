#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

// Global variables
vector<vector<int>> GOAL_STATE = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

// vector<vector<int>> INITIAL_STATE = {
//      {2,5,0},
//      {1,3,8},
//      {6,4,7}
//  };

vector<vector<int>> INITIAL_STATE = {
     {2,5,8},
     {1,3,0},
     {6,4,7}
 };
//  vector<vector<int>> INITIAL_STATE = {
//      {2,5,8},
//      {1,3,7},
//      {6,4,0}
//  };

// vector<vector<int>> INITIAL_STATE = {
//     {2,5,8},
//     {1,3,7},
//     {6,0,4}
// };

// vector<vector<int>> INITIAL_STATE = {
//     {2,5,8},
//     {1,3,7},
//     {0,6,4}
// };

// vector<vector<int>> INITIAL_STATE = {
//     {2, 5, 8},
//     {0, 3, 7},
//     {1, 6, 4}
// };

struct Node
{
    vector<vector<int>> state;
    Node *parent = nullptr;
    string action;
    int path_cost;

    Node(vector<vector<int>> state, Node *parent, string action, int path_cost)
    {
        this->state = state;
        this->parent = parent;
        this->action = action;
        this->path_cost = path_cost;
    }
};

void printState(vector<vector<int>> state)
{
    for (int i = 0; i < state.size(); i++)
    {
        for (int j = 0; j < state[i].size(); j++)
        {
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> moveLeft(vector<vector<int>> state, int row, int col)
{
    // Moves the blank tile to the left
    if (col == 0)
    {
        vector<vector<int>> empty_state = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        return empty_state;
    }
    else
    {
        int temp = state[row][col];
        state[row][col] = state[row][col - 1];
        state[row][col - 1] = temp;
        return state;
    }
}

vector<vector<int>> moveRight(vector<vector<int>> state, int row, int col)
{
    // Moves the blank tile to the right
    if (col == 2)
    {
        vector<vector<int>> empty_state = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        return empty_state;
    }
    else
    {
        int temp = state[row][col];
        state[row][col] = state[row][col + 1];
        state[row][col + 1] = temp;
        return state;
    }
}

vector<vector<int>> moveUp(vector<vector<int>> state, int row, int col)
{
    // Moves the blank tile up
    if (row == 0)
    {
        vector<vector<int>> empty_state = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        return empty_state;
    }
    else
    {
        int temp = state[row][col];
        state[row][col] = state[row - 1][col];
        state[row - 1][col] = temp;
        return state;
    }
}

vector<vector<int>> moveDown(vector<vector<int>> state, int row, int col)
{
    // Moves the blank tile down

    if (row == 2)
    {
        vector<vector<int>> empty_state = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        return empty_state;
    }
    else
    {
        int temp = state[row][col];
        state[row][col] = state[row + 1][col];
        state[row + 1][col] = temp;
        return state;
    }
}

bool isGoalState(vector<vector<int>> state)
{
    // Checks if the current state is the goal state
    for (int i = 0; i < state.size(); i++)
    {
        for (int j = 0; j < state[i].size(); j++)
        {
            if (state[i][j] != GOAL_STATE[i][j])
                return false;
        }
    }
    return true;
}

vector<vector<int>> findIndex(vector<vector<int>> state)
{
    // Finds the index of the blank tile
    vector<vector<int>> index;
    for (int i = 0; i < state.size(); i++)
    {
        for (int j = 0; j < state[i].size(); j++)
        {
            if (state[i][j] == 0)
            {
                index.push_back({i, j});
                return index;
            }
        }
    }
    return {{-1, -1}};
}

vector<Node> expand(Node node)
{
    // Used to compare if action was valid. If invalid, do not add to children vector
    vector<vector<int>> EMPTY = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    // Create resulting vector of children nodes
    vector<Node> children;

    // Find the index of the blank tile and store the resulting row and col
    vector<vector<int>> index = findIndex(node.state);
    int row = index[0][0];
    int col = index[0][1];

    // Create the children nodes
    Node left = Node(moveLeft(node.state, row, col), &node, "left", node.path_cost + 1);
    Node right = Node(moveRight(node.state, row, col), &node, "right", node.path_cost + 1);
    Node up = Node(moveUp(node.state, row, col), &node, "up", node.path_cost + 1);
    Node down = Node(moveDown(node.state, row, col), &node, "down", node.path_cost + 1);

    // Add the children nodes to the children vector
    children.push_back(left);
    children.push_back(right);
    children.push_back(up);
    children.push_back(down);

    // return the vector of children nodes
    return children;
}

Node bfs(vector<vector<int>> initial_state, int *frontier_size, int *reached_size)
{
    // Initialize the starting node
    Node root(initial_state, NULL, "", 0);

    // Check if the initial state is the goal state
    if (isGoalState(root.state))
    {
        *frontier_size = 0;
        *reached_size = 1;
        return root;
    }

    // Initialize the frontier and reached
    vector<Node> frontier;
    frontier.push_back(root);
    vector<Node> reached;

    // Loop until the frontier is empty
    while (frontier.size() != 0)
    {
        // Pop the first element in the frontier
        // Acts as a queue
        Node node = frontier[0];
        frontier.erase(frontier.begin());

        // Store element in reached.
        reached.push_back(node);

        // Check if the current nodes state is the goal state
        if (isGoalState(node.state))
        {
            // If it is the goal state, return the node and the sizes of the frontier and reached
            *reached_size = reached.size();
            *frontier_size = frontier.size();
            return node;
        }

        // Expand the current node to get its children
        vector<Node> children = expand(node);

        // Loop over all current children
        for (int i = 0; i < children.size(); i++)
        {
            // Flag determines if the child already is in reached
            bool flag = false;

            // Account for if one of the children attempted to move the blank tile out of bounds
            if (children[i].state == vector<vector<int>>{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}})
                continue;

            // Loop over all elements in reached to determine if child is already in reached
            for (int j = 0; j < reached.size(); j++)
            {
                if (children[i].state == reached[j].state)
                {
                    flag = true;
                    break;
                }
            }

            // If not in reached, add to reached.
            // Also add to frontier to expand later
            if (!flag)
            {
                frontier.push_back(children[i]);
                reached.push_back(children[i]);
            }
        }
    }

    // If the frontier is empty and no solution has been found, return the initial node.
    return root;
}

int main()
{
    int frontier_size = 0, reached_size = 0;

    // If no empty space then there is not solution
    if (findIndex(INITIAL_STATE)[0][0] == -1)
    {
        cout << "Invalid initial state" << endl;
        return 0;
    }

    // Print the initial state
    printState(INITIAL_STATE);
    cout << endl;

    // Time how long it takes for the algorithm to complete
    auto start = high_resolution_clock::now();
    Node end = bfs(INITIAL_STATE, &frontier_size, &reached_size);
    auto stop = high_resolution_clock::now();

    // If the initial state is the goal state, no solution was found
    if (end.state == INITIAL_STATE)
    {
        cout << "No solution found" << endl;
        return 0;
    }

    // If solution was found, print the solution and other information
    printState(end.state);
    cout << "\nNumber of steps: " << end.path_cost << endl;
    cout << "frontier size: " << frontier_size << endl;
    cout << "reached size: " << reached_size << endl;
    cout << "Time taken: " << duration_cast<milliseconds>(stop - start).count() << " milliseconds" << endl;

    return 0;
}