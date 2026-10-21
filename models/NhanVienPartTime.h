#ifndef NHANVIENPARTTIME_H
#define NHANVIENPARTTIME_H

#include "NhanVien.h"

using namespace std;

class NhanVienPartTime : public NhanVien {
private:
    double luongTheoGio;

public:
    NhanVienPartTime();
    NhanVienPartTime(string maNV, string hoTen, string ngaySinh, string gioiTinh,
                     string soDienThoai, string email, string diaChi,
                     string maPB, string chucVu, string ngayVaoLam, double luongCoBan,
                     double luongTheoGio);

    double tinhLuong(const ChamCong& cc) const;
    double getLuongGoc() const;
    double getLuongCoBan(const ChamCong& cc) const;
    void hienThiThongTin() const;
    void hienThiChiTiet() const;

    // Ghi de ham tang ca
    double getTienTangCa(const ChamCong& cc) const;

    string taoDongDuLieu() const;
};

#endif // NHANVIENPARTTIME_H
