#include <iostream>

class Time
{
private:
    unsigned hours = 0;
    unsigned minutes = 0;
    unsigned seconds = 0;

    unsigned getSecondsFromMidnight() const
    {
        return hours * 3600 + hours * 60 + seconds;
    }
    void setTimeFromSeconds(unsigned secondsFromMidnight)
    {
        if (secondsFromMidnight >= 24 * 3600)
        {
            hours = 0;
            minutes = 0;
            seconds = 0;
            return;
        }

        hours = secondsFromMidnight / 3600;
        secondsFromMidnight %= 3600;
        minutes = secondsFromMidnight / 60;
        seconds = secondsFromMidnight % 60;
    }
public:
    Time() = default;
    Time(unsigned hours, unsigned minutes, unsigned seconds)
    {
        setHours(hours);
        setMinutes(minutes);
        setSeconds(seconds);
    }
    Time(unsigned secondsFromMidnight)
    {
        setTimeFromSeconds(secondsFromMidnight);
    }

    void setHours(unsigned hVal)
    {
        if (hVal <= 23)
        {
            hours = hVal;
        }
        else
        {
            hours = 0;
        }
    }
    unsigned getHours() const
    {
        return hours;
    }

    void setMinutes(unsigned mVal)
    {
        if (mVal <= 59)
        {
            minutes = mVal;
        }
        else
        {
            minutes = 0;
        }
    }
    unsigned getMinutes() const
    {
        return minutes;
    }

    void setSeconds(unsigned sVal)
    {
        if (sVal <= 59)
        {
            seconds = sVal;
        }
        else
        {
            seconds = 0;
        }
    }
    unsigned getSeconds() const
    {
        return seconds;
    }

    void increment()
    {
        unsigned secondsFromMidnight = getSecondsFromMidnight();
        secondsFromMidnight++;
        setTimeFromSeconds(secondsFromMidnight);
    }
    void print() const
    {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }
    int compare(const Time& other) const
    {
        unsigned thisSecondsFromMidnight = getSecondsFromMidnight();
        unsigned otherSecondsFromMidnight = other.getSecondsFromMidnight();

        return thisSecondsFromMidnight - otherSecondsFromMidnight;
    }
    Time getDiff(const Time& other)
    {
        unsigned diffSeconds = fabs(getSecondsFromMidnight() - other.getSecondsFromMidnight());
        return Time(diffSeconds);
    }

    bool isPartyTime() const
    {
        Time begin(23, 0, 0);
        Time end(6, 0, 0);

        return compare(begin) > 0 || compare(end) < 0;
    }

    bool isDinnerTime() const
    {
        Time begin(20, 30, 0);
        Time end(22, 0, 0);

        return compare(begin) > 0 || compare(end) < 0;
    }

};

int main()
{
    Time t(0, 0, 0);
    std::cout << t.isPartyTime();
    t.setHours(45);
    std::cout << t.getHours() << std::endl;
}