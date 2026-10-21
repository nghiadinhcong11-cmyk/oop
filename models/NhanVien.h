#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <string>

#include "ChamCong.h"

using namespace std;

class NhanVien {
protected:
    string maNV;
    string hoTen;
    string ngaySinh;
    string gioiTinh;
    string soDienThoai;
    string email;
    string diaChi;
    string maPB;
    string chucVu;
    string ngayVaoLam;
    string loaiNV;
    double luongCoBan;

public:
    NhanVien();
    NhanVien(string maNV, string hoTen, string ngaySinh, string gioiTinh,
             string soDienThoai, string email, string diaChi,
             string maPB, string chucVu, string ngayVaoLam, string loaiNV, double luongCoBan);
    virtual ~NhanVien();

    // Getters
    string getMaNV() const;
    string getHoTen() const;
    string getLoaiNV() const;
    string getNgaySinh() const;
    string getGioiTinh() const;
    string getSoDienThoai() const;
    string getEmail() const;
    string getDiaChi() const;
    virtual double getLuongGoc() const = 0;
    virtual double getLuongCoBan(const ChamCong& cc) const = 0;
    string getMaPB() const;

    // Setters
    void setMaNV(string maNV);
    void setHoTen(string hoTen);
    void setNgaySinh(string ngaySinh);
    void setGioiTinh(string gioiTinh);
    void setSoDienThoai(string soDienThoai);
    void setEmail(string email);
    void setDiaChi(string diaChi);
    void setChucVu(string chucVu);
    void setNgayVaoLam(string ngayVaoLam);
    void setLuongCoBan(double luongCoBan);
    void setMaPB(string maPB);

    string getNgayVaoLam() const;
    string getChucVu() const;

    // Pure virtual function - bay gio nhan vao ChamCong
    virtual double tinhLuong(const ChamCong& cc) const = 0;

    // Cac ham ho tro tinh toan tung thanh phan
    virtual double getPhuCap() const { return 0; }
    virtual double getTienTangCa(const ChamCong& cc) const { return 0; }

    // Display basic info
    virtual void hienThiThongTin() const;
    virtual void hienThiChiTiet() const;

    // Serialization for File I/O
    virtual string taoDongDuLieu() const;
};

#endif // NHANVIEN_H
