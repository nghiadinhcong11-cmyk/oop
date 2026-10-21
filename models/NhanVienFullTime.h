#ifndef NHANVIENFULLTIME_H
#define NHANVIENFULLTIME_H

#include "NhanVien.h"

using namespace std;

class NhanVienFullTime : public NhanVien {
private:
    double phuCap;
    double tienTangCa;

public:
    NhanVienFullTime();
    NhanVienFullTime(string maNV, string hoTen, string ngaySinh, string gioiTinh,
                     string soDienThoai, string email, string diaChi,
                     string maPB, string chucVu, string ngayVaoLam, double luongCoBan,
                     double phuCap, double tienTangCa);

    double tinhLuong(const ChamCong& cc) const;
    double getLuongGoc() const;
    double getLuongCoBan(const ChamCong& cc) const;
    void hienThiThongTin() const;
    void hienThiChiTiet() const;

    // Ghi de cac ham thanh phan luong
    double getPhuCap() const;
    double getTienTangCa(const ChamCong& cc) const;

    string taoDongDuLieu() const;

    // Getters/Setters
    void setPhuCap(double phuCap);
    double getTienTangCa() const;
    void setTienTangCa(double tienTangCa);
};

#endif // NHANVIENFULLTIME_H
