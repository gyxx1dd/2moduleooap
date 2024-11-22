#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class RentalService {
public:
    virtual double getSnowboardPrice() const = 0;     
    virtual double getSetupPrice() const = 0;         
    virtual ~RentalService() = default;
};

class BasicRentalService : public RentalService {
public:
    double getSnowboardPrice() const override {
        return 25.0; 
    }

    double getSetupPrice() const override {
        return 10.0; 
    }
};

class PremiumRentalService : public RentalService {
public:
    double getSnowboardPrice() const override {
        return 50.0; 
    }

    double getSetupPrice() const override {
        return 20.0; 
    }
};

class SkiMuneris {
protected:
    shared_ptr<RentalService> rentalService;
public:
    SkiMuneris(shared_ptr<RentalService> service) : rentalService(move(service)) {}
    virtual void addSnowboard(int count) = 0;
    virtual double calculateTotalPrice() const = 0;
    virtual ~SkiMuneris() = default;
};

class SnowboardRental : public SkiMuneris {
private:
    struct Snowboard {
        int id;
        string brand;
        int shoeSize;
        string direction;
    };
    vector<Snowboard> snowboards;
    int count = 0;
public:
    SnowboardRental(shared_ptr<RentalService> service) : SkiMuneris(move(service)) {}

    void addSnowboard(int count) override {
        for (int i = 0; i < count; ++i) {
            Snowboard snowboard = { i + 1, "BrandX", 42, (i % 2 == 0) ? "Left" : "Right" };
            snowboards.push_back(snowboard);
        }
        this->count += count;
        cout << count << " snowboards added to rental.\n";
    }

    double calculateTotalPrice() const override {
        double itemPrice = rentalService->getSnowboardPrice();
        double setupPrice = rentalService->getSetupPrice();
        return count * (itemPrice + setupPrice);
    }
};

int main() {
    shared_ptr<RentalService> basicService = make_shared<BasicRentalService>();
    SnowboardRental basicRental(basicService);
    basicRental.addSnowboard(3);
    cout << "Total price for basic rental: $" << basicRental.calculateTotalPrice() << endl;
    shared_ptr<RentalService> premiumService = make_shared<PremiumRentalService>();
    SnowboardRental premiumRental(premiumService);
    premiumRental.addSnowboard(2);
    cout << "Total price for premium rental: $" << premiumRental.calculateTotalPrice() << endl;
    return 0;
}
