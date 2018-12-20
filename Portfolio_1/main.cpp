#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

       class Sensor{
              public:
              //int a,b;
       };
// Sub class inheriting from Base Class(Sensor)
       class Temperaturesensor : public Sensor
       {
              public:
              int a=20;
       };

// Sub class inheriting from Base Class(Sensor)
       class Humiditysensor : public Sensor
       {
              public:
              int b=40;
       };

       class IoT_Queue
       {
             public:
               int a,b;
             public:
               void tempValue()
               {
                 int a=20;
                  while(a++ < 30)
                    {
                        int temp = (rand() % 70) + 1;
                        cout << "The Temperature Sensor Value: " << temp <<endl;
                    }
               }
               void humValue()
               {
                 int b=40;
                 while(b++ < 50)
                    {
                        int humidity = (rand() % 70) + 1;
                        cout << "The Humidity Sensor Value: " << humidity <<endl;
                    }

               }
       };
//main function
       int main()
       {
            
          cout << "The Temperature and Humidity Sensor readings Storing in Data Queue " <<endl; 
          Temperaturesensor temp;
		  Humiditysensor hum;
          IoT_Queue obj3;
		  temp.a;
		  hum.b;
          obj3.tempValue();
          obj3.humValue();
          cout << "The Sensor Values is been Stored in Data Queue"<<endl;
           

        return 0;
	   }
