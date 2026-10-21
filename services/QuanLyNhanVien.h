#ifndef QUANLYNHANVIEN_H
#define QUANLYNHANVIEN_H

#include "../models/NhanVien.h"
#include <vector>
#include <memory>
#include <string>

using namespace std;

class QuanLyNhanVien {
private:
    vector<unique_ptr<NhanVien>> dsNhanVien;

public:
    bool themNhanVien(unique_ptr<NhanVien> nv);
    void hienThiDanhSach() const;
    bool suaNhanVien(string maNV);
    bool xoaNhanVien(string maNV);

    NhanVien* timTheoMa(string maNV) const;
    vector<NhanVien*> timTheoTen(string ten) const;
    vector<NhanVien*> timTheoPhongBan(string maPB) const;
    vector<NhanVien*> timTheoLoai(string loai) const;

    const vector<unique_ptr<NhanVien>>& getDanhSach() const;
    int getSoLuong() const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif // QUANLYNHANVIEN_H
