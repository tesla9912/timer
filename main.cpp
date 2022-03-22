#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>

using namespace std;

class timer {
private:
    tm askedTime, currentTime, differenceInTime;
    time_t now;
public:
    timer()
    {
        now = time(0);
        currentTime = *localtime(&now);
        askedTime = currentTime;
        askedTime.tm_sec = 0;
    }

    void getTime(){
        string Time;
        cout<<"Enter time in 24-hour format [HH:MM] : "; getline(cin,Time);
        int pos = 0;
        while ((pos = Time.find(':')) != string::npos)
        {
            string token = Time.substr(0,pos);
            stringstream convert (token);
            convert >> askedTime.tm_hour;
            Time.erase(0,pos+1);
        }
        stringstream convert (Time);
        convert >> askedTime.tm_min;
    }

    void timeDifference() // function to calculate difference between current time and asked time.
    {
        int seconds = difftime(mktime(&askedTime),now);
        differenceInTime.tm_min = seconds / 60;
        differenceInTime.tm_hour = differenceInTime.tm_min / 60;
        differenceInTime.tm_min = differenceInTime.tm_min % 60;
        differenceInTime.tm_sec = seconds % 60;
        if (seconds < 0)
        {
            differenceInTime.tm_hour = 24 + differenceInTime.tm_hour - 1;
            differenceInTime.tm_min = 0 - differenceInTime.tm_min;
            differenceInTime.tm_sec = 0 - differenceInTime.tm_sec;
        }
    }


    void start_timer() // function to start timer and print the time reaming to hit the desired time.
    {
        while (true)
        {
            system("clear");
            now = time(0);
            currentTime = *localtime(&now);
            timeDifference();
            cout<<"TIME REMAINING:    "<<differenceInTime.tm_hour<<":"<<differenceInTime.tm_min<<":"<<differenceInTime.tm_sec;
            if (differenceInTime.tm_hour == 0 && differenceInTime.tm_min == 0 && differenceInTime.tm_sec == 0)
            {
                cout<<endl<<"Time Completed"<<endl;
                break;
            }
        }
    }
};


int main()
{
    timer A;
    A.getTime();
    A.start_timer();

    return 0;
}




