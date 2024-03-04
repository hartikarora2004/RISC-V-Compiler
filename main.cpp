#include<bits/stdc++.h>
#include <fstream>
using namespace std;
// R format - add, and, or, sll, slt, sra, srl, sub, xor, mul, div, rem
// I format - addi, andi, ori, lb, ld, lh, lw, jalr
// S format - sb, sw, sd, sh
// SB format - beq, bne, bge, blt
// U format - auipc, lui
// UJ format - jal
std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
int main()
    {   
        std::map<string,vector<std::string>> encodes_map = {
        {"add", {"0000011", "000", 'R'}},
        {"and", {"0000011", "111", 'R'}},
        {"or", {"0000011", "110", 'R'}},
        {"sll", {"0000011", "001", 'R'}},
        {"slt", {"0000011", "010", 'R'}},
        {"sra", {"0000011", "101", 'R'}},
        {"srl", {"0000011", "101", 'R'}},
        {"sub", {"0100011", "000", 'R'}},
        {"xor", {"0000011", "100", 'R'}},
        {"mul", {"0000011", "000", 'R'}},
        {"div", {"0000011", "100", 'R'}},
        {"rem", {"0000011", "110", 'R'}},
        {"addi", {"0010011", "000", 'I'}},
        {"andi", {"0010011", "111", 'I'}},
        {"ori", {"0010011", "110", 'I'}},
        {"lb", {"0000011", "000", 'I'}},
        {"ld", {"0000011", "011", 'I'}},
        {"lh", {"0000011", "001", 'I'}},
        {"lw", {"0000011", "010", 'I'}},
        {"jalr", {"1100111", "000", 'I'}},
        {"sb", {"0100011", "000", 'S'}},
        {"sw", {"0100011", "010", 'S'}},
        {"sd", {"0100011", "011", 'S'}},
        {"sh", {"0100011", "001", 'S'}},
        {"beq", {"1100011", "000", 'B'}},
        {"bne", {"1100011", "001", 'B'}},
        {"bge", {"1100011", "101", 'B'}},
        {"blt", {"1100011", "100", 'B'}},
        {"auipc", {"0010111", "000", 'U'}},
        {"lui", {"0110111", "000", 'U'}},
        {"jal", {"1101111", "000", 'J'}}
    };
        map <string,int> labels;
        ifstream file("assemblycode.asm");
        printf("The contents of the file are: \n");
        int pc = 0x0 ;
        if(file.is_open())
        {   
            while(!file.eof())
            {
                string line;
                getline(file, line);
                if(line.find(':') != string::npos)
                {
                    string label = line.substr(0, line.find(':'));
                    labels[label] = pc;
                }
                else
                    {
                    pc += 4 ;
                    }
            }
        }
        file.close();
        ofstream mc("machinecode.mc");
        pc = 0x0;
        while(!file.eof())
            {
                string line;
                getline(file, line);
                if(line.find(':') == string::npos)
                    {   
                        vector<string> tokens = splitString(line, ' ');
                        string instruction = tokens[0];
                        char format = encodes_map[instruction][2];
                        switch(format)
                        {
                            case 'R': 
                                mc << pc," ",encode_in_r(tokens)<< endl;
                            case 'I':
                                mc << pc," ",encode_in_i(tokens)<< endl;
                            case 'S':
                                mc << pc," ",encode_in_s(tokens)<< endl;
                            case 'B':
                                mc << pc," ",encode_in_sb(tokens)<< endl;
                            case 'U':
                                mc << pc," ",encode_in_u(tokens)<< endl;
                            case 'J':
                                mc << pc," ",encode_in_uj(tokens)<< endl;

                        }
                        pc += 4 ;
                    }
            }
        return 0;
    }

