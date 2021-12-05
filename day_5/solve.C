#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <boost/algorithm/string.hpp>
 
struct Point
{
    int x;
    int y;
};

int solve(std::vector<std::pair<Point, Point>> points)
{
    int max_x = 0, max_y = 0;
    for (auto point: points)
    {
        max_x = std::max(max_x, point.first.x);
        max_x = std::max(max_x, point.second.x);
        max_y = std::max(max_y, point.first.y);
        max_y = std::max(max_y, point.second.y);
    }

    std::vector<std::vector<int>> map(max_x+1, std::vector<int>(max_y+1, 0));

    for (int i = 0; i < points.size(); i++)
    {
        std::pair<Point, Point> position = points[i];
        
        int x1 = position.first.x, y1 = position.first.y;
        int x2 = position.second.x, y2 = position.second.y;

       // std::cout << x1 << " " << y1 << " " << "," << x2 << " " << y2 << std::endl;

        if (abs(x1 - x2) == abs(y1 - y2))
        {
            if (x1 <= x2)
            {
                if (y1 <= y2)
                {
                    while (x1 <= x2 && y1 <= y2)
                    {
                        map[x1][y1]++;
                        x1 = x1 + 1;
                        y1 = y1 + 1;
                    }
                }
                else
                {
                    while (x1 <= x2 && y1 >= y2)
                    {
                        map[x1][y1]++;
                        x1 = x1 + 1;
                        y1 = y1 - 1;
                    }
                }
            }
            else
            {
                if (y1 <= y2)
                {
                    while (x1 >= x2 && y1 <= y2)
                    {
                        map[x1][y1]++;
                        x1 = x1 - 1;
                        y1 = y1 + 1;
                    }
                }
                else
                {
                    while (x1 >= x2 && y1 >= y2)
                    {
                        map[x1][y1]++;
                        x1 = x1 - 1;
                        y1 = y1 - 1;
                    }
                }
            }
        }
        else if (x1 == x2)
        {
            if (y1 <= y2)
            {
                for(int y = y1; y <= y2; y++)
                {
                    map[x1][y]++;   
                }
            }
            else
            {
                for(int y = y1; y >= y2; y--)
                {
                    map[x1][y]++;
                }
            }
        }
        else if (y1 == y2)
        {
            if (x1 <= x2)
            {
                for(int x = x1; x <= x2; x++)
                {
                    map[x][y1]++;   
                }
            }
            else
            {
                for(int x = x1; x >= x2; x--)
                {
                    map[x][y1]++;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] > 1)
            {
                result = result + 1;
            }
        }
    }

    return result;
}


int main()
{
    std::ifstream fin("input.txt");
    
    std::vector<std::pair<Point, Point>> points;
    if (fin.is_open())
    {
        std::string line;
        while (std::getline(fin, line))
        { 
            std::vector<std::string> line_parts;
            boost::split(line_parts, line, boost::is_any_of(",->"));
        
            int x1 = std::stoi(line_parts[0]), y1 = std::stoi(line_parts[1]);
            int x2 = std::stoi(line_parts[3]), y2 = std::stoi(line_parts[4]);
            

            points.push_back(std::make_pair(Point {x1, y1}, Point {x2, y2}));
        }
    }

    int result = solve(points);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
