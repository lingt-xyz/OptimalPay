#include <iostream>
#include <vector>
#include <map>
#include <fstream>

// alias of descending order Map
using descendingMap = std::map<int, int, std::greater <int>>;

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

struct Input
{
    int amount;
    std::vector<int> denominations;
};

struct Output
{
    bool hasSolution;
    std::map<int, int, std::greater <int>> solution;
};

Input readFile()
{
    Input input;
    input.amount = 0;

    std::ifstream infile(INPUT_FILE_NAME);
    if (!infile.is_open())
    {
        std::cout << "Unable to open file: " << INPUT_FILE_NAME;
        return input;
    }

    // how many denominations are available
    int types = -1;
    // is first line read
    bool firstLine = false;

    int number;
    while(infile >> number)
    {
        if(!firstLine)
        {
            if(number <= 0)
            {
                return input;
            }
            types = number;
            firstLine = true;
        }
        else
        {
            if(types)
            {
                input.denominations.push_back(number);
                types--;
            }
            else
            {
                input.amount = number;
            }
        }
    }
    return input;
}

void writeFile(Output output)
{
    std::ofstream outfile(OUTPUT_FILE_NAME);
    if (!outfile.is_open())
    {
        std::cout << "Unable to open file: " << OUTPUT_FILE_NAME;
        return;
    }
    if(output.hasSolution)
    {
        outfile << 1 << "\n";
        for(auto element : output.solution)
        {
            outfile << element.first << " " << element.second << "\n";
        }
    }
    else
    {
        outfile << 0;
    }
}

/**
 * Greedy algorithm to solve the optimal pay problem.
 */
Output optimalPay(Input input)
{
    Output output;
    if(input.amount <= 0 || input.denominations.size() <= 0)
    {
        output.hasSolution = false;
        return output;
    }

    std::map<int, int, std::greater <int>> solution;
    int quotient;
    int amount = input.amount;
    for (int d : input.denominations)
    {
        quotient = 0;

        // greedy choice: always choose the largest denomination
        if(amount >= d)
        {
            quotient = amount / d;
            amount = amount % d;
        }

        // ignore the unused denomination
        if(quotient)
        {
            solution[d] = quotient;
        }
    }

    if(amount != 0)
    {
        output.hasSolution = false;
    }
    else
    {
        output.hasSolution = true;
        output.solution = solution;
    }
    return output;
}

int main()
{
    Input input = readFile();
    Output output = optimalPay(input);
    writeFile(output);
    return 0;
}
