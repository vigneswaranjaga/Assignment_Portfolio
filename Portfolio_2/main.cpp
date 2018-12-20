#include<iostream>
using namespace std;
class Sensor
{
  class State *current;
  public:
    Sensor();
    void setCurrent(State *s)
    {
        current = s;
    }
    void idle();
    void sensing();
    void processing();
};

class State
{
  public:
  virtual void idle(Sensor *sen)
    {
        cout << "  Idle\n";
    }
    virtual void sensing(Sensor *sen)
    {
        cout << "   Sensing Sensor\n";
    }
    virtual void processing(Sensor *sen)
    {
        cout << " Sensing sensor\n";
    }
};

void Sensor::idle()
{
  current->idle(this);
}

void Sensor::sensing()
{
  current->sensing(this);
}

void Sensor::processing()
{
  current->processing(this);
}

class Sense: public State
{
  public:
    Sense()
    {
        cout << "   Sensing Temperature Sensor ";
        cout << "   Sensing Humidity Sensor ";
     int a=20;
                  while(a++ < 30)
                    {
                        int temp = (rand() % 70) + 1;
                        cout << "The Temperature Sensor Value: " << temp <<endl;
                    }
     int b=40;
                 while(b++ < 50)
                    {
                        int humidity = (rand() % 70) + 1;
                        cout << "The Humidity Sensor Value: " << humidity <<endl;
                    }
    };
    ~Sense()
    {
        cout << "   Sensing completed\n";
        
    };
   // void processing(Sensor *sen);
};

class Process: public State
{
  public:
    Process()
    {
        cout << " Processing in transfering data ";
    };
    ~Process()
    {
        cout << "   Processing completed\n";
    };
    void sensing(Sensor *sen)
    {
        cout << "   Sensing to processing State";
        sen->setCurrent(new Sense());
        delete this;
    }
};


void Sense::sensing(Sensor *sen)
{
  cout << "   sensing to processing";
  sen->setCurrent(new Process());
  delete this;
}

void Sense::processing(Sensor *sen)
{
  cout << "   Processing to idle";
  sen->setCurrent(new Process());
  delete this;
}

Sensor::Sense()
{
  current = new Process();
  cout << "Idle" ;
}

int main()
{
  void(Sensor:: *ptrs[])() =
  {
    Sensor::processing, Sensor::sensing
  };
  Sensor fsm;
  int num;
  while (1)
  {
    cout << "Enter the state to be done:";
    cin >> num;
    (fsm.*ptrs[num])();
  }
}