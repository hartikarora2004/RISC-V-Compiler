#include<bits/stdc++.h>
#include <fstream>
using namespace std;

vector<string> splitString(const string& input, char delimiter) {
    vector<std::string> tokens;
    istringstream iss(input);
    string token;

    while (getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

int string_to_int(string s) {
    int x = 0;
    int sign = 1;

    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1); 
    }

    for(int i = 0; i < s.size(); i++) {
        x = x * 10 + (s[i] - '0');
    }

    return x * sign; 
}

std::map<string,vector<std::string>> encodes_map = {
    {"add", {"0110011", "000", "0000000", "R"}},   // add
    {"and", {"0110011", "111", "0000000", "R"}},   // and
    {"or",  {"0110011", "110", "0000000", "R"}},   // or
    {"sll", {"0110011", "001", "0000000", "R"}},   // sll
    {"slt", {"0110011", "010", "0000000", "R"}},   // slt
    {"sra", {"0110011", "101", "0100000", "R"}},   // sra
    {"srl", {"0110011", "101", "0000000", "R"}},   // srl
    {"sub", {"0110011", "000", "0100000", "R"}},   // sub
    {"xor", {"0110011", "100", "0000000", "R"}},   // xor
    {"mul", {"0110011", "000", "0000001", "R"}},   // mul
    {"div", {"0110011", "100", "0000001", "R"}},   // div
    {"rem", {"0110011", "110", "0000001", "R"}},   // rem
    {"addi", {"0010011", "000", "", "I"}},        // addi
    {"andi", {"0010011", "111", "", "I"}},        // andi
    {"ori",  {"0010011", "110", "", "I"}},        // ori
    {"lb",   {"0000011", "000", "", "I"}},        // lb
    {"ld",   {"0000011", "011", "", "I"}},        // ld
    {"lh",   {"0000011", "001", "", "I"}},        // lh
    {"lw",   {"0000011", "010", "", "I"}},        // lw
    {"jalr", {"1100111", "000", "", "I"}},       // jalr
    {"sb",   {"0100011", "000", "", "S"}},       // sb
    {"sw",   {"0100011", "010", "", "S"}},       // sw
    {"sd",   {"0100011", "011", "", "S"}},       // sd
    {"sh",   {"0100011", "001", "", "S"}},       // sh
    {"beq",  {"1100011", "000", "", "B"}},      // beq
    {"bne",  {"1100011", "001", "", "B"}},      // bne
    {"bge",  {"1100011", "101", "", "B"}},      // bge
    {"blt",  {"1100011", "100", "", "B"}},      // blt
    {"auipc", {"0010111", "000", "", "U"}},     // auipc
    {"lui",   {"0110111", "000", "", "U"}},     // lui
    {"jal",   {"1101111", "000", "", "J"}}     // jal
};

int reg(string register_name) {
    return string_to_int(register_name.substr(1));
}

bitset<32> encode_in_r(vector<string> tokens) {
    bitset<32> machine_code ;
    bitset<32> opcode(encodes_map[tokens[0]][0]);
    bitset<32> rd(reg(tokens[1]));
    rd = rd << 7;
    bitset<32> funct3(encodes_map[tokens[0]][1]);
    funct3 = funct3 << 12;
    bitset<32> rs1(reg(tokens[2])); 
    rs1 = rs1 << 15;
    bitset<32> rs2(reg(tokens[3]));
    rs2 = rs2 << 20;
    bitset<32> funct7(encodes_map[tokens[0]][2]);
    funct7 = funct7 << 25;
    machine_code = (opcode | rd | funct3 | rs1 | rs2 | funct7);
    return machine_code; // Added return statement
}

bitset<32> encode_in_i(vector<string> tokens) {
    bitset<32> machine_code ;
    bitset<32> opcode(encodes_map[tokens[0]][0]);
    bitset<32> rd(reg(tokens[1]));
    rd = rd << 7;
    bitset<32> funct3(encodes_map[tokens[0]][1]);
    funct3 = funct3 << 12;
    bitset<32> rs1(reg(tokens[2])); 
    rs1 = rs1 << 15;
    bitset<32> imm(string_to_int(tokens[3]));
    imm = imm << 20;
    machine_code = (opcode | rd | funct3 | rs1 | imm);
    return machine_code; // Added return statement
}

bitset<32> encode_in_s(vector<string> tokens) {
    bitset<32> machine_code ;
    bitset<32> opcode(encodes_map[tokens[0]][0]);
    bitset<32> rs2(reg(tokens[1]));
    rs2 = rs2 << 20;
    bitset<32> funct3(encodes_map[tokens[0]][1]);
    funct3 = funct3 << 12;
    int index = tokens[2].find('(');
    string imm_str = tokens[2].substr(0, index);
    bitset<32> imm(string_to_int(imm_str));
    bitset<32> rs1(reg(tokens[2].substr(index + 1, tokens[2].size() - index - 2)));
    rs1 = rs1 << 15;
    bitset<32> last_5_bits = imm &  bitset<32>(0x1F);
    last_5_bits = last_5_bits << 7;
    imm = imm << 20;
    bitset<32> first_7_bits = imm &  bitset<32>(0xFE000000);
    machine_code = (opcode | rs2 | funct3 | rs1 | last_5_bits | first_7_bits);
    return machine_code; // Added return statement
}

int main() {   
    map <string,int> labels;
    ifstream file("assemblycode.asm");
    printf("The contents of the file are: \n");
    int pc = 0x0 ;
    
    if (file.is_open()) {   
        while (!file.eof()) {
            string line;
            getline(file, line);
            
            if (line.find(':') != string::npos) {
                string label = line.substr(0, line.find(':'));
                labels[label] = pc;
            } else {
                pc += 4 ;
            }
        }
    }
    
    file.close();
    ofstream mc("machinecode.mc");
    pc = 0x0;
    
    while (!file.eof()) {
        string line;
        getline(file, line);
        
        if (line.find(':') == string::npos) {   
            vector<string> tokens = splitString(line, ' ');
            string instruction = tokens[0];
            char format = encodes_map[instruction][2][0];
            
            switch(format) {
                case 'R': 
                    mc << pc << " " << encode_in_r(tokens) << endl;
                    break;
                case 'I':
                    mc << pc << " " << encode_in_i(tokens) << endl;
                    break;
                case 'S':
                    mc << pc << " " << encode_in_s(tokens) << endl;
                    break;
                 case 'B':
                    mc << pc," ",encode_in_sb(tokens)<< endl;
                    break;
                 case 'U':
                     mc << pc," ",encode_in_u(tokens)<< endl;
                    break;
                 case 'J':
                    mc << pc," ",encode_in_uj(tokens)<< endl;
                    break;
            }
            pc += 4 ;
        }
    }
    return 0;
}
