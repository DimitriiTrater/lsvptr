#include <vector>
#include <set>
#include <map>
#include <ranges>
#include <iostream>

using Vertex = int;
using Graph = std::vector<std::vector<Vertex>>;
using Path = std::vector<Vertex>;

void print_path(Path const& path)
{
    for (auto const& el: path)
        std::cout<< el << " ";
    std::cout << "\n";
}

auto euler(Graph const& _graph) -> std::vector<int>
{
    auto graph = _graph;
    std::map<int, int> edge_count{};

    if (graph.empty())
    {
        return {};
    }

    for (auto const& elem: std::ranges::iota_view{0ULL, graph.size()})
    {
        edge_count[elem] = graph.at(elem).size();
    }

    Path curr_path {0};
    Vertex current {0};
    std::vector<int> cycle {};


    while (curr_path.size())
    {
        if (edge_count[current])
        {
            curr_path.emplace_back(current);

            Vertex next = graph[current].back();
            edge_count[current] -= 1;
            graph[current].pop_back();

            current = next;
        }
        else
        {
            cycle.emplace_back(current);
            current = curr_path.back();
            curr_path.pop_back();
        }
    }
    std::vector<int> result{};
    for(auto const & el: std::ranges::reverse_view(cycle))
    {
        result.emplace_back(el);
    }
    return result;
}


int main()
{
    Graph test1 {
        {1},
        {2},
        {0}
    };
    Graph test2 {
        {1, 6},
        {2},
        {0, 3},
        {4},
        {2, 5},
        {0},
        {4}
    };
    Graph test3 {
        {1, 2},
        {0},
        {0},
    };

    std::vector<int> cycle = euler(test3);
    print_path(cycle);
    return 0;
}