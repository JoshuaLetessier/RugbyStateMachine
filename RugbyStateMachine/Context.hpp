#pragma once
#include <ostream>

namespace Context
{
enum class State 
{
    // Ajoutez vos états ici
    IDLE,
    DEFEND,
	ATTACK,
	BALLKEEPER,
    DEBUG
};

enum class Team
{
	RED,
	GREEN
};

}; // namespace Context