#ifndef NHANVIENTHUCTAP_H
#define NHANVIENTHUCTAP_H

#include "NhanVien.h"

class NhanVienThucTap : public NhanVien {
private:
    double troCap;

public:
    NhanVienThucTap();
    NhanVienThucTap(std::string maNV, std::string hoTen, std::string ngaySinh, std::string gioiTinh,
                    std::string soDienThoai, std::string email, std::string diaChi,
                    std::string maPB, std::string chucVu, double luongCoBan,
                    double troCap);

    double tinhLuong(const ChamCong& cc) const override;
    void hienThiThongTin() const override;

    double getPhuCap() const override;

    std::string serialize() const override;
};

#endif // NHANVIENTHUCTAP_H
