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

    virtual int GetRoomBusyDays() const = 0;
    virtual int GetAdditionalIncome() const = 0;
    Guest (GuestType, RoomType, int StayDuration); // decleration of constructor
    virtual ~Guest(); // Deconstructor does nothing here but is inherited?
    

};
// Sub classes 
class Family : public Guest{
    public:
    int GetAdditionalIncome() const;
    int GetRoomBusyDays() const;
    Family(GuestType, RoomType, int StayDuration);
    

};
class Rockstar : public Guest{
    public:
    int GetAdditionalIncome() const;
    int GetRoomBusyDays() const;
    Rockstar(GuestType gtype, RoomType gytpe , int StayDuration);
    
};
class Businessman : public Guest{
    private:
    int income;

    public:
    Businessman(GuestType gtype, RoomType rtype, int stayDuration,int additionalIncome);
    int GetAdditionalIncome() const;
    int GetRoomBusyDays() const;


   
};

class GuestManager{
    private:
    std::vector<Guest*> guestList;
    int numStdRoom = 0;//number of standard rooms
    int priceStdRoom = 0;//price of standard rooms
    int numCmfRoom = 0;//number of comfy rooms
    int priceCmfRoom = 0;//price of comfy rooms
    int usedStdRoom = 0;//number of standard rooms that are currently being used
    int usedCmfRoom = 0;

    public:
    GuestManager(int StandardRooms, int dayPriceStandard, int ComfortRooms, int dayPriceComfort);
    bool AddGuest (GuestType gtype, RoomType rtype, int stayDays, int additionalIncome = 0);
    bool IsAvailable(RoomType rtype, int inDays = 0);
    int IncomingProfit();
    float EarningEfficiency();
    //int CurrentPerDay();
    bool operator< (GuestManager& b); //  GuestManager A is less than GuestManager B if A.IncomingProfit() is less than B.IncomingProfit() this needs to be overridden?
    ~GuestManager();

};
