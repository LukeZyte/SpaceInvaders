#include "NicknameScreen.h"

NicknameScreen::NicknameScreen(sf::RenderWindow& _window)
	: window(_window)
{
	textFontColor = sf::Color::White;
	
	if (!localFont.loadFromFile(PIXELOIDSANS_FILEPATH))
		std::cout << "Could not load a font file!\n";

	// Title Init
	mainText.setFont(localFont);
	mainText.setString("Enter your nickname (3 - 9 characters)");
	mainText.setFillColor(textFontColor);
	mainText.setCharacterSize(32);
	mainText.setStyle(sf::Text::Regular);
	mainText.setPosition((WINDOW_WIDTH / 2) - (mainText.getGlobalBounds().width / 2), 300.f);

	// InputText Init
	inputNicknameText.setFont(localFont);
	inputNicknameText.setFillColor(textFontColor);
	inputNicknameText.setCharacterSize(32);
	inputNicknameText.setStyle(sf::Text::Bold);
	inputNicknameText.setPosition((WINDOW_WIDTH / 2) - (inputNicknameText.getGlobalBounds().width / 2), 400.f);

	// enterText Init
	enterText.setFont(localFont);
	enterText.setString("[ Enter ] Submit >>");
	enterText.setFillColor(sf::Color::White);
	enterText.setCharacterSize(24);
	enterText.setStyle(sf::Text::Bold);
	enterText.setPosition((WINDOW_WIDTH - 100.f - enterText.getGlobalBounds().width), WINDOW_HEIGHT - 250.f);

	// quitText Init
	quitText.setFont(localFont);
	quitText.setString("<< [ Esc ] Back");
	quitText.setFillColor(sf::Color::White);
	quitText.setCharacterSize(24);
	quitText.setStyle(sf::Text::Bold);
	quitText.setPosition(100.f, WINDOW_HEIGHT - 250.f);
}

NicknameScreen::~NicknameScreen()
{

}

void NicknameScreen::draw()
{
	window.draw(mainText);
	inputNicknameText.setPosition((WINDOW_WIDTH / 2) - (inputNicknameText.getGlobalBounds().width / 2), 400.f);
	window.draw(inputNicknameText);
	window.draw(enterText);
	window.draw(quitText);
}

void NicknameScreen::updateNickname()
{
	if (inputNickname.getSize() <= 0)
	{
		return;
	}
	inputNickname.erase(inputNickname.getSize() - 1);
	inputNicknameText.setString(inputNickname);
}

void NicknameScreen::updateNickname(sf::Event event)
{
	char letter = (char)event.text.unicode;
	char upperLetter = std::toupper(letter);
	std::string upperLetterStr(1, upperLetter);

	std::regex reg(R"([A-Z])");
	if (!std::regex_match(upperLetterStr, reg))
	{
		return;
	}
	if (inputNickname.getSize() > 9)
	{
		return;
	}

	inputNickname += upperLetterStr;
	inputNicknameText.setString(inputNickname);
}

void NicknameScreen::resetNickname()
{
	inputNickname.clear();
	inputNicknameText.setString("");
}