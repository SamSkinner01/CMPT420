from collections import deque
import numpy as np
import time
import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning) 

GOAL_STATE = [[0, 1, 2], [3, 4, 5], [6, 7, 8]]
GOAL_STATE = np.array(GOAL_STATE)

class Node:
    def __init__(self, state, parent, action, path_cost):
        self.state = state
        self.parent = parent
        self.action = action
        self.path_cost = path_cost


def printState(state):
    """
    Prints the board.
    Requires a 3x3 list
    """
    for i in range(3):
        for j in range(3):
            print(state[i][j], end = " ")
        print()
    print()


def isGoalState(state):
    """
    Checks if the state is the goal state.
    """
    if np.array_equal(state, GOAL_STATE):
        return True
    else:
        return False


def getIndex(state):
    """
    Returns the index (i and j) of the blank tile
    """
    empty = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
    if np.array_equal(state, empty):
        return -1, -1
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0:
                return i, j


def moveUp(state):
    """
    Moves the blank tile up
    """
    row, col = getIndex(state)

    if row == 0 or row == -1 and col == -1:
        return np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
    else:
        new_state = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col], new_state[row-1][col] = new_state[row-1][col], new_state[row][col]
        new_state = np.array(new_state)
        return new_state

def moveDown(state):
    """
    Moves the blank tile down
    """
    row, col = getIndex(state)

    if row == 2 or row == -1 and col == -1:
        return np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
    else:
        new_state = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col], new_state[row+1][col] = new_state[row+1][col], new_state[row][col]
        new_state = np.array(new_state)
        return new_state

def moveLeft(state):
    """
    Moves the blank tile left
    """
    row, col = getIndex(state)

    if col == 0 or row == -1 and col == -1:
        return np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
    else:
        new_state = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col], new_state[row][col-1] = new_state[row][col-1], new_state[row][col]
        new_state = np.array(new_state)
        return new_state

def moveRight(state):
    """
    Moves the blank tile right
    """
    row, col = getIndex(state)

    if col == 2 or row == -1 and col == -1:
        return np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
    else:
        new_state = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col], new_state[row][col+1] = new_state[row][col+1], new_state[row][col]
        new_state = np.array(new_state)
        return new_state

def breadthFirstSearch(initial_node):
    """
    Takes an initial state. Will expand the initial state.
    Priortizes expanding the states at the same depth using
    a FIFO queue. If one of the children is the goal state,
    then that child is returned. If no solution is found,
    then None is returned.
    """
    initial_state = initial_node.state
    initial_state = np.array(initial_state)
    empty = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
    if isGoalState(initial_state):
        return initial_node, 0, 1
    frontier = deque([initial_node])
    reached = np.array([initial_node])
    while frontier:
        node = frontier.popleft()
        child = expand(node)
        for i in range(len(child)):
            state = child[i].state
           
           
            state = np.array(state)
            if np.array_equal(state, empty):
                continue
            if isGoalState(state):
                return child[i], len(frontier), len(reached)
            
            # Check if the current state node has already been reached
            flag = False
            for j in range(len(reached)):
                if np.array_equal(state, reached[j].state):
                    flag = True
                    break

            if not flag:
                frontier.append(child[i])
                reached = np.append(reached, child[i])

    return None, len(frontier), len(reached)


def expand(node):
    """
    Performs the four possible moves. If a move is not possible,
    the move function returns None. If that happens, it will
    be ignored.
    """
    state = node.state
    expanded_nodes = []

    expanded_nodes.append(
        Node(moveUp(state), node, "Up", node.path_cost+1))
    expanded_nodes.append(
        Node(moveDown(state), node, "Down", node.path_cost+1))
    expanded_nodes.append(
        Node(moveLeft(state), node, "Left", node.path_cost+1))
    expanded_nodes.append(
        Node(moveRight(state), node, "Right", node.path_cost+1))

    return expanded_nodes

def allActions(node):
    """
    Prints actions and states from the initial state to the goal state.
    """
    actions = []
    states = []

    while node.parent != None:
        actions.append(node.action)
        states.append(node.state)
        node = node.parent
    actions.reverse()
    states.reverse()
    for i in range(len(actions)):
        print(f"Step {i+1}:")
        print(f"Action: {actions[i]}")
        print("\nNew State:")
        printState(states[i])
    print()

def menu():
    print("8-Puzzle Solver")
    print("---------------")
    print("To Note: ")
    print("1. The blank tile is represented by a 0.\n")
    print("2. The goal state is:")
    printState(GOAL_STATE)
    print()

def main():
    menu()

    # Takes 10 steps
    # initial_state = [
    #     [2, 5, 0], 
    #     [1, 3, 8], 
    #     [6, 4, 7]
    # ]

    # Takes 11 steps and much longer than the one above.
    initial_state = [
        [2, 5, 8], 
        [1, 3, 0], 
        [6, 4, 7]
    ]

    # Apprently complicated
    # initial_state = [
    #     [8, 1, 2], 
    #     [7, 0, 3], 
    #     [6, 5, 4]
    # ]
    initial_state = np.array(initial_state)

    initial_node = Node(initial_state, None, None, 0)

    print("Initial State:")
    printState(initial_state)

    start = time.time()
    goal_node, len_of_frontier, len_of_reached = breadthFirstSearch(initial_node)
    end = time.time()

    empty = np.array([[0, 0, 0], [0, 0, 0], [0, 0, 0]])
    if goal_node == None:
        print("No solution found")
    else:
        allActions(goal_node)
        print("Total Number of Steps: ", goal_node.path_cost)
        print("Length of Frontier: ", len_of_frontier)
        print("Length of Reached: ", len_of_reached)
    print(f"Time: {end-start} seconds")


if __name__ == '__main__':
    main()
