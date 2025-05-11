#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <deque>
#include <chrono>
#include <ctime>
#include <cstdlib>

using Graph = std::map<std::pair<int, int>, std::set<std::pair<int, int>>>;
using Vertex = std::pair<int, int>;
using Edge = std::pair<std::string, std::string>;

const std::vector<std::pair<int, int>> MOVE_OFFSETS = {
    {-1, -2}, { 1, -2},
    {-2, -1}, { 2, -1},
    {-2,  1}, { 2,  1},
    {-1,  2}, { 1,  2},
};

void addEdge(Graph& g, const Vertex& v1, const Vertex& v2) {
    g[v1].insert(v2);
    g[v2].insert(v1); // bo graf jest nieskierowany
}

std::vector<std::pair<int, int>> legalMovesFrom (int row, int col, int boardSize) {
    std::vector<std::pair<int, int>> legalMoves;
    for (const auto& offset : MOVE_OFFSETS) {
        int newRow = row + offset.first;
        int newCol = col + offset.second;
        if (newRow >= 0 && newRow < boardSize && newCol >= 0 && newCol < boardSize) {
            legalMoves.emplace_back(newRow, newCol);
        }
    }
    return legalMoves;
}

Graph buildGraph(int boardSize) {
    Graph graph;
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; col++) {
            std::vector<std::pair<int, int>> legalMoves = legalMovesFrom(row, col, boardSize);
            for (const auto& move : legalMoves) {
                addEdge(graph, {row, col}, move);
            }
        }
    }
    return graph;
}

std::vector<Vertex> firstTrue (std::vector<std::vector<Vertex>>& sequence) {
    for (const auto& item : sequence) {
        if (!item.empty()) {
            return item;
        }
    }
    return {};
}

std::vector<std::pair<int, int>> traverse(
    std::vector<Vertex> path,
    const std::pair<int, int>& current_vertex, // Current position
    const Graph& graph, // The knight's move graph
    int total_squares, // Total number of squares on the board
    // Heuristic function: takes a vertex and the graph, returns a value for sorting neighbors.
    // Default heuristic (no sorting)
    std::function<int(const std::pair<int, int>&, const Graph&)> heuristic =
        [](const std::pair<int, int>& v, const Graph& g) { return 0; }
) {
    // Add the current vertex to the path
    path.push_back(current_vertex);

    // Base case: If the path includes all squares, we found a solution.
    if (path.size() == total_squares) {
        return path;
    }

    // Find neighbors that have not yet been visited in the current path.
    std::vector<std::pair<int, int>> yet_to_visit;
    // Check if the current_vertex exists in the graph (should always be true for a valid board)
    if (graph.count(current_vertex)) {
        for (const auto& neighbor : graph.at(current_vertex)) {
            // Check if the neighbor is NOT in the current path
            bool visited = false;
            for (const auto& visited_vertex : path) {
                if (visited_vertex == neighbor) {
                    visited = true;
                    break;
                }
            }
            if (!visited) {
                yet_to_visit.push_back(neighbor);
            }
        }
    }


    // If there are no unvisited neighbors, it's a dead end.
    if (yet_to_visit.empty()) {
        return {}; // Return an empty vector indicating no solution down this path
    }

    // Sort the next possible vertices based on the heuristic (e.g., Warnsdorff's rule)
    // The default heuristic does not change the order.
    std::sort(yet_to_visit.begin(), yet_to_visit.end(),
              [&](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  // Calculate the heuristic value for each neighbor
                  int heuristic_a = heuristic(a, graph);
                  int heuristic_b = heuristic(b, graph);
                  // Sort based on the heuristic values
                  return heuristic_a < heuristic_b;
              });


    // Try all valid paths from here recursively.
    std::vector<std::vector<std::pair<int, int>>> possible_solutions;
    for (const auto& next_vertex : yet_to_visit) {
        // Recursive call: explore path from next_vertex
        std::vector<std::pair<int, int>> result_path = traverse(path, next_vertex, graph, total_squares, heuristic);
        // If the recursive call found a solution (returned a non-empty path), return it immediately.
        if (!result_path.empty()) {
             return result_path;
        }
    }

    // If none of the recursive calls found a solution, return an empty vector.
    return {};
}

// Function to find a Knight's Tour solution on a board of given size.
// Optionally takes a heuristic function for optimizing the search (e.g., Warnsdorff's rule).
// Returns a vector representing the solution path if found, otherwise an empty vector.
// Equivalent to the outer 'find_solution_for' function in Python.
std::vector<std::pair<int, int>> find_solution_for(
    int board_size,
    // Default heuristic (no sorting)
    std::function<int(const std::pair<int, int>&, const Graph&)> heuristic =
        [](const std::pair<int, int>& v, const Graph& g) { return 0; }
) {
    // Build the graph representing knight's moves
    Graph graph = build_graph(board_size);
    int total_squares = board_size * board_size;

    // Try to find a solution starting from every square on the board.
    // Iterate through all vertices in the graph (all squares).
    for (const auto& pair : graph) {
        const std::pair<int, int>& starting_vertex = pair.first;
        // Start the recursive traversal from the current starting vertex.
        std::vector<std::pair<int, int>> solution = traverse({}, starting_vertex, graph, total_squares, heuristic);
        // If a solution is found, return it immediately.
        if (!solution.empty()) {
            return solution;
        }
    }

    // If no solution is found starting from any square, return an empty vector.
    return {};
}