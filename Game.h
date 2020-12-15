#include <SFML/Graphics.hpp>

const int SIZE = 4;						// ������ �������� ���� � �������
const int ARRAY_SIZE = SIZE * SIZE;		// ������ �������
const int FIELD_SIZE = 500;				// ������ �������� ���� � ��������
const int CELL_SIZE = 120;				// ������ ������ � ��������

enum class Direction { Left, Right, Up, Down };
class Game : public sf::Drawable, public sf::Transformable {
protected:
	int elements[ARRAY_SIZE];
	int empty_index;
	bool solved;
	sf::Font font;

public:
	Game();
	void Init();
	bool Check();
	void Move(Direction direction);
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

