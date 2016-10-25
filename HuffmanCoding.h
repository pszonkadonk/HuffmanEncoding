//
//  HuffmanCoding.h
//  HuffmanCodingAssignment
//
//  Created by Michael Pszonka on 12/7/15.
//  Copyright (c) 2015 Michael Pszonka. All rights reserved.
//




#ifndef HuffmanCodingAssignment_HuffmanCoding_h
#define HuffmanCodingAssignment_HuffmanCoding_h

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>


// Node for holding a symbol and frequency

struct node {
public:
    struct node *left;
    struct node *right;
    std::string prefix = "";
    char symbol;
    int frequency;
    
    node() {}
    
    node(int f) {
        
        frequency = f;
        symbol = '\0';
    }
};

// Serves as comparator for priority queue in order to sort the queue by frequencies.

struct cmpnode {
    bool operator()(const node *left, const node *right) { return left->frequency > right->frequency; }
};

// HuffmanTree  holds the bitLength which is the number of bits in the coded message.
// The prefix, for traversing nodes and recording either a 0 or 1.
// leaf refers to the nodes that will be added to the trees/forests
// forest is the priority queue data structure that holds all individual nodes/trees until their time to be merged.

struct HuffmanTree {
    
    int bitLength = 0;
    std::string prefix = "";
    node *leaf;
    node *root;
    std::priority_queue<node*, std::vector<node*>, cmpnode> forest;
    
};

// Huffman Coding contains the members that perform operations to encode files

class HuffmanCoding {
    
public:
    // constructor
    HuffmanCoding();
    
    // read file will read in the inFile.dat and remove all spaces/punctuation/special characters.
    // it then merges the contents of the file into a singular string.
    
    std::string readFile();
    
    // counts the occurences of each symbol (character) in the file and
    // returns a map (frequency table) with that information.
    // in addition it outputs this frequency table to outFile.dat
    
    std::map<char, int> countFrequency(std::string &f);
    
    
    // creates struct nodes out of each symbol in the
    // frequency Table and inserts each individual node into
    // the priority queue, forest
    
    void createNodeHeap(std::map<char, int> &m);
    
    // mergeNodes performs the action of building up trees
    // within the priority queue until the forest has a
    // length of one, at which point it returns a pointer
    // to the root node in the Huffman Tree
    
    node* mergeNodes();
    
    // generates the Huffman encoding for each symbol
    // in the file by traversing the tree and marking either
    // a 0 or 1.  Parameter pre is a default value, in order to
    // keep track of the encoding during traversal.
    
    void generateCodes(node *leaf, std::string pre="");
    
    // Write the total bit length of the encoded message to outFile.dat
    
    void writeBitLength();
    
    // file content prior to being cleaned
    
    std::string fileContent;
    
    // file content without punctuation/spaces/special characters
    
    std::string cleanedFileContent;
    
    // frequency Table
    
    std::map<char, int> frequencyTable;
    
    // HuffmanTree struct that holds the queue/prefix codes/bitlength etc
    
    HuffmanTree huffmanTree;
    
private:
    // inputFile and outputFile
    // inFile.dat and outFile.dat
    std::ifstream inputFile;
    std::ofstream outputFile;
    
};


#endif
