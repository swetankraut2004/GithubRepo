#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Define a structure to store plant information
struct Plant
{
    int serialNo;
    string commonName;
    string scientificName;
    string typeOfPlant;
    string habitat;
    int lifeSpan;
};

static int lastSerialNo = 0;

void addAPlant(fstream &file, Plant &plant)
{
    lastSerialNo++;
    plant.serialNo = lastSerialNo;

    file << plant.serialNo << "," << plant.commonName << "," << plant.scientificName
         << "," << plant.typeOfPlant << "," << plant.habitat << "," << plant.lifeSpan << "\n";
}

void displayWholeData(ifstream &file)
{
    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }
}

void searchAPlant(ifstream &file, const string &plantName)
{
    string line;
    bool found = false;

    while (getline(file, line))
    {
        vector<string> elements;
        size_t pos = 0;
        string delimiter = ",";
        while ((pos = line.find(delimiter)) != string::npos)
        {
            elements.push_back(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());
        }

        elements.push_back(line);

        if (elements.size() >= 2 && elements[1] == plantName)
        {
            cout << "Plant found:" << endl;
            cout << line << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Plant not found." << endl;
    }
}

void deleteAPlantData(fstream &file, const string &plantName)
{
    string line;
    vector<string> lines;

    while (getline(file, line))
    {
        vector<string> elements;
        size_t pos = 0;
        string delimiter = ",";
        while ((pos = line.find(delimiter)) != string::npos)
        {
            elements.push_back(line);
        }
    }

    file.close();
    file.open("plant_database.csv", ios::out | ios::trunc);

    for (const string &l : lines)
    {
        file << l << "\n";
    }

    cout << "Plant data deleted." << endl;
}

int main()
{
    int choice;
    fstream outFile("plant_database.csv", ios::app);
    ifstream inFile("plant_database.csv");
    fstream inOutFile("plant_database.csv", ios::in | ios::out);

    // Declare a Plant object to use for adding plants
    Plant newPlant;

    while (true)
    {
        cout << "Botanical Garden Management System" << endl;
        cout << "1. Add a Plant" << endl;
        cout << "2. Display All Plants" << endl;
        cout << "3. Search for a Plant" << endl;
        cout << "4. Delete a Plant" << endl;
        cout << "5. Clear All Data" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter Common Name: ";
            cin.ignore();
            getline(cin, newPlant.commonName);
            cout << "Enter Scientific Name: ";
            getline(cin, newPlant.scientificName);
            cout << "Enter Type of Plant: ";
            getline(cin, newPlant.typeOfPlant);
            cout << "Enter Habitat: ";
            getline(cin, newPlant.habitat);
            cout << "Enter Life Span: ";
            cin >> newPlant.lifeSpan;
            addAPlant(outFile, newPlant);
            break;
        }
        case 2:
        {
            displayWholeData(inFile);
            break;
        }
        case 3:
        {
            string searchPlantName;
            cout << "Enter the Plant Name to search: ";
            cin >> searchPlantName;
            searchAPlant(inFile, searchPlantName);
            break;
        }
        case 4:
        {
            string deletePlantName;
            cout << "Enter the Plant Name to delete: ";
            cin >> deletePlantName;
            deleteAPlantData(inOutFile, deletePlantName);
            break;
        }
        case 5:
        {
            inOutFile.close();
            remove("plant_database.csv");
            ofstream newFile("plant_database.csv");
            newFile.close();
            cout << "All data cleared." << endl;
            break;
        }
        case 6:
            cout << "Exiting the program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    }

    return 0;
}
