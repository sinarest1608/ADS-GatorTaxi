// KSHITIJ SINHA
// UFID: 1416-0481
// COP5536 - Spring23

// Importing basic libraries for I/O, File Handling and the gatorTaxiHelper file
// that has the GatorTaxi class and the required functions.
#include <iostream>
#include <fstream>
#include <sstream>
#include "gatorTaxiHelper.h"

using namespace std;

// The main runner for the program. Has been modified to receive command line arguments for the input file name.
// Command to runafter make: < ./gatorTaxi input_file >
int main(int argc, char *argv[])
{
    // Creating object for Gator Taxi class to access functions written.
    GatorTaxi gator_taxi;

    // Check if input file passed in commnad line, else exit the program.
    if (argc <= 1)
    {
        cout << "No Input File!";
        exit(0);
    }

    // Cehck if input file has .txt extension, if not append automatically.
    string input_file = argv[1];
    int flag = 0;
    for (auto s : input_file)
    {
        if (s == '.')
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        input_file += ".txt";
    }
    // Set the input file to file variable
    ifstream inputFile(input_file);
    string line;

    // Open the file and read line by line.
    if (inputFile.is_open())
    {
        for (int i = 0; getline(inputFile, line); i++)
        {
            //  Extract paranthesis index and set inputOperation according to the input file.
            int paranthesisIdx = line.find("(");
            string inputOperation = line.substr(0, paranthesisIdx);

            //  Insert Command
            if (inputOperation == "Insert")
            {
                // Extracting input between paranthesis
                string input = line.substr(6);
                input = input.substr(1, input.size() - 2);
                stringstream ss(input);
                int num1, num2, num3;
                char comma;
                ss >> num1 >> comma >> num2 >> comma >> num3;
                gator_taxi.Insert(num1, num2, num3);
            }
            // Print Command
            else if (inputOperation == "Print")
            {

                // Extracting input between paranthesis
                string input = line.substr(5);
                input = input.substr(1, input.size() - 2);

                if (input.find(',') != std::string::npos)
                {
                    stringstream ss(input);
                    int num1, num2;
                    char comma;
                    ss >> num1 >> comma >> num2;
                    gator_taxi.Print(num1, num2);
                }
                else
                {
                    stringstream ss(input);
                    int num1;
                    char comma;
                    ss >> num1;
                    gator_taxi.Print(num1);
                }
            }
            // UpdateTrip
            else if (inputOperation == "UpdateTrip")
            {
                // Extracting input between paranthesis
                string input = line.substr(10);
                input = input.substr(1, input.size() - 2);
                stringstream ss(input);
                int num1, num2;
                char comma;
                ss >> num1 >> comma >> num2;
                gator_taxi.UpdateTrip(num1, num2);
            }
            // GetNextRide
            else if (inputOperation == "GetNextRide")
            {
                gator_taxi.GetNextRide();
            }
            // CancelRide
            else if (inputOperation == "CancelRide")
            {
                string input = line.substr(10);
                input = input.substr(1, input.size() - 2);
                stringstream ss(input);
                int num1;
                char comma;
                ss >> num1;
                gator_taxi.CancelRide(num1);
            }
        }
    }

    //  Close the input file
    inputFile.close();
    return 0;
}