#include "mstime.h"

using namespace std;

// default contructor
MStime::MStime() {
    tmp = new tm();
    tmp->tm_isdst = 0;
}

// contructor takes a tm* and an amount of milliseconds
MStime::MStime(tm* t, unsigned long i /*=0 by default*/) {
    setTM(t);
    setMS(i);
}

// copy constructor
MStime::MStime(const MStime& m){
    setTM(m.tmp);
    setMS(m.ms);
}

// = copies contents of MStime
MStime MStime::operator=(const MStime &other){
    MStime m;
    m.setTM(other.tmp);
    m.setMS(other.ms);
    return m;
}

// copy contents of tm struct. needed so the struct can be copied and then only one copy of it changed
void MStime::setTM(tm* t){
    tmp = new tm();
    tmp->tm_isdst = t->tm_isdst;
    tmp->tm_sec = t->tm_sec;
    tmp->tm_min = t->tm_min;
    tmp->tm_hour = t->tm_hour;
    tmp->tm_mday = t->tm_mday;
    tmp->tm_mon = t->tm_mon;
    tmp->tm_year = t->tm_year;
}

// controls what can ms can be set to. if the number is too large it can wrap around to seconds, minutes, hours, and days
void MStime::setMS(unsigned long i){
    int s = tmp->tm_sec, min = tmp->tm_min, h = tmp->tm_hour, d = tmp->tm_mday;
    ms = i;

    while (ms >= 1000){
        ms -= 1000;
        s++;

        if (s >= 60){
            s -= 60;
            min ++;
        }
        if (min >=60){
            min -= 60;
            h ++;
        }
        if (h >= 24){
            h -= 24;
            d ++;
        }
    }
    tmp->tm_hour = h; tmp->tm_min = min; tmp->tm_sec = s; tmp->tm_mday = d;
}

// add i milliseconds to this MStime. wraps around to seconds, minutes, hours, and days
MStime MStime::operator+(const unsigned long i){
    MStime* m = new MStime(*this);

    m->ms += i;
    while (m->ms >= 1000){
        m->ms -= 1000;
        m->tmp->tm_sec++;

        if (m->tmp->tm_sec >= 60){
            m->tmp->tm_sec -= 60;
            m->tmp->tm_min++;
        }
        if (m->tmp->tm_min >= 60){
            m->tmp->tm_hour++;
            m->tmp->tm_min -= 60;
        }
        if (m->tmp->tm_hour >= 24){
            m->tmp->tm_mday++;
            m->tmp->tm_yday++;
            m->tmp->tm_wday++;
            m->tmp->tm_hour -= 24;
        }
    }

    return *m;
}

// finds the difference between two times. positive when this time is after the given other time
double MStime::operator-(const MStime &other){
    time_t t1 = mktime(tmp);
    time_t t2 = mktime(other.tmp);
    double d = difftime(t1,t2); // t1 - t2
    d *= 1000;
    d += (ms - other.ms);
    return d;
}

// formats this time as the time portion of a UDP string
string MStime::toString(){
    string s = ""; char * c = new char[10];
    s += "-D"; s += to_string(tmp->tm_mday); s += "."; s += to_string(tmp->tm_mon + 1);
    s += "."; s += to_string(tmp->tm_year - 100); s += "T"; s += to_string(tmp->tm_hour);
    s += "."; s += to_string(tmp->tm_min); s += "."; s += to_string(tmp->tm_sec);
    sprintf(c,"%03u",static_cast<unsigned int>(ms)); s += string(c); // make sure 3 digits are printed for ms
    s += "-";

    return s;
}
