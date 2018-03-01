#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "string.h"

using namespace std;

class Commands
{
public:
    vector<string> cmds;
    time_t timestamp;
    int cmdCounter;

    void push_back(string str);
    void push_back_block(string str);
    void clear();
};

class Observer
{
public:
    virtual void dump(Commands &cmd) = 0;
};

class Dumper
{
    Commands cmds;
    vector<Observer *> subs;
public:
    void subscribe(Observer *ob);
    void notify();
    void dump_commands(Commands &cmd);
};

class ConsoleDumper : public Observer
{
public:
    ConsoleDumper(Dumper *dmp);
    void dump(Commands &cmd);
};

class FileDumper : public Observer
{
public:
    FileDumper(Dumper *dmp);
    void dump(Commands &cmd);
};


class BulkContext
{
    size_t commandsCount;
    Dumper* dumper;
    ConsoleDumper* conDumper;
    FileDumper* fileDumper;

    Commands cmds;
    string line;
    int curCounter = 0;
    bool blockFound = false;
    int nestedBlocksCount = 0;

public:
    BulkContext(size_t bulk_size);
    ~BulkContext();

    void processLine(const char *line, size_t size);
    void proc();
};
