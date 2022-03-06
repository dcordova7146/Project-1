#include <iostream>
#include "GuestManager.h"


// Guest class implementations
Guest::Guest(GuestType gtype, RoomType rtype, int stayDuration){}
Guest::~Guest(){} // destructor 
int Guest::getBookedDays(){
    return bookedDays;
}
RoomType Guest::getRoomType() const{
    return room;
}
GuestType Guest::getGuestType() const{
    return guest;
}

//sub classes implementation
Businessman::Businessman(GuestType gtype, RoomType rtype, int stayDuration,int additionalIncome):Guest(gtype, rtype, stayDuration){
    room = rtype;
    guest = gtype;
    bookedDays = stayDuration;
    income = additionalIncome;
}
Rockstar::Rockstar(GuestType gtype, RoomType rtype, int stayDuration):Guest(gtype, rtype, stayDuration){
    room = rtype;
    guest = gtype;
    bookedDays = stayDuration;
}
Family::Family(GuestType gtype, RoomType rtype, int stayDuration):Guest(gtype, rtype, stayDuration){
    room = rtype;
    guest = gtype;
    bookedDays = stayDuration;
}

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
    return income;
}
int Businessman::GetRoomBusyDays() const{
    return bookedDays;
}

//Guestmanager class implementations
GuestManager::GuestManager(int StandardRooms, int dayPriceStandard, int ComfortRooms, int dayPriceComfort){
    numStdRoom = StandardRooms;
    numCmfRoom = ComfortRooms;
    priceStdRoom = dayPriceStandard;
    priceCmfRoom = dayPriceComfort;
    
}
GuestManager:: ~GuestManager(){ //destructor
    for(long unsigned int i = 0; i <guestList.size();i++){
        delete guestList[i];
        guestList[i] = nullptr;
    }

}
bool GuestManager::AddGuest(GuestType gtype, RoomType rtype, int stayDays, int additionalIncome){
    //loop that checks if this guestmanager object has a rtype available 
    //std::cout << "Guest add attempt " << std::endl;
    if (IsAvailable(rtype)) {
        //std::cout << "1";
        if (gtype == GuestType::Businessman ) {
            Guest* ptr = new Businessman(gtype, rtype, stayDays, additionalIncome);
            guestList.push_back(ptr);
            //std::cout << "busy man added" << std::endl;
            
        }
        if(gtype == GuestType::Family) {
            Guest* ptr = new Family(gtype, rtype, stayDays);
            guestList.push_back(ptr);
            //std::cout << "family added" << std::endl;
        }
        if(gtype == GuestType::Rockstar){
            Guest* ptr = new Rockstar(gtype, rtype, stayDays);
            guestList.push_back(ptr);
            //std::cout << "rockstar added" << std::endl;
        }
        if(rtype == RoomType::Comfort){usedCmfRoom++;}
        if(rtype == RoomType::Standard){usedStdRoom++;}
        return true;
    }
    //std::cout << "failed" << std::endl;
    return false;
}
bool GuestManager::IsAvailable(RoomType rtype, int inDays){
    //loop that checks if a roomtype is going to be available within indays time
    //decrement amount of rooms here based on what type of room it is
    //memory leaks?
    if(inDays == 0){
        //std::cout << "Is avail test" << std::endl;
         if(rtype == RoomType::Comfort){
            if(usedCmfRoom >= numCmfRoom ){
                return false;
            }
        }else if(rtype == RoomType::Standard){
            if(usedStdRoom >= numStdRoom){
                return false;
            }
        }
        return true;
     }else{
        //for loop checking in days
        for(long unsigned int i = 0;i < guestList.size();i++){
            if(guestList[i]->GetRoomBusyDays() <= inDays){
                //std::cout << "Num busy days: ";
                //std::cout << guestList[i]->GetRoomBusyDays() <<  std::endl;
                return true;
            }
        }
        return false;
        
    }
   
}
int GuestManager::IncomingProfit(){
    //for loop iterates thru guestlist vector and adds up profit make sure to account for buisinessman additional income
    int profit = 0;
    for(long unsigned int i = 0;i < guestList.size();i++){
        if(guestList[i]->getRoomType() == RoomType::Standard ){
            if(guestList[i]->getGuestType() == GuestType::Businessman){
                profit += (guestList[i]->GetAdditionalIncome() * guestList[i]->GetRoomBusyDays())+ (priceStdRoom * guestList[i]->GetRoomBusyDays());
            }else if (guestList[i]->getGuestType() == GuestType::Rockstar){
                profit += (priceStdRoom * (guestList[i]->GetRoomBusyDays()-10));
            }else{
                profit += (priceStdRoom * guestList[i]->GetRoomBusyDays());
            }

        }if (guestList[i]->getRoomType() == RoomType::Comfort){
             if(guestList[i]->getGuestType() == GuestType::Businessman){
                profit += (guestList[i]->GetAdditionalIncome() * guestList[i]->GetRoomBusyDays())+ (priceCmfRoom * guestList[i]->GetRoomBusyDays());
             }else if(guestList[i]->getGuestType() == GuestType::Rockstar){
                profit += (priceCmfRoom * (guestList[i]->GetRoomBusyDays()-10));
             }else{
                profit += (priceCmfRoom * guestList[i]->GetRoomBusyDays());
             }
        }

    }
    //std::cout << "Profit: " << profit << std::endl;
    return profit;

}
float GuestManager::EarningEfficiency(){
    //current_per_day_income/max_per_day_income
    // current per day is = current per day function result
    //(numCmfRoom * priceCmfRoom) + (numStdRoom * priceStdRoom) 1 day base max income
    float currentPerDay = 0;
    float maxPerDay = 0;
    //std:: cout << guestList.size();
    for(long unsigned int i = 0; i < guestList.size();i++){
    //std::cout << "run +1" << std::endl;
        if(guestList[i]->getRoomType()==RoomType::Standard){
            //std::cout << "standard room : ";
            if(guestList[i]->getGuestType()==GuestType::Family){
                //std::cout << " + 1 family guest price added : " << priceStdRoom << std::endl; 
                currentPerDay += priceStdRoom;
            }
            if(guestList[i]->getGuestType()==GuestType::Rockstar){
                //std::cout << " + 1 ROckstar guest price added " << std::endl; 

                currentPerDay += priceStdRoom;
            }
            if(guestList[i]->getGuestType()==GuestType::Businessman){
                //std::cout << " + 1 Busyman guest price added + "<< guestList[i]->GetAdditionalIncome() << std::endl; 
                currentPerDay += priceStdRoom + guestList[i]->GetAdditionalIncome();
            }
        }
        if(guestList[i]->getRoomType()==RoomType::Comfort){
            //std::cout << "comfort room: ";
            if(guestList[i]->getGuestType()==GuestType::Family){
                //std::cout << " + 1 family guest price added : " << priceCmfRoom << std::endl;
                currentPerDay += priceCmfRoom;
            }
            if(guestList[i]->getGuestType()==GuestType::Rockstar){
                //std::cout << " + 1 ROckstar guest price added" << std::endl;
                currentPerDay += priceCmfRoom;
            }
            if(guestList[i]->getGuestType()==GuestType::Businessman){
                //std::cout << " + 1 Busyman guest price added + "<< guestList[i]->GetAdditionalIncome() << std::endl;
                currentPerDay += priceCmfRoom + guestList[i]->GetAdditionalIncome();
            }
        }
    }
    maxPerDay = ((float(numCmfRoom * priceCmfRoom) + float(numStdRoom * priceStdRoom)));   
    //std::cout << "Max Per Day:  "<< maxPerDay << std::endl;
    return float((currentPerDay)/(maxPerDay));   
}
bool GuestManager:: operator <(GuestManager& b){
    return (IncomingProfit() < b.IncomingProfit());
}




