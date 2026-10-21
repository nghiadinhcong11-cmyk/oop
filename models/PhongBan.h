#ifndef PHONGBAN_H
#define PHONGBAN_H

#include <string>
#include <iostream>

using namespace std;

class PhongBan {
private:
    string maPB;
    string tenPB;
    string truongPhong;
    string moTa;

public:
    PhongBan();
    PhongBan(string maPB, string tenPB, string truongPhong, string moTa);

    // Getters
    string getMaPB() const;
    string getTenPB() const;

    // Setters
    void setMaPB(string maPB);
    void setTenPB(string tenPB);

    void hienThi() const;
    string taoDongDuLieu() const;
};

#endif // PHONGBAN_H
