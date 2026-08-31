#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <string>

#include "ChamCong.h"

class NhanVien {
protected:
    std::string maNV;
    std::string hoTen;
    std::string ngaySinh;
    std::string gioiTinh;
    std::string soDienThoai;
    std::string email;
    std::string diaChi;
    std::string maPB;
    std::string chucVu;
    std::string loaiNV;
    double luongCoBan;

public:
    NhanVien();
    NhanVien(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
             std::string soDienThoai, std::string email, std::string diaChi,
             std::string maPB, std::string chucVu, std::string loaiNV, double luongCoBan);
    virtual ~NhanVien();

    // Getters
    std::string getMaNV() const;
    std::string getHoTen() const;
    std::string getLoaiNV() const;
    double getLuongCoBan() const;
    std::string getMaPB() const;

    // Setters
    void setMaNV(std::string maNV);
    void setHoTen(std::string hoTen);
    void setLuongCoBan(double luongCoBan);
    void setMaPB(std::string maPB);

    // Pure virtual function - bay gio nhan vao ChamCong
    virtual double tinhLuong(const ChamCong& cc) const = 0;

    // Cac ham ho tro tinh toan tung thanh phan
    virtual double getPhuCap() const { return 0; }
    virtual double getTienTangCa(const ChamCong& cc) const { return 0; }

    // Display basic info
    virtual void hienThiThongTin() const;

    // Serialization for File I/O
    virtual std::string serialize() const;
};

#endif // NHANVIEN_H
