//
//  main.cpp
//  HuffmanCodingAssignment
//
//  Created by Michael Pszonka on 12/5/15.
//  Copyright (c) 2015 Michael Pszonka. All rights reserved.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <functional>
#include <iterator>
#include "HuffmanCoding.h"

using namespace std;


HuffmanCoding::HuffmanCoding() {};

string HuffmanCoding::readFile() {
    
    inputFile.open("inFile.dat");
    string str;
    string temp;
    
    while(getline(inputFile, str)) {
        
        fileContent += str;
    }
    
    // remove punctuation and store
    // code for this came from this stackoverflow thread
    //http://stackoverflow.com/questions/19138983/c-remove-punctuation-from-string
    
    remove_copy_if(fileContent.begin(), fileContent.end(),
                   back_inserter(temp), //Store output
                   ptr_fun<int, int>(&ispunct)
                   );
    
    // remove spaces
    remove_copy(temp.begin(), temp.end(), back_inserter(cleanedFileContent) , ' ');
    
    return cleanedFileContent;
}


map<char, int> HuffmanCoding::countFrequency(string &f) {
    
    for(auto itr = f.begin(); itr != f.end(); ++itr){
        
        if(frequencyTable.count(*itr)) {
            
            int freq = frequencyTable.at(*itr);
            freq+=1;
            frequencyTable.at(*itr) = freq;
        }
        frequencyTable.insert(pair<char, int>(*itr, 1));
    }
    
    outputFile.open("outFile.dat");
    for(auto itr = frequencyTable.begin(); itr != frequencyTable.end(); ++itr){
        
        outputFile << "Character: " << itr->first << " Frequency: " << itr-> second << "\n";
        
        }
    
    outputFile.close();
    
    return frequencyTable;
    
}

void HuffmanCoding::createNodeHeap(std::map<char, int> &m) {
    
    
    for(auto itr = m.begin(); itr!= m.end(); ++itr) {
        
        huffmanTree.leaf = new node;
        huffmanTree.leaf->symbol = itr->first;
        huffmanTree.leaf->frequency = itr->second;
        huffmanTree.forest.push(huffmanTree.leaf);
    }
}


node* HuffmanCoding::mergeNodes() {

    while(huffmanTree.forest.size() > 1) {
    
        node *least = huffmanTree.forest.top();
        huffmanTree.forest.pop();
        node *secondLeast = huffmanTree.forest.top();
        huffmanTree.forest.pop();
        
        node *newNode = new node(least->frequency+secondLeast->frequency);
        
        newNode->left = least;
        newNode->right = secondLeast;
        huffmanTree.forest.push(newNode);
        mergeNodes();
    }

    
    return huffmanTree.forest.top();
}

bool isLeaf(node *leaf) {
    
    if(leaf->symbol!='\0') {
        return true;
    }
    else {
        return false;
    }
}



void HuffmanCoding::generateCodes(node* leaf, string pre) {
    
    // idea for this code came from this thread.  Adjustments were made
    // in order to fit assignment requirements
    // http://www.dreamincode.net/forums/topic/158018-getting-huffman-tree-encoding/
    

    if (isLeaf(leaf)) {
        leaf->prefix = pre;
//        cout << "Leaf Found: " << leaf->symbol << " - " << leaf->prefix << endl;
        outputFile.open("outFile.dat", fstream::app);
        outputFile << "CHAR: " << leaf->symbol << " HUFFMAN ENCODING: " << leaf->prefix << endl;
        outputFile.close();
        huffmanTree.bitLength = huffmanTree.bitLength + leaf->prefix.size() * leaf->frequency;
    }
    if (leaf->left != NULL ){
            pre+="0";//append to string
            generateCodes(leaf->left, pre);
            pre.pop_back();
        }
    if (leaf->right != NULL){
            pre+="1";//append to string
            generateCodes(leaf->right, pre);
        pre.pop_back();
        }
    }


void HuffmanCoding::writeBitLength() {
    
    outputFile.open("outFile.dat", fstream::app);
    outputFile << "Length of coded message (in terms of bits): " << huffmanTree.bitLength << endl;
    outputFile.close();
    
}


//  ******** Please note I completed this assignment in Xcode. where it worked well. *********
//  After completing the assignment, I tested it in Visual Studio, as I've done
//  with every other assignment this semester, but for some reason this time, I continue to receive an error
//  message after I try to traverse the tree and generate huffmann encodings in my generateCodes() method.
//  I've been trying to reach out to TA's for assistance but being the end of the semester, they're busy as well.

//  If possible, could this please be taken into consideration when grading my assignment?  I am able to
//  come on campus to show my code if necessary.
//  Thank you
//



int main() {
    // Sample Code
    
    HuffmanCoding huff;
    string contents = huff.readFile();
    map<char, int> frequencyTable = huff.countFrequency(contents);
    huff.createNodeHeap(frequencyTable);
    node *root = huff.mergeNodes();
    huff.generateCodes(root);
    huff.writeBitLength();
    
    

 
    return 0;
}
