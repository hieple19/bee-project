#include "ExternalConditions.h"

/* constructor for ExternalConditions */
ExternalConditions::ExternalConditions()
{

}

ExternalConditions::ExternalConditions(int temp, Season mySeason, Weather myWeather){
    this->temp = temp;
    this->mySeason = mySeason;
    this->myWeather = myWeather;
}

/**
 * @brief ExternalConditions::setTemp sets temperature
 * @param t
 */
void ExternalConditions::setTemp(int t) {
    temp = t;
}

/**
 * @brief ExternalConditions::getTemp gets Run's temperature
 * @return
 */
int ExternalConditions::getTemp() {
    return temp;
}

/**
 * @brief ExternalConditions::setSeason sets season
 * @param s
 */
void ExternalConditions::setSeason(Season s) {
    mySeason = s;
}

void ExternalConditions::setSeason(int index) {
    if( index==0) mySeason=spring;
    if( index==1) mySeason=summer;
    if( index==2) mySeason=autumn;
    if( index==3) mySeason=winter;
}

/**
 * @brief ExternalConditions::getSeason
 * @return current season
 */
ExternalConditions::Season ExternalConditions::getSeason() {
    return mySeason;
}

/**
 * @brief ExternalConditions::setWeather sets current weather
 * @param w
 */
void ExternalConditions::setWeather(Weather w) {
    myWeather = w;
}

/* setter for enum weather myWeather */
void ExternalConditions::setWeather(int index) {
    if( index==0)myWeather=rainy;
    if( index==1)myWeather=sunny;
    if( index==2)myWeather=windy;
    if( index==3)myWeather= snowy;
}

/**
 * @brief ExternalConditions::getWeather
 * @return current weather
 */
ExternalConditions::Weather ExternalConditions::getWeather(){
    return myWeather;
}
