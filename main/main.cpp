#include <iostream>
#include <iomanip>
#include <fstream>

#include "json.hpp"
#include "test.h"
#include "algoexecutor.h"

using namespace std;

string to_len(string original, int len)
{
    for (int i = original.length(); i < len; ++i)
    {
        original.push_back(' ');
    }
    return original;
}

class Writer
{
public:
    virtual void addLine(string name, vector<float> values)
    {
        if (parent)
        {
            parent->addLine(name, values);
        }
    }
    virtual void write()
    {
        if (parent)
        {
            parent->write();
        }
    }
    Writer *parent;
};

string to_hex(int v)
{
    std::stringstream sstream;
    sstream << std::hex << v;
    return sstream.str();
}

class JsonWriter : public Writer
{
public:
    nlohmann::json j;
    JsonWriter(Writer *parent_, vector<int> labels)
    {
        parent = parent_;
        j = {
            {"type", "line"},
            {"data",
             {{"labels", labels},
              {"datasets", nlohmann::json::array()}}}};
    }

    virtual void addLine(string name, vector<float> values)
    {
        j["data"]["datasets"].push_back({{"label", name},
                                         {"data", values},
                                         {"borderColor", "#" + to_hex(rand() % 256) + to_hex(rand() % 256) + to_hex(rand() % 256)},
                                         {"backgroundColor", "#FFFFFF"}});
        Writer::addLine(name, values);
    }
    virtual void write()
    {
        fstream fout;
        fout.open("/home/zuievant/Desktop/Projects/PatternMatchingAlgorithmsTester/out.json", ios_base::out);
        fout << j.dump();
        fout.close();
        Writer::write();
    }
};
class FileWritter : public Writer
{
public:
    vector<int> labels;
    map<string, vector<float>> value;

    FileWritter(Writer *parent_, vector<int> labels_)
    {
        parent = parent_;
        labels = labels_;
    }

    virtual void addLine(string name, vector<float> values)
    {
        value[name] = values;
        Writer::addLine(name, values);
    }
    virtual void write()
    {
        fstream fout;
        fout.open("/home/zuievant/Desktop/Projects/PatternMatchingAlgorithmsTester/out.csv", ios_base::out);
        fout << fixed << setprecision(2);
        fout << to_len("length", 12) + "\t";
        for (auto v : labels)
            fout << to_len(to_string(v), 4) << "\t";
        fout << "\n";

        for (auto q : value)
        {
            fout << to_len(q.first, 12) << "\t";
            for (auto v : q.second)
            {
                fout << v << "\t";
            }
            fout << "\n";
        }
        fout.close();
        Writer::write();
    }
};

int main()
{
    vector<Algo *> algos = get_algos();
    vector<int> patternLengths = {8, 16, 32, 48, 64, 96, 128, 192, 256};
    vector<vector<float>> test_res = test(algos, patternLengths, 64, 900000, 20, 5);

    Writer *wr1 = new JsonWriter(nullptr, patternLengths);
    Writer *writter = new FileWritter(wr1, patternLengths);

    for (int i = 0; i < test_res.size(); ++i)
    {
        writter->addLine(algos[i]->name, test_res[i]);
    }
    writter->write();
}