#include "Context.hpp"  

class Ball;

class DebugController  
{  
public:  
   DebugController();  
   ~DebugController();  
   void handleEvent(sf::RenderWindow* window);

private:  

    void selectEntity(int mouseX, int mouseY);
   void moveEntity();  
   void releaseEntity();  

   void shootBall(int mouseX, int mouseY);

   void resetPlayerState();

   std::vector<Entity*> mEntities;  
   Context::State mState;  
   Player* selectedPlayer;  
   Ball* selectedBall;
   bool isDragging = false;  
   sf::RenderWindow* mWindow;  
};
