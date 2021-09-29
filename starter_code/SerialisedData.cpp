#include "SerialisedData.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Exceptions.h"

using std::ios;

//CONSTRUCTOR
SerialisedData::SerialisedData(std::string file_path, SerialisedData::Mode mode) {
    this->file_path = file_path;
    this->mode = mode;
    data = nullptr;

    std::ios_base::openmode stream_flags = ios::binary;
    if (mode & SerialisedData::Mode::READ)
        stream_flags = stream_flags | ios::in;
    if (mode & SerialisedData::Mode::WRITE)
        stream_flags = stream_flags | ios::out;
    
    stream = new std::fstream(this->file_path, stream_flags);
    if (!(mode & SerialisedData::Mode::WRITE) && !stream->good())
        throw file_not_found_exception();
}

//DECONSTRUCTOR
SerialisedData::~SerialisedData() {
    stream->close();
    delete stream;
    deleteData();
}

void SerialisedData::deleteData() {
    if (data != nullptr)
        delete[] data;
    data = nullptr;
}

char* SerialisedData::getData() {
    return data;
}

size_t SerialisedData::getLength() {
    return length;
}

void SerialisedData::Read() {
    if (!(mode & SerialisedData::Mode::READ))
        throw invalid_mode_exception();
    stream->seekg(0, ios::end);
    length = stream->tellg();
    stream->seekg(0, ios::beg);
    deleteData();
    data = new char[length];
    stream->read(data, length);
}

void SerialisedData::Write(char* data, size_t length) {
    if (!(mode & SerialisedData::Mode::WRITE))
        throw invalid_mode_exception();
    deleteData();
    this->data = new char[length];
    for (size_t i = 0; i < length; ++i)
        this->data[i] = data[i];

    this->length = length;
}

void SerialisedData::Flush() {
    if (!(mode & SerialisedData::Mode::WRITE))
        throw invalid_mode_exception();
    stream->seekp(0, ios::beg);
    stream->write(data, length);
    stream->flush();
}