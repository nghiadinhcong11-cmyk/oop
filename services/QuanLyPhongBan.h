#ifndef QUANLYPHONGBAN_H
#define QUANLYPHONGBAN_H

#include "../models/PhongBan.h"
#include <vector>

using namespace std;

class QuanLyPhongBan {
private:
    vector<PhongBan> dsPhongBan;

public:
    void themPhongBan(const PhongBan& pb);
    void hienThiDanhSach() const;
    PhongBan* timPhongBan(string maPB);
    bool suaPhongBan(string maPB);
    bool xoaPhongBan(string maPB);
    const vector<PhongBan>& getDanhSach() const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif // QUANLYPHONGBAN_H
