#ifndef QUANLYCHAMCONG_H
#define QUANLYCHAMCONG_H

#include "../models/ChamCong.h"
#include <vector>

using namespace std;

class QuanLyChamCong {
private:
    vector<ChamCong> dsChamCong;

public:
    void themChamCong(const ChamCong& cc);
    void hienThiDanhSach() const;
    ChamCong* timChamCong(string maNV, int thang, int nam);
    bool suaChamCong(string maNV, int thang, int nam);
    bool xoaChamCong(string maNV, int thang, int nam);
    vector<ChamCong*> timTheoNhanVien(string maNV);
    vector<ChamCong*> timTheoThang(int thang, int nam);

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif // QUANLYCHAMCONG_H
