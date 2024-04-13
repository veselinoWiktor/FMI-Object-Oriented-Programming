#include <iostream>
#include <fstream>
#include <iomanip>

namespace Constants
{
	constexpr unsigned MAX_NAME_LENGTH = 64;
	constexpr unsigned MAX_CONTENT_LENGTH = 256;
	const unsigned MAX_SONGS_IN_PLAYLIST = 30;
	const size_t GENRES_COUNT = 5;

	const unsigned SECONDS_IN_MINUTE = 60;
	const unsigned SECONDS_IN_HOUR = 60 * SECONDS_IN_MINUTE;
}

namespace Utils
{
	unsigned findStrlen(const char* str)
	{
		if (!str)
		{
			return 0;
		}

		int length = 0;
		while (*str)
		{
			str++;
			length++;
		}

		return length;
	}

	char strCompare(const char* firstStr, const char* secondStr)
	{
		if (!firstStr || !secondStr)
		{
			return (char)1;
		}

		while (*firstStr && *secondStr && *firstStr == *secondStr)
		{
			firstStr++;
			secondStr++;
		}

		return *firstStr - *secondStr;
	}

	char makeBitOne(char ch, size_t pos)
	{
		int mask = 1 << pos;
		return (ch | pos);
	}
}

enum class Genres : unsigned char
{
	Pop = 1,
	Rock = 2,
	HipHop = 4,
	Electronic = 8,
	Jazz = 16,
};

class Time
{
private:
	unsigned hours = 0;
	unsigned minutes = 0;
	unsigned seconds = 0;

public:
	Time() : hours(0), minutes(0), seconds(0)
	{

	}
	Time(unsigned hours, unsigned minutes, unsigned seconds)
	{
		setHours(hours);
		setMinutes(minutes);
		setSeconds(seconds);
	}

	unsigned getHours() const
	{
		return hours;
	}
	void setHours(unsigned value)
	{
		if (value > 23)
		{
			hours = 0;
		}
		else
		{
			hours = value;
		}
	}

	unsigned getMinutes() const
	{
		return minutes;
	}
	void setMinutes(unsigned value)
	{
		if (value < 0 || value > 59)
		{
			minutes = 0;
		}
		else
		{
			minutes = value;
		}
	}

	unsigned getSeconds() const
	{
		return seconds;
	}
	void setSeconds(unsigned value)
	{
		if (value < 0 || value > 59)
		{
			seconds = 0;
		}
		else
		{
			seconds = value;
		}
	}

	unsigned getTimeInSeconds() const
	{
		return (hours * Constants::SECONDS_IN_HOUR) + (minutes * Constants::SECONDS_IN_MINUTE) + seconds;
	}

	void serialize(std::ostream& os) const
	{
		if (!os.good())
		{
			return;
		}

		os << std::setw(2) << std::setfill('0') << getHours() << ':'
			<< std::setw(2) << std::setfill('0') << getMinutes() << ':'
			<< std::setw(2) << std::setfill('0') << getSeconds();
	}
};

class Song
{
private:
	char name[Constants::MAX_NAME_LENGTH + 1];
	Time duration;
	unsigned char genre = 0;
	char content[Constants::MAX_CONTENT_LENGTH + 1];
	size_t contentSize = 0;

	void setContentLength(std::ifstream& ifs)
	{
		unsigned currPos = ifs.tellg();
		ifs.seekg(0, std::ios::end);
		unsigned result = ifs.tellg();
		ifs.seekg(currPos);

		contentSize = result;
	}
	void serializeGenre(std::ostream& os) const
	{
		if (!os.good())
		{
			return;
		}

		char currentNum = 0;
		for (size_t i = 0; i < Constants::GENRES_COUNT; i++)
		{
			int mask = 1 << i;
			if ((genre | mask) == genre)
			{
				switch ((Genres)mask)
				{
				case Genres::Rock:
					os << "Rock"; break;
				case Genres::Pop:
					os << "Pop"; break;
				case Genres::HipHop:
					os << "Hip Hop"; break;
				case Genres::Electronic:
					os << "Electronic"; break;
				case Genres::Jazz:
					os << "Jazz"; break;
				default:
					break;
				}
				currentNum |= mask;
			}

			if (currentNum < genre)
			{
				os << '&';
			}
		}
	}

