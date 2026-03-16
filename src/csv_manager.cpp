#include "csv_manager.h"
#include <filesystem>

const string header = "year,month,day,hour,minute,second";


void CSV_Manager::openFile(string path)
{
    bool createHeader = false;  // no header || file does not exist
    bool truncate = false;      // depracted file

    /* Check if file exists */
    if (!filesystem::exists(path))
    {
        createHeader = true;
    }
    
    else 
    {
        /* File exists - validate header (name of columns)*/
        ifstream validate(path);
        string firstRow;
        getline(validate,firstRow);

        if (firstRow != header)
        {
            createHeader = true;
            truncate = true;
        }
        validate.close();
    }

    /* Open with proper attribute */
    if (truncate) file.open(path);
    else file.open(path,ios::app);

    
    if (!file.is_open())
    {
        cout <<"Failed to open file!" << endl;
    }

    if (createHeader)
    {
        file << header << "\n";
    }

}

void CSV_Manager::closeFile()
{
    if (file.is_open())
    {
        file.close();
    }
}

void CSV_Manager::AddRow()
{

}