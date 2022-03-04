#include <iostream>
#include <vector>
// .h is only decleration
enum class RoomType{
    Standard, Comfort
};

enum class GuestType{
    Family, Businessman, Rockstar
};

class Guest{
    protected:
    RoomType room;
    GuestType guest;
    int bookedDays;

    public:
    GuestType getGuestType() const;
    RoomType getRoomType() const;
    int getBookedDays();

    virtual int GetRoomBusyDays() = 0;
    virtual int GetAdditionalIncome() const = 0;
    Guest (GuestType, RoomType, int StayDuration); // decleration of constructor
    virtual ~Guest(); // Deconstructor does nothing here but is inherited?
    

}
// Sub classes 
class Family : public Guest{
    
}
class Rockstar : public Guest{
    
}
class Businessman : public Guest{
    private:
    int income;
   
}

class GuestManager{
    std::vector<Guest*> guestList;
    GuestManager (int StandardRooms, int dayPriceStandard, int ComfortRooms, int dayPriceComfort);
    bool AddGuest (GuestType, RoomType, int stayDays, int additionalIncome);
    bool IsAvailable(RoomType, int inDays);
    int IncomingProfit();
    float EarningEfficiency();
    bool operator < (const GuestManager a); //  GuestManager A is less than GuestManager B if A.IncomingProfit() is less than B.IncomingProfit() this needs to be overridden?
    

}
