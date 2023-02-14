def printState(state):
    """
    Prints the board.
    Requires a 3x3 list
    """
    for i in range(3):
        for j in range(3):
            print(state[i][j], end=" ")
        print()

def isGoalState(state):
    """
    Checks if the state is the goal state.
    """
    goal_state = [ [1,2,3], [4,5,6], [7,8,0] ]

    if goal_state == state: return True
    else: return False

def getIndex(state):
    if state == None: return -1,-1
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0: return i,j

def moveDown(state):
    """
    Moves a number down into the blank tile, and the blank tile moves upward.
    """
    row,col = getIndex(state)

    if row == 0 or row == -1 and col == -1: 
        return None
    else: 
        new_state = [[0,0,0],[0,0,0],[0,0,0]]
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
    row,col = getIndex(state)

    if row == 2 or row == -1 and col == -1: 
        return None
    else: 
        new_state = [[0,0,0],[0,0,0],[0,0,0]]
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
    row,col = getIndex(state)

    if col == 2 or row == -1 and col == -1: 
        return None
    else: 
        new_state = [[0,0,0],[0,0,0],[0,0,0]]
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
    row,col = getIndex(state)

    if col == 0 or row == -1 and col == -1: 
        return None
    else: 
        new_state = [[0,0,0],[0,0,0],[0,0,0]]
        for i in range(3):
            for j in range(3):
                new_state[i][j] = state[i][j]
        
        new_state[row][col] = state[row][col-1]
        new_state[row][col-1] = 0

        return new_state


def breadthFirstSearch(initial_state):
    """
    Takes an initial state. Will expand the initial state.
    Priortizes expanding the states at the same depth using
    a FIFO queue. If one of the children is the goal state,
    then that child is returned. If no solution is found,
    then None is returned.
    """
    if isGoalState(initial_state): return initial_state
    frontier = [initial_state]
    reached = [initial_state]
    while frontier:
        state = frontier.pop()
        for child in expand(state):
            if child == None: continue
            if isGoalState(child): return child
            if child not in reached:
                frontier.append(child)
                reached.append(child)
    return None


def expand(state):
    """
    Performs the four possible moves. If a move is not possible,
    the move function returns None. If that happens, it will
    be ignored.
    """
    expanded_states = []
    expanded_states.append(moveDown(state))
    expanded_states.append(moveUp(state))
    expanded_states.append(moveLeft(state))
    expanded_states.append(moveRight(state))

    return expanded_states

def main():
    initial_state = [ [1,2,3], [0,5,6], [4,7,8]]
    printState(initial_state, end="\n\n")
    goal = breadthFirstSearch(initial_state)
    if goal == None: print("No solution found")
    else: printState(goal)

if __name__ == '__main__':
    main()