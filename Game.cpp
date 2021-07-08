//Title: Game.cpp
//Author: Amarjot Gill
//Date: 2/14/2021
//Description: This is part of the No Man's Alchemy Project in CMSC 202 @ UMBC

#include "Game.h"

Game::Game(){
    LoadMaterials();
    string shipName;
    cout << "What is the name of your Ship?" << endl;
    // getline so ship name can be spaced and multiple words
    getline(cin,shipName);
    // creates the players ship
    m_myShip.SetName(shipName);
    // copies all the loaded materials into the player's ship
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        m_myShip.AddMaterial(m_materials[i]);
    } 
}

void Game::LoadMaterials(){
    string name;
    // keep tracks of position
    int currentPosition = 0;
    ifstream theFile(PROJ2_DATA);
    if(theFile.is_open()){
        while(currentPosition != PROJ2_SIZE){
            // will add a new word and then increase the index
            getline(theFile,name,',');
            m_materials[currentPosition].m_name = name;
            // ',' will allow to read , on line
            getline(theFile,name,',');
            m_materials[currentPosition].m_type = name;
            
            getline(theFile,name,',');
            m_materials[currentPosition].m_material1 = name;

            getline(theFile,name);
            m_materials[currentPosition].m_material2 = name;

            m_materials[currentPosition].m_quantity = 0;
            currentPosition++;
        }
    }
    cout << currentPosition << " Materials loaded" << endl;
    theFile.close();
}

void Game::StartGame(){
    int currentOption;
    char rank;
    do{ 
        currentOption = MainMenu();
    if (currentOption == ONE){
        DisplayMaterials();
    }else if(currentOption == TWO){
        SearchMaterials();
    }else if(currentOption == THREE){
        CombineMaterials();
    }else if (currentOption == FOUR){
        CalcScore();
    }
        // gets the ship get rank after every loop too check if win condition has been met
        rank = m_myShip.GetRank();
    } while (currentOption != FIVE && rank != S);
    // once loops break checks if players rank is S and displays win message if it is
    if (rank == S)
    {
        cout << "Congrats you have won!" << endl;
    }else{
        cout << "Thanks for playing No Man's Alchemy" << endl;
    }
}

int Game::MainMenu(){
    int playerOption;
    do
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Display your Ship's Materials" << endl;
        cout << "2. Search for Raw Materials" << endl;
        cout << "3. Attempt to Merge Materials" << endl;
        cout << "4. See Score" << endl;
        cout << "5. Quit" << endl;
        cin >> playerOption;
    // make sure user only enters a 1 - 5 as an option
    } while (playerOption <= 0 || playerOption > FIVE);

    return playerOption;
}

void Game::DisplayMaterials(){
    Material PlayerMaterial;
    for (int i = 0; i < PROJ2_SIZE; i++){  
        PlayerMaterial = m_myShip.GetMaterial(i);
        // i + 1 because i starts at 0
        cout << i + ONE << ". " << m_materials[i].m_name << " " << PlayerMaterial.m_quantity << endl;
    }
}

void Game::SearchMaterials(){
    Material searchMat;
    do
    {   // randomly searches the list only the size of the material list
       int randomIndex = rand() % PROJ2_SIZE;

       // assigns search mat to it
        searchMat = m_materials[randomIndex];
        // will keep running until item is a raw type
    } while (searchMat.m_type != RAW);

    cout << searchMat.m_name << " Found!" << endl;
    m_myShip.IncrementQuantity(searchMat);
}

void Game::RequestMaterial(int &itemNumber){
    do
    {
        cout << "Which materials would you like to merge?" << endl;
        cout << "To list known materials enter -1" << endl;
        cin >> itemNumber;
        if(itemNumber == NEGATIVE_ONE){
            DisplayMaterials();
        }
    // loop will go until user enters a number 1 - 62;
    } while (itemNumber <= NEGATIVE_ONE || itemNumber == 0 || itemNumber > PROJ2_SIZE);
    // decreases itemnNumber because array starts at index 0
    itemNumber--;
}

void Game::CombineMaterials(){
    int itemNumber;
    int itemNumber2;
    int recipeNumber;
    bool enoughMats;
    bool decreasedMats;
    int matResults;
    // request itemNumver for both numvers
    RequestMaterial(itemNumber);
    RequestMaterial(itemNumber2);
    recipeNumber = SearchRecipes(m_materials[itemNumber].m_name, m_materials[itemNumber2].m_name);

    // SearchRecipes will return a -1 if they can not be combind
    if(recipeNumber == NEGATIVE_ONE){
        cout << "Items can not be combind together" << endl;
    }else{
        // checks to make sure player ships has enough of both material
        enoughMats = m_myShip.CheckQuantity(m_materials[itemNumber], m_materials[itemNumber2]);
        if(enoughMats){
            // decreases both materials because they have been added
            decreasedMats = m_myShip.DecrementQuantity(m_materials[itemNumber]);
            decreasedMats = m_myShip.DecrementQuantity(m_materials[itemNumber2]);
            // checks to see if this is a unique item or not
            matResults = m_myShip.CheckMaterial(m_materials[recipeNumber]);
            if(decreasedMats){
                cout << "You have built " << m_materials[recipeNumber].m_name << " for your ship" << endl;
            }
            // if a unique item is built then this will run increasing player rank
            if (matResults == NEGATIVE_ONE){
                m_myShip.IncrementQuantity(m_materials[recipeNumber]);
                m_myShip.IncRank();
            }else{
                m_myShip.IncrementQuantity(m_materials[recipeNumber]);
            }   
        }else{
            cout << "You do not have enough materials to combine" << endl;
            }
        }
}

int Game::SearchRecipes(string item1, string item2){
     for (size_t i = 0; i < PROJ2_SIZE; i++)
        {   // this long if statement will return the index of the material that material1 and material2 is equal to the names of item1 and 2 
           if((m_materials[i].m_material1 == item1 || m_materials[i].m_material1 == item2) && (m_materials[i].m_material2 == item1 || m_materials[i].m_material2 == item2)){
               return i;
           }
        }
        return NEGATIVE_ONE;
}

void Game::CalcScore(){
    cout << "***The Ship***" << endl;
    cout << m_myShip.GetName() << endl;
    cout << m_myShip.GetRank() << endl;
}
