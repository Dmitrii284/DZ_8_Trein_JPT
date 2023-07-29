//
//#include <iostream>
//#include <string>
//#include <sstream>
//
//
//class IPAddress {
//private:
//    int octet1_;
//    int octet2_;
//    int octet3_;
//    int octet4_;
//
//public:
//    IPAddress() : octet1_(0), octet2_(0), octet3_(0), octet4_(0) {}
//    IPAddress(int octet1, int octet2, int octet3, int octet4)
//        : octet1_(octet1), octet2_(octet2), octet3_(octet3), octet4_(octet4) {}
//
//    friend std::istream& operator>>(std::istream& input, IPAddress& obj);
//
//    bool isValidIP() {
//        if (octet1_ >= 0 && octet1_ <= 255 &&
//            octet2_ >= 0 && octet2_ <= 255 &&
//            octet3_ >= 0 && octet3_ <= 255 &&
//            octet4_ >= 0 && octet4_ <= 255) {
//            return true;
//        }
//        return false;
//    }
//
//    std::string getNetworkAddress(const IPAddress& subnetMask) {
//        int networkOctet1 = octet1_ & subnetMask.octet1_;
//        int networkOctet2 = octet2_ & subnetMask.octet2_;
//        int networkOctet3 = octet3_ & subnetMask.octet3_;
//        int networkOctet4 = octet4_ & subnetMask.octet4_;
//
//        std::stringstream ss;
//        ss << networkOctet1 << "." << networkOctet2 << "." << networkOctet3 << "." << networkOctet4;
//
//        return ss.str();
//    }
//
//    bool operator==(const IPAddress& other) {
//        return octet1_ == other.octet1_ &&
//            octet2_ == other.octet2_ &&
//            octet3_ == other.octet3_ &&
//            octet4_ == other.octet4_;
//    }
//
//    bool operator<(const IPAddress& other) {
//        if (octet1_ != other.octet1_) {
//            return octet1_ < other.octet1_;
//        }
//        if (octet2_ != other.octet2_) {
//            return octet2_ < other.octet2_;
//        }
//        if (octet3_ != other.octet3_) {
//            return octet3_ < other.octet3_;
//        }
//        return octet4_ < other.octet4_;
//    }
//};
//
//std::istream& operator>>(std::istream& input, IPAddress& obj) {
//    char dot;
//    input >> obj.octet1_ >> dot >> obj.octet2_ >> dot >> obj.octet3_ >> dot >> obj.octet4_;
//    return input;
//}
//
//class SubnetMask {
//private:
//    int octet1_;
//    int octet2_;
//    int octet3_;
//    int octet4_;
//
//public:
//    SubnetMask() : octet1_(0), octet2_(0), octet3_(0), octet4_(0) {}
//    SubnetMask(int octet1, int octet2, int octet3, int octet4)
//        : octet1_(octet1), octet2_(octet2), octet3_(octet3), octet4_(octet4) {}
//
//    friend std::istream& operator>>(std::istream& input, SubnetMask& obj);
//
//    bool operator==(const SubnetMask& other) {
//        return octet1_ == other.octet1_ &&
//            octet2_ == other.octet2_ &&
//            octet3_ == other.octet3_ &&
//            octet4_ == other.octet4_;
//    }
//
//    int getNumPossibleHosts() {
//        int numOnes = 0;
//        std::string binaryString = toBinaryString();
//        for (char c : binaryString) {
//            if (c == '1') {
//                numOnes++;
//            }
//        }
//        // Exclude network address and broadcast address
//        return (1 << (32 - numOnes)) - 2;
//    }
//
//private:
//    std::string toBinaryString() {
//        std::string binaryString;
//
//        appendOctetToBinaryString(octet1_, binaryString);
//        appendOctetToBinaryString(octet2_, binaryString);
//        appendOctetToBinaryString(octet3_, binaryString);
//        appendOctetToBinaryString(octet4_, binaryString);
//
//        return binaryString;
//    }
//
//    void appendOctetToBinaryString(int octet, std::string& binaryString) {
//        std::string octetBinaryString;
//        for (int i = 7; i >= 0; i--) {
//            octetBinaryString.push_back(((octet >> i) & 1) + '0');
//        }
//        binaryString += octetBinaryString;
//    }
//};
//
//std::istream& operator>>(std::istream& input, SubnetMask& obj) {
//    char dot;
//    input >> obj.octet1_ >> dot >> obj.octet2_ >> dot >> obj.octet3_ >> dot >> obj.octet4_;
//    return input;
//}
//
//int main()
//{
//    setlocale(LC_ALL, "Rus");
//   
//
//    SubnetMask mask;
//    std::cin >> mask;
//
//
//    IPAddress ip_adress;
//    std::cin >> ip_adress;
//
//    if (!ip_adress.isValidIP())
//    {
//        std::cout << "\n\nERROR ip_adress IS NOT MATCH" << '\n';
//        exit(1);
//    }
//    mask.getNumPossibleHosts();   
//    ip_adress.isValidIP();
//    return 0;
//}