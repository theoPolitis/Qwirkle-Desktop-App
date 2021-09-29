#ifndef ASSIGN2_SERIALISEDDATA_H
#define ASSIGN2_SERIALISEDDATA_H
#include <string>
#include <fstream>

class SerialisedData {
    public:
        enum Mode { READ = 1, WRITE = 2, READWRITE = 3};
        
        SerialisedData(std::string file_path, Mode mode);
        ~SerialisedData();

        char* getData();
        size_t getLength();

        // Reads the contents of the file and saves its contents to data
        // Only allowed in READ and READWRITE modes
        void Read();

        // Sets this->data to a deep copy of data
        // Only allowed in WRITE and READWRITE modes
        void Write(char* data, size_t length);

        // Wipes data
        // Only allowed in WRITE and READWRITE modes
        void Clear();

        // Pushes the contents of data to the file
        // Only allowed in WRITE and READWRITE modes 
        void Flush();

    private:
        std::string file_path;
        char* data;
        size_t length;
        Mode mode;
        std::fstream* stream;

        // Deletes data if it's been set
        void deleteData();
};



#endif //ASSIGN2_SERIALISEDDATA_H