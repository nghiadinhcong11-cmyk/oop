#ifndef PHONGBAN_H
#define PHONGBAN_H

#include <string>
#include <iostream>

class PhongBan {
private:
    std::string maPB;
    std::string tenPB;
    std::string truongPhong;
    std::string moTa;

public:
    PhongBan();
    PhongBan(std::string maPB, std::string tenPB, std::string truongPhong, std::string moTa);

    // Getters
    std::string getMaPB() const;
    std::string getTenPB() const;

    // Setters
    void setMaPB(std::string maPB);
    void setTenPB(std::string tenPB);

    void hienThi() const;
    std::string serialize() const;
};

#endif // PHONGBAN_H
