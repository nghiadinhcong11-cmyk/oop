#ifndef QUANLYLUONG_H
#define QUANLYLUONG_H

#include "../models/Luong.h"
#include <vector>

class QuanLyLuong {
private:
    std::vector<Luong> dsLuong;

public:
    void themLuong(const Luong& l);
    void hienThiBangLuong(int thang, int nam) const;
    void hienThiTatCa() const;
    Luong* timLuong(std::string maNV, int thang, int nam);
    std::vector<Luong*> timLuongTheoNhanVien(std::string maNV);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // QUANLYLUONG_H
