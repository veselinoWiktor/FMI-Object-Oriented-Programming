#pragma once
class StringPool
{
private:
	struct StringNode {
		char* data = nullptr;
		unsigned refCount = 0;

		StringNode();
		StringNode(const StringNode& stringNode) = delete;
		StringNode& operator=(const StringNode& stringNode) = default;
		~StringNode() = default;

		void allocateData(const char* str);
	};

	void resize(size_t newCapacity);

	int lowerBound(const char* str, bool& found) const;
	const char* insert(const char* str, size_t index);

	void removeString(size_t index);

	StringNode* nodes;
	size_t count = 0;
	size_t capacity = 0;

public:
	StringPool();
	StringPool(const StringPool& other) = delete;
	StringPool& operator=(const StringPool& other) = delete;
	~StringPool();

	const char* getString(const char* str);
	void releaseString(const char* str);
};

