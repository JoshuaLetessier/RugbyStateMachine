#pragma once

// Include SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Include standard librariess
#include <windows.h>

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <optional>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define GREEN_TEAM_GOAL static_cast<float>(WINDOW_WIDTH * 0.1f)
#define RED_TEAM_GOAL static_cast<float>(WINDOW_WIDTH * 0.9f)
#define DISTANCE_TO_PASS 80.f

#define GET_CURRENT_TIME std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
// Include all the headers of the classes you want to use in your project
#include "Context.hpp"
#include "Utils.hpp"
#include "Entity.hpp"
#include "StateMachine/Action.hpp"
#include "StateMachine/Condition.hpp"
#include "ColliderManager.hpp"
#include "GameManager.hpp"

#include "GameManager.hpp"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif
