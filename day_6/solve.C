#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <boost/algorithm/string.hpp>

void perform_simulation(std::map<long long, long long>& fish_map)
{
    long long new_fish = 0;
    for(int fish_live_period = 0; fish_live_period <= 8; fish_live_period++)
    {
        if (fish_map.find(fish_live_period) != fish_map.end())
        {
            long long current_fish_count = fish_map[fish_live_period];
            fish_map.erase(fish_live_period);
            
            if (fish_live_period == 0)
            {
                new_fish = current_fish_count;
            }
            else
            {
                if (fish_map.find(fish_live_period - 1) == fish_map.end())
                {
                    fish_map[fish_live_period - 1] = current_fish_count;
                }
                else
                {
                    fish_map[fish_live_period - 1] += current_fish_count;
                }
            }
        }
    }

    if (new_fish != 0)
    {
        if (fish_map.find(6) == fish_map.end())
        {
            fish_map[6] = new_fish;
        }
        else
        {
            fish_map[6] += new_fish;
        }
        if (fish_map.find(8) == fish_map.end())
        {
            fish_map[8] = new_fish;
        }
        else
        {
            fish_map[8] += new_fish;
        }
    }
}

long long solve(std::vector<int> input)
{
    std::map<long long, long long> fish_map;
    for(int i = 0; i < input.size(); i++)
    {
        if (fish_map.find(input[i]) == fish_map.end())
        {
            fish_map[input[i]] = 1;
        }
        else
        {
            fish_map[input[i]] += 1;
        }
    }   
    int day = 1;
    while (day <= 256)
    {
        perform_simulation(fish_map);
        day = day + 1;
    }
    long long result = 0;
    for (auto it = fish_map.begin(); it != fish_map.end(); it++)
    {
        result += it->second;
    }
    return result;
}

int main()
{
    std::ifstream fin("input.txt"); 
    std::vector<int> input;
    if (fin.is_open())
    {
        std::string line;
        while (std::getline(fin, line)) {
            std::vector<std::string> line_parts;
            boost::split(line_parts, line, boost::is_any_of(","));
            for(auto l: line_parts)
            {
                input.push_back(std::stoi(l));
            }
        }
    }
    long long result = solve(input);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
