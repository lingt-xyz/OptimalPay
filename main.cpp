#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <limits>


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
    // key: the denomination; value: how many denomination
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
 * Dynamic programming to solve the optimal pay problem.
 */
Output optimalPay(Input input)
{
    Output output;
    if(input.amount <= 0 || input.denominations.size() <= 0)
    {
        output.hasSolution = false;
        return output;
    }

    /*
     * first step: construct the c-table and s-table
     */
    // cTable is used to store how many denomination in an optimal solution
    int cTable [input.amount+1];
    // sTable stores the preceding amount that can leads to an optimal solution to the current amount.
    int sTable [input.amount+1];

    cTable [0] = 0;
    sTable [0] = 0;
    int infinity = std::numeric_limits<int>::max();
    for(int amount=1; amount<= input.amount; amount++)
    {
        int minCost = infinity;
        sTable [amount] = -1;
        for (int d : input.denominations)
        {
            int cost = 1;
            if((amount - d >= 0) && (cTable[amount - d] != infinity))
            {
                cost = 1 + cTable[amount - d];
                if(cost < minCost)
                {
                    minCost = cost;
                    sTable [amount] = amount - d;
                }
            }
        }
        cTable[amount] = minCost;
    }

    /*
     * second step: construct the solution
     */
    std::map<int, int, std::greater <int>> solution;
    if(sTable [input.amount] == -1)
    {
        output.hasSolution = false;
    }
    else
    {
        output.hasSolution = true;

        int amount = input.amount;
        int difference;
        do
        {
            difference = amount - sTable[amount];
            amount = sTable[amount];
            solution[difference]++;
        }
        while(amount);
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
