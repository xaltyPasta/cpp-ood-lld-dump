#include <bits/stdc++.h>
using namespace std;


// +---------------------+
// |       Cell          |
// +---------------------+
// | - value: string     |
// | - formula: string   |
// | - dependents: vector<Cell*> |
// +---------------------+
// | + setValue(string)  |
// | + setFormula(string)|
// | + evaluate():string |
// +---------------------+

//         ▲ uses
//         |
// +-----------------------+
// |        Sheet          |
// +-----------------------+
// | - cells: 2D vector<Cell>  |
// +---------------------------+
// | + getCell(row, col)       |
// | + getCellByRef(ref)       |
// | + setCellValue()          |
// | + setCellFormula()        |
// +---------------------------+

//         ▲ uses
//         |
// +-----------------------------+
// |       FormulaParser         |
// +-----------------------------+
// | + evaluate(formula, sheet)  |
// +-----------------------------+

class Cell
{
    string value;
    string formula;
    vector<Cell *> dependents;

    void setValue(const string &val);
    void setFormula(const string &f);
    string evaluate();
};

class Sheet
{
private:
    int rows, cols;
    vector<vector<Cell>> Cells;

public:
    Sheet(int rows, int cols);
    Cell &getCell(int row, int col);
    Cell &getCellByRef(const string &ref);
    void setCellValue(int row, int col, const string &value);
    void setCellFormula(int row, int col, const string &formula);
    void updateDependencies(Cell &cell);
};

class FormulaParser
{
public:
    static string evaluate(const string &formula, Sheet &sheet);
};

int main()
{
    return 0;
}