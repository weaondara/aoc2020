// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
using namespace std;

void task1(list<string> lines)
{
  set<int> executed;
  int ip = 0;
  int nextip = 0;
  int acc = 0;
  
  while(executed.find(nextip) == executed.end()) {
    ip = nextip;
    executed.insert(ip);
    string line = *next(lines.begin(), ip);
    //cout << nextip << ": " << line << endl;
    string cmd = line.substr(0, 3);
    int val = stoi(line.substr(4));
    if(cmd == "nop")
    {
      nextip++;
    } 
    else if(cmd == "acc")
    {
      acc += val;
      nextip++;
    }
    else if(cmd == "jmp")
    {
      nextip += val;
    }
  }
  
  cout << "Task 1: ip: " << ip << "; next: " << nextip << "; acc: " << acc << endl;
}

int terminates(list<string> lines)
{
  set<int> executed;
  int ip = 0;
  int nextip = 0;
  int acc = 0;
  
  while(executed.find(nextip) == executed.end()) {
    ip = nextip;
    if(ip == lines.size())
      return acc;
    executed.insert(ip);
    string line = *next(lines.begin(), ip);
    //cout << nextip << ": " << "(" << line.length() << ")" << line << endl;
    string cmd = line.substr(0, 3);
    int val = stoi(line.substr(4));
    //cout << "t" << endl;
    if(cmd == "nop")
    {
      nextip++;
    } 
    else if(cmd == "acc")
    {
      acc += val;
      nextip++;
    }
    else if(cmd == "jmp")
    {
      nextip += val;
    }
  }
  //cout << "t2" << endl;
  return 0;
}

void task2(list<string> lines)
{
  int ip = 0;
  int acc;
  while(true) {
    auto it = next(lines.begin(), ip);
    string line = *it;
    //cout << "c " << ip << ": " << line << endl;
    string cmd = line.substr(0, 3);
    int val = stoi(line.substr(4));
    if(cmd == "acc")
    {
      ip++;
    }
    else if(cmd == "jmp")
    {
      string old = string(line);
      //cout << line << " => " << "nop " + to_string(val) << endl;
      *it = "nop " + to_string(val);
      //cout << " => " << *next(lines.begin(), ip) << endl;
      if (acc = terminates(lines))
      {
        break;
      }
      else
      {
        *it = old;
        //cout << " => " << *next(lines.begin(), ip) << endl;
        ip += val;
      }
    }
    else if(cmd == "nop")
    {
      string old = string(line);
      //cout << line << " => " << "jmp " + to_string(val) << endl;
      *it = "jmp " + to_string(val);
      //cout << " => " << *next(lines.begin(), ip) << endl;
      if(acc = terminates(lines))
      {
        break;
      }
      else
      {
        *it = old;
        //cout << " => " << *next(lines.begin(), ip) << endl;
        ip++;
      }
    }
  }
  
  cout << "Task 2: ip: " << ip  << "; acc: " << acc << endl;
}

int main () {
  string line;
  ifstream file ("input");
  list<string> lines;
  if (file.is_open())
  {
    while (getline(file, line))
    {
      if(line.length() > 3)
        lines.push_back(string(line));
    }
    file.close();
  } 
  else cerr << "cannot rea file" << endl;

  task1(lines);
  task2(lines);

  return 0;
}
