#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

/*
ID: bmpringle
LANG: C++
TASK: friday
*/

bool isLeapYear(int year) {
    //year must be divisible by 4 and either not divisble by 100 or divisible by 400
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return true;
    }
    return false;
}

struct Month {
    Month(std::string name, int days) : name(name), days(days) {

    }

    std::string name;
    int days;
};

static const Month January = Month("January", 31);
static const Month February = Month("February", 28);
static const Month FebruaryLeap = Month("February", 29);
static const Month March = Month("March", 31);
static const Month April = Month("April", 30);
static const Month May = Month("May", 31);
static const Month June = Month("June", 30);
static const Month July = Month("July", 31);
static const Month August = Month("August", 31);
static const Month September = Month("September", 30);
static const Month October = Month("October", 31);
static const Month November = Month("November", 30);
static const Month December = Month("December", 31);

int main() {
    std::ifstream input ("friday.in");
    std::ofstream output ("friday.out");

    std::string buffer;
    std::getline(input, buffer);

    int YEARS = std::stoi(buffer);

    int mondays = 0;
    int tuesdays = 0;
    int wednesdays = 0;
    int thursdays = 0;
    int fridays = 0;
    int saturdays = 0;
    int sundays = 0;

    const Month months[12] = {January, February, March, April, May, June, July, August, September, October, November, December};

    int dayOfTheWeek = 0; //0-6 --> Monday-Sunday

    for(int i = 0; i < YEARS; ++i) {
        int year = 1900 + i;
        const Month& secondMonth = (isLeapYear(year)) ? FebruaryLeap : February;

        for(int month = 0; month < 12; ++month) {
            const Month& currentMonth = (month != 1) ? months[month] : secondMonth;

            switch((dayOfTheWeek + 13) % 7) {
                case 0:
                    ++mondays;
                    break;
                case 1:
                    ++tuesdays;
                    break;
                case 2:
                    ++wednesdays;
                    break;
                case 3:
                    ++thursdays;
                    break;
                case 4:
                    ++fridays;
                    break;
                case 5:
                    ++saturdays;
                    break;
                case 6:
                    ++sundays;
                    break;
                default:
                    return 1;
            }

            dayOfTheWeek += currentMonth.days;
            dayOfTheWeek %= 7;
        }
    }

    std::string out = std::to_string(sundays) + " " + std::to_string(mondays) + " " + std::to_string(tuesdays) + " " + std::to_string(wednesdays) + " " + std::to_string(thursdays) + " " + std::to_string(fridays) + " " + std::to_string(saturdays) + "\n";
    output.write(out.data(), out.size());

    return 0;
}