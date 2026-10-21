#ifndef LUONG_H
#define LUONG_H

#include <string>
#include <iostream>

using namespace std;

class Luong {
private:
    string maLuong;
    string maNV;
    string loaiNV;   // Loai nhan vien de hien thi phieu luong dung dinh dang
    int thang;
    int nam;
    double luongGoc;      // Luong goc (FT: Luong thang, PT/TT: Luong/Gio)
    double luongCoBan;    // Luong thuc te (FT: Sau dieu chinh, PT/TT: Luong tinh theo gio)
    double phuCap;
    double tienTangCa;
    double khauTru;
    double luongThucNhan;

public:
    Luong();
    Luong(string maLuong, string maNV, string loaiNV, int thang, int nam,
          double lg, double lcb, double pc, double ttc, double kt, double ltn);

    void hienThiPhieuLuong() const;

    // Getters
    string getMaLuong() const;
    string getMaNV() const;
    string getLoaiNV() const;
    int getThang() const;
    int getNam() const;
    double getLuongGoc() const;
    double getLuongCoBan() const;
    double getPhuCap() const;
    double getTienTangCa() const;
    double getKhauTru() const;
    double getLuongThucNhan() const;

    string taoDongDuLieu() const;
};

#endif // LUONG_H
