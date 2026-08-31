#ifndef QUANLYPHONGBAN_H
#define QUANLYPHONGBAN_H

#include "../models/PhongBan.h"
#include <vector>

class QuanLyPhongBan {
private:
    std::vector<PhongBan> dsPhongBan;

public:
    void themPhongBan(const PhongBan& pb);
    void hienThiDanhSach() const;
    PhongBan* timPhongBan(std::string maPB);
    bool suaPhongBan(std::string maPB);
    bool xoaPhongBan(std::string maPB);
    const std::vector<PhongBan>& getDanhSach() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // QUANLYPHONGBAN_H