	void loadContent(const char* fileName)
	{
		if (!fileName)
		{
			content[0] = '\0';
			return;
		}

		std::ifstream ifs(fileName, std::ios::binary);
		if (!ifs.is_open())
		{
			content[0] = '\0';
			return;
		}

		setContentLength(ifs);
		if (contentSize >= Constants::MAX_CONTENT_LENGTH)
		{
			content[0] = '\0';
			return;
		}

		ifs.read(content, contentSize);
		content[contentSize] = '\0';
	}

public:
	Song() : name("\0"), duration(), genre(0), content("\0") {}
	Song(const char* songName, unsigned hours, unsigned minutes, unsigned seconds,
		const char* genres, const char* contentFileName)
	{
		setName(songName);
		setDuration(hours, minutes, seconds);
		setGenre(genres);
		loadContent(contentFileName);
	}
	Song(const char* songName, const Time& duration,
		const char* genres, const char* contentFileName)
	{
		setName(songName);
		setDuration(duration);
		setGenre(genres);
		loadContent(contentFileName);
	}

	const char* getName() const
	{
		return name;
	}
	void setName(const char* value)
	{
		unsigned valueLength = Utils::findStrlen(value);
		if (!value || valueLength >= Constants::MAX_NAME_LENGTH)
		{
			name[0] = '\0';
			return;
		}

		int nameIdx = 0;
		while (*value)
		{
			name[nameIdx] = *value;
			nameIdx++;
			value++;
		}

		name[nameIdx] = '\0';
	}

	unsigned char getGenre() const
	{
		return genre;
	}
	void setGenre(const char* value)
	{
		if (!value)
		{
			genre = 0;
			return;
		}

		while (*value)
		{
			switch (*value)
			{
			case 'r': genre |= (int)Genres::Rock; break;
			case 'p': genre |= (int)Genres::Pop; break;
			case 'h': genre |= (int)Genres::HipHop; break;
			case 'e': genre |= (int)Genres::Electronic; break;
			case 'j': genre |= (int)Genres::Jazz; break;
			default:
				break;
			}

			value++;
		}
	}

	const char* getContent() const
	{
		return content;
	}
	void setContent(const char* value)
	{
		if (!value)
		{
			return;
		}

		size_t contentSize = Utils::findStrlen(value);
		if (contentSize > Constants::MAX_CONTENT_LENGTH)
		{
			return;
		}

		char* put = content;
		while (*value)
		{
			*put = *value;
			put++;
			value++;
		}
		*put = '\0';
	}

	unsigned getDurationInSeconds() const
	{
		return duration.getTimeInSeconds();
	}
	void setDuration(unsigned hours, unsigned minutes, unsigned seconds)
	{
		duration.setHours(hours);
		duration.setMinutes(minutes);
		duration.setSeconds(seconds);
	}
	void setDuration(const Time& value)
	{
		duration = value;
	}

	size_t getContentSize() const
	{
		return contentSize;
	}

	void modifySong(unsigned modificationStep)
	{
		if (contentSize == 0 || modificationStep < 1)
		{
			return;
		}

		int currentCharIdx = contentSize - 1;
		int currentBitIndex = modificationStep - 1;
		for (size_t i = 0; i <= (contentSize * 8) - modificationStep; i += modificationStep)
		{
			content[currentCharIdx] = Utils::makeBitOne(content[currentCharIdx], currentBitIndex);
			currentBitIndex += modificationStep;

			if (currentBitIndex > 7)
			{
				currentBitIndex -= 8;
				currentCharIdx--;
			}
		}
	}

	void mergeWithSong(const Song& song)
	{
		size_t smallerContentLength = (contentSize < song.contentSize) ? contentSize : song.contentSize;

		for (size_t i = 0; i < smallerContentLength; i++)
		{
			content[i] ^= song.content[i];
		}
	}

	void serialize(std::ostream& os) const
	{
		if (!os.good())
		{
			return;
		}

		os << name << ", ";
		duration.serialize(os);
		os << ", ";
		serializeGenre(os);
	}
};

bool songNameComparer(const Song& firstSong, const Song& secondSong)
{
	return (Utils::strCompare(firstSong.getName(), secondSong.getName()) < 0);
}

bool songDurationComparer(const Song& firstSong, const Song& secondSong)
{
	return firstSong.getDurationInSeconds() < secondSong.getDurationInSeconds();
}

class Playlist
{
private:
	Song songs[Constants::MAX_SONGS_IN_PLAYLIST];
	size_t songsCount = 0;

