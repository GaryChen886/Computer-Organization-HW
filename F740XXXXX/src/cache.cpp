#include<bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;
typedef long long ll;
void move(int size, int begin, vector<int> &cache){   
    int temp = cache[begin]; 
    for(int i = begin; i < size - 1; i++){
        cache[i] = cache[i+1];
    }
    cache[size-1] = temp;    
}

int inputSet(int size, vector<int> &cache, int address){
    for(int i = 0; i < size; i++){
        if(cache[i] == address)
            return i;
    }
    return -1;
}

int32_t main(int argc, char **argv){
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string input;
    ifstream trace(argv[1]);
    ofstream output;
    output.open(argv[2]);
    ll cache_word = 0;
    ll block_word = 0;
    ll associativity = 0; 
    ll replace = 0; 
    
    
    getline(trace, input);
    cache_word = stoi(input);
    getline(trace, input);
    block_word = stoi(input);
    getline(trace, input);
    associativity = stoi(input);
    getline(trace, input);
    replace = stoi(input);    
    ll blocks = cache_word / block_word;
    ll temp = blocks;
    ll offset = block_word * 4;
    vector<int> directed_cache;
    vector<vector<int>> asso_cache;
    double miss_num = 0, hit_num = 0, miss_rate = 0;
    ll tag = 0, index = 0;
    ll index_bit = 0, offset_bit = 0;
    ll set_num = 0;
    while(offset != 1){
        offset_bit++;
        offset = offset / 2;
    }
    while(temp != 1){
        index_bit++;
        temp = temp / 2;
    }
    ll address = 0;    
    switch(associativity){
        case 0:
            directed_cache.resize(blocks);
            while(getline(trace, input)){
                address = stoi(input);
                address = address * 4;
                address = address >> offset_bit;
                tag = address >> index_bit;
                
                if(tag)
                    index = address % blocks;
                else
                    index = address;                
                if(directed_cache[index] == 0){
                    output << "-1\n";
                    miss_num++;
                    directed_cache[index] = tag;
                } 
                else if(directed_cache[index] && directed_cache[index] != tag){
                    output << directed_cache[index] << "\n";
                    miss_num++;
                    directed_cache[index] = tag;
                } 
                else {
                    output << "-1\n";
                    hit_num++;
                }                
            }
            break;
        case 1:
            set_num = blocks / 4;
            asso_cache.resize(set_num);
            index_bit -= 2;
            while(getline(trace, input)){
                address = stoi(input);
                address = address * 4;
                address = address / (offset_bit * 2);              
                tag = address / (index_bit * 2);
                if(tag)
                    index = address % set_num;
                else
                    index = address;                
                if(asso_cache[index].size() != 4 && inputSet(asso_cache[index].size(), asso_cache[index], tag) == -1){
                    output << "-1\n";
                    asso_cache[index].push_back(tag);
                    miss_num++;             
                } 
                else if(inputSet(asso_cache[index].size(), asso_cache[index], tag) != -1){
                    output << "-1\n";
                    move(asso_cache[index].size(), inputSet(asso_cache[index].size(), asso_cache[index], tag), asso_cache[index]);
                    hit_num++;
                } 
                else {
                    output << asso_cache[index][0] << "\n";
                    asso_cache[index][0] = tag;
                    move(4, 0, asso_cache[index]);
                    miss_num++;
                }
            }
            break;
        case 2:
            set_num = blocks / blocks;
            asso_cache.resize(set_num);            
            index = 0;
            while(getline(trace, input)){
                address = stoi(input);
                address = address * 4;
                address = address / (offset_bit * 2);
            
                tag = address;                
                if(asso_cache[index].size() != blocks && inputSet(asso_cache[index].size(), asso_cache[index], tag) == -1){
                    output << "-1\n";
                    asso_cache[index].push_back(tag);
                    miss_num++;             
                } 
                else if(inputSet(asso_cache[index].size(), asso_cache[index], tag) != -1){
                    output << "-1\n";
                    move(asso_cache[index].size(), inputSet(asso_cache[index].size(), asso_cache[index], tag), asso_cache[index]);
                    hit_num++;
                } 
                else {
                    output << asso_cache[index][0] << "\n";
                    asso_cache[index][0] = tag;
                    move(4, 0, asso_cache[index]);
                    miss_num++;
                }
            }
            break;
            
    }    
    output << fixed << setprecision(6) << "Miss rate = " << miss_num / (miss_num + hit_num);
    return 0;
}

