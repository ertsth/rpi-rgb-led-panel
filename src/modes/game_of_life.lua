-- TODO: replace hardcoded values with parameters provided from c++
WIDTH = 64
HEIGHT = 64

ALIVE = 1
DEAD = 0

BORN_RULE = "3"
SURVIVE_RULE = "23"

local function createEmptyGrid(value)
    local grid = {}
    for i = 1, HEIGHT do
        grid[i] = {}
        for j = 1, WIDTH do
            grid[i][j] = value or DEAD
        end
    end
    return grid
end

local function printGrid(grid)
    for i = 1, #grid do
        for j = 1, #grid[i] do
            io.write(grid[i][j] .. " ")
        end
        io.write('\n')
    end
end

local function copyGrid(grid)
    local copy = {}
    for i = 1, #grid do
        copy[i] = {}
        for j = 1, #grid[i] do
            copy[i][j] = grid[i][j]
        end
    end
    return copy
end

local function shouldBorn(state, numNeighboors)
    return state == DEAD and string.find(BORN_RULE, numNeighboors) ~= nil
end

local function shouldSurvive(state, numNeighboors)
    return state == ALIVE and string.find(SURVIVE_RULE, numNeighboors) ~= nil
end

local function newState(currentState, numNeighboors)
    if shouldBorn(currentState, numNeighboors) or
        shouldSurvive(currentState, numNeighboors) then
        return ALIVE
    else
        return DEAD
    end
end

local function isEdgeCell(x, y, w, h)
    return ((x < 1 or x > w) or (y < 1 or y > h))
end

local function countNeighbors(grid, x, y)
    local numNeighboors = 0
    for i = x - 1, x + 1 do
        for j = y - 1, y + 1 do
            if i == x and j == y then
                goto continue
            end
            if not isEdgeCell(i, j, #grid, #grid[1]) then
                if grid[i][j] == ALIVE then
                    numNeighboors = numNeighboors + 1
                end
            end
            ::continue::
        end
    end
    return numNeighboors
end

local function calculateNext(grid)
    local newGrid = copyGrid(grid)
    for i = 1, #grid do
        for j = 1, #grid[i] do
            local numNeighboors  = countNeighbors(grid, i, j)
            newGrid[i][j] = newState(grid[i][j], numNeighboors)
        end
    end
    return newGrid
end

local function drawGrid(grid)
    matrix_fill(0, 0, 0)

    for i = 1, #grid do
        for j = 1, #grid[i] do
            if grid[i][j] == ALIVE then
                matrix_set_pixel(i - 1, j - 1, 0, 255, 255)
            else
                matrix_set_pixel(i - 1, j - 1, 0, 0, 0)
            end
        end
    end
    os.execute("sleep 0.5")
end

local function startGame()
    local activeGrid = createEmptyGrid()
    math.randomseed(os.time())

    -- fill with random numbers
    for i = 1, #activeGrid do
        for j = 1, #activeGrid[i] do
            activeGrid[i][j] = math.random(0, 1)
        end
    end

    local i = 0
    while i < 50 do
        printGrid(activeGrid)
        print()
        local bufferGrid = calculateNext(activeGrid)
        activeGrid = copyGrid(bufferGrid)
        drawGrid(activeGrid)
        i = i + 1
    end
end

startGame()