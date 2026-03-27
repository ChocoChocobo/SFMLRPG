#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// ---------------Структура книги---------------
struct Book
{
	sf::String title;
	sf::String author;
	sf::String year;
};
// ---------------Класс поля ввода---------------
class InputField // shape, событие нажатия по фигуре, отрисовка букв, положение, размер, get-функция по возвращению значения объекта, подпись к полю ввода
{
public:
	// Удобно разграничить функционал конструктора следующим образом: инициализацию производить в значениях по умолчанию, а настраивать объекты в теле конструктора
	//			шрифт,				 подпись к полю ввода,		позиция в окне,		размер
	InputField(const sf::Font& font, sf::String caption, sf::Vector2f position, sf::Vector2f size) : captionText(font, caption, 18), valueText(font, "", 18) 
	{
		// fieldShape
		fieldShape.setPosition(position);
		fieldShape.setSize(size);
		fieldShape.setFillColor(sf::Color(EGGSHELL_COLOR));
		fieldShape.setOutlineColor(sf::Color(ROSY_GRANITE_COLOR));
		fieldShape.setOutlineThickness(3.0f);
		// caption
		captionText.setFillColor(sf::Color(CHARCOAL_BROWN_COLOR));
		captionText.setPosition({ position.x, position.y - 25.0f });
		// valueText
		captionText.setFillColor(sf::Color(CHARCOAL_BROWN_COLOR));
		captionText.setPosition({ position.x + 10.0f, position.y + 5.0f});
	}

	// Функция для проверки попадания в окно
	// Если точка, передаваемая в качестве параметра лежит в границах окна, возвращаем true
	bool Contains(sf::Vector2f point) const
	{
		const sf::Vector2f position = fieldShape.getPosition();
		const sf::Vector2f size = fieldShape.getSize();

		return point.x >= position.x && point.x <= position.x + size.x && point.y >= position.y && point.y <= position.y + size.y;
	}

	// Функция изменения цвета фигуры при активном или неактивном режиме 
	void SetActive(bool isActive)
	{
		this->isActive = isActive;
		fieldShape.setOutlineColor(isActive ? sf::Color(163, 149, 148, 255) : sf::Color(163, 149, 148, 100));
	}

	// Get-функция по возвращению строкового значения поля ввода
	const sf::String& GetValue() const
	{
		return valueString;
	}

	// Вспомогательная функция очистки текста в поле ввода
	void ClearInputValue()
	{
		valueString.clear();
	}

	// Функция-обработчик события введения символа пользователем, принимающая символ юникода
	void HandleTextEntered(char unicode)
	{
		if (!isActive) return; // Если пользователь не в активном окне ввода, то завершаем работу функции
		// Ситуации стирания
		if (unicode == 8) // Backspace
		{
			if (!valueString.isEmpty()) valueString.erase(valueString.getSize() - 1);
		}
		else if (unicode >= 32) // Ситуация добавления символов
		{
			if (valueString.getSize() < maxLength) valueString += sf::String(unicode);
		}
	}

	// Функция отрисовки, принимающая ссылку на графическое окно
	void Draw(sf::RenderWindow& renderWindow)
	{
		renderWindow.draw(captionText);
		renderWindow.draw(fieldShape);
		renderWindow.draw(valueText);
	}

private:
	// Отрисовываемые элементы
	sf::RectangleShape fieldShape;
	sf::Text captionText; // подпись
	sf::Text valueText;
	// Прочие элементы
	sf::String valueString;
	bool isActive = false;
	unsigned int maxLength = 32;

	const sf::Color ROSY_GRANITE_COLOR = { 163, 149, 148 };
	const sf::Color EGGSHELL_COLOR = { 237, 235, 215 };
	const sf::Color CHARCOAL_BROWN_COLOR = { 66, 62, 55 };
	const sf::Color SUNFLOWER_GOLD_COLOR = { 227, 178, 60 };
};
// ---------------Класс кнопки---------------

int main()
{
	// ---------------Инициализация основного окна---------------
	sf::Font font("Comic Sans MS.ttf");	

	// ---------------Инициализация основного окна---------------
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;
	sf::RenderWindow mainWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Home Library");

	// ---------------Создание объектов---------------
													// Размер по x - количество букв * 10
													// Размер по y - размер символа * 2
	InputField bookTitle(font, "Название книги", {}, { 320.0f, 36.f });

	// ---------------Обработка событий---------------
	while (mainWindow.isOpen())
	{
		// Обработка события по взаимодействию с главным окном
		while (const std::optional event = mainWindow.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				mainWindow.close();
			}
			// дополнительная обработка события нахождения мыши в пределах окна и нажатия. getIF - вспомогательная функция, определяющая наличие события с дополнительным уссловием
			else if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mouseEvent->button == sf::Mouse::Button::Left)
				{
					sf::Vector2f mousePoint = { float(mouseEvent->position.x), float(mouseEvent->position.y) };

					if (bookTitle.Contains(mousePoint))
					{
						bookTitle.SetActive(true);
					}
					else
					{
						bookTitle.SetActive(false);
					}
				}
			}
			// Обработка события печатания
			else if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
			{
				bookTitle.HandleTextEntered(textEntered->unicode);
			}
		}
	}
	// ---------------Очистка элементов---------------
	mainWindow.clear(sf::Color(227, 178, 60));

	// ---------------Отрисовка элементов---------------
	bookTitle.Draw(mainWindow);
}