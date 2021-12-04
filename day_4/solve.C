#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <boost/algorithm/string.hpp>

// Position
struct Position
{
    int value;
    bool is_visited;
};

// Represent the board
struct Board
{
    std::vector<std::vector<Position>> data;
};

void mark_visited(int number, Board* board)
{
    for (int i = 0; i < board->data.size(); i++)
    {
        for (int j = 0; j < board->data[i].size(); j++)
        {
            if (board->data[i][j].value == number)
            {
                board->data[i][j].is_visited = true;
            }
        }
    }
}

bool is_it_a_win(Board board)
{
    // Check rows
    for (size_t i = 0; i < board.data.size(); i++)
    {
        bool is_bingo = true;
        for (size_t j = 0; j < board.data[i].size(); j++)
        {
            if (board.data[i][j].is_visited == false)
            {
                is_bingo = false;
            }
        }
        if (is_bingo)
        {
            return true;
        }
    }

    // check columns
    for (size_t j = 0; j < board.data[0].size(); j++)
    {
        bool is_bingo = true;
        for (size_t i = 0; i < board.data.size(); i++)
        {
            if (board.data[i][j].is_visited == false)
            {
                is_bingo = false;
            }
        }
        if (is_bingo)
        {
            return true;
        }
    }


    // check left diagonal
    bool is_bingo = true;
    for (size_t i = 0; i < board.data.size(); i++)
    {
        for (size_t j = 0; j < board.data[i].size(); j++)
        {
            if (i != j)
            {
                continue;
            }
            if (board.data[i][j].is_visited == false)
            {
                is_bingo = false;
            }
        }
    }
    if (is_bingo)
    {
        return true;
    }

    // check right diagonal
    is_bingo = false;
    for (int j = board.data[0].size() - 1; j >= 0; j--)
    {
        for (int i = 0; i < board.data.size(); i++)
        {
            if ( i + j != board.data.size())
            {
                continue;
            }
            if (board.data[i][j].is_visited == false)
            {
                is_bingo = false;
            }
        }
    }
    if (is_bingo)
    {
        return true;
    }

    return false;
}

int get_remaining_numbers(Board board)
{
    int result = 0;
    for (int i = 0; i < board.data.size(); i++)
    {
        for (int j = 0; j < board.data[i].size(); j++)
        {
            if (board.data[i][j].is_visited == false)
            {
                result = result + board.data[i][j].value;
            }
        }
    }
    return result;
}

int solve(std::vector<Board> boards, std::vector<int> numbers)
{
    
    int last_number;
    std::vector<int> bingo_order;

    for (auto number: numbers)
    {
        for(size_t i = 0; i < boards.size(); i++)
        { 
            mark_visited(number, &boards[i]);
            if (std::find(bingo_order.begin(), bingo_order.end(), i) == bingo_order.end())
            {
                if (is_it_a_win(boards[i]))
                {
                    last_number = number;
                    bingo_order.push_back(i);
                }
            }
        }
       
        if (bingo_order.size() == boards.size())
        {
            break;
        }
    }

    Board board = boards[bingo_order.back()];

    int remaining = get_remaining_numbers(board);
    return remaining * last_number;
}
        
int main()
{
    std::ifstream fin("input.txt");
    
    std::vector<int> numbers;
    std::vector<Board> boards;

    if (fin.is_open())
    {
        std::string line;
        std::getline(fin, line);
        
        std::vector<std::string> line_parts;
        boost::split(line_parts, line, boost::is_any_of(","));
        for (int i = 0; i < line_parts.size(); i++)
        {
            numbers.push_back(std::stoi(line_parts[i]));
        }
        getline(fin, line);
        
        std::vector<std::vector<Position>> board;
        while(std::getline(fin, line))
        {
            if (line.empty())
            {   
                Board br;
                br.data = board;
                boards.push_back(br);
                board.clear();
            }
            else
            {
                line_parts.clear();
                boost::split(line_parts, line, boost::is_any_of(" "));
                std::vector<Position> temp;
                for (int i = 0; i < line_parts.size(); i++)
                {
                    if (line_parts[i].length() == 0)
                    {
                        continue;
                    }
                    Position position;
                    position.value = std::stoi(line_parts[i]);
                    position.is_visited = false;
                    temp.push_back(position);
                }
                board.push_back(temp);
            }
        }
        
        Board br;
        br.data = board;
        boards.push_back(br);
        board.clear();
    }
    
    int result = solve(boards, numbers);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
