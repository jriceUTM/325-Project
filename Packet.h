
#ifndef PACKET_H
#define PACKET_H

#include <string>
using namespace std;

struct Packet {
    string source;
    string destination;
    string payload;
    int priority;

    bool operator<(const Packet& other) const {
        return priority < other.priority;
    }

    bool operator>(const Packet& other) const {
        return priority > other.priority;
    }
};

#endif
