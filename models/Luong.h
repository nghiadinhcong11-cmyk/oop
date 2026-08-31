#ifndef LUONG_H
#define LUONG_H

#include <string>
#include <iostream>

class Luong {
private:
    std::string maLuong;
    std::string maNV;
    int thang;
    int nam;
    double luongCoBan;
    double phuCap;
    double tienTangCa;
    double khauTru;
    double luongThucNhan;

public:
    Luong();
    Luong(std::string maLuong, std::string maNV, int thang, int nam,
          double lcb, double pc, double ttc, double kt, double ltn);

    void hienThiPhieuLuong() const;

    // Getters
    std::string getMaNV() const;
    int getThang() const;
    int getNam() const;

    std::string serialize() const;
};

#endif // LUONG_H
