#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int solve(std::vector<int> depths)
{
    int result = 0;
    for (size_t i = 1; i < depths.size(); i++)
    {
        if (depths[i] > depths[i-1])
        {
            result = result + 1;
        }
    }
    return result;
}


int solve2(std::vector<int> depths)
{
    size_t prev = 0, result = 0;
    for (int i = 2; i < depths.size(); i++)
    {
        size_t curr = 0;
        int j = i;
        while (j >= i - 2)
        {
            curr = curr + depths[j];
            j = j - 1;
        }
        if (curr > prev and prev != 0)
        {
            result = result + 1;
        }
        prev = curr;
    }
    return result;
}


int main() {
    std::vector<int> depths;
    std::ifstream fin("input.txt");
    
    if (fin.is_open())
    {
        std::string line;
        while(std::getline(fin, line))
        {
            depths.push_back(std::stoi(line));
        }
    }
    
    int result = solve(depths);
    std::cout << "Result: " << result << std::endl;
    
    int result2 = solve2(depths);
    std::cout << "Result of big: " << result2 << std::endl;

    return 0;
}
