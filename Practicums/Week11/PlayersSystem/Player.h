#pragma once

enum class StarsCount {
	One = 0,
	Two = 256,
	Three = 512,
	Four = 1024,
	Five = 2048
};

class Player
{
private:
	int id;
	int points;
	StarsCount starsCount; 
};

