#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <boost/algorithm/string.hpp>


int solve(std::vector<std::string> readings)
{
    std::string gamma = "", epsilon = "";
    for (size_t j = 0; j < readings[0].size(); j++)
    {
        int on_counter = 0, off_counter = 0;
        for (size_t i = 0; i < readings.size(); i++)
        {
            if (readings[i][j] == '0')
            {
                off_counter++;
            }
            else
            {
                on_counter++;
            }
        }
        if (on_counter > off_counter)
        {
            gamma = gamma + '1';
            epsilon = epsilon + '0';
        }
        else
        {
            gamma = gamma + '0';
            epsilon = epsilon + '1';
        }
    }

    std::cout << "gamma: " << gamma << std::endl;
    std::cout << "epsilon: " << epsilon << std::endl;

    int g = 0, e = 0, power_index = 0;
    for (int i = gamma.length() - 1; i >= 0; i--)
    {
        int g_digit = gamma[i] - '0';
        int e_digit = epsilon[i] - '0';
        g = g + pow(2, power_index) * g_digit;
        e = e + pow(2, power_index) * e_digit;
        power_index = power_index + 1;
    }

    return g * e;
}


std::vector<std::string> reduce(std::vector<std::string> readings, int pos)
{
    std::vector<std::string> gamma_readings, epsilon_readings;
    int on_counter = 0, off_counter = 0;
    for (size_t i = 0; i < readings.size(); i++)
    {
        if (readings[i][pos] == '0')
        {
            epsilon_readings.push_back(readings[i]);
            off_counter++;
        }
        else
        {
            gamma_readings.push_back(readings[i]);
            on_counter++;
        }
    }
    if (on_counter > off_counter)
    {
        return gamma_readings;
    }
    else if (off_counter > on_counter)
    {
        return epsilon_readings;
    }
    else
    {
        return gamma_readings;
    }
}

std::vector<std::string> reduce2(std::vector<std::string> readings, int pos)
{
    std::vector<std::string> gamma_readings, epsilon_readings;
    int on_counter = 0, off_counter = 0;
    for (size_t i = 0; i < readings.size(); i++)
    {
        if (readings[i][pos] == '0')
        {
            epsilon_readings.push_back(readings[i]);
            off_counter++;
        }
        else
        {
            gamma_readings.push_back(readings[i]);
            on_counter++;
        }
    }
    if (on_counter < off_counter)
    {
        return gamma_readings;
    }
    else if (off_counter < on_counter)
    {
        return epsilon_readings;
    }
    else
    {
        return epsilon_readings;
    }
}


int solve2(std::vector<std::string> readings)
{
    std::vector<std::string> current_readings = readings;
    int index = 0;
    while (current_readings.size() != 1)
    {
        current_readings = reduce(current_readings, index);
        index = index + 1;
    }
    std::string o2_str = current_readings[0];
    std::cout << "o2: " << o2_str << std::endl;


    current_readings = readings;
    index = 0;
    while (current_readings.size() != 1)
    {
        current_readings = reduce2(current_readings, index);
        index = index + 1;
    }
    std::string co2_str = current_readings[0];
    std::cout << "co2: " << co2_str << std::endl;

    int o2 = 0, co2 = 0, power_index = 0;
    for (int i = o2_str.length() - 1; i >= 0; i--)
    {
        int o2_digit  = o2_str[i] - '0';
        int co2_digit = co2_str[i] - '0';
        o2 = o2 + pow(2, power_index) * o2_digit;
        co2 = co2 + pow(2, power_index) * co2_digit;
        power_index = power_index + 1;
    }
    return o2 * co2;
}


int main()
{
    std::ifstream fin("input.txt");
    std::vector<std::string> readings;
    if (fin.is_open())
    {
        std::string line;
        while(std::getline(fin, line))
        {
            readings.push_back(line);
        }
    }
    
    int result = solve(readings);
    std::cout << "Result: " << result << std::endl;
        
    int result2 = solve2(readings);
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}
