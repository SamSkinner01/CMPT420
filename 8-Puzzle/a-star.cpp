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

// vector<vector<int>> INITIAL_STATE = {
//      {2,5,8},
//      {1,3,0},
//      {6,4,7}
//  };
// vector<vector<int>> INITIAL_STATE = {
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

// 15 steps
vector<vector<int>> INITIAL_STATE = {
    {2, 5, 8},
    {0, 3, 7},
    {1, 6, 4}
};

// vector<vector<int>> INITIAL_STATE = {
//     {8, 1, 2},
//     {7, 0, 3},
//     {6, 5, 4}
// };

// vector<vector<int>> INITIAL_STATE = {
//     {7, 2, 4},
//     {5, 0, 6},
//     {8, 3, 1}
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
            std::cout << state[i][j] << " ";
        }
        std::cout << endl;
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

int manhattanDistance(vector<vector<int>> state)
{
    // Calculates the manhattan distance of the current state
    int distance = 0;
    // For each tile in the state calculate the manhattan distance
    for (int i = 0; i < state.size(); i++)
    {
        for (int j = 0; j < state[i].size(); j++)
        {
            // If the tile is the blank tile, skip it
            if(state[i][j] == 0)
                continue;
            // tile is the value at the current row and column
            int tile = state[i][j];
            // the goal row and column is where the tile should be
            int goal_row = tile / 3;
            int goal_col = tile % 3;
            // calculate the distance between the two points.
            distance += abs(i - goal_row) + abs(j - goal_col);
        }
    }
    return distance;
}

int evaluate(Node node)
{
    // Calculates the evaluation function of the current node
    return node.path_cost + manhattanDistance(node.state);
}

void sortFrontier(vector<Node> &frontier)
{
    for (int i = 0; i < frontier.size(); i++)
    {
        for (int j = 0; j < frontier.size() - 1; j++)
        {
            if (evaluate(frontier[j]) > evaluate(frontier[j + 1]))
            {
                Node temp = frontier[j];
                frontier[j] = frontier[j + 1];
                frontier[j + 1] = temp;
            }
        }
    }
}

Node a_star(vector<vector<int>> initial_state, int *frontier_size, int *reached_size)
{
    vector<vector<int>> EMPTY = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    // Create the initial node
    Node initial = Node(initial_state, NULL, "", 0);

    // Create the frontier and reached sets
    vector<Node> frontier;
    vector<Node> reached;

    // Add the initial node to the frontier
    frontier.push_back(initial);
    reached.push_back(initial);

    

    // While the frontier is not empty
    while (frontier.size() != 0)
    {
        sortFrontier(frontier);
        // Get the node with the lowest evaluation function
        Node node = frontier[0];
        frontier.erase(frontier.begin());
        

        // If the node is the goal state, return the node
        if (isGoalState(node.state))
        {
            *frontier_size = frontier.size();
            *reached_size = reached.size();
            return node;
        }

        // Expand the node
        vector<Node> children = expand(node);

        // For each child node
        for (int i = 0; i < children.size(); i++)
        {
            if (children[i].state == EMPTY)
                continue;
            
            bool flag = false;
            vector<vector<int>> child_state = children[i].state;
            int child_path_cost = children[i].path_cost;
            int reached_path_cost = 0;
            for (int j = 0; j < reached.size(); j++)
            {
                vector<vector<int>> reached_state = reached[j].state;

                if (child_state == reached_state)
                {
                    reached_path_cost = reached[j].path_cost;
                    flag = true;
                    break;
                }
            }
            if (!flag || child_path_cost < reached_path_cost)
                {
                    frontier.push_back(children[i]);
                    reached.push_back(children[i]);
                }
        }
    }

    return initial;
}

int main()
{
    int frontier_size = 0, reached_size = 0;

    // If no empty space then there is not solution
    if (findIndex(INITIAL_STATE)[0][0] == -1)
    {
        std::cout << "Invalid initial state" << endl;
        return 0;
    }

    // Print the initial state
    printState(INITIAL_STATE);
    std::cout << endl;

    // Time how long it takes for the algorithm to complete
    auto start = high_resolution_clock::now();
    Node end = a_star(INITIAL_STATE, &frontier_size, &reached_size);
    auto stop = high_resolution_clock::now();

    // If the initial state is the goal state, no solution was found
    if (end.state == INITIAL_STATE)
    {
        std::cout << "No solution found" << endl;
        return 0;
    }

    // If solution was found, print the solution and other information
    printState(end.state);
    std::cout << "\nNumber of steps: " << end.path_cost << endl;
    std::cout << "frontier size: " << frontier_size << endl;
    std::cout << "reached size: " << reached_size << endl;
    std::cout << "Time taken: " << duration_cast<milliseconds>(stop - start).count() << " milliseconds" << endl;

    return 0;
}