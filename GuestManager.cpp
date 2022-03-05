#include <iostream>
#include "GuestManager.h"


// Guest class implementations
int Guest::getBookedDays(){
    return bookedDays;
}
RoomType Guest::getRoomType() const{
    return room;
}
GuestType Guest::getGuestType() const{
    return guest;
}

//sub classes implementationm
int Guest::GetRoomBusyDays() const{
    return bookedDays;
}
int Guest::GetAdditionalIncome() const {
    return 0;
}
int Family::GetRoomBusyDays() const{
    return bookedDays;
}
int Family::GetAdditionalIncome() const{
    return 0;
}

int Rockstar::GetRoomBusyDays() const{
    return bookedDays + 10;
}
int Rockstar::GetAdditionalIncome() const{
    return 0;
}
int Businessman::GetAdditionalIncome() const{
    return income * bookedDays;
}
int Businessman::GetRoomBusyDays() const{
    return bookedDays;
}


// Guestmanager class implementations
GuestManager::GuestManager(int StandardRooms, int dayPriceStandard, int ComfortRooms, int dayPriceComfort){
    //these should be const?
    numStdRoom = StandardRooms;
    numCmfRoom = ComfortRooms;
    priceStdRoom = dayPriceStandard;
    priceCmfRoom = dayPriceComfort;
    usedCmfRoom = 0;
    usedStdRoom = 0;
    
}
bool GuestManager::AddGuest(GuestType gtype, RoomType rtype, int stayDays, int additionalIncome = 0){
    //loop that checks if this guestmanager object has a rtype available 
    if (IsAvailable(rtype)) {
        if (gtype == GuestType::Businessman ) {
            Guest*  ptr = new Businessman(gtype, rtype, stayDays, additionalIncome);
            guestList.push_back(ptr);
            
        }
        if(gtype == GuestType::Family) {
            Guest*  ptr = new Family(gtype, rtype, stayDays);
            guestList.push_back(ptr);
        }
        if(gtype == GuestType::Rockstar){
            Guest*  ptr = new Rockstar(gtype, rtype, stayDays);
            guestList.push_back(ptr);
        }
        if(rtype == RoomType::Comfort){usedCmfRoom++;}
        if(rtype == RoomType::Standard){usedStdRoom++;}
        return true;
    }
    return false;
}
bool GuestManager::IsAvailable(RoomType rtype, int inDays = 0){
    //loop that checks if a roomtype is going to be available within indays time
    //decrement amount of rooms here based on what type of room it is
    //memory leaks?
    if(inDays == 0){
         if(rtype == RoomType::Comfort){
            if(usedCmfRoom > numCmfRoom ){
                return false;
            }
        }
        if(rtype == RoomType::Standard){
            if(usedStdRoom > numCmfRoom){
                return false;
            }
        }
        return true;
     }else{
        //for loop checking days
        for(int i = 0;i < guestList.size();i++){
            if(guestList[i]->GetRoomBusyDays() <= inDays){
                return true;
            }
        }
        return false;
        
    }
   
}
int GuestManager::IncomingProfit(){
    //for loop iterates thru guestlist vector and adds up profit make sure to account for buisinessman additional income
    int profit = 0;
    for(int i = 0;i < guestList.size();i++){
        if(guestList[i]->getRoomType() == RoomType::Standard ){
            if(guestList[i]->getGuestType() == GuestType::Businessman){
                profit += (guestList[i]->GetAdditionalIncome() * guestList[i]->GetRoomBusyDays())+ (priceStdRoom * guestList[i]->GetRoomBusyDays());
            }else{
                profit += (priceStdRoom * guestList[i]->GetRoomBusyDays());
            }

        }else if (guestList[i]->getRoomType() == RoomType::Comfort){
             if(guestList[i]->getGuestType() == GuestType::Businessman){
                profit += (guestList[i]->GetAdditionalIncome() * guestList[i]->GetRoomBusyDays())+ (priceCmfRoom * guestList[i]->GetRoomBusyDays());
             }else{
                 profit += (priceCmfRoom * guestList[i]->GetRoomBusyDays());
             }
        }

    }

}
int GuestManager::MaxIncome(){
    // my own function to facilite earning efficiency
    // should just be a loop that would iterate thru all rooms and calculating max income
    //max_per_day_income is the sum of base day prices of all existing rooms. 
    //current_per_day_income is the sum of base day prices of all currently occupied rooms plus all additional income generated per day the by current businessmen guests.

    //(numCmfRoom * priceCmfRoom) + (numStdRoom * priceStdRoom) 1 day base max income
    int maxperday = 0;
    for(int i = 0; i < guestList.size();i++){
        if(guestList[i]->getRoomType()==RoomType::Comfort){
            if(guestList[i]->getGuestType()==GuestType::Businessman){
                maxperday += guestList[i]->GetAdditionalIncome() + priceCmfRoom;
            }else{
                maxperday += priceCmfRoom;
            }
        }else if(guestList[i]->getRoomType()==RoomType::Standard){
            if(guestList[i]->getGuestType()==GuestType::Businessman){
                maxperday += guestList[i]->GetAdditionalIncome() + priceStdRoom;
            }else{
                maxperday += priceStdRoom;
            }
        }
    }
    return maxperday;
    
}
float GuestManager::EarningEfficiency(){
    //current_per_day_income/max_per_day_income
    return float((MaxIncome())/(((numCmfRoom * priceCmfRoom) + (numStdRoom * priceStdRoom))));   
}
bool GuestManager:: operator <(GuestManager b){
    return (IncomingProfit() < b.IncomingProfit());
}




