#ifndef QUANLYLUONG_H
#define QUANLYLUONG_H

#include "../models/Luong.h"
#include <vector>

using namespace std;

class QuanLyLuong {
private:
    vector<Luong> dsLuong;

public:
    void themLuong(const Luong& l);
    void hienThiBangLuong(int thang, int nam) const;
    void hienThiTatCa() const;
    Luong* timLuong(string maNV, int thang, int nam);
    vector<Luong*> timLuongTheoNhanVien(string maNV);
    const vector<Luong>& getDanhSach() const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif // QUANLYLUONG_H
