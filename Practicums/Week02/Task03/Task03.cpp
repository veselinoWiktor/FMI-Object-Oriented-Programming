#include <iostream>
#include <fstream>

constexpr unsigned MAX_PAIRS_IN_RELATION = 25;
const char RELATION_FILENAME[] = "relation.txt";

struct Pair {
    unsigned int firstNum;
    unsigned int secondNum;
};

struct Relation {
    Pair pairs[MAX_PAIRS_IN_RELATION];
    size_t size = 0;
};

Pair createPair()
{
    return Pair{};
}

Pair initPair(unsigned firstNum, unsigned secondNum)
{
    Pair result = createPair();
    result.firstNum = firstNum;
    result.secondNum = secondNum;
    return result;
}

void addPairToRelation(Relation& relation, const Pair& pair)
{
    if (relation.size == MAX_PAIRS_IN_RELATION)
    {
        return;
    }

    relation.pairs[relation.size++] = pair;
}

void writePairToFile(std::ofstream& ofs, const Pair& pair)
{
    ofs << pair.firstNum << " " << pair.secondNum << std::endl;
}

void readPairFromFile(std::ifstream& ifs, Pair& pair)
{
    unsigned firstNum, secondNum;
    ifs >> firstNum >> secondNum;
    pair.firstNum = firstNum;
    pair.secondNum = secondNum;
}

void writeRelationToFile(const Relation& relation)
{
    std::ofstream ofs(RELATION_FILENAME);
    if (!ofs.is_open())
    {
        return;
    }

    ofs << relation.size << std::endl;
    for (size_t i = 0; i < relation.size; i++)
    {
        writePairToFile(ofs, relation.pairs[i]);
    }
    ofs.close();
}

void readRelationFromFile(Relation& relation)
{
    std::ifstream ifs(RELATION_FILENAME);
    if (!ifs.is_open())
    {
        return;
    }

    ifs >> relation.size;
    for (size_t i = 0; i < relation.size; i++)
    {
        readPairFromFile(ifs, relation.pairs[i]);
    }
    ifs.close();
}

int main()
{
    Relation relation;

    Pair pair = initPair(0, 1);
    addPairToRelation(relation, pair);
    pair = initPair(0, 2);
    addPairToRelation(relation, pair);

    writeRelationToFile(relation);

    Relation readRelation;
    readRelationFromFile(readRelation);
    ;
    std::cout << "viktor";
}
