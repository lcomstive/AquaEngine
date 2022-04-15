#pragma once
#include <string>
#include <BGFXEntry/entry.h>

class BaseGame : public entry::AppI
{
	unsigned int
		m_Width = 0,
		m_Height = 0,
		m_Reset = 0,
		m_Debug = 0;

	entry::MouseState m_MouseState = {};

	std::string m_LogDirectory = "Logs/";

	void InitLogger();

public:
	BaseGame();

	void init(int argc, const char* const* argv, unsigned int width, unsigned int height) override;
	virtual int shutdown() override;

	bool update() override;
};