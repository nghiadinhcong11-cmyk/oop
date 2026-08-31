#ifndef NHANVIENPARTTIME_H
#define NHANVIENPARTTIME_H

#include "NhanVien.h"

class NhanVienPartTime : public NhanVien {
private:
    double luongTheoGio;

public:
    NhanVienPartTime();
    NhanVienPartTime(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
                     std::string soDienThoai, std::string email, std::string diaChi,
                     std::string maPB, std::string chucVu, double luongCoBan,
                     double luongTheoGio);

    double tinhLuong(const ChamCong& cc) const override;
    void hienThiThongTin() const override;

    // Override
    double getTienTangCa(const ChamCong& cc) const override;

    std::string serialize() const override;
};

#endif // NHANVIENPARTTIME_H
