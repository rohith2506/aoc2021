#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <boost/algorithm/string.hpp>

int calculate_ap(int n)
{
    return n * (n + 1) / 2;
}

int solve(std::vector<int> numbers)
{
    int result = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        int temp = 0;
        for (int j = 0; j < numbers.size(); j++)
        {
            temp += calculate_ap(abs(numbers[j] - i));
        }
        if (result == 0)
        {
            result = temp;
        }
        else
        {
            result = std::min(temp, result);
        }
    }
    return result;
}

int main()
{
    std::ifstream fin("input.txt"); 
    std::vector<int> numbers;
    if (fin.is_open())
    {
        std::string line;
        while (std::getline(fin, line)) {
            std::vector<std::string> line_parts;
            boost::split(line_parts, line, boost::is_any_of(","));
            for(auto l: line_parts)
            {
                numbers.push_back(std::stoi(l));
            }
        }
    }
    long long result = solve(numbers);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
