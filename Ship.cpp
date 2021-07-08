//Title: Ship.cpp
//Author: Amarjot Gill
//Date: 2/14/2021
//Description: This is part of the No Man's Alchemy Project in CMSC 202 @ UMBC
#include "Ship.h"


Ship::Ship(){
    // bases for each variable
    m_shipName = BASE_SHIP_NAME;
    m_shipRank = D;
    m_numMaterials = 0;
    // populates m_myMatierals with placeholder values
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        m_myMaterials[i].m_name = PLACEHOLDER;
        m_myMaterials[i].m_quantity = 0;
    }
}

Ship::Ship(string ShipName){
    m_shipName = ShipName;
}

void Ship::SetName(string name){
    m_shipName = name;
}

string Ship::GetName(){
    return m_shipName;
}

void Ship::AddMaterial(Material Mat){
    for (int i = 0; i < PROJ2_SIZE; i++){
        // returns if material is already in list  
        if (m_myMaterials[i].m_name == Mat.m_name){
            return;
            // if at index is a placeholder item then it adds the new item from m_materials
        }else if(m_myMaterials[i].m_name == PLACEHOLDER){
            m_myMaterials[i].m_name = Mat.m_name;
            m_myMaterials[i].m_quantity = 0;
            return;
        }
    }
}

int Ship::CheckMaterial(Material Mat){
    for (int i = 0; i < PROJ2_SIZE; i++)
    {   // returns the index if the the material exist and the player has more than 0
        if (m_myMaterials[i].m_name == Mat.m_name && m_myMaterials[i].m_quantity > 0){
            return i;
        } 
    }
    return NEGATIVE_ONE;
}

void Ship::IncrementQuantity(Material Mat){
    for (int i = 0; i < PROJ2_SIZE; i++)
    {   // increments the quantity
        if(m_myMaterials[i].m_name == Mat.m_name){
            m_myMaterials[i].m_quantity++;
        }
    }
}

bool Ship::DecrementQuantity(Material Mat){
    for (int i = 0; i < PROJ2_SIZE; i++)
    {   // decreases quantity
        if(m_myMaterials[i].m_name == Mat.m_name){ 
            if(m_myMaterials[i].m_quantity == 0){
                return false;
            }else{
                m_myMaterials[i].m_quantity--;
                return true; 
            } 
        }
    }
    return false;
}

bool Ship::CheckQuantity(Material Mat, Material Mat2){
    // bool for both materials
    bool goodAmount1;
    bool goodAmount2;
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (m_myMaterials[i].m_name == Mat.m_name){
            if (m_myMaterials[i].m_quantity > 0){
                // sets it too true if player has more then 0 of material
               goodAmount1 = true;
            }else if(m_myMaterials[i].m_quantity == 0){
                goodAmount1 = false;
            }  
        }

        if (m_myMaterials[i].m_name == Mat2.m_name){
            if (m_myMaterials[i].m_quantity > 0){
               goodAmount2 = true;
            }else if(m_myMaterials[i].m_quantity == 0){
                goodAmount2 = false;
            } 
        }
    }
    // if both goodAmounts are true then player has enough to combine
    if (goodAmount1 & goodAmount2){
        return true;
    }else{
        return false;
    }
}

char Ship::GetRank(){
    return m_shipRank;
}

void Ship::IncRank(){
    // increases player rank by one
    if(m_shipRank == D){
        m_shipRank = C;
    }else if(m_shipRank == C){
        m_shipRank = B;
    }else if (m_shipRank == B){
        m_shipRank = A;
    }else if(m_shipRank == A){
        m_shipRank = S;
    }
}

Material Ship::GetMaterial(int index){
    return m_myMaterials[index];
}
