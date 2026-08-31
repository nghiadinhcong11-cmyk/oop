#ifndef QUANLYCHAMCONG_H
#define QUANLYCHAMCONG_H

#include "../models/ChamCong.h"
#include <vector>

class QuanLyChamCong {
private:
    std::vector<ChamCong> dsChamCong;

public:
    void themChamCong(const ChamCong& cc);
    void hienThiDanhSach() const;
    ChamCong* timChamCong(std::string maNV, int thang, int nam);
    bool suaChamCong(std::string maNV, int thang, int nam);
    bool xoaChamCong(std::string maNV, int thang, int nam);
    std::vector<ChamCong*> timTheoNhanVien(std::string maNV);
    std::vector<ChamCong*> timTheoThang(int thang, int nam);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // QUANLYCHAMCONG_H
