#pragma once
class SetExpression
{
public:
	SetExpression() = default;
	SetExpression(const SetExpression& other) = delete;
	SetExpression& operator=(const SetExpression& other) = delete;
	virtual ~SetExpression() = default;

	struct Element
	{
		bool sets[26] = { false };

		void set(char ch, bool value)
		{
			if ('A' <= ch && ch <= 'Z')
			{
				sets[ch - 'A'] = value;
			}
		}

		bool get(char ch) const
		{
			if ('A' <= ch && ch <= 'Z')
			{
				return sets[ch - 'A'];
			}
		}
	};

	virtual bool isElementIn(const Element& element) const = 0;
	virtual SetExpression* clone() const = 0;
};

