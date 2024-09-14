#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;

class Students
{
private:
    char name[50], address[50];
    int roll;
    float marks;

public:
    void getData()
    {
        cout << "\nEnter name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter roll: ";
        cin >> roll;
        cout << "Enter marks: ";
        cin >> marks;
        cout << "Enter address: ";
        cin.ignore();
        cin.getline(address, 50);
    }
    void putData()
    {
        cout << setw(10) << name << setw(15) << roll << setw(20) << marks << setw(30) << address << endl;
    }
    int getRoll()
    {
        return roll;
    }
    ~Students() {}
};

int option()
{
    int n;
    cout << "\nWhat would you like to do? " << endl;
    cout << "1. Write records into file\n"
         << "2. Read records from the file\n"
         << "3. Update record in the file\n"
         << "4. Search record of a student\n"
         << "5. Modify record of a student\n"
         << "6. Delete record of a student\n"
         << "7. Count the number of objects in file and total file size\n"
         << "8. Exit\n";
    cin >> n;
    return n;
}

int main()
{
    Students std;
    fstream inout;
    int choice, roll, object, isfound;

    while (true)
    {
        choice = option();
        system("cls");  // Clear the screen
        switch (choice)
        {
        case 1: // Write into the file
        {
            inout.open("REC.txt", ios::out);
            int z;
            cout << "Enter the number of students: ";
            cin >> z;
            for (int i = 0; i < z; i++)
            {
                std.getData();
                inout.write((char *)&std, sizeof(std));
            }
            cout << "File written!!" << endl;
            inout.close();
            break;
        }

        case 2: // Read file
        {
            inout.open("REC.txt", ios::in);
            cout << "Current content of the file" << endl;
            cout << setw(10) << "Name" << setw(15) << "Roll No" << setw(20) << "Marks" << setw(30) << "Address" << endl;
            while (inout.read((char *)&std, sizeof(std)))
            {
                std.putData();
            }
            inout.close();
            break;
        }

        case 3: // Update the record of the students
        {
            inout.open("REC.txt", ios::app);
            cout << "Add student record: " << endl;
            std.getData();
            inout.write((char *)&std, sizeof(std));
            cout << "Record Added!!!" << endl;
            inout.close();
            break;
        }

        case 4: // Search the record of the student
        {
            inout.open("REC.txt", ios::in);
            isfound = 0;
            cout << "Enter Roll number: ";
            cin >> roll;
            while (inout.read((char *)&std, sizeof(std)))
            {
                if (std.getRoll() == roll)
                {
                    isfound = 1;
                    cout << "Searched record!!" << endl;
                    cout << setw(10) << "Name" << setw(15) << "Roll No" << setw(20) << "Marks" << setw(30) << "Address" << endl;
                    std.putData();
                    break;
                }
            }
            if (isfound == 0)
                cout << "The record with the roll number " << roll << " is not found!" << endl;
            inout.close();
            break;
        }

        case 5: // Modify Record
        {
            inout.open("REC.txt", ios::in | ios::out);
            object = isfound = 0;
            cout << "Enter roll number: ";
            cin >> roll;
            while (inout.read((char *)&std, sizeof(std)))
            {
                if (std.getRoll() == roll)
                {
                    isfound = 1;
                    int location = object * sizeof(std);
                    inout.seekp(location, ios::beg);
                    cout << "Enter new data" << endl;
                    std.getData();
                    inout.write((char *)&std, sizeof(std));
                    cout << "Record Modified" << endl;
                    break;
                }
                object++;
            }
            if (isfound == 0)
                cout << "The record with the roll number " << roll << " is not found!" << endl;
            inout.close();
            break;
        }

        case 6: // Delete Record
        {
            inout.open("REC.txt", ios::in);
            Students st[48];
            int i = 0, j;
            cout << "Enter Roll Number: ";
            cin >> roll;
            while (inout.read((char *)&st[i], sizeof(st[i])))
            {
                ++i;
            }
            j = i;
            inout.close();

            inout.open("REC.txt", ios::out);
            for (int i = 0; i < j; i++)
            {
                if (st[i].getRoll() != roll)
                {
                    inout.write((char *)&st[i], sizeof(st[i]));
                }
            }
            cout << "Record Deleted!!!!" << endl;
            inout.close();
            break;
        }

        case 7: // Count the number of objects in file and total file size
        {
            int fileSize;
            inout.open("REC.txt", ios::in);
            inout.seekg(0, ios::end);
            fileSize = inout.tellg();
            cout << "The total file size is: " << fileSize << " Bytes" << endl;
            cout << "And number of objects: " << (fileSize / sizeof(std)) << endl;
            inout.close();
            break;
        }

        case 8:
            cout << "End of the program." << endl;
            exit(0);

        default:
            cout << "Wrong choice, try again!" << endl;
            break;
        }
    }

    return 0;
}
