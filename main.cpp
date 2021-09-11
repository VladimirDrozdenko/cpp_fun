/*
sample code, just to start, it's run with the following commands:

g++ -std=c++1z -O2 -Wall $1 -lstdc++fs
./a.out $2 $3 $4 $5
echo comparing "correct_output.csv" with $5
cmp --silent correct_output.csv $5 || echo "files are different!" 

where 
  $1 - cpp file name
  $2 - name of input csv
  $3 - column name
  $4 - replacement string
  $5 - output file name

*/

#include <algorithm>
#include <iterator>
#include <string>  
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


const std::string delim = ",";

struct CmdInput {
    std::string inFileName;
    std::string columnName;
    std::string replacementValue;
    std::string outFileName;

    CmdInput(int argc, const char* const argv[]) {
        inFileName = argv[1];       // "expressive_cpp17_before.csv";
        columnName = argv[2];       // "City";
        replacementValue = argv[3]; // "London";
        outFileName = argv[4];      // "expressive_cpp17_after.csv";
    }
};

std::string trimString(const std::string& s) {

    size_t b = 0, e = s.size();
    while (b != e && isspace(s[b]))
        ++b;

    --e;
    while (b != e && isspace(s[e]))
        --e;

    return s.substr(b, e-b+1);
}


void readLine(std::ifstream& fs, std::vector<std::string>& outputColumns) {

    std::string h;
    if (std::getline(fs, h)) {
        size_t b = 0, e = h.find(delim);
        while (e < h.size()) {
            outputColumns.push_back(trimString(h.substr(b, e-b)));
            b = e + 1;
            e = h.find(delim, b+1);
        }
        outputColumns.push_back(trimString(h.substr(b, e-b)));
    }
}

std::string vector2CsvString(const std::vector<std::string>& v) {

    std::string s;
    for (auto i = v.cbegin(); i != v.cend(); ++i) {
        if (i != v.cend() - 1)
            s.append(*i + delim);
        else
            s.append(*i);
    }

    return s;
}

int main(int argc, char* argv[])
{
    if (argc != 5) {
        std::cerr << "Expected input:" << std::endl;
        std::cerr << "   " << argv[0] << " input.csv columnName replacementValue output.csv" << std::endl;
        return 1;
    }

    const CmdInput input(argc, argv);

    std::ifstream fs(input.inFileName);
    if (!fs.is_open()) {
        fs.close();
        return std::cerr << "input file missing" << std::endl, 2;
    }

    std::vector<std::string> headerColumns;
    readLine(fs, headerColumns);
    if (headerColumns.size() == 0) {
        fs.close();
        return std::cerr << "input file missing" << std::endl, 3;
    }

    size_t columnPosition = static_cast<size_t>(-1);
    auto itrFoundPos = std::find(headerColumns.cbegin(), headerColumns.cend(), input.columnName);
    if (itrFoundPos != headerColumns.cend())
        columnPosition = std::find(headerColumns.cbegin(), headerColumns.cend(), input.columnName) - headerColumns.cbegin();

    if (columnPosition == static_cast<size_t>(-1)) {
        fs.close();
        return std::cerr << "column name doesn't exists in the input file" << std::endl, 4;
    }

    std::ofstream os(input.outFileName);
    if (!os.is_open()) {
        fs.close();
        return std::cerr << "failed to open " << input.outFileName << " for write" << std::endl, 5;
    }

    // writing file header
    os << vector2CsvString(headerColumns) << std::endl;
    
    while (!fs.eof()) {
        std::vector<std::string> row;
        readLine(fs, row);
        row[columnPosition] = input.replacementValue;

        // writing modified row
        os << vector2CsvString(row) << std::endl;
    }
    
	os.close();
    fs.close();
}