#pragma once

class Time {
private:
	unsigned hours = 0;
	unsigned minutes = 0;
	unsigned seconds = 0;

	unsigned getSecondsFromMidnight() const;
	void setTimeFromSeconds(unsigned seconds);

public:
	Time() = default;
	Time(unsigned hours, unsigned minutes, unsigned seconds);
	explicit Time(unsigned secondsFromMidnight);

	void increment();

	void setHours(unsigned hours);
	void setMinutes(unsigned minutes);
	void setSeconds(unsigned seconds);

	unsigned getHours() const;
	unsigned getMinutes() const;
	unsigned getSeconds() const;

	int compare(const Time& other) const;
	bool isPartyTime() const;
	bool isDinnerTime() const;
	Time getDiff(const Time& other) const;
	void print() const;
};