	void sort(bool (*comparer)(const Song&, const Song&))
	{
		for (size_t i = 0; i < songsCount - 1; i++)
		{
			int minIdx = i;

			for (size_t j = i + 1; j < songsCount; j++)
			{
				if ((*comparer)(songs[j], songs[minIdx]))
				{
					minIdx = j;
				}
			}

			if (minIdx != i)
			{
				std::swap(songs[minIdx], songs[i]);
			}
		}
	}

	void setSongsCount(size_t value)
	{
		if (value < 0 || value > Constants::MAX_SONGS_IN_PLAYLIST)
		{
			songsCount = 0;
		}

		songsCount = value;
	}
	void setSongs(Song* value)
	{
		if (!value)
		{
			return;
		}

		for (size_t i = 0; i < songsCount; i++)
		{
			songs[i] = value[i];
		}
	}

public:
	Playlist() = default;
	Playlist(Song* songs, size_t songsCount)
	{
		setSongsCount(songsCount);
		setSongs(songs);
	}

	void add(const char* songName, unsigned hours, unsigned minutes, unsigned seconds,
		const char* genres, const char* contentFileName)
	{
		if (songsCount >= Constants::MAX_SONGS_IN_PLAYLIST)
		{
			return;
		}

		Song s(songName, hours, minutes, seconds, genres, contentFileName);
		songs[songsCount] = s;

		songsCount++;
	}

	void add(const char* songName, const Time& duration,
		const char* genres, const char* contentFileName)
	{
		if (songsCount >= Constants::MAX_SONGS_IN_PLAYLIST)
		{
			return;
		}

		Song s(songName, duration, genres, contentFileName);
		songs[songsCount++] = s;
	}

	void print() const
	{
		for (size_t i = 0; i < songsCount; i++)
		{
			songs[i].serialize(std::cout);
			std::cout << std::endl;
		}
	}

	const Song& findByName(const char* name) const
	{
		if (!name)
		{
			return {};
		}

		for (size_t i = 0; i < this->songsCount; i++)
		{
			if (!Utils::strCompare(songs[i].getName(), name))
			{
				return songs[i];
			}
		}
	}

	Playlist findByGenre(char genre) const
	{
		Genres currGenre;

		switch (genre)
		{
		case 'p': currGenre = Genres::Pop; break;
		case 'r': currGenre = Genres::Rock; break;
		case 'h': currGenre = Genres::HipHop; break;
		case 'e': currGenre = Genres::Electronic; break;
		case 'j': currGenre = Genres::Jazz; break;
		default:
			return {};
			break;
		}


		Playlist result;
		unsigned char currSongGenre = 0;
		for (size_t i = 0; i < songsCount; i++)
		{
			currSongGenre = songs[i].getGenre();
			if ((currSongGenre | (int)currGenre) == currSongGenre)
			{
				result.songs[result.songsCount++] = songs[i];
			}
		}

		return result;
	}

	void sortByDuration()
	{
		sort(songDurationComparer);
	}

	void sortByName()
	{
		sort(songNameComparer);
	}

	void modifySong(const char* songName, unsigned modificationStep)
	{
		if (!songName)
		{
			return;
		}

		for (size_t i = 0; i < songsCount; i++)
		{
			if (!Utils::strCompare(songs[i].getName(), songName))
			{
				songs[i].modifySong(modificationStep);
			}
		}
	}

	void mix(const char* firstSong, const char* secondSong)
	{
		if (!firstSong || !secondSong)
		{
			return;
		}

		Song* firstSongPtr = nullptr;
		for (size_t i = 0; i < this->songsCount; i++)
		{
			if (!Utils::strCompare(songs[i].getName(), firstSong))
			{
				firstSongPtr = &songs[i];
			}
		}

		if (!firstSongPtr)
		{
			return;
		}

		for (size_t i = 0; i < this->songsCount; i++)
		{
			if (!Utils::strCompare(songs[i].getName(), secondSong))
			{
				(*firstSongPtr).mergeWithSong(songs[i]);
				return;
			}
		}
	}

	void save(const char* songName, const char* fileName) const
	{
		if (!songName || !fileName)
		{
			return;
		}

		Song song;
		for (size_t i = 0; i < this->songsCount; i++)
		{
			if (!Utils::strCompare(songs[i].getName(), songName))
			{
				song = songs[i];
			}
		}

		std::ofstream ofs(fileName, std::ios::binary);
		if (!ofs.is_open())
		{
			return;
		}

		ofs.write((const char*)song.getContent(), song.getContentSize());
		ofs.close();
	}
};