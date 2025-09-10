#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class House
{
    private:
        string address;
        double area_msq;
        double price_eur;

    public:
        House(string _address, double _area_msq, double _price_eur);

        bool operator<(const House &house2) const;

        void setAddress(string _address);
        void setArea(double _area_msq);
        void setPrice(double _set_price);
        string getAddress();

    friend ostream &operator<<(ostream &out, const House &house);
};

class Apartment
{
    private:
        shared_ptr<House> house_ptr;
        int number;
        double area_msq;
        double monthly_rent_eur;

    public:
        Apartment(
            shared_ptr<House> _house_ptr,
            int _number,
            double _area_msq,
            double _monthly_rent_eur
        );

        bool operator<(const Apartment &apartment2) const;
        void printApartment() const;
};


/*
    House methods
*/
House::House(string _address, double _area_msq, double _price_eur) :
    address(_address), area_msq(_area_msq), price_eur(_price_eur) {}

bool House::operator<(const House &house2) const
{
    return (price_eur / area_msq) < (house2.price_eur / house2.area_msq);
}

void House::setAddress(string _address) { address = _address; }
void House::setArea(double _area_msq) { area_msq = _area_msq; }
void House::setPrice(double _price_eur) { price_eur = _price_eur; }

string House::getAddress() { return address; }

ostream &operator<<(ostream &out, const House &house)
{
    cout<< house.address << ", "
        << house.area_msq << ", "
        << house.price_eur;
    return out;
}

/*
    Apartment methods
*/
Apartment::Apartment(
    shared_ptr<House> _house_ptr,
    int _number,
    double _area_msq,
    double _monthly_rent_eur
) :
house_ptr(_house_ptr),
number(_number),
area_msq(_area_msq),
monthly_rent_eur(_monthly_rent_eur) {}

bool Apartment::operator<(const Apartment &apartment2) const
{
    return monthly_rent_eur < apartment2.monthly_rent_eur;
}
void Apartment::printApartment() const
{
    cout<< "Address: " << house_ptr->getAddress() << ". Apartment nr: " << number << "\n"
        << "Apartment size: " << area_msq << " m^2\n"
        << "Monthly rent: " << monthly_rent_eur << " euros"
        << endl;
}


void sort_apartments(vector<Apartment> &apartments)
{
    sort(
        apartments.begin(),
        apartments.end(),
        [](const Apartment &a1, const Apartment &a2) {
            return a1 < a2;
        }
    );
}

int main()
{
    House house1("742 evergreen terrace", 6900.69, 420000.42);
    House house2("123 fakestreet", 4200.42, 69000.69);

    vector<Apartment> apartment_vec;

    double min_apt_area = 20.0,
        max_apt_area = min_apt_area * 10;

    double min_apt_rent = 300.0,
        max_apt_rent = min_apt_rent * 10;

    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> rand_area(min_apt_area, max_apt_rent);
    uniform_real_distribution<> rand_rent(min_apt_rent, max_apt_rent);

    for (int i = 0; i < 3; i++) {
        Apartment apartment(
            make_shared<House>(house1),
            i+1,
            rand_area(gen),
            rand_rent(gen)
        );
        apartment_vec.push_back(apartment);
    }
    for (int j = 0; j < 4; j++) {
        Apartment apartment(
            make_shared<House>(house2),
            j+1,
            rand_area(gen),
            rand_rent(gen)
        );
        apartment_vec.push_back(apartment);
    }

    sort_apartments(apartment_vec);
    for (const auto apt : apartment_vec) {
        apt.printApartment();
        cout << '\n';
    }

    return 0;
}