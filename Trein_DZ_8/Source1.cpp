#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>

// Класс "IP-адрес"
class IPAddress {
public:
    std::vector<int> octets; // Октеты IP-адреса

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& input, IPAddress& ipAddress) {
        std::string address;
        input >> address;

        std::stringstream ss(address);
        std::string octet;
        while (getline(ss, octet, '.')) {
            int value = stoi(octet);
            ipAddress.octets.push_back(value);
        }
        return input;
    }

    // Метод-член для проверки валидности IP-адреса
    bool checkValidity() {
        if (octets.size() != 4) {
            return false;
        }

        for (int octet : octets) {
            if (octet < 0 || octet > 255) {
                return false;
            }
        }
        return true;
    }

    // Метод-член для получения сетевого адреса
    IPAddress getNetworkAddress(const IPAddress& subnetMask) {
        IPAddress networkAddress;
        for (int i = 0; i < 4; i++) {
            int networkOctet = octets[i] & subnetMask.octets[i];
            networkAddress.octets.push_back(networkOctet);
        }
        return networkAddress;
    }

    // Перегрузка оператора сравнения (==)
    bool operator==(const IPAddress& other) {
        return octets == other.octets;
    }

    // Перегрузка оператора сравнения (<)
    bool operator<(const IPAddress& other) {
        return octets < other.octets;
    }
};

// Класс "Маска сети"
class SubnetMask {
public:
    std::vector<int> octets; // Октеты маски

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& input, SubnetMask& mask) {
        std::string maskString;
        input >> maskString;

        std::stringstream ss(maskString);
        std::string octet;
        while (getline(ss, octet, '.')) {
            int value = stoi(octet);
            mask.octets.push_back(value);
        }
        return input;
    }

    // Метод-член для проверки принадлежности IP-адреса к подсети
    bool isBelongingToSubnet(const IPAddress& ipAddress) {
        if (octets.size() != 4 || ipAddress.octets.size() != 4) {
            return false;
        }

        for (int i = 0; i < 4; i++) {
            int networkOctet = ipAddress.octets[i] & octets[i];
            if (networkOctet != octets[i]) {
                return false;
            }
        }
        return true;
    }

    // Метод-член для вычисления количества возможных узлов в сети
    int getNumberOfPossibleNodes() {
        int numberOfOnes = 0;
        for (int octet : octets) {
            std::string binary = std::bitset<8>(octet).to_string();
            for (char bit : binary) {
                if (bit == '1') {
                    numberOfOnes++;
                }
            }
        }
        return (1 << (32 - numberOfOnes)) - 2;
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    // Проверка ввода IP-адреса
    IPAddress ipAddress;
    std::cout << "Введите IP-адрес: ";
    std::cin >> ipAddress;

    // Проверка валидности IP-адреса
    if (ipAddress.checkValidity()) {
        std::cout << "IP-адрес является валидным!" << std::endl;
    }
    else {
        std::cout << "IP-адрес не является валидным!" << std::endl;
    }

    // Проверка ввода маски сети
    SubnetMask subnetMask;
    std::cout << "Введите маску сети: ";
    std::cin >> subnetMask;

    // Проверка принадлежности IP-адреса к подсети
    if (subnetMask.isBelongingToSubnet(ipAddress)) {
        std::cout << "IP-адрес принадлежит к данной сети!" << std::endl;
    }
    else {
        std::cout << "IP-адрес не принадлежит к данной сети!" << std::endl;
    }

    // Получение сетевого адреса
    /*IPAddress networkAddress = ipAddress.getNetworkAddress(subnetMask);
    std::cout <<"Сетевой адрес: ";    
    for (int i = 0; i < 4; i++) {
        std::cout << networkAddress.octets[i];
        if (i != 3) {
            std::cout << ".";
        }
    }
    std::cout << std::endl;*/

    // Проверка сравнения IP-адресов
    IPAddress ipAddress2;
    std::cout << "Введите второй IP-адрес: ";
    std::cin >> ipAddress2;

    if (ipAddress == ipAddress2) {
        std::cout << "IP-адреса равны!" << std::endl;
    }
    else if (ipAddress < ipAddress2) {
        std::cout << "Первый IP-адрес меньше!" << std::endl;
    }
    else {
        std::cout << "Второй IP-адрес меньше!" << std::endl;
    }

    // Подсчет количества возможных узлов в сети
    int numberOfPossibleNodes = subnetMask.getNumberOfPossibleNodes();
    std::cout << "Количество возможных узлов в сети: " << numberOfPossibleNodes << std::endl;

    return 0;
}
