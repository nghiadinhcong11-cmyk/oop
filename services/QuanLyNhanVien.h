#ifndef QUANLYNHANVIEN_H
#define QUANLYNHANVIEN_H

#include "../models/NhanVien.h"
#include <vector>
#include <memory>
#include <string>

class QuanLyNhanVien {
private:
    std::vector<std::unique_ptr<NhanVien>> dsNhanVien;

public:
    bool themNhanVien(std::unique_ptr<NhanVien> nv);
    void hienThiDanhSach() const;
    bool suaNhanVien(std::string maNV);
    bool xoaNhanVien(std::string maNV);

    NhanVien* timTheoMa(std::string maNV) const;
    std::vector<NhanVien*> timTheoTen(std::string ten) const;
    std::vector<NhanVien*> timTheoPhongBan(std::string maPB) const;
    std::vector<NhanVien*> timTheoLoai(std::string loai) const;

    const std::vector<std::unique_ptr<NhanVien>>& getDanhSach() const;
    int getSoLuong() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // QUANLYNHANVIEN_H
