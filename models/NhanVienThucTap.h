#ifndef NHANVIENTHUCTAP_H
#define NHANVIENTHUCTAP_H

#include "NhanVien.h"

using namespace std;

class NhanVienThucTap : public NhanVien {
private:
    double troCap;

public:
    NhanVienThucTap();
    NhanVienThucTap(string maNV, string hoTen, string ngaySinh, string gioiTinh,
                    string soDienThoai, string email, string diaChi,
                    string maPB, string chucVu, string ngayVaoLam, double luongCoBan,
                    double troCap);

    double tinhLuong(const ChamCong& cc) const;
    double getLuongGoc() const;
    double getLuongCoBan(const ChamCong& cc) const;
    void hienThiThongTin() const;
    void hienThiChiTiet() const;

    double getPhuCap() const;

    string taoDongDuLieu() const;
};

#endif // NHANVIENTHUCTAP_H
