GOAL_STATE = [[0, 1, 2], [3, 4, 5], [6, 7, 8]]

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
            print(state[i][j], end=" ")
        print()
    print()


def isGoalState(state):
    """
    Checks if the state is the goal state.
    """
    if GOAL_STATE == state:
        return True
    else:
        return False


def getIndex(state):
    """
    Returns the index (i and j) of the blank tile
    """
    if state == None:
        return -1, -1
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0:
                return i, j


def moveDown(state):
    """
    Moves a number down into the blank tile, and the blank tile moves upward.
    """
    row, col = getIndex(state)

    if row == 0 or row == -1 and col == -1:
        return None
    else:
        new_state = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col] = state[row-1][col]
        new_state[row-1][col] = 0

        return new_state


def moveUp(state):
    """
    Moves an a number up into the blank tile, and the blank tile moves downward.
    """
    row, col = getIndex(state)

    if row == 2 or row == -1 and col == -1:
        return None
    else:
        new_state = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col] = state[row+1][col]
        new_state[row+1][col] = 0

        return new_state


def moveLeft(state):
    """
    Moves a number left into the blank tile, and the blank tile moves right.
    """
    row, col = getIndex(state)

    if col == 2 or row == -1 and col == -1:
        return None
    else:
        new_state = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col] = state[row][col+1]
        new_state[row][col+1] = 0

        return new_state


def moveRight(state):
    """
    Moves a number right into the blank tile, and the blank tile moves left.
    """
    row, col = getIndex(state)

    if col == 0 or row == -1 and col == -1:
        return None
    else:
        new_state = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]

        new_state[row][col] = state[row][col-1]
        new_state[row][col-1] = 0

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
    if isGoalState(initial_state):
        return initial_node, 0, 1
    frontier = [initial_node]
    reached = [initial_node]
    while frontier:
        node = frontier.pop()
        for child in expand(node):
            state = child.state
            if state == None:
                continue
            if isGoalState(state):
                return child, len(frontier), len(reached)
            if state not in reached:
                frontier.append(child)
                reached.append(child)

    return None


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


def main():
    print("8-Puzzle Solver")
    print("---------------")
    print("To Note: ")
    print("1. The blank tile is represented by a 0.\n")
    print("2. The goal state is:")
    printState(GOAL_STATE)
    print("3. The actions are: Up, Down, Left, Right\n")
    print("4. These actions refer to a number moving into the blank tile. Not the blank tile moving in that direction.")
    print()
    
    initial_state = [
        [3, 1, 2],
        [4, 5, 8],
        [6, 7, 0]
    ]

    initial_node = Node(initial_state, None, None, 0)

    print("Initial State:")
    printState(initial_state)

    goal_node, len_of_frontier, len_of_reached = breadthFirstSearch(initial_node)

    if goal_node.state == None:
        print("No solution found")
    else:
        steps = 0
        all_states = []
        all_actions = []
        while goal_node.parent != None:
            steps += 1
            all_states.append(goal_node.state)
            all_actions.append(goal_node.action)
            goal_node = goal_node.parent

        all_states.reverse()
        all_actions.reverse()
        for i in range(len(all_states)):
            print(f"Step {i+1}:")
            print(f"Action: {all_actions[i]}")
            print("\nNew State:")
            printState(all_states[i])
        print("Total Number of Steps: ", steps)
        print("Length of Frontier: ", len_of_frontier)
        print("Length of Reached: ", len_of_reached)


if __name__ == '__main__':
    main()
