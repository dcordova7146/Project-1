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
int Rockstar::GetRoomBusyDays() const{
    return bookedDays + 10;
}
int Guest::GetAdditionalIncome() const{
    return 0;
}
int Businessman::GetAdditionalIncome() const{
    return income;
}

// Guestmanager class implementations
bool GuestManager::AddGuest(GuestType gtype, RoomType rtype, int stayDays, int additionalIncome = 0){
    //loop that checks if this guestmanager object has a rtype available 

}
bool GuestManager::IsAvailable(RoomType rtype, int inDays = 0){
    //loop that checks if a roomtype is going to be available within indays time
    //does add geust need to call this fucntion?
}
int GuestManager::IncomingProfit(){
    //for loop iterates thru guestlist vector and adds up profit make sure to account for buisinessman additional income
    //
}
float GuestManager::MaxIncome(){
    // my own function to facilite max income 
    // should just be a loop that would iterate thru all rooms and calculating max income
    
}
float GuestManager::EarningEfficiency(){
    //current_per_day_income/max_per_day_income
    return float(IncomingProfit()/MaxIncome());   
}
bool GuestManager:: operator <(GuestManager b){
    return (this.IncomingProfit() < b.IncomingProfit());
}




