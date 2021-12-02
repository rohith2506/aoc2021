#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <boost/algorithm/string.hpp>

int solve(std::vector<std::pair<std::string, int>> directions)
{
    int horizontal = 0, vertical = 0, aim = 0;
    for (size_t i = 0; i < directions.size(); i++)
    {
        std::pair<std::string, int> dir_pair = directions[i];
        std::string direction = dir_pair.first;
        int amount = dir_pair.second;

        if (direction == "forward")
        {
            horizontal = horizontal + amount;
            vertical = vertical + aim * amount;
        }
        else if (direction == "up")
        {
            aim = aim - amount;
            if (aim < 0)
            {
                aim = 0;
            }
        }
        else
        {
            aim = aim + amount;
        }
    }
    return horizontal * vertical;
}


int main() {
    std::ifstream fin("input.txt");
    std::vector<std::pair<std::string, int>> directions;

    if (fin.is_open())
    {
        std::string line;
        while(std::getline(fin, line))
        {
            std::vector<std::string> line_parts;
            boost::split(line_parts, line, boost::is_any_of(" "));
            std::string direction = line_parts[0];
            int amount = std::stoi(line_parts[1]);
            directions.push_back(std::make_pair(direction, amount));
        }
    }
    
    int result = solve(directions);
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}
