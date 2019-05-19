#ifndef EXTERNALCONDITIONS_H
#define EXTERNALCONDITIONS_H


class ExternalConditions{
public:
    enum Season { // enum of seasons
        spring, // 0
        summer, // 1
        autumn, // 2
        winter, // 3
    };
    enum Weather { // enum of weather conditions
        rainy,
        sunny,
        windy,
        snowy,
    };
    ExternalConditions();
    ExternalConditions(int temp, Season mySeason, Weather myWeather);
    void setTemp(int t);
    int getTemp();
    void setSeason(Season s);
    void setSeason(int index);
    Season getSeason();
    void setWeather(Weather w);
    void setWeather(int index);
    Weather getWeather();
private:
    int temp; // temperature
    Season mySeason; // season
    Weather myWeather; // weather
};
#endif // EXTERNALCONDITIONS_H
