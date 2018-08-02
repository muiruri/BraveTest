/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kenny
 *
 * Created on August 1, 2018, 8:52 PM
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <regex>

using namespace std;

void countCars(string plate1, string plate2);
void getNumberPlate(string sentence );
int getCarsFromStart(char *plate);
/*
 * 
 */
int main(int argc, char** argv) {   
    getNumberPlate("This is KBQ 714N which was bought after KBN 320G which was after KAA 300 which was bought before KCQ 300B ");
    countCars("KBQ 714N", "KAA 001A");
    return 0;
}

/**
 *  This function outputs the number of cars between the given two plates.
 * @param plate1
 * @param plate2
 */
void countCars(string plate1, string plate2) {
    char plate1Arr[9];
    strcpy(plate1Arr, plate1.c_str());
    
    char plate2Arr[9];
    strcpy(plate2Arr, plate2.c_str());
    
    int x1 = getCarsFromStart(plate1Arr);
    int x2 = getCarsFromStart(plate2Arr);
    
    int total = x1 - x2;
    std::cout << "Number of Cars bought between " + plate1 + " and " + plate2 + " is " + to_string(total) << endl;
}

/**
 *  This function counts the number of cars from the beginning of time to the current plate.
 *  It assumes the plates start from KAA 001A
 * @param plate - The plate number
 * @return - the number of cars from start to the given plate.
 */
int getCarsFromStart(char *plate) {
    int start = 64;
    
    int last = +plate[7] - start;
    
    char number[3];
    number[0] = plate[4];
    number[1] = plate[5];
    number[2] = plate[6];
    int count1 = ((last - 1) * 24) + std::stoi(number);
    
    int letter = +plate[2] - start;
    int letter1Cars = (letter - 1) * 999 * 24;
    
    int letter2 = +plate[1] - start;
    int letter2Cars =  (letter2 - 1) * 999 * 24 * 24;
    
    int total = letter2Cars + letter1Cars + count1;
    return total;
}


/**
 *  Give a sentence, this function uses regular expression to get all the matches for number plate sequence.
 *  A number plate takes the form K** 000*
 *  where ** is any letter except uppercase (i) and (o)
 * @param sentence
 */
void getNumberPlate(string sentence) {
    std::regex r("[A-Z]{3}\\s[0-9]{3}[A-Z]{0,1}"); // entire match will be 2 numbers
    std::smatch m;
    std::regex_search(sentence, m, r);
    
    std::regex_iterator<std::string::iterator> rit ( sentence.begin(), sentence.end(), r );
    std::regex_iterator<std::string::iterator> rend;
  
    int i = 0;
    std::cout << "Found plates " << std::endl;
    while (rit!=rend) {
        std::cout << rit->str() << std::endl;
        ++rit;
        i++;
    }
    if(i > 0) {
        cout << "Summary : found " + std::to_string(i) + " number plates" << endl;
    } else {
        std::cout << "No plates we found. " << std::endl;
    }
}

