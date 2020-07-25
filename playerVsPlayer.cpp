#include "playerVsPlayer.h"
#include "battleUserPlayer.h"




#include "ship.h"
#include <iostream>




// Constructor
PlayerVsPlayer::PlayerVsPlayer()
{
    
}

// Return bool whether game is finished
bool PlayerVsPlayer::isGameOver()
{
    return (player1.isAllShipsDestroyed() || player2.isAllShipsDestroyed());
}

/* Method to update the Grids after a location has been choosen for a player's turn */
void PlayerVsPlayer::updateGridsAndShips(const std::pair<int,int> &gridLocationToUpdate, const Player& player, const Player& enemyPlayer)
{
    // Updating the Player's status grid for the shots they have fired
    bool shipWasHit = false;
    for(Ship enemyShip : enemyPlayer.getShips()) // For each Ship belonging to the enemy player
    {
        if(enemyShip.isLocationOfShip(gridLocationToUpdate)) // If the player hit a ship
        {            
            enemyShip.addToLocationsDestroyed(gridLocationToUpdate); // Add to locaitons destroyed on the ship instance
            shipWasHit = true;
        }
    }
   
    int row = std::get<1>(gridLocationToUpdate);
    int col = std::get<0>(gridLocationToUpdate);
    
    if(shipWasHit)
        player.getEnemyGrid().getGrid()[row][col] = 'H';
    else
        player.getEnemyGrid().getGrid()[row][col] = 'M';
    
    // Updating the Enemy's grid for the shots they have recieved
    if(shipWasHit)
        enemyPlayer.getOwnGrid().getGrid()[row][col] = 'H';
    else
        enemyPlayer.getOwnGrid().getGrid()[row][col] = 'M';
}

void displayGrid(const Grid &gridToDisplay)
{
    std::cout << "[   ] | [ 0 ] [ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ] [ 6 ] [ 7 ] [ 8 ] [ 9 ]" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    for(int row=0; row<10; row++)
    {
        std::cout << "[ " << row << " ] |";
        
        for(int col=0; col<10; col++)
        {
            std::cout << " [ " << gridToDisplay.getGrid()[row][col] << " ]";
        }
        std::cout << std::endl;
    }
}

/* Method which controls turns */
void PlayerVsPlayer::play()
{
    std::pair<int,int> shotTakenP1 = player1.takeTurn();
    updateGridsAndShips(shotTakenP1, player1, player2);
    
    if(isGameOver())
        return;
    
    std::pair<int,int> shotTakenP2 = player1.takeTurn();
    updateGridsAndShips(shotTakenP2, player2, player1);
}

/* Method which controls turns */
void PlayerVsPlayer::placeShips()
{
    player1.addShip(player1.placeShip(5));
    std::cout << "Your current grid: " << std::endl;
    displayGrid(player1.getOwnGrid());
    
    
    player1.addShip(player1.placeShip(4));
    std::cout << "Your current grid: " << std::endl;
    displayGrid(player1.getOwnGrid());
    
    
    player1.addShip(player1.placeShip(3)); 
    std::cout << "Your current grid: " << std::endl;
    displayGrid(player1.getOwnGrid());
    
    player1.addShip(player1.placeShip(3));
        std::cout << "Your current grid: " << std::endl;
    displayGrid(player1.getOwnGrid());
    
    player1.addShip(player1.placeShip(2));
    std::cout << "Your current grid: " << std::endl;
    displayGrid(player1.getOwnGrid());
    
    /*player2.addShip(player2.placeShip(5));
    player2.addShip(player2.placeShip(4));
    player2.addShip(player2.placeShip(3));
    player2.addShip(player2.placeShip(3));
    player2.addShip(player2.placeShip(2));*/
}