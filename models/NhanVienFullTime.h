#ifndef NHANVIENFULLTIME_H
#define NHANVIENFULLTIME_H

#include "NhanVien.h"

class NhanVienFullTime : public NhanVien {
private:
    double phuCap;
    double tienTangCa;

public:
    NhanVienFullTime();
    NhanVienFullTime(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
                     std::string soDienThoai, std::string email, std::string diaChi,
                     std::string maPB, std::string chucVu, double luongCoBan,
                     double phuCap, double tienTangCa);

    double tinhLuong(const ChamCong& cc) const override;
    void hienThiThongTin() const override;

    // Override cac thanh phan luong
    double getPhuCap() const override;
    double getTienTangCa(const ChamCong& cc) const override;

    std::string serialize() const override;

    // Getters/Setters
    void setPhuCap(double phuCap);
    double getTienTangCa() const;
    void setTienTangCa(double tienTangCa);
};

#endif // NHANVIENFULLTIME_H